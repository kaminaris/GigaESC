# GigaESC - EPC2304

---

# ⚠️Please do not order before contacting me on discord️⚠️

this is a very hard board to solder requires:

- Good knowledge of microsoldering
- **A microscope**
- Hot air capable of reaching 450°C
- A very thin soldering iron tip
- An oscilloscope

## GaN Soldering procedure

Use 60/40 solder from a reputable source. Trying to use lead-free solder by hand will be extremely difficult. Using poor-quality products will also result in failure, and this applies to flux as well.

This board has 4 layers, so it can absorb a lot of heat. Using high-quality solder is essential because the board is very sensitive to cold joints.

Having a good soldering iron is crucial and can make the difference between success and failure.

To solder GaN mosfets i strongly recommend using soldering paste instead, everything else can be done with wire tin.

1. Apply solder paste with flux on the footprint.
2. Position the GaN mosfet in place.
3. Use hot air until the solder melts and the GaN device is securely in place, applying gentle pressure to ensure proper contact.
4. Remove any excess solder with a soldering iron.
5. Allow the solder to cool down.

**[Repeat]**

1. Heat the solder joint again with hot air.
2. Apply flux.
3. Use tweezers to gently swirl the MOSFET, ensuring each pad has an equal amount of solder.
4. Reposition the MOSFET properly.
5. Allow the solder to cool down.

**[Repeat until the GaN mosfet self-aligns perfectly.]**

**⚠️While doing soldering procedure, make sure there are no microblobs of solder underneath mosfets.**
This may take a couple of tries to get it right.

## Testing procedure

1. Check with a multimeter the following parameters:
    - Resistance between + and - terminals: Should be very high, nearly open loop.
    - Resistance between each phase to ground: Should be greater than 40 kOhms.
    - Resistance between each phase to VBat+: Should be in the megaohms range.
    - Phase comparison: Each phase should have similar resistance readings to the others.
    - Gate connection check: Ensure each gate connects to the main PL and PH lines (this can be verified from the top of the PCB).
2. If electrically everything seems fine, connect to the main board and turn on the VESC:
    - Error code check: If any error code appears, there may be an issue, most commonly cold joints.
    - Current offset measurement:
        - Measure current offsets before doing anything with the VESC. 
        - They should all be within +/-10 LSB and around 2070
         ![](https://i.imgur.com/1YrZJtV.png)
3. Connect the motor and measure its RL properties:
    - If you observe any abnormal values, such as very high inductance:
       - Check and fix any cold joints.
       - Use a multimeter to ensure each current sensor at idle is outputting about 1.65V.
       - Ensure each current sensor is receiving 5V.
4. Once any initial problems are resolved:
    - Set the current to the lowest possible value in FOC -> General and perform a full detection until all parameters are green and appear reasonable:
    ![](https://i.imgur.com/bXIzNDb.png)
    - If you have another VESC, compare results with it. It will depend on motor itself so do not compare them to mine.
    - Perform a short double pulse test, for example: double_pulse 100 10 5 10. Confirm both edges look okay and are not overshooting.
    - Perform the motor detection.
