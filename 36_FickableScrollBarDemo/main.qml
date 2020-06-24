import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Flickable and ScrollBar Demo")

    Flickable{
        width: parent.width
        height: parent.height
        contentHeight: mColumnId.implicitHeight
        ScrollBar.vertical:  ScrollBar{}
        Column{
            id : mColumnId
            anchors.fill: parent
            Rectangle{
                color: "red"
                width: parent.width
                height: 200
                Text{
                    anchors.centerIn: parent
                    text:"Element 1"
                    font.pointSize: 30
                    color:"white"
                }
            }
            Rectangle{
                color: "beige"
                width: parent.width
                height: 200
                Text{
                    anchors.centerIn: parent
                    text:"Element 6"
                    font.pointSize: 30
                    color:"white"
                }
            }
            Rectangle{
                color: "dodgerblue"
                width: parent.width
                height: 200
                Text{
                    anchors.centerIn: parent
                    text:"Element 7"
                    font.pointSize: 30
                    color:"white"
                }
            }
        }
    }
}












