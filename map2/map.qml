import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.15



Rectangle{
    property double oldlat: 22.9086
    property double oldlng: 120.2058
    property var recentFiles: []
    property var tiptitle: ["date : ","ID : ","class : ", "length : "]
    Plugin{
        id:mapPlugin
        name: "osm"}


    Map{
        id:mapView
        anchors.fill:parent
        plugin: mapPlugin
        center:QtPositioning.coordinate(oldlat,oldlng);
        zoomLevel:6
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






        MapCircle {
            center {
                latitude: oldlat+1
                longitude: oldlng
            }
            radius: 5000.0
            color: 'red'
            border.width: 3

            property string toolTipText: "message \nmmmm"
            ToolTip.text: toolTipText
            ToolTip.visible: toolTipText ? mas.containsMouse : false
            //MouseArea {
            //       anchors.fill: parent
            //       onClicked: { console.log("5454 world") }
           // }
            MouseArea {
                id: mas
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



                   //MouseArea {
                   //       anchors.fill: parent
                   //       onClicked: { console.log("5454 world") }
                  // }
                   MouseArea {
                       id: msas
                       anchors.fill: parent
                       hoverEnabled: true
                   }
               }
           }


    }


    MapCircle {
        id:h2
        center:QtPositioning.coordinate(oldlat,oldlng-2);
        radius: 5000.0
        color: 'blue'
        border.width: 3
        property string toolTipText: "message \nmmmm"
        ToolTip.text: toolTipText
        ToolTip.visible: toolTipText ? m.containsMouse : false
        //MouseArea {
        //       anchors.fill: parent
        //       onClicked: { console.log("5454 world") }
       // }
        MouseArea {
            id: m
            anchors.fill: parent
            hoverEnabled: true
        }
    }



    function setCenter(lat,lng){
        recentFiles=[]
        mapView.pan(oldlat-lat,oldlng-lng)
        //mapView.circle(oldlat,oldlng,20);
        oldlat=lat
        oldlng=lng
        //var Component = Qt.createComponent("qrc:/map.qml")
        //var item = Component.createObject(mapPlugin, {coordinate: QtPositioning.coordinate(lat, lng)})
        h1.radius=10000;
        h1.center=QtPositioning.coordinate(oldlat,oldlng);

        h1.visible=false
        console.log(h1.center);
        //h1.claer();
        var o  = provider.createObject(mapView)
        //o.append({id:hhh})

        o.center=QtPositioning.coordinate(oldlat,oldlng+10);
        o.ToolTip.text="hello world";
        mapView.addMapItem(o)
        recentFiles.push(o)
        var p  = provider.createObject(mapView)
        p.center=QtPositioning.coordinate(oldlat,oldlng+5);
        mapView.addMapItem(p)
        recentFiles.push(p)
        //console.log(mo.mouseX,' ',mo.mouseY);
        //mapView.povider.p.visible=false
        //recentFiles[0].visible=false
        //console.log(recentFiles.length)


        mapView.addMapItem( h2)
    }


    function remove(){
        //mapView.p.visible=false
        console.log(recentFiles.length)

        for (var i=0;i<recentFiles.length;i++){

         recentFiles[i].visible=false
        }


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
        //temp.ToolTip.border.color= "red";
        mapView.addMapItem(temp)
        recentFiles.push(temp)
    }


}
