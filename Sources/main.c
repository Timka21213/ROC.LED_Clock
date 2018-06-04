#include <msp430g2553.h>
#include <dop.h>

#define WDT_meas_setting (DIV_SMCLK_512)
#define zad 128
#define tuch 1200

/* Definitions for use with the WDT settings*/
#define DIV_SMCLK_32768 (WDT_MDLY_32)       // SMCLK/32768
#define DIV_SMCLK_8192  (WDT_MDLY_8)        // SMCLK/8192
#define DIV_SMCLK_512   (WDT_MDLY_0_5)      // SMCLK/512
#define DIV_SMCLK_64    (WDT_MDLY_0_064)    // SMCLK/64

//#define LED_1   (0x04)                      // P1.0 LED output

unsigned int meas_A, meas_B, jdun = 0;
char key_A = 0, key_B = 0, naj_A = 0, naj_B = 0, uderj_AB = 0;
char rejim = 0, jdun_A = 0, jdun_B = 0; // 0 - режим отображения времени, 1 - режим настройки времени, 2 - режим сна
char s32 = 0, s = 0, m = 0, h = 0;
char i = 0;

void measure_count(void);                   // Measures each capacitive sensor
void cap_test(void);

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

	P2SEL |= (BIT6 | BIT7);               // Set P2.6 and P2.6 SEL for XIN, XOUT
	P2SEL2 &= ~(BIT6 | BIT7);            // Set P2.6 and P2.7 SEL2 for XIN, XOUT

	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz

	BCSCTL1 &= (~XTS);                       // ACLK = LFXT1CLK
	BCSCTL3 &= ~(BIT4 | BIT5);                 // 32768Hz crystal on LFXT1

	IE1 |= WDTIE;                             // enable WDT interrupt

	gashenie();

	TA0CTL = TASSEL_3 + MC_2;                   // TACLK, cont mode
	TA0CCTL1 = CM_3 + CCIS_2 + CAP;               // Pos&Neg,GND,Cap

	P1DIR &= ~ BIT0;
	P1SEL &= ~ BIT0;
	P2DIR &= ~ BIT3;
	P2SEL &= ~ BIT3;

	// Таймер считающий время
	TA1CCR0 = 1024;
	TA1CCTL0 = CCIE;
	TA1CTL = TASSEL_1 + ID_0 + MC_1;

	__bis_SR_register(GIE);                  // Enable interrupts

	while (1)
	{
		if (rejim == 0)
		{
			if (jdun > 500)
			{
				key_A = 0;
				key_B = 0;
				rejim = 2;
				gashenie();
				__bis_SR_register(LPM3_bits);
			}
			else
			{
				measure_count();                        // Measure all sensors

				if (meas_A < tuch)           // Determine if each key is pressed
				{                                     // per a preset threshold
					jdun = 0;
					key_A = 1;
				}
				else
					key_A = 0;

				if (meas_B < tuch)           // Determine if each key is pressed
				{                                     // per a preset threshold
					jdun = 0;
					key_B = 1;
				}
				else
					key_B = 0;

				i = 1;
				while (i == 1)
				{
					vremya_h(h);
					if (s32 < 16)
						vremya_m(m);
					gashenie();
				}
			}
		}
		else
		{
			if (jdun > zad)
			{
				rejim = 0;
				jdun_A = 0;
				jdun_B = 0;
				jdun = 0;
				__bis_SR_register(LPM3_bits);
			}
			else
			{
				s = 0;
				measure_count();                        // Measure all sensors

				if (meas_A < tuch)           // Determine if each key is pressed
				{                                     // per a preset threshold
					jdun = 0;
					key_A = 1;
					if ((!uderj_AB) && (!naj_A))
					{
						if (h == 11)
							h = 0;
						else
							h++;
					}
					naj_A = 1;
				}
				else
				{
					key_A = 0;
					naj_A = 0;
				}

				if (meas_B < tuch)           // Determine if each key is pressed
				{                                     // per a preset threshold
					jdun = 0;
					key_B = 1;
					if ((!uderj_AB) && (!naj_B))
					{
						if (m == 59)
							m = 0;
						else
							m++;
					}
					naj_B = 1;
				}
				else
				{
					key_B = 0;
					naj_B = 0;
				}
				i = 1;
				while (i == 1)
				{
					vremya_h(h);
					vremya_m(m);
					sistem_led();
					gashenie();
				}
			}
		}
	}
}                                           // End Main

/* Measure count result (capacitance) of each sensor*/
/* Routine setup for four sensors, not dependent on NUM_SEN value!*/
void measure_count(void)
{
	P2SEL2 |= BIT3;
	WDTCTL = WDT_meas_setting;              // WDT, ACLK, interval timer
	TA0CTL |= TACLR;              // Clear Timer_A TAR
	__bis_SR_register(LPM0_bits + GIE);              // Wait for WDT interrupt
	meas_A = TACCR1;              // Save result
	WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog timer
	P2SEL2 &= ~BIT3;

	P1SEL2 |= BIT0;
	WDTCTL = WDT_meas_setting;              // WDT, ACLK, interval timer
	TA0CTL |= TACLR;              // Clear Timer_A TAR
	__bis_SR_register(LPM0_bits + GIE);              // Wait for WDT interrupt
	meas_B = TACCR1;              // Save result
	WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog timer
	P1SEL2 &= ~BIT0;
}

void cap_test(void)
{
	measure_count();
	if ((meas_A < tuch) || (meas_B < tuch))
	{
		rejim = 0;
		jdun = 0;
	}
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)

{
	TA0CCTL1 ^= CCIS0;                        // Create SW capture of CCR1
	__bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A(void)
{
	i = 0;
	s32++;
	if (s32 > 31)
	{
		s++;
		s32 = 0;
	}
	if (s > 59)
	{
		m++;
		s = 0;
	}
	if (m > 59)
	{
		h++;
		m = 0;
	}
	if (h > 11)
	{
		h = 0;
	}
	switch (rejim)
	{
	case 0:
		if (key_A)
		{
			if (jdun_A < zad)
				jdun_A++;
		}
		else
		{
			jdun_A = 0;
			uderj_AB = 0;
		}
		if (key_B)
		{
			if (jdun_B < zad)
				jdun_B++;
		}
		else
		{
			jdun_B = 0;
			uderj_AB = 0;
		}
		if ((jdun_A == zad) && (jdun_B == zad))
		{
			uderj_AB = 1;
			rejim = 1;
		}

		jdun++;
		__bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
		break;
	case 1:
		if (key_A && key_B && uderj_AB)
		{
			jdun_A = 0;
			jdun_B = 0;
		}
		else
			uderj_AB = 0;
		if (key_A)
		{
			if (jdun_A < 32)
				jdun_A++;
			else
				naj_A = 0;
		}
		else
		{
			jdun_A = 0;
		}
		if (key_B)
		{
			if (jdun_B < 32)
				jdun_B++;
			else
				naj_B = 0;
		}
		else
		{
			jdun_B = 0;
		}
		jdun++;
		__bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
		break;
	case 2:
		if ((s32 % 4) == 0)
			cap_test();
		break;
	}
}
