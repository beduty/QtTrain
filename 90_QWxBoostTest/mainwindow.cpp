#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    boost::thread worker([](){
        boost::posix_time::seconds sleep_time(3);
        boost::this_thread::sleep(sleep_time);
        qDebug()<<"Thread_work Button Click!!"<<endl;
    });
    //qDebug()<<"Button Click!!"<<endl;
    worker.join();
}
