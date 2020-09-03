#include "learnqtlogo.h"

LearnQtLogo::LearnQtLogo(QObject *parent) : QObject(parent)
{

}

QColor LearnQtLogo::bgColor() const
{
    return m_bgColor;
}

QColor LearnQtLogo::textColor() const
{
    return m_textColor;
}

QString LearnQtLogo::text() const
{
    return m_text;
}

LearnQtLogo::QtTopic LearnQtLogo::topic() const
{
    return m_topic;
}

void LearnQtLogo::setBgColor(QColor bgColor)
{
    if (m_bgColor == bgColor)
        return;

    m_bgColor = bgColor;
    emit bgColorChanged(m_bgColor);
}

void LearnQtLogo::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(m_textColor);
}

void LearnQtLogo::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(m_text);
}

void LearnQtLogo::setTopic(LearnQtLogo::QtTopic topic)
{
    if (m_topic == topic)
        return;

    m_topic = topic;
    emit topicChanged(m_topic);
}
