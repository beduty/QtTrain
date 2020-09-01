#include "movie.h"

Movie::Movie(QObject *parent) : QObject(parent),
    m_title("Movie Title"),
    m_character("Main Character")
{

}

QString Movie::title() const
{
    return m_title;
}

QString Movie::character() const
{
    return m_character;
}

void Movie::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void Movie::setCharacter(QString character)
{
    if (m_character == character)
        return;

    m_character = character;
    emit characterChanged(m_character);
}
