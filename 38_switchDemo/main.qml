import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Switch Demo")

    Column{
        width: parent.width
        spacing: 20
        Switch{
            anchors.horizontalCenter:
                    parent.horizontalCenter
            text: "Wifi"
            checked: false
            onCheckedChanged: {
                if(checked === true)
                {
                    console.log("Wifi On")
                }else{
                    console.log("Wifi Off")
                }
            }
        }
        Switch{
            anchors.horizontalCenter:
                    parent.horizontalCenter
            text: "BlueTooth"
            checked: true
        }
        Switch{
            anchors.horizontalCenter:
                    parent.horizontalCenter
            text: "NFC"
            enabled: false
        }
    }

}
