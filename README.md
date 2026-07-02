# EcoLight Maestro: Time & Intensity Adaptive Street Light Automation

## Abstract

**EcoLight Maestro** is an embedded systems project developed to automate street lighting by combining **real-time scheduling** with **ambient light intensity sensing**. The system intelligently controls street lights based on the current time and surrounding light conditions, ensuring energy-efficient operation while reducing unnecessary power consumption. The project is built around the **LPC2148 ARM7 Microcontroller**, which continuously monitors time using the on-chip **Real-Time Clock (RTC)** and measures ambient light intensity through an **LDR (Light Dependent Resistor)** connected to the ADC.

During nighttime hours (6:00 PM to 6:00 AM), the microcontroller checks the light intensity. If the measured light level falls below a predefined threshold, the street light LEDs are automatically switched ON. If sufficient ambient light is detected, the LEDs remain OFF, preventing unnecessary energy usage. During daytime hours, the system only displays the current date, time, and day on the LCD without controlling the street lights.

To maintain accurate operation, the project includes an RTC configuration feature. By pressing an external interrupt switch, the user can access a menu-driven interface displayed on the LCD. Using a keypad, the user can edit the RTC parameters such as hours, minutes, seconds, date, month, year, and day. All entered values are validated to ensure they fall within valid ranges before updating the RTC registers.

The project integrates several embedded system concepts, including Real-Time Clock programming, Analog-to-Digital Conversion (ADC), external interrupts, keypad interfacing, LCD display control, and sensor-based automation. The firmware is developed in **Embedded C** using the **Keil µVision IDE** and programmed into the LPC2148 microcontroller using **Flash Magic**.

EcoLight Maestro provides a reliable, low-cost, and energy-efficient solution for automatic street light control. By combining time-based scheduling with real-time light intensity detection, the system minimizes electricity consumption, extends the lifespan of lighting equipment, and reduces manual intervention. This project is suitable for smart city applications, highways, residential areas, industrial campuses, parking lots, and public infrastructure, demonstrating the practical use of embedded systems in intelligent energy management and sustainable automation.
