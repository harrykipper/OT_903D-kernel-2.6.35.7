




#ifndef _CFG_AUDIO_H
#define _CFG_AUDIO_H

#include "../cfgfileinc/CFG_AUDIO_File.h"
#include "../inc/sph_coeff_default.h"
#include "../inc/audio_custom.h"
#include "../inc/audio_acf_default.h"
#include "../inc/audio_effect_default.h"
#include "../inc/med_audio_default.h"
#include "../inc/audio_volume_custom_default.h"

AUDIO_CUSTOM_PARAM_STRUCT speech_custom_default =
{
    /* INT8 volume[MAX_VOL_CATE][MAX_VOL_TYPE] */
      /* Normal volume: TON, SPK, MIC, FMR, SPH, SID, MED */
      GAIN_NOR_TON_VOL, GAIN_NOR_KEY_VOL, GAIN_NOR_MIC_VOL, GAIN_NOR_FMR_VOL, GAIN_NOR_SPH_VOL, GAIN_NOR_SID_VOL, GAIN_NOR_MED_VOL
      ,
      /* Headset volume: TON, SPK, MIC, FMR, SPH, SID, MED */
      GAIN_HED_TON_VOL, GAIN_HED_KEY_VOL, GAIN_HED_MIC_VOL, GAIN_HED_FMR_VOL, GAIN_HED_SPH_VOL, GAIN_HED_SID_VOL, GAIN_HED_MED_VOL
      ,
      /* Handfree volume: TON, SPK, MIC, FMR, SPH, SID, MED */
      GAIN_HND_TON_VOL, GAIN_HND_KEY_VOL, GAIN_HND_MIC_VOL, GAIN_HND_FMR_VOL, GAIN_HND_SPH_VOL, GAIN_HND_SID_VOL, GAIN_HND_MED_VOL
   ,
    /* UINT16 speech_common_para[12] */
      DEFAULT_SPEECH_COMMON_PARA
   ,
    /* UINT16 speech_mode_para[8][16] */
      DEFAULT_SPEECH_NORMAL_MODE_PARA,
      DEFAULT_SPEECH_EARPHONE_MODE_PARA,
      DEFAULT_SPEECH_LOUDSPK_MODE_PARA,
      DEFAULT_SPEECH_BT_EARPHONE_MODE_PARA,
      DEFAULT_SPEECH_BT_CORDLESS_MODE_PARA,
      DEFAULT_SPEECH_CARKIT_MODE_PARA,
      DEFAULT_SPEECH_AUX1_MODE_PARA,
      DEFAULT_SPEECH_AUX2_MODE_PARA
   ,
    /* UINT16 speech_volume_para[4] */
      DEFAULT_SPEECH_VOL_PARA
   ,
    /* UINT16 debug_info[16] */
      DEFAULT_AUDIO_DEBUG_INFO
   ,
    /* INT16 sph_in_fir[6][45], sph_out_fir */
      SPEECH_INPUT_FIR_COEFF,
      SPEECH_OUTPUT_FIR_COEFF
   ,
    /* UINT16 DG_DL_Speech */
      DG_DL_Speech
   ,
    /* UINT16 DG_Microphone */
      DG_Microphone
   ,
    /* UINT16 FM record volume*/
      FM_Record_Vol
   ,
    /* UINT16 BT sync type and length*/
      DEFAULT_BLUETOOTH_SYNC_TYPE,
      DEFAULT_BLUETOOTH_SYNC_LENGTH
   ,
    /* UINT16 BT PCM in/out digital gain*/
      DEFAULT_BT_PCM_IN_VOL,
      DEFAULT_BT_PCM_OUT_VOL
   ,
    /* user mode : normal mode, earphone mode, loud speaker mode */
    /* UCHAR  user_mode             */
      VOL_NORMAL
   ,
    /* auto VM record setting */
      DEFAULT_VM_SUPPORT,
      DEFAULT_AUTO_VM,
   /* Micbais voltage 1900 --> 2200 */
      MICBAIS,
};

AUDIO_CUSTOM_WB_PARAM_STRUCT wb_speech_custom_default = 
{
    /* unsigned short speech_mode_wb_para[8][16] */
        DEFAULT_WB_SPEECH_NORMAL_MODE_PARA,    
        DEFAULT_WB_SPEECH_EARPHONE_MODE_PARA,    
        DEFAULT_WB_SPEECH_LOUDSPK_MODE_PARA,
        DEFAULT_WB_SPEECH_BT_EARPHONE_MODE_PARA,    
        DEFAULT_WB_SPEECH_BT_CORDLESS_MODE_PARA,
        DEFAULT_WB_SPEECH_CARKIT_MODE_PARA,    
        DEFAULT_WB_SPEECH_AUX1_MODE_PARA,   
        DEFAULT_WB_SPEECH_AUX2_MODE_PARA,
    /* short sph_wb_in_fir[6][90] */
        WB_Speech_Input_FIR_Coeff,
    /* short sph_wb_out_fir[6][90] */
        WB_Speech_Output_FIR_Coeff,
};


AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default =
{
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_DRC_FORGET_TABLE,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_EFFECT_CUSTOM_PARAM_STRUCT audio_effect_custom_default =
{
    // DSRD parameters
    BSRD_LEVEL,
    BSRD_DISTANCE1,
    BSRD_DISTANCE2,
    BSRD_BAND_SELECT,

    // BASS
    BASS_CUTOFF_FREQ,
    BASS_ISVB,

    //EQ effect
    NORMAL_GAIN_LEVEL,
    DANCE_GAIN_LEVEL,
    BASS_GAIN_LEVEL,
    CLASSICAL_GAIN_LEVEL,
    TREBLE_GAIN_LEVEL,
    PARTY_GAIN_LEVEL,
    POP_GAIN_LEVEL,
    ROCK_GAIN_LEVEL,

    //loudness mode
    LOUDENHANCEMODE,

    //TS
    TIME_TD_TF,
    TIME_TS_RATIO
};

AUDIO_PARAM_MED_STRUCT audio_param_med_default ={
	SPEECH_INPUT_MED_FIR_COEFF,
	SPEECH_OUTPUT_MED_FIR_COEFF,
	FIR_output_index,
	FIR_input_index,
	MED_SPEECH_NORMAL_MODE_PARA,
	MED_SPEECH_EARPHONE_MODE_PARA,
	MED_SPEECH_BT_EARPHONE_MODE_PARA,
	MED_SPEECH_LOUDSPK_MODE_PARA,
	MED_SPEECH_CARKIT_MODE_PARA,
	MED_SPEECH_BT_CORDLESS_MODE_PARA,
	MED_SPEECH_AUX1_MODE_PARA,
	MED_SPEECH_AUX2_MODE_PARA
};


AUDIO_VOLUME_CUSTOM_STRUCT audio_volume_custom_default ={
    AUD_VOLUME_RING,
    AUD_VOLUME_KEY,
    AUD_VOLUME_MIC,
    AUD_VOLUME_FMR,
    AUD_VOLUME_SPH,
    AUD_VOLUME_SID,
    AUD_VOLUME_MEDIA,
    AUD_VOLUME_MATV
};

AUDIO_CUSTOM_EXTRA_PARAM_STRUCT dual_mic_custom_default =
{
   DEFAULT_SPEECH_DUAL_MIC_ABF_PARA,
   DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA
};


#endif


