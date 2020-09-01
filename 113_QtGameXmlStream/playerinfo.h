#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QString>
#include <QVector>
#include <QPoint>
#include <QObject>
class InventoryItem;
class Player;
struct PlayerInfo{
    QVector<Player> players;
};

class InventoryItem{
    Q_GADGET // Q_ENUM 을 사용하려면 Q_GADGET을 추가해줘야 한다.
    // Q_ENUM을 쓰면 열거형<->문자열로 상호 변환할 수 있다.
public:
    enum class Type{
        Weapon,
        Armor,
        Gem,
        Book,
        Other
    };
    Q_ENUM(Type)

    Type type;
    QString subType;
    int durability;
    static Type typeByName(const QStringRef &r);
};

class Player{
public:
    QString name;
    QString password;
    int experience;
    int hitPoints;
    QVector<InventoryItem> inventory;
    QString location;
    QPoint position;
};

#endif // PLAYERINFO_H
