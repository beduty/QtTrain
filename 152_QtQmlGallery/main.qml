import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12


ApplicationWindow{
    id : window
    width: 360
    height: 520
    visible: true
    title: "Qml Gallery"
    header: ToolBar{
        Material.foreground: "white"
        RowLayout{
            spacing: 20
            anchors.fill: parent
            ToolButton{
                action: navigateBackAction
                //action: drawerOpen
            }
            Label{
                id : titleLabel
                text : listView.currentItem ? listView.currentItem.text : "Gallery"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton{
                action: optionsMenuAction
                Menu{
                    id : optionsMenu
                    x : parent.width-width
                    transformOrigin: Menu.TopRight
                    Action{
                        text : "Setting"
                        onTriggered:  optionsMenuAction
                    }
                    Action{
                        text : "About"
                        onTriggered:  optionsMenuAction
                    }
                }
            }
        }
    }
    Action{
        id : optionsMenuAction
        icon.source: "/icons/gallery/20x20@4/menu.png"
        onTriggered: optionsMenu.open()
    }
    Action{
        id : drawerOpen
        icon.source: "/icons/gallery/20x20/drawer.png"
        onTriggered: drawer.open()
    }
    Shortcut{
        sequences: ["Esc", "Back"]
        enabled: stackView.depth>1
        onActivated: navigateBackAction.trigger()
    }

    Action{
        id : navigateBackAction
        icon.source: stackView.depth > 1 ? "/icons/gallery/20x20/back.png" : "/icons/gallery/20x20/drawer.png"
        onTriggered: {
            if(stackView.depth > 1){
                stackView.pop()
                listView.currentIndex = -1
            }else {
                drawer.open()
            }
        }
    }
    Drawer{
        id : drawer
        width: window.width * 2/3
        height: window.height
        interactive: stackView.depth === 1
        ListView{
            id : listView
            focus : true
            currentIndex : -1
            anchors.fill : parent
            ScrollIndicator.vertical: ScrollIndicator{}

            delegate: ItemDelegate{
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()
                }
            }
            model: ListModel{
                ListElement {title : "BusyIndicator"; source : "qrc:/pages/BusyIndicatorPage.qml"}
                ListElement {title : "Button"; source : "qrc:/pages/ButtonPage.qml"}
                ListElement {title : "CheckBox"; source : "qrc:/pages/CheckboxPage.qml"}
                ListElement {title : "ComboBox"; source : "qrc:/pages/ComboBoxPage.qml"}
                ListElement {title : "DelayButton"; source : "qrc:/pages/DelayButtonPage.qml"}
                ListElement {title : "Dial"; source : "qrc:/pages/DialPage.qml"}
                ListElement {title : "Dialog"; source : "qrc:/pages/DialogPage.qml"}
                ListElement {title : "Delegates"; source : "qrc:/pages/DelegatePage.qml"}
                ListElement {title : "Frame"; source : "qrc:/pages/FramePage.qml"}
                ListElement {title : "GroupBox"; source : "qrc:/pages/GroupboxPage.qml"}
                ListElement {title : "PageIndicator"; source : "qrc:/pages/PageIndicator.qml"}
                ListElement {title : "ProgressBar"; source : "qrc:/pages/ProgressBar.qml"}
                ListElement {title : "RangeSlider"; source : "qrc:/pages/RangeSlider.qml"}
                ListElement {title : "ScrollBar"; source : "qrc:/pages/ScrollBarPage.qml"}
                ListElement {title : "Slider"; source : "qrc:/pages/SliderPage.qml"}
                ListElement {title : "SpinBox"; source : "qrc:/pages/SpinBox.qml"}
                ListElement {title : "StackView"; source : "qrc:/pages/StackViewPage.qml"}
            }
        }
    }

    StackView{
        id : stackView
        anchors.fill: parent
        initialItem: Pane{
            id : pane
            Image{
                id: logo
                width: pane.availableWidth/2
                height: pane.availableHeight/2
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -50
                fillMode: Image.PreserveAspectFit
                source: "/images/qt-logo.png"
            }
            Label{
                text: "Qt Quick Controls 2 provides a set of controls that can be used to build complete interfaces in Qt Quick."
                anchors.margins: 20
                anchors.top : logo.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: arrow.top
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                wrapMode: Label.Wrap
            }
            Image{
                id : arrow
                source: "/images/arrow.png"
                anchors.left: parent.left
                anchors.bottom: parent.bottom
            }
        }
    }

}



















