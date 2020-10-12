/*
 * nco.c
 *
 *  Created on: Aug 3, 2020
 *      Author: Zac
 */
#include "nco.h"

void NCO_init(NCO *nco, int clock_freq, Waveform wf)
{
	nco->phase_accum = 0;
	nco->delta_phase = 0;
	nco->clock_freq = clock_freq;

	switch(wf)
	{
		case WF_SINE:
			for(int i = 0; i < LUT_LENGTH; ++i)
			{
				nco->lut[i] = ((sin(i*2*M_PI/LUT_LENGTH) + 1)*(4096/2));
			}
			break;

		case WF_SQUARE:
			for(int n = 0; n < LUT_LENGTH; ++n)
			{
				if(n < (LUT_LENGTH / 2))
				{
					nco->lut[n] = 255;
				}
				else
				{
					nco->lut[n] = 0;
				}
			}
			break;

		case WF_TRIANGLE:
			for(int n = 0; n < LUT_LENGTH/2; ++n)
			{
				nco->lut[n] = n * 2;
			}
			for(int n = LUT_LENGTH/2; n > 0; --n)
			{
				nco->lut[n] = n * 2;
			}
			break;

		case WF_SAW:
			for(int n = 0; n < LUT_LENGTH; ++n)
			{
				nco->lut[n] = n;
			}
			break;

		case WF_REV_SAW:
			for(int n = LUT_LENGTH; n > 0; --n)
			{
				nco->lut[n] = n;
			}
			break;
	}
}

int NCO_next_signal(NCO *nco)
{
	nco->phase_accum += nco->delta_phase;
	return nco->lut[(uint16_t)(nco->phase_accum>>6)];
}

void NCO_set_freq(NCO *nco, float freq)
{
	float phase_word = freq * ((float)65536/(float)nco->clock_freq);
//	float phase_word = (float)freq / (float)65536/(float)nco->clock_freq;
	nco->delta_phase = phase_word;
}

