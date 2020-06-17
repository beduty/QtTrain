import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Signal and Slots Demo")
    property int increment : 50

    Rectangle{
        id : rectangleId
        signal greet(string message) // Declare signal
        function myGreeting(mMessage){
            console.log("myGreeting slot called. The parameter is : " + mMessage)
            increment += 25
        }

        onGreet : {
            console.log("onGreet : greet signal emited")
        }
        onWidthChanged: {
            console.log("onWidthChanged : " + rectangleId.width)        }

        width:  200 + increment
        height:  300
        color: "red"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                rectangleId.greet("Hello threre") // Fire the signal
            }
        }
        Component.onCompleted: {
            greet.connect(myGreeting)
        }
    }
}
