import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Transform Demo")

    Rectangle{
        id : containerRectId
        anchors.fill : parent
        color: "beige"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                rect1Id.x = 50
                rect2Id.rotation = 0
                rect3Id.scale = 1
            }
        }
    }

    ClickableRect{
        id : rect1Id
        width: 100
        height: 100
        x : 50
        y : 100
        color: "red"
        onClicked: {
            // TRanslation on X
            x += 20
        }
    }

    ClickableRect{
        id : rect2Id
        width: 100
        height: 100
        x : 250
        y : 100
        transformOrigin: Item.BottomRight
        color: "green"
        onClicked: {
            // rotation
            rotation += 15
        }
    }

    ClickableRect{
        id : rect3Id
        width: 100
        height: 100
        x : 450
        y : 100
        color: "blue"
        transformOrigin: Item.TopLeft
        onClicked: {
            // scaling
            scale += 0.05
        }
    }















}
