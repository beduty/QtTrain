import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Grid Positioners Demo")
    Rectangle{
        id : containerRectId
        width: 300
        height: width
        border.color: "black"
        //anchors.centerIn : parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Grid{
            columns: 3
            //spacing: 10
            rowSpacing: 10
            columnSpacing: 5
            horizontalItemAlignment: Grid.AlignHCenter
            verticalItemAlignment: Grid.AlignVCenter

            Rectangle{
                id : topLeftRectId
                width: 100; height: width
                color: "magenta"
                Image {
                    anchors.centerIn: parent
                    width: 50; height: width
                    source: "image/melani.PNG"
                }
            }
            Rectangle{
                id : topCenterRectId
                width: 60; height: width
                color: "yellowgreen"
            }
            Rectangle{
                id : topRightRectId
                width: 100; height: width
                color: "dodgerblue"
            }
            Rectangle{
                id : centerLeftRectId
                width: 100; height: width
                color: "red"
            }
            Rectangle{
                id : centerCenterRectId
                width: 100; height: width
                color: "green"
            }
            Rectangle{
                id : centerRightRectId
                width: 100; height: width
                color: "blue"
            }
            Rectangle{
                id : bottomLeftRectId
                width: 100; height: width
                color: "royalblue"
            }
            Rectangle{
                id : bottomCenterRectId
                width: 100; height: width
                color: "yellow"
            }
            Rectangle{
                id : bottomRightRectId
                width: 100; height: width
                color: "pink"
            }
        }
    }
}
