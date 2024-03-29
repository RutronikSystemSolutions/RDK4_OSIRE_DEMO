# RDK4 OSIRE® E3731i Demonstration

 ams OSIRE® E3731i LED stripe and RDK4 wiring diagram.<img src="images/rdk4_osire_diagram.jpg" style="zoom:90%;" />

**NOTE:** The SB55 has to be removed and SB54 has to be shorted on the bottom side of RDK4 to enable the  Arduino +5V supply from USB-C KitProg3 terminal. It will hold current up to 400 mA only.

## Requirements

- [ModusToolbox™ software](https://www.cypress.com/products/modustoolbox-software-environment) v3.1
- [RDK4 Rev1.](https://www.rutronik24.com/product/rutronik/rdk4/20820197.html)
- ams OSIRE® E3731i LED stripe with 20 LEDs on it. (RUT: LEDATV3196) link: TBD 
- [single LED](https://www.rutronik24.com/product/ams+osram/q65113a6250/21371365.html) 
- [amsOSRAM GUI Access: ](https://www.osram.com/apps/downloadcenter/os/?path=%2Fos-files%2FSoftware%2FP002%2F) Please download the zip-file: P0002_F0003_20_12_2022. To un-zip, please use the following password: **qygy93Nf4x7vBxP8rnvS**
- [AppNote OSIRE® E3731i](https://ams-osram.com/products/multi-chips/multi-color-leds/osram-osire-e3731i-krtbi-d2lm31-31)

## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>



1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox&trade; Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool.

2. Pick a RDK4 kit supported by the code example from the PSoC&trade; 4 BSPs list shown in the **Project Creator - Choose Board Support Package (BSP)** dialogue.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialogue, choose the RDK4_OSIRE_DEMO example in the Peripherals category by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>

### Operation

The firmware example uses KitProg3 UART to connect with ams OSRAM RGBi-GUI-MicroController software. Additionally, it has stand-alone modes that enable the control and demonstration of OSIRE LEDs. 

- Connect the LED Stripe to the RDK4 as it is shown in a picture at the top of this document.

- Connect the PC to your RDK’s USB KitProg3 terminal.

- Programm the firmware.

- All the detected LEDs will start changing colours – it is a default startup mode.

- Load the ams OSRAM RGBi-GUI-MicroController software.

  <img src="images/amsOSRAM GUI startup.jpg" style="zoom:80%;" />

  <img src="images/board_select.jpg" style="zoom:150%;" />

- Select the COM Port where the RDK4 KitProg3 is connected.

  <img src="images/port_select.jpg" style="zoom:100%;" />

- Start working with LEDs from the first **INIT_DIR** command. If you need to set all the LEDs at once, please set the address to 0 – it is the broadcasting address. 

  <img src="images/gui_ready.jpg" style="zoom:80%;" />

If you wish to use the demo without PC software, you may use the embedded example modes. The modes are switched using the CapSence buttons CSB1 and CSB3. NOTE: CapSense Buttons are sensitive, please be accurate while touching them.  

- By default, the „MinimalRGB“ demo is always engaged from the startup.
- Touch the CSB1 once and you will get into „ColorCorrectionStripe“ mode. The USER LED on the RDK4 will start blinking in YELLOW. From this point, the user needs to decide if he needs to read all the OTP memory from every OSIRE LED and store it in the microcontroller memory or not. If you are running this demo for the first time – this is necessary. So to do that please touch the CSB3 button gently and wait until the USER LED starts blinking in GREEN. Press the CSB1 now and the demo will start. If the memory has been saved previously, you only need to keep pressing the CSB1 and you will get to this mode finally.
- If you touch the CSB1 further – you will get into the „RunningLights“ mode. You will see how the stripe is changing the colours sequentially for every LED, they are updated once per 10 milliseconds. 
- By touching and holding the CSB1 will get you back to the „MinimalRGB“ demo.



### Debugging

If you successfully have imported the example, the debug configurations are already prepared to use with a the KitProg3 or MiniProg4. Open the ModusToolbox™ perspective and find the Quick Panel. Click on the desired debug launch configuration and wait for the programming to complete and the debugging process to start.

<img src="images/debug_start.jpg" style="zoom:100%;" />

## Legal Disclaimer

The evaluation board including the software is for testing purposes only and, because it has limited functions and limited resilience, is not suitable for permanent use under real conditions. If the evaluation board is nevertheless used under real conditions, this is done at one’s responsibility; any liability of Rutronik is insofar excluded. 

<img src="images/rutronik_origin_kaunas.png" style="zoom:50%;" />



