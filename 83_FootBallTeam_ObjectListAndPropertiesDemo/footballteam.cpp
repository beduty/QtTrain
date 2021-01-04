#include <QDebug>
#include "footballteam.h"

FootBallTeam::FootBallTeam(QObject *parent) : QObject(parent)
{

//    m_player1.setName("Player1");
//    m_player1.setPosition("Middle Field1");
//    m_player1.setPlaying(true);

//    m_player2.setName("Player2");
//    m_player2.setPosition("Middle Field2");
//    m_player2.setPlaying(false);

//    m_player3.setName("Player3");
//    m_player3.setPosition("Middle Field3");
//    m_player3.setPlaying(true);

//    m_player4.setName("Player4");
//    m_player4.setPosition("Middle Field4");
//    m_player4.setPlaying(true);

//    m_player5.setName("Player5");
//    m_player5.setPosition("Middle Field5");
//    m_player5.setPlaying(false);

//    m_players.append(&m_player1);
//    m_players.append(&m_player2);
//    m_players.append(&m_player3);
//    m_players.append(&m_player4);
//    m_players.append(&m_player5);
}

QString FootBallTeam::title() const
{
    return m_title;
}

QString FootBallTeam::coatch() const
{
    return m_coatch;
}

Player *FootBallTeam::captain() const
{
    return m_captain;
}

void FootBallTeam::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void FootBallTeam::setCoatch(QString coatch)
{
    if (m_coatch == coatch)
        return;

    m_coatch = coatch;
    emit coatchChanged(m_coatch);
}

void FootBallTeam::setCaptain(Player *captain)
{
    if (m_captain == captain)
        return;

    m_captain = captain;
    emit captainChanged(m_captain);
}

QQmlListProperty<Player> FootBallTeam::players()
{
    return QQmlListProperty<Player>(this,this,&FootBallTeam::appendPlayer,
                                    &FootBallTeam::playerCount,
                                    &FootBallTeam::player,
                                    &FootBallTeam::clearPlayers);
}

void FootBallTeam::appendPlayerCustom(Player * player)
{
    qDebug()<< "Adding player to vector"<< player->name();
    m_players.append(player);
}

int FootBallTeam::playerCountCustom() const
{
    return m_players.count();
}

Player *FootBallTeam::playerCustom(int index) const
{
    return m_players.at(index);
}

void FootBallTeam::clearPlayersCustom()
    {
        m_players.clear();
}

void FootBallTeam::appendPlayer(QQmlListProperty<Player> * list, Player * player)
{
    reinterpret_cast<FootBallTeam*>(list->data)->appendPlayerCustom(player);
}

int FootBallTeam::playerCount(QQmlListProperty<Player> * list)
{
    return reinterpret_cast<FootBallTeam*>(list->data)->playerCountCustom();
}

Player *FootBallTeam::player(QQmlListProperty<Player> * list, int index)
{
    return reinterpret_cast<FootBallTeam*>(list->data)->playerCustom(index);
}

void FootBallTeam::clearPlayers(QQmlListProperty<Player> * list)
{
    reinterpret_cast<FootBallTeam*>(list->data)->clearPlayersCustom();
}
