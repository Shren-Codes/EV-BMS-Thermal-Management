#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHTesp.h"
#include "secrets.h"

// ---------------- WIFI DETAILS ----------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ---------------- COMPONENT PINS ----------------
const int DHT_PIN = 15;
const int COOLING_LED = 2;

// ---------------- OBJECTS ----------------
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
DHTesp dhtSensor;

// ---------------- ALERT FLAGS ----------------
bool warningSent = false;
bool criticalSent = false;
bool rapidRiseSent = false;

// ---------------- dT/dt TRACKING ----------------
float prevTemp = 0.0;
unsigned long prevTime = 0;
bool firstReading = true;

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("EV BMS THERMAL MONITORING SYSTEM");
  Serial.println("================================");

  // DHT22 setup
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Cooling system
  pinMode(COOLING_LED, OUTPUT);
  digitalWrite(COOLING_LED, LOW);

  // ---------------- WIFI ----------------

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // HTTPS certificate verification disabled for Wokwi testing
  client.setInsecure();

  // ---------------- TELEGRAM STARTUP ALERT ----------------

  bool sent = bot.sendMessage(
    CHAT_ID,
    "✅ EV BMS System Online\n"
    "Thermal Monitoring Started\n"
    "Thresholds: Warning>35°C | Critical>45°C",
    ""
  );

  if (sent) {
    Serial.println("Telegram: Startup alert sent");
  } else {
    Serial.println("Telegram: Startup alert failed");
  }

  // Initialize time tracking
  prevTime = millis();
}


// =================================================
// MAIN LOOP
// =================================================

void loop() {

  // ---------------- READ TEMPERATURE ----------------

  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temp = data.temperature;

  Serial.print("Battery Temperature: ");
  Serial.print(temp, 1);
  Serial.println(" °C");


  // =================================================
  // dT/dt CALCULATION
  // =================================================

  unsigned long currentTime = millis();

  float dt = (currentTime - prevTime) / 1000.0;

  float dTdt = 0.0;

  if (!firstReading && dt > 0) {

    dTdt = (temp - prevTemp) / dt;

    Serial.print("Rate of Rise: ");
    Serial.print(dTdt, 2);
    Serial.println(" °C/s");


    // =================================================
    // RAPID TEMPERATURE RISE ALERT
    // =================================================

    if (dTdt > 0.5 && !rapidRiseSent) {

      String message =
        "⚡ RAPID TEMPERATURE RISE!\n"
        "Current Temp: " + String(temp, 1) + " °C\n"
        "Rate: " + String(dTdt, 2) + " °C/s\n"
        "Thermal Runaway Risk — Check Immediately!";

      if (bot.sendMessage(CHAT_ID, message, "")) {

        Serial.println("Telegram: Rapid-rise alert sent");

        rapidRiseSent = true;
      }
    }


    // Reset rapid-rise alert when temperature rise normalizes
    if (dTdt <= 0.2) {
      rapidRiseSent = false;
    }
  }

  firstReading = false;

  prevTemp = temp;

  prevTime = currentTime;


  // =================================================
  // NORMAL CONDITION
  // =================================================

  if (temp < 35.0) {

    Serial.println("Battery Status: NORMAL");
    Serial.println("Cooling System: OFF");

    digitalWrite(COOLING_LED, LOW);

    warningSent = false;
    criticalSent = false;
  }


  // =================================================
  // WARNING CONDITION
  // =================================================

  else if (temp >= 35.0 && temp < 45.0) {

    Serial.println("WARNING: Battery Temperature High");
    Serial.println("Cooling System Activated");

    digitalWrite(COOLING_LED, HIGH);


    if (!warningSent) {

      String message =
        "⚠️ WARNING!\n"
        "EV Battery Temperature High\n"
        "Current Temp: " + String(temp, 1) + " °C\n"
        "Cooling System Activated";

      if (bot.sendMessage(CHAT_ID, message, "")) {

        Serial.println("Telegram: Warning alert sent");

        warningSent = true;
      }
    }
  }


  // =================================================
  // CRITICAL CONDITION
  // =================================================

  else {

    Serial.println("CRITICAL: Thermal Runaway Risk!");
    Serial.println("Emergency Cooling Activated");

    digitalWrite(COOLING_LED, HIGH);


    if (!criticalSent) {

      String message =
        "🔴 CRITICAL ALERT!\n"
        "Thermal Runaway Risk Detected\n"
        "Current Temp: " + String(temp, 1) + " °C\n"
        "Rate of Rise: " + String(dTdt, 2) + " °C/s\n"
        "Emergency Cooling Activated";

      if (bot.sendMessage(CHAT_ID, message, "")) {

        Serial.println("Telegram: Critical alert sent");

        criticalSent = true;
      }
    }
  }


  Serial.println("---------------------------");

  delay(3000);
}