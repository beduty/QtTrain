import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id : rootId
    visible: true
    width: 360
    height: 520
    title: qsTr("Drawer Demo")
    header : ToolBar{
        height: 50
        background: Rectangle{
            color: "mintcream"
        }
        RowLayout{
            spacing: 20
            anchors.fill: parent
            ToolButton{
                background: Rectangle{
                    color: "mintcream"
                }
                icon.source: "images/drawer.png"
                onClicked: {
                    // Open Drawer
                    drawerId.open()
                    console.log("ToolButton Clicked")
                }
            }
            Label{
                id : titleLabel
                text : "Drawer Demo"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }
    Rectangle{
        id : contentRectId
        anchors.fill: parent
        color: "lightsteelblue"
    }
    Drawer{
        id : drawerId
        width: Math.min(rootId.width, rootId.height) * (2/3)
        height: rootId.height
        interactive: true
        ColumnLayout{
            spacing: 0
            width: parent.width
            Button{
                width: parent.width
                height: 50
                text: "Item1"
                font.pointSize: 20
                Layout.fillWidth: true
                background: Rectangle{color: "beige"}
                onClicked: {
                    console.log("Clicked on Item1")
                    contentRectId.color = "red"
                    drawerId.close()
                }
            }
            Button{
                width: parent.width
                height: 50
                text: "Item2"
                font.pointSize: 20
                Layout.fillWidth: true
                background: Rectangle{color: "yellowgreen"}
                onClicked: {
                    console.log("Clicked on Item2")
                    contentRectId.color = "green"
                    drawerId.close()
                }
            }
            Button{
                width: parent.width
                height: 50
                text: "Item3"
                font.pointSize: 20
                Layout.fillWidth: true
                background: Rectangle{color: "dodgerblue"}
                onClicked: {
                    console.log("Clicked on Item3")
                    contentRectId.color = "blue"
                    drawerId.close()
                }
            }
        }
    }
}


















