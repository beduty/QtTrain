import QtQuick 2.9
import QtQuick.Window 2.2

Rectangle {
    id: button
    // 버튼프로그래밍 인터페이스를 확장할 수 있다.
    // property 로 선언된 변수들은 가져다 쓰는 쪽에서 onTextColorChanged 등으로
    // 시그널 핸들러를 쓸 수 있다.
    property color textColor: "black"
    property color textPressedColor: "white"
    property color topColor : "#eeeeee"
    property color bottomColor : "#777777"

    // property alias로 선언하여, 외부에서 접근할 수 있다.
    // Button 내부에서 onPressed2Changed 를 통해서 해당 alias 가
    // 변경될 때마다 이벤트 받아서 콜백함수 만들 수 있다.
    property alias pressed2 : buttonMouseArea.pressed
    // MouseArea::pressed는 마우스 클릭 상태를 저장한다.

    property var myBtnText : "buttonText"

    // 시그널 보낼 수 있다. 외부에서 Button 사용할 때,
    // onClicked: 를 통해서 콜백 함수 만들 수 있다.
    signal clicked2()
    signal mouseEnter()
    signal mouseLeave()

    clip: true
    radius: 5
    border {width: 1; color: "black"}
    implicitWidth: Math.max(buttonContent.implicitWidth + 8, 80)
    implicitHeight: buttonContent.implicitHeight + 8
    gradient: Gradient{
        GradientStop{position: 0; color : button.topColor}
        GradientStop{position: 1; color : button.bottomColor}
    }

    Row{
        id: buttonContent
        anchors.centerIn: parent
        spacing: 4

        // 클릭되면 Padding 1을 준다.
        anchors.verticalCenterOffset: buttonMouseArea.pressed ? 1: 0
        anchors.horizontalCenterOffset: buttonMouseArea.pressed? 1: 0

        Image {
            id: buttonIcon
            source: "qrc:/edit-undo.png"
        }
        Text {
            id: buttonText
            text: qsTr(myBtnText)
            color: buttonMouseArea.pressed? button.textPressedColor : button.textColor
        }
    }

    MouseArea {
        id: buttonMouseArea
        hoverEnabled: true
        anchors.fill: parent
        onContainsMouseChanged:{
            if(containsMouse)
                button.mouseEnter()
            else
                button.mouseLeave()
        }

        onClicked: button.clicked2()  // onClicked될 떄 시그널 clicked2를 보낸다!
        acceptedButtons: Qt.LeftButton | Qt.MiddleButton | Qt.RightButton
//        onClicked: {
//            console.log(mouse.button);
//            switch(mouse.button) {
//              case Qt.LeftButton:   console.log("Left button clicked");
//                 break;      case Qt.MiddleButton: console.log("Middle button clicked");
//                 break;      case Qt.RightButton:  console.log("Right button clicked");
//                 break;
//            }
//        }
    }
}
