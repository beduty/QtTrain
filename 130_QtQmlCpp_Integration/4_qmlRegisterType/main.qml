import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import MyCounter 1.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyCounter{
        id : mCounter
        //qmlRegisterType<Counter>("MyCounter", 1,0, "MyCounter");로
        // 등록하였기 때문에, QML 객체로 사용가능하다.
        //qmlRegisterUncreatableType<Counting>("MyCounter", 1,0, "MyCounting","..");
        // 은 Counting클래스가 Counter 클래스의 속성(Q_PROPERTY)으로 사용하였기 때문에,
        // QML에서 알아차릴수 있도록 등록 해줘야 해서 사용헀다.
        // --> 오로지 MyCounter.MyCounting으로 속성값 혹은 열거형 값을 가져오는 용도로만 사용할 수 있다.
        //     --> MyCounting{..}으로 객체 생성은 불가능하다!
    }
    Column{
        anchors.centerIn: parent
        spacing: 10
        Rectangle{
            width: 200
            height: 200
            radius: 20
            color: (mCounter.count >= 0) ? "green" : "red"
            Text{
                id : mText
                text: mCounter.count
                anchors.centerIn: parent
                font.pointSize: 40
                color: "white"
            }
        }
        Button{
            width: 200
            text:"Start"
            onClicked: {
                mCounter.start()
            }
        }
        Button{
            width: 200
            text:"Stop"
            onClicked: {
                mCounter.stop()
            }
        }
        Button{
            width: 200
            text:"Up"
            onClicked: {
                mCounter.setCounting(MyCounting.UP)
            }
        }
        Button{
            width: 200
            text:"Down"
            onClicked: {
                mCounter.setCounting(MyCounting.DOWN)
            }
        }
    }
}














