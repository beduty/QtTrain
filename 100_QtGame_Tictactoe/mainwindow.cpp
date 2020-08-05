#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <filesystem>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include "configurationdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->startNewGame, &QPushButton::pressed, [](){
//        qDebug() << "Button Pressed!";
//    });
    connect(ui->quit, &QAction::triggered, qApp, &QApplication::quit);

    connect(ui->gameBoard, &TicTacToeWidget::currentPlayerChanged, this, &MainWindow::updateNameLabels);
    connect(ui->gameBoard, &TicTacToeWidget::gameOver, this, &MainWindow::handleGameOver);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::on_startNewGame_clicked()
//{
//}

void MainWindow::updateNameLabels()
{
    setLabelBold(ui->player1Name, ui->gameBoard->currentPlayer() == TicTacToeWidget::Player::Player1);
    setLabelBold(ui->player2Name, ui->gameBoard->currentPlayer() == TicTacToeWidget::Player::Player2);
}

void MainWindow::handleGameOver(TicTacToeWidget::Player winner)
{
    QString message;
    if(winner == TicTacToeWidget::Player::Draw)
        message = ("Game Ended width a draw.");
    else{
        QString winnerName = winner == TicTacToeWidget::Player::Player1?
                    ui->player1Name->text() : ui->player2Name->text();
        message = tr("%1").arg(winnerName);
    }
    QMessageBox::information(this, tr("Info"), message);
}

void MainWindow::setLabelBold(QLabel *label, bool isBold)
{
    QFont f = label->font();
    f.setBold(isBold);
    label->setFont(f);
}

void MainWindow::on_startNewGame_triggered()
{
    ConfigurationDialog dialog(this);
    if(dialog.exec() == QDialog::Rejected)
    {
        return; // do Nothing if dialog rejected;
    }

    ui->player1Name->setText(dialog.player1Name());
    ui->player2Name->setText(dialog.player2Name());
    ui->gameBoard->initNewGame();

}
