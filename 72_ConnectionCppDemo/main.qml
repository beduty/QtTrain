import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Connection Cpp Demo")

    Connections{
        target: CppSignalSender
        onCallQml : {
            console.log("This is Qml : call Qml siganl cought")
            mText.text = parameter
        }
        onCppTimer : {
            mRectText.text = value
        }
    }

    Column{
        Rectangle{
            width: 200
            height: 200
            color: "dodgerblue"
            radius: 20
            Text {
                id: mRectText
                text: "0"
                color: "white"
                font.pointSize: 30
                anchors.centerIn: parent
            }
        }

        Button{
            text: "Call C++ Method"
            onClicked: {
                // 여기서 emit Signal을 보낸다.(callQml)
                CppSignalSender.cppSlot()
            }
        }
        Text {
            id: mText
            text: qsTr("text")
        }
    }
}
