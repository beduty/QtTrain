import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("BusyIndicator Demo")

    ColumnLayout {
        y: 200
        width: parent.width
        //height: parent.height
        BusyIndicator{
            id : busyIndicatorId
            Layout.alignment: Qt.AlignHCenter
        }
        ColumnLayout{
            Button{
                id : button1
                text : "Running"
                Layout.fillWidth: true
                onClicked: {
                    busyIndicatorId.running = true
                    busyIndicatorId.visible = true
                    console.log("Running")
                }
            }
            Button{
                id : button2
                text : "Not Running"
                Layout.fillWidth: true
                onClicked: {
                    busyIndicatorId.running = false
                    busyIndicatorId.visible = false
                    console.log("Stop")
                }
            }
        }
//        Item {
//            Layout.fillHeight: true
//            Layout.fillWidth: true
////            Rectangle{
////                anchors.fill : parent
////                color: "red"
////            }
//        }
    }
}
