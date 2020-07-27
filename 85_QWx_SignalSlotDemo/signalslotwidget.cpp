#include "signalslotwidget.h"
#include "ui_signalslotwidget.h"

SignalSlotWidget::SignalSlotWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignalSlotWidget)
{
    ui->setupUi(this);
}

SignalSlotWidget::~SignalSlotWidget()
{
    delete ui;
}

