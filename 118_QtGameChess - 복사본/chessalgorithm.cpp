#include "chessalgorithm.h"
#include "chessboard.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent)
    : QObject(parent), m_board(0),m_result(NoResult), m_currentPlayer(NoPlayer)
{

}

ChessBoard *ChessAlgorithm::board() const
{
    return  m_board;
}

void ChessAlgorithm::newGame()
{
    setupBoard();
    board()->setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void ChessAlgorithm::setupBoard()
{
    // 8x8 크기의 체스 판을 설정한다.
    setBoard(new ChessBoard(8,8,this));
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    // 기존의 체스판정보를 지우고, 새로운 체스판 정보로 업데이트 한다.
    if(board == m_board)
        return;
    if(m_board)
        delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

void ChessAlgorithm::setResult(ChessAlgorithm::Result value)
{
    if(result() == value)
        return;
    if(result() == NoResult){
        m_result = value;
        emit gameOver(m_result);
    }else{
        m_result = value;
    }
}

void ChessAlgorithm::setCurrentPlayer(ChessAlgorithm::Player value)
{
    if(currentPlayer() == value)
        return;
    m_currentPlayer = value;
    emit currentPlayerChanged(m_currentPlayer);
}

bool ChessAlgorithm::move(int colFrom, int rankFrom, int colTo, int rankTo)
{
    Q_UNUSED(colFrom)
    Q_UNUSED(rankFrom)
    Q_UNUSED(colTo)
    Q_UNUSED(rankTo)
    return false;
}

bool ChessAlgorithm::move(const QPoint &from, const QPoint &to)
{
    return move(from.x(), from.y(), to.x(), to.y());
}
