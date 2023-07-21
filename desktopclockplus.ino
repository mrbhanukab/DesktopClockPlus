#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define OLED screen properties
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Array of Wi-Fi credentials
const char* ssid[] = {"SSID1", "SSID2", "SSID 3", "SSID 4 N SO ON"};
const char* password[] = {"PASSWORD1", "PASSWORD2", "PASSWORD3", "PASSWORD4"};
const int numNetworks = sizeof(ssid) / sizeof(ssid[0]);

// Variables to hold date and time information
String currentTime = "";
String currentMonthName = "";
String currentDay = "";
String remainingDaysS = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
// Bitmap images stored in PROGMEM
// 'focus', 20x20px
const unsigned char icon_focus [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x01, 0xf8, 0x00, 0x03, 0xfc, 0x00, 0x07, 0xfe, 0x00, 0x07,
  0xfe, 0x00, 0x07, 0xfe, 0x00, 0x03, 0xfc, 0x00, 0x03, 0xfc, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x1f,
  0xf0, 0x0f, 0xff, 0xe0, 0x1f, 0xff, 0xe0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xf0,
  0x0f, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x01, 0xff, 0xc0, 0x00, 0x07, 0x00
};
// 'nochat', 20x20px
const unsigned char icon_nochat [] PROGMEM = {
  0xdf, 0xf0, 0x00, 0xfc, 0x78, 0x00, 0x70, 0x1c, 0x00, 0xf8, 0x0e, 0x00, 0xdc, 0x07, 0x00, 0xce,
  0x03, 0xc0, 0x87, 0x03, 0xe0, 0x83, 0x83, 0xf0, 0xc1, 0xc7, 0x70, 0xc0, 0xe6, 0xf0, 0x60, 0x7f,
  0x70, 0x70, 0x3f, 0xf0, 0xef, 0xff, 0xf0, 0xff, 0xff, 0x70, 0xff, 0x5f, 0xf0, 0x03, 0xbf, 0xe0,
  0x01, 0xfb, 0xf0, 0x00, 0xff, 0xf0, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x30
};
// 'nophone', 20x20px
const unsigned char icon_nophone [] PROGMEM = {
  0x03, 0xfc, 0x00, 0x0f, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x3e, 0x07, 0xc0, 0x7f, 0xff, 0xe0, 0x73,
  0xff, 0xe0, 0xf3, 0x1f, 0xf0, 0xe3, 0x3e, 0x70, 0xe3, 0x7c, 0x70, 0xe3, 0xfc, 0x70, 0xe3, 0xfc,
  0x70, 0xe3, 0xec, 0x70, 0xe7, 0xcc, 0x70, 0xff, 0x8c, 0xf0, 0x7f, 0xfd, 0xe0, 0x7f, 0xfd, 0xe0,
  0x3e, 0x07, 0xc0, 0x1f, 0xff, 0x80, 0x0f, 0xff, 0x00, 0x03, 0xfc, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 240)
const int icon_allArray_LEN = 3;
const unsigned char* icon_allArray[3] = {
  icon_focus,
  icon_nochat,
  icon_nophone
};

// Function to connect to Wi-Fi
void connectToWiFi() {
  int attempt = 0;

// Display connection status on the OLED screen
// and try connecting to the current Wi-Fi network
// If successful, display connection message; otherwise, try the next network.
// If connected, display a success message; otherwise, display a failure message and restart the ESP8266.
  while (attempt < numNetworks && WiFi.status() != WL_CONNECTED) {
    display.setTextSize(1);
    display.setCursor(0, 10);
    display.setTextColor(WHITE);
    display.println("Connecting to,");
    display.setCursor(0, 20);
    display.setTextSize(2);
    display.println(String(ssid[attempt]));
    display.display();
    WiFi.begin(ssid[attempt], password[attempt]);
    delay(5500); // Wait 5.5 seconds for connection
    attempt++;
    display.clearDisplay();
  }
  if (WiFi.status() == WL_CONNECTED) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    display.println("Connected to WiFi");
    display.display();
    delay(1500);
    display.clearDisplay();
  } else {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    display.println("Failed to connect & Restarting");
    display.display();
    delay(1500);
    display.clearDisplay();
    ESP.restart();
  }
}

void setup() {
  // Initialization and configuration of the OLED display
  // Display introductory message for 2 seconds
  // Connect to Wi-Fi
  // Initialize the NTPClient for time synchronization

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.print("Focus Mode");
  display.setCursor(0, 30);
  display.print("ON");
  display.display();
  delay(2000);
  display.clearDisplay();
  connectToWiFi();
  display.clearDisplay();
  timeClient.begin();
  timeClient.setTimeOffset(19800); // Set the time offset to GMT +5:30 (19800 seconds)
}

