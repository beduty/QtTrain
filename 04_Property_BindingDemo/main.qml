import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")    

    Rectangle{
        id : redRectId
        width: 50
        height: width*1.5
        color: "red"
    }

    Rectangle{
        id : blueRectId
        color: "blue"
        width: 100
        height: 100
        anchors.bottom: parent.bottom

        MouseArea{
            anchors.fill: parent
            onClicked: {
                redRectId.width += 10
            }
        }
    }

    Rectangle{
        id: greenRectId
        color: "green"
        width: 100
        height: 100
        anchors.bottom: parent.bottom
        anchors.left: blueRectId.right
        MouseArea{
            anchors.fill: parent
            onClicked: {
                //redRectId.height -= 10 이렇게 하니까 파란색 버튼을 눌렀을 때 Height가 변경되지 않았다.
                redRectId.height = Qt.binding(function(){
                    return redRectId.width *2.0
                })
            }
        }
    }
}










