import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Global Object Demo")

    property var fonts : Qt.fontFamilies()

    Rectangle{
        width: 300
        height: 100
        color: "red"
        anchors.centerIn: parent
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("Quitting the App")
                Qt.quit()

                for(var i =0; i < fonts.length; i++)
                {
                    console.log("[" + i + "] : " + fonts[i])
                }

                var mName = "Daniel Gakwaya"
                var mNameHash = Qt.md5(mName)
                console.log("The hash of the name is : " + mNameHash )
                Qt.openUrlExternally("http://www.google.com")
                Qt.openUrlExternally("file:///C:/Users/jungt/Desktop/AIK-SKC_TestIMG/AlignR.bmp")

                console.log("The current platform is " + Qt.platform.os)
            }
        }
    }
}
