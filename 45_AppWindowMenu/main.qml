import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("ApplicationWidnow Demo")

    menuBar: MenuBar{
        Menu{
            title: qsTr("&File")
            Action{
                id : newActionId
                text: qsTr("&New")
                icon.source: "images/newFileIcon.png"
                onTriggered: {
                    console.log("Clicked on New")
                }
            }
            Action{
                id : openActionId
                text: qsTr("&Open..")
                icon.source: "images/openIcon.png"
            }
            Action{
                id : saveActionId
                text: qsTr("&Save")
                icon.source: "images/saveIcon.png"
            }
            Action{
                id:saveAsActionId
                text : qsTr("Save &As...")
                icon.source: "images/saveAsIcon.png"
            }
            MenuSeparator{}
            Action{
                id : quitActionId
                text : qsTr("Quit")
                icon.source: "images/quitIcon.png"
                onTriggered: Qt.quit()
            }
        }
        Menu{
            title: qsTr("&Edit")
            Action{id : cutMenuId; icon.source: "images/cutIcon.png"; text : qsTr("Cut")}
            Action{icon.source: "images/copyIcon.png"; text : qsTr("Copy")}
            Action{icon.source: "images/pasteIcon.png"; text : qsTr("Paste")}
            MenuSeparator{}
            Action{icon.source: "images/undoIcon.png"; text : qsTr("Undo")}
            Action{icon.source: "images/redoIcon.png"; text : qsTr("Redo")}
        }
        Menu{
            title: qsTr("&Help")
            Action{
                text : qsTr("&About")
                icon.source: "images/info.png"
            }
        }
    }
    header: ToolBar{
        Row{
            anchors.fill: parent
            ToolButton{
                action : newActionId
            }
            ToolButton{
                action : saveActionId
            }
            ToolButton{
                action : saveAsActionId
            }
            ToolButton{
                action : quitActionId
            }
        }
    }
    footer: TabBar{
        id : mTabBar
        width: parent.width
        TabButton{
            text: qsTr("Page1")
            onClicked: {
                mStackId.pop()
                mStackId.push("qrc:/Page1.qml")
                console.log("Number of items : "+ mStackId.depth)
            }
        }
        TabButton{
            text: qsTr("Page2")
            onClicked: {
                mStackId.pop()
                mStackId.push("qrc:/Page2.qml")
                console.log("Number of items : "+ mStackId.depth)
            }
        }
        TabButton{
            text: qsTr("Page3")
            onClicked: {
                mStackId.pop()
                mStackId.push("qrc:/Page3.qml")
                console.log("Number of items : "+ mStackId.depth)
            }
        }
    }
    StackView{
        id : mStackId
        anchors.fill : parent
        initialItem: Page1{

        }
    }
}


























