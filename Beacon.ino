#include <SPI.h>
#include <LoRa.h>

#define SS 5    // GPIO5 - SS
#define RST 14  // GPIO14 - RESET
#define DI0 2   // GPIO2 - IRQ

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Transmitter");

  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(433E6)) {  // Initialize LoRa with 433 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println("Hello LoRa");

  // send packet
  LoRa.beginPacket();
  LoRa.print("Hello LoRa");
  LoRa.endPacket();

  delay(5000);  // wait for 5 seconds
}
