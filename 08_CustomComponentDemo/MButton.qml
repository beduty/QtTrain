import QtQuick 2.12

Item {
    id : rootId
    property alias buttonText : buttonTextId.text
    property alias buttonColor : containerRectId.color
    width:  containerRectId.width
    height: containerRectId.height
    signal buttonClicked

    Rectangle{
        id : containerRectId
        width   : buttonTextId.implicitWidth + 50
        height: buttonTextId.implicitHeight + 50
        color: "red"
        border {
            color : "blue"
            width: 3
        }
        Text{
            id : buttonTextId
            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                rootId.buttonClicked()
                //console.log("Clicked On : " + buttonTextId.text)
            }
        }
    }
}

