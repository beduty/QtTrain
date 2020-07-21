import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("String Date Number Types Demo")
    property  string mValue : "Click %1 times, double is %2"
    property int clickCount : 0

    Connections{
        target: CppClass
        onSendDateTime : {
            console.log("Received datetime : " + datetimeParam);
            console.log("Year : " + datetimeParam.getFullYear());
            console.log("... : " + datetimeParam.toGMTString());
        }
        onSendTime : {
            console.log("Received time : " + timeParam);
        }
    }

    Button{
        id : mButtom
        text : "Click Me"
        onClicked: {
            //CppClass.cppSlot()

            var date = new Date();
            CppClass.timeSlot(date);
            CppClass.dateTimeSlot(date);

            clickCount++
            mButtom.text = mValue.arg(clickCount).arg(clickCount*2)
        }
    }

    Component.onCompleted: {
        var mDate = new Date();
        // 1. toLocaleDateString(contains date)
        print(mDate.toLocaleDateString());
        print(mDate.toLocaleDateString(Qt.locale("de_DE")));
        print(mDate.toLocaleDateString(Qt.locale("fr_FR")));
        print(mDate.toLocaleDateString(Qt.locale("zh_CN"), "yyyy-MMMM-dd"));

        // 2. toLocaleString(contains date and time)
        print(mDate.toLocaleString(Qt.locale("en_US"), "yyyy-MMM-dd -- HH:mm:ss"));

        // 3. toLocaleTimeString(contains time)
        print(mDate.toLocaleTimeString(Qt.locale("en_US"), "HH:mm:ss"));

        // 4. fromLocalDateString
        var myDate = Date.fromLocaleDateString(Qt.locale("en_US"), "2018-09-17", "yyyy-MM-dd")
        print("Date is " + myDate)

        // 5. fromLocaleString
        myDate = Date.fromLocaleString(Qt.locale("en_US"), "2018-09-17 --16:23:35", "yyyy-MM-dd --HH:mm:ss")
        print(myDate)

        // 6. fromLocaleTimeString
        myDate = Date.fromLocaleTimeString(Qt.locale("en_US"), "16:23:35", "HH:mm:ss")
        print(myDate)

        var mLocale = Qt.locale("zh_CN")
        var number = Number("123.01")
        var outStr = number.toLocaleCurrencyString(mLocale, mLocale.currencySymbol(Locale.CurrencySymbol))
        print("currency is : " + outStr)
        mButtom.text = outStr

        mLocale = Qt.locale("zh_CN")
        number = Number("124.03")
        outStr = number.toLocaleString(mLocale, 'f', 4)
        print("currency is : " + outStr)
    }
}