// Function to update date and time information
// Fetch the current time from the NTP server
// Format the time in HH:MM format
// Extract the month, day, and calculate the number of remaining days to a specific target date
void updateDateTime() {
  String months[12] = {"Janu", "Febu", "Marh", "Aprl", "May", "June", "July", "Augu", "Sept", "Octo", "Nove", "Dece"};
  timeClient.update();
  if (timeClient.getMinutes() < 10) {
    currentTime = String(timeClient.getHours()) + ":0" + String(timeClient.getMinutes());
  }
  else {
    currentTime = String(timeClient.getHours()) + ":" + String(timeClient.getMinutes());
  }
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int currentMonth = ptm->tm_mon + 1;
  currentMonthName = String(months[currentMonth - 1]);
  currentDay = String(ptm->tm_mday);

  int remainingDays = 0;
  // Extract current date components from the struct tm
  int currentY = ptm->tm_year + 1900;
  int currentM = ptm->tm_mon + 1;
  int currentD = ptm->tm_mday;

  // Set the target date
  int targetYear = 2023;
  int targetMonth = 11;
  int targetDay = 26;

  // Calculate the remaining days
  if (currentY < targetYear || (currentY == targetYear && currentM < targetMonth) ||
      (currentY == targetYear && currentM == targetMonth && currentD < targetDay)) {
    // Target date is in the future
    struct tm targetTime;
    targetTime.tm_year = targetYear - 1900;
    targetTime.tm_mon = targetMonth - 1;
    targetTime.tm_mday = targetDay;
    targetTime.tm_hour = 0;
    targetTime.tm_min = 0;
    targetTime.tm_sec = 0;

    time_t targetTimestamp = mktime(&targetTime);
    time_t currentTimestamp = mktime(ptm);

    remainingDays = (targetTimestamp - currentTimestamp) / (24 * 60 * 60);

    remainingDaysS = String(remainingDays);

  }
}

// Display functions for different screens
void display1() {
  display.setTextSize(3);
  display.setCursor(30, 5);
  display.setTextColor(WHITE);
  display.println(currentMonthName);
  display.setCursor(50, 28);
  display.setTextSize(2);
  display.println(currentDay);
  display.setTextSize(1);
  display.setCursor(0, 55);
  display.print(currentTime);
  display.setCursor(92, 55);
  display.print("[1/5]");
  display.display();
}

void display2() {
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(0, 5);
  display.println(remainingDaysS);
  display.setTextSize(1);
  display.println("days left until the A/L exam");
  display.setCursor(0, 55);
  display.print(currentTime);
  display.setCursor(92, 55);
  display.print("[2/5]");
  display.display();
}

void display3() {
  const char* quotes[] = {
    "Do the Hard Work, Especially When You Don’t Feel Like It",
    "The harder you work, the luckier you get.",
    "So many books, so little time.",
    "You can’t be average and expect extraordinary results.",
    "Don’t wait for opportunities, create them.",
    "Don't waste your sperm, it is a precious resource.",
    "It's time to begin, isn't it?",
    "If I can't do it, then who can?",
    "There is no such thing as super human, there are people who hard work",
    "Don’t let your past mistakes define your future potential.",
    "Never let people who choose the path of least resistance steer you away from your chosen path of most resistance.",
    "No one is going to come help you. No one’s coming to save you.",
    "You are in danger of living a life so comfortable and soft, that you will die without ever realizing your true potential.",
    "Don’t focus on what you think you deserve. Take aim on what you are willing to earn!",
    "In the military we always say we don’t rise to the level of our expectations, we fall to the level of our training.",
    "Success isn’t owned, it’s leased. And rent is due every day.",
    "You can’t be afraid to fail. Failure is just a lesson.",
    "Stop being a victim, start being a winner.",
    "Success is not a matter of luck; it’s a matter of strategy, discipline, and hard work."
  };

  int numQuotes = sizeof(quotes) / sizeof(quotes[0]);
  int randomIndex = random(numQuotes);  // Generate a random index within the range of the array
  String randomQuote = quotes[randomIndex];

  display.setTextSize(1);
  display.setCursor(0, 5);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println(randomQuote);
  display.setCursor(0, 55);
  display.print(currentTime);
  display.setCursor(92, 55);
  display.print("[3/5]");
  display.display();
}
void display4() {
  display.drawBitmap(17, 5,  icon_focus, 20, 20, WHITE);
  display.drawBitmap(54, 5,  icon_nochat, 20, 20, WHITE);
  display.drawBitmap(91, 5,  icon_nophone, 20, 20, WHITE);
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.setTextColor(WHITE);
  display.println("["+WiFi.SSID()+" | "+String(WiFi.RSSI()) + "dBm]");
  display.setCursor(0, 55);
  display.print(currentTime);
  display.setCursor(92, 55);
  display.print("[4/5]");
  display.display();
}

// Continuously loop through different screens and update the OLED display accordingly
void loop() {
  updateDateTime();
  display1();
  delay(4000);
  display.clearDisplay();
  display2();
  delay(4000);
  display.clearDisplay();
  display3();
  delay(5000);
  display.clearDisplay();
  display4();
  delay(4000);
  display.clearDisplay();
}
