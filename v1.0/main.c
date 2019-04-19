/*
 BY: Prangon Das
 Date: 4/15/19
 Initial RGB control - working
 */
#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>

// Blinks on RPi Plug P1 pin 29 (which is GPIO pin 5)
#define pin1 RPI_V2_GPIO_P1_29

// Blinks on RPi Plug P1 pin 31 (which is GPIO pin 6)
#define pin2 RPI_V2_GPIO_P1_31

// Blinks on RPi Plug P1 pin 33 (which is GPIO pin 13)
#define pin3 RPI_V2_GPIO_P1_33


int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
	//bcm2835_set_debug(1);

    if (!bcm2835_init())
      return 1;

    // Set the pins to be an output
    bcm2835_gpio_fsel(pin1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(pin2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(pin3, BCM2835_GPIO_FSEL_OUTP);

    // Blink
    while (1)
    {
	// Turn it on
	bcm2835_gpio_write(pin1, HIGH);
	bcm2835_gpio_write(pin2, HIGH);
	bcm2835_gpio_write(pin3, LOW);
	
	// wait a bit
	bcm2835_delay(500);
	
	// turn it on
	bcm2835_gpio_write(pin1, LOW);
	bcm2835_gpio_write(pin2, HIGH);
	bcm2835_gpio_write(pin3, HIGH);
	
	// wait a bit
	bcm2835_delay(500);
		// turn it on
	bcm2835_gpio_write(pin1, HIGH);
	bcm2835_gpio_write(pin2, LOW);
	bcm2835_gpio_write(pin3, HIGH);
	
	// wait a bit
	bcm2835_delay(500);
    }
    bcm2835_close();
    return 0;
}