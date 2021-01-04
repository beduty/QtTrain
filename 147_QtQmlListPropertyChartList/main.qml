import QtQuick 2.12
import QtQuick.Window 2.12
import StairChart 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout{
        width: parent.width
        Button{
            width: parent.width
            height: 50
            onClicked:{
                //myChart.stairs
            }
        }

        StairChart{
            id : myChart
            title: "Whear Consumption by 2030 in Mills of Tons"
            bgColor: "lightgray"
            stairs: [
                Stair{
                    from: 50
                    value: 250
                    color: "red"
                    text: "RW"
                },
                Stair{
                    from: 100
                    value: 320
                    color: "yellow"
                    text: "CN"
                },
                Stair{
                    from: 150
                    value: 133
                    color: "lightblue"
                    text: "DE"
                },
                Stair{
                    from: 200
                    value: 202
                    color: "steelblue"
                    text: "FR"
                },
                Stair{
                    from: 250
                    value: 250
                    color: "skyblue"
                    text: "US"
                },
                Stair{
                    from: 300
                    value: 200
                    color: "beige"
                    text: "ZA"
                },
                Stair{
                    from: 350
                    value: 300
                    color: "cyan"
                    text: "JP"
                },
                Stair{
                    from: 400
                    value: 122
                    color: "red"
                    text: "VT"
                }
            ]
        }
    }

}
