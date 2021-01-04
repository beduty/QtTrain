import QtQuick 2.0
import QtQuick.Controls 2.12

ScrollablePage {
    id : page
    Column{
        spacing: 40
        width: parent.width
        Label{
            text: "The Dial is similar to a traditional dial knob that is found on devices"
            +"such as stereos or industrial equipment. it allows the user to specify a value within a range."
            wrapMode: Label.Wrap
            horizontalAlignment: Text.AlignHCenter
        }
        Label{
            id : dialVal
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }

        Dial{
            value: 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            onMoved: {

                dialVal.text = value
            }
        }
    }
}
