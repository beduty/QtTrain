#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVector>

/// View-Model 패턴으로 치면 Model에 해당된다.
/// 체스판 상태를 저장한다.
/// QVector<char> m_boardData; 로 (int m_ranks, m_columns)만큼 데이터를 가진다.
/// View에서 Click Signal을 MainWindow에서 Slot처리하는데,
/// Slot처리할 때 m_boardData의 데이터를 변경한다. (ChessBoard::movePiece(..))
///
class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int ranks = 8, int columns = 8, QObject *parent = 0);

    int ranks() const { return m_ranks; }
    int columns() const { return m_columns; }
    char data(int column, int rank) const; /// 행,열에 해당되는 Piece 정보를 리턴한다.
    void setData(int column, int rank, char value); /// Piece 정보를 업데이트한다.
    void movePiece(int fromColumn, int fromRank, int toColumn, int toRank); /// from -> to 로 Piece를 옮긴다.
    void setFen(const QString &fen); /// 문자열로 모든 체스판의 Piece정보를 설명할 수 있다.

protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    void initBoard(); /// 체스판 정보를 저장하는  m_boardData의 내용을 초기화한다.
    bool setDataInternal(int column, int rank, char value); /// Piece 정보를 업데이트한다.

signals:
    /// 시그널을 보내면 View에서 Slot으로 처리한다. Piece정보가 업데이트될때 시그널을 보내고, View에서 업데이트한다.
    void ranksChanged(int);
    void columnsChanged(int);
    void boardReset();
    void dataChanged(int c, int r);

private:
    int m_ranks, m_columns;
    QVector<char> m_boardData;
};

#endif // CHESSBOARD_H
