import QtQuick 2.12
import QtQuick.Controls 2.12

ScrollablePage{
    id : page
    Column{
        spacing: 40
        width: parent.width
        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "BusyIndicator is used to indicate activity while content is being loaded,"
                  + " or when the UI is blocked waiting for a resource to become available."
        }
        BusyIndicator{
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
