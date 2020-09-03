import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
Item {
    id : rootId
    function openDialog(){
        inputDialog.open()
    }
    // alias는 QVariant 느낌이다. 모든 것을 포괄할 수 있다.
    // 외부에서 접근할 수 있도록 property 선언해준다.
    property alias personNames : addPerNamesField.text
    property alias personAge : addPerAgeField.value
    signal inputDialogAccepted // 외부에서 시그널 받아서 콜백 만들 수 있다!

    Dialog{
        id : inputDialog
        x : (parent.width - width)/2
        y : (parent.height - height)/2
        parent: Overlay.overlay
        focus: true
        modal : true
        title: "Person data"
        standardButtons: Dialog.Ok | Dialog.Cancel
        ColumnLayout{
            spacing: 20
            anchors.fill: parent
            Label{
                elide: Label.ElideRight
                text : "Please enter the data : "
                Layout.fillWidth: true
            }
            TextField{
                id : addPerNamesField
                focus: true
                placeholderText: "Names"
                Layout.fillWidth: true
            }
            SpinBox{
                editable: true
                id : addPerAgeField
                value : 13
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
