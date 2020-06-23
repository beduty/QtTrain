import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("SplitView Demo")

    SplitView{
        anchors.fill: parent
        orientation: Qt.Horizontal
        //orientation: Qt.Vertical

        Rectangle {
            width: 200
            Layout.maximumWidth: 400
            color: "lightblue"
            Text {
                text: "View 1"
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: centerItem
            Layout.minimumWidth: 50
            Layout.fillWidth: true
            color: "lightgray"
            Text {
                text: "View 2"
                anchors.centerIn: parent
            }
            Column{
                Label{
                    width: 100
                    height: 50
                    wrapMode: Label.Wrap
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text : "First Name : "
                }
                TextField{
                    id : textFieldId
                    width: 200
                    height: 50
                    placeholderText: "Type your First Name"
                    onEditingFinished: {
                        console.log("Text Edit Finished : " + text)
                    }
                }
            }

        }
        Rectangle {
            width: 200
            color: "lightgreen"
            Text {
                text: "View 3"
                anchors.centerIn: parent
            }
        }
    }



}
