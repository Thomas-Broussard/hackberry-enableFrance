### Flash the Hackberry board with XLoader

Xloader is a utility for flashing a microcontroller from the Arduino family from an .hex file.

It will allow you to quickly load the latest stable software in your Hackberry Hand.

### How to flash the board

1. Run **_utilities/Xloader/Xloader.exe_** file. The XLoader windows opens:

![image1](https://user-images.githubusercontent.com/26286587/59448174-e4bb3c00-8e04-11e9-842a-49d434ada5df.png)

2. Select the file to flash, in **_hex_files/_** directory

![image2](https://user-images.githubusercontent.com/26286587/59447896-6068b900-8e04-11e9-91d2-6cda80b670f5.png)

_Choose the file corresponding to the hand you wish to achieve (**right_hand** or **left_hand**)_


3. Enter the following parameters : 
* Device : **Duelmilanove/Nano(ATmega328)**
* COM port : the COM port on which your board is connected (here, COM4)
* Baud rate : **57600**

![image3](https://user-images.githubusercontent.com/26286587/59448299-20ee9c80-8e05-11e9-9782-aec88c4c1b5c.png)

4. Click **Upload** to flash your board and wait

![image4](https://user-images.githubusercontent.com/26286587/59448480-7e82e900-8e05-11e9-9363-9ef9e5189862.png)

5. Your Hackberry board is now flashed and ready to run ! 

![image5](https://user-images.githubusercontent.com/26286587/59448538-affbb480-8e05-11e9-82ab-b324e5411535.png)




