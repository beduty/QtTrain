import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Mouse Area Demo")
    Rectangle{
        id : canvasRect1Id
        width: parent.width
        height: 200
        color: "beige"

        Rectangle{
            id : movingRect1Id
            width: 50
            height: width
            color: "blue"
        }

        MouseArea{
            id : mouseArea1
            anchors.fill: parent
            onClicked: {
                console.log("mouse X : " + mouse.x)
                movingRect1Id.x = mouse.x
            }

            hoverEnabled: true
            onHoveredChanged: {
                if(containsMouse == true){
                    // 마우스가 MouseArea에 있으면, true
                    canvasRect1Id.color = "green"
                }else{
                    canvasRect1Id.color = "red"
                }
            }
        }
    }
    Rectangle{
        y:250
        id : canvasRect2Id
        width: parent.width
        height: 200
        color: "beige"

        Rectangle{
            id : movingRect2Id
            width: 50
            height: width
            color: "blue"
        }

        MouseArea{
            id : mouseArea2
            anchors.fill: parent
            drag.target: movingRect2Id
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: canvasRect2Id.width -movingRect2Id.width
        }
    }

}





//    Rectangle{
//        id : containerRectId
//        width: parent.width
//        height: 200
//        color: "beige"
//        Rectangle{
//            id : movingRectId
//            width: 50
//            height: width
//            color: "blue"
//        }
//        MouseArea{
//            anchors.fill: parent
//            onClicked: {
//                console.log(mouse.x)
//                movingRectId.x = mouse.x
//            }
//            onWheel: {
//                console.log("X : " + wheel.x + "Y : " + wheel.y + "angle Data : "+ wheel.angleDelta)
//            }
//            hoverEnabled: true
//            onHoveredChanged: {
//                if(containsMouse == true)
//                {
//                    containerRectId.color = "red"
//                }
//                else{
//                    containerRectId.color = "green"
//                }

//            }
//        }
//    }
//    Rectangle{
//        id : dragContainerId
//        width: parent.width
//        height: 200
//        color: "beige"
//        y : 250
//        Rectangle {
//            id : draggableRect
//            width: 50
//            height: width
//            color: "blue"
//            onXChanged: {
//                console.log("X Coordinate is : " + x )
//            }
//        }
//        MouseArea{
//            anchors.fill: parent
//            drag.target: draggableRect
//            drag.axis: Drag.XAxis
//            drag.minimumX: 0
//            drag.maximumX: dragContainerId.width-draggableRect.width
//        }
//    }



















