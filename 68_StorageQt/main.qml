import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

Window{
    id : rootId
    visible : true
    width : 640
    height : 480
    title : qsTr("Qt Storage Setting Demo")

    Rectangle{
        id : rectId
        anchors.fill : parent
        color : "red"
        MouseArea {
            anchors.fill : parent
            onClicked : {
                colorDialogId.open()
            }
            ColorDialog{
                id : colorDialogId
                title : "Please choose a color"
                onAccepted : {
                    console.log("The New color is :" + color)
                    rectId.color = color
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
        }
    }
    Settings{
        category : "window"
        property alias x1 : rootId.x
        property alias y2 : rootId.y
        property alias width3 : rootId.width
        property alias height4 : rootId.height
    }
    Settings{
        category : "colors"
        property alias rectColor2 : rectId.color
    }
}







