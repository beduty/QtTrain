import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Focus scope Demo")

    Column{
        MButton{

        }
        MButton{
            focus : true
            color: "green"
        }
    }

}