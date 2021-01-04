import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
ScrollablePage {
    id : page

    readonly property int buttonWidth: Math.max(button.implicitWidth, Math.min(button.implicitWidth*2, page.availableWidth/3))


    Column{
        spacing: 40
        width: parent.width
        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Text.AlignHCenter
            text: "Dialog is a popup that is mostly used for short-term taskes"
             + "and brief communications with the user."
        }
        Button{
            text: "Message"
            anchors.horizontalCenter: parent.horizontalCenter
            width: buttonWidth
            onClicked:  {
                msgDlg.open()
            }

            Dialog{
                id : msgDlg
                anchors.centerIn: parent
                title: "Message"
                Label{
                   text :  "Lorem ipsum dolor sit amet..."
                }
            }
        }
        Button{
            id : button
            text: "Confirmation"
            anchors.horizontalCenter: parent.horizontalCenter
            width: buttonWidth
            onClicked:  {
                confirmDlg.open()
            }
            Dialog{
                id : confirmDlg
                anchors.centerIn: parent
                title: "Confirmation"
                modal: true
                standardButtons: Dialog.Yes | Dialog.No
                parent: Overlay.overlay

                Column {
                    spacing: 20
                    width: parent.width
                    Label {
                        text: "The document has been modified.\nDo you want to save your changes?"
                    }
                    CheckBox {
                        text: "Do not ask again"
                        anchors.right: parent.right
                    }
                }
            }
        }
        Button{
            text: "Content"
            width: buttonWidth
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                contentDlg.open()
            }
            Dialog{
                id : contentDlg
                anchors.centerIn: parent
                width: page.width*2/3
                //height: width * 1.3
                contentHeight: logo.height * 2
                title: "Content"
                standardButtons: Dialog.Close

                Flickable{
                    clip : true
                    anchors.fill: parent
                    contentHeight: column.height
                    ScrollIndicator.vertical: ScrollIndicator{}

                    Column{
                        id : column
                        width: parent.width
                        spacing: 20

                        Image {
                            id: logo
                            width: parent.width/2
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "/images/qt-logo.png"
                            fillMode: Image.PreserveAspectFit
                        }

                        Label {
                            id : label
                            wrapMode: Label.Wrap
                            width: parent.width
                            text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc finibus "
                                + "in est quis laoreet. Interdum et malesuada fames ac ante ipsum primis "
                                + "in faucibus. Curabitur eget justo sollicitudin enim faucibus bibendum. "
                                + "Suspendisse potenti. Vestibulum cursus consequat mauris id sollicitudin. "
                                + "Duis facilisis hendrerit consectetur. Curabitur sapien tortor, efficitur "
                                + "id auctor nec, efficitur et nisl. Ut venenatis eros in nunc placerat, "
                                + "eu aliquam enim suscipit."
                        }
                    }
                }
            }
        }
        Button{
            text: "Input"
            width: buttonWidth
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked:  {
                inputDlg.open()
            }

            Dialog{
                id : inputDlg
                anchors.centerIn: parent
                width: page*2/3
                title: "Input"
                modal : true
                focus: true
                standardButtons: Dialog.Ok | Dialog.Cancel

                Column{
                    spacing: 20
                    anchors.fill: parent

                    Label {
                        elide: Label.ElideRight
                        text: "Please enter the credentials:"
                        Layout.fillWidth: true
                    }
                    TextField{
                        focus: true
                        placeholderText : "Username"
                        width: parent.width
                    }
                    TextField{
                        placeholderText : "Password"
                        echoMode: TextField.PasswordEchoOnEdit
                        width: parent.width
                    }
                }
            }
        }
    }
}












