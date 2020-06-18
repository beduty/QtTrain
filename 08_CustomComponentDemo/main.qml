import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World222")
    Row{
        x: 20
        spacing: 10
        MButton{
            buttonColor : "yellowgreen"
            buttonText : "Button 1"
            onButtonClickedSignal:  {
                rectId.color = "blue"
                console.log("Clicked on Button1 from main file")
            }
        }
        MButton{
            buttonText : "beige"
            onButtonClickedSignal: {
                rectId.color = "orange"
                console.log("Clicked on Button2 from main file")
            }
        }
    }
    Rectangle{
        id :rectId
        x :20
        y: 70
        width: 190
        height: 30
        color: "beige"
    }

}


















