# Battery-Management-System-Simulation
This project is a C-based simulation of a multi-cell Battery Management System (BMS). The goal is to replicate the essential tasks a real BMS performs in electric vehicles and energy storage systems: estimating state-of-charge (SoC), monitoring voltage and temperature, modeling aging, and preparing for fault handling.

Instead of relying on hardware, this simulator models the physics of a battery pack virtually. It’s designed to be lightweight, portable, and easy to extend — making it useful for both educational purposes and early-stage algorithm testing.


🔍 What the Simulator Does

The program creates a virtual battery pack composed of multiple cells. At each time step, the simulator updates the state of each cell by applying physics-based models:

State of Charge (SoC) Estimation

Uses coulomb counting to track how much charge has flowed in/out.

Includes a simple charge efficiency factor.

Open Circuit Voltage (OCV) Modeling

Each cell’s voltage is determined by its SoC and temperature.

Uses bilinear interpolation across lookup tables (SoC × Temp).

Thermal Model

Cells heat up based on current and internal resistance (I²R losses).

Heat transfer occurs between adjacent cells and with the environment.

Includes clamping for realistic min/max operating temperatures.

Aging Model (Placeholder)

Tracks calendar aging in hours.

Can be extended to cycle-based degradation.

Fault Injection Hooks

Framework for simulating faults such as:

Over-voltage (OV)

Under-voltage (UV)

)

📈 Why This Matters

In real systems, the BMS is responsible for:

Preventing dangerous conditions (thermal runaway, over-discharge).

Estimating remaining energy (SoC) and lifetime (SoH).

Balancing cells for safety and longevity.

This simulator abstracts those same principles into a numerical C program, letting you see how SoC, voltage, and temperature evolve over time under a given load current.

For example, a constant discharge current results in:

SoC decreasing steadily

Voltage sagging (due to both OCV curve and internal resistance)

Temperature rising (from heat generation)

Over-temperature (OT)

Under-temperature (UT)
