#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>

/// ChessView에서는 판단등의 작업은 하지 않는다.
/// ChessBoard에서 정보 업데이트 될 때 보내는 Signal받아서 Slot처리만 한다!
/// View에서 그리는 작업은 다음과 같다. (paintEvent)
///   1. 랭크 정보를 그린다.(측면 테두리 숫자 텍스트)
///   2. 컬럼 정보를 그린다.(하단 테두리 알파벳 텍스트)
///   3. Field(타일) 그린다.
///   4. 선택된 내용(HighHight) 그린다.
///   5. Icon(Piece) 그린다.
///

class ChessBoard;
class ChessView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize fieldSize
               READ fieldSize WRITE setFieldSize
               NOTIFY fieldSizeChanged)
public:
    class Highlight {
    public:
        Highlight() {}
        virtual ~Highlight() {}
        virtual int type() const { return 0; }
    };

    class FieldHighlight : public Highlight {
    public:
        enum { Type = 1 };
        FieldHighlight(int column, int rank, QColor color)
            : m_field(column, rank), m_color(color) {}
        inline int column() const { return m_field.x(); }
        inline int rank() const { return m_field.y(); }
        inline QColor color() const { return m_color; }
        int type() const { return Type; }
    private:
        QPoint m_field;
        QColor m_color;
    };

    explicit ChessView(QWidget *parent = 0);
    void setBoard(ChessBoard*);
    ChessBoard* board() const;
    QSize fieldSize() const;
    QSize sizeHint() const;
    QRect fieldRect(int column, int rank) const;
    void setPiece(char type, const QIcon &icon);
    QIcon piece(char type) const;
    QPoint fieldAt(const QPoint &pt) const;

    void addHighlight(Highlight *hl);
    void removeHighlight(Highlight *hl);
    inline Highlight *highlight(int index) const { return m_highlights.at(index); }
    inline int highlightCount() const { return m_highlights.size(); }

public slots:
    void setFieldSize(QSize fieldSize);

signals:
    void fieldSizeChanged(QSize fieldSize);
    void clicked(const QPoint &);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    virtual void drawColumn(QPainter *painter, int column);
    virtual void drawRank(QPainter *painter, int rank);
    virtual void drawField(QPainter *painter, int column, int rank);
    virtual void drawPiece(QPainter *painter, int column, int rank);
    virtual void drawHighlights(QPainter *painter);

private:
    QPointer<ChessBoard> m_board;
    QSize m_fieldSize;
    QMap<char,QIcon> m_pieces;
    QList<Highlight*> m_highlights;
};

#endif // CHESSVIEW_H
