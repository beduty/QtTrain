import QtQuick 2.12
import QtQuick.Window 2.12
import "testItem.js" as Utilities1

Window {
    visible: true
    width: 650
    height: 480
    title: qsTr("JS Import Demo")

    function addlog(msg)   {
        console.log("Msg : " + msg)
    }

    Rectangle{
        width: 300
        height: 100
        color: "yellowgreen"

        Text{
            text: "Click Me"
            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                addlog("Hi Js!!")
                Utilities1.greeting()
                console.log("Our ages combined yeild : "
                            + Utilities1.combineAges(33,17))
                console.log("The difference of 50 and 33 ios : "
                            + Utilities1.substract(50,33))
            }
        }
    }
}



