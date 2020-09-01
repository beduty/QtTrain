import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("StringList Model Demo")

    ListView{
        id : mListView
        anchors.fill: parent
        model: continentModel // QStringList의 QString을 하나하나 받아서 delegate를 만든다.
        delegate: Rectangle{
            height: 50
            radius: 10
            width: parent.width
            color: "dodgerblue"
            border.color: "cyan"
            Text {
                text: modelData // model데이터 하나.
                font.pointSize: 20
                anchors.centerIn: parent
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
