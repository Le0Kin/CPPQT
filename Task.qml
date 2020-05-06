import QtQuick 2.0
import QtQuick.Layouts 1.3

Row {
    Layout.fillWidth: true
    height: 35

    property alias idColor: _ID.color
    property alias nameColor: _NameTask.color
    property alias descriptionColor: _DescriptionTask.color
    property alias startColor: _DateStartTask.color
    property alias endColor: _DateEndTask.color
    property alias progColor: _NowProgress.color

    property alias idTask: _IdText.text
    property alias nameTask: _NameTaskText.text
    property alias descriptionTask: _DescriptionTaskText.text
    property alias dateStart: _DateStartTaskText.text
    property alias dateEnd: _DateEndTaskText.text
    property alias progressTask: _NowProgressText.text


    // ID
    Rectangle {
        id: _ID
        width: parent.width * 7 / 100   // 7%
        height: parent.height
        anchors.left: parent
        border.width: 1
        Text {
            id: _IdText
            text: qsTr("ID")
            anchors.centerIn: parent
        }
    }

    // Name task
    Rectangle {
        id: _NameTask
        width: parent.width * 18.6 / 100   // 18.6%
        height: parent.height
        anchors.left: parent
        border.width: 1
        Text {
            id: _NameTaskText
            text: qsTr("Название задачи")
            anchors.centerIn: parent
        }
    }

    // Decription task
    Rectangle {
        id: _DescriptionTask
        width: parent.width * 18.6 / 100   // 18.6%
        height: parent.height
        anchors.left: parent
        border.width: 1
        Text {
            id: _DescriptionTaskText
            text: qsTr("Описание задачи")
            anchors.centerIn: parent
        }
    }

    // Date start
    Rectangle {
        id: _DateStartTask
        width: parent.width * 18.6 / 100   // 18.6%
        height: parent.height
        anchors.left: parent
        border.width: 1
        Text {
            id: _DateStartTaskText
            text: qsTr("Дата начала выполнения задачи")
            anchors.centerIn: parent
        }
    }

    // Date end
    Rectangle {
        id: _DateEndTask
        width: parent.width * 18.6 / 100   // 18.6%
        height: parent.height
        anchors.left: parent
        border.width: 1
        Text {
            id: _DateEndTaskText
            text: qsTr("Дата окончания выполнения задачи")
            anchors.centerIn: parent
        }
    }

    // Now progress
    Rectangle {
        id: _NowProgress
        width: parent.width * 18.6 / 100   // 18.6%
        height: parent.height
        anchors.left: parent
        border.width: 1
        Text {
            id: _NowProgressText
            text: qsTr("Текущий прогресс")
            anchors.centerIn: parent
        }
    }
}

