#include "playerinfo.h"
#include <QMetaEnum>

InventoryItem::Type InventoryItem::typeByName(const QStringRef &r)
{
    // 문자열로부터 Enum값을 가져올 수 있다.
    // Meta타입 QMetaEnum을 만들고, const char *로 변환해서
    //  keysToValue를 넣는다. -> enum 값으로 리턴된다
    QMetaEnum metaEnum = QMetaEnum::fromType<InventoryItem::Type>();
    QByteArray latin1 = r.toLatin1();
    int result = metaEnum.keysToValue(latin1.constData());
    return static_cast<InventoryItem::Type>(result);
}
