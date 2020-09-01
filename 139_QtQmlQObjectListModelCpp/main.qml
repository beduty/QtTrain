import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QObject List Model Demo")

    ListView{
        id : mListView
        anchors.fill: parent
        model: personModel
        delegate: Rectangle{
            height: 90
            radius: 10
            width: parent.width
            color: "gray"
            border.color: "cyan"
            RowLayout{
                anchors.fill: parent
                anchors.margins: 20
                TextField{
                    // model의 데이터가 QObject이므로 여기의 속성값에 바로 접근할 수 있다.
                    // modelData.names로 값을 받아올 수도 있지만,
                    // Q_PROPERTY의 getter로 바로 값을 가져올 수도 있다!
                    text : names //modelData.names
                    Layout.fillWidth: true
                }
                SpinBox{
                    editable:true
                    value: modelData.age
                    Layout.fillWidth: true
                }
                Rectangle{
                    width: 50
                    height: 50
                    color: modelData.favoriteColor
                }
            }
        }
    }

    // QList<QObject*> personList 대신에 ListModel로도 동일한 효과를 줄 수 있다.
    // 하지만 값을 바꾸고 업데이트하고 하는 방식이 C++로 더 풍부하게 할 수 있어서 CPP추천
    // Editable Object List 는 다음 프로젝트에서~~
    ListModel{
        id : mModelId
        ListElement{
            names : "Daniel Sten"; favoriteColor : "blue"; age : 10
        }
        ListElement {
            names : "Stevie Wongers"; favoriteColor : "cyan"; age : 23
        }
        ListElement {
            names : "Nicholai Ven"; favoriteColor : "red"; age : 33
        }
        ListElement {
            names : "William Glen"; favoriteColor : "yellowgreen"; age : 45
        }
    }

}
