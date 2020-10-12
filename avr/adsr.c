/*
 * adsr.c
 *
 *  Created on: Oct 10, 2020
 *      Author: Zac
 */

#include "adsr.h"

void ADSR_init(ADSR *adsr, uint16_t a, uint16_t d, float s, uint16_t r)
{
	ADSR_set_vals(adsr, a, d, s, r);

	adsr->tick = 0;
	adsr->state = ENV_INIT;
}

void ADSR_set_vals(ADSR *adsr, uint16_t a, uint16_t d, float s, uint16_t r)
{
	adsr->attack = a;
	adsr->decay = d;
	adsr->sustain = s;
	adsr->release = r;
}

void  ADSR_set_attack(ADSR *adsr, uint16_t a){adsr->attack = a;}
void  ADSR_set_decay(ADSR *adsr, uint16_t d){adsr->decay = d;}
void  ADSR_set_sustain(ADSR *adsr, float s){adsr->sustain = s;}
void  ADSR_set_release(ADSR *adsr, uint16_t r){adsr->release = r;}

void  ADSR_note_on(ADSR *adsr)
{
	adsr->tick = 0;
	adsr->state = ENV_ATTACK;
}
void  ADSR_note_off(ADSR *adsr)
{
	adsr->tick = 0;
	adsr->state = ENV_RELEASE;
}

float ADSR_get_next(ADSR *adsr)
{
	switch(adsr->state)
	{
		case ENV_INIT:
		{
			adsr->amplitude = 0.0;
			break;
		}

		case ENV_ATTACK:
		{
			adsr->amplitude = ((float)adsr->tick / (float)adsr->attack);

			if(adsr->tick < adsr->attack-1)
			{
				adsr->tick++;
			}
			else
			{
				adsr->tick = 0;
				adsr->state = ENV_DECAY;
			}

			break;
		}

		case ENV_DECAY:
		{
			if(adsr->amplitude > adsr->sustain)
			{
				adsr->amplitude = 1.0 - ((float)adsr->tick / (float)adsr->decay);
			}

			if(adsr->tick < adsr->decay-1)
			{
				adsr->tick++;
			}
			else
			{
				adsr->tick = 0;
				adsr->state = ENV_SUSTAIN;
			}
			break;
		}

		case ENV_SUSTAIN:
		{
			adsr->amplitude = adsr->sustain;
			break;
		}

		case ENV_RELEASE:
		{
			adsr->amplitude = adsr->sustain - ((float)adsr->tick / (float)adsr->release);

			if(adsr->tick < adsr->release-1)
			{
				adsr->tick++;
			}
			else
			{
				adsr->tick = 0;
				adsr->state = ENV_INIT;
			}
			break;
		}
	}

	return adsr->amplitude;
}
