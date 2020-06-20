import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CheckBox Demo")

    ColumnLayout{
        spacing: 20
        anchors.horizontalCenter:  parent.horizontalCenter
        CheckBox{
            text: "Option1"
            checked : true
            onCheckStateChanged: {
                if (checked === true){
                    console.log("Option1 is checked")
                }else{
                    console.log("Option1 is unchecked")
                }
            }
        }
        CheckBox{
            text: "Option2"
            checked : true
            onCheckStateChanged: {
                if (checked === true){
                    console.log("Option2 is checked")
                }else{
                    console.log("Option2 is unchecked")
                }
            }
        }
        CheckBox{
            text: "Option3"
            checked : false
            enabled: false
        }
    }
}


