# SS-PCMs-heatsink: Evaluation of Imidazolium Ionenes as Solid-Solid Phase Change Materials for Heat Sinks

## Overview

This repository contains the Arduino code used to control the experimental setup and acquire data for the study titled "Evaluation of Imidazolium Ionenes as Solid-Solid Phase Change Materials for Heat Sinks." The main objective of this research is to evaluate the performance of imidazolium ionenes as solid-solid phase change materials (SS-PCMs) to enhance heat dissipation in electronic devices.

The miniaturization and increased power of electronic devices have led to higher heat generation, which in turn affects their lifespan. This work explores how imidazolium ionenes, featuring solid-solid transitions, can improve the capacity of current heat sinks. The synthesized ionenes demonstrated an average reduction of 9 °C in the operating temperature of the experimental device compared to the device without ionenes.

## Associated Publication

This code is part of the research paper:

Arriaza-Echanes, C., Krüger Carrasco, G.I., Comesaña-Gándara, B., Terraza, C., Sanhueza, L., & Ortiz, P.A. (2025). “Evaluation of Imidazolium Ionenes as Solid-Solid Phase Change Materials for Heat Sinks.” *Polymers*. **[In Review]**

## Hardware Requirements

The experimental setup (described in Figure 2 and 3 of the manuscript) uses the following main electronic components:

* **Microcontroller**: Arduino Mega 2560
* **Temperature Sensors**: Four Type K thermocouples with amplifier modules like MAX6675 (as discussed for the code). Three for measurement and one for control.
* **Heat Source**: 12W PTC heating plate (capable of reaching 120 °C)
* **Power Supply**: Adjustable LM317 (28 V; 2 A / 220 V) for the heating plate
* Connection wires, breadboard (optional).

## Software Requirements

* **Arduino IDE**: Version 1.8.x or higher.
* **Arduino Libraries**:
    * `max6675.h` (if using MAX6675 modules for the thermocouples). You can install this from the Arduino IDE's library manager.

## Code Description (`heatsink_datalogger.ino`)

The Arduino sketch (`.ino` file) provided in this repository is designed to:

1.  **Control the experiment's operating time**: Manages the heating and cooling cycle.
    * **Stage 1 (Heating)**: The experimental setup is heated to achieve a constant sample temperature of 40 °C for 30 minutes (1800 seconds).
    * **Stage 2 (Cooling)**: Allows the system to cool naturally for 60 minutes (3600 seconds) after the heat supply is suspended.
2.  **Data Acquisition**: Reads the temperature from the four Type K thermocouples.
3.  **Data Logging**: Sends temperature data and system status (e.g., relay state, elapsed time) via the serial port for later analysis. The output format is CSV.

## Data Output Format (CSV)

The Arduino script sends data via the serial monitor in the following CSV format:

`T_1(C),T_2(C),T_3(C),PROM_T(C),T_4(C),TotalTime(s),RelayState`

Where:
* `T_1, T_2, T_3`: Temperatures from the measurement thermocouples in °C.
* `PROM_T`: Average of T1, T_2, T_3 in °C.
* `T_4`: Temperature from the control thermocouple in °C.
* `TotalTime(s)`: Total elapsed time of the experiment in seconds.
* `RelayState`: State of the relay controlling the heat source (`ON`/`OFF` or `HIGH`/`LOW`).

## Instructions for Use

1.  **Hardware Setup**:
    * Assemble the experimental device as described in Section 2.4 and Figures 2 & 3 of the manuscript.
    * Connect the thermocouples (with their MAX6675 modules, if used) to the Arduino Mega 2560 according to the pins defined in the code.
    * Connect the PTC heating plate to the relay, and the relay to the Arduino and the LM317 power supply.
2.  **Software and Code**:
    * Open the `.ino` file from this repository with the Arduino IDE.
    * Ensure you have the `max6675.h` library (or any other required libraries) installed.
    * In the IDE, select "Arduino Mega 2560" as the board and the correct COM port.
3.  **Running the Experiment**:
    * Upload the sketch to the Arduino.
    * Open the Arduino IDE's Serial Monitor (set to 9600 baud) to view and log the data.
    * The experiment will start automatically, following the defined heating and cooling cycle.

## How to Cite

If you use this code or data from this repository in your research, please cite our publication:

Arriaza-Echanes, C., Krüger Carrasco, G.I., Comesaña-Gándara, B., Terraza, C., Sanhueza, L., & Ortiz, P.A. (2025). “Evaluation of Imidazolium Ionenes as Solid-Solid Phase Change Materials for Heat Sinks.” *Polymers*. [In Review]

You can also cite this repository directly:

Arriaze-Echanes C. *et al.* (2025). *SS-PCMs-heatsink: Code for the evaluation of imidazolium ionenes as SS-PCMs in heat sinks*. https://github.com/KrugerGK/SS-PCMs-heatsink

## License

This project is licensed under the terms of the MIT License. See the `LICENSE` file for more details.

## Authors and Contact

* Carolina Arriaza-Echanes
* Gabriel I. Krüger Carrasco
* Bibiana Comesaña-Gándara
* Claudio Terraza
* Loreto Sanhueza
* Pablo A. Ortiz (Corresponding Author)

For any inquiries, please contact Pablo A. Ortiz or Carolina Arriaza-Echanes.

---
Applied Nanotechnology Center, Faculty of Sciences, Engineering and Technology, Universidad Mayor, Santiago, Chile.
