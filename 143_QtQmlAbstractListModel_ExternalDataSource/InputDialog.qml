import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
//import QtQuick.Dialogs 1.2

Item {
    id : rootId
    function openDialog(){
        inputDialog.open()
    }
    property alias personNames: addPerNamesField.text
    property alias personAge: addPerAgeField.value
    signal inputDialogAccepted

    Dialog{
        id : inputDialog
        x : (parent.width - width) /2
        y : (parent.height-height)/2
        width: parent.width/2
        parent: Overlay.overlay
        focus : true
        modal : true
        title: "Person data"
        standardButtons: Dialog.Ok | Dialog.Cancel
        ColumnLayout{
            spacing: 20
            anchors.fill: parent
            Label{
                elide: Label.ElideRight
                text: "Please enter the data : "
                Layout.fillWidth: true
            }
            TextField{
                id : addPerNamesField
                focus : true
                placeholderText: "Names"
                Layout.fillWidth: true
            }
            SpinBox{
                editable: true
                id : addPerAgeField
                value: 13
                Layout.fillWidth: true
            }
        }
        onAccepted: {
            console.log("Accepted adding person")
            rootId.inputDialogAccepted()
        }
        onRejected: {
            console.log("Rejected adding person")
        }
    }

}























