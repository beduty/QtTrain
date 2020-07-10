//import QtQuick 2.12
//import QtQuick.Window 2.12

//Window {
//    id : rootId
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Animation Intro Demo")
//    property  bool running : false
//    Rectangle{
//        id : containerRectId
//        anchors.fill: parent
//        color : "beige"
//        Rectangle{
//            id : rect1Id
//            width:100
//            height: 100
//            x : 50
//            y : 50
//            color: "dodgerblue"
//            PropertyAnimation on x{
//                to : 530
//                duration: 2000
//                running: rootId.running
//            }
//            NumberAnimation on y{
//                to : 300
//                duration : 2000
//                running : rootId.running
//            }
//            RotationAnimation on rotation{
//                to : 600
//                duration: 2000
//                running: rootId.running
//            }
//            PropertyAnimation on scale{
//                to : 3
//                duration : 2000
//                running : rootId.running
//            }
//        }
//        MouseArea{
//            anchors.fill: parent
//            onPressed: {
//                rootId.running = true
//            }
//            onReleased: {
//                rootId.running = false
//            }
//        }
//    }
//}



import QtQuick 2.12
import QtQuick.Window 2.12
Window{
    id : rootId
    visible : true
    width : 640
    height : 480
    title : qsTr("Animation Intro Demo")
    property bool isRunning : false
    Rectangle {
        id : containerRectId
        anchors.fill : parent
        color : "beige"
        Rectangle{
            id : rect1Id
            width : 100
            height : 100
            x: 50
            y : 50
            color : "dodgerblue"
            PropertyAnimation on x {
                to : 530
                duration : 2000
                running : isRunning
            }
            PropertyAnimation on y {
                to : 300
                duration : 2000
                running : isRunning
            }
            PropertyAnimation on rotation {
                to : 600
                duration : 2000
                running : isRunning
            }
            PropertyAnimation on scale {
                to : 3
                duration : 2000
                running : isRunning
            }
            PropertyAnimation on color {
                to : "orange"
                duration : 2000
                running : isRunning
            }
        }
        MouseArea{
            anchors.fill : parent
            onPressed : {
                rootId.isRunning = true
            }
            onReleased : {
                rootId.isRunning = false
                rect1Id.scale = 1
                rect1Id.x = 50
                rect1Id.y = 50
                rect1Id.rotation = 0
                rect1Id.color = "dodgerblue"
            }
        }
    }
}
