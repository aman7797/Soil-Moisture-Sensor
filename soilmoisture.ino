#include "DHT.h"

#define DHTPIN 2      // DHT11 PIN
#define SMPIN A0      // SM PIN
#define BPIN 3        // BUZZER PIN
#define MPIN1 4       // BUZZER PIN
#define MPIN2 5       // BUZZER PIN

int pauseBuzzer = 1;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(BPIN, OUTPUT);
  pinMode(MPIN1, OUTPUT);
  pinMode(MPIN2, OUTPUT);
  dht.begin();
}

void loop() {
  delay(1000);

  // Read SM and convert in percentage
  float sm = analogRead(SMPIN);
  float s = map(sm,1020,490,0,100);
  // Read humidity in percentage
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  if (s < 10.00 && pauseBuzzer == 0) {
    digitalWrite(BPIN, HIGH);
    digitalWrite(MPIN1, HIGH);
    digitalWrite(MPIN2, LOW);                                                              
    pauseBuzzer = 1;
  } else if (s > 10 || s < 10.00 && pauseBuzzer == 1) {
     digitalWrite(BPIN, LOW);
     if(s > 10.00) {
      digitalWrite(MPIN1, LOW);
      digitalWrite(MPIN2, LOW);
     }
    pauseBuzzer = 0;
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f) || isnan(sm)) {
    Serial.println("Failed to read from sensors!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Soil Moisture Value: ");
  Serial.print(sm);
  Serial.print("\t");
  Serial.print("Soil Moisture Percentage: ");
  Serial.print(s);
  Serial.print(" %\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
