# Final Checkups for VESC-based ESC

2. Use a thermal camera to check for unexpected hot spots during operation at low power.
3. Verify deadtime settings in firmware/configuration to prevent shoot-through:
    - Connect oscilloscope to high and low gates. Make sure the deadtime is sufficient to prevent overlap.
      ![](https://i.imgur.com/ziRLdyr.png)
    - Make sure phase voltage does not spike too much
      ![](https://i.imgur.com/LvjBbHq.png)
4. Double pulse test:
    - Clean the board and ensure no debris or solder balls are present.
    - Connect one probe to phase 1 and another to output of current sensor.
    - `double_pulse 100 10 5 10` - Preface, first on time, off time, second on time
    - gradually increase the voltage and time on for the first pulse looking out for issues
    - Check for double pulses on the high side gate.
      ![](https://i.imgur.com/eOoGuC0.png)
6. Run foc_openloop_test to verify motor operation:
    - Set the test to a low current (e.g., 5A) and observe motor behavior.
    - Ensure the motor spins smoothly without excessive noise or vibration.
    - Check for any abnormal current spikes or temperature increases.
4. Calibrate current sensors using VESC Tool or relevant software, confirm accurate readings.
7. Review all configuration parameters before full-power operation.

