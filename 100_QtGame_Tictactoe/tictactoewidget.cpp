#include "tictactoewidget.h"
#include <QGridLayout>
#include <QSignalMapper>
TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{
    m_currentPlayer = Player::Invalid;

    QSignalMapper* mapper = new QSignalMapper(this);
    // 직접 위젯을 만들때 포함되는 많은 오브젝트들의 Signal관리는 QSignalMapper로 처리해준다.
    // connect(button, SIGNAL(clicked()), mapper, SLOT(map()))로 등록하면, 버튼이 눌려서 Signal이
    // Mapper로 몰리고, 여기서 QSignalMapper가 몇번 Idx의 버튼이 눌렸는지 파악하여 다시 Signal보낸다!

    QGridLayout *gridLayout = new QGridLayout(this);
    for(int row = 0; row <3; ++row)
    {
        for (int column = 0; column<3; ++column) {
            QPushButton *button = new QPushButton(" ");
            button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            gridLayout->addWidget(button, row, column);
            m_board.append(button);
            mapper->setMapping(button, m_board.count()-1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
}

void TicTacToeWidget::setCurrentPlayer(TicTacToeWidget::Player p)
{
    if(m_currentPlayer == p)
        return;
    m_currentPlayer = p;
    emit currentPlayerChanged(p);
}

void TicTacToeWidget::initNewGame()
{
    for(QPushButton *button : m_board)
    {
        button->setText(" ");
    }
    setCurrentPlayer(Player::Player1);
}

void TicTacToeWidget::handleButtonClick(int index)
{
    if(m_currentPlayer == Player::Invalid)
        return; // Game is Not Started.

    if(index < 0 || index >= m_board.size())
        return ; // out of bounds check

    QPushButton *button = m_board.at(index);
    if(button->text() != " ")
        return; // Invalid Move

    button->setText(currentPlayer() == Player::Player1 ? "X" : "O");
    Player winner = checkWinCondition();
    if(winner == Player::Invalid){
        setCurrentPlayer(currentPlayer() == Player::Player1 ? Player::Player2 : Player::Player1);
        return;
    }
    else{
        emit gameOver(winner);
    }
}

TicTacToeWidget::Player TicTacToeWidget::checkWinCondition() const
{
    Player result = Player::Invalid;
    // check horizontals
    for(int row = 0; row < 3; ++row) {
        result = checkWinConditionForLine(row * 3,
                                          row * 3 + 1,
                                          row * 3 + 2);
        if (result != Player::Invalid) {
            return result;
        }
    }
    // check verticals
    for(int column = 0; column < 3; ++column) {
         result = checkWinConditionForLine(column,
                                           3 + column,
                                           6 + column);
        if (result != Player::Invalid) {
            return result;
        }
    }
    // check diagonals
    result = checkWinConditionForLine(0, 4, 8);
    if (result != Player::Invalid) {
        return result;
    }
    result = checkWinConditionForLine(2, 4, 6);
    if (result != Player::Invalid) {
        return result;
    }
    // check if there are unoccupied fields left
    for(QPushButton *button: m_board) {
        if(button->text() == " ") {
            return Player::Invalid;
        }
    }
    return Player::Draw;
}

TicTacToeWidget::Player TicTacToeWidget::checkWinConditionForLine(int index1, int index2, int index3) const
{
    QString text1 = m_board.at(index1)->text();
    if(text1 == " ")
        return Player::Invalid;
    QString text2 = m_board.at(index2)->text();
    QString text3 = m_board.at(index3)->text();
    if(text1 == text2 && text1 == text3)
    {
        return text1 == "X" ? Player::Player1 : Player::Player2;
    }
    return Player::Invalid;
}













