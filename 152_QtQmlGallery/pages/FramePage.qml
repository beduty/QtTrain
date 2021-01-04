import QtQuick 2.0
import QtQuick.Controls 2.12

ScrollablePage{
    id: page
    readonly property int itemWidth: Math.min(column.implicitWidth*3, page.availableWidth*2/3)
    Column{
        spacing: 40
        width: parent.width

        Label{
            width: parent.width
            wrapMode: Label.Wrap
            text: "Frame is used to logical group of controls together, within a visual frame."
            horizontalAlignment: Text.AlignHCenter
        }

        Frame{
            anchors.horizontalCenter:  parent.horizontalCenter
            width: itemWidth
            Column{
                id : column
                ButtonGroup
                {
                    id:buttonGroup
                }
                RadioButton{
                    checked: true
                    text : "First"
                }
                RadioButton{
                    text : "Second"
                }
                RadioButton{
                    text : "Third"
                }
            }

        }
    }
}
