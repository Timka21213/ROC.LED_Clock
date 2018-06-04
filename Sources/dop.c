/*
 * dop.c
 *
 *  Created on: 11 θώνÿ 2017 γ.
 *      Author: Seplus
 */
#include "msp430.h"
#include "dop.h"
char z = 1;
void sistem_led(void)
{
	gashenie();
	P1DIR |= BIT5;
	port(1, 1);
}
void port(char a, char b)
{
	z = 1;
	z <<= b;
	if (a == 1)
	{
		P1DIR |= z;
		P1OUT |= z;
	}
	else
	{
		P2DIR |= z;
		P2OUT |= z;
	}
}

void vremya_h(char h)
{
	gashenie();
	if (h < 3)
	{
		P1DIR |= BIT7;
		switch (h)
		{
		case 0:
			port(1, 2);
			break;
		case 1:
			port(1, 6);
			break;
		case 2:
			port(2, 1);
			break;
		}
	}
	else
	{
		if (h < 6)
		{
			P1DIR |= BIT6;
			switch (h)
			{
			case 3:
				port(1, 7);
				break;
			case 4:
				port(1, 2);
				break;
			case 5:
				port(2, 1);
				break;
			}
		}
		else
		{
			if (h < 9)
			{
				P2DIR |= BIT1;
				switch (h)
				{
				case 6:
					port(1, 7);
					break;
				case 7:
					port(1, 6);
					break;
				case 8:
					port(1, 2);
					break;
				}
			}
			else
			{
				P1DIR |= BIT2;
				switch (h)
				{
				case 9:
					port(1, 7);
					break;
				case 10:
					port(1, 6);
					break;
				case 11:
					port(2, 1);
					break;
				}
			}
		}
	}
}

void vremya_m(char m)
{
	gashenie();
	switch (m)
	{
	case 0:
		P1DIR |= BIT7;
		port(1, 2);
		break;
	case 1:
		P2DIR |= BIT4;
		port(1, 1);
		break;
	case 2:
		P2DIR |= BIT4;
		port(2, 5);
		break;
	case 3:
		P2DIR |= BIT4;
		port(2, 0);
		break;
	case 4:
		P2DIR |= BIT4;
		port(2, 2);
		break;
	case 5:
		P1DIR |= BIT7;
		port(1, 6);
		break;
	case 6:
		P2DIR |= BIT4;
		port(1, 4);
		break;
	case 7:
		P2DIR |= BIT4;
		port(1, 3);
		break;
	case 8:
		P2DIR |= BIT4;
		port(1, 5);
		break;
	case 9:
		P2DIR |= BIT5;
		port(2, 4);
		break;
	case 10:
		P1DIR |= BIT7;
		port(2, 1);
		break;
	case 11:
		P2DIR |= BIT5;
		port(1, 1);
		break;
	case 12:
		P2DIR |= BIT5;
		port(2, 0);
		break;
	case 13:
		P2DIR |= BIT5;
		port(2, 2);
		break;
	case 14:
		P2DIR |= BIT5;
		port(1, 4);
		break;
	case 15:
		P1DIR |= BIT6;
		port(1, 7);
		break;
	case 16:
		P2DIR |= BIT5;
		port(1, 3);
		break;
	case 17:
		P2DIR |= BIT5;
		port(1, 5);
		break;
	case 18:
		P2DIR |= BIT0;
		port(2, 4);
		break;
	case 19:
		P2DIR |= BIT0;
		port(2, 5);
		break;
	case 20:
		P1DIR |= BIT6;
		port(1, 2);
		break;
	case 21:
		P2DIR |= BIT0;
		port(1, 1);
		break;
	case 22:
		P2DIR |= BIT0;
		port(2, 2);
		break;
	case 23:
		P2DIR |= BIT0;
		port(1, 4);
		break;
	case 24:
		P2DIR |= BIT0;
		port(1, 3);
		break;
	case 25:
		P1DIR |= BIT6;
		port(2, 1);
		break;
	case 26:
		P2DIR |= BIT0;
		port(1, 5);
		break;
	case 27:
		P2DIR |= BIT2;
		port(2, 4);
		break;
	case 28:
		P2DIR |= BIT2;
		port(2, 5);
		break;
	case 29:
		P2DIR |= BIT2;
		port(2, 0);
		break;
	case 30:
		P2DIR |= BIT1;
		port(1, 7);
		break;
	case 31:
		P2DIR |= BIT2;
		port(1, 1);
		break;
	case 32:
		P2DIR |= BIT2;
		port(1, 4);
		break;
	case 33:
		P2DIR |= BIT2;
		port(1, 3);
		break;
	case 34:
		P2DIR |= BIT2;
		port(1, 5);
		break;
	case 35:
		P2DIR |= BIT1;
		port(1, 6);
		break;
	case 36:
		P1DIR |= BIT4;
		port(2, 4);
		break;
	case 37:
		P1DIR |= BIT4;
		port(2, 5);
		break;
	case 38:
		P1DIR |= BIT4;
		port(2, 0);
		break;
	case 39:
		P1DIR |= BIT4;
		port(2, 2);
		break;
	case 40:
		P2DIR |= BIT1;
		port(1, 2);
		break;
	case 41:
		P1DIR |= BIT4;
		port(1, 1);
		break;
	case 42:
		P1DIR |= BIT4;
		port(1, 3);
		break;
	case 43:
		P1DIR |= BIT4;
		port(1, 5);
		break;
	case 44:
		P1DIR |= BIT3;
		port(2, 4);
		break;
	case 45:
		P1DIR |= BIT2;
		port(1, 7);
		break;
	case 46:
		P1DIR |= BIT3;
		port(2, 5);
		break;
	case 47:
		P1DIR |= BIT3;
		port(2, 0);
		break;
	case 48:
		P1DIR |= BIT3;
		port(2, 2);
		break;
	case 49:
		P1DIR |= BIT3;
		port(1, 4);
		break;
	case 50:
		P1DIR |= BIT2;
		port(1, 6);
		break;
	case 51:
		P1DIR |= BIT3;
		port(1, 1);
		break;
	case 52:
		P1DIR |= BIT3;
		port(1, 5);
		break;
	case 53:
		P1DIR |= BIT5;
		port(2, 4);
		break;
	case 54:
		P1DIR |= BIT5;
		port(2, 5);
		break;
	case 55:
		P1DIR |= BIT2;
		port(2, 1);
		break;
	case 56:
		P1DIR |= BIT5;
		port(2, 0);
		break;
	case 57:
		P1DIR |= BIT5;
		port(2, 2);
		break;
	case 58:
		P1DIR |= BIT5;
		port(1, 4);
		break;
	case 59:
		P1DIR |= BIT5;
		port(1, 3);
		break;
	}
}

void gashenie(void)
{
	P1DIR = 0;
	P2DIR = 0;
	P1OUT = 0;
	P2OUT = 0;
}
