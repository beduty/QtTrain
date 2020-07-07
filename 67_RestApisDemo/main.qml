import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Rest_Apis_Demo")
    function fetchJokes(url, callback){
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
            if ( xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED){
                console.log("HEADERS RECEIVED")
            }else if(xhr.readyState === XMLHttpRequest.DONE ){
                print('DONE')
                if( xhr.status === 200){
                    console.log("Resource found")
                    callback(xhr.responseText.toString())
                }else{
                    console.log("Resource not found")
                    callback(null)
                }
            }
        }
        xhr.open("GET",url)
        xhr.send()
    }

    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        ListModel{
            id : mListModelId
        }

        ListView{
            id : mListViewId
            model : mListModelId
            delegate: delegateId
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        SpinBox{
            id : spinBoxId
            Layout.fillWidth: true
            value:10
        }
        Button{
            id :buttonId
            Layout.fillWidth: true
            text: "Fetch"
            onClicked: {
                fetchJokes("http://api.icndb.com/jokes/random/" +spinBoxId.value, function(response){
                    //console.log(response)
                    if(response){
                        //Parse the Data
                        var object = JSON.parse(response)
                        object.value.forEach(function(joke){
                            mListModelId.append({"joke":joke.joke})
                        })
                    }
                    else{
                        console.log("Something went wrong")
                    }
                })
            }
        }
        Component{
            id : delegateId
            Rectangle{
                id : rectangleId
                width : parent.width
                height: textId.implicitHeight+30
                color: "beige"
                border.color : "yellowgreen"
                radius: 5
                Text{
                    width : parent.width
                    height: parent.height
                    id : textId
                    anchors.centerIn: parent
                    text : joke
                    font.pointSize: 13
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

    }
}
