//import QtQuick 2.11

//Item {
//    property  var backgroundColor
//    property  var startColor
//    property  var endColor
//    property  string easingText
//    property  int animDuration
//    property  var easingType
//    property  int containerwidth

//    width: smallContainerRectId1.width
//    height: smallContainerRectId1.height

//    property int finalX : smallContainerRectId1.width- containedRectId1.width
//    Rectangle{
//        id : smallContainerRectId1
//        width : containerwidth
//        height: 50
//        color: backgroundColor
//        Text{
//            text : easingText
//            anchors.centerIn: parent
//        }
//        Rectangle{
//            id : containedRectId1
//            color: startColor
//            width: 50
//            height: 50
//            border{
//                width: 5
//                color: "black"
//            }
//            radius: 10
//            MouseArea{
//                anchors.fill: parent
//                property bool toRight : false
//                onClicked: {
//                    if(toRight === false)
//                    {
//                        // MOve to Right
//                        toRight = true
//                        mNumberAnimationId.to = finalX
//                        mNumberAnimationId.start()
//                        mColorAnimationId.from = startColor
//                        mColorAnimationId.to = endColor
//                        mColorAnimationId.start()
//                    }else {
//                        // MOve to Left
//                        toRight = false
//                        mNumberAnimationId.to = 0
//                        mColorAnimationId.from = endColor
//                        mColorAnimationId.to = startColor
//                        mNumberAnimationId.start()
//                        mColorAnimationId.start()
//                    }

//                }
//            }

//            NumberAnimation {
//                id : mNumberAnimationId
//                target: containedRectId1
//                property: "x"
//                duration: animDuration
//                easing.type: easingType
//                to : finalX
//            }


//            ColorAnimation {
//                id : mColorAnimationId
//                target: containedRectId1
//                property : "color"
//                from: startColor
//                to: endColor
//                duration: animDuration
//            }
//            Component.onCompleted: {
//                console.log("The width of the contained rect is : "+ parent.width)
//            }
//        }
//    }

//}

import QtQuick 2.12
Item{
    property var backgroundColor
    property var startColor
    property var endColor
    property string easingText
    property int animDuration
    property var easingType
    property int trackWidth
    property int finalX : trackWidth - smallRectId.width
    width : trackWidth
    height : 50

    PropertyAnimation{
        id : xAnimId
        property : "x"
        target : smallRectId
        duration : animDuration
        easing.type : easingType
        to : finalX
    }
    PropertyAnimation{
        id : colorAnimId
        property : "color"
        target : smallRectId
        duration : animDuration
        to : endColor
        from : startColor
    }

    Rectangle{
        id : trackId
        width : trackWidth
        height : 50
        color : backgroundColor
        Text {
            text : easingText
            anchors.centerIn : parent
        }
        Rectangle{
            id : smallRectId
            color : startColor
            width : 50
            height : 50
            border {
                width : 5
                color : "black"
            }
            radius : 10
            MouseArea{
                anchors.fill : parent
                property bool toRight : false
                onClicked : {
                    if (toRight === false)
                    {
                        toRight = true
                        xAnimId.to = finalX
                        xAnimId.start()
                        colorAnimId.to = endColor
                        colorAnimId.from = startColor
                        colorAnimId.start()
                    }
                    else
                    {
                        toRight = false
                        xAnimId.to = 0
                        xAnimId.start()
                        colorAnimId.to = startColor
                        colorAnimId.from = endColor
                        colorAnimId.start()
                    }
                }
            }
        }
    }
}
