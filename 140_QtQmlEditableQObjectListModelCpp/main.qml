import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView{
        id : mListView
        anchors.fill: parent
        model: myModel
        // 모델의 내용이 하나라도 바뀌면, Reload된다!!.
        // 변경안해도 될 것들도 전부 갱신이 되기때문에 비싼 연산이다!
        delegate: Rectangle{
            height: 90
            radius: 10
            color : "gray"
            border.color: "cyan"
            width: parent.width
            RowLayout{
                anchors.fill: parent
                anchors.margins: 20
                TextField{
                    text: names
                    Layout.fillWidth: true
                    onEditingFinished: {
                         // index는 Model의 인덱스이다.
                         // text는 TextField의 값이다.
                        Wrapper.setNames(index, text)
                    }
                }
                SpinBox{
                    editable: true
                    value: age
                    Layout.fillWidth: true
                    onValueChanged: {
                        if(value === model.age){

                        }else{
                            Wrapper.setAge(index, value)  // value는 SpinBox의 값이다.
                        }
                    }
                }
                Rectangle{
                    width: 50
                    height: 50
                    color: favoriteColor
                    Component.onCompleted: {
                        Wrapper.callTest();
                    }
                }
            }
        }
    }
    Button{
        id : mButton
        width: parent.width
        anchors.bottom: parent.bottom
        height: 50
        text : "Add Person"
        onClicked: {
            Wrapper.addPerson();
        }
    }
}
















