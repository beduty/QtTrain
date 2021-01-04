import QtQuick 2.12
import QtQuick.Controls 2.12
ScrollablePage {
    id: page
    Column{
        spacing: 40
        width: parent.width
        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Text.AlignHCenter
            text: "Slider is used to select a value by sliding a handle along a track."
        }

        Label{
            id : horizSliderVal
            text: "0.5"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Slider{
            value: 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            onMoved: {
                horizSliderVal.text = value
            }
        }


        Label{
            id : verticalSliderVal
            text: "0.5"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Slider{
            value: 0.5
            orientation: Qt.Vertical
            anchors.horizontalCenter: parent.horizontalCenter
            onMoved: {
                verticalSliderVal.text = value
            }
        }
    }

}
