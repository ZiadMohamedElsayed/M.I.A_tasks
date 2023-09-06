# Rotary Encoder Step Counter

## Introduction

This Arduino code interfaces with a rotary encoder to count steps and provides a simple demonstration of its functionality. In this document, we'll discuss the code, its functionality, and how to implement a LPF for the encoder.

## Code Overview

The provided Arduino code accomplishes the following tasks:

- Interfaces with a rotary encoder connected to pins `encoderPinA` and `encoderPinB`.
- Utilizes interrupts to detect changes in the encoder signal.
- Increments or decrements a counter based on the direction of rotation.
- Outputs the current count to the Serial monitor for testing.

### Code Structure

- `setup()` initializes the pins, attaches an interrupt to `encoderPinA`, and initializes Serial communication.
- `loop()` is intentionally left empty, as the main action takes place in the interrupt service.
- `updateEncoder()` is the interrupt service that handles encoder signal changes, updates the counter, and prints the count.

## Proper LPF Cutoff Frequency (fc)

### Specifications
- Encoder has 540 pulses per revolution.
- The tracked vehicle has three wheels, with only one motorized wheel, which has an encoder.
- The motorized wheel has a diameter of 40 cm.
- The maximum speed of WALL-E is 0.5 m/s.

### Design Steps

#### 1. Calculate Maximum Angular Speed
   - WALL-E's maximum speed is 0.5 m/s.
   - Wheel diameter (D) = 40 cm = 0.4 m.
   - Radius (r) = D / 2 = 0.4 m / 2 = 0.2 m.
   - Maximum angular speed (ω) in radians per second: ω = v / r, where v is the linear speed in m/s and r is the radius in meters.
   - ω = 0.5 m/s / 0.2 m = 2.5 rad/s.

#### 2. Calculate Maximum Encoder Pulse Frequency
   - The encoder produces 540 pulse per revolution.
   - Maximum frequency of encoder pulses (fmax) = (ω / (2π)) * PPR, where ω is the angular speed in radians per second, and PPR is the number of pulses produced by the encoder per revolution.
   - fmax = (2.5 rad/s / (2π)) * 540 ≈ 214.86 Hz.

#### 3. Determine Cutoff Frequency for LPF
   - To accurately capture the encoder pulses, have a cut-off frequency at least 7 to 10 times bigger than the maximum acceptable frequency.
   - fc ≈ 7 * 214.86 Hz ≈ 1.504 kHz.
  
## Conclusion

This Arduino code effectively interfaces with a rotary encoder to count steps and provides a basic framework for further development. To implement noise filtering the cutoff frequency (fc) for the low-pass filter should be approximately 1.504 kHz to effectively filter the encoder signal while capturing the desired information accurately.
Note that this is a rough estimation, and the actual filter design and components may vary based on the specific characteristics of the encoder and the desired filtering performance.
