# simple project with EK-TM4C1294XL LaunchPad using UART with interrupts



## Getting Started


These instructions will give details on how to create simple project using TivaWare library and code composer studio to Initialize and use UART in EK-TM4C1294XL connected LaunchPa
We will communicate with the board through the UART, which is connected as a virtual serial port through the emulator USB connection.
in this project we will use interrupts to receive and transmit characters. 
We will select receiver interrupts (RX) and receiver timeout interrupts (RT).
The receiver interrupt is generated when a single character has been received (when FIFO is disabled) or when the specified FIFO level has been reached (when FIFO is enabled). 
The receiver timeout interrupt is generated when a character has been received, and a second character has not been received within a 32-bit period.
we will add a visual indicator to show that we received and transmitted a character. So we’ll need to add code similar to previous project to blink the LED inside the interrupt handler. 


### Prerequisites

What software you need to install 

```
in addition to Code Composer Studio (CCS) and TivaWare library 
we will need terminal program to test our code so You can download PuTTY from the address below.  
http://the.earth.li/~sgtatham/putty/latest/x86/putty.exe .
►configure putty as:
Select Serial as the Connection type. Enter your COM port number and 115200 for the speed. Click Serial at the bottom of the Category pane.  Make the  8, 1, None, None  and click Open.  
If you prefer some other terminal program, use these settings
```


### kit initialization
```

► JP4 and 5 configure the LaunchPad for either CAN or UART communication. Vertical is CAN and horizontal is UART . Make sure that all four jumpers are in the horizontal (UART) position 
When plugged into a USB host, the ICDI enumerates as both a debugger and a virtual COM port. 
JP4 and JP5 control the selection of which UART from the TM4C1294NCPDTI is connected to the virtual COM port.
In the default configuration, UART0 maps to the virtual COM port of the ICDI.
In the CAN jumper configuration, UART2 maps to the virtual COM port of the ICDI.
```


## initialize code composer studio

same as we did in [test-gpio project](https://github.com/ahosny333/test-gpio)
```
► build variables for the paths that CCS will need to find your files.
► Link driverlib.lib to Your Project 
► Add the INCLUDE search paths for the header files 
 ```

### configuration to use UART Interrupts 
```
insert the address of the UART interrupt handler into the interrupt vector table as the following : 
► Open the tm4c1294ncpdt_startup_ccs.c file. Just below the prototype for _c_int00(void), add the UART interrupt handler prototype:
 extern void UARTIntHandler(void); 
► On about line 92, you’ll find the interrupt vector table entry for UART0 Rx and Tx.
 The default interrupt handler is named IntDefaultHandler. Replace this name with UARTIntHandler so the line looks like:
 UARTIntHandler,                      // UART0 Rx and Tx   

```

## Sponsored by
<a href = "https://the-diy-life.co">
<img src="https://the-diy-life.co/images/logo_diylife.jpg"  width="248" height="248">
</a>
