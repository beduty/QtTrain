import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id : rootId
    visible: true
    width: 640
    height: 480
    title: qsTr("Grouped Animation")
    property int animationDuration : 500
    Rectangle{
        anchors.fill : parent
        color: "gray"
        Rectangle{
            id : circleId
            width  : 50
            height: 50
            radius: 70
            color: "yellowgreen"
        }

        //SequentialAnimation{  // 순차적으로 동작한다.
        ParallelAnimation{ // 동시에 동작한다.
            id : groupedAnimId
            NumberAnimation{
                target: circleId
                property: "x"
                to : rootId.width-circleId.width
                from : 0
                duration: animationDuration
            }
            NumberAnimation{
                easing.type: Easing.OutBounce
                easing.amplitude: 3
                target: circleId
                property: "y"
                to : rootId.height-circleId.height
                from : 0
                duration: animationDuration
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                //Reset the values : x and y
                circleId.x = 0
                circleId.y = 0
                groupedAnimId.start()
            }
        }
    }
}
