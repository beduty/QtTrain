import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Inline-Model-Demo")

    ListView{
        id : mListView
        anchors.fill: parent
        model : ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"]
        delegate: Component{
            id :delegateId
            Rectangle{
                id : rectangleId
                width: parent.width
                height: 50
                color: "beige"
                border.color: "yellowgreen"
                radius: 10
                Text {
                    id : textId
                    anchors.centerIn: parent
                    font.pointSize: 20
                    text: modelData // default로 정의된 model을 이렇게 데이터 지정한다.
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //modelData = "Z"
                        console.log("Clicked on : " + modelData)
                    }
                }
            }
        }
    }
}







//
