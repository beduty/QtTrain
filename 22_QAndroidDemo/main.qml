import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Rectangle{
        color: "Orange"
        anchors.fill: parent
        Text {
            font.pointSize: 20
            anchors.centerIn: parent
            color: "white"
            text: qsTr("Hello World")
        }
        MouseArea{

            anchors.fill : parent
            onClicked: {
                console.log("Clicked on the rectangle")
            }
        }
    }
}
