var objects = new Array(20);

////////////////////////////////////////////////////////////////////

let obj1 = new Object ();
obj1.function = "Easy";
obj1.answer = "10";
obj1.text = "Напишите наименьшее целое число x, для которого истинно высказывание: \n\n НЕ (X < 9) И НЕ (X нечётное).";
objects[1] = obj1;

let obj2 = new Object ();
obj2.function = "Easy";
obj2.answer = "10";
obj2.text = "Напишите наименьшее целое число x, для которого истинно высказывание: \n\n НЕ (X <= 8) И НЕ (X >= 15) И (X чётное).";
objects[2] = obj2;

let obj3 = new Object ();
obj3.function = "Easy";
obj3.answer = "102";
obj3.text = "Напишите наименьшее натуральное трёхзначное число, для которого ИСТИННО высказывание: \n\n НЕ (Число нечётное) И (Число кратно 3).";
objects[3] = obj3;

let obj4 = new Object ();
obj4.function = "Easy";
obj4.answer = "10";
obj4.text = "Напишите наибольшее целое число x, для которого истинно высказывание: \n\n НЕ (X <= 6) И НЕ (X >= 11).";
objects[4] = obj4;

let obj5 = new Object ();
obj5.function = "Easy";
obj5.answer = "4";
obj5.text = "Напишите наибольшее целое число x, для которого истинно высказывание: \n\n НЕ (X нечётное) И НЕ (X >= 6).";
objects[5] = obj5;

let obj6 = new Object ();
obj6.function = "Easy";
obj6.answer = "98";
obj6.text = "Напишите наибольшее двузначное число, для которого истинно высказывание: \n\n (первая цифра нечётная) И НЕ (число делится на 3).";
objects[6] = obj6;

///////////////////////////////////////////////

let obj7 = new Object ();
obj7.function = "Easy";
obj7.answer = "31";
obj7.text = "Каждое из логических выражений F и G содержит 5 переменных. В таблицах истинности выражений F и G есть ровно 5 одинаковых строк, причём ровно в 4 из них в столбце значений стоит 1. \n\n Сколько строк таблицы истинности для выражения F ∨ G содержит 1 в столбце значений?";
objects[7] = obj7;

let obj8 = new Object ();
obj8.function = "Hard";
obj8.answer = "zyx";
obj8.text1 = "Логическая функция F задаётся выражением (¬z)∧x ∨ x∧y. \n\n Определите, какому столбцу таблицы истинности функции F соответствует каждая из переменных x, y, z.";
obj8.text2 = "В ответе напишите буквы x, y, z в том порядке, в котором идут соответствующие им столбцы (сначала – буква, соответствующая 1-му столбцу; затем – буква, соответствующая 2-му столбцу; затем – буква, соответствующая 3-му столбцу). Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно. \n\n Пример. Пусть задано выражение x → y, зависящее от двух переменных x и y, и таблица истинности:";
obj8.text3 = "Тогда 1-му столбцу соответствует переменная y, а 2-му столбцу соответствует переменная x. В ответе нужно написать: yx.";
obj8.img1 = "exImg5";
obj8.img2 = "exImg6";
objects[8] = obj8;

let obj9 = new Object ();
obj9.function = "Hard";
obj9.answer = "xywz";
obj9.text1 = "Логическая функция F задаётся выражением x ∧ ¬y ∧ (¬z ∨ w). На рисунке приведён фрагмент таблицы истинности функции F, содержащий все наборы аргументов, при которых функция F истинна. Определите, какому столбцу таблицы истинности функции F соответствует каждая из переменных w, x, y, z.";
obj9.text2 = "В ответе напишите буквы w, x, y, z в том порядке, в котором идут соответствующие им столбцы (сначала — буква, соответствующая первому столбцу; затем — буква, соответствующая второму столбцу, и т. д.) Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно. \n\n Пример. Если бы функция была задана выражением ¬x ∨ y, зависящим от двух переменных: x и y, и был приведён фрагмент её таблицы истинности, содержащий все наборы аргументов, при которых функция F истинна.";
obj9.text3 = "Тогда первому столбцу соответствовала бы переменная y, а второму столбцу — переменная x. В ответе следовало бы написать: yx.";
obj9.img1 = "exImg7";
obj9.img2 = "exImg8";
objects[9] = obj9;

