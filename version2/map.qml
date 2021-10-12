import QtQuick 2.0
import QtLocation 5.8
import QtPositioning 5.8
import QtQuick.Controls 2.15




Rectangle{
    property double oldlat: 22.9086
    property double oldlng: 120.2058
    property var recentFiles: []
    property var tiptitle: ["date : ","ID : ","class : ", "length : "]
    property var colortype: ["red","yellow","green", "blue"]
    property var animaltype: ["tuna","shark","marlin", "none"]
    Plugin{
        id:mapPlugin
        name: "osm"



    }



    Map{
        id:mapView
        anchors.fill:parent
        plugin: mapPlugin
        center:QtPositioning.coordinate(oldlat,oldlng);
        zoomLevel:6
        //PluginParameter { name: "osm.mapping.custom.host"; value: "0cf39d2b3cf048539cdc2a4bca87cada" }
        activeMapType: supportedMapTypes[10]    // 2 4

        onCenterChanged: {


            h1.radius=5000.0*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))
            for (var i=0;i<recentFiles.length;i++){
             recentFiles[i].radius=5000.0*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))*(6/(mapView.zoomLevel))
            }
        }
        MapCircle {
            id:h1
            visible: true
            center:QtPositioning.coordinate(oldlat,oldlng);
            radius: 5000.0*6/(mapView.zoomLevel)
            color: 'green'
            border.width: 3
            property string toolTipText: "mgrdfessage \nmmmm"
            //ToolTip.text: toolTipText
            //ToolTip.visible: toolTipText ? ma.containsMouse : false
            ToolTip {
                id: control
                property string toolTipText: "mgrdfessage \nmmmm"
                text: qsTr("A descriptive tool tip of what the button does")

                background: Rectangle {
                    border.color: "#21be2b"
                }
                visible: toolTipText ? ma.containsMouse : false
            }
            //MouseArea {
            //       anchors.fill: parent
            //       onClicked: { console.log("5454 world") }
           // }
            MouseArea {
                id: ma
                anchors.fill: parent
                hoverEnabled: true
            }


        }
        Component{
               id: provider
               MapCircle{
                   visible:true
                   center:QtPositioning.coordinate(oldlat,oldlng+10);
                   radius: 500.0
                   color: 'green'
                   border.width: 3
                   property string toolTipText: " "
                   ToolTip.text: toolTipText

                   ToolTip.visible: toolTipText ? msas.containsMouse : false
                   MouseArea {
                       id: msas
                       anchors.fill: parent
                       hoverEnabled: true
                   }
               }
           }


    }

    function setCenter(lat,lng){
        mapView.center.latitude=lat
        mapView.center.longitude=lng
        mapView.zoomLevel =10
    }


    function remove(){

        //mapView.p.visible=false
        console.log(recentFiles.length)

        for (var i=0;i<recentFiles.length;i++){
         //mapView.removeMapItem(recentFiles[i])

         recentFiles[i].visible=false
         //recentFiles.pop()
        }
        recentFiles=[]


    }
    function testd(list_test){



        //mapView.p.visible=false
        console.log(list_test[0])
        var temp  = provider.createObject(mapView)
        temp.center=QtPositioning.coordinate(list_test[4],list_test[5]);
        temp.ToolTip.text=tiptitle[0]+list_test[0];
        for (var i=0;i<3;i++){
          temp.ToolTip.text=temp.ToolTip.text+"\n"+tiptitle[i+1]+list_test[i+1];
        }
        temp.color= search(list_test[2])
        temp.border.color = search(list_test[2])
        mapView.addMapItem(temp)
        recentFiles.push(temp)
        //mapView.zoomLevel=mapView.zoomLevel+1
        //mapView.zoomLevel=mapView.zoomLevel-1

    }

    function search(txt)
    {
        console.log(txt)
        for (var i=0;i<4;i++)
        {
            console.log("sss")
            console.log(txt)
            console.log(txt==animaltype[i])
            if (animaltype[i]==txt){
                return colortype[i]
            }
        }

        return colortype[3]
    }


}
