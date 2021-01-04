import QtQuick 2.12
import QtQuick.Controls 2.12

ScrollablePage {
    id : page
    Column{
        width : parent.width
        spacing: 40

        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Text.AlignHCenter
            text: "ProgressBar indicates the progress of an operation."
                + "it can be set in an indeterminate mode to indicate "
                + "that the length of the operation is unknown."
        }

        ProgressBar{
            id : progressBar
            value: 0.5
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ProgressBar{
            indeterminate: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button{
            text: "+"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                var val = progressBar.value

                if (val > 0.95)
                    progressBar.value  = 0.0
                else
                    progressBar.value  = val+ 0.1
            }
        }
    }

}
