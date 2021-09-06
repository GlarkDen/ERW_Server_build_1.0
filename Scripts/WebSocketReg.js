function SendRegClick() {
    var socket = null;
    var connection = false;
    socket = new WebSocket("ws://94.50.161.247:8082");
    
    socket.onopen = function () {
        console.log("Соединение установлено.");
        var login = document.getElementById("Logining").value;
        var password = document.getElementById("Passwording").value;
        if (login.length > 3 && password.length > 3) {
            if (login.length < 21 && password.length < 21) {
                if (!login.includes(' ') && !password.includes(' ')) {
                    var msg = "Login: " + login + " Password: " + password + " ";
                    socket.send(msg);
                    console.log("Отправка");
                } else {
                    alert("Логин и пароль не должны содержать пробелов");
                    connection = true;
                    socket.close();
                    console.log("Закрытие соединения");
                }
            } else {
                alert("Длинна пароля и логина не должна превышать 20 символов");
                connection = true;
                socket.close();
                console.log("Закрытие соединения");
            }
        } else {
            alert("Длинна пароля и логина должна быть больше 3 символов");
            connection = true;
            socket.close();
            console.log("Закрытие соединения");
        }
    };
    
    socket.onclose = function (event) {
        if (event.wasClean) {
            console.log('Соединение закрыто чисто');
        } else {
            console.log('Обрыв соединения');
            if (!connection) alert("Лимитное число подключение, подождите пару минут и попробуйте отправить данные ещё раз");
        }
        console.log('Код: ' + event.code + ' причина: ' + event.reason);
    };
    
    socket.onmessage = function (event) {
        console.log("Получены данные " + event.data);
        if (event.data == "regtrue") {
            alert("Регистрация успешна");
            socket.close();
            console.log("Закрытие соединения");
            connection = true;
            document.location.href = "http://94.50.161.247:8082/Informatics";
        } else if (event.data == "loglock") {
            alert("Логин занят");
            connection = true;
            socket.close();
            console.log("Закрытие соединения");
        }
    };
    
    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
    };
}