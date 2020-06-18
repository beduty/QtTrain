import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Signal and Slots Demo")

    property int increment : 0
    Rectangle{
        id : rectId
        color: "red"
        width:  100
        height:  50+ increment

        // 시그널 정의
        signal greet(string message)
        onGreet : {
            //시그널 보낼때 호출된다.
            console.log(" fire greet signal !!")
        }

        // 마우스 클릭할 때 시그널 보낸다!!
        MouseArea {
            anchors.fill: parent
            onClicked: {
                // Fire the signal 방출!!
                rectId.greet("Hello threre")
            }
        }

        // 시그널 보낸 메시지는 myGreeting으로 흘러들어간다.
        Component.onCompleted: {
            greet.connect(myGreeting)
        }

        // 메시지 흘러들어오면 미리정의된 동작을 수행한다.
        function myGreeting(mMessage){
            console.log("signal grap!" + mMessage)
            increment += 25
        }

        onHeightChanged: {
            console.log("height : "  + rectId.height)
        }
    }
}
