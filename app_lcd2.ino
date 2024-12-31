#include <ThingSpeak.h>                             // Add ThingSpeak library
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>                                    // Include the Wire library for I2C communication
#include <NTPClient.h>                               // Include NTP Client for time
#include <WiFiUdp.h>                                 // Include WiFi UDP for NTP

LiquidCrystal_I2C lcd(0x27, 16, 2);                 // Initialize LCD with I2C address 0x27 and size 16x2
WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); // IST Timezone Offset: 19800 seconds

unsigned long counterChannelNumber = 2713621;       // Channel ID for ThingSpeak
const char * myCounterReadAPIKey = "RKRQSFPZ1XZD1JEW";  // Read API Key for ThingSpeak
const int FieldNumber1 = 1;                         // The field you wish to read from the channel

String presentStr, previousStr = " ";
unsigned long lastMessageTime = 0;                  // To track the time when data was received
bool isDataDisplayed = false;

const int buzzerPin = D5; // Define the buzzer pin

void setup()
{
  Serial.begin(115200);
  
  // Initialize I2C communication for the LCD
  Wire.begin();
  lcd.begin(16, 2);            
  lcd.init();              
  lcd.backlight();         

  lcd.setCursor(0, 0);     
  lcd.print("Initializing");    
  
  delay(500);
  
  // Connect to WiFi
  WiFi.begin("Redmi 9 Power", "shraddha");  // Replace with your WiFi SSID and password
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected to WiFi, IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Initialize NTP Client
  timeClient.begin();
  
  // Initialize the buzzer pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{
  timeClient.update(); // Update the time from NTP server
  
  // Read data from ThingSpeak field
  presentStr = ThingSpeak.readStringField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  
  // Check if new data is received
  if (presentStr != "" && presentStr != previousStr)
  {
    displayData(presentStr);          // Display the received data
    lastMessageTime = millis();       // Record the time of receiving data
    isDataDisplayed = true;
    previousStr = presentStr;         // Update previous string
  }
  
  // If no new data is received and 15 seconds have passed, show the clock
  if (isDataDisplayed && millis() - lastMessageTime > 15000)
  {
    isDataDisplayed = false;          // Reset the flag
    lcd.clear();
  }
  
  // Show the clock if no data is displayed
  if (!isDataDisplayed)
  {
    displayClock();                   // Display the clock
  }

  delay(1000);  // Delay to avoid spamming the server
}

void displayData(String data)
{
  lcd.clear();                           // Clear the screen
  if (data.length() > 16)
  {
    String line1 = data.substring(0, 16);   // Get the first 16 characters
    String line2 = data.substring(16);     // Get the remaining characters
    lcd.setCursor(0, 0);
    lcd.print(line1);                      // Display first line
    lcd.setCursor(0, 1);
    lcd.print(line2);                      // Display second line
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print(data);                       // Display data on the first line
  }
  Serial.println(data);                    // Debug output
  
  // Turn on the buzzer for 5 seconds when new data is received
  digitalWrite(buzzerPin, HIGH);           // Turn on buzzer
  delay(5000);                             // Keep the buzzer on for 5 seconds
  digitalWrite(buzzerPin, LOW);            // Turn off buzzer
}

void displayClock()
{
  lcd.setCursor(0, 0);                     // Set cursor to the first line
  lcd.print("Time: ");
  lcd.print(timeClient.getHours());        // Display hours
  lcd.print(":");
  lcd.print(timeClient.getMinutes());      // Display minutes
  lcd.print(":");
  lcd.print(timeClient.getSeconds());      // Display seconds
}