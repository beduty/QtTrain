#include "hellowidget.h"
#include "ui_hellowidget.h"

HelloWidget::HelloWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HelloWidget)
{
    ui->setupUi(this);
}

HelloWidget::~HelloWidget()
{
    delete ui;
}

