# IPRO - TRUE Shot
###### IIT IPRO - Basketball Shooting Sleeve

Measures bend of the wrist  using a Flex Sensor (4.5") along with the motion of the hand using the built-in accelerometer in the Tiny Tile (Intel Curie - Arduino 101).


### Resources

| Name | Description | Link |
| ---- | ----------- | ---- |
| ESP Graphing Software | Easily graphs and trains model based on the XYZ of the accelerometer | [GitHub Repo](https://github.com/damellis/ESP) |
| Visual Studio 2015 | Need the 2015 version for openFramework to be compatible with ESP Graphing Software | [Download](https://go.microsoft.com/fwlink/?LinkId=532606&clcid=0x409) |
| nRF Toolbox App | Used with the Bluetooth module in Arduino 101 to communicate with using UART | [App Page](https://www.nordicsemi.com/eng/Products/Nordic-mobile-Apps/nRF-Toolbox-App)
| DRV2605L Waveform Effects List | Page 60 has all the IDs for each of the 123 effects | [TI Manual](http://www.ti.com/lit/ds/symlink/drv2605l.pdf)

### Sketches

| Sketch Name | Description |
| ----------- | ----------- |
| accelData.ino | LSM9DS0 Accelerometer - Displays XYZ when physical button pressed |
| lsmCalibration.ino | Calibration for LSM9DS0 and Debug XYZ |
| rotate3D.ino | 3D Model Gyroscope using LSM9DS0 with Processing IDE Code |
| sleeveDev.ino | Proof of Concept using LSM9DS0 |
| trueShot-dev.ino | Proof of Concept using Tiny Tile with Bluetooth and Haptic Feedback Demo |

![TRUEShot Fritzing](http://i.imgur.com/YB74Trg.png)