let obj10 = new Object ();
obj10.function = "Hard";
obj10.answer = "zwxy";
obj10.text1 = "Логическая функция F задаётся выражением ¬w ∧ z ∧ (y → x). \n\n На рисунке приведён фрагмент таблицы истинности функции F, содержащий все наборы аргументов, при которых функция F истинна. \n\n Определите, какому столбцу таблицы истинности функции F соответствует каждая из переменных w, x, y, z.";
obj10.text2 = "В ответе напишите буквы w, x, y, z в том порядке, в котором идут соответствующие им столбцы (сначала – буква, соответствующая первому столбцу; затем – буква, соответствующая второму столбцу, и т.д.) Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно. \n\n Пример. Пусть задано выражение x → y, зависящее от двух переменных x и y, и таблица истинности:";
obj10.text3 = "Тогда первому столбцу соответствует переменная y, а второму столбцу соответствует переменная x. В ответе нужно написать: yx.";
obj10.img1 = "exImg9";
obj10.img2 = "exImg10";
objects[10] = obj10;

/////////////////////////////////////////////////////////////

let obj11 = new Object ();
obj11.function = "Hard";
obj11.answer = "ywzx";
obj11.text1 = "Логическая функция F задаётся выражением ((x → y ) ∧ (y → w)) ∨ (z ≡ ( x ∨ y)). \n\n Дан частично заполненный фрагмент, содержащий неповторяющиеся строки таблицы истинности функции F. \n\n Определите, какому столбцу таблицы истинности соответствует каждая из переменных x, y, z, w.";
obj11.text2 = "В ответе напишите буквы x, y, z, w в том порядке, в котором идут соответствующие им столбцы (сначала — буква, соответствующая первому столбцу; затем — буква, соответствующая второму столбцу, и т. д.). Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно. \n\n Пример. Пусть задано выражение x → y, зависящее от двух переменных x и y, и фрагмент таблицы истинности:";
obj11.text3 = "Тогда первому столбцу соответствует переменная y, а второму столбцу соответствует переменная x. В ответе нужно написать: yx.";
obj11.img1 = "exImg1";
obj11.img2 = "exImg2";
objects[11] = obj11;

let obj12 = new Object ();
obj12.function = "Hard";
obj12.answer = "zyxw";
obj12.text1 = "Логическая функция F задаётся выражением ((x → y ) ≡ (z → w)) ∨ (x ∧ w). \n\n Дан частично заполненный фрагмент, содержащий неповторяющиеся строки таблицы истинности функции F. \n\n Определите, какому столбцу таблицы истинности соответствует каждая из переменных x, y, z, w.";
obj12.text2 = "В ответе напишите буквы x, y, z, w в том порядке, в котором идут соответствующие им столбцы (сначала — буква, соответствующая первому столбцу; затем — буква, соответствующая второму столбцу, и т. д.). Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно. \n\n Пример. Пусть задано выражение x → y, зависящее от двух переменных x и y, и фрагмент таблицы истинности:";
obj12.text3 = "Тогда первому столбцу соответствует переменная y, а второму столбцу соответствует переменная x. В ответе нужно написать: yx.";
obj12.img1 = "exImg3";
obj12.img2 = "exImg4";
objects[12] = obj12;

let obj13 = new Object ();
obj13.function = "Hard";
obj13.answer = "zxy";
obj13.text1 = "Логическая функция F задаётся выражением: (¬x ∧ y ∧ z) ∨ (¬x ∧ ¬y ∧ z) ∨ (¬x ∧ ¬y ∧ ¬z). \n\n На рисунке приведён фрагмент таблицы истинности функции F, содержащий все наборы аргументов, при которых функция F истинна. \n\n Определите, какому столбцу таблицы истинности функции F соответствует каждая из переменных x, y, z.";
obj13.text2 = "В ответе напишите буквы x, y, z в том порядке, в котором идут соответствующие им столбцы (сначала – буква, соответствующая первому столбцу, затем – буква, соответствующая второму столбцу, и т. д.) Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно. \n\n Пример. Пусть задано выражение x → y, зависящее от двух переменных x и y, и таблица истинности:";
obj13.text3 = "Тогда 1-му столбцу соответствует переменная y, а 2-му столбцу соответствует переменная x. В ответе нужно написать: yx.";
obj13.img1 = "exImg11";
obj13.img2 = "exImg12";
objects[13] = obj13;

