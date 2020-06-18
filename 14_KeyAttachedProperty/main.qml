import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Key Attached Property")

    Rectangle{
        id : containedRect
        anchors.centerIn: parent
        width: 300
        height: 50
        color: "dodgerblue"
        focus: true
        Keys.onDigit1Pressed: {
            console.log("Specific Signal : pressed on Key 1")
            event.accepted = false // 테스트 하려거든 true로 바꿔보아라.
        }
        Keys.onDigit5Pressed: {
            if(event.modifiers === Qt.ControlModifier){
                console.log("Pressed Control + 5")
            }else{
                console.log("Pressed regular 5")
            }
        }
        Keys.onPressed: {
            if(event.key === Qt.Key_1){
                console.log("General Signal : pressed on Key 1")
            }
            if ((event.key === Qt.Key_6) && (event.modifiers & Qt.ControlModifier)){
                console.log("Pressed Control + 6")
            }
        }

    }



}
