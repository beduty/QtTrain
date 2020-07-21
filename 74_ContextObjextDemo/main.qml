import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Context Object Demo")

    Rectangle{
        id : mRect1
        width: mText1.implicitWidth + 20
        height:  mText1.implicitHeight + 20
        color: "beige"
        border.color: "yellowgreen"
        Text {
            id: mText1
            anchors.centerIn: parent
            //text: mLastname
            text: lastname
            font.pointSize: 20
        }
    }

    Rectangle{
        id : mRect2
        anchors.left: mRect1.right
        anchors.leftMargin: 5
        width: mText2.implicitWidth + 20
        height:  mText2.implicitHeight + 20
        color: "beige"
        border.color: "yellowgreen"
        Text {
            id: mText2
            anchors.centerIn: parent
            //text: mFirstname
            // engine.rootContext()->setContextObject(&propWrapper);를 사용하면 직접 함수에 접근가능하다.
            text: firstname
            font.pointSize: 20
        }
    }
}
