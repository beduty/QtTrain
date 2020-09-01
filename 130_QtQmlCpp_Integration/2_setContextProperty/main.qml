import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
Window {
    id :root
    visible: true
    width: 320
    height: 500
    title: qsTr("SwipeViewPageIndicatoreDemo")
    Connections{
        target: CppUrlDownloader
        onPostChanged :{
            console.log("size :  " + mPosts.length);// <<  << CppUrlDownloader.mPosts.size();
        }
    }

    PageIndicator {
        id: pageIndicatorId
        count: swipeViewId.count
        currentIndex: swipeViewId.currentIndex
        anchors.bottom: swipeViewId.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
    SwipeView {
        id: swipeViewId
        currentIndex: pageIndicatorId.currentIndex
        anchors.fill: parent
        Item {
            id: firstPage
            width: root.width
            height: root.height
            Text{
                id : txt1Id
                text: "1"
                y : 50
                anchors.horizontalCenter:  parent.horizontalCenter
            }
            Flickable{
                anchors.top : txt1Id.bottom
                anchors.topMargin: 50
                width: root.width
                height: root.height
                contentHeight: mGridId.implicitHeight
                ScrollBar.vertical: ScrollBar{}
                GridLayout{
                    id : mGridId
                    columns: 2
                    anchors.centerIn: parent

                    ScrollView{
                        implicitHeight: 200
                        implicitWidth: firstPage.width
                        TextArea{
                            id: textAreaId
                            background: Rectangle{
                                width: parent.width
                                height: 200
                                color: "black"
                            }
                            color: "white"
                            placeholderText: "Listening..."
                            font.pointSize: 8
                        }
                        Layout.fillWidth: true
                        Layout.columnSpan: 2
                    }
                    Button{
                        text: "Send to C++"
                        onClicked: {
                            var arr=['Apple', 'Banana', 'Avocado', 'Pear', 'Orange'];
                            CppLists.vectorToCpp(arr);

                            var text = textAreaId.text;
                            var receive = text + "\n[sendData]\n";
                            arr.forEach(function(element){
                                receive += (" "+element );
                            });
                            textAreaId.text = receive + "\n";
                        }
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Button{
                        text: "Read from C++"
                        onClicked: {
                            var arr = CppLists.vectorFromCpp();
                            var text = textAreaId.text;
                            var receive = text + "\n[readData]\n";
                            arr.forEach(function(element){
                                receive += ( " "+element );
                            });
                            textAreaId.text = receive+ "\n";
                        }
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Button{
                        text : "QVariant List, Map to Cpp"
                        onClicked: {
                            var  arr =  ['Africa', 'Asia', 'North America', 'South America', 'Oceania', 'Antarctica']
                            var obj = {
                                firstName : "John",
                                lastName : "Doe",
                                location : "Earth"
                            }
                            CppLists.listMapToCpp(arr,obj);

                            var text = textAreaId.text;
                            var receive = text + "\n[send QVariantList Data]\n";
                            for (var i = 0; i < arr.length; i++)
                                receive += (" "+arr[i] );

                            receive += "\n\n[send QVariantMap Data]\n";
                            for (var prop in obj)
                                receive += ("  "+ prop + ":" + obj[prop] );

                            textAreaId.text = receive + "\n";
                        }
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    Button{
                        text : "GetVariantListFromCpp"
                        onClicked: {
                            var arr = CppLists.listFromCpp()

                            var text = textAreaId.text;
                            var receive = text + "\n[read QVariantList Data]\n";
                            arr.forEach(function(element){
                                receive += ( "  "+element );
                            });
                            textAreaId.text = receive+ "\n";
                        }
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    Button{
                        text : "GetVariantMapFromCpp"
                        onClicked: {
                            var data = CppLists.mapFromCpp()
                            var text = textAreaId.text;
                            var receive = text + "\n[read QVariantMap Data]\n";
                            for(var mKey in data){
                                receive += ("  "+ mKey + ":" + data[mKey] );
                            }
                            textAreaId.text = receive+ "\n";
                        }
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
        }
        Item {
            id: secondPage
            width: root.width
            height: root.height
            ColumnLayout{
                anchors.fill: parent
                Button{
                    id : downloadButn
                    Layout.fillWidth: true
                    height: 50
                    text: "download"
                    onClicked:{
                        CppUrlDownloader.downloadPosts(5);
                    }
                }
                Button{
                    id : delete1Btn
                    Layout.fillWidth: true
                    height: 50
                    text: "delete last one"
                    onClicked:{
                        CppUrlDownloader.removeLast();
                    }
                }
                ListView{
                    id : mListView
                    width: secondPage.width
                    Layout.fillHeight: true
                    highlight: Rectangle{
                        width: secondPage.width
                        color: "red"
                        opacity: 0.1
                        radius: 14
                        border.color: "yellowgreen"
                        z : 3
                    }
                    model: CppUrlDownloader.posts
                    delegate: Component{
                        id :delegateId
                        Rectangle{
                            id : rectangleId
                            width: parent.width
                            height: textId.implicitHeight + 10
                            color: "beige"
                            border.color: "yellowgreen"
                            radius: 10
                            Text {
                                id : textId
                                width: parent.width
                                height: parent.height
                                anchors.centerIn: parent
                                font.pointSize: 13
                                text:modelData
                                wrapMode: Text.WordWrap
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("clicked on :  " + modelData)
                                    mListView.currentIndex = index
                                }
                            }
                        }
                    }
                }
            }
        }
        Item {
            id: thirdPage
            width: root.width
            height: root.height
            Text{
                text: "3"
                anchors.centerIn: parent
            }
        }
    }
}
