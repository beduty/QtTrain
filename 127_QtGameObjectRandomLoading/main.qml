import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    /// 어떤 요소들을 만들어야 하는지 모르는 경우가 있다. (외부에서 받는 경우 등등)
    // 이럴때 객체를 어떻게 만들어야 할까? --> 유연하게 객체를 추가하는 방법이 있을까?

    // 오브젝트 동적으로 추가하기!
    //   - 발사하는 총알들 표현.
    //   - 화면에 새로 나타나는 캐릭터들
    // --> 어떻게 나타낼거니?  Component!!!

    // [Component]
    //   - QML에서 콘텐츠 선언하여 엔진에 새로 추가하는 방법
    //   - 생성 방법 : Qt.createComponent("Circle.qml");
    //          --> 로컬경로 & 원격Url 모두 허용한다. 다운로드하여 Component만든다.
    //   [생성 순서]
    //   - 1. var component = Qt.createComponent로 컴포넌트로 만든다.
    //   - 2. component.createObject( A , ...)로 컴포넌트로부터 Object를 생성한다.
    //   - 2-1.  --> A는 생성한 오브젝트를 어디의 자식으로 넣을지 지정
    //   - 2-2.  --> ...은 색상, 위치, 크기등을 지정한다.

    Button{
        id: btn
        width: 100
        height: 50
        text: "text"
        onClicked: {
            var circleComponent = Qt.createComponent("Circle.qml");
            addCircle(circleComponent)
        }
    }
    ColumnLayout{
        id: layout
        anchors.fill : parent
        Layout.alignment: Qt.AlignCenter
    }
    function addCircle(circleComponent){
        ["red", "yellow", "green"].forEach(function(color){
            var circle =  circleComponent.createObject(layout);
            circle.color = color;
            circle.Layout.alignment = Qt.AlignCenter;
        });
    }
    function addRect(rectComponent, onObject, init_x){
        ["red", "yellow", "green"].forEach(function(color){
            var rect =  rectComponent.createObject(onObject);
            rect.color = color;
            rect.x = (color === "red")? init_x : ((color === "yellow")? init_x+rect.width*1.5 : init_x+rect.width*3.0)
            rect.y = 3
        });
    }

    // 동적으로 생성하고자 하는 것들을 만들수 있다.
    // createComponent 쓰려면 Component객체를 써줘야 한다.
    Component{
        id : rectComponent
        Rectangle{
            width: 10
            height: 10
        }
    }

    // 윈도우가 만들어지면 호출된다.
    Component.onCompleted: {
        // 여기서 동적으로 개체를 만든다.
        var circleComponent = Qt.createComponent("Circle.qml");
        var circle1 = circleComponent.createObject(layout,{color:"dodgerblue"})
        var circle2 = circleComponent.createObject(layout,{color:"red", alignment : Qt.AlignCenter})
        var circle3 = circleComponent.createObject(layout,{color:"blue", alignment : Qt.AlignCenter})
        circle1.Layout.alignment = Qt.AlignCenter
        circle2.Layout.alignment = Qt.AlignCenter
        circle3.Layout.alignment = Qt.AlignCenter
        addRect(rectComponent, btn, 5)

//  외부 Url 사용할 때 다운로드 완료되면 콜백되어 컴포넌트를 만든다.
//        if(circleComponent.status === Component.Ready){
//            addCircle(circleComponent);
//            console.log("Add!")
//        }else if(circleComponent.status === Component.Error){
//            console.warn(circleComponent.errorString())
//        }
    }
}

