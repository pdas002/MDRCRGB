/*
 BY: Prangon Das
 Date: 4/19/19
10 sec fading LED and then flash for 2 seconds!
 */

#include <bcm2835.h>
#include <stdio.h>
#include <time.h>


#define chan RPI_V2_GPIO_P1_12
#define chan1 RPI_V2_GPIO_P1_33 // These two have the same brightness channel so changing channel 1 affects both
#define alsochan1 RPI_V2_GPIO_P1_35 // ^^^

// Channels
#define PWM_CHANNEL 0
#define PWM_CHANNEL1 1

// This controls the max range of the PWM signal
#define RANGE 1024

int main(int argc, char **argv)
{
	setbuf(stdout, NULL); // disable buffering on stdout so output of RPI can be seen
    if (!bcm2835_init())
	return 1;

    // Set the output pin to Alt Fun 5, to allow PWM channel 0 to be output there
	// Set the output pin to Alt Fun 0, to allow PWM channel 1 to be output there
    bcm2835_gpio_fsel(chan, BCM2835_GPIO_FSEL_ALT5);
	bcm2835_gpio_fsel(alsochan1, BCM2835_GPIO_FSEL_ALT5);
	bcm2835_gpio_fsel(chan1, BCM2835_GPIO_FSEL_ALT0);
	
    // Clock divider is set to 16.
    // With a divider of 16 and a RANGE of 1024, in MARKSPACE mode,
    // the pulse repetition frequency will be
    // 1.2MHz/1024 = 1171.875Hz
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
	
	bcm2835_pwm_set_mode(PWM_CHANNEL1, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL1, RANGE);

    // Vary the PWM m/s ratio between 1/RANGE and (RANGE-1)/RANGE
    // over the course of a a few seconds
    int direction = 1; // 1 is increase, -1 is decrease
    int gdata = 1;
	int bdata = 1024;
	time_t secs;
	int startOver = 1;
	while(1){
		secs =  startOver == 1 ? 4 : 2;
		startOver = startOver == 1 ?  0 : 1;
		printf("%d", startOver);
		time_t startTime = time(NULL);
		while (time(NULL) - startTime < secs)
		{
			if (gdata == 1) // so it doesn't seem as if turned off
			{
				direction = 1;   // Switch to increasing
			}
			else if (gdata == RANGE-1){
				direction = -1;  // Switch to decreasing
			}
			gdata += direction;
			bdata -= direction; // Go the opposite way so it fades from one color to other
			bcm2835_pwm_set_data(PWM_CHANNEL1, bdata);
			bcm2835_pwm_set_data(PWM_CHANNEL, gdata);
			bcm2835_delay(startOver == 1 ? .5 : 2);
		}
	}

    bcm2835_close();
    return 0;
}
