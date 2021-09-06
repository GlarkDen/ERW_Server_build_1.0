#include <iostream>
#include <sstream>
#include <fstream>
#include <string> // работа со строками
#include <semaphore.h> // для потоков
#include <pthread.h> // потоки
#include <json.hpp> // базы данных
#include <ctime> // время

using json = nlohmann::json;

#include <sys/stat.h>
#include <fcntl.h> 
#include <time.h>
#include <signal.h>

// стандартные библиотеки
#include <iostream>
#include <fstream>
#include <thread>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h> 
#include <signal.h>
#include <chrono>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

const char response_403 [] = // Ответ клиенту - ошибка
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>403</title>"
"<style>body { background-color: #312f2f }"
"h1 { font-size:4cm; text-align: center; color: #666;}</style></head>"
"<body><h1>403</h1></body></html>\r\n";

const char response [] = // Ответ клиенту - заголовок 
"HTTP/1.1 200 OK\r\n"
"Version: HTTP/1.1\r\n"
"Content-Type: text/html; charset=utf-8\r\n"
"\r\n";

//Web Socket
////////////////////////////////////////////////////////////////////////////////////////

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

#if BYTE_ORDER == LITTLE_ENDIAN
#define blk0(i) (block->l[i] = (rol(block->l[i],24)&0xFF00FF00) \
    |(rol(block->l[i],8)&0x00FF00FF))

#elif BYTE_ORDER == BIG_ENDIAN
#define blk0(i) block->l[i]

#else
#error "Endianness not defined!"
#endif

#define blk(i) (block->l[i&15] = rol(block->l[(i+13)&15]^block->l[(i+8)&15] \
    ^block->l[(i+2)&15]^block->l[i&15],1))

#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);

#define WS_TEXT_FRAME 0x01
#define WS_PING_FRAME 0x09
#define WS_PONG_FRAME 0x0A
#define WS_CLOSING_FRAME 0x08

char GUIDKey[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"; //36

char response_ws[] = "HTTP/1.1 101 Switching Protocols\r\n"
"Upgrade: websocket\r\n"
"Connection: Upgrade\r\n"
"Sec-WebSocket-Accept: "; //97

unsigned char charset[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

#define BUFSIZE 1024
#define FILESTR 32
#define ALLARRAY 64
#define SHA_DIGEST_LENGTH 20
#define SW_BUF 65552

//char patch_to_dir[ALLARRAY] = {0,};
//char fpfile[ALLARRAY] = {0,};
//char buffer[BUFSIZE] = {0,};
//int client_fd, count_warning_log =0;
//struct stat stat_buf;
sem_t sem;

typedef struct
 {
   uint32_t state[5];
   uint32_t count[2];
   unsigned char buffer[64];
 } SHA1_CTX;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int clientCount = 0;
bool threadControl = false;
bool logs;
int client_count;
unsigned int timeout;
std::string ip;

std::string jsonWrite (std::string path, std::string write, std::string parameter, uint8_t type) {

json File;
std::ifstream Namer(path, std::ios::in | std::ios::binary);
    if (!Namer.is_open())
    {
      return "File not open\n";
    }
    try
    {
      Namer >> File;
    }
    catch (nlohmann::json::exception)
    {
      Namer.close();
      return "File json error\n";
    }

    Namer.close();

    if (File.find(parameter) != File.end())
    {
      if (type == 1) {
        int rewrite;
        try {
          rewrite = atoi(write.c_str());
        } catch (std::invalid_argument) {
          return "Error convert type\n";
        }
        File[parameter] = rewrite;
      } else if (type == 2) {
        bool rewrite;
        if (write.find("true") != std::string::npos) {
          rewrite = true;
        } else if (write.find("false") != std::string::npos) {
          rewrite = false;
        } else {
          return "Error convert type\n";
        }
        File[parameter] = rewrite;
      } else if (type == 0) {
        File[parameter] = write;
      }
      
      std::ofstream Namew;
      Namew.open(path);
      if (Namew.is_open())
      {
        Namew << File;
      }
      Namew.close();
    }
    else
    {
      return "Parameter not find\n";
    }

    return "true";

}

/////////////////////////////////////////////// SHA1 /////////////////////////////////////////////////////////////
void SHA1Transform( uint32_t state[5], const unsigned char buffer[64])

 {
    uint32_t a, b, c, d, e;
    typedef union
     {
       unsigned char c[64];
       uint32_t l[16];
     } CHAR64LONG16;

    CHAR64LONG16 block[1];    
    memcpy(block, buffer, 64);

    a = state[0]; b = state[1]; c = state[2]; d = state[3]; e = state[4];

    R0(a, b, c, d, e, 0); R0(e, a, b, c, d, 1); R0(d, e, a, b, c, 2); R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4); R0(a, b, c, d, e, 5); R0(e, a, b, c, d, 6); R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8); R0(b, c, d, e, a, 9); R0(a, b, c, d, e, 10); R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12); R0(c, d, e, a, b, 13); R0(b, c, d, e, a, 14); R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16); R1(d, e, a, b, c, 17); R1(c, d, e, a, b, 18); R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20); R2(e, a, b, c, d, 21); R2(d, e, a, b, c, 22); R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24); R2(a, b, c, d, e, 25); R2(e, a, b, c, d, 26); R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28); R2(b, c, d, e, a, 29); R2(a, b, c, d, e, 30); R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32); R2(c, d, e, a, b, 33); R2(b, c, d, e, a, 34); R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36); R2(d, e, a, b, c, 37); R2(c, d, e, a, b, 38); R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40); R3(e, a, b, c, d, 41); R3(d, e, a, b, c, 42); R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44); R3(a, b, c, d, e, 45); R3(e, a, b, c, d, 46); R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48); R3(b, c, d, e, a, 49); R3(a, b, c, d, e, 50); R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52); R3(c, d, e, a, b, 53); R3(b, c, d, e, a, 54); R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56); R3(d, e, a, b, c, 57); R3(c, d, e, a, b, 58); R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60); R4(e, a, b, c, d, 61); R4(d, e, a, b, c, 62); R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64); R4(a, b, c, d, e, 65); R4(e, a, b, c, d, 66); R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68); R4(b, c, d, e, a, 69); R4(a, b, c, d, e, 70); R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72); R4(c, d, e, a, b, 73); R4(b, c, d, e, a, 74); R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76); R4(d, e, a, b, c, 77); R4(c, d, e, a, b, 78); R4(b, c, d, e, a, 79);

    state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;
    a = b = c = d = e = 0;
    memset(block, 0, sizeof(block));
 }

