// Created by Rıza Arda Kırmızıoğlu and Berk Özdilek.
/*
This is an example of IvenCloudESP library in which you can activate your device,
create data objects, send data to Iven Product Cloud and handle tasks.
For further explanations about functions in library, hardware setup and REQUIRED manual
settings of ESP8266 check blog: http://blog.iven.io
*/

#include <IvenCloudESP.h>

// Analog read pin for LDR voltage value.
#define lightPin 0

// Software serial digital pins for Arduino to communicate with ESP8266
#define arduino_rx_esp_tx 2
#define arduino_tx_esp_rx 3

// Sensor voltage value (between 0-1023 for 5v and 0-675 for 3.3v)
int sensorValue = 0;

// 
bool available;
bool isActive = false;

IvenCloudESP client(arduino_rx_esp_tx, arduino_tx_esp_rx, 9600, true);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lightPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!isActive) {

  	// Activates device, has API-KEY and returns IvenResponse object.
    IvenResponse i = client.activateDevice("secret_key", "device_uid");
    
    Serial.println(i.status);
    if (i.status == 200)
      isActive = true;
      Serial.println("api-key is taken");
  } else {
  	// Creates IvenData object
    IvenData data;

    sensorValue = analogRead(lightPin);
    if (sensorValue < 400) 
      available = true;
    else available = false;

    // Creates json object for the body of the HTTP POST request.
    data.add("available", available);

    // Posts data to Iven Product Cloud
    IvenResponse p = client.sendData(data);

    Serial.println(p.status);
    Serial.println(p.ivenCode);
    Serial.println(p.task);
  }
}