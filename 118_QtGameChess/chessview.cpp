#include "chessview.h"
#include "chessboard.h"
#include <QMouseEvent>
#include <QPainter>

ChessView::ChessView(QWidget *parent) : QWidget(parent)
{

}

void ChessView::setBoard(ChessBoard *board)
{
    if(m_board == board) return;

    if(m_board) {
        // 기존에 연결되어있던 Signal-slot을 해제한다.
        m_board->disconnect(this);
    }
    m_board = board;
    // 새로운 Board와 다시 Signal-Slot을 연결한다.
    if(board){
        // Slot처리 update()는 화면 업데이트를 의미한다.
        connect(board, SIGNAL(dataChanged(int,int)), this, SLOT(update()));
        connect(board, SIGNAL(boardReset()), this, SLOT(update()));
    }
    updateGeometry();
}

ChessBoard *ChessView::ChessView::board() const
{
    return m_board;
}

QSize ChessView::fieldSize() const
{
    return m_fieldSize;
}

void ChessView::setFieldSize(QSize fieldSize)
{
    if (m_fieldSize == fieldSize)
        return;

    m_fieldSize = fieldSize;
    emit fieldSizeChanged(fieldSize);
    updateGeometry();
}

QSize ChessView::sizeHint() const
{
    if(!m_board) return QSize(100,100);
    QSize boardSize = QSize(fieldSize().width()  * m_board->columns() +1,
                            m_fieldSize.height() * m_board->ranks()   +1);
    int rankSize = fontMetrics().width('M')+4; // font 사이즈를 리턴한다! (M이 Font크기가 가장 크기때문!)
    int columnSize = fontMetrics().height()+4; // 그정도 크기만 있으면 되기 떄문!
    return boardSize+QSize(rankSize, columnSize);
}

QRect ChessView::fieldRect(int column, int rank) const
{
    if(!m_board) return QRect();
    const QSize fs = fieldSize(); // 50x50 사이즈를 리턴한다.
    QRect fRect = QRect(QPoint((column-1)*fs.width(), (m_board->ranks()-rank)*fs.height()), fs);
    // 컬럼, 랭크 정보를 기반으로 Tile사이즈 더하면 타일의 위치와 크기를 알 수 있다.
    // (column-1)인 이유는 Rank번호 기록할때 위치 조정하기 위해서이다. 랭크 기록하는 곳은 딱 숫자만 입력하게 되어 있어서
    // fs.width()를 곱해주면 공간이 너무 커지기 때문에 인덱스에 -1을 해준다.

    // 왼쪽 테두리에 Rank 정보가 있으므로 그만큼 더해줘야 한다. (offset)
    int offset = fontMetrics().width('M'); // 'M' 이 문자중에는 가장 큰 문자라 이를 기준으로 삼는다.
    return fRect.translated(offset+4, 0);
}

void ChessView::setPiece(char type, const QIcon &icon)
{
    /// Piece정보를 QMap으로 관리한다.
    ///  char 'p'에 해당하는 QIcon을 바로 얻어올 수 있다.
    m_pieces.insert(type, icon);
    update();
}

QIcon ChessView::piece(char type) const
{
    // char넣으면 해당하는 값 리턴한다.
    return m_pieces.value(type, QIcon());
}

void ChessView::paintEvent(QPaintEvent *)
{
    if(!m_board) return;
    QPainter painter(this);
    for(int r = m_board->ranks(); r>0; --r) {
         ///   1. 랭크 정보를 그린다.(측면 테두리 숫자 텍스트)
        painter.save();
        drawRank(&painter, r);
        painter.restore();
    }
    for(int c = 1; c<=m_board->columns();++c) {
        ///   2. 컬럼 정보를 그린다.(하단 테두리 알파벳 텍스트)
        painter.save();
        drawColumn(&painter, c);
        painter.restore();
    }
    for(int r = 1; r<=m_board->ranks();++r) {
        for(int c = 1; c<=m_board->columns();++c) {
            ///   3. Field(타일) 그린다.
            painter.save();
            drawField(&painter, c, r);
            painter.restore();
        }
    }
    ///   4. 선택된 내용(HighHight) 그린다.
    drawHighlights(&painter);
    for(int r = m_board->ranks(); r>0; --r) {
        for(int c = 1; c<=m_board->columns();++c) {            
            ///   5. Icon(Piece) 그린다.
            drawPiece(&painter, c, r);
        }
    }
}