let obj14 = new Object ();
obj14.function = "Easy";
obj14.answer = "127";
obj14.text = "Каждое из логических выражений F и G содержит 7 переменных. В таблицах истинности выражений F и G есть ровно 7 одинаковых строк, причём ровно в 6 из них в столбце значений стоит 0. \n\n Сколько строк таблицы истинности для выражения F ∧ G содержит 0 в столбце значений?";
objects[14] = obj14;

////////////////////////////////////////////////////////////

var Time = 0;
function Timer () {
    timer = setTimeout(Timer,1000);
    Time++;
}
Timer();

var level = 1;
var task = new Array(3);
var levelup = new Array(3);

var time = false;
var lastnumber = 1;

function White() {
    document.getElementById(lastnumber+'p').style="background-color: #FFFFFF;";
    time = false;
}

function Replace (start, end) {
    var A = Math.round(Math.random()*(end-start)+start);
    var B = Math.round(Math.random()*(end-start)+start);
    while (B==A) {
        B = Math.round(Math.random()*(end-start)+start);
    }
    var C = Math.round(Math.random()*(end-start)+start);
    while ((C==A) | (C==B)) {
        C = Math.round(Math.random()*(end-start)+start);
    }

    task[1] = A;
    task[2] = B;
    task[3] = C;

    var i = 1;
    while (i<=3) {
        document.getElementById(i+'p').style="background-color: #FFFFFF;";
        document.getElementById(i+'p').value="";
        if (objects[task[i]].function == "Easy") {
            document.getElementById("h"+i).style = "display:none";
            document.getElementById("e"+i).style = "display:block";
            document.getElementById(i).innerText = objects[task[i]].text;
        } else {
            document.getElementById("e"+i).style = "display:none";
            document.getElementById("h"+i).style = "display:block";
            document.getElementById("h"+i+"_1").innerText = objects[task[i]].text1;
            document.getElementById("h"+i+"_2").innerText = objects[task[i]].text2;
            document.getElementById("h"+i+"_3").innerText = objects[task[i]].text3;
            document.getElementById("h"+i+"_i1").src = objects[task[i]].img1;
            document.getElementById("h"+i+"_i2").src = objects[task[i]].img2;
        }
        i++;
    }
}

function Answer (number) {
    if (objects[task[number]].answer==document.getElementById(number+'p').value) {
        levelup[number]=true;
        if (time) {
            clearTimeout(timeColor);
            time = false;
        }
        document.getElementById(number+'p').style="background-color: #4CAF50;";
    } else {
        document.getElementById(number+'p').style="background-color: #f44336;";
        if (!time) {
            timeColor = setTimeout(White, 3000);
            lastnumber = number;
            time = true;
        }
    }

    if ((levelup[1] == true) && (levelup[2] == true) && (levelup[3] == true)) {
        if (level == 1) {
            document.getElementById("level").innerText = "Уровень: Средне";
            levelup = {};
            level++;
            Replace(7,10);
        } else if (level == 2) {
            document.getElementById("level").innerText = "Уровень: Сложно";
            levelup = {};
            level++;
            Replace(11,14)
        } else {
            clearTimeout(timer);
            alert("Вы выполнили упражнение за "+Math.round(Time/60)+" минут(ы). Не останавливаетесь на достигнутом, страйтесь совершенствовать результат!");
            document.location.href = "http://94.50.161.247:8082/Exercise-2";
        }
    }
}

function Download () {
    document.getElementById("h1").style = "display:none";
    document.getElementById("h2").style = "display:none";
    document.getElementById("h3").style = "display:none";

    var A = Math.round(Math.random()*5+1);
    var B = Math.round(Math.random()*5+1);
    while (B==A) {
        B = Math.round(Math.random()*5+1);
    }
    var C = Math.round(Math.random()*5+1);
    while ((C==A) | (C==B)) {
        C = Math.round(Math.random()*5+1);
    }

    task[1] = A;
    task[2] = B;
    task[3] = C;

    document.getElementById("1").innerText = objects[A].text;
    document.getElementById("2").innerText = objects[B].text;
    document.getElementById("3").innerText = objects[C].text;
}

