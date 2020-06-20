import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("FlowDemo")

    Item {
          width: 310; height: 170

          Column {
              anchors.horizontalCenter: parent.horizontalCenter
              anchors.verticalCenter: parent.verticalCenter

              spacing: 5

              Rectangle { color: "lightblue"; radius: 10.0
                          width: 300; height: 50
                          Text { anchors.centerIn: parent
                                 font.pointSize: 24; text: "Books" } }
              Rectangle { color: "gold"; radius: 10.0
                          width: 300; height: 50
                          Text { anchors.centerIn: parent
                                 font.pointSize: 24; text: "Music" } }
              Rectangle { color: "lightgreen"; radius: 10.0
                          width: 300; height: 50
                          Text { anchors.centerIn: parent
                                 font.pointSize: 24; text: "Movies" } }
          }
      }

    // 화면에 맞게 Rectangle의 위치를 조정한다.
    // 줄에 가득하면 아래로 내린다.
    Flow{
        y:200
        id:containerFlowId
        width: parent.width
        height: parent.height
        //flow: Flow.TopToBottom
        //layoutDirection: Qt.RightToLeft
        spacing: 20
        Rectangle{
            id : topLeftRectId
            width: 70
            height: 70
            color: "green"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "1"
            }
        }
        Rectangle{
            id : topCenterRectId
            width: 100
            height: 100
            color: "beige"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "2"
            }
        }
        Rectangle{
            id : topRightRectId
            width: 100
            height: 100
            color: "dodgerblue"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "3"
            }
        }
        Rectangle{
            id : leftCenterRectId
            width: 100
            height: 100
            color: "magenta"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "4"
            }
        }
        Rectangle{
            id : centerRectId
            width: 100
            height: 100
            color: "red"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "5"
            }
        }
        Rectangle{
            id : rightcenterId
            width: 100
            height: 100
            color: "yellow"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "6"
            }
        }
        Rectangle{
            id : bottomLectRectId
            width: 100
            height: 100
            color: "royalblue"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "7"
            }
        }
        Rectangle{
            id : bottomCenterRect
            width: 100
            height: 100
            color: "greenyellow"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "8"
            }
        }
        Rectangle{
            id : bottomRightRectId
            width: 100
            height: 100
            color: "blue"
            Text{
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 30
                text: "9"
            }
        }
    }
}
