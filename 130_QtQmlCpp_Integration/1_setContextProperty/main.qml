import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property string mValue : "getData %1"
    property int clickCount: 0

    // QObject 상속받은 cpp클래스에서 보내는 시그널은
    // Connections 객체에서 처리한다.
    Connections{
        target: MyTimer
        onTimerTrigger: {
            // 시그널 처리한다.
            mRectText.text = value
        }
        onAckQml:{
            mText.text = parameter;
        }
    }
    Connections{
        target: Movie
        onTitleChanged: {
            console.log("title Changed!")
            titleId.text = title;
        }
        onCharacterChanged:{
            console.log("character Changed!")
            mainCharId.text = character;
        }
    }
    Connections{
        target: CppData
        onSendInt : {
            var text = textAreaId.text;
            var receive = text + "\n << int : " + param + ", type is : "+ typeof(param);
            textAreaId.text = receive;
        }
        onSendDouble : {
            var text = textAreaId.text;
            var receive = text + "\n << double : " + doubleParam + ", type is : "+ typeof(doubleParam);
            textAreaId.text = receive;
        }
        onSendBoolRealFloat : {
            var text = textAreaId.text;
            var receive = text + "\n << bool : " + boolParam + ", type is : "+ typeof(boolParam)
                        + "\n << qreal : " + realParam + ", type is : "+ typeof(realParam)
                        + "\n << float : " + floatParam + ", type is : "+ typeof(floatParam);
            textAreaId.text = receive;
        }
        onSendStringUrl : {
            var text = textAreaId.text;
            var receive = text + "\n << string : " + stringParam + ", type is : "+ typeof(stringParam)
                        + "\n << url : " + urlParam + ", type is : "+ typeof(urlParam);
            textAreaId.text = receive;
        }
        onSendColorFont : {
            var text = textAreaId.text;
            var receive = text + "\n << Color : (" + colorParam.r + "," +colorParam.g+ "," +colorParam.b+ ")" + ", type is: " + typeof(colorParam)
                        + "\n <<Font : " + fontParam + ", type is : "+ typeof(fontParam);
            textAreaId.text = receive;
            textAreaId.color = colorParam;
            colorContainer.color =colorParam;
        }
        onSendDate : {
            var text = textAreaId.text;
            var receive = text + "\n << Date : " + dateParam + ", type is : "+ typeof(dateParam)
                        + "\n <<Year is : " + dateParam.getFullYear()
                        + "\n <<Month is : " + dateParam.getMonth()
                        + "\n <<Day of week is : " + dateParam.getDay()
                        + "\n <<The Day of month is : " + dateParam.getDate();
            textAreaId.text = receive;
        }
        onSendPoint : {
            var text = textAreaId.text;
            var receive = text + "\n << Point : " + pointParam + ", type is: " + typeof(pointParam)
                        + "\n <<PointF : " + pointfParam + ", type is: " + typeof(pointfParam);
            textAreaId.text = receive;
        }
        onSendSize : {
            var text = textAreaId.text;
            var receive = text + "\n << Size : " + sizeParam + ", type is: " + typeof(sizeParam)
                        + "\n <<SizeF : " + sizefParam + ", type is: " + typeof(sizefParam);
            textAreaId.text = receive;
        }
        onSendRect : {
            var text = textAreaId.text;
            var receive = text + "\n << Rect : " + rectParam + ", type is: " + typeof(rectParam)
                        + "\n <<RectF : " + rectfParam + ", type is: " + typeof(rectfParam);
            textAreaId.text = receive;
        }
    }

    Row{
        spacing: 20
        Column{
            spacing: 10
            Rectangle{
                id : colorContainer
                width: 100
                height: 100
                color: "dodgerblue"
                radius: 20
                Text{
                    id  : mRectText
                    text : "0"
                    color: "white"
                    font.pointSize: 20
                    anchors.centerIn: parent
                }
            }
            Button{
                text : "call c++ Method"
                onClicked: {
                    // public slots: 내부에 있어야 된다!
                    MyTimer.cppSlot()
                }
            }
            Text{
                id : mText
                text : "listen.."
            }
        }
        Rectangle{
            width: 3
            height: parent.height
            color: "orange"
        }

        Column{
            spacing: 10
            Text{
                id : titleId
                width: 100
                text : "John Wick"
                font.pointSize: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text{
                id : mainCharId
                width: 100
                text: "Taeyeong"
                font.pointSize: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle{
                width: 100
                height: 20
            }

            Row{
                spacing: 5
                anchors.left: parent.left
                TextField{
                    id : titleTF
                    width: 70
                }
                Button{
                    id : titleBtn
                    width: 50
                    text :"Save"
                    onClicked: {
                        Movie.setTitle(titleTF.text)
                    }
                }
            }
            Row{
                spacing: 5
                anchors.left: parent.left
                TextField{
                    id : mainCharTF
                    width: 70
                }
                Button{
                    id : mainCharBtn
                    width: 50
                    text :"Save"
                    onClicked: {
                        Movie.setCharacter(mainCharTF.text)
                    }
                }
            }
        }
        Rectangle{
            width: 3
            height: parent.height
            color: "orange"
        }
        Column{
            ScrollView{
                width: 300
                height: 300
                TextArea{
                    id: textAreaId
                    background: Rectangle{
                        width: parent.width
                        height: parent.height
                        color: "black"
                    }
                    color: "white"
                    wrapMode: TextArea.Wrap
                    placeholderText: "Listening..."
                    font.pointSize: 8
                }
            }
            Row{
                width: 300
                height: 30
                Button{
                    id : mButton
                    text: mValue.arg(clickCount)
                    width: 200
                    onClicked: {
                        clickCount++;
                        mButton.text = mValue.arg(clickCount)
                        CppData.getData(colorContainer.color)
                    }
                }
                Button{
                    text: "clear"
                    width: 100
                    highlighted: true
                    onClicked: {
                        textAreaId.clear();
                    }
                }
            }
        }
    }
}











