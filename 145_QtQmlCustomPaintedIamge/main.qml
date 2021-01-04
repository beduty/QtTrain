import QtQuick 2.12
import QtQuick.Window 2.12
import QtLogo 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Logo{
        id : mLogo1
        text: "Learn QT"
        bgColor: "blue"
        textColor: "red"

        MouseArea{
            anchors.fill: parent
            drag.target: mLogo1
            onClicked: {
                mLogo1.text = "sds"
                console.log(mLogo1.text)
                mLogo1.setText("sdaes")
                console.log(mLogo1.text)
                //mLogo1.setBgColor("green");
            }
        }
    }
    Logo{
        id : mLogo2
        anchors.top : mLogo1.bottom
        anchors.topMargin: 20
        text: "Go Fluid"
        bgColor: "beige"
        textColor: "black"
        topic: Logo.QTQUICK
    }
}
