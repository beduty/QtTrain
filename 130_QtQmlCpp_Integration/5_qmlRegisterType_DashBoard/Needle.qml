import QtQuick 2.0

Item {
    id : root
    property int length: parent.width * 0.4
    property color color : "white"
    property color middleColor : "red"
    property int size: 2

    Rectangle{
        width: root.size
        height: length + 20
        color: root.color
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -20
        antialiasing: true
    }
    Rectangle{
        anchors.centerIn: parent
        width: 8 + root.size
        height: width
        radius: width/2
        color: root.color
        Rectangle{
            anchors.fill: parent
            anchors.margins: parent.width * 0.25
            color: root.middleColor
        }
    }
}
