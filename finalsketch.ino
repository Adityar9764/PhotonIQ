/*
  IoT-Based Smart Lighting System using ESP32, LDR Sensor & Relay
  ---------------------------------------------------------------
  Author: Aditya Raj
  Description:
    An IoT-powered smart lighting system that automatically controls
    illumination based on ambient light intensity and sends real-time
    telemetry to ThingsBoard Cloud via MQTT.
*/

#include <WiFi.h>
#include <PubSubClient.h>

// ---------------- Pin Configuration ----------------
#define LDR_PIN 34       // LDR sensor input pin
#define RELAY_PIN 23     // Relay control pin

// ---------------- Behaviour Flags -------------------
#define LDR_HIGH_IS_BRIGHT 0   // 0 if low LDR value = bright, 1 if high = bright
#define RELAY_ACTIVE_LOW   1   // 1 if relay triggers on LOW signal

// ---------------- Wi-Fi Credentials -----------------
const char* ssid     = "YOUR_WIFI_SSID";       // 🔒 Replace with your Wi-Fi name
const char* password = "YOUR_WIFI_PASSWORD";   // 🔒 Replace with your Wi-Fi password

// ---------------- ThingsBoard MQTT Details ----------
#define THINGSBOARD_SERVER  "mqtt.thingsboard.cloud"
#define THINGSBOARD_PORT    1883
#define ACCESS_TOKEN        "YOUR_ACCESS_TOKEN" // 🔒 Replace with your device token

// ---------------- Global Objects --------------------
WiFiClient espClient;
PubSubClient client(espClient);

// ---------------- Helper: Connect Wi-Fi -------------
void connectWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi connected! IP: " + WiFi.localIP().toString());
}

// ---------------- Helper: Connect ThingsBoard -------
void connectThingsBoard() {
  if (!client.connected()) {
    Serial.print("Connecting to ThingsBoard...");
    if (client.connect("ESP32_Device", ACCESS_TOKEN, NULL)) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(", retrying in 3s...");
      delay(3000);
    }
  }
}

// ---------------- Setup Function --------------------
void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Set relay OFF initially
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW);

  // Initialize connections
  connectWiFi();
  client.setServer(THINGSBOARD_SERVER, THINGSBOARD_PORT);
}

// ---------------- Main Loop -------------------------
void loop() {
  connectThingsBoard();   // Ensure MQTT connection remains active
  client.loop();

  // Read LDR analog value
  int ldrValue = analogRead(LDR_PIN);

  // Determine brightness level (threshold = 2000)
  bool bright = LDR_HIGH_IS_BRIGHT ? (ldrValue > 2000) : (ldrValue < 2000);
  bool relayState;

  // Relay logic
  if (bright) {
    Serial.println("🌞 Bright – LED OFF");
    digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW);
    relayState = 0;
  } else {
    Serial.println("🌙 Dark – LED ON");
    digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? LOW : HIGH);
    relayState = 1;
  }

  // Prepare telemetry payload
  String payload = "{\"ldr_value\":" + String(ldrValue) +
                   ",\"light_status\":" + String(bright ? 1 : 0) +
                   ",\"relay_state\":" + String(relayState) + "}";

  // Publish telemetry data to ThingsBoard
  Serial.println("📤 Sending: " + payload);
  if (!client.publish("v1/devices/me/telemetry", payload.c_str())) {
    Serial.println("⚠️ Failed to publish telemetry!");
  }

  delay(3000);   // Send data every 3 seconds
}