void ChessView::drawRank(QPainter *painter, int rank)
{
    QRect r = fieldRect(1, rank);
    QRect rankRect = QRect(0, r.top(), r.left(), r.height()).adjusted(2, 0, -2, 0);
    QString rankText = QString::number(rank);
    painter->drawText(rankRect, Qt::AlignVCenter|Qt::AlignRight, rankText);
}

void ChessView::drawColumn(QPainter *painter, int column)
{
    QRect r = fieldRect(column, 1);
    QRect columnRect = QRect(r.left(), r.bottom(),
                             r.width(), height()-r.bottom()).adjusted(0, 2, 0, -2);
    painter->drawText(columnRect, Qt::AlignHCenter|Qt::AlignTop, QChar('a'+column-1));
}

void ChessView::drawField(QPainter *painter, int column, int rank)
{
    // 체스판 타일을 그린다.
    QRect rect = fieldRect(column, rank);
    QColor fillColor = (column+rank) % 2 ? palette().color(QPalette::Light)
                                         : palette().color(QPalette::Mid);
    painter->setPen(palette().color(QPalette::Dark));
    painter->setBrush(fillColor);
    painter->drawRect(rect);
}

void ChessView::drawPiece(QPainter *painter, int column, int rank)
{
    // 보드의 데이터 얻어와서 QIcon 을 그린다.!
    QRect rect = fieldRect(column, rank);
    char value = m_board->data(column, rank);
    if(value != ' ') {
        QIcon icon = piece(value);
        if(!icon.isNull()) {
            icon.paint(painter, rect, Qt::AlignCenter);
        }
    }
}

void ChessView::drawHighlights(QPainter *painter)
{
    // 선택된 Piece에 해당하는 하이라이트를 그린다.
    for(int idx=0; idx < highlightCount(); ++idx) {
        Highlight *hl = highlight(idx);
        if(hl->type() == FieldHighlight::Type) {
            FieldHighlight *fhl = static_cast<FieldHighlight*>(hl);
            QRect rect = fieldRect(fhl->column(), fhl->rank());
            painter->fillRect(rect, fhl->color());
        }
    }
}

QPoint ChessView::fieldAt(const QPoint &pt) const
{
    // 현재 찍은 포인트에 해당하는 타일의 정보를 받아서, 타일의 좌상단으로 바꾸고 리턴한다.
    if(!m_board) return QPoint();
    const QSize fs = fieldSize();
    int offset = fontMetrics().width('M')+4; // 'M' is the widest letter
    if(pt.x() < offset) return QPoint();
    int c = (pt.x()-offset) / fs.width();
    int r = pt.y()/fs.height();
    if(c < 0 || c >= m_board->columns() || r<0 || r >= m_board->ranks())
        return QPoint();
    return QPoint(c+1, m_board->ranks() - r); // max rank - r
}

void ChessView::mouseReleaseEvent(QMouseEvent *event)
{
    // 마우스 뗄때 시그널 보낸다.
    // 메인 윈도우에서 이를 받아서 Hight처리와 Piece 움직이는 동작을 수행한다.
    QPoint pt = fieldAt(event->pos());
    if(pt.isNull()) return;
    emit clicked(pt);
}

void ChessView::addHighlight(ChessView::Highlight *hl)
{
    // 마우스로 선택할떄 추가된다.
    m_highlights.append(hl);
    update();
}

void ChessView::removeHighlight(ChessView::Highlight *hl)
{
    // 선택된 상태에서 마우스로 다른곳 클릭할때 사라진다.
    m_highlights.removeOne(hl);
    update();
}
