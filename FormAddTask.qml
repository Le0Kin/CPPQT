import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.0

Window {
    width:400
    height:300
    minimumWidth: 400
    minimumHeight: 300

    ColumnLayout {
        width: parent.width
        height: parent.height


        RowLayout {
            id: _nameTask_layout
            anchors.left: parent.left
            height: parent.height / 6

            Text {
                id: _nameTask_label
                text: qsTr("Название задачи")
                verticalAlignment: Text.AlignVCenter
                height: parent.height
                width: parent.width / 10 * 100
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
            }

            TextField {
                id: _nameTask_input
                width: parent.width / 90 * 100
                height: parent.height
                Layout.fillWidth: true
                font.pixelSize: 12
                text: "Name"
            }
        }

        RowLayout {
            id: _descriptionTask_layout
            anchors.left: parent.left
            height: parent.height / 6

            Text {
                id: _descriptionTask_label
                text: qsTr("Описание задачи")
                verticalAlignment: Text.AlignVCenter
                height: parent.height
                width: parent.width / 10 * 100
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
            }

            TextField {
                id: _descriptionTask_input
                width: parent.width / 90 * 100
                height: parent.height
                Layout.fillWidth: true
                font.pixelSize: 12
                text: "Description"
            }
        }

        RowLayout {
            id: _dateStart_layout
            anchors.left: parent.left
            height: parent.height / 6

            Text {
                id: _dateStart_label
                text: qsTr("Дата начала")
                verticalAlignment: Text.AlignVCenter
                height: parent.height
                width: parent.width / 10 * 100
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
            }

            TextField {
                id: _dateStart_input
                width: parent.width / 90 * 100
                height: parent.height
                Layout.fillWidth: true
                font.pixelSize: 12
                text: "00.00.0000"
            }
        }

        RowLayout {
            id: _dateEnd_layout
            anchors.left: parent.left
            height: parent.height / 6

            Text {
                id: _dateEnd_label
                text: qsTr("Дата окончания")
                verticalAlignment: Text.AlignVCenter
                height: parent.height
                width: parent.width / 10 * 100
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
            }

            TextField {
                id: _dateEnd_input
                width: parent.width / 90 * 100
                height: parent.height
                Layout.fillWidth: true
                font.pixelSize: 12
                text: "00.00.0000"
            }
        }

        RowLayout {
            id: _progress_layout
            anchors.left: parent.left
            height: parent.height / 6

            Text {
                id: _progress_label
                text: qsTr("Текущий прогресс")
                verticalAlignment: Text.AlignVCenter
                height: parent.height
                width: parent.width / 10 * 100
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
            }

            TextField {
                id: _progress_input
                width: parent.width / 90 * 100
                height: parent.height
                Layout.fillWidth: true
                font.pixelSize: 12
                text: "0"
            }
        }

        Button {
            text: "Добавить"
            Layout.fillWidth: true

            onClicked: {

                database.insertDataToTable(_nameTask_input.text, _descriptionTask_input.text, _dateStart_input.text, _dateEnd_input.text, _progress_input.text)
                mymodel.updateModel()

//                var component
//                var sprite
//                component = Qt.createComponent("Task.qml")
//                if (component.status === Component.Ready){
//                    sprite = component.createObject(_mainLayout, {"idTask": _addTask.id(), "nameTask": _addTask.name(), "descriptionTask": _addTask.description(),
//                                                                  "dateStart": _addTask.dateStart(), "dateEnd": _addTask.dateEnd(), "progressTask": _addTask.progress()})
//                }
            }

        }
    }
}


