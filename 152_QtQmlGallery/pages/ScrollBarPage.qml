import QtQuick 2.0
import QtQuick.Controls 2.12

Flickable {
    id : flickable
    contentHeight: pane.height
    ScrollBar.vertical: ScrollBar{
        policy: ScrollBar.AlwaysOn
    }
    //ScrollIndicator.vertical: ScrollIndicator { }

    Pane{
        id : pane
        width: flickable.width
        height: flickable.height * 1.2

        Column{
            spacing: 40
            width: parent.width

            Label{
                width: parent.width
                wrapMode: Label.Wrap
                horizontalAlignment: Text.AlignHCenter
                text: "ScrollBar is an interactive bar that can be used to scroll to a specific position. "
                    + "A scroll bar can be either vertical or horizontal, and can be attached to any Flickable, "
                    + "such as ListView and GridView."
            }

            Image {
                rotation: 90
                source: "/images/arrows.png"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
