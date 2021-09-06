var log = false;
var Clientlogin;
var socket = null;
socket = new WebSocket("ws://94.50.161.247:8082");

socket.onopen = function () {
    console.log("Соединение установлено.");
    socket.send("loginIp");
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
    console.log("Получены данные " + event.data);
    if ((event.data != "filenotopen") && (event.data != "filejsonerror") && (event.data != "ipnotfound")) {
        log = true;
        Clientlogin = event.data;
        console.log("Вход по ip успешен");
        document.getElementById("input").style = "display:none";
        document.getElementById("login").style = "display:block";
        document.getElementById("out").style = "display:block";
        document.getElementById("prof").style = "display:block";
        var lenWord = Math.floor(210/Clientlogin.length);
        /*var newLogin = Clientlogin;
        if (Clientlogin.length > 10) {
            newLogin = Clientlogin.slice(0,Math.ceil(Clientlogin.length/2))+"\n"+Clientlogin.slice(Math.ceil(Clientlogin.length/2));
        }*/
        document.getElementById("login").innerText = Clientlogin;
        document.getElementById("login").style = "font-size: +"+lenWord+"px;";
        socket.close();
        console.log("Закрытие соединения");
    } else {
        console.log("Вход по ip не выполнен: "+event.data);
        document.getElementById("input").style = "display:block";
        document.getElementById("input").style = "valign='center'";
        document.getElementById("login").style = "display:none";
        document.getElementById("out").style = "display:none";
        document.getElementById("prof").style = "display:none";
        socket.close();
        console.log("Закрытие соединения");
    }
};

socket.onerror = function (error) {
    console.log("Ошибка " + error.message);
};

function SendClick() {
    var socket = null;
    var connection = false;
    socket = new WebSocket("ws://94.50.161.247:8082");

    socket.onopen = function () {
        console.log("Соединение установлено.");
        var login = document.getElementById("Loginin").value;
        var password = document.getElementById("Passwordin").value;
        if (login.length > 3 && password.length > 3) {
            if (login.length < 21 && password.length < 21) {
                if (!login.includes(' ') && !password.includes(' ')) {
                    var msg = "Ilogin: " + login + " Password: " + password + " ";
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
        if ((event.data != "filenotopen") && (event.data != "filejsonerror") && (event.data != "logerror") && (event.data != "paserror")) {
            socket.close();
            Clientlogin = event.data;
            console.log("Закрытие соединения");
            connection = true;
            document.getElementById("input").style = "display:none";
            document.getElementById("login").style = "display:block";
            document.getElementById("out").style = "display:block";
            document.getElementById("prof").style = "display:block";
            document.getElementById("login").innerText = Clientlogin;
            var lenWord = Math.floor(210/Clientlogin.length);
            document.getElementById("login").style = "font-size: +"+lenWord+"px;";
            log = true;
        } else if (event.data == "logerror") {
            connection = true;
            socket.close();
            console.log("Закрытие соединения");
            alert("Данного логина не существует");
        } else if (event.data == "paserror") {
            connection = true;
            socket.close();
            console.log("Закрытие соединения");
            alert("Неверный пароль");
        }
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
    };
}

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

    document.getElementById("input").style = "display:block";
    document.getElementById("input").style = "valign='center'";
    document.getElementById("login").style = "display:none";
    document.getElementById("out").style = "display:none";
    document.getElementById("prof").style = "display:none";
}

function Profile () {
    document.location.href = "http://94.50.161.247:8082/Profile";
}

/////////////////////////////////////////

setTimeout(Top, 50);

function Top () {

    var socket = null;
    socket = new WebSocket("ws://94.50.161.247:8082");

    socket.onopen = function () {
        console.log("Соединение установлено.");
        socket.send("Top");
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
        console.log("Получены данные " + event.data);
        if (event.data != "filenotopen") {
            var req = event.data;
            var clienTop = 1; 
            var i = 0;
            var clientCount = 0;
            var l = "";
            var t = "";
            var f = "";
            var trueAnswer = 0;

            while (req[i]!=" ") {
                l += req[i];
                i++;
            }

            clientCount=Number(l);
            l = "";
            i++;

            while (clienTop <= clientCount) {
                while (req[i]!=" ") {
                    l += req[i];
                    i++;
                }

                i++;
                while (req[i]!=" ") {
                    t += req[i];
                    i++;
                }

                i++;
                while (req[i]!=" ") {
                    f += req[i];
                    i++;
                }

                document.getElementById("l"+clienTop).innerText = l;
                if ((Number(t)+Number(f))==0) {
                    trueAnswer = 0;
                } else {
                    trueAnswer = Math.round((Number(t)/(Number(t)+Number(f)))*100);
                }
                document.getElementById("lt"+clienTop).innerText = Number(t)+Number(f)+" заданий; "+trueAnswer+"% верно.";

                l="";
                t="";
                f="";

                clienTop++;

                i++;
            }

            while (clienTop <= 10) {
                document.getElementById("l"+clienTop).innerText = "Пусто";
                document.getElementById("lt"+clienTop).innerText = "0 заданий; 0% верно.";

                clienTop++;
            }
        }
        socket.close();
        console.log("Закрытие соединения");
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
    };
}