import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Dial Demo")

    Column{
        width: parent.width
        spacing: 40
        Label {
            width: parent.width
            wrapMode: Label.Wrap

            horizontalAlignment: Qt.AlignHCenter
            text: "A Know Used to let the user choose a value from a range"
            font.pointSize: 15
        }
        Dial{
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            from: 1
            to : 100
            value: 50
            //wrap : true // 100까지가고나서 1로 휙 움직일 수 있다.
            onValueChanged: {
                //console.log("Current value : " + value)
                console.log("Current value : " + Math.ceil(value))
            }
        }

    }
}
