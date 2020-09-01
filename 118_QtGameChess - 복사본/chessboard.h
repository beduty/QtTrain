#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged) // Row이다.
    Q_PROPERTY(int columns READ columns NOTIFY columnChanged)

public:
    explicit ChessBoard(int rank, int column,QObject *parent = nullptr);
    int ranks() const{return m_ranks;}
    int columns() const{return m_columns;}
    char data(int column, int rank);
    void setData(int column, int rank, char value);
    void movePiece(int fromColumn, int fromRank, int toColumn, int toRank);
    void setFen(const QString &fen); // fen은 체스 표기법을 의미한다.

protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    void initBoard();
    bool setDataInternal(int column, int rank, char value);

signals:
    void ranksChanged(int rank);
    void columnChanged(int column);
    void boardReset();
    void dataChanged(int c, int r);

private:
    int m_ranks, m_columns;
    QVector<char> m_boardDarta;
};

#endif // CHESSBOARD_H
