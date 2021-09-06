var time = false;
var lastnumber = 1;

var answers = new Array(10);

function Generate (numberG) {
if (numberG == 1) {
    var A = Math.round(Math.random()*20+10);
    var B = Math.round(Math.random()*35+15);
    var C = Math.round(Math.random()*9+1);
    document.getElementById(numberG+"A").innerText = A;
    document.getElementById(numberG+"B").innerText = B;
    document.getElementById(numberG+"C").innerText = C;
    answers[numberG]=Math.round(A*1000*B/8*C*60*4/1024/1024/10)*10;
} else {
    var A = Math.round(Math.random()*30000+10000);
    var B = Math.round(Math.random()*1000+4);
    var C = Math.round(Math.random()*2000+500);
    var D = Math.round(Math.random()*1500+700);
    document.getElementById(numberG+"A").innerText = A;
    document.getElementById(numberG+"B").innerText = B;
    document.getElementById(numberG+"C").innerText = C;
    document.getElementById(numberG+"D").innerText = D;
    answers[numberG]=Math.round(C*D*Math.ceil(Math.log2(B))/A);
}
document.getElementById(numberG+'p').style="background-color: #FFFFFF;";
document.getElementById(numberG+"p").value = "";
}

function White() {
    document.getElementById(lastnumber+'p').style="background-color: #FFFFFF;";
    time = false;
}

function CheckAnswer (number) {
    if (document.getElementById(number+'p').value == answers[number]) {
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
}

function Answer (numberA) {
    if (time) {
        clearTimeout(timeColor);
        time = false;
    }
    document.getElementById(numberA+'p').style="background-color: #4CAF50;";
    document.getElementById(numberA+'p').value = answers[numberA];
}