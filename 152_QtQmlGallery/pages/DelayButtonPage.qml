import QtQuick 2.0
import QtQuick.Controls 2.12

ScrollablePage {
    id : page
    Column{
        spacing: 40
        width: parent.width
        Label{
            wrapMode: Label.Wrap
            horizontalAlignment: Text.AlignHCenter
            text : "DelayButton is a checkable button that incorporates a deley"
            + "before the button is activated. This delay prevent accidental pressed"
            width: parent.width
        }

        DelayButton{
            text: "DelayButton"
            delay: 1000
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
