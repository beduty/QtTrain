import QtQuick 2.12
import QtQuick.Window 2.12
import OutlineTextItem 1.0

Window {
    visible: true
    width: 800
    height: 400
    title: qsTr("Hello World")

    Rectangle{
        anchors.fill: parent
        OutlineTextItem{
            anchors.centerIn: parent
            text : "This is outliend text"
            fontFamily: "Arial"
            fontPixelSize: 64
            color: "#33ff0000"
            antialiasing: true
            border.color: "blue"
            border.width: 2
            border.style: Qt.DotLine
        }
        NumberAnimation on rotation {
            running: true
            from :0
            to : 360
            duration: 3000
        }
    }
}
