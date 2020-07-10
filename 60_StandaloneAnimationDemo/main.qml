//import QtQuick 2.12
//import QtQuick.Window 2.12

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("StandAlone Animation Demo")
//    Rectangle{
//        id : containerRectId
//        anchors.fill : parent
//        color: "beige"
//        Rectangle{
//            id : containedRectId
//            width: 100
//            height: 100
//            color: "dodgerblue"
//            x :  50 ;  y : 50
//            PropertyAnimation {
//                id : mXAnimationId
//                target : containedRectId
//                property : "x"
//                duration: 2000
//                to : 530
//            }
//            PropertyAnimation {
//                id : mRotationAnimation
//                target: containedRectId
//                property : "rotation"
//                to : 2000
//                duration: 2000
//            }
//        }
//        MouseArea{
//            anchors.fill: parent
//            onPressed : {
//                //mXAnimationId.to = mouseX
//                mXAnimationId.start() // 정의해둔 애니메이션 실행해줘야 한다.
//                mRotationAnimation.start()
//            }
//            onReleased: {
//                mXAnimationId.stop()
//                mRotationAnimation.stop()
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
    title : qsTr("StandAlone Animation Demo")
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

            PropertyAnimation{
                id : mXAnimId
                target : rect1Id
                property : "x"
                to : 530
                duration : 2000
            }
            PropertyAnimation{
                id : mYAnimId
                target : rect1Id
                property : "y"
                to : 300
                duration : 2000
            }
            PropertyAnimation{
                id : mRotateAnimId
                target : rect1Id
                property : "rotation"
                to : 600
                duration : 2000
            }
            PropertyAnimation{
                id : mScaleAnimId
                target : rect1Id
                property : "scale"
                to : 3
                duration : 2000
            }
            PropertyAnimation{
                id : mColorAnimId
                target : rect1Id
                property : "color"
                to : "orange"
                duration : 2000
            }
        }
        MouseArea{
            anchors.fill : parent
            onPressed : {
                mXAnimId.start()
                mYAnimId.start()
                mRotateAnimId.start()
                mScaleAnimId.start()
                mColorAnimId.start()
            }
            onReleased: {
                mXAnimId.stop()
                mYAnimId.stop()
                mRotateAnimId.stop()
                mScaleAnimId.stop()
                mColorAnimId.stop()
            }
        }
    }
}
