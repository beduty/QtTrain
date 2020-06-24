import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("GropBoxDemo")

    Column{
        spacing: 10
        anchors.fill: parent

        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "A GroupBox wrapping around RadioButtons."
        }
        GroupBox{
            title: "Choose bonus"
            anchors.horizontalCenter:
                                parent.horizontalCenter
            Column{
                RadioButton{
                    text:"Coke"
                    onCheckedChanged: {
                        if(checked === true){
                            console.log("Coke Checked")
                        }else{
                            console.log("Coke UnChecked")
                        }
                    }
                }
                RadioButton{
                    text:"Tea"
                    onCheckedChanged: {
                        if(checked === true){
                            console.log("Tea Checked")
                        }else{
                            console.log("Tea UnChecked")
                        }
                    }
                }
                RadioButton{
                    text:"Ice"
                    onCheckedChanged: {
                        if(checked === true){
                            console.log("Ice Checked")
                        }else{
                            console.log("Ice UnChecked")
                        }
                    }
                }
            }
        }


        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "A GroupBox wrapping around CheckBoxes."
        }
        GroupBox{
            title: "Choose Qt supported Desktop Platform"
            anchors.horizontalCenter: parent.horizontalCenter
            Column{
                CheckBox{
                    text:"Windows"
                    onCheckedChanged: {
                        if(checked === true){
                            console.log("Windows Checked")
                        }else{
                            console.log("Windows is Not Checked")
                        }
                    }
                }
                CheckBox{
                    text:"Mac"
                    onCheckedChanged: {
                        if(checked === true){
                            console.log("Mac Button Checked")
                        }else{
                            console.log("Mac Button is Not Checked")
                        }
                    }
                }
                CheckBox{
                    text:"Linux"
                    onCheckedChanged: {
                        if(checked === true){
                            console.log("Linux Button Checked")
                        }else{
                            console.log("Linux Button is Not Checked")
                        }
                    }
                }
            }
        }
    }
}
