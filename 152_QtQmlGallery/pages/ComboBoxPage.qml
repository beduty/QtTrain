import QtQuick 2.0
import QtQuick.Controls 2.12

ScrollablePage {
    id : page

    Column{
        spacing: 40
        width: parent.width
        Label{
            text: "ComboBox is a combined button and popup list"
            +"It presents a list of options to user that occupies minimal screen space."
            wrapMode: Label.Wrap
            horizontalAlignment: Text.AlignHCenter
        }

        ComboBox {
            model: ["First", "Second", "Third"]
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}
