import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 400
    height: 600
    minimumWidth: 400
    minimumHeight: 600
    title: qsTr("Hello World")

    ColumnLayout{
        anchors.fill: parent
        ListView{
            id : mListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: myModel
            delegate: Rectangle{
                height: 90
                width: parent.width
                radius: 10
                color: "gray"
                border.color: "cyan"
                RowLayout{
                    anchors.fill: parent
                    anchors.margins: 20
                    TextField{
                        text : names2
                        Layout.fillWidth: true
                        onEditingFinished: {
                            console.log("Editing finished, new text is : " + text + " at index : " + index)
                            // PersonModel::roleNames() 에서 지정한 role이름으로 접근할 수 있다.
                            model.names2 = text //The roles here are defined in model class
                        }
                    }
                    SpinBox{
                        id : mSpinbox
                        editable: true
                        Layout.fillWidth: true
                        onValueChanged: {
                            model.age2 = value; // Role이름으로 지정한 이름으로 접근한다.
                        }
                        Component.onCompleted: {
                            mSpinbox.value = model.age2
                        }
                    }
                    Rectangle{
                        width: 50
                        height: 50
                        color: model.favoriteColor2
                        MouseArea{
                            anchors.fill: parent
                            ColorDialog{
                                id : colorDialog
                                title : "Please choose a color"
                                onAccepted: {
                                    console.log("You chose : " + colorDialog.color)
                                    model.favoriteColor2 = color
                                }
                                onRejected: {
                                    console.log("Canceled")
                                }
                            }
                            onClicked: {
                                colorDialog.open()
                            }
                        }
                    }
                }
            }
        }
        RowLayout{
            width: parent.width
            Button{
                Layout.fillWidth: true
                height: 50
                text : "Remove Last"
                onClicked: {
                    myModel.removeLastPerson()
                }
            }
        }
    }
}





















