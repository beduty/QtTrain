import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 1000
    title: qsTr("Page and TabBar Demo")

    Page{
        id : pageId
        anchors.fill   : parent
        header: Rectangle{
            width: parent.width
            height: 50
            color: "red"
            Label{
                anchors.centerIn: parent
                text : "Page and TabBar Demo"
                font.pixelSize: 22
            }
        }
        SwipeView{
            id : swipeViewId
            anchors.fill   : parent
            currentIndex: tabBarId.currentIndex
            Image {
                source: "images/1.png"
            }
            Image {
                source: "images/2.png"
            }
            Image {
                source: "images/3.png"
            }
        }
        footer: TabBar{
            id : tabBarId
            currentIndex: swipeViewId.currentIndex
            TabButton{
                text : "First"
            }
            TabButton{
                text : "Second"
            }
            TabButton{
                text : "Third"
            }
        }
    }
}
