import QtQuick 2.12
import QtQuick.Window 2.12
import SingleTon 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Singleton Object")
    Rectangle{
        id : rect1
        width: 200
        height: 200
        radius: 20
        color: "red"
        Text {
            id: mText1
            text: SingleTon.someProperty
            color: "white"
            anchors.centerIn: parent
            font.pointSize: 30
        }
    }
    Rectangle{
        id : rect2
        anchors.left : rect1.right
        width: 200
        height: 200
        radius: 20
        color: "blue"
        Text {
            id: mText2
            text: SingleTon.someProperty
            color: "white"
            anchors.centerIn: parent
            font.pointSize: 30
        }
    }
}
