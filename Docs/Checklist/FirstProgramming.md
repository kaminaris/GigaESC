# First Programming Checklist for VESC-based ESC

1. Confirm essential power rails 3.3V are present and stable.
2. Connect the programming header SWD to the microcontroller.
3. Ensure the board is powered via a current-limited supply (1-3A max).
4. Use either black magic probe or ST-Link for programming.
5. Load the appropriate firmware onto the ESC.
6. Connect the ESC to a computer via USB and connect with vesc tool.
7. **DO NOT forget to upload bootloader first if it is not already present.**
8. Monitor for excessive current draw or heating during programming. 
It should be around 0.04A

