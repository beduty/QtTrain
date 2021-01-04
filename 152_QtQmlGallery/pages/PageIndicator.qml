import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
ScrollablePage {
    id : page

    ColumnLayout{
        spacing: 40
        width: parent.width
        Label{
            Layout.fillWidth: true
            wrapMode: Label.Wrap
            text: "PageIndicator is used to indicate the currently active page in a container of pages."
            horizontalAlignment: Text.AlignHCenter
        }


        SwipeView {
            id: view
            currentIndex: 1
            Layout.fillWidth: true
            height: 300
            Rectangle {
                Layout.fillWidth: true
                height: parent.height
                color: "orange"
            }

            Rectangle {
                Layout.fillWidth: true
                height: parent.height
                color: "dodgerblue"
            }

            Rectangle {
                Layout.fillWidth: true
                height: parent.height
                color: "olive"
            }
        }

        PageIndicator {
            id: indicator
            count: view.count
            currentIndex: view.currentIndex
            anchors.bottom: view.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
