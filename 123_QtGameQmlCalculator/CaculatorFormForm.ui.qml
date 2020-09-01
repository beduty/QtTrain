import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element
    property alias operationFactorial: operationFactorial
    property alias operationAdd: operationAdd
    property alias reset: reset
    property alias result: result
    property alias argument2: argument2
    property alias element: element
    property alias argument1: argument1
    property alias operationMultiply: operationMultiply

    TextField {
        id: argument1
        x: 68
        anchors.top: parent.top
        anchors.topMargin: 60
        placeholderText: qsTr("0")
    }

    RadioButton {
        id: operationMultiply
        x: 143
        y: 124
        text: qsTr("x")
    }

    RadioButton {
        id: operationAdd
        x: 74
        y: 124
        text: qsTr("+")
        checked: true
    }

    TextField {
        id: argument2
        x: 68
        y: 187
        placeholderText: qsTr("0")
    }

    Label {
        id: label
        x: 153
        y: 248
        text: qsTr("=")
    }

    Button {
        id: reset
        x: 118
        y: 324
        text: qsTr("Reset")
    }

    Label {
        id: result
        x: 153
        y: 288
        text: qsTr("00")
    }

    RadioButton {
        id: operationFactorial
        x: 216
        y: 124
        text: qsTr("!")
    }

    Connections {
        target: operationMultiply
        onPressed: print("multiply clicked")
    }
    states: [
        State {
            name: "single_argument"

            PropertyChanges {
                target: argument2
                opacity: 0
            }

            PropertyChanges {
                target: operationFactorial
                text: qsTr("!")
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:320}D{i:1;anchors_y:59}D{i:6;anchors_x:141;anchors_y:312}
}
##^##*/

