
# Automated Cat Feeder

This repository contains the code and documentation for an automated cat feeder. The feeder is designed to dispense food at scheduled times and when the cat is detected at the feeding portal. It uses various hardware components controlled by an ESP32 microcontroller.

## Table of Contents

- [Hardware Components](#hardware-components)
- [Phases and Steps](#phases-and-steps)
- [Function List](#function-list)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Hardware Components

1. **Main body (Reservoir and Feed Screw)**
   - **ESP32**: Central processor that communicates with modules and controls the feeding mechanism via I2C.
   - **Stepper Motor 1**: Controls rotation of the reservoir.
   - **Stepper Motor 2**: Controls rotation of the feed screw.
   - **End stop**: Indicates the home position of Stepper Motor 1.
   - **RTC**: Keeps track of time.

2. **Module/Food Bay**
   - **RFID Reader**: Detects the cat's presence.
   - **Servo Motor**: Opens the door.
   - **Tiny1614 IC**: Manages local operations and communicates with the ESP32 via I2C.

## Phases and Steps

### Phase 1: Daily Initialization and Calibration

**Event**: Start of Day  
**Trigger**: ESP32 starts the day (e.g., at midnight).  
**Actions**:
1. **Calibrate the reservoir position**:
   - Move the reservoir anti-clockwise until it hits the end stop switch.
   - Set this position as position 0.
   - Subsequent positions will be calculated from this point.
2. **Scheduled Feeding Check**:
   - Check log to see if the cat has entered before feed time; if not, send notice to the owner.
   - At scheduled times (e.g., 9 a.m. and 6 p.m.), check if it's time to feed the cat.
   - Calculate the required amount of food.
   - Send signals to Stepper Motor 1 to rotate the reservoir to the correct position.
   - Activate Stepper Motor 2 to dispense the food.
   - Log the feeding event.

### Phase 2: Cat Detection and Feeding

**Event**: Cat Detection  
**Trigger**: Cat detected at the food bay.  
**Actions**:
1. **Validate Cat Presence**:
   - Detect cat via RFID Reader.
   - Validate cat's information.
2. **Dispense Food**:
   - Open the door using the Servo Motor. (food was served at scheduled times)
   - Log the cat's entry time and RFID tag information.

## Function List

### Initialization Functions

```cpp
void calibrateReservoir(); // Calibrates the reservoir position
void initializeRTC(); // Initializes the RTC
void loadFeedingSchedule(); // Loads the feeding schedule
void checkFeedingSchedule(); // Checks the feeding schedule at 9 a.m. and 6 p.m.
void checkIfAlreadyAte(); // Checks if the cat has already eaten before the second feed of the day
```

### Cat Detection Functions

```cpp
void detectCat(); // Detects when a cat is present
void validateCatInfo(); // Validates the detected cat's information
void logCatEntry(); // Logs the cat's entry time and RFID tag information
void openDoor(); // Sends command to Tiny1614 to open the door
```

### Feeding Mechanism Functions

```cpp
void determineFoodAmount(); // Determines the required amount of food
void rotateReservoir(); // Rotates the reservoir to the correct position
void rotateFeedScrew(); // Rotates the feed screw to dispense food
```

## Installation

To set up the automated cat feeder, follow these steps:

1. Clone the repository:

```bash
git clone https://github.com/yourusername/automated-cat-feeder.git
cd automated-cat-feeder
```

2. Install dependencies:
   - Install the necessary libraries for the ESP32 and Tiny1614. This can be done using the Arduino Library Manager or PlatformIO, depending on your development environment.

3. Upload the code:
   - Connect your ESP32 and Tiny1614 to your computer and upload the respective codes to each microcontroller.

## Usage

Once the system is set up and the code is uploaded, the automated cat feeder will:
- Initialize and calibrate the reservoir position at the start of each day.
- Check the feeding schedule at 9 a.m. and 6 p.m.
- Detect the presence of the cat using the RFID reader.
- Open the door to the food bay when the cat is detected.
- Dispense the required amount of food based on the feeding schedule.

## Contributing

Contributions are welcome! If you have any suggestions or improvements, please create a pull request or open an issue.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
