#include <QDataStream>
#include <QFile>
#include <QtDebug>
#include "playerinforeader.h"

int main(int argc, char *argv[])
{
    QFile file(":/playerinfo.xml");
    file.open(QFile::ReadOnly | QFile::Text);

    PlayerInfoReader reader(&file);
    PlayerInfo playerInfo = reader.read();
    if(!playerInfo.players.isEmpty()){
        qDebug() << "Name : " << playerInfo.players.first().name;
        qDebug() << "Password : " << playerInfo.players.first().password;
        qDebug() << "Hp : " << playerInfo.players.first().hitPoints;
        qDebug() << "Exp : " << playerInfo.players.first().experience;
        qDebug() << "Count : " << playerInfo.players.count();
        qDebug() << "Size of inventory : " << playerInfo.players.first().inventory.size();
        qDebug() << "Inventory item 1 : " << playerInfo.players.first().inventory[0].type
                 << playerInfo.players.first().inventory[0].subType
                 << playerInfo.players.first().inventory[0].durability;
        qDebug() << "Inventory item 2 : " << playerInfo.players.first().inventory[1].type
                 << playerInfo.players.first().inventory[1].subType
                 << playerInfo.players.first().inventory[1].durability;
        qDebug() << "Room : " << playerInfo.players.first().location
                 << playerInfo.players.first().position;
    }
    file.close();
    return 0;
}
