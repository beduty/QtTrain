import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 200
    height: 200
    title: qsTr("Hello World")

    Button {
        id: button
        anchors.centerIn: parent
        //(*시그널 핸들러*) clicked2 시그널 들어오면 콜백된다.
        onClicked2: console.log("Clicked!")

        // 커스텀Button 아이템의 alias 파라메터인 pressed2가 변경되면 콜백된다.
        onPressed2Changed: {
            console.log("The button is currently " +
                        (pressed2? "" : "not") + "pressed")
        }
        onMouseEnter: {
            console.log("Mouse On Button")
            myBtnText = "enter"
        }
        onMouseLeave: {
            console.log("Mouse leave Button")
            myBtnText = "leave"
        }
    }
}
