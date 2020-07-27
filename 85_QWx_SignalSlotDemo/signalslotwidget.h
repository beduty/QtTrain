#ifndef SIGNALSLOTWIDGET_H
#define SIGNALSLOTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SignalSlotWidget; }
QT_END_NAMESPACE

class SignalSlotWidget : public QWidget
{
    Q_OBJECT

public:
    SignalSlotWidget(QWidget *parent = nullptr);
    ~SignalSlotWidget();

private:
    Ui::SignalSlotWidget *ui;
};
#endif // SIGNALSLOTWIDGET_H
