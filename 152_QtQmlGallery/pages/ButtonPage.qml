import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

ScrollablePage {
    id : page

    Column{
        spacing: 40
        width: parent.width

        Label {
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "Button presents a push-button that can be pushed or clicked by the user. "
                + "Buttons are normally used to perform an action, or to answer a question."
        }
        ColumnLayout{
            spacing: 20
            anchors.horizontalCenter : parent.horizontalCenter
            Button{
                text: "First"
                Layout.fillWidth: true
            }
            Button{
                text: "Second"
                focus: true
                //highlighted: true
                Layout.fillWidth: true
            }
            Button{
                text: "Third"
                enabled: false
                Layout.fillWidth: true
            }
        }
    }
}
