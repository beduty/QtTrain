#include "chessboard.h"

ChessBoard::ChessBoard(int ranks, int columns, QObject *parent)
    : QObject(parent), m_ranks(ranks), m_columns(columns)
{
    initBoard();
}

char ChessBoard::data(int column, int rank) const
{
    /// column과 rank에 해당하는 데이터를 리턴한다.
    return m_boardData.at((rank-1)*columns()+(column-1));
}

void ChessBoard::setData(int column, int rank, char value)
{
    if(setDataInternal(column, rank, value))
        emit dataChanged(column, rank);
}

void ChessBoard::movePiece(int fromColumn, int fromRank, int toColumn, int toRank)
{
    /// 기존에 있던 위치의 데이터를 To 로 옮긴다.
    /// From.에 있던 데이터는 이제 비었으므로 ' '로 초기화한다.
    setData(toColumn, toRank, data(fromColumn, fromRank));
    setData(fromColumn, fromRank, ' ');
}

void ChessBoard::initBoard()
{
    /// 체스판 데이터(m_boardData)초기화
    /// m_boardData 내용을 ' '로 채워 초기화한다.
    m_boardData.fill(' ', ranks()*columns());
    emit boardReset();
}

bool ChessBoard::setDataInternal(int column, int rank, char value)
{
    ///setData(..)에서 호출되어 체스판 데이터(m_boardData) 업데이트 한다.
    int index = (rank-1)*columns()+(column-1);
    if(m_boardData.at(index) == value) return false;
    m_boardData[index] = value;
    return true;
}

void ChessBoard::setFen(const QString &fen)
{
    /// 다음과 같이 들어온다.
    /// board()->setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    /// '/'는 줄문자이다. 한줄을 의미한다.
    /// '/' 앞에 있는 rnbqkbnr는 룩, 나이트, 비숍, 퀸, 킹 ~을 나타낸다.
    /// 'p'는 폰을 의미한다.
    /// 숫자 '8'은 그냥 없는 공백을 의미한다.
    /// 대문자는 흰색을 의미한다. 소문자는 검정색
    /// 'w'는 화이트 차례 먼저임을 알린다.
    int index = 0;
    int skip = 0;
    const int columnCount = columns();
    QChar ch;
    for(int rank = ranks(); rank >0; --rank) {
        for(int column = 1; column <= columnCount; ++column) {
            if(skip > 0) {
                ch = ' ';
                skip--;
            } else {
                ch = fen.at(index++);
                if(ch.isDigit()) {
                    skip = ch.toLatin1()-'0';
                    ch = ' ';
                    skip--;
                }
            }
            setDataInternal(column, rank, ch.toLatin1());
        }
        QChar next = fen.at(index++);
        if(next != '/' && next != ' ') {
            initBoard();
            return; // fail on error
        }
    }
    emit boardReset();
}
