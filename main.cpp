#include "mbed.h"
#include "USBSerial.h"

//#define ATTEMPT_1             // as suggested by USBSerial in handbook https://developer.mbed.org/handbook/USBSerial. This worked once libraries were updated.
#ifndef ATTEMPT_1
    //#define ATTEMPT_2         // https://developer.mbed.org/handbook/SerialPC
    #ifndef ATTEMPT_2
        //#define ATTEMPT_3       // https://developer.mbed.org/questions/49485/Serial-comunication/
        #ifndef ATTEMPT_3
            #define ATTEMPT_4   // using writeBlock
        #endif
    #endif
#endif

// The LED flash is to ensure the timing is right
DigitalOut myled1(LED2); //left most LED if board is held as shown in Pinout diagram above
DigitalOut myled2(LED3); //2nd from left
DigitalOut myled3(LED4); //3rd from left
DigitalOut myled4(LED1); //4th from left (right most)

#if defined(ATTEMPT_1) || defined(ATTEMPT_4)
USBSerial serial;
#elif defined(ATTEMPT_2)
Serial pc(USBTX, USBRX); // tx, rx P0_19, P0_18
#elif defined(ATTEMPT_3)
Serial port1(P0_26, P0_27);
Serial port2(P1_14, P1_13);
// Serial port3(USB_DM, USB_DP); // This doesn't compile
Serial port4(P0_18, P0_19 );
#endif



int main() {
    unsigned char buf[] = "I am a virtual serial port\r\n";
    int bufLength = 28;
    while(1) 
    {
        #if defined(ATTEMPT_1)
        serial.printf("I am a virtual serial port\r\n");
        
        #elif defined(ATTEMPT_2)
        pc.printf("Hello World!\n");
        
        #elif defined(ATTEMPT_3)
        port1.printf("Hello port 1\r\n");
        myled1 = 1; //left most LED turns ON, rest off
        myled2 = 0;
        myled3 = 0;
        myled4 = 0;
        
        wait(1); //1 sec wait time
        port2.printf("Hello port 2\r\n");
        myled1 = 0;
        myled2 = 1; //2nd from left LED turns ON, rest off
        myled3 = 0;
        myled4 = 0;

        wait(1);
        port4.printf("Hello port 4\r\n");
        myled1 = 0;
        myled2 = 0;
        myled3 = 1; //3rd from left LED turns ON, rest off
        myled4 = 0;
        
        wait(1);
        myled1 = 0;
        myled2 = 0;
        myled3 = 0;
        myled4 = 1; //4th from left (right most) LED turns ON, rest off
        
        #elif defined(ATTEMPT_4)        
        serial.printf("I am a virtual serial port\r\n");
        serial.writeBlock(buf, bufLength);   
        
        #endif
        wait(1);
    }
}
