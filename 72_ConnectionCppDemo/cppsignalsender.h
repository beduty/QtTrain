#ifndef CPPSIGNALSENDER_H
#define CPPSIGNALSENDER_H

#include <QObject>
#include <QTimer>

class CppSignalSender : public QObject
{
    Q_OBJECT
public:
    explicit CppSignalSender(QObject *parent = nullptr);

signals: //emit
    void callQml(QString parameter);
    void cppTimer(QString value);

public slots: //capture
    void cppSlot();
private:
    QTimer *mTimer;
    int mValue;

};

#endif // CPPSIGNALSENDER_H
