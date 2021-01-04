#ifndef SINGLETONCLASS_H
#define SINGLETONCLASS_H

#include <QObject>
#include <QTimer>
#include <QQmlEngine>
#include <QJSEngine>

class SingletonClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int someProperty READ someProperty WRITE setSomeProperty NOTIFY somePropertyChanged)

public:
    explicit SingletonClass(QObject *parent = nullptr);
    int someProperty() const;
    static QObject* singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:
    void setSomeProperty(int someProperty);

signals:
    void somePropertyChanged(int someProperty);

private:
    int m_someProperty;
    QTimer *m_timer;
};

#endif // SINGLETONCLASS_H
