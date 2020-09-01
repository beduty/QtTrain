#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include "chessboard.h"

#include <QObject>

/// ChessAlgorithm은 체스게임을 시작하고, 보드 정보를 리턴한다.
/// Private 멤버로 보드정보를 저장한다._체스 말의 위치를 저장한다.

class ChessBoard;
class ChessAlgorithm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Result result READ result)
    Q_PROPERTY(Player currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)

public:
    enum Result{NoResult, Player1Wins, Draw, Player2Wins};
    Q_ENUM(Result)
    enum Player{NoPlayer, Player1, Player2};
    Q_ENUM(Player)

    explicit ChessAlgorithm(QObject *parent = nullptr);
    ChessBoard* board() const;
    inline Result result() const {return m_result;}
    inline Player currentPlayer() const {return m_currentPlayer;}

public slots:
    virtual void newGame();
    virtual bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    bool move(const QPoint &from, const QPoint &to);

signals:
    void boardChanged(ChessBoard*);
    void gameOver(ChessAlgorithm::Result);
    void currentPlayerChanged(Player);

protected:
    virtual void setupBoard();
    void setBoard(ChessBoard* board);
    void setResult(Result);
    void setCurrentPlayer(Player);

private:
    ChessBoard* m_board;
    Result m_result;
    Player m_currentPlayer;
};

#endif // CHESSALGORITHM_H
