import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Window{
    visible : true
    width : 640
    height : 480
    title : qsTr("FontDlg Demo")

    Column{
        spacing : 20
        anchors.centerIn : parent
        Button{
            text : "Change Font"
            anchors.horizontalCenter : parent.horizontalCenter
            onClicked:{
                fontDialogId.open()
            }
        }
        Text {
            id : textId
            text : "HelloWorld"
        }
        FontDialog{
            id : fontDialogId
            title : "Choose Font"
            font : Qt.font({
                  family : "Arial",
                  pointSize : 24,
                  weight : Font.Normal
            })
            onAccepted : {
                console.log("Choose Font : " + font)
                textId.font = fontDialogId.font
            }
            onRejected : {
                console.log("Dialog rejected")
            }
        }
    }
}


//import QtQuick 2.12
//import QtQuick.Window 2.12
//import QtQuick.Dialogs 1.2
//import QtQuick.Controls 2.12
//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("FontDlg Demo")

//    Column{
//        spacing: 20
//        anchors.centerIn: parent
//        Button{
//            text: "Change Font"
//            anchors.horizontalCenter: parent.horizontalCenter
//            onClicked: {
//                fontDialogId.open()
//            }
//        }
//        Text {
//            id : textId
//            text : "Hello World"
//        }
//        FontDialog{
//            id : fontDialogId
//            title: "Choose Font"
//            font : Qt.font({
//                family : "Arial",
//                pointSize : 24,
//                weight : Font.Normal
//            })
//            onAccepted: {
//                console.log("Chose font : " + font)
//                textId.font = fontDialogId.font
//            }
//            onRejected: {
//                console.log("Dialog rejected")
//            }
//        }
//    }
//}
