import QtQuick 2.3
import QtQuick.Window 2.2
import QtPositioning 5.3
import QtLocation 5.5

Item {

    PositionSource {
        id: kor
        active: true
        onPositionChanged: {
            map.center = position.coordinate;
        }
    }


    Map {

        id: map
        anchors.fill: parent
        plugin: Plugin {name: "osm" }
        center: kor.position.coordinate
        zoomLevel: 20


        MapQuickItem {
            coordinate: kor.position.coordinate
            sourceItem: Image {
                id: name
                source: "marker.png"
            }
            anchorPoint.x: image.width / 2
            anchorPoint.y: image.height
        }


    }
}
