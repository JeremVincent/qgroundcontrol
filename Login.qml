import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import QGroundControl 1.0
import QGroundControl.Controllers 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {


    property var margin: 5

    LoginController {
        id: _loginController
    }

    ParcelleManagerController {
        id: _parcelleManagerController
    }

    Popup {
        id: adminInterface
        width: parent.width
        height: parent.height
        modal: true
        ColumnLayout {
            anchors.fill: parent
        TabView {
            Layout.fillWidth: true
            Layout.fillHeight: true


            Tab {
                title: "User Manager"


                ColumnLayout {
                    anchors.fill: parent
                   Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"


                        TableView {
                            id: userTableView
                            anchors.fill: parent
                            selectionMode: SelectionMode.MultiSelection
                            TableViewColumn {
                                role: "username"
                                title: "Username"
                                movable: false
                                width: userTableView.width/3
                            }
                            TableViewColumn {
                                role: "nom"
                                title: "Nom"
                                movable : false
                                width: userTableView.width/3
                            }
                            TableViewColumn {
                                role: "prenom"
                                title: "Prenom"
                                movable : false
                                width: userTableView.width/3
                            }

                            SqlCustomModel {
                                id: userModel

                                Component.onCompleted: {
                                    setupForUser()
                                }

                            }

                            model: userModel

                            Dialog {
                                id: addUserDialog
                                modal: true


                                onAccepted: {
                                    _loginController.addUser(userModel, a_usernameField.text, a_passwordField.text, a_nomField.text, a_prenomField.text)
                                }


                                title: "Add User"

                                standardButtons: Dialog.Ok | Dialog.Cancel
                                x: (parent.width - width) / 2
                                y: (parent.height - height) / 2

                                GridLayout {
                                    columns: 4
                                    anchors.fill: parent

                                    Label {
                                        text: "Username"
                                    }
                                    Label {
                                        text: "Password"
                                    }
                                    Label {
                                        text: "Nom"
                                    }
                                    Label {
                                        text: "Prenom"

                                    }
                                    TextField {
                                        id: a_usernameField
                                    }
                                    TextField {
                                        id: a_passwordField
                                        echoMode: TextInput.Password
                                    }
                                    TextField {
                                        id: a_nomField
                                    }
                                    TextField {
                                        id: a_prenomField
                                    }
                                }
                            }

                            Dialog {
                                id: editUserDialog

                                property int userIndex: 0

                                function refresh() {
                                    userField.updateContent()
                                    nomField.updateContent()
                                    prenomField.updateContent()
                                }

                                onAccepted: {
                                    _loginController.modifyUser(userModel, userIndex, userField.text, nomField.text, prenomField.text)
                                }


                                title: "Edit Parcelle"

                                standardButtons: Dialog.Ok | Dialog.Cancel
                                x: (parent.width - width) / 2
                                y: (parent.height - height) / 2
                                modal: true

                                GridLayout {
                                    columns: 3
                                    anchors.fill: parent

                                    Label {
                                        text: "username"
                                    }
                                    Label {
                                        text: "nom"
                                    }
                                    Label {
                                        text: "prenom"
                                    }
                                    TextField {
                                        id: userField
                                        enabled: false
                                        function updateContent() {
                                            text=userModel.getRecordValue(editUserDialog.userIndex, "username")
                                        }
                                    }
                                    TextField {
                                        id: nomField
                                        function updateContent() {
                                            text=userModel.getRecordValue(editUserDialog.userIndex, "nom")
                                        }
                                    }
                                    TextField {
                                        id: prenomField
                                        function updateContent() {
                                            text=userModel.getRecordValue(editUserDialog.userIndex, "prenom")
                                        }
                                    }
                                }
                            }

                            Dialog {
                                id: editPassDialog
                                modal: true

                                property int userIndex: 0

                                function refresh() {
                                    userField2.updateContent()
                                }

                                onAccepted: {
                                    if (newPassField.text == confirmationField.text) {
                                        _loginController.modifyPassword(userModel, userIndex, userField2.text, oldPassField.text, newPassField.text)
                                    }
                                    else {
                                        wrongConfirmationDialog.open()
                                    }
                                }


                                title: "Edit Password"

                                standardButtons: Dialog.Ok | Dialog.Cancel
                                x: (parent.width - width) / 2
                                y: (parent.height - height) / 2

                                GridLayout {
                                    columns: 4
                                    anchors.fill: parent

                                    Label {
                                        text: "username"
                                    }
                                    Label {
                                        text: "old password"
                                    }
                                    Label {
                                        text: "new password"
                                    }
                                    Label {
                                        text: "confirmation"
                                    }

                                    TextField {
                                        id: userField2
                                        enabled: false
                                        function updateContent() {
                                            text=userModel.getRecordValue(editPassDialog.userIndex, "username")
                                        }
                                    }
                                    TextField {
                                        id: oldPassField
                                         echoMode: TextInput.Password
                                    }
                                    TextField {
                                        id: newPassField
                                         echoMode: TextInput.Password
                                    }
                                    TextField {
                                        id: confirmationField
                                        echoMode: TextInput.Password
                                    }


                                }


                            }

                        }
                   }
                   RowLayout {
//                       columns: 4
//                       anchors.fill: parent

                       Button {
                           Layout.fillWidth: true
                           Layout.margins : margin
                           text: "Add User"
                           onClicked: {
                               addUserDialog.open()
                           }
                       }

                       Button {
                            Layout.fillWidth: true
                            Layout.margins : margin
                            text: "Remove User"
                                onClicked: {
                                        var selected=[]
                                        userTableView.selection.forEach( function(rowIndex) {console.log("Selected : "+rowIndex);selected.push(rowIndex)} )
                                        userTableView.selection.clear()

                                        _loginController.deleteUser(userModel,selected)
                                   }
                        }

                        Button {

                            Layout.margins : margin
                            Layout.fillWidth: true

                            Layout.alignment: Qt.AlignHCenter
                            text: "Modify User"


                                onClicked: {
                                if(userTableView.selection.count===1) {
                                    var sel=0
                                    userTableView.selection.forEach(function(rowIndex) {sel=rowIndex})
                                    editUserDialog.userIndex=sel
                                    editUserDialog.refresh()
                                    editUserDialog.open()
                                }
                                else {
                                    errorModifyOnlyOneDialog.open()
                                }
                            }
                        }

                        Button {

                            Layout.margins : margin
                            Layout.fillWidth: true

                            Layout.alignment: Qt.AlignHCenter
                            text: "Modify Password"


                                onClicked: {
                                if(userTableView.selection.count===1) {
                                    var sel=0
                                    userTableView.selection.forEach(function(rowIndex) {sel=rowIndex})
                                    editPassDialog.userIndex=sel
                                    editPassDialog.refresh()
                                    editPassDialog.open()
                                }
                                else {
                                    errorModifyOnlyOneDialog.open()
                                }
                            }
                        }
                   }
                }
            }
            Tab {
                title: "Mission Manager"
                ColumnLayout {
                    anchors.fill: parent
                   Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"

                        SqlCustomModel {
                            id: missionModel

                            Component.onCompleted: {
                                setupForMission()
                            }

                        }

                        TableView {
                            id: missionTableView
                            anchors.fill: parent
                            selectionMode: SelectionMode.MultiSelection
                            TableViewColumn {
                                role: "owner"
                                title: "Owner"
                                movable: false
                                width: missionTableView.width/2
                            }
                            TableViewColumn {
                                role: "name"
                                title: "name of the mission"
                                movable : false
                                width: missionTableView.width/2
                            }

                            model: missionModel
                        }
                   }


                    Button {
                        Layout.fillWidth: true
                        Layout.margins : margin
                        text: "Remove Mission"
                            onClicked: {
                                    var selected=[]
                                    missionTableView.selection.forEach( function(rowIndex) {console.log("Selected : "+rowIndex);selected.push(rowIndex)} )
                                    missionTableView.selection.clear()

                                    _loginController.deleteMission(missionModel,selected)
                               }
                    }
                }
            }
            Tab {
                title: "Parcelle Manager"
                ColumnLayout {
                    anchors.fill: parent
                   Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"

                        SqlCustomModel {
                            id: parcelleModel

                            Component.onCompleted: {
                                setupForParcelle()
                            }

                        }

                        TableView {
                            id: parcelleTableView
                            anchors.fill: parent
                            selectionMode: SelectionMode.MultiSelection
                            TableViewColumn {
                                role: "owner"
                                title: "Owner"
                                movable: false
                                width: 2*parcelleTableView.width/8
                            }
                            TableViewColumn {
                                role: "name"
                                title: "name of the parcelle"
                                movable : false
                                width: 4*parcelleTableView.width/8
                            }
                            TableViewColumn {
                                role: "type"
                                title: "Type"
                                movable: false
                                width: parcelleTableView.width/8
                            }
                            TableViewColumn {
                                role: "speed"
                                title: "Speed"
                                movable: false
                                width: parcelleTableView.width/8
                            }

                            model: parcelleModel
                        }
                   }


                    Button {
                        Layout.fillWidth: true
                        Layout.margins : margin
                        text: "Remove Parcelle"
                            onClicked: {
                                    var selected=[]
                                    parcelleTableView.selection.forEach( function(rowIndex) {console.log("Selected : "+rowIndex);selected.push(rowIndex)} )
                                    parcelleTableView.selection.clear()

                                    _parcelleManagerController.deleteParcelle(parcelleModel,selected)
                               }
                    }
                }
            }
            Tab {
                title: "Flight Parameters"

                ColumnLayout {
                    anchors.fill: parent
                    property var m: 5
                    property var m2: 2

                Label {
                    text: "Speed"
                    color: "gray"
                    Layout.margins: m2
                }
                GridLayout {
                    columns: 3

                    Label {
                        text: "Low Speed"
                    }
                    Label {
                        text: "Medium Speed"
                    }
                    Label {
                        text: "High Speed"
                    }


                    TextField {
                        id: lowspeed
                        text: _loginController.getSpeedLow()
                    }
                    TextField {
                        id: medspeed
                        text: _loginController.getSpeedMed()
                    }
                    TextField {
                        id: highspeed
                        text: _loginController.getSpeedHigh()
                    }
                }

                Label {
                    text: "Limite number"
                    color: "gray"
                    Layout.margins: m2
                }

                GridLayout {
                    columns: 3

                    Label {
                        text: "Limit of session        "
                    }
                    Label {
                        text: "Limit of parcelle / user"
                    }
                    Label {
                        text: "Limit of mission / user "
                    }


                    TextField {
                        id: nbSession
                        text: _loginController.getNbSession()
                    }
                    TextField {
                        id: nbParcelle
                        text: _loginController.getNbParcelle()
                    }
                    TextField {
                        id: nbMission
                        text: _loginController.getNbMission()
                    }
                }


                Label {
                    text: "Checklist"
                    color: "gray"
                    Layout.margins: m2
                }

                TextArea {
                    id: checklistArea
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: _loginController.getParamChecklist()
                    Layout.margins: m
                }

                Button {
                    text: "Save"
                    Layout.margins: m
                    onClicked: {
                        _loginController.setParamSpeed(lowspeed.text, medspeed.text, highspeed.text)
                        _loginController.setParamLimit(nbSession.text, nbParcelle.text, nbMission.text)
                        _loginController.setParamChecklist(checklistArea.text)
                    }
                }
                }
            }
        }
        Button {
            Layout.alignment: Qt.AlignRight
            text: "Disconnect"
            Layout.margins: 5
            style: ButtonStyle {
                   background: Rectangle {
                       implicitWidth: 120
                       implicitHeight: 35
                       border.width: control.activeFocus ? 2 : 1
                       border.color: "pink"
                       radius: 20
                       gradient: Gradient {
                           GradientStop { position: 0 ; color: control.pressed ? "pink" : "red" }
                           GradientStop { position: 1 ; color: control.pressed ? "purple" : "darkred" }
                       }
                   }
               }
            onClicked: {
                adminInterface.close()
                _loginController.onAdminClosed()
            }
        }
        }

    }

    Rectangle {
        color: "black"
        anchors.fill: parent

    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.bottomMargin: parent.height/6
        anchors.topMargin: parent.height/6
        anchors.leftMargin: parent.width/3
        anchors.rightMargin: parent.width/3

    ColumnLayout {

        anchors.fill: parent
        anchors.margins: margin

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Layout.alignment: Qt.AlignHCenter
            Layout.rightMargin: 10
            Layout.leftMargin: 10
            color: "pink"
            ColumnLayout {
                anchors.fill: parent
            Label {
                text: "Please Login!"
                color: "white"
                Layout.alignment: Qt.AlignCenter
                font.bold: true

            }
            }

        }

        Image {
            source:"/res/resources/icons/mainlogo.png"
            fillMode: Image.PreserveAspectFit
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth:true
        }

        Label {
            text: "Username"
            color: "gray"
            Layout.alignment: Qt.AlignHCenter
            Layout.rightMargin: 20
        }

        TextField {
            id: usernameField
            Layout.alignment: Qt.AlignHCenter

        }

        Label {
            text: "Password"
            color: "gray"
            Layout.alignment: Qt.AlignHCenter
            Layout.rightMargin: 20
        }

        TextField {
            id: passwordField
            Layout.alignment: Qt.AlignHCenter
            echoMode: TextInput.Password
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            text : "Login"

        onClicked: {
            var username=usernameField.text
            if(_loginController.login(username, passwordField.text))
            {
                if(username==="admin")
                {
                    console.log("ADMIN LOGIN")
                    adminInterface.open()
                }
                else {
                    console.log("Logged in as user "+username)
                    _loginController.loadMainWindow()
                    loginMainWindow.close()
                }
            }
            else {
                errorLogin.open()
            }
            usernameField.text=""
            passwordField.text=""
        }
    }
    }
    }
    }
    Dialog {
        id: errorLogin
        modal: true
        title: "Error"
        standardButtons: Dialog.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        Label{
            text: "Invalid username or password!"
        }

    }

    Dialog {
        id: wrongConfirmationDialog
        standardButtons: Dialog.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        modal: true
        title: "Error"
        Label{
            text: "New password and confirmation is not the same"
        }

    }

    Dialog {

        id: errorModifyOnlyOneDialog
        standardButtons: Dialog.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        title: "Error"
        modal: true

        Label{
            text: "Please select ONE line to modify."
        }

    }

}
