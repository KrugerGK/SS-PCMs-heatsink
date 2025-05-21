#include "max6675.h" // Thermocouple library for Arduino
#include <millisDelay.h>
/*
THERMOCOUPLES MAX6675 ->  ARDUINO MEGA2560
    GND ->  GND_PIN BLACK_WIRE
    VCC ->  5V_PIN YELLOW_WIRE // Connect to 5V
    SCK ->  PIN_12 GREEN_WIRE
    SO  ->  PIN_11 ORANGE_WIRE
    CS1 ->  PIN_10 Thermocouple_1 PURPLE_WIRE
    CS2 ->  PIN_9  Thermocouple_2 PURPLE_WIRE
    CS3 ->  PIN_8  Thermocouple_3 PURPLE_WIRE
    CS4 ->  PIN_7  Thermocouple_4 PURPLE_WIRE
*/
// Constants for pins
const int LED_PIN = 2;      // Indicator LED pin
const int RELAY_PIN_1 = 3;  // Relay 1 pin (main control)
const int RELAY_PIN_2 = 4;  // Relay 2 pin (if separate control, otherwise review if needed)

// Pins for MAX6675 thermocouples
const int thermoDO = 11;  // Data out
const int thermoCS1 = 10; // Chip select for thermocouple 1
const int thermoCS2 = 9;  // Chip select for thermocouple 2
const int thermoCS3 = 8;  // Chip select for thermocouple 3
const int thermoCS4 = 7;  // Chip select for thermocouple 4 
const int thermoCLK = 12; // Clock pin

// State variables
int relay_state = LOW;    // The current state of relay (LOW = OFF, HIGH = ON)
bool ledOn = false;       // The current state of LED

//  Variable sfor temperature readings
float t1, t2, t3 t4;  // Temperature readings from thermocouples 1, 2, 3, and 4
float prom;           // Average temperature

// Variables for non-blocking timer
unsigned long DELAY_TIME = 1800000; // Time interval in milliseconds (30 minutes)
unsigned long previousMillis = 0;   // Store the last time the state was updated
bool delayRunning = false;          // Controls if the timing cyvle is active

// Initialize the MAX6675 thermocouples
MAX6675 thermocouple_1(thermoCLK, thermoCS1, thermoDO);
MAX6675 thermocouple_2(thermoCLK, thermoCS2, thermoDO);
MAX6675 thermocouple_3(thermoCLK, thermoCS3, thermoDO);
MAX6675 thermocouple_4(thermoCLK, thermoCS4, thermoDO);

void setup() {
  Serial.begin(9600);
  Serial.println("\nMAX6675 test\n");
  Serial.println("T_1,T_2,T_3,PROM_T,T_4,TimeTotal,TimerRele,Rele_State");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off
  
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, relay_state);
  // If Relay 2 is not used, this can be removed
  // pinMode(RELAY_PIN_2, OUTPUT); // If Relay 2 is no used, this can be removed
  // digitalWrite(RELAY_PIN_2, relay_state); // If Relay 2 is no used, this can be removed

  previousMillis = millis(); // Initialize the timer
  delayRunning = true;       // Start the timer cycle
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time
  
  // Read temperature from thermocouples
  t1 = thermocouple_1.readCelsius();
  t2 = thermocouple_2.readCelsius();
  t3 = thermocouple_3.readCelsius();
  t4 = thermocouple_4.readCelsius();  // Thermocouple 4, used for testing and additional monitoring
  
  // Handle MAX6675 reading errors (NaN - Not a Number)
  
  if (isnan(t1)) { Serial.println("Error reading thermocouple 1"); t1 = -1; /* The hot plate will be heating, so a negative value will indicate no reading */ }
  if (isnan(t2)) { Serial.println("Error reading thermocouple 2"); t2 = -1;}
  if (isnan(t3)) { Serial.println("Error reading thermocouple 3"); t3 = -1;}
  if (isnan(t4)) { Serial.println("Error reading thermocouple 4"); t4 = -1;}

  // Calculate average only if readings are valid
  int validReadings = 0;
  float sumReadings = 0;
  if (t1 != -1) { sumReadings += t1; validReadings++; }
  if (t2 != -1) { sumReadings += t2; validReadings++; }
  if (t3 != -1) { sumReadings += t3; validReadings++; }
  
  if (validReadings > 0) {
    prom = sumReadings / validReadings;
  } else {
    prom = -1; // Set to -1 if no valid readings 
  } 
  
  // Timer logic to control the relay and LED
  if (delayRunning && (currentMillis - previousMillis >= DELAY_TIME)) {
    previousMillis = currentMillis; // Save the last time the state was updated
    delayRunning = false;           // Stop the timer cycle
    ledOn = !ledOn;                 // Toggle LED state
    if (ledOn) {
      relay_state = HIGH;           // Set relay to ON
    } else {
      relay_state = LOW;            // Set relay to OFF
    }
    digitalWrite(LED_PIN,relay_state); // Update LED state
  }
  // Update relay state
  digitalWrite(RELAY_PIN_1, relay_state);
  digitalWrite(RELAY_PIN_2, relay_state);
  // Print data in CSV format
  Serial.print(t1); Serial.print(F(","));
  Serial.print(t2); Serial.print(F(","));
  Serial.print(t3); Serial.print(F(","));
  Serial.print(prom); Serial.print(F(","));
  Serial.print(t4); Serial.print(F(","));
  Serial.print(experimentElapsedTimeSeconds); Serial.print(F(","));
  Serial.println(relay_state == HIGH ? F("ON") : F("OFF")); 
  delay(1000); // Send data every second
}
