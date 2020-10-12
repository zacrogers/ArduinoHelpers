/*
* Numerically controlled oscillator
*
*/
#ifndef NCO_H_
#define NCO_H_

#include <stdint.h>
#include <math.h>

#define PHASE_ACC_WIDTH 8
#define LUT_LENGTH 1024
#define BIT_DEPTH 16

typedef enum
{
	WF_SINE = 0,
	WF_SQUARE,
	WF_TRIANGLE,
	WF_SAW,
	WF_REV_SAW
}Waveform;

typedef struct
{
	int lut[LUT_LENGTH];
	uint16_t phase_accum;
	uint16_t delta_phase;
	int clock_freq;
}NCO;

void NCO_init(NCO *nco, int clock_freq, Waveform wf);
int  NCO_next_signal(NCO *nco);
void NCO_set_freq(NCO *nco, float freq);


#endif /* NCO_H_ */