void SHA1Init( SHA1_CTX * context)
 {
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
 }

void SHA1Update( SHA1_CTX * context, const unsigned char *data, uint32_t len)
 {
    uint32_t i;
    uint32_t j;

    j = context->count[0];
    if ((context->count[0] += len << 3) < j) context->count[1]++;

    context->count[1] += (len >> 29);
    j = (j >> 3) & 63;
    if((j + len) > 63)
     {
       memcpy(&context->buffer[j], data, (i = 64 - j));

       SHA1Transform(context->state, context->buffer);
       for(; i + 63 < len; i += 64)
        {
          SHA1Transform(context->state, &data[i]);
        }

       j = 0;
     }

    else i = 0;

    memcpy(&context->buffer[j], &data[i], len - i);
 }

void SHA1Final( unsigned char digest[20], SHA1_CTX * context)
 {
    unsigned i;
    unsigned char c, finalcount[8];

    for(i = 0; i < 8; i++)
     {
       finalcount[i] = (unsigned char) ((context->count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8)) & 255);     
     }

    c = 0200;
    SHA1Update(context, &c, 1);

    while((context->count[0] & 504) != 448)
     {
       c = 0000;
       SHA1Update(context, &c, 1);
     }

    SHA1Update(context, finalcount, 8); 

    for(i = 0; i < 20; i++)
     {
       digest[i] = (unsigned char) ((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
     }

    memset(context, 0, sizeof(*context));
    memset(&finalcount, 0, sizeof(finalcount));
 }

void SHA1(unsigned char *hash_out, const char *str, unsigned int len)
 {
    SHA1_CTX ctx;
    unsigned int ii;
    SHA1Init(&ctx);
    for (ii=0; ii<len; ii+=1) SHA1Update(&ctx, (const unsigned char*)str + ii, 1);
    SHA1Final((unsigned char *)hash_out, &ctx);
    hash_out[20] = 0;
 }

int base64_encode(unsigned char sha_key_in[], unsigned char base64_key_out[], int len) // записывает готовый ответ клиенту
 {
   int idx, idx2, blks, left_over;

   blks = (len / 3) * 3;
   for(idx=0, idx2=0; idx < blks; idx += 3, idx2 += 4) 
    {
      base64_key_out[idx2] = charset[sha_key_in[idx] >> 2];
      base64_key_out[idx2+1] = charset[((sha_key_in[idx] & 0x03) << 4) + (sha_key_in[idx+1] >> 4)];
      base64_key_out[idx2+2] = charset[((sha_key_in[idx+1] & 0x0f) << 2) + (sha_key_in[idx+2] >> 6)];
      base64_key_out[idx2+3] = charset[sha_key_in[idx+2] & 0x3F];
    }

   left_over = len % 3;

   if(left_over == 1) 
    {
      base64_key_out[idx2] = charset[sha_key_in[idx] >> 2];
      base64_key_out[idx2+1] = charset[(sha_key_in[idx] & 0x03) << 4];
      base64_key_out[idx2+2] = '=';
      base64_key_out[idx2+3] = '=';
      idx2 += 4;
    }

   else if(left_over == 2) 
    {
      base64_key_out[idx2] = charset[sha_key_in[idx] >> 2];
      base64_key_out[idx2+1] = charset[((sha_key_in[idx] & 0x03) << 4) + (sha_key_in[idx+1] >> 4)];
      base64_key_out[idx2+2] = charset[(sha_key_in[idx+1] & 0x0F) << 2];
      base64_key_out[idx2+3] = '=';
      idx2 += 4;
    }

   base64_key_out[idx2] = 0;
   return(idx2);
 }

// HTTP, для чтения и отправки файлов
int ReadFromFileAll(std::string Path, int result, int client_socket, bool logs, std::string position)
{
    //ServerWork = false;

    std::ifstream file;
    file.open(Path, std::ifstream::binary); // открыть файл с пометкой "для чтения"

    long size;
    char *byf;

    if (!file.is_open()) // проверим, удачно ли открылся файл
    {
        if (logs=true) std::cout << "Error opening file" << std::endl;
        return -1;
    }

    file.seekg(0, std::ios::end); // установим указатель в конец файла (позиция 0 от конца)
    size = file.tellg();          // считаем текущую позицию в файле (она и есть размер файла в байтах)

    file.seekg(atoi(position.c_str()), std::ios::beg); // установим указатель в начало файла (позиция 0 от начала)
    byf = new char[size];    
    file.read(byf, size);         // прочитать все байты в буфер

    int startOfFileType = Path.find_last_of('.');
    std::string fileType = Path.substr(startOfFileType + 1, Path.length());
    std::string type;

    if (fileType == "png") {
      type = "image/png";
    } else if (fileType == "bmp") {
      type = "image/bmp";
    } else if (fileType == "gif") {
      type = "image/gif";
    } else if (fileType == "jpg" || fileType == "jpeg") {
      type = "image/jpeg";
    } else if (fileType == "svg") {
      type = "image/svg+xml";
    } else if (fileType == "ico") {
      type = "image/x-icon";
    } else if (fileType == "css") {
      type = "text/css";
    } else if (fileType == "js") {
      type = "text/javascript";
    } else if (fileType == "wav") {
      type = "audio/wav";
    } else if (fileType == "mkv") {
      type = "video/x-matroska";
    } else if (fileType == "mp4") {
      type = "video/mp4";
    } else {
      type = "text/html";
    }

    std::string headercopy = response;
    std::size_t pos = headercopy.find("text/html");
    if (pos != std::string::npos)
      headercopy.replace(pos, 9, type);

    // Отправляем ответ клиенту с помощью функции send
    result = send(client_socket, headercopy.c_str(), headercopy.length(), 0);
    result = send(client_socket, byf, size, 0);

    return 0;

}

// Список: вопрос - овтвет для Web Socket
std::string answerFunction(int client_fd, std::string req, std::string ipClient)
{

  if (req.find("Login: ") != std::string::npos)
  {

    json inFile;
    std::string login;
    std::string password;
    int i = 7;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    login = req.substr(7, i - 7);

    i += 11;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    password = req.substr(b, i - b);

    //std::cout << "login: " << login << " password: " << password << '\n';

    std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    FNamer.close();

    if (inFile.find(login) != inFile.end())
    {
      return "loglock";
    }
    else
    {
      inFile[login]["password"] = password;
    }

    int numb = 1;

    std::string list = inFile["LoginList"];
    int len = list.length();
    list[len-1] = ' ';
    list += login+".";
    inFile["LoginList"] = list;

    while (numb<=27) {
      inFile[login][std::to_string(numb)]["true"]=0;
      inFile[login][std::to_string(numb)]["false"]=0;
      numb++;
    }

    std::ofstream FNamew;
    FNamew.open("clients.json");
    if (FNamew.is_open())
    {
      FNamew << inFile;
    }
    FNamew.close();

    json inFileIp;
    std::ifstream FNamerip("ip.json", std::ios::in | std::ios::binary);
    if (!FNamerip.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamerip >> inFileIp;
    }
    catch (nlohmann::json::exception)
    {
      FNamerip.close();
      return "filejsonerror";
    }

    FNamerip.close();
    inFileIp[ipClient] = login;

    std::ofstream FNamewip;
    FNamewip.open("ip.json");
    if (FNamewip.is_open())
    {
      FNamewip << inFileIp;
    }
    FNamewip.close();

    return "regtrue";
  }
  else if (req.find("Ilogin: ") != std::string::npos)
  {

    json inFile;
    std::string login;
    std::string password;
    int i = 8;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    login = req.substr(8, i - 8);

    i += 11;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    password = req.substr(b, i - b);

    std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(login) == inFile.end())
    {
      return "logerror";
    }
    else
    {
      if (inFile[login]["password"] == password)
      {
        json inFileIp;
        std::ifstream FNamerip("ip.json", std::ios::in | std::ios::binary);
        if (!FNamerip.is_open())
        {
          return "filenotopen";
        }
        try
        {
          FNamerip >> inFileIp;
        }
        catch (nlohmann::json::exception)
        {
          FNamerip.close();
          return "filejsonerror";
        }

        FNamerip.close();
        inFileIp[ipClient]=login;

        std::ofstream FNamewip;
        FNamewip.open("ip.json");
        if (FNamewip.is_open())
        {
          FNamewip << inFileIp;
        }
        FNamewip.close();

        return login;
      }
      else
      {
        return "paserror";
      }
    }
  }
  else if (req.find("Top") != std::string::npos)
  {

    json inFile;

    std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filenotopen";
    }

    FNamer.close();

    std::string logList = inFile["LoginList"];
    int clientCount = 1;
    int i = 0;

    while (logList[i]!='.') {
      if (logList[i]==' ') {
        clientCount++;
      }
      i++;
    }

    std::string clients[clientCount] = {};
    int clientsTrue[clientCount] = {};
    int clientsFalse[clientCount] = {};

    i = 0;
    int h = 1;
    int count = 0;
    int True = 0;
    int False = 0;
    int Trans = 0;

    while (logList[i]!='.') {
      if (logList[i]!=' ') {
        clients[count]+=logList[i];
      } else {
        while (h<=27) {
          Trans = inFile[clients[count]][std::to_string(h)]["true"];
          True += Trans;
          Trans = inFile[clients[count]][std::to_string(h)]["false"];
          False += Trans;
          h++;
        }
        clientsTrue[count]=True;
        clientsFalse[count]=False;
        True = 0;
        False = 0;
        count++;
        h=1;
      }
      i++;
    }

    bool list = true;
    std::string Klogin;
    i = 1;

    while (list) {
      list = false;
      while (i<clientCount) {
        if (clientsTrue[i-1]<clientsTrue[i]) {
          Klogin = clients[i];
          True = clientsTrue[i];
          False = clientsFalse[i];
          clients[i] = clients[i-1];
          clientsTrue[i] = clientsTrue[i-1];
          clientsFalse[i] = clientsFalse[i-1]; 
          clients[i-1] = Klogin;
          clientsTrue[i-1] = True;
          clientsFalse[i-1] = False; 
          list = true;
        }
        i++;
      }
      i = 1;
    }

    i = 0;

    std::string answer;
    answer += std::to_string(clientCount);
    answer += " ";

    if (clientCount>10) {
      clientCount = 10;
    }

    while (i<clientCount) {
      answer += clients[i]+" ";
      answer += std::to_string(clientsTrue[i]);
      answer += " ";
      answer += std::to_string(clientsFalse[i]);
      answer += " ";
      i++;
    }
      
    return answer;

  }
  else if (req.find("clearNum: ") != std::string::npos)
  {

    json inFile;
    std::string login;
    std::string number;
    int i = 10;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number = req.substr(10, i - 10);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    login = req.substr(b, i - b);

    std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(login) == inFile.end())
    {
      return "loginerror";
    }
    else
    {
      inFile[login][number]["true"]=0;
      inFile[login][number]["false"]=0;
      std::ofstream FNamew;
      FNamew.open("clients.json");
      if (FNamew.is_open())
      {
        FNamew << inFile;
      }
      FNamew.close();
      return "clear";
    }
  }
  else if (req.find("OldPas: ") != std::string::npos)
  {

    json inFile;
    std::string oldpas;
    std::string newpas;
    std::string login;
    int i = 8;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    oldpas = req.substr(8, i - 8);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    newpas = req.substr(b, i - b);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    login = req.substr(b, i - b);

    std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(login) == inFile.end())
    {
      return "loginerror";
    }
    else
    {
      if (inFile[login]["password"]==oldpas) {
        inFile[login]["password"]=newpas;
        std::ofstream FNamew;
        FNamew.open("clients.json");
        if (FNamew.is_open())
        {
          FNamew << inFile;
        }
        FNamew.close();
        return "resetTrue";
      } else {
        return "paserror";
      }
    }
  }
  else if (req.find("loginIp") != std::string::npos)
  {

    json inFile;

    std::ifstream FNamerip("ip.json", std::ios::in | std::ios::binary);
    if (!FNamerip.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamerip >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamerip.close();
      return "filejsonerror";
    }

    if (inFile.find(ipClient) == inFile.end())
    {
      return "ipnotfound";
    }
    else
    {
      return inFile[ipClient];
    }
  }
  else if (req.find("Profile") != std::string::npos)
  {

    json inFile;
    std::string answer;
    std::string login;

    std::ifstream FNamerip("ip.json", std::ios::in | std::ios::binary);
    if (!FNamerip.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamerip >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamerip.close();
      return "filejsonerror";
    }

    if (inFile.find(ipClient) == inFile.end())
    {
      return "ipnotfound";
    }
    else
    {
      login = inFile[ipClient];
    }

    json TaskFile;

    std::ifstream FName("clients.json", std::ios::in | std::ios::binary);
    if (!FName.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FName >> TaskFile;
    }
    catch (nlohmann::json::exception)
    {
      FName.close();
      return "filejsonerror";
    }

    if (TaskFile.find(login) == TaskFile.end())
    {
      return "ipnotfound";
    }
    else
    {

      json inFilePr;

      std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
      if (!FNamer.is_open())
      {
        return "filenotopen";
      }
      try
      {
        FNamer >> inFilePr;
      }
      catch (nlohmann::json::exception)
      {
        FNamer.close();
        return "filenotopen";
      }

      FNamer.close();

      std::string logList = inFilePr["LoginList"];
      int clientCount = 1;
      int i = 0;

      while (logList[i]!='.') {
        if (logList[i]==' ') {
          clientCount++;
        }
        i++;
      }

      std::string clients[clientCount] = {};
      int clientsTrue[clientCount] = {};
      int clientsFalse[clientCount] = {};

      i = 0;
      int h = 1;
      int count = 0;
      int True = 0;
      int False = 0;
      int Trans = 0;

      while (logList[i]!='.') {
        if (logList[i]!=' ') {
          clients[count]+=logList[i];
        } else {
          while (h<=27) {
            Trans = inFilePr[clients[count]][std::to_string(h)]["true"];
            True += Trans;
            Trans = inFilePr[clients[count]][std::to_string(h)]["false"];
            False += Trans;
            h++;
          }
          clientsTrue[count]=True;
          clientsFalse[count]=False;
          True = 0;
          False = 0;
          count++;
          h=1;
        }
        i++;
      }

      bool list = true;
      std::string Klogin;
      i = 1;

      while (list) {
        list = false;
        while (i<clientCount) {
          if (clientsTrue[i-1]<clientsTrue[i]) {
            Klogin = clients[i];
            True = clientsTrue[i];
            False = clientsFalse[i];
            clients[i] = clients[i-1];
            clientsTrue[i] = clientsTrue[i-1];
            clientsFalse[i] = clientsFalse[i-1]; 
            clients[i-1] = Klogin;
            clientsTrue[i-1] = True;
            clientsFalse[i-1] = False; 
            list = true;
          }
          i++;
        }
        i = 1;
      }

      i = 0;

      std::string topNum = "0";

      while (i<clientCount) {
        if (clients[i]==login) {
          topNum = std::to_string(i+1);
          break;
        }
        i++;
      }

      answer += login;
      answer += " ";
      answer += topNum;
      i = 1;
      std::string Sym;
      int Symint;
      while (i<=27) {
        answer += " ";
        Symint = TaskFile[login][std::to_string(i)]["true"];
        Sym = std::to_string(Symint);
        answer += Sym;
        answer += "_";
        Symint = TaskFile[login][std::to_string(i)]["false"];
        Sym = std::to_string(Symint);
        answer += Sym;
        i++;
      }
    }

    return answer;

  }
  else if (req.find("OutLogin") != std::string::npos)
  {

    json inFileIp;
    std::ifstream FNamerip("ip.json", std::ios::in | std::ios::binary);
    if (!FNamerip.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamerip >> inFileIp;
    }
    catch (nlohmann::json::exception)
    {
      FNamerip.close();
      return "filejsonerror";
    }

    FNamerip.close();

    if (inFileIp.find(ipClient) == inFileIp.end()) {
      return "delnotfound";
    } else { 
      inFileIp.erase(ipClient);
    }

    std::ofstream FNamewip;
    FNamewip.open("ip.json");
    if (FNamewip.is_open())
    {
      FNamewip << inFileIp;
    }
    FNamewip.close();

    return "delip";

  }
  else if (req.find("Number: ") != std::string::npos) 
  {

    json inFile;
    if (logs==true) std::cout << req << "\n";
    std::string number1;
    std::string number2;
    std::string answer;
    std::string logining;
    int i = 8;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number1 = req.substr(8, i - 8);

    i += 1;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    number2 = req.substr(b, i - b);

    i += 1;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    answer = req.substr(b, i - b);

    i += 1;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    logining = req.substr(b, i - b);

    if (logs==true) std::cout << "Task: " << number1 << " № " << number2 << " answer: " << answer << " login: " << logining <<"\n";

    std::ifstream FNamer("numbers.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(number1) == inFile.end())
    {
      return "numbernotfind";
    }
    else
    {
      if (logining=="1") {
        json inFilePas;
        json inFileLog;
        std::string login;

        std::ifstream Flog("ip.json", std::ios::in | std::ios::binary);
        if (!Flog.is_open())
        {
          return "filenotopen";
        }
        try
        {
          Flog >> inFileLog;
        }
        catch (nlohmann::json::exception)
        {
          Flog.close();
          return "filejsonerror";
        }

        Flog.close();

        if (inFileLog.find(ipClient) != inFileLog.end())
        {
          login = inFileLog[ipClient];
          std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
          if (!FNamer.is_open())
          {
            return "filenotopen";
          }
          try
          {
            FNamer >> inFilePas;
          }
          catch (nlohmann::json::exception)
          {
            FNamer.close();
            return "filejsonerror";
          }

          FNamer.close();

          if (inFilePas.find(login) != inFilePas.end())
          {
            int jsonType;
            if (answer == inFile[number1][number2]["answer"])
            {
              jsonType = inFilePas[login][number1]["true"];
              inFilePas[login][number1]["true"] = jsonType + 1;
            }
            else
            {
              jsonType = inFilePas[login][number1]["false"];
              inFilePas[login][number1]["false"] = jsonType + 1;
            }
            std::ofstream FNamew;
            FNamew.open("clients.json");
            if (FNamew.is_open())
            {
              FNamew << inFilePas;
            }
            FNamew.close();
          }
        }
      }
      return inFile[number1][number2]["answer"];
    }
  }
  else if (req.find("Number25: ") != std::string::npos) 
  {

    json inFile;
    if (logs==true) std::cout << req << "\n";
    std::string number1;
    std::string number2;
    std::string answer[12];
    std::string logining;
    bool Tanswer = true;
    int i = 10;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number1 = req.substr(10, i - 10);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    number2 = req.substr(b, i - b);

    i++;
    b = i;
    int cicle = 1;
    while (cicle <= 12) {
      while (req[i] != ' ')
      {
        i++;
      }
      if (b!=i) {
        answer[cicle] = req.substr(b, i - b);
      } else {
        answer[cicle] = "0";
      }
      cicle++;
      i++;
      b = i;
    }

    while (req[i] != ' ')
    {
      i++;
    }
    logining = req.substr(b, i - b);

    if (logs==true) std::cout << "Task: " << number1 << " № " << number2 << " answer: " << answer[12] << " login: " << logining <<"\n";

    std::ifstream FNamer("numbers.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(number1) == inFile.end())
    {
      return "numbernotfind";
    }
    else
    {
      if (logining=="1") {
        json inFilePas;
        json inFileLog;
        std::string login;

        std::ifstream Flog("ip.json", std::ios::in | std::ios::binary);
        if (!Flog.is_open())
        {
          return "filenotopen";
        }
        try
        {
          Flog >> inFileLog;
        }
        catch (nlohmann::json::exception)
        {
          Flog.close();
          return "filejsonerror";
        }

        Flog.close();

        if (inFileLog.find(ipClient) != inFileLog.end())
        {
          login = inFileLog[ipClient];
          std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
          if (!FNamer.is_open())
          {
            return "filenotopen";
          }
          try
          {
            FNamer >> inFilePas;
          }
          catch (nlohmann::json::exception)
          {
            FNamer.close();
            return "filejsonerror";
          }

          FNamer.close();

          if (inFilePas.find(login) != inFilePas.end())
          {
            int jsonType;

            cicle = 1;
            while (cicle <= 12) {
              if (answer[cicle] != inFile[number1][std::to_string(cicle)]["answer"]) {
                Tanswer = false;
                break;
              }
              cicle++;
            }

            if (Tanswer)
            {
              jsonType = inFilePas[login][number1]["true"];
              inFilePas[login][number1]["true"] = jsonType + 1;
            }
            else
            {
              jsonType = inFilePas[login][number1]["false"];
              inFilePas[login][number1]["false"] = jsonType + 1;
            }
            std::ofstream FNamew;
            FNamew.open("clients.json");
            if (FNamew.is_open())
            {
              FNamew << inFilePas;
            }
            FNamew.close();
          }
        }
      } else {
        cicle = 1;
          while (cicle <= 12) {
            if (answer[cicle] != inFile[number1][std::to_string(cicle)]["answer"]) {
            Tanswer = false;
            break;
          }
          cicle++;
        }
      }
      if (Tanswer) {
        return "True";
      } else {
        return "False";
      }
    }
  }
  else if (req.find("Number25A: ") != std::string::npos) 
  {

    json inFile;
    if (logs==true) std::cout << req << "\n";
    std::string number1;
    std::string number2;
    int i = 11;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number1 = req.substr(11, i - 11);

    i += 1;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    number2 = req.substr(b, i - b);


    if (logs==true) std::cout << "Task: " << number1 << " № " << number2 << " Answer\n";

    std::ifstream FNamer("numbers.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(number1) == inFile.end())
    {
      return "numbernotfind";
    }
    else
    {
      std::string request;
      int cicle = 1;
      while (cicle <= 12) {
        request += inFile[number1][std::to_string(cicle)]["answer"];
        request += " ";
        cicle++;
      }
      return request;
    }
  }
  else if (req.find("Number2: ") != std::string::npos) 
  {

    json inFile;
    if (logs==true) std::cout << req << "\n";
    std::string number1;
    std::string number2;
    std::string answer1;
    std::string answer2;
    std::string logining;
    bool Tanswer = false;
    int i = 9;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number1 = req.substr(9, i - 9);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    number2 = req.substr(b, i - b);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    answer1 = req.substr(b, i - b);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    answer2 = req.substr(b, i - b);

    i++;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    logining = req.substr(b, i - b);

    if (logs==true) std::cout << "Task: " << number1 << " № " << number2 << " answer26-7: " << answer1 << "  " << answer2 << " login: " << logining <<"\n";

    std::ifstream FNamer("numbers.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(number1) == inFile.end())
    {
      return "numbernotfind";
    }
    else
    {
      if (logining=="1") {
        json inFilePas;
        json inFileLog;
        std::string login;

        std::ifstream Flog("ip.json", std::ios::in | std::ios::binary);
        if (!Flog.is_open())
        {
          return "filenotopen";
        }
        try
        {
          Flog >> inFileLog;
        }
        catch (nlohmann::json::exception)
        {
          Flog.close();
          return "filejsonerror";
        }

        Flog.close();

        if (inFileLog.find(ipClient) != inFileLog.end())
        {
          login = inFileLog[ipClient];
          std::ifstream FNamer("clients.json", std::ios::in | std::ios::binary);
          if (!FNamer.is_open())
          {
            return "filenotopen";
          }
          try
          {
            FNamer >> inFilePas;
          }
          catch (nlohmann::json::exception)
          {
            FNamer.close();
            return "filejsonerror";
          }

          FNamer.close();

          if (inFilePas.find(login) != inFilePas.end())
          {
            int jsonType;

            
            if ((answer1 == inFile[number1]["1"]["answer"]) && (answer2 == inFile[number1]["2"]["answer"])) {
              Tanswer = true;
            }

            if (Tanswer)
            {
              jsonType = inFilePas[login][number1]["true"];
              inFilePas[login][number1]["true"] = jsonType + 1;
            }
            else
            {
              jsonType = inFilePas[login][number1]["false"];
              inFilePas[login][number1]["false"] = jsonType + 1;
            }
            std::ofstream FNamew;
            FNamew.open("clients.json");
            if (FNamew.is_open())
            {
              FNamew << inFilePas;
            }
            FNamew.close();
          }
        }
      } else {
        if ((answer1 == inFile[number1]["1"]["answer"]) && (answer2 == inFile[number1]["2"]["answer"])) {
          Tanswer = true;
        }
      }
      if (Tanswer) {
        return "True";
      } else {
        return "False";
      }
    }
  }
  else if (req.find("Number2A: ") != std::string::npos) 
  {

    json inFile;
    if (logs==true) std::cout << req << "\n";
    std::string number1;
    std::string number2;
    int i = 10;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number1 = req.substr(10, i - 10);

    i += 1;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    number2 = req.substr(b, i - b);


    if (logs==true) std::cout << "Task: " << number1 << " № " << number2 << " Answer26-7\n";

    std::ifstream FNamer("numbers.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(number1) == inFile.end())
    {
      return "numbernotfind";
    }
    else
    {
      std::string request;
      
      request += inFile[number1]["1"]["answer"];
      request += " ";
      request += inFile[number1]["2"]["answer"];
      request += " ";

      return request;
    }
  }
  else if (req.find("NumberA: ") != std::string::npos) 
  {

    json inFile;
    if (logs==true) std::cout << req << "\n";
    std::string number1;
    std::string number2;
    int i = 9;
    int b = 0;
    while (req[i] != ' ')
    {
      i++;
    }
    number1 = req.substr(9, i - 9);

    i += 1;
    b = i;
    while (req[i] != ' ')
    {
      i++;
    }
    number2 = req.substr(b, i - b);

    if (logs==true) std::cout << "TaskA: " << number1 << " № " << number2 << "\n";

    std::ifstream FNamer("numbers.json", std::ios::in | std::ios::binary);
    if (!FNamer.is_open())
    {
      return "filenotopen";
    }
    try
    {
      FNamer >> inFile;
    }
    catch (nlohmann::json::exception)
    {
      FNamer.close();
      return "filejsonerror";
    }

    if (inFile.find(number1) == inFile.end())
    {
      return "numbernotfind";
    }
    else
    {
      return inFile[number1][number2]["answer"];
    }
  } else
  {
    return "I don't understand you";
  }
}

// Для отправки сообщений через Web Socket
void * ws_func(void *client_arg)
{
  std::string clientIp = ip;
  int client_fd = *(int *)client_arg;
  sem_post(&sem);
  char inbuf[SW_BUF] = {
      0,
  };
  char reciv_r[48] = {
      0,
  };

  while (1)
  {
    memset(inbuf, 0, SW_BUF);
    long int rec_b = read(client_fd, inbuf, SW_BUF - 1); // ожидаем данные от клиента и читаем их по приходу

    if (threadControl) {
      pthread_exit(NULL);
    }

    if (rec_b == 0 || rec_b == -1) // если возникла ошибка
    {
      break;
    }

    if (rec_b > 0) // если чё то получили, то ...
    {
      char masking_key[4] = {
          0,
      };                         // сюда положим маску
      char opcode;               // сюда тип фрейма
      unsigned char payload_len; // сюда длину сообщения (тела), то есть без служебных байтов либо цифры 126 или 127

      opcode = inbuf[0] & 0x0F;

      payload_len = inbuf[1] & 0x7F;
      //printf("Maska: 0x%02x\n", inbuf[1] & 0x80 ? 1:0);

      unsigned char payload[SW_BUF] = {
          0,
      };

      if (opcode == WS_CLOSING_FRAME) // от клиента получен код закрытия соединения
      {
        clientCount--;
        if (logs == true) std::cout << "\n" << "Client send close code \nClient count: " << clientCount << "\n";
        // send close code
        /*std::string answer = "1000";
        const char *messag = answer.c_str();
        int message_size = (int)strlen(messag);
        char out_data[128] = {
            0,
        };
        memcpy(out_data + 2, messag, message_size); // копируем сообщение в массив "out_data" начиная со второго байта (первые два байта для опкода и длины тела)

        out_data[0] = 0x81;
        out_data[1] = (char)message_size;

        if (send(client_fd, out_data, message_size + 2, 0) == -1)
        {
          if (logs == true) std::cout << "\nError sending\n";
        }*/ 
        if (close(client_fd) == -1)
        {
          if (logs == true) std::cout << "Error close client WS\n";
        }
        pthread_exit(NULL); // убиваем поток
      }

      else if (opcode == WS_PONG_FRAME) // от клиента получен PONG (маскированный)
      {
        masking_key[0] = inbuf[2];
        masking_key[1] = inbuf[3];
        masking_key[2] = inbuf[4];
        masking_key[3] = inbuf[5];

        unsigned int i = 6, pl = 0;
        for (; pl < payload_len; i++, pl++)
        {
          payload[pl] = inbuf[i] ^ masking_key[pl % 4];
        }
      }

      else if (opcode == WS_TEXT_FRAME && payload_len < 126) // от клиента получен текст
      {
        masking_key[0] = inbuf[2];
        masking_key[1] = inbuf[3];
        masking_key[2] = inbuf[4];
        masking_key[3] = inbuf[5];

        unsigned int i = 6, pl = 0;
        for (; pl < payload_len; i++, pl++)
        {
          payload[pl] = inbuf[i] ^ masking_key[pl % 4];
        }

        //printf("Payload_len: %d\n", inbuf[1] & 0x7F); // выводим длинну сообщения
        std::string readmsg((char *)payload);
        std::string answer = answerFunction(client_fd, readmsg, clientIp);

        if (answer.length() < 126) // возможна ошибка при длине строки 125 - не запишется нуль-терминатор ???
        {
          const char *messag = answer.c_str();
          int message_size = (int)strlen(messag);
          char out_data[128] = {
              0,
          };
          memcpy(out_data + 2, messag, message_size); // копируем сообщение в массив "out_data" начиная со второго байта (первые два байта для опкода и длины тела)

          out_data[0] = 0x81;
          out_data[1] = (char)message_size;

          if (send(client_fd, out_data, message_size + 2, 0) == -1)
          {
            if (logs==true) std::cout << "\nError sending\n";
            if (close(client_fd) == -1) {
              if (logs==true) std::cout << "Error close client WS\n";
            }
            pthread_exit(NULL);
          }
        }
        else if (answer.length() <= 65535)
        {
          const char *messag = answer.c_str();
          unsigned short message_size = strlen(messag);
          char out_data[SW_BUF] = {
              0,
          };
          memcpy(out_data + 4, messag, message_size); // копируем сообщение в массив "out_data" начиная со второго байта (первые два байта для опкода и длины тела)

          out_data[0] = 0x81;                       // == 10000001 == FIN1......opcod 1 (текст)
          out_data[1] = 126;                        // пишем цифру 126, котороя в двоичном виде == 01111110, соответственно маска 0, остальные 7 бит == 126
          out_data[3] = message_size & 0xFF;        // собираем длину сообщения
          out_data[2] = (message_size >> 8) & 0xFF; // собираем длину сообщения

          //printf("\nSize out Msg3: %d\n", message_size);

          if (send(client_fd, out_data, message_size + 4, 0) == -1) // отправка
          {
            if (logs==true) std::cout << "\nError sending\n";
            if (close(client_fd) == -1) {
              if (logs==true) std::cout << "Error close client WS\n";
            }
            pthread_exit(NULL);
          }
        }

      } // END if < 126

      else if (opcode == WS_TEXT_FRAME && payload_len == 127) // от клиента получен текст
      {
        if (logs==true) std::cout << "Text > 65535\n";
      }

    } // END if(n > 0)

  } // END while(1)

} // END ws_func

// Для управления севрвером через консоль
void * serverControl(void *) {
  std::string readText; 

  while (true)
  {

    std::cin >> readText;

    if (readText == "stop")
    {
      threadControl = true;
      pthread_exit(NULL);
    }
    else if (readText == "hello")
    {
      std::cout << "Hello!\n";
    }
    else if (readText == "client")
    {
      std::cout << "Client count: " << clientCount << '\n';
    }
    else if (readText == "resetlogins")
    {
      json sda;

      int numb = 1;
      sda["example"]["password"] = "example";
      sda["LoginList"] = "example.";

      while (numb<=27) {
        sda["example"][std::to_string(numb)]["true"]=0;
        sda["example"][std::to_string(numb)]["false"]=0;
        numb++;
      }

      std::ofstream FNamew;
      FNamew.open("clients.json");
      if (FNamew.is_open())
      {
        FNamew << sda;
        FNamew.close();
      }
      else
      {
        std::cout << "Error open file\n";
      }

      json sdaip;

      sdaip["ip"] = "client";

      std::ofstream FNamewip;
      FNamewip.open("ip.json");
      if (FNamewip.is_open())
      {
        FNamewip << sdaip;
        FNamewip.close();
      }
      else
      {
        std::cout << "Error open file\n";
      }
    }
    else if (readText == "resetip")
    {
      json sda;

      sda["ip"] = "client";

      std::ofstream FNamew;
      FNamew.open("ip.json");
      if (FNamew.is_open())
      {
        FNamew << sda;
        FNamew.close();
      }
      else
      {
        std::cout << "Error open file\n";
      }
    }
    else if (readText == "resetsettings")
    {
      json sda;

      sda["Timeout"] = 500;
      sda["Log"] = false;
      sda["Client count"] = 10;
      sda["Port"] = "8082";

      std::ofstream FNamew;
      FNamew.open("settings.json");
      if (FNamew.is_open())
      {
        FNamew << sda;
        FNamew.close();
      } else
      {
        std::cout << "Error open file\n";
      }
    }
    else if (readText.find("clearlogin") != std::string::npos)
    {

    }
    else if (readText.find("timeout") != std::string::npos)
    {
      int i = 8;
      std::string s;
      while (readText[i]!=' ')
      {
        s += readText[i];
        i++;
        if (i>30) break;
      }
      if (s.length()<30) {
        std::string er = jsonWrite("settings.json",s,"Timeout",1);
        if (er != "true")
        {
          std::cout << er;
        } else {
          try {
            timeout = atoi(s.c_str());
          } catch (std::invalid_argument) {
            std::cout << "Error convert type\n";
          }
        }
      }  else {
        std::cout << "Write length > 30\n";
      } 
    }
    else if (readText.find("log") != std::string::npos)
    {
      int i = 4;
      std::string s;
      while (readText[i]!=' ')
      {
        s += readText[i];
        i++;
        if (i>30) break;
      }
      if (s.length()<30) {
        std::string er = jsonWrite("settings.json",s,"Log",2);   
        if (er!="true") {
          std::cout << er;
        } else {
          if (s.find("true") != std::string::npos) {
            logs = true;
          }  else if (s.find("false") != std::string::npos) {
            logs = false;
          } else {
            std::cout << "Error convert type\n";
          }
        }
      } else {
        std::cout << "Write length > 30\n";
      }
    }
    else if (readText.find("clientcount") != std::string::npos)
    {
      int i = 12;
      std::string s;
      while (readText[i]!=' ')
      {
        s += readText[i];
        i++;
        if (i>30) break;
      }
      if (s.length()<30) {
        std::string er = jsonWrite("settings.json",s,"Client count",1);
        if (er != "true")
        {
          std::cout << er;
        } else {
          try {
            client_count = atoi(s.c_str());
          } catch (std::invalid_argument) {
            std::cout << "Error convert type\n";
          }
        }
      } else {
        std::cout << "Write length > 30\n";
      }
    }
    else if (readText.find("addlogin") != std::string::npos)
    {
      
    }
    else if (readText.find("port") != std::string::npos)
    {
      int i = 5;
      std::string s;
      while (readText[i]!=' ')
      {
        s += readText[i];
        i++;
        if (i>30) break;
      }
      if (s.length()<30) {
        std::cout << '_' << s << "_\n";
        std::string er = jsonWrite("settings.json",s,"Port",0);
        if (er != "true")
        {
          std::cout << er;
        }
      } else {
        std::cout << "Write length > 30\n";
      }
    }
  }

}

int main()
{

  json settings;
  uint port;
  bool check = true;

  // Загрузка настроек из файлов
  std::ifstream setting("settings.json", std::ios::in | std::ios::binary);
  if (!setting.is_open())
  {
    std::cout << "Error open file settings\n";
    timeout = 500;
    logs = true;
    client_count = 5;
    port = 8080;
    check = false;
  }
  try
  {
    setting >> settings;
  }
  catch (nlohmann::json::exception)
  {
    check = false;
    setting.close();
    std::cout << "File json error\n";
    timeout = 500;
    logs = true;
    client_count = 5;
    port = 8080;
  }

  setting.close();
  if (check) {
    if (settings.find("Timeout") == settings.end())
    {
      std::cout << "Timeout not find\n";
      timeout = 500;
    }
    else
    {
      timeout = settings["Timeout"];
    }
    if (settings.find("Log") == settings.end())
    {
      std::cout << "Log not find\n";
      logs = true;
    }
    else
    {
      logs = settings["Log"];
    }
    if (settings.find("Client count") == settings.end())
    {
      std::cout << "Client count not find\n";
      client_count = 5;
    }
    else
    {
      client_count = settings["Client count"];
    }
    if (settings.find("Port") == settings.end())
    {
      std::cout << "Port not find\n";
      port = 8080;
    }
    else
    {
      std::string n = settings["Port"];
      port = atoi(n.c_str());
    }
  }

  int one = 1;
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);

  int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listen_socket < 0)
    return 1;

  setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)); // настройки сокета 1

  //if (timeout > 0)
  //{
    struct timeval tv;
    tv.tv_sec = (timeout / 1000);
    tv.tv_usec = (timeout % 1000) * 1000; // timeout - милисекунды, но tv.tv_usec - микросекунды
    setsockopt(listen_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv); // настройки сокета 2
  //}

  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);

  if (bind(listen_socket, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) == -1)
  {
    close(listen_socket);
    return 1;
  }

  if (listen(listen_socket, 5) == -1)
  {
    close(listen_socket);
    return 1;
  }

  signal(SIGPIPE, SIG_IGN);

  const int max_client_buffer_size = 1024;
  char buf[max_client_buffer_size];
  int client_socket = -1;

  // Запускаем поток для управления сервером
  pthread_t threadcontrol;
  int status_control = pthread_create(&threadcontrol, NULL, serverControl, NULL);
  if (status_control != 0) {
        std::cout << "\nCONTROL_THREAD_NOT_CREATED\n";
    }

  std::string lastip;
  // Зацикливаем приём - передачу данных
  while (true)
  {
    if (threadControl) {
      pthread_exit(NULL);
    }

    client_socket = accept(listen_socket, (struct sockaddr *)&cli_addr, &sin_len); // Соединяем сокет
    
    if (logs==true) {
      if (lastip!=std::string(inet_ntoa(cli_addr.sin_addr))) {
        std::cout<<std::string(inet_ntoa(cli_addr.sin_addr))<<"\n";
        lastip=std::string(inet_ntoa(cli_addr.sin_addr));
      }
    }
    ip=std::string(inet_ntoa(cli_addr.sin_addr));
    //client_socket = accept(listen_socket, NULL, NULL); // Соединяем сокет
    

    int result = read(client_socket, buf, max_client_buffer_size); // Принимаем сообщения

    if (result == -1)
    {
      // ошибка получения данных
      //if (logs==true) std::cout << "Error read buffer: " << result << "\n";
      close(client_socket);
    }
    else if (result == 0)
    {
      // соединение закрыто клиентом
      if (logs==true) std::cout << "Client close connection\n";
    }
    else if (result > 0)
    {
      bool upgraded = false; // запоминаем, происходит ли переход на ws
      // Мы знаем фактический размер полученных данных, поэтому ставим метку конца строки
      // В буфере запроса.
      buf[result] = '\0';
      // std::cout << buf; // вывод запроса к серверу


      if (strstr(buf, "Upgrade: websocket") != NULL)
      {
        if (clientCount >= client_count) {
          if (logs==true) std::cout << "Client limits out, close socket\n";
          close(client_socket);
        } else {
          char *p = NULL;
          pthread_t ws_thread;

          if ((p = strstr(buf, "Sec-WebSocket-Key:")) != NULL)
          {
            char resultstr[64] = {
                0,
            };
            int i = 0, it = 0;
            for (i = 19; it < 24; i++, it++)
            {
              resultstr[it] = p[i];
            }

            strcat(resultstr, GUIDKey);

            ////////////////////////////sha1///////////////////////////////////////
            unsigned char temp[SHA_DIGEST_LENGTH] = {
                0,
            };
            SHA1(temp, resultstr, strlen(resultstr));

            ////////////////////////////Base64////////////////////////////////////
            unsigned char key_out[64] = {
                0,
            };
            base64_encode(temp, key_out, sizeof(temp));

            //printf("\nKey_for_client:%s\n", key_out);

            sem_init(&sem, 0, 0);

            char resp[131] = {
                0,
            };
            snprintf(resp, 130, "%s%s%s", response_ws, key_out, "\r\n\r\n");
            if (send(client_socket, resp, sizeof(char) * strlen(resp), 0) == -1)
              if (logs==true) std::cout << "Sending response WS\n";
            
            //////////////////////////// START WS /////////////////////////////////
            if (pthread_create(&ws_thread, NULL, &ws_func, &client_socket) != 0)
            {
              if (logs==true) std::cout << "Creating WS thread failed\n";
              return 0;
            } 
            else {
              clientCount++;
              if (logs==true) std::cout << "Client count: " << clientCount << "\n";
            }
            pthread_detach(ws_thread);
            upgraded = true;
            sem_wait(&sem);
          }
        }
      }
      else
      {
        json inFile;
        std::string bufstr = buf;
        std::string fileName;
        std::string position;

        // read for video
        if (strstr(buf, "Range: bytes=") != NULL) {
          int g = bufstr.find("Range: bytes=")+13;
          while (bufstr[g]!='-') {
            position.push_back(bufstr[g]);
            g++;
          }
          //std::cout << "\n" << "Range: " << position << "\n";
        } else {
          position = "0";
        }
        //////////

        int i = bufstr.find("GET / ")+6;
        while (bufstr[i]!=' ' && bufstr[i]!='\r') {
          fileName.push_back(bufstr[i]);
          i++;
        }

        std::ifstream FName ("path_table.json", std::ios::in | std::ios::binary);
        if (!FName.is_open())
        {
            result = send(client_socket, response_403, sizeof(response_403) - 1, 0);
            if (logs==true) std::cout << "File path_table not open\n";
        }
        try
        {
            FName >> inFile;
        }
        catch (nlohmann::json::exception)
        {
            FName.close();
            result = send(client_socket, response_403, sizeof(response_403) - 1, 0);
            if (logs==true) std::cout << "File path_table json error\n";
        }

        FName.close();

        //std::string k = inFile.dump(); 
        //std::cout << '\n' << k << '\n';

        if (inFile.find(fileName) != inFile.end()) {
          ReadFromFileAll(inFile[fileName], result, client_socket, logs, position);
        } else {
          if (logs==true) std::cout << "File not find: "+fileName+'\n';
          result = send(client_socket, response_403, sizeof(response_403) - 1, 0);
        }
      }

      if (result == -1)
      {
        // произошла ошибка при отправке данных
        //if (logs==true) std::cout << "Error send file: " << WSAGetLastError() << "\n";
      }
      // Закрываем соединение к клиентом
      if (!upgraded) {
        close(client_socket);
      }
    }
  }
        // Убираем за собой

        close(listen_socket);
        //freeaddrinfo(addr);
        //WSACleanup();
        return 0;
       
}
