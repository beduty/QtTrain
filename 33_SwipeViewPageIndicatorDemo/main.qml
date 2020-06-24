import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 1000
    title: qsTr("SwipeViewPageIndicatoreDemo")

    SwipeView{
        id : swipeViewId
        anchors.fill: parent
        currentIndex:
                 pageIndicatorId.currentIndex
        Image{
            id : imgage1
            source: "images/1.png"
        }
        Image{
            id : imgage2
            source: "images/2.png"
        }
        Image{
            id : imgage3
            source: "images/3.png"
        }

    }
    PageIndicator{
        id : pageIndicatorId
        anchors.bottom: parent.bottom
        anchors.horizontalCenter:
                       parent.horizontalCenter
        currentIndex: swipeViewId.currentIndex
        interactive: true
        count: swipeViewId.count
    }

}
