import QtQuick 2.12
Rectangle {
    id : root
    signal myclick
    MouseArea{
        anchors.fill : parent
        onClicked: root.myclick()
    }
}
