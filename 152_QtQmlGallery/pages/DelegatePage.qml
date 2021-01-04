import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Pane{
    padding: 0

    // .qml로 정의하는 Item의 Inline버전이다.
    // Component로 만들어 두면, 필요할때 마다 호출하면 되기에 재사용하기 좋다.
    // 보통 ListView의 delegate로 활용한다.
    // ListView의 delegate로 Component를 사용하려면, Loader를 쓰면 된다.
    // Loader의 sourceComponent 프로퍼티에 Component id를 넣으면 된다.
    Component{
        id : switchDelegateComponent
        SwitchDelegate{
            text : labelText
        }
    }

    // Group을 만들어주어야 RadioButton이 그룹으로 묶인다.
    // 하나가 선택되면, 기존 선택된 Button이 해제된다.
    ButtonGroup {
        id: radioButtonGroup
    }
    Component{
        id : radioDelegateComponent
        RadioDelegate{
            text: labelText
            ButtonGroup.group: radioButtonGroup
        }
    }

    Component {
        id: itemDelegateComponent
        ItemDelegate {
            text: labelText
            width: parent.width
        }
    }
    Component{
        id : checkDelegateComponent
        CheckDelegate{
            text: labelText
            width: parent.width
            onDoubleClicked:view.model.remove(ourIndex)
        }
    }
    Component{
        id : swipeDelegateComponent
        SwipeDelegate{
            id : swipeDelegate
            text: labelText
            width: parent.width
            Component{
                id : removeComponent
                Rectangle{
                    color: SwipeDelegate.pressed ? "#333" : "#444"
                    width: parent.width
                    height: parent.height
                    clip: true
                    SwipeDelegate.onClicked: view.model.remove(ourIndex)
                    Label{
                        font.pixelSize: swipeDelegate.font.pixelSize
                        text: "Remove"
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
            swipe.left: removeComponent
            swipe.right: removeComponent
        }
    }

    //  Map 구조 활용하여 delegateComponentMap["ItemDelegate"]를 호출하면,
    // Component{ id: itemDelegateComponent}가 리턴된다.
    property var delegateComponentMap: {
        "ItemDelegate" : itemDelegateComponent,
        "CheckDelegate": checkDelegateComponent,
        "SwipeDelegate": swipeDelegateComponent,
        "SwitchDelegate": switchDelegateComponent,
        "RadioDelegate": radioDelegateComponent
    }


    ColumnLayout{
        id : column
        spacing: 40
        anchors.fill: parent
        anchors.topMargin: 20
        Label{
            Layout.fillWidth: true
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "Delegate controls are used as delegates in views such as ListView."
        }
        ListView{
            id : listView
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ListModel{
                ListElement{type : "ItemDelegate"; text: "ItemDele1" }
                ListElement{type : "ItemDelegate"; text: "ItemDele2" }
                ListElement{type : "ItemDelegate"; text: "ItemDele3" }
                ListElement{type : "CheckDelegate"; text: "CheckDele1" }
                ListElement{type : "CheckDelegate"; text: "CheckDele2" }
                ListElement{type : "CheckDelegate"; text: "CheckDele3" }
                ListElement { type: "SwipeDelegate"; text: "SwipeDele1" }
                ListElement { type: "SwipeDelegate"; text: "SwipeDele2" }
                ListElement { type: "SwipeDelegate"; text: "SwipeDele3" }
                ListElement { type: "SwitchDelegate"; text: "SwitchDele1" }
                ListElement { type: "SwitchDelegate"; text: "SwitchDele2" }
                ListElement { type: "SwitchDelegate"; text: "SwitchDele3" }
                ListElement { type: "RadioDelegate"; text: "RadioDele1" }
                ListElement { type: "RadioDelegate"; text: "RadioDele2" }
                ListElement { type: "RadioDelegate"; text: "RadioDele3" }
                ListElement { type: "RadioDelegate"; text: "RadioDele4" }
                ListElement { type: "RadioDelegate"; text: "RadioDele5" }
            }
            section.property: "type"
            section.delegate: Pane {
                width: listView.width
                height: sectionLabel.implicitHeight + 20

                Label {
                    id: sectionLabel
                    text: section
                    anchors.centerIn: parent
                }
            }

            // Delegate로 ListView에 넣을 아이템들의 형태를 고정적으로 사용하지 않고,
            // 다양하게 쓰려면 Delay Loading을 하는 Loader를 쓴다.
            // Component로 Wrapping한 ItemDelegate를 sourceComponent로 전달하면 끝!
            delegate: Loader {
                id: delegateLoader
                width: listView.width
                sourceComponent: delegateComponentMap[model.type]

                // 여기서 Property 선언하면 Component에서 가져다 쓸 수 있다.
                // Component내에서 labelText 쓰면 모델의 Text를 가져올 수 있다.
                // Swipe될 때, ListModel에서 데이터를 지워야 하므로, ListView도 넘겨준다.
                // Component에서는 view.model.remove(outIndex)로 모델의 내용을 지울 수 있다.
                // Model의 Index를 알아야 Swipe할 때 지울 데이터를 알 수 있으므로, index도 ourIndex로 속성 지정한다.
                property ListView view: listView
                property int ourIndex: model.index
                property string labelText: model.text

                // ListView의 모델이 지워질 때, ListView.onRemove가 호출된다.
                // Swipe될 때의 삭제 애니메이션을 지정할 수 있다.
                ListView.onRemove: SequentialAnimation {
                    PropertyAction {
                        target: delegateLoader
                        property: "ListView.delayRemove"
                        value: true
                    }
                    NumberAnimation {
                        target: item
                        property: "height"
                        to: 0
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}
