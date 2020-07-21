import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Basic Data Types")

    Connections{
        target: CppClass
        onSendInt : {
            console.log("Received int : " + param + ", type is : "+ typeof(param))
        }
        onSendDouble : {
            console.log("Received double : " + doubleParam + ", type is : "+ typeof(doubleParam))
        }
        onSendBoolRealFloat : {
            console.log("Received bool : " + boolParam + ", type is : "+ typeof(boolParam))
            console.log("Received qreal : " + realParam + ", type is : "+ typeof(realParam))
            console.log("Received float : " + floatParam + ", type is : "+ typeof(floatParam))
        }
        onSendStringUrl : {
            console.log("Received string : " + stringParam + ", type is : "+ typeof(stringParam))
            console.log("Received url : " + urlParam + ", type is : "+ typeof(urlParam))
        }
        onSendColorFont : {
            console.log("Received Color : (" + colorParam.r + "," +colorParam.g+ "," +colorParam.b+ ")" + ", type is: " + typeof(colorParam))
            console.log("Received Font : " + fontParam + ", type is : "+ typeof(fontParam))
            mRect.color = colorParam
            mButton.font = fontParam
        }
        onSendDate : {
            console.log("Received Date : " + dateParam + ", type is : "+ typeof(dateParam))
            console.log("Year is : " + dateParam.getFullYear())
            console.log("Month is : " + dateParam.getMonth())
            console.log("Day of week is : " + dateParam.getDay())
            console.log("The Day of month is : " + dateParam.getDate())
        }
        onSendPoint : {
            console.log("Received Point : " + pointParam + ", type is: " + typeof(pointParam))
            console.log("Received PointF : " + pointfParam + ", type is: " + typeof(pointfParam))
        }
        onSendSize : {
            console.log("Received Size : " + sizeParam + ", type is: " + typeof(sizeParam))
            console.log("Received SizeF : " + sizeFParam + ", type is: " + typeof(sizeFParam))
        }
        onSendRect : {
            console.log("Received Rect : " + rectParam + ", type is: " + typeof(rectParam))
            console.log("Received RectF : " + rectFParam + ", type is: " + typeof(rectFParam))
        }
    }
    Rectangle{
        id : mRect
        width: 200
        height: 200
        color: "black"
        radius: 20
    }
    Button{
        id : mButton
        anchors.top: mRect.bottom
        text : "Click Me"
        onClicked: {
            //CppClass.cppSlot();
            CppClass.receivePoint(Qt.point(100,300));
            CppClass.receiveRect(Qt.rect(100,300.2,86.1,78));
        }
    }
}
