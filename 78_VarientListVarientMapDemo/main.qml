import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QVariantList and QVariant Map")

    function arrayObjectFunc(array, object){
        console.log("--- Printing Array---")
        array.forEach(function(element){
            console.log("Array item : " + element)
        })

        console.log("---Printing Object---")
        for(var mKey in object){
            console.log("Objction [" + mKey +"]" + object[mKey])
        }
    }

    Button{
        id : button1
        text : "Pass data to Cpp"
        onClicked: {
            var  arr =  ['Africa', 'Asia', 'North America', 'South America', 'Oceania', 'Antarctica']
            var obj = {
                firstName : "John",
                lastName : "Doe",
                location : "Earth"
            }
            CppClass.passFromQmlToCpp(arr,obj);
        }
    }

    Button{
        id : button2
        anchors.top: button1.bottom
        text : "GetVariantListFromCpp"
        onClicked: {
            var data = CppClass.getVariantListFromCpp()
            data.forEach(function(element){
                console.log("Array item :  " + element)
            })
        }
    }

    Button{
        id : button3
        anchors.top: button2.bottom
        text : "GetVariantMapFromCpp"
        onClicked: {
            var data = CppClass.getVariantMappFromCpp()
            for(var mKey in data){
                console.log("Object [" + mKey + "] : " + data[mKey])
            }
        }
    }

    Button{
        id : button4
        anchors.top: button3.bottom
        text : "Trigger JS Call"
        onClicked: {
            CppClass.triggetJSCall();
        }
    }
}
