ThingSpeak Data Sender App

This app allows users to input data, which is then sent to a ThingSpeak server and displayed on an I2C LCD connected to an ESP8266. It facilitates real-time communication between a mobile app and a physical display.

Features

User Input: Enter custom data through a text input field.

Data Transfer: Sends data to ThingSpeak via HTTP requests.

ESP8266 Integration: Displays the received data on an I2C LCD.

Real-Time Updates: The ESP8266 fetches the latest data from ThingSpeak and displays it.


Requirements

MIT App Inventor: Used to build the mobile app.

ThingSpeak Account: Create a ThingSpeak channel to send and store the data.

ESP8266: To fetch data from ThingSpeak and display it on the LCD.

16x2 I2C LCD: Display the data on the physical screen.


Setup Instructions

1. App Configuration

Open the MIT App Inventor platform and import the provided project.

Set up the HTTP request block to send the user input to the ThingSpeak server. Replace the placeholder API key with your ThingSpeak channel's API key.


2. ThingSpeak Setup

Create an account on ThingSpeak and create a channel.

Note down the Channel ID and Write API Key for use in the app.


3. ESP8266 Configuration

Load the provided ESP8266 code into your ESP8266 device.

Ensure the ESP8266 is connected to your Wi-Fi network and able to fetch data from ThingSpeak.

Connect the I2C LCD to the ESP8266 as per the wiring instructions.


4. Test the App

Open the app on your Android device.

Enter some data and press the submit button.

Verify that the data appears on the I2C LCD after being fetched from ThingSpeak.


Code Explanation

1. MIT App Inventor App:

The app collects user input and sends it to the ThingSpeak server using the Web component and the ThingSpeak API.


2. ESP8266 Code:

The ESP8266 fetches data from the ThingSpeak channel and displays it on the LCD. It also checks if new data is received and updates the display accordingly.


Troubleshooting

No Data Displayed on LCD: Check the ThingSpeak channel for updates and ensure the ESP8266 is correctly fetching data.

App Not Sending Data: Ensure that the correct API key is configured and the ThingSpeak channel is accepting data.
