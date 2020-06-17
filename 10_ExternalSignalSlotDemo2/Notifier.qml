import QtQuick 2.12

Item {
    property int count : 0
    width: notifierRectId.width
    height: notifierRectId.height
    property alias rectColor : notifierRectId.color
    signal notify(string count) // Declare signal
    property Receiver target : null
    onTargetChanged: {
        notify.connect(target.receiveInfo)
    }

    Rectangle{
        id : notifierRectId
        width: 200
        height: 200
        color : "red"

        Text{
            id : displayTextId
            anchors.centerIn: parent
            font.pointSize: 20
            text : count
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                count ++
                notify(count)
            }
        }
    }
}
