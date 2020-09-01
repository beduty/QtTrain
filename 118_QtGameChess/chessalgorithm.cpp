#include "chessalgorithm.h"
#include "chessboard.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject(parent), m_board(0)
{

}

ChessBoard *ChessAlgorithm::board() const
{
    return m_board;
}

void ChessAlgorithm::newGame()
{
    // 체스판을 새로 만들고, setFen을 통해서 체스판의 Piece 정보를 초기화한다.
    setupBoard();
    board()->setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8,8, this));
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if(board == m_board) return;
    if(m_board) delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

