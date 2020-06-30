import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Repeater Demo")
    Flickable{
        contentHeight: columnId.implicitHeight
        anchors.fill: parent

        Column{
            id : columnId
            anchors.fill: parent
            spacing: 2
            Repeater{
                //model : 20 // 0~19의 연속된 숫자가 들어간다.  Repeater는 동일한 속성의 Delegate를 연달아 생성할 떄 사용한다.
                model : ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
                delegate: Rectangle{
                    width: parent.width
                    height: 50
                    color: "dodgerblue"
                    Text{
                        anchors.centerIn: parent
                        text: modelData
                    }
                    MouseArea{
                        anchors.fill:parent
                        onClicked: {
                            console.log("Clicked on : " + modelData)
                        }
                    }
                }
            }
        }
    }
}
