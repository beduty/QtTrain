
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Section Demo(Decoration)")

    ListView{
        id : mListViewId
        anchors.fill : parent
        model : mListModel
        delegate: delegateId
        section {
            property: "company"
            criteria: ViewSection.FullString
            delegate: Rectangle{
                id : sectionRectId
                width: parent.width
                height: 50
                color: "red"
                border.color: "yellowgreen"
                radius: 14
                Text{
                    id : sectiontextId
                    text : section
                    anchors.centerIn: parent
                    font.pointSize: 20
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("Clicked on : " + section)
                    }
                }
            }
        }
    }
    ListModel{
        id : mListModel
        ListElement{ names : "User_1"; company : "Google" }
        ListElement{ names : "User_2"; company : "Google" }
        ListElement{ names : "User_3"; company : "Google" }
        ListElement{ names : "User_4"; company : "Google" }
        ListElement{ names : "User_5"; company : "TENCENT" }
        ListElement{ names : "User_6"; company : "TENCENT" }
        ListElement{ names : "User_7"; company : "APPLE" }
        ListElement{ names : "User_8"; company : "APPLE" }
        ListElement{ names : "User_9"; company : "BAIDU" }
        ListElement{ names : "User_10"; company : "BAIDU" }
    }

    Component{
        id : delegateId
        Rectangle{
            id : rectangleId
            width: parent.width
            height: 50
            color: "beige"
            border.color: "yellowgreen"
            radius: 14
            Text{
                id : textId
                anchors.centerIn: parent
                text : names
                font.pointSize: 20
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked on : " + names)
                }
            }
        }
    }

}
