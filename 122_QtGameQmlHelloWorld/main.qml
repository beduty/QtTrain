import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 250
    height: 150
    title: qsTr("Hello World")

    Column{
        anchors.centerIn: parent
        spacing: 30
        TextField{
            id : textField
            text: "Edit me"
        }
        Label{
            text: {
                var x = textField.text
                return "(" + x + ")"
            }
        }
    }
}
