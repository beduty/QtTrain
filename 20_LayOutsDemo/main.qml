import QtQuick 2.12
import QtQuick.Window 2.12

////////////////////////////////////
import QtQuick.Layouts 1.12
////////////////////////////////////

Window {
    visible: true
    width: mGridLayoutId.implicitWidth
    height: mGridLayoutId.implicitHeight
    title: qsTr("Layouts Demo")

    //RowLayout{
    //Grid{// 화면 사이즈에 상관없이 상호간격이 고정
    GridLayout{//화면 사이즈에 맞게 상호간격이 변경
        id : mGridLayoutId
        anchors.fill: parent
        columns: 3
        layoutDirection: "LeftToRight"

        Rectangle{
            id: topLeftRectId
            width: 50
           // height: width
            color: "green"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 200
            Layout.maximumWidth: 200
        }
        Rectangle{
            id: topCenterRectId
            width: 60
            height: width
            color: "red"
            Layout.alignment: Qt.AlignRight
        }
        Rectangle{
            id: topRigfhtRectId
            width: 70
            height: width
            color: "blue"
            Layout.alignment: Qt.AlignCenter
        }
        Rectangle{
            id: centerLeftRectId
            width: 90
            height: width
            Layout.fillWidth: true
            color: "yellowgreen"
            Layout.columnSpan: 2
        }
        Rectangle{
            id: centerRigfhtRectId
            width: 100
            height: width
            color: "magenta"
        }

        Rectangle{
            id: bottomLeftRectId
            width: 110
            height: width
            color: "orange"
        }
        Rectangle{
            id: bottomCenterRectId
            width: 120
            height: width
            color: "dodgerblue"
        }
        Rectangle{
            id: bottomRigfhtRectId
            width: 130
            height: width
            color: "gold"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

}
