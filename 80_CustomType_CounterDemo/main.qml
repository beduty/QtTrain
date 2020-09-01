import QtQuick 2.12
import QtQuick.Window 2.12
import com.blikoon.counter 1.0
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CustomType_CounterDemo")

    Connections{
        target: MyCounter2
        onCountChanged : {
            console.log("Change!")
            mText.text = MyCounter2.count +"tt"
        }
    }

    Connections{
        target: mCounter
        onCountChanged : {
            console.log("Change2!")
            //mText.text = mCounter.count+"ss"
        }
    }

    MyCounter{
        id: mCounter
    }
    Column{
        anchors.centerIn: parent
        spacing: 10
        Rectangle{
            width: 200
            height: 200
            radius: 20
            color: (mCounter.count >= 0) ? "green" : "red"
            Text {
                id: mText
                //text: MyCounter2.count//"0"//mCounter.count // emit countChanged가 될때 업데이터된다.
                //text: "0"//mCounter.count // emit countChanged가 될때 업데이터된다.
                text : mCounter.count
                anchors.centerIn: parent
                font.pointSize: 20
                color: "white"
            }
        }
        Button{
            text: "Start"
            width: 200
            onClicked: {
                mCounter.start()
                //MyCounter2.start()
            }
        }

        Button{
            text: "Stop"
            width: 200
            onClicked: {
                mCounter.stop()
            }
        }

        Button{
            text: "Up"
            width: 200
            onClicked: {
                mCounter.up = true;
            }
        }
        Button{
            text: "Down"
            width: 200
            onClicked: {
                mCounter.up = false;
            }
        }

    }
}
