#include "msp430fr2355.h"
#include <msp430.h>
#include SYSTEM.H
#include intrinsics.H



int main(void)
{
    //Setup Code (Runs when processor resets)
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    rgbinit();

    PM5CTL0 &= ~LOCKLPM5;                   //Disable the GPIO power on

    while(1)
    {
        setIgnitor();
        turnonPilotValve();
        Wait2Seconds();
        checkflame();

        //while((CallforHeat() || (checkFlame()) ||(readBoilerTemp()<Threshold)));
        while(1){

            cfh = CallForHeat();
            cf = checkFlame;

            if(!CallforHeat()){
                break;
            }
            else if (!checkFlame()){
                FLAME_EXTINGUISHED =1;
                break;
            }
        }

        turnOffMainValve();
        turnOffPilotValve();
        turnOffIgnitor();

        _bis_SR_register(CPUOFF);
    }
    
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    while(1)
    {
        P1OUT ^= BIT0;                      // Toggle P1.0 using exclusive-OR
        __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s
    }
}
