import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("FileDlg Demo")

    Column{
        spacing: 20
        anchors.centerIn: parent
        Button{
            text:"Choose FIle or Folder"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                fileDialogId.open()
            }
        }
        Text {
            id : textId
            text: "Use hasn't chosen yet"
            wrapMode: Text.Wrap
        }
        FileDialog{
            title: "Choose File or Folder"
            id : fileDialogId
            selectFolder: false
            selectMultiple: true
            onAccepted: {
                textId.text = fileUrls[0]
                for(var i = 0 ; i < fileUrls.length; i++)
                {
                    console.log("Value " + i + " is :" + fileUrls[i])
                }
            }
            onRejected: {

            }
        }
    }

}
