# MPU6050 Gyroscope Interface and Noise Filtering

## Introduction
This Arduino code interfaces with the MPU6050 Inertial Measurement Unit (IMU) to retrieve the Yaw angle. It also includes a calibration function to improve accuracy. In this document, we'll discuss the code, its functionality, and how to configure filtering for a noisy environment.

## Code Overview
The provided Arduino code accomplishes the following tasks:
- Communicates with the MPU6050 IMU using the I2C protocol.
- Reads gyroscope data (X, Y, and Z axes) from the MPU6050.
- Applies calibration offsets to the gyroscope data.
- Calculates the Yaw angle based on the gyroscope data.
- Ensures that the Yaw angle wraps around to stay within the range of 0 to 360 degrees.
- Prints the current Yaw angle.

### Code Structure
- `setup()` initializes the communication, sets the gyroscope sensitivity and DLPF bandwidth, and performs gyro calibration.
- `loop()` continuously reads gyro data, calculates the Yaw angle, and prints it.
- `readGyroData()` reads gyroscope data and applies calibration offsets.
- `calculateYawAngle()` calculates the Yaw angle and ensures it stays within the 0-360 degree range.
- `calibrateGyro()` performs gyro calibration by collecting samples and calculating offsets.
- `Delay()` is a custom delay function.

## Noise Filtering
If the MPU6050 sensor is in a noisy environment, it's essential to implement filtering to reduce noise interference. The MPU6050 has a Digital Low-Pass Filter (DLPF) that can be configured to adjust the cutoff frequency for noise reduction.

- By default, the DLPF bandwidth is set to 256 Hz. It's suitable for most applications but may not be sufficient in a noisy environment.
- You can adjust the DLPF bandwidth by modifying the `dlpfSetting` variable in the `setup()` function.
- The `dlpfSetting` values correspond to different cutoff frequencies: 0 = 260Hz, 1 = 184Hz, 2 = 94Hz, 3 = 44Hz, 4 = 21Hz, 5 = 10Hz.
- Lowering the DLPF bandwidth (higher `dlpfSetting`) increases filtering and reduces noise but will also increase response time.

The choice of DLPF setting should be based on the trade-off between noise reduction and sensor response time. Here are some general guidelines:

- Low Noise Priority: If your application is in a very noisy environment, you may want to use a lower DLPF setting to reduce noise interference. Settings 4 or 5 (21Hz or 10Hz) can be suitable for such cases. However, keep in mind that lower DLPF settings will increase the response time of the sensor.
- Balanced Approach: Setting 3 (44Hz) is often a good compromise between noise reduction and response time. It provides reasonable noise filtering while maintaining a relatively fast sensor response.
- Fast Response Priority: If your application requires a quick response time and noise is not a significant concern, you can choose a higher DLPF setting, like 0 or 1 (260Hz or 184Hz). This will result in minimal filtering but faster sensor response.
- Experimentation: The best choice may depend on your specific noise conditions and performance requirements. It's a good practice to experiment with different DLPF settings in your actual environment to find the optimal balance.

## Conclusion
This Arduino code interfaces with the MPU6050 sensor, retrieves the Yaw angle, and includes a calibration function. It can be configured to filter noise by adjusting the DLPF bandwidth based on your specific noise conditions. Experiment with different settings to find the right balance between noise reduction and sensor response time for your application.
