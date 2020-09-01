import QtQuick 2.4
//싱글톤 버전
//import CalculatorApp 1.0

CaculatorFormForm {
    // ui.qml에서 State를 추가해준뒤, 기존 것과의 차이를 준다.
    // --> 알아서 QML에서 transitions 를 만들어준다.
    // --> 사용자는 state:{..}에서 Input에 따른 state이름을 return해주면된다!
    state: {
        if(operationFactorial.checked){
            return "single_argument"
        }
        else{return "";}
    }
    // 알아서 Animating된다.
    transitions: Transition {
        PropertyAnimation{
            property: "opacity"
            duration: 300
        }
    }
    reset.onClicked:{
        argument1.text = "0";
        argument2.text = "0";
        operationAdd.checked = true;
    }
    result.text: {
        var value1 = parseFloat(argument1.text);
        var value2 = parseFloat(argument2.text);
        if(operationMultiply.checked)
            return value1*value2;
        else if(operationFactorial.checked){
            // C++ 객체를 QML엔진에서 엑세스할 수 있는 JavaScript 객체로 노출했다.
            //advancedCalculator를 전역변수로 주입했기 때문에,
            // 인스턴스의 멤버함수를 사용할 수 있다!
            //싱글톤 버전
            //return AdvancedCalculator.factorial(value1);
            console.log("test : " +  advancedCalculator.type)
            return advancedCalculator.factorial(value1);
        }
        else
            return value1+value2;
    }
}
