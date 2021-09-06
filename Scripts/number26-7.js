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

//////////////////////////
var time = false;

function TestAnswer (nid) {
    var socket = null;
    socket = new WebSocket("ws://94.50.161.247:8082");

    socket.onopen = function () {
        console.log("Соединение установлено.");
        var strlog;
        if (log) {
            strlog=" 1 ";
        } else {
            strlog=" 0 ";
        }
        nameText = document.getElementById("name").innerText;
        if (nameText.length == 28) {
            num = nameText[27];
        } else {
            num = nameText[27]+nameText[28];
        }
        socket.send("Number2: "+num+" "+nid+" "+document.getElementById("1p").value+" "+document.getElementById("2p").value+strlog);
    };

    socket.onclose = function (event) {
        if (event.wasClean) {
            console.log('Соединение закрыто чисто');
        } else {
            console.log('Обрыв соединения');
            console.log('Код: ' + event.code + ' причина: ' + event.reason);
        }
    };

    socket.onmessage = function (event) {
        console.log("Получены данные " + event.data);
        if (event.data=="True") {
            if (time) {
                clearTimeout(timeColor);
                time = false;
            }
            document.getElementById("1p").style="background-color: #4CAF50;";
            document.getElementById("2p").style="background-color: #4CAF50;";
        } else {
            document.getElementById("1p").style="background-color: #f44336;";
            document.getElementById("2p").style="background-color: #f44336;";
            if (!time) {
                timeColor = setTimeout(White, 3000);
                time = true;
            }
        }
        socket.close();
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
        socket.close();
    };

    function White() {
        document.getElementById("1p").style="background-color: #FFFFFF;";
        document.getElementById("2p").style="background-color: #FFFFFF;";
        time = false;
    }
}

function Answer (nod) {
    var socket = null;
    socket = new WebSocket("ws://94.50.161.247:8082");

    if (time) {
        clearTimeout(timeColor);
        time = false;
    }

    socket.onopen = function () {
        console.log("Соединение установлено.");
        nameText = document.getElementById("name").innerText;
        if (nameText.length == 28) {
            num = nameText[27];
        } else {
            num = nameText[27]+nameText[28];
        }
        socket.send("Number2A: "+num+" "+nod+" ");
    };

    socket.onclose = function (event) {
        if (event.wasClean) {
            console.log('Соединение закрыто чисто');
        } else {
            console.log('Обрыв соединения');
            console.log('Код: ' + event.code + ' причина: ' + event.reason);
        }
    };

    socket.onmessage = function (event) {
        console.log("Получены данные " + event.data);
        var req = event.data;
        var write = "";
        var b = 0;
        while (req[b]!=" ") {
            write += req[b];
            b++;
        }
        b++;
        document.getElementById("1p").value=write;
        document.getElementById("1p").style="background-color: #4CAF50;";

        write = "";
        while (req[b]!=" ") {
            write += req[b];
            b++;
        }
        document.getElementById("2p").value=write;
        document.getElementById("2p").style="background-color: #4CAF50;";
        socket.close();
    };

    socket.onerror = function (error) {
        console.log("Ошибка " + error.message);
        socket.close();
    };
}