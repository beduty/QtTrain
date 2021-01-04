import QtQuick 2.12
import QtQuick.Controls 2.12

ScrollablePage {
    id : page
    Column{
        spacing: 40
        width: parent.width
        Label{
            text: "RangeSlider is used to select a range specified by two values. by sliding each handle along a track."
            width: parent.width
            wrapMode: Text.Wrap
            horizontalAlignment: Qt.AlignHCenter
        }
        RangeSlider{
            from: 1
            to : 100
            first.value: 25
            second.value: 75
            anchors.horizontalCenter: parent.horizontalCenter
        }
        RangeSlider {
            orientation: Qt.Vertical
            first.value: 0.25
            second.value: 0.75
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
