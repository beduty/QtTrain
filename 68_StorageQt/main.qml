import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.settings 1.0
import QtQuick.Dialogs 1.2

Window {
    id : rootId
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Storage Setting Demo")

    Rectangle{
        id : rectId
        anchors.fill: parent
        color: "red"
        MouseArea{
            anchors.fill : parent
            onClicked: {
                colorDialogId.open()
            }
            ColorDialog{
                id : colorDialogId
                title : "Please choose a color"
                onAccepted: {
                    console.log("The new color is :  "+ color)
                    rectId.color = color
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
        }
    }
    Settings{
        category: "window"
        property alias x : rootId.x
        property alias y : rootId.y
        property alias width : rootId.width
        property alias height : rootId.height
    }
    Settings{
        category: "colors"
        property alias rectColor : rectId.color
    }
}











