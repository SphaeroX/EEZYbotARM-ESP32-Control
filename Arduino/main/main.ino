/*
  "Arduino IDE: Tools -> Partition Scheme:change "Default" to "Huge APP(3MB No OTA)""
*/

#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "EEPROM.h"
#include "StringSplitter.h"

Servo myservo_1;
Servo myservo_2;
Servo myservo_3;
Servo myservo_4;

const char *ssid = "RoBotArm";
const char *password = "12121212";

WebServer server(80);

String program;
int program_state = 0;
int program_step = 0;
int programm_current_mode = 0;
int programm_current_step = 0;

// EEPROM
int address = 0;
#define EEPROM_SIZE 512

// us axes mg995
int servo_us_min = 500;       // using default min/max of 1000us and 2000us
int servo_us_max = 2500;

// us gripper sg90
int servo_sg90_us_min = 900;       // using default min/max of 1000us and 2000us
int servo_sg90_us_max = 2100;

int servo_hertz = 50;         // standard 50 hz servo

int servo_pin_1 = 22; // rotate
int servo_pin_2 = 4; // forward
int servo_pin_3 = 16; // updown
int servo_pin_4 = 17; // gripper

int servo_pos_1 = 87;
int servo_pos_2 = 0;
int servo_pos_3 = 5;
int servo_pos_4 = 50;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // ------------------------------------------------      webserver handle linking
  server.on("/change_axis", handleChangeAxis);
  server.on("/get_programm", handleGetProgramm);
  server.on("/toggle_programm", handleChangeProgramm);
  server.on("/save_teach", handleSaveTeach);

  server.begin();
  Serial.println("HTTP server started");

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo_1.setPeriodHertz(servo_hertz);
  myservo_1.attach(servo_pin_1, servo_us_min, servo_us_max);
  myservo_1.write(servo_pos_1);
  myservo_2.setPeriodHertz(servo_hertz);
  myservo_2.attach(servo_pin_2, servo_us_min, servo_us_max);
  myservo_2.write(servo_pos_2);
  myservo_3.setPeriodHertz(servo_hertz);
  myservo_3.attach(servo_pin_3, servo_us_min, servo_us_max);
  myservo_3.write(servo_pos_3);
  myservo_4.setPeriodHertz(servo_hertz);
  myservo_4.attach(servo_pin_4, servo_sg90_us_min, servo_sg90_us_max);
  myservo_4.write(servo_pos_4);
}

void setCrossOrigin() {
  server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
  server.sendHeader(F("Access-Control-Max-Age"), F("600"));
  server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
  server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
}

void loop() {
  server.handleClient();

  if (program_state) {
    Serial.print("exec program: ");
    Serial.println(program);
    
    int startPos = 0;

    for (int i = 0; i < program.length(); i++) {
      if (program.substring(i, i + 1) == ";") {
        String command = program.substring(startPos, i);

        Serial.print("exec command: ");
        Serial.println(command);

        if (command.startsWith("MOVE")) {
          StringSplitter *splitter = new StringSplitter(command, ' ', 6);
          ptp_move(splitter->getItemAtIndex(1).toInt(), splitter->getItemAtIndex(2).toInt(), splitter->getItemAtIndex(3).toInt(), splitter->getItemAtIndex(4).toInt(), splitter->getItemAtIndex(5).toInt());
        }

        if (command.startsWith("WAIT")) {
          StringSplitter *splitter = new StringSplitter(command, ' ', 2);
          delay(splitter->getItemAtIndex(1).toInt());
        }

        if (command.startsWith("EXIT")) {
          program_state = 0;
        }

        startPos = i + 1;
      }
    }

    program_step++;
  }

  delay(2);//allow the cpu to switch to other tasks
}
