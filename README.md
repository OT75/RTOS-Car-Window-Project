# Power Window Control System using Tiva C and FreeRTOS

The Power Window Control System is implemented using Tiva C running FreeRTOS. The scope of the project includes the implementation of the front passenger door window with control panels for both the passenger and the driver. The system incorporates limit switches to restrict the window motor's movement within the top and bottom limits of the window. Additionally, obstacle detection is implemented using a push button to indicate jamming.

![Screenshot 2024-02-17 184124](https://github.com/ShehabAdel99/-Power-Window-Control-System/assets/96583491/e8dd4586-77a6-4c30-a54b-d4069925090a)

## System Basic Features

- Manual Open/Close Function: Continuous pushing or pulling of the power window switch results in the window opening or closing until the switch is released.

- One Touch Auto Open/Close Function: Briefly pushing or pulling the power window switch fully opens or closes the window.

- Window Lock Function: Activating the window lock switch disables the opening and closing of all windows except the driver's window.

- Jam Protection Function: If foreign matter is detected during a one-touch auto close operation, the system automatically stops the power window and moves it downward for approximately 0.5 seconds to release the obstruction.

## Project Implementation


The system hardware includes the following components:

1) Tiva C: Microcontroller platform used for system control and management.

2) Limit Switches: Top and bottom limit switches are utilized to restrict the movement of the window motor.

3) DC Motor: Represents the operation of the window.

4) Push Buttons: Used for operating the window in both the passenger and driver sides.

5) ON/OFF Switch: Controls the locking of the passenger panel from the driver panel.

## Usage
To utilize the Power Window Control System:

1) Set up the Tiva C microcontroller platform with FreeRTOS.
2) Connect and configure the limit switches, DC motor, push buttons, and ON/OFF switch as per the system requirements.
3) Implement the necessary software logic to control the window functions, including manual open/close, one-touch auto open/close, window lock, and jam protection.
4) Ensure proper integration and communication between the hardware components and the Tiva C microcontroller.
5) Test the system thoroughly to verify the functionality of each feature and ensure proper operation.

## Authors
- Omar Tarek Mohamed
- Omar Mohamed Ibrahim Al Sayed
- Mohamed Hatem Zakaria
- Ibrahim Ashraf

