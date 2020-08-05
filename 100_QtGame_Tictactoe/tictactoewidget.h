#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include <QPushButton>
class TicTacToeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TicTacToeWidget(QWidget *parent = nullptr);
    enum class Player{Invalid, Player1, Player2, Draw };
    Q_ENUM(Player)
    Player currentPlayer() const {return m_currentPlayer;}
    void setCurrentPlayer(Player p);
    void initNewGame();

signals:
    void currentPlayerChanged(Player);
    void gameOver(Player);

private slots:
    void handleButtonClick(int index);

private:
    QVector<QPushButton*> m_board;
    Player m_currentPlayer;

    TicTacToeWidget::Player checkWinCondition() const;
    TicTacToeWidget::Player checkWinConditionForLine(int index1, int index2, int index3) const;
};
#endif // TICTACTOEWIDGET_H
