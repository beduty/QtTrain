import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML DataTypes Demo")

    property string mstring : "Hello World2"
    property int mInd : 45
    property bool isFemale : true
    property double mDouble : 77.5
    property url mUrl : "www.google.com"

    property var aNumber : 100
    property var aBool : false
    property var aString: "Hello World!"
    property var aColor : Qt.rgba(0.2, 0.3, 0.4, 0.5)
    property var aRect: Qt.rect(10,10,10,10)
    property var aPoint : Qt.point(10,10)
    property var aSize : Qt.size(10,10)
    property var aVector3d : Qt.vector3d(100,100,100)
    property var aArray : [1,2,3,"four", "five", (function(){return "six";})]
    property var anObject : {"foo" : 10, "bar" : 20}
    property var aFuntion : (function() {return "one"; })
    property var aFont  : Qt.font({family: "Consolas", pointSize: 30, bold: false})
    property date mDate: "2018-07-19"
    property var aFunction: (function() { return "Seven"; })

    Rectangle{
        width: 200
        height: 100
        anchors.centerIn: parent
        color: aColor

        Text {
            id: mTextId
            text: isFemale? qsTr("Im Female") :qsTr("Im Male")
            anchors.centerIn: parent
            font: aFont
        }
    }

    Component.onCompleted: {
        console.log("The value of mString is : " + mstring)
        console.log("The value of mInd is : " + mInd)
        if (isFemale){
            console.log("I'm Woman")
        }
        else
        {
            console.log("I'm Man")
        }
        console.log("The value of mDouble is : " + mDouble)
        console.log("The value of mUrl is : " + mUrl)

        console.log("----------------------Playing with var datatype ------------------------")
        console.log("The value of aNumber is : " + aNumber)
        console.log("The value of aBool is : " + aBool)
        console.log("The value of aString is : " + aString)
        console.log("The value of aColor is : " + aColor)
        console.log("The components of aRect are : x : "+ aRect.x
                            + " y :"+ aRect.y + " width :" + aRect.width + " height :"+ aRect.height)

        console.log("The value of aPoint is : " + aPoint)
        console.log("The value of aSize is : " + aSize)
        console.log("The value of aVector3d is : " + aVector3d)
        console.log("The value of anObject is : " + anObject)
        console.log("The value of aFuntion is : " + aFuntion)
        console.log("The value of aArray is : " + aArray)
        console.log("The length of the array is :"+aArray.length)
        for(var i = 0; i < aArray.length ; i++)
        {
            if ( i === 5)
            {
                console.log(aArray[i]())
            }else{
                console.log(aArray[i])
            }
        }

        console.log("The value of aNumber is : " + aNumber)
        console.log("The date is :"+ mDate)
        console.log("The function value is :"+aFunction())
    }
}
