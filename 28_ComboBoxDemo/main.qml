import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("ComboBox Demo")
    Column{
        spacing: 40
        width: parent.width
        Label {
            text: "Non Editable Combo"
            wrapMode: Label.wrapMode
            horizontalAlignment: Qt.AlignHCenter
            width: parent.width
        }

        ComboBox{
            id : nonEditabbleComboId
            model : ["One","Two","Three","Four","Five"]
            anchors.horizontalCenter: parent.horizontalCenter
            onActivated: {
                console.log("[" + currentIndex + "]" + currentText + "is activated")
            }
        }


        Label {
            text: "Editable Combo"
            wrapMode: Label.wrapMode
            horizontalAlignment: Qt.AlignHCenter
            width: parent.width
        }

        ComboBox{
            id : editabbleComboId
            editable: true
            textRole : "text"
            model : ListModel{
                id : model
                ListElement{text : "Dog"; location2 : "Kigali"}
                ListElement{text : "Chiken"; location2 : "Beijing"}
                ListElement{text : "Cat"; location2 : "Mumbai"}
                ListElement{text : "MeerKat"; location2 : "Paris"}
            }

            anchors.horizontalCenter: parent.horizontalCenter
            onActivated: {
                console.log("[" + currentIndex + "]" + currentText + "is activated")
            }
            onAccepted: {
                if(find(editText) === -1){
                    model.append({ text : editText, location2 : "US"})
                }
            }
        }

        Button{
            text: "Capture current element"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                console.log("[" + model.get(editabbleComboId.currentIndex).text + "] : " + model.get(editabbleComboId.currentIndex).location2)
            }
        }
    }
}
