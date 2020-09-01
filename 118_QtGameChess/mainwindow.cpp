#include "mainwindow.h"
#include "chessboard.h"
#include "chessview.h"
#include "chessalgorithm.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_selectedField(0)
{
    ui->setupUi(this);
    m_view = new ChessView;
    connect(m_view, &ChessView::clicked, this, &MainWindow::viewClicked);
    // ChessView에서 클릭Signal 보낼 때 처리할 Slot 연결해준다.

    // 대문자는 White를 의미한다. 소문자는 black를 의미한다.
    m_view->setPiece('P', QIcon(":/pieces/Chess_plt45.svg")); // pawn
    m_view->setPiece('K', QIcon(":/pieces/Chess_klt45.svg")); // king
    m_view->setPiece('Q', QIcon(":/pieces/Chess_qlt45.svg")); // queen
    m_view->setPiece('R', QIcon(":/pieces/Chess_rlt45.svg")); // rook
    m_view->setPiece('N', QIcon(":/pieces/Chess_nlt45.svg")); // knight
    m_view->setPiece('B', QIcon(":/pieces/Chess_blt45.svg")); // bishop

    m_view->setPiece('p', QIcon(":/pieces/Chess_pdt45.svg")); // pawn
    m_view->setPiece('k', QIcon(":/pieces/Chess_kdt45.svg")); // king
    m_view->setPiece('q', QIcon(":/pieces/Chess_qdt45.svg")); // queen
    m_view->setPiece('r', QIcon(":/pieces/Chess_rdt45.svg")); // rook
    m_view->setPiece('n', QIcon(":/pieces/Chess_ndt45.svg")); // knight
    m_view->setPiece('b', QIcon(":/pieces/Chess_bdt45.svg")); // bishop

    m_algorithm = new ChessAlgorithm(this);
    m_algorithm->newGame();
    /// 체스판을 만들고, Board의 Piece정보를 업데이트한다. (setFen..)
    /// setFen으로 설정한 Board의 Piece 정보를 가지고, ChessView에서는 직접 Icon을 배치한다.

    m_view->setBoard(m_algorithm->board()); // Board 정보를 받아다가 View에 업데이트한다.
    setCentralWidget(m_view);// m_view를 MainWindow에 붙인다.
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(50,50)); // 체스판 타일 크기를 지정한다.
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::viewClicked(const QPoint &field)
{
    if(m_clickPoint.isNull())
    {
        if(m_view->board()->data(field.x(), field.y()) != ' ')
        {
            // Piece를 선택한 경우에 여기로 들어온다.
            m_clickPoint = field;

            // 선택한 곳을 HighLight 해준다. 정보를 만들고, m_view에 추가한다.
            m_selectedField = new ChessView::FieldHighlight(
                        field.x(), field.y(), QColor(255, 0, 0, 50));
            m_view->addHighlight(m_selectedField);
        }
    } else {
        // 선택된 상태에서 다른 타일을 클릭한 경우에 들어온다.
        if(field != m_clickPoint) {
            // 선택된 타일과 다른 타일이 선택된 경우에는 Piece를 옮긴다.
            m_view->board()->movePiece(m_clickPoint.x(), m_clickPoint.y(), field.x(), field.y());
        }
        // 선택한 포인트를 초기화하고, HighLight된 정보들을 지운다.
        m_clickPoint = QPoint();
        m_view->removeHighlight(m_selectedField);
        delete m_selectedField;
        m_selectedField = 0;
    }
}
