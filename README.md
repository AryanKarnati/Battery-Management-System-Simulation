# Battery-Management-System-Simulation
This project is a C-based simulation of a multi-cell Battery Management System (BMS). The goal is to replicate the essential tasks a real BMS performs in electric vehicles and energy storage systems: estimating state-of-charge (SoC), monitoring voltage and temperature, modeling aging, and preparing for fault handling.

Instead of relying on hardware, this simulator models the physics of a battery pack virtually. It’s designed to be lightweight, portable, and easy to extend — making it useful for both educational purposes and early-stage algorithm testing.

## 🔍 What the Simulator Does

The simulator creates a **virtual battery pack** composed of multiple cells. At each time step, it updates the state of each cell using physics-based models:

### ⚡ State of Charge (SoC) Estimation
- Tracks charge in/out using **coulomb counting**  
- Includes a **charge efficiency factor**  

### 🔋 Open Circuit Voltage (OCV) Modeling
- Voltage depends on **SoC × Temperature**  
- Uses **bilinear interpolation** across lookup tables  

### 🌡️ Thermal Model
- Cells heat up from **I²R losses**  
- Heat transfer occurs between **adjacent cells** and the **environment**  
- Includes **temperature clamping** for realistic min/max ranges  

### ⏳ Aging Model (Placeholder)
- Tracks **calendar aging** in hours  
- Can be extended to **cycle-based degradation**  

### ⚠️ Fault Injection Hooks
- Framework for simulating:  
  - Over-voltage (OV)  
  - Under-voltage (UV)  
  - Over-temperature (OT)  
  - Under-temperature (UT)  

## 📈 Why This Matters

In real systems, a **Battery Management System (BMS)** is responsible for:  
- 🛑 Preventing dangerous conditions (thermal runaway, over-discharge)  
- 🔋 Estimating remaining energy (**SoC**) and lifetime (**SoH**)  
- ⚖️ Balancing cells for safety and longevity  

This simulator abstracts those same principles into a **numerical C program**, letting you visualize how **SoC, voltage, and temperature** evolve over time under a given load current.

### Example: Constant Discharge Current
- 🔽 **SoC decreases steadily**  
- 📉 **Voltage sags** (due to both OCV curve and internal resistance)  
- 🌡️ **Temperature rises** (from heat generation)  

### Fault Conditions (Future Hooks)
- ⚠️ Over-temperature (**OT**)  
- ❄️ Under-temperature (**UT**)  


