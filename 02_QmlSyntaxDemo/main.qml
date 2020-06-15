import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id : rootId
    visible: true
    width: 640
    height: 480
    title: qsTr("Qml Syntax Demo")
    property string textToShow : "123456"

    Row{
        id : row1
        anchors.centerIn: parent
        spacing: 20
        Rectangle{
            id  : redRectId
            width: 150; height :150
            color: "red"
            radius: 20
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Click on the red rectangle")
                    textToShow = "red"

                }
            }
        }
        Rectangle{
            id  : greenRectId
            width: 150; height :150
            color: "green"
            radius: 20
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Click on the green rectangle")
                    textToShow = "green"

                }
            }
        }
        Rectangle{
            id  : blueRectId
            width: 150; height :150
            color: "blue"
            radius: 20
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Click on the blue rectangle")
                    textId.text = "blues"
                }
            }
        }
        Rectangle{
            id  : textRectId
            width: 150; height :150
            color: "dodgerblue"
            radius: 100
            Text{
                id:textId
                anchors.centerIn: parent
                text: textToShow
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Click on the text rectangle")
                    textId.text = "loop"
                }
            }
        }
    }
}
