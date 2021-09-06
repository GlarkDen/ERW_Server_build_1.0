var log = false;
var Clientlogin;
var socket = null;
socket = new WebSocket("ws://94.50.161.247:8082");

socket.onopen = function () {
    console.log("Соединение установлено.");
    socket.send("Profile");
    console.log("Отправка");
};

socket.onclose = function (event) {
    if (event.wasClean) {
        console.log('Соединение закрыто чисто');
    } else {
        console.log('Обрыв соединения');
    }
    console.log('Код: ' + event.code + ' причина: ' + event.reason);
};

socket.onmessage = function (event) {
    console.log("Получены данные: " + event.data);
    if ((event.data != "filenotopen") && (event.data != "filejsonerror") && (event.data != "ipnotfound")) {
        log = true;
        var msg = event.data;
        msg += " ";
        var i = msg.indexOf(" ");
        var h = 1;
        var body;
        var count;
        var trueCount;
        var falseCount;
        var Procent;
        var clientTop = "";
        Clientlogin = msg.slice(0,i);

        i++;
        while (msg[i]!=" ") {
            clientTop += msg[i];
            i++;
        }

        document.getElementById("Top").innerText = "Ваше место в топе: "+clientTop;

        //Задание 1: Правильно: ; Неправильно ; Всего решено: ; Процент правильного выполнения: .

        while (h<=27) {
            body = "Задание "+h+": Правильно: ";
            i++;
            count = "";
            while (msg[i]!="_") {
                count += msg[i];
                i++;
            }
            i++;
            trueCount = Number(count);
            body += count;
            count = "";
            body += "; Неправильно: ";
            while (msg[i]!=" ") {
                count += msg[i];
                i++;
            }
            falseCount = Number(count);
            body += count;
            count = "";
            if (trueCount+falseCount == 0) {
                Procent = 0;
            } else {
                Procent = Math.round((trueCount/(trueCount+falseCount))*100);
            }
            body += "; Всего решено: "+(trueCount+falseCount)+"; Процент правильного выполнения: "+Procent+"%.";
            document.getElementById(h+"t").innerText = body;
            h++;
        }
        console.log("Вход по ip успешен");
        document.getElementById("input").style = "display:none";
        document.getElementById("login").style = "display:block";
        document.getElementById("out").style = "display:block";
        var lenWord = Math.floor(210/Clientlogin.length);
        document.getElementById("loginCenter").innerText = Clientlogin;
        document.getElementById("loginCenter").style = "font-size: +"+lenWord+"px;";
        document.getElementById("login").innerText = Clientlogin;
        document.getElementById("login").style = "font-size: +"+lenWord+"px;";

        socket.close();
        console.log("Закрытие соединения");
    } else {
        document.location.href = "http://94.50.161.247:8082/Informatics";
    }
};

socket.onerror = function (error) {
    console.log("Ошибка " + error.message);
};

function OutClick () {
    var socket = null;
    socket = new WebSocket("ws://94.50.161.247:8082");

    socket.onopen = function () {
        console.log("Соединение установлено.");
        
        socket.send("OutLogin");
        console.log("Отправка");
        socket.close();
        console.log("Закрытие соединения");
        log = false;
        Clientlogin = "";
            
    };

    socket.onclose = function (event) {
        if (event.wasClean) {
            console.log('Соединение закрыто чисто');
        } else {
            console.log('Обрыв соединения');
        }
        console.log('Код: ' + event.code + ' причина: ' + event.reason);
    };

    socket.onmessage = function (event) {
        console.log("Получены данные " + event.data);
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
    };

    document.location.href = "http://94.50.161.247:8082/Informatics";

}

function Reset (num) {
    var socket = null;
    socket = new WebSocket("ws://94.50.161.247:8082");

    socket.onopen = function () {
        console.log("Соединение установлено.");
        
        socket.send("clearNum: "+num+" "+Clientlogin+" ");
        document.getElementById(num+"t").innerText = "Задание "+num+": Правильно: 0; Неправильно 0; Всего решено: 0; Процент правильного выполнения: 0%.";
        console.log("Отправка");
        socket.close();
        console.log("Закрытие соединения");
            
    };

    socket.onclose = function (event) {
        if (event.wasClean) {
            console.log('Соединение закрыто чисто');
        } else {
            console.log('Обрыв соединения');
        }
        console.log('Код: ' + event.code + ' причина: ' + event.reason);
    };

    socket.onmessage = function (event) {
        console.log("Получены данные " + event.data);
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
    };
}

function ResetPassword () {
    var socket = null;
    var connection = false;
    socket = new WebSocket("ws://94.50.161.247:8082");

    socket.onopen = function () {
        console.log("Соединение установлено.");
        pasold = document.getElementById('1p').value;
        pasnew = document.getElementById('2p').value;
        if (pasold.length > 3 && pasnew.length > 3) {
            if (pasold.length < 21 && pasnew.length < 21) {
                if (!pasold.includes(' ') && !pasnew.includes(' ')) {
                    var msg = "OldPas: "+pasold+" "+pasnew+" "+Clientlogin+" ";
                    socket.send(msg);
                    console.log("Отправка");
                } else {
                    alert("Пароли не должны содержать пробелов");
                    connection = true;
                    socket.close();
                    console.log("Закрытие соединения");
                }
            } else {
                alert("Длинна пароля не должна превышать 20 символов");
                connection = true;
                socket.close();
                console.log("Закрытие соединения");
            }
        } else {
            alert("Длинна пароля должна быть больше 3 символов");
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
        if (event.data == "resetTrue") {
            alert("Пароль сменён");
            document.getElementById('1p').value = "";
            document.getElementById('2p').value = "";
        } else if (event.data == "paserror") {
            alert("Неверный пароль");
        }
        socket.close();
        console.log("Закрытие соединения");
        connection = true;
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
    };
}