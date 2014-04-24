

#ifndef MED_AUDIO_CUSTOM_H
#define MED_AUDIO_CUSTOM_H

// normal mode parameters ------------------------
#define NORMAL_SPEECH_OUTPUT_FIR_COEFF \
       803,  -696,  1021,  -877,   889,\
       181,  -102,   270,  -877,  1435,\
     -1236,  1413, -3102,  3184, -3963,\
      4431, -6984,  4077, -9645, 12052,\
    -14934, 20675, 20675,-14934, 12052,\
     -9645,  4077, -6984,  4431, -3963,\
      3184, -3102,  1413, -1236,  1435,\
      -877,   270,  -102,   181,   889,\
      -877,  1021,  -696,   803,     0,\
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

#define HEADSET_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,  0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

// handfree mode parameters ------------------------
#define HANDFREE_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,  0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

// VoIP_BT  mode parameters ------------------------
#define VOIPBT_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,  0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

// VoIP_NORMAL mode parameters ------------------------
#define VOIPNORMAL_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,  0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

// VoIP_Handfree mode parameters ------------------------
#define VOIPHANDFREE_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

// AUX1 mode parameters ------------------------
#define AUX1_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0

// AUX2 mode parameters ------------------------
#define AUX2_SPEECH_OUTPUT_FIR_COEFF \
    32767,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    0,	  0,	 0, 	0,   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    \
    32767,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0, \
    0,	  0,	 0, 	0,	   0


#define SPEECH_OUTPUT_MED_FIR_COEFF \
    NORMAL_SPEECH_OUTPUT_FIR_COEFF,\
    HEADSET_SPEECH_OUTPUT_FIR_COEFF ,\
    HANDFREE_SPEECH_OUTPUT_FIR_COEFF ,\
    VOIPBT_SPEECH_OUTPUT_FIR_COEFF,\
    VOIPNORMAL_SPEECH_OUTPUT_FIR_COEFF,\
    VOIPHANDFREE_SPEECH_OUTPUT_FIR_COEFF,\
    AUX1_SPEECH_OUTPUT_FIR_COEFF,\
    AUX2_SPEECH_OUTPUT_FIR_COEFF

#define SPEECH_INPUT_MED_FIR_COEFF\
       66,  -404,   174,  -179,   -61,\
     -471,  -210,  -169,   509,  -348,\
      356,  1216, -2108,  2317, -1712,\
     3231, -1735,  3023, -5039,  4595,\
    -9686, 32767, 32767, -9686,  4595,\
    -5039,  3023, -1735,  3231, -1712,\
     2317, -2108,  1216,   356,  -348,\
      509,  -169,  -210,  -471,   -61,\
     -179,   174,  -404,    66,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
                                      \
    32767,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0,\
        0,     0,     0,     0,     0


#define FIR_output_index \
    0,0,0,0,0,0,0,0

#define FIR_input_index \
    0,0,0,0,0,0,0,0

#define MED_SPEECH_NORMAL_MODE_PARA \
    96,   253,  16388,     30,   57351,     31,   400,     1, \
    4112,  	4325,      11,        0,       0,      0,     0,  8192

#define MED_SPEECH_EARPHONE_MODE_PARA \
    96,   253,  10756,      30,   57351,     31,   400,     0, \
    4112,      4325,     11,     0,       0,     0,     0,     0

#define MED_SPEECH_BT_EARPHONE_MODE_PARA \
    64,   253,  8228,     0,   49749,     0,   400,     0, \
    4112,      4325,     11,     0,       0,     0,     0,     86

#define MED_SPEECH_LOUDSPK_MODE_PARA \
    96,   224,   4710,     30,   57351,     0,   400,     0, \
    4112,      4325,     11,     0,       0,     0,     0,     0

#define MED_SPEECH_CARKIT_MODE_PARA \
    96,   224,   5256,     30,   57351,     0,   400,     0, \
    4112,      4325,     11,     0,       0,     0,     0,     0

#define MED_SPEECH_BT_CORDLESS_MODE_PARA \
    0,      0,      0,      0,      0,      0,      0,      0, \
    0,      0,      0,      0,      0,      0,      0,      0

#define MED_SPEECH_AUX1_MODE_PARA \
    0,      0,      0,      0,      0,      0,      0,      0, \
    0,      0,      0,      0,      0,      0,      0,      0

#define MED_SPEECH_AUX2_MODE_PARA \
    0,      0,      0,      0,      0,      0,      0,      0, \
    0,      0,      0,      0,      0,      0,      0,      0

#endif
