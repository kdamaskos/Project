#include "string"

#include "mbed.h"


#define SEND_ERROR      -1

#define SEND_WEBPAGE    0

#define UPDATE_DATA     1

/*
string htmlPage = "<html>"
"<head><title>Wifi Form</title>"
"</head>"
"<body>"
"<h2>Wifi Connection Form</h2>"
"<form action=\"route\" method = \"get\">"
"<label for=\"fname\">SSID:</label><br>"
"<input type=\"text\" id=\"ssid\" name=\"ssid\" ><br>"
"<label for=\"fname\">Password:</label><br>"
"<input type=\"text\" id=\"psw\" name=\"psw\" ><br>"
"<br>"
"<input type=\"submit\" value=\"Submit\">"
"</form>"
"</body>"
"</html>";
*/


string htmlPage = "<html>"
"<html>"
"<head>"
    "<title>"
    "JavaScript | Sending JSON data to server."
    "</title>"
"</head>"

"<body style=\"text-align:center;\" id=\"body\">"
    "<h1 style=\"color:green;\">"
    "O giannis einai poustis"
    "</h1>"

    "<p>"
        "<!-- Making a text input -->"
        "<input type=\"text\" id=\"name\" placeholder=\"Your username\">"
        "<input type=\"email\" id=\"email\" placeholder=\"pass\">"

        "<!-- Button to send data -->"
        "<button onclick=\"sendJSON()\">Send JSON</button>"

    "<!-- For printing result from server -->"
    "<p class=\"result\" style=\"color:green\"></p>"

"</p>"

"<!-- Include the JavaScript file -->"
"<script >"
    "function sendJSON(){"

            "let result = document.querySelector('.result');"
            "let name = document.querySelector('#name');"
            "let email = document.querySelector('#email');"

       
            "let xhr = new XMLHttpRequest();"
            "let url = \"input\";"


            "xhr.open(\"POST\", url, true);"

         
            "xhr.setRequestHeader(\"Content-Type\", \"application/json\");"

   
            "xhr.onreadystatechange = function () {"
                "if (xhr.readyState === 4 && xhr.status === 200) {"

              
                   "result.innerHTML = this.responseText;"

                "}"
            "};"

   
            "var data = JSON.stringify({\"name\": name.value, \"email\": email.value });"

     
            "xhr.send(data);"
        "}"




"</script>"

"</body>"
"</html>";


void readStrUntil(BufferedSerial * serial_port, string * str, char until) 
{
    char c;

    while (true) 
    {

        serial_port->read((void*)&c, 1);

        if (c != until) 
        {
            *str += c;
        } 
        else 
        {
            break;
        }
    }
}

void waitFor(BufferedSerial * serial_port, char * text) 
{
    string s;

    char c;

    for (int i = 0; i < strlen(text); i++) 
    {
        serial_port->read((void*)&c, 1);
        s += c;
        if (c != text[i]) {
            i = 0;
        }
    }

    printf("%s\n", s.c_str());
}

void sendCommand(BufferedSerial * serial_port, char * cmd) 
{
    
    char buff[20];

    strcpy(buff, cmd);

    strcat(buff, "\r\n");

    printf("Send :%s\n",buff);

    serial_port->write(buff, strlen(buff));


}


void tcpReply(BufferedSerial * serial_port,int linkId, string data) 
{
    char buffer[30];

    sprintf(buffer, "AT+CIPSEND=%d,%d\r\n", linkId, data.length());

    serial_port->write((void*)buffer, strlen(buffer));

    thread_sleep_for(100); // Can't use waitFor here as it isn't fast enough

    char c;

    for (int i = 0; i < data.length(); i++) 
    {
        // Artificially slowing down this to prevent errors
        c = data[i];

        serial_port->write((void*)&c, 1);

    }

    waitFor(serial_port,(char *)"SEND OK");

    sprintf(buffer, "AT+CIPCLOSE=%d\r\n", linkId);

    serial_port->write((void*)buffer, strlen(buffer));

    waitFor(serial_port,(char *)"OK");
}


void httpReply(BufferedSerial * serial_port,int linkId, string code, string payload) 
{

    string data = "HTTP/1.1 " + code + "\r\nContent-Type: text/html\r\n\r\n" + payload;

    tcpReply(serial_port,linkId, data);

}



void handleRequest(BufferedSerial * serial_port,int linkId, int page) 
{ 
    
    if (page == 0) 
    { 

        httpReply(serial_port,linkId, "200 OK", htmlPage); // Website send

    }
    else if ( page == 1 ) 
    { 

        httpReply(serial_port,linkId, "200 OK", "SSID and password set");

        printf("got wifi\n");

    } 
    else 
    { 

        httpReply(serial_port,linkId, "404 Not Found", "404 Not found!");

    }

}



void server(char * ssid, char * psw)
{
    BufferedSerial serial_port(D8, D2);

    printf("Server setup\n");

    serial_port.set_baud(115200);

    sendCommand(&serial_port,(char *)"AT+RST");
    waitFor(&serial_port,(char *)"OK");

    ThisThread::sleep_for(1s);

    sendCommand(&serial_port,(char *)"ATE0");
    waitFor(&serial_port,(char *)"OK");


    sendCommand(&serial_port,(char *)"AT+CIFSR");
    waitFor(&serial_port,(char *)"OK");

    
    sendCommand(&serial_port,(char *)"AT+CWMODE=2");
    waitFor(&serial_port,(char *)"OK");
   // serial_port.read(buffer, sizeof(buffer));

    sendCommand(&serial_port,(char *)"AT+CIPMUX=1");
    waitFor(&serial_port,(char *)"OK");
    //serial_port.read(buffer, sizeof(buffer));

    sendCommand(&serial_port,(char *)"AT+CIPSERVER=1,80");
    waitFor(&serial_port,(char *)"OK");
    //serial_port.read(buffer, sizeof(buffer));

     char buffer[500] = {0};

    while (true) 
    {
        // Input looks like this: +IPD,0,372:GET / HTTP/1.1
        waitFor(&serial_port,(char *)"+IPD,");

        // Parse linkId
        int linkId = 0;

        char c;

        while (true) 
        {
            //serial_port.read(buffer, sizeof(buffer));
            //printf("%s\n",buffer);
            
            serial_port.read((void*)&c, 1);
            if (c == ',') break;
            linkId = linkId * 10 + (c - '0');
            
        }

        serial_port.read(buffer, 150);
        //printf("%s\n",buffer);

        if(strstr(buffer,"/route?") != NULL)
        {
               
            psw = strstr(buffer,"&psw=");

            char *end = strstr(psw," ");

            end[0] = NULL;

            psw[0] = NULL;

            char * ssid = strstr(buffer,"ssid=");

            handleRequest(&serial_port,linkId,UPDATE_DATA);

            //ssid = ssid +5;

            //psw = psw +5;

            printf("\n\nssid = %s, psw = %s\n\n",ssid,psw);

            break;

        }
        else if (strstr(buffer,":GET ") != NULL)
        {

            handleRequest(&serial_port,linkId,SEND_WEBPAGE);

        }
        else if(strstr(buffer,":POST ") != NULL)
        {   
            waitFor(&serial_port,(char *)"name\":\"");

            waitFor(&serial_port,(char *)"email\":\"");

            //handleRequest(&serial_port,linkId, SEND_ERROR);

        }
        else 
        {   

            handleRequest(&serial_port,linkId, SEND_ERROR);

        }

    }

    ThisThread::sleep_for(1s);


}