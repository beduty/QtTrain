import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Frame Demo")
    RowLayout{
        anchors.centerIn: parent
        Layout.margins: 200
        Layout.alignment: Qt.AlignCenter
        Frame{
            ColumnLayout{
                Button{ text : "Button1" }
                Button{ text : "Button2" }
                Button{ text : "Button3" }
            }
        }
        Frame{
            ColumnLayout{
                CheckBox{ text : "E-mail" }
                CheckBox{ text : "Calendar" }
                CheckBox{ text : "Contacts" }
            }
        }
    }
}
