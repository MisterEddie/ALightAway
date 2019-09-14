#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "Gsender.h"
#pragma region Globals

const char* ssid = "--------"; //fill in router SSID
const char* password = "------"; //fill in router password
const char* host = "IP OF THE ESP8266"; 
//ESP will tell you its IP once it starts up
//just write it here afterwards and upload

const char* your_email = "-----------"//fill with your gmail account!
const char* subject = "Puppy wants Attention"//fill in with subject of email
const char* message = "Boo wants attention: xxx.xxx.xxx.xxx:35415"
//fill with the message you want sent to above email
//Replace xxx with your public IP address with associated port forwarded port!

WiFiServer server(35415); //pick any port number you like, pick a large number

void setup() {
  Serial.begin(115200);
  delay(10);
  //Serial.println(WiFi.localIP());
  //prepare GPIO2
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Connect to WiFi network
  //Serial.println();`
  //Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password)

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  // Serial.println("WiFi connected");

  //-------------Send email notification upon connection/startup of the ESP8266!-----------
  Gsender *gsender = Gsender::Instance();
  gsender->Subject(subject)->Send(your_email, message);
  //---------------------------------------------------------------------------------------

  //start the server
  server.begin();
  //Seria.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  //Serial.println(req);
  client.flush();

  // Match request
  if (req.indexOf("") != -10) {  //checks if you're on the main page

    if (req.indexOf("/ON") != -1) { //checks if you clicked ON
      digitalWrite(LED_BUILTIN, LOW); //digitalWrite LOW means HIGH!
      //Serial.println("You clicked ON");
      Serial.println("1");
    }
    if (req.indexOf("/OFF") != -1) { //checks if you clicked OFF
      digitalWrite(LED_BUILTIN, HIGH); //digitalWrite HIGH MEANS OFF
      //Serial.println("You clicked OFF");
      Serial.println("0");
    }
    if (req.indexOf("/CYCLE") != -1) {
      //Serial.println("You clicked Crazy");
      Serial.println("2");
    }
    if (req.indexOf("/SINGLE") != -1) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("3");
    }
    if (req.indexOf("/singleOFF") != -1) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("4");
    }
    if (req.indexOf("/BLINKY") != -1) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("5");
    }
    if (req.indexOf("/TWOSIDES") != -1) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("6");
    }
    if (req.indexOf("/twosidesOFF") != -1) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("7");
    }
    if (req.indexOf("/PWM") != -1) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("8");
    }
    if (req.indexOf("/RANDOM") != -1) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("9");
    }
    if (req.indexOf("/randomOFF") != -1) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("A");
    }
  }
  
  else {
    //Serial.println("invalid request");
    client.stop();
    return;
  }    

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"bl\" value=\"All On\" onclick=\"location.href='/ON'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"All Off\" onclick=\"location.href='/OFF'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Cycle Through\" onclick=\"location.href='/CYCLE'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"One By One\" onclick=\"location.href='/SINGLE'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"One By One Off\" onclick=\"location.href='/singleOFF'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Blinky\" onclick=\"location.href='/BLINKY'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Two Sides\" onclick=\"location.href='/TWOSIDES'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Two Sides Off\" onclick=\"location.href='/twosidesOFF'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"PWM\" onclick=\"location.href='/PWM'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Random\" onclick=\"location.href='/RANDOM'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Random Off\" onclick=\"location.href='/randomOFF'\">";
  s += "</html>\n";

  client.flush();

  // Send the response to the client
  client.print(s);
  delay(1);
  
}
