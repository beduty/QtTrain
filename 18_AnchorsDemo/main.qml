import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Anchors Demo")
    Rectangle{
        id : containerRectId
        width: 300
        height: width
        border.color: "black"
        anchors.centerIn: parent

        Rectangle{
            id : topLeftRectId
            width:100
            height: width
            color: "magenta"

        }
        Rectangle{
            id : topCenterRectId
            width: 100
            height: width
            color: "yellowgreen"
            anchors.left: topLeftRectId.right
            anchors.top : topLeftRectId.top
            anchors.topMargin: 10
            anchors.leftMargin: 10
            // topMargin 과 leftMargin과 달리, rightMargin은 동작하지 않는다.
            // 그 이유는 anchors.right를 사용하지 않았기 떄문이다.
            // anchors.속성을 써줘야만 Margin도 사용할 수 있다.
            anchors.rightMargin: 10
        }
        Rectangle{
            id : topRightRectId
            width: 100
            height: width
            color: "dodgerblue"
            anchors.left: topCenterRectId.right
            anchors.top : topCenterRectId.top
        }
        Rectangle{
            id : centerLeftRectId
            width: 100
            height: width
            color: "red"
            anchors.top: topLeftRectId.bottom
        }
        Rectangle{
            id : centerCenterRectId
            width: 100
            height: width
            color: "green"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            // Offset을 사용하려면 Offset 앞의 속성을
            // 먼저 사용해줘야 한다.(horizontalCenter..)
            anchors.horizontalCenterOffset: 10
            anchors.verticalCenterOffset: 10
        }
        Rectangle{
            id : centerRightRectId
            width: 100
            height: width
            color: "blue"
            anchors.left: centerCenterRectId.right
            anchors.top: topRightRectId.bottom
        }
        Rectangle{
            id : bottomLeftRectId
            width: 100
            height: width
            color: "royalblue"
            anchors.top: centerLeftRectId.bottom
        }
        Rectangle{
            id : bottomCenterRectId
            width: 100
            height: width
            color: "yellow"
            anchors.left: bottomLeftRectId.right
            anchors.top: centerCenterRectId.bottom
        }
        Rectangle{
            id : bottomRightRectId
            width: 100
            height: width
            color: "pink"
            anchors.left: bottomCenterRectId.right
            anchors.top: centerRightRectId.bottom
        }
    }

    Rectangle{
        id: siblingRect
        width: 200
        height: 200
        color: "orange"
        anchors.right: containerRectId.left
    }
}
