#include <SPI.h>
#include <LoRa.h>

#define SS 5    // GPIO5 - SS
#define RST 14  // GPIO14 - RESET
#define DI0 2   // GPIO2 - IRQ
#define BUZZER_PIN 13  // Buzzer connected to GPIO13

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Mobile Device - LoRa Receiver with Buzzer");

  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(433E6)) {  // Initialize LoRa with 433 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    String receivedText = "";
    while (LoRa.available()) {
      receivedText += (char)LoRa.read();
    }

    // get RSSI of packet
    int rssi = LoRa.packetRssi();
    Serial.print(receivedText);
    Serial.print("' with RSSI ");
    Serial.println(rssi);

    // guide the hiker based on the RSSI value
    if (rssi > -70) {
      Serial.println("Very close to the fixed device");
      digitalWrite(BUZZER_PIN, LOW);  // No beep, close to the fixed device
    } else if (rssi > -90) {
      Serial.println("Getting closer to the fixed device");
      digitalWrite(BUZZER_PIN, LOW);  // No beep, getting closer
    } else {
      Serial.println("Far from the fixed device, move closer");
      digitalWrite(BUZZER_PIN, HIGH);  // Beep, far from the fixed device
    }
  }
}
