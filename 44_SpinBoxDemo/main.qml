import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("SpinBox Demo")

    Column{
        spacing: 20
        width : parent.width
        SpinBox{
            id : spinBoxId
            from: 1
            to : 100
            value: 20
            stepSize: 5
            editable: true
            anchors.horizontalCenter: parent.horizontalCenter
            onValueChanged: {
                console.log("Currnet value changed to : " + value)
            }
        }
        Button{
            anchors.horizontalCenter: parent.horizontalCenter
            text : "Capture value"
            onClicked: {
                console.log("The Current value in the spinbox is " + spinBoxId.value)
            }
        }
    }
}
