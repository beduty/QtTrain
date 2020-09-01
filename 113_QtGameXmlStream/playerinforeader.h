#ifndef PLAYERINFOREADER_H
#define PLAYERINFOREADER_H
#include <QXmlStreamReader>
#include "playerinfo.h"
#include <QIODevice>
class PlayerInfoReader
{
    Q_GADGET
public:
    PlayerInfoReader(QIODevice* device);

    enum class Token{
        Invalid = -1,
        PlayerInfo,
        Player,
        Name, Password, Inventory, Location,
        Position,
        InvItem
    };
    Q_ENUM(Token)

    static Token tokenByName(const QStringRef &r);
    PlayerInfo read();
protected:
    Player readPlayer();
    QVector<InventoryItem> readInventory();
private:
    QXmlStreamReader reader;
};

#endif // PLAYERINFOREADER_H
























