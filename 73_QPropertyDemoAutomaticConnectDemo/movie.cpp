#include "movie.h"
#include <QDebug>
Movie::Movie(QObject *parent) : QObject(parent),
    m_mainCharcter("Main Character"),
    m_title("Moview Title")
{

}

QString Movie::mainCharcter() const
{
    qDebug() << "Getting the main character";
    return m_mainCharcter;
}

QString Movie::title() const
{
    qDebug() << "Getting the title";
    return m_title;
}

void Movie::setmainCharcter(QString mainCharcter)
{
    qDebug() << "Setting the main character";
    if (m_mainCharcter == mainCharcter)
        return;

    m_mainCharcter = mainCharcter;
    // 여기서 Emit해줬기때문에 바인딩된 Qml 객체에서 업데이트 한다!
    // emit을 주석처리하면 변수가 바뀌어도 Qml에서 변경되지 않는다.
    emit mainCharcterChanged(m_mainCharcter);
}

void Movie::settitle(QString title)
{
    qDebug() << "Setting the title";
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}
