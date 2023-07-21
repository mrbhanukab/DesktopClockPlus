# DesktopClockPlus

**DesktopClockPlus** is a creative ESP8266-based project that brings a smart desktop clock with an OLED display to life. This project combines real-time synchronization with Wi-Fi connectivity to provide essential time and date information along with additional useful features to enhance productivity and focus.

## How It Works

The DesktopClockPlus project utilizes an ESP8266 microcontroller to drive the OLED display and connect to available Wi-Fi networks. The code is organized into several sections, each serving specific functionalities:

1. **Libraries and OLED Display Configuration:** The necessary libraries, such as SPI, Wire, Adafruit_GFX, and Adafruit_SSD1306, are included to enable seamless communication with the OLED display. The OLED display is configured with the required properties, such as screen dimensions, reset pin, and I2C address.

2. **Wi-Fi Credentials:** The array `ssid[]` stores the names of Wi-Fi networks, and the array `password[]` stores the corresponding passwords. The variable `numNetworks` holds the total number of Wi-Fi networks available. Users can modify these arrays to add their Wi-Fi credentials.

3. **Date and Time Variables:** The variables `currentTime`, `currentMonthName`, `currentDay`, and `remainingDaysS` are used to store the current time, current month name, current day, and the number of remaining days to a specific target date, respectively. The project includes a countdown timer to track the days remaining until a target date (set as "2023-11-26" by default). Users can customize the target date for their specific use case.

4. **Wi-Fi Connection Function:** The `connectToWiFi()` function attempts to connect the ESP8266 to Wi-Fi using the stored credentials. It iterates through the available networks and displays the connection status on the OLED screen. If a connection is successful, it displays a connection message; otherwise, it attempts to connect to the next network. If none of the networks can be connected, it displays a failure message and restarts the ESP8266. This function streamlines the process of connecting the device to Wi-Fi networks without manual intervention.

5. **Setup Function:** The `setup()` function initializes the serial communication, OLED display, and NTPClient for time synchronization. It also displays an introductory message on the OLED screen, connects to Wi-Fi, and sets the time offset to the local time zone. Users can customize the introductory message or add additional setup steps, such as displaying a custom logo or connecting to a specific Wi-Fi network.

6. **Date and Time Update Function:** The `updateDateTime()` function retrieves the current time from an NTP server using the NTP client library. It formats the time as "HH: MM" and extracts the current month's name and day. Additionally, it calculates the number of remaining days to a specific target date (hardcoded as "2023-11-26"). This functionality allows users to track the days remaining until a significant event, such as an exam. Users can modify the target date and customize the date format according to their preferences.

7. **Display Functions:** The `display1()`, `display2()`, `display3()`, and `display4()` functions are responsible for displaying different screens on the OLED. They provide information such as the current date and time, remaining days to the target date, random motivational quotes, and icons indicating focus mode. These screens are shown sequentially, and each screen's information is updated periodically. Users can customize the display order, add more screens, or modify the screen content.

8. **Loop Function:** The `loop()` function is the main loop that continuously updates the date and time information, displays the screens sequentially, and clears the OLED display between screen transitions. This loop allows users to cycle through the different screens and access various information at regular intervals. Users can adjust the timing between screens and add additional functionalities within the loop to customize the user experience.

## Video Preview
https://github.com/mrbhanukab/DesktopClockPlus/assets/87383814/081f9c1b-b828-4813-a207-08e8b0db7658

[Or Watch it on Youtube](https://www.youtube.com/watch?v=ZybLtMQlZGE)
## How to Set Up DesktopClockPlus

1. **Clone the Repository:** Begin by cloning the DesktopClockPlus repository from [GitHub](https://github.com/mrbhanukab/DesktopClockPlus) to your local machine.

2. **Open the Arduino IDE:** Ensure that you have the Arduino IDE installed on your computer. Open the `DesktopClockPlus.ino` file in the Arduino IDE.

3. **Install Required Libraries:** In the Arduino IDE, go to "Sketch" > "Include Library" > "Manage Libraries." Search for the required libraries (Adafruit_GFX, Adafruit_SSD1306, ESP8266WiFi, WiFiClient, NTPClient, WiFiUdp) and click "Install" for each one.

4. **Configure Wi-Fi Credentials:** Open the `DesktopClockPlus.ino` file and modify the `ssid[]` and `password[]` arrays with the names and passwords of your Wi-Fi networks. Add or remove networks as needed using the provided format.

5. **Customize Target Date:** If you want to track the days remaining until a specific date other than "2023-11-26," update the `targetYear`, `targetMonth`, and `targetDay` variables in the `updateDateTime()` function.

6. **Upload the Code:** Connect your ESP8266 to your computer and select the correct board and port in the Arduino IDE. Then, click "Upload" to flash the code onto the ESP8266.

7. **Assembly:** If you haven't done so already, connect the OLED display to the ESP8266 following the appropriate connections. The wire path for the connection ([source](https://lastminuteengineers.com/oled-display-esp8266-tutorial/))<br> ![The wire path for the connection](https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/Fritzing-Wiring-OLED-Display-with-ESP8266-NodeMCU.png)

8. **Power Up:** Power up the ESP8266, and you should see the DesktopClockPlus in action on the OLED display.

## Customization

DesktopClockPlus offers several areas for customization:

- **Wi-Fi Credentials:** Add or remove Wi-Fi networks in the `ssid[]` and `password[]` arrays.

- **Target Date:** Adjust the `targetYear`, `targetMonth`, and `targetDay` variables in the `updateDateTime()` function to track a different target date.

- **Introductory Message:** Modify the setup message displayed in the `setup()` function to personalize the startup sequence.

- **Display Content:** Customize the text and icons shown on each screen in the `display1()`, `display2()`, `display3()`, and `display4()` functions.

## Credits

DesktopClockPlus is created by [mrbhanukab](https://github.com/mrbhanukab). Feel free to contribute, report issues, or provide suggestions on the GitHub repository.

For more information on OLED display with NodeMCU, visit [lastminuteengineers.com](https://lastminuteengineers.com/oled-display-esp8266-tutorial/).

Get DesktopClockPlus and transform your workspace into a productivity-enhancing hub! Stay focused, organized, and motivated with this smart desktop clock companion.

[![github](https://img.shields.io/badge/Github-mrbhanukab-%23333?style=for-the-badge&logo=GitHub&logoColor=white)](https://github.com/mrbhanukab)<br>
[![twitter](https://img.shields.io/badge/Twitter-mrbhanuka-%2300acee?style=for-the-badge&logo=Twitter&logoColor=white)](https://twitter.com/mrbhanuka)"
