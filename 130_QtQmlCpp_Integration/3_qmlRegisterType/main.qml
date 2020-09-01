import QtQuick 2.12
import QtQuick.Window 2.12
import PokeData 1.0
import QtQuick.Layouts 1.12
Window {
    visible: true
    width: 300
    height: 480
    title: qsTr("Hello World")
    //property string imgpath: "https://raw.githubusercontent.com/fanzeyi/pokemon.json/master/images/"
    property string path : "https://raw.githubusercontent.com/fanzeyi/pokemon.json/master/images/"//"%1.png"
    function getPath(index) {
       return ( (index > 98)? (path +(index+1) + ".png" ) :
                       (index > 8)? path +"0" +(index+1) + ".png":
                                    path +"00" +(index+1) + ".png" );
    }

    PokeData{
        id : pokemon
    }
    ColumnLayout {
        anchors.fill: parent
        Rectangle{
            id :rect
            Layout.fillWidth: true
            height: 50
            color: "orange"
            Text {
                anchors.centerIn: parent
                text: qsTr("pokeData!" + pokemon.imgUrls.length)
                color: "black"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked!")
                    pokemon.fetch()
                }
            }
        }
        ListView{
            id : lstViewId
            Layout.fillWidth: true
            Layout.fillHeight: true
            model : pokemon.imgUrls
            delegate: Component{
                id :delegateId
                Rectangle{
                    id : rectangleId
                    width: parent.width
                    height: 100
                    color: "beige"
                    border.color: "yellowgreen"
                    radius: 10
                    Row{
                        anchors.fill: parent
                        Item{
                            height: parent.height
                            width: parent.width/2
                            Image{
                                anchors.centerIn: parent
                                height: parent.height-10
                                width: parent.width
                                source: getPath(index)
                                fillMode: Image.PreserveAspectFit
                            }
                        }
                        Item{
                            width: parent.width/2
                            height:  parent.height
                            Text {
                                anchors.fill: parent
                                text: modelData
                                font.pointSize: 20
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }
            }
        }
    }
}
