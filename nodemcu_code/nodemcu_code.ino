#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL34BVxY-I0"
#define BLYNK_TEMPLATE_NAME "Data"
#define BLYNK_AUTH_TOKEN "aKqVb24KoEQ0wFGEtJyWFPY4h_pxp3p8"
#define BLYNK_PRINT Serial


#define SS_PIN 2
#define RST_PIN 0
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32


#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MFRC522 mfrc522(SS_PIN, RST_PIN);

char ssid[] = "Iphone 12";
char pass[] = "tubelight";

unsigned long startTime = 0;
bool timerRunning = false;
bool val = true;
int alcohol = 0;


byte correctUID[] = { 0x72, 0x1A, 0x46, 0x51 };
byte correctUID1[] = { 0x13, 0xC2, 0x31, 0xBC };
byte uidLength = 4;
bool driver1 = false;
bool driver2 = false;
bool seat_status = false;



void setup() {
  Serial.begin(9600);
  pinMode(D0, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  welcome();
  delay(3000);
  scan_card();
}



void loop() {

  scan_card();

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println();
  Serial.print("UID tag :");
  bool isCorrectUID = true;
  bool isCorrectUID1 = true;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);


    if (i < uidLength && mfrc522.uid.uidByte[i] != correctUID[i]) {
      isCorrectUID = false;
    }
    if (i < uidLength && mfrc522.uid.uidByte[i] != correctUID1[i]) {
      isCorrectUID1 = false;
    }
  }


  if (isCorrectUID && mfrc522.uid.size == uidLength) {
    Serial.println("\nWelcome!");
    driver1 = true;
    driver2 = false;
    val = true;
    login("Driver 1");
  } else if (isCorrectUID1 && mfrc522.uid.size == uidLength) {
    Serial.println("\nWelcome!");
    driver1 = false;
    driver2 = true;
    val = true;
    login("Driver 2");
  } else {
    Serial.println("\nAccess Denied");
    access_declined();
  }

  delay(2000);
}





void welcome() {
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F(" Long Haul  Project"));
  display.display();
}





void scan_card() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Scan Card"));
  display.display();
}



void access_granted(String d_name) {
  Serial.println(d_name);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 0);
  display.println(F("Access"));
  display.setCursor(15, 15);
  display.println(F("Granted"));
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setCursor(15, 0);
  display.println(d_name);
  display.display();
  delay(3000);
}



void access_declined() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Error"));
  display.display();
  delay(3000);
}




void check_alcohol() {
  alcohol = analogRead(A0);
  Serial.print("alcohol: ");
  Serial.println(alcohol);
  if (alcohol >= 450) {

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F(" Alcohol   Detected"));
    display.display();
    Blynk.virtualWrite(V3, 10);
    delay(1000);
    Blynk.virtualWrite(V3, 0);
    delay(3000);
    val = false;
  }
}

void check_seatbelt() {

  if (digitalRead(D0)) {
    Serial.println("Seat Belt Removed");
    seat_status = true;
    Blynk.virtualWrite(V4, 10);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("  WARNING  Seat Belt"));
    display.display();
    delay(2000);
  } else {
    seat_status = false;
  }
}




void login(String name) {
  startTime = millis();
  access_granted(name);
  while (val) {

    startTimer();

    if (timerRunning) {
      displayElapsedTime();
    }


    delay(1000);
    Blynk.run();
  }
}




void startTimer() {
  if (!timerRunning) {
    startTime = millis();
    timerRunning = true;


    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Timer Started!");
    display.display();


    Serial.println("Timer Started!");
  }
}





void displayElapsedTime() {
  check_alcohol();
  check_seatbelt();
  unsigned long currentTime = millis();
  unsigned long elapsedTime = (currentTime - startTime) / 1000;


  int hours = elapsedTime / 3600;
  int minutes = (elapsedTime % 3600) / 60;
  int seconds = elapsedTime % 60;


  char timeBuffer[20];
  sprintf(timeBuffer, "%02d:%02d:%02d", hours, minutes, seconds);

  display.clearDisplay();
  display.setCursor(15, 0);
  display.println("Duty Time");
  display.setCursor(15, 19);
  display.println(timeBuffer);
  display.display();
  if (elapsedTime >= 30) {
    if (driver1 == true) {
      Blynk.virtualWrite(V1, 10);
      Serial.println("Elapsed time has exceeded 30 seconds for driver 1");
      val = false;
      delay(1000);
      Blynk.virtualWrite(V1, 0);

    } else if (driver2 == true) {
      Blynk.virtualWrite(V2, 10);
      Serial.println("Elapsed time has exceeded 30 seconds for driver 2");
      val = false;
      delay(1000);
      Blynk.virtualWrite(V2, 0);
    }
  }

  Serial.println(timeBuffer);
}