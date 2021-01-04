import QtQuick 2.12
import QtQuick.Controls 2.12

ScrollablePage {
    id : page
    Column{
        spacing: 40
        width: parent.width
        Label{
            wrapMode: Label.Wrap
            width: parent.width
            text : "SpinBox allows the user to choose an integer value by clicking the up or down indicator buttons,"
            + "by pressing up or down on the keyboard, or by entering a text value in the input field."
        }
        SpinBox{
            from:40
            to: 60
            value: 50
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}
