import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World222")
    Row{
        x: 100
        MButton{
            buttonColor : "green"
            buttonText : "Button 1"
            onButtonClicked: {
                console.log("Clicked on Button1 from main file")
            }
        }
        MButton{
            buttonText : "Button 2"
            onButtonClicked: {
                console.log("Clicked on Button2 from main file")
            }
        }
    }

}


















