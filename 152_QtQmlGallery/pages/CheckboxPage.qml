import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
ScrollablePage {

    Column{
        spacing: 40
        width: parent.width

        Label{
            text : "CheckBox presents an option button that can be toggled on or off"
            + "Check boxes are typically used to select one or more options from a set of "
            wrapMode: Label.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }

        ColumnLayout{
            anchors.horizontalCenter: parent.horizontalCenter
            CheckBox{
                text : "First"
                checked: true
                Layout.fillHeight: true
            }
            CheckBox{
                text : "Second"
                checked: false
                Layout.fillHeight: true
            }
            CheckBox{
                text : "Third"
                checked: true
                enabled: false
                Layout.fillHeight: true
            }
        }
    }
}
