import QtQuick 2.11

Item {
    property  var backgroundColor
    property  var startColor
    property  var endColor
    property  string easingText
    property  int animDuration
    property  var easingType
    property  int containerwidth

    width: smallContainerRectId1.width
    height: smallContainerRectId1.height

    property int finalX : smallContainerRectId1.width- containedRectId1.width
    Rectangle{
        id : smallContainerRectId1
        width : containerwidth
        height: 50
        color: backgroundColor
        Text{
            text : easingText
            anchors.centerIn: parent
        }
        Rectangle{
            id : containedRectId1
            color: startColor
            width: 50
            height: 50
            border{
                width: 5
                color: "black"
            }
            radius: 10
            MouseArea{
                anchors.fill: parent
                property bool toRight : false
                onClicked: {
                    if(toRight === false)
                    {
                        // MOve to Right
                        toRight = true
                        mNumberAnimationId.to = finalX
                        mNumberAnimationId.start()
                        mColorAnimationId.from = startColor
                        mColorAnimationId.to = endColor
                        mColorAnimationId.start()
                    }else {
                        // MOve to Left
                        toRight = false
                        mNumberAnimationId.to = 0
                        mColorAnimationId.from = endColor
                        mColorAnimationId.to = startColor
                        mNumberAnimationId.start()
                        mColorAnimationId.start()
                    }

                }
            }

            NumberAnimation {
                id : mNumberAnimationId
                target: containedRectId1
                property: "x"
                duration: animDuration
                easing.type: easingType
                to : finalX
            }


            ColorAnimation {
                id : mColorAnimationId
                target: containedRectId1
                property : "color"
                from: startColor
                to: endColor
                duration: animDuration
            }
            Component.onCompleted: {
                console.log("The width of the contained rect is : "+ parent.width)
            }
        }
    }

}