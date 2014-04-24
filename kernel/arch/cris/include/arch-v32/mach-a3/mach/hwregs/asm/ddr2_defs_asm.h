
#ifndef __ddr2_defs_asm_h
#define __ddr2_defs_asm_h


#ifndef REG_FIELD
#define REG_FIELD( scope, reg, field, value ) \
	REG_FIELD_X_( value, reg_##scope##_##reg##___##field##___lsb )
#define REG_FIELD_X_( value, shift ) ((value) << shift)
#endif

#ifndef REG_STATE
#define REG_STATE( scope, reg, field, symbolic_value ) \
	REG_STATE_X_( regk_##scope##_##symbolic_value, reg_##scope##_##reg##___##field##___lsb )
#define REG_STATE_X_( k, shift ) (k << shift)
#endif

#ifndef REG_MASK
#define REG_MASK( scope, reg, field ) \
	REG_MASK_X_( reg_##scope##_##reg##___##field##___width, reg_##scope##_##reg##___##field##___lsb )
#define REG_MASK_X_( width, lsb ) (((1 << width)-1) << lsb)
#endif

#ifndef REG_LSB
#define REG_LSB( scope, reg, field ) reg_##scope##_##reg##___##field##___lsb
#endif

#ifndef REG_BIT
#define REG_BIT( scope, reg, field ) reg_##scope##_##reg##___##field##___bit
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) REG_ADDR_X_(inst, reg_##scope##_##reg##_offset)
#define REG_ADDR_X_( inst, offs ) ((inst) + offs)
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
	REG_ADDR_VECT_X_(inst, reg_##scope##_##reg##_offset, index, \
			 STRIDE_##scope##_##reg )
#define REG_ADDR_VECT_X_( inst, offs, index, stride ) \
	((inst) + offs + (index) * stride)
#endif

/* Register rw_cfg, scope ddr2, type rw */
#define reg_ddr2_rw_cfg___col_width___lsb 0
#define reg_ddr2_rw_cfg___col_width___width 4
#define reg_ddr2_rw_cfg___nr_banks___lsb 4
#define reg_ddr2_rw_cfg___nr_banks___width 1
#define reg_ddr2_rw_cfg___nr_banks___bit 4
#define reg_ddr2_rw_cfg___bw___lsb 5
#define reg_ddr2_rw_cfg___bw___width 1
#define reg_ddr2_rw_cfg___bw___bit 5
#define reg_ddr2_rw_cfg___nr_ref___lsb 6
#define reg_ddr2_rw_cfg___nr_ref___width 4
#define reg_ddr2_rw_cfg___ref_interval___lsb 10
#define reg_ddr2_rw_cfg___ref_interval___width 11
#define reg_ddr2_rw_cfg___odt_ctrl___lsb 21
#define reg_ddr2_rw_cfg___odt_ctrl___width 2
#define reg_ddr2_rw_cfg___odt_mem___lsb 23
#define reg_ddr2_rw_cfg___odt_mem___width 1
#define reg_ddr2_rw_cfg___odt_mem___bit 23
#define reg_ddr2_rw_cfg___imp_strength___lsb 24
#define reg_ddr2_rw_cfg___imp_strength___width 1
#define reg_ddr2_rw_cfg___imp_strength___bit 24
#define reg_ddr2_rw_cfg___auto_imp_cal___lsb 25
#define reg_ddr2_rw_cfg___auto_imp_cal___width 1
#define reg_ddr2_rw_cfg___auto_imp_cal___bit 25
#define reg_ddr2_rw_cfg___imp_cal_override___lsb 26
#define reg_ddr2_rw_cfg___imp_cal_override___width 1
#define reg_ddr2_rw_cfg___imp_cal_override___bit 26
#define reg_ddr2_rw_cfg___dll_override___lsb 27
#define reg_ddr2_rw_cfg___dll_override___width 1
#define reg_ddr2_rw_cfg___dll_override___bit 27
#define reg_ddr2_rw_cfg_offset 0

/* Register rw_timing, scope ddr2, type rw */
#define reg_ddr2_rw_timing___wr___lsb 0
#define reg_ddr2_rw_timing___wr___width 3
#define reg_ddr2_rw_timing___rcd___lsb 3
#define reg_ddr2_rw_timing___rcd___width 3
#define reg_ddr2_rw_timing___rp___lsb 6
#define reg_ddr2_rw_timing___rp___width 3
#define reg_ddr2_rw_timing___ras___lsb 9
#define reg_ddr2_rw_timing___ras___width 4
#define reg_ddr2_rw_timing___rfc___lsb 13
#define reg_ddr2_rw_timing___rfc___width 7
#define reg_ddr2_rw_timing___rc___lsb 20
#define reg_ddr2_rw_timing___rc___width 5
#define reg_ddr2_rw_timing___rtp___lsb 25
#define reg_ddr2_rw_timing___rtp___width 2
#define reg_ddr2_rw_timing___rtw___lsb 27
#define reg_ddr2_rw_timing___rtw___width 3
#define reg_ddr2_rw_timing___wtr___lsb 30
#define reg_ddr2_rw_timing___wtr___width 2
#define reg_ddr2_rw_timing_offset 4

/* Register rw_latency, scope ddr2, type rw */
#define reg_ddr2_rw_latency___cas___lsb 0
#define reg_ddr2_rw_latency___cas___width 3
#define reg_ddr2_rw_latency___additive___lsb 3
#define reg_ddr2_rw_latency___additive___width 3
#define reg_ddr2_rw_latency_offset 8

/* Register rw_phy_cfg, scope ddr2, type rw */
#define reg_ddr2_rw_phy_cfg___en___lsb 0
#define reg_ddr2_rw_phy_cfg___en___width 1
#define reg_ddr2_rw_phy_cfg___en___bit 0
#define reg_ddr2_rw_phy_cfg_offset 12

/* Register rw_phy_ctrl, scope ddr2, type rw */
#define reg_ddr2_rw_phy_ctrl___rst___lsb 0
#define reg_ddr2_rw_phy_ctrl___rst___width 1
#define reg_ddr2_rw_phy_ctrl___rst___bit 0
#define reg_ddr2_rw_phy_ctrl___cal_rst___lsb 1
#define reg_ddr2_rw_phy_ctrl___cal_rst___width 1
#define reg_ddr2_rw_phy_ctrl___cal_rst___bit 1
#define reg_ddr2_rw_phy_ctrl___cal_start___lsb 2
#define reg_ddr2_rw_phy_ctrl___cal_start___width 1
#define reg_ddr2_rw_phy_ctrl___cal_start___bit 2
#define reg_ddr2_rw_phy_ctrl_offset 16

/* Register rw_ctrl, scope ddr2, type rw */
#define reg_ddr2_rw_ctrl___mrs_data___lsb 0
#define reg_ddr2_rw_ctrl___mrs_data___width 16
#define reg_ddr2_rw_ctrl___cmd___lsb 16
#define reg_ddr2_rw_ctrl___cmd___width 8
#define reg_ddr2_rw_ctrl_offset 20

/* Register rw_pwr_down, scope ddr2, type rw */
#define reg_ddr2_rw_pwr_down___self_ref___lsb 0
#define reg_ddr2_rw_pwr_down___self_ref___width 2
#define reg_ddr2_rw_pwr_down___phy_en___lsb 2
#define reg_ddr2_rw_pwr_down___phy_en___width 1
#define reg_ddr2_rw_pwr_down___phy_en___bit 2
#define reg_ddr2_rw_pwr_down_offset 24

/* Register r_stat, scope ddr2, type r */
#define reg_ddr2_r_stat___dll_lock___lsb 0
#define reg_ddr2_r_stat___dll_lock___width 1
#define reg_ddr2_r_stat___dll_lock___bit 0
#define reg_ddr2_r_stat___dll_delay_code___lsb 1
#define reg_ddr2_r_stat___dll_delay_code___width 7
#define reg_ddr2_r_stat___imp_cal_done___lsb 8
#define reg_ddr2_r_stat___imp_cal_done___width 1
#define reg_ddr2_r_stat___imp_cal_done___bit 8
#define reg_ddr2_r_stat___imp_cal_fault___lsb 9
#define reg_ddr2_r_stat___imp_cal_fault___width 1
#define reg_ddr2_r_stat___imp_cal_fault___bit 9
#define reg_ddr2_r_stat___cal_imp_pu___lsb 10
#define reg_ddr2_r_stat___cal_imp_pu___width 4
#define reg_ddr2_r_stat___cal_imp_pd___lsb 14
#define reg_ddr2_r_stat___cal_imp_pd___width 4
#define reg_ddr2_r_stat_offset 28

/* Register rw_imp_ctrl, scope ddr2, type rw */
#define reg_ddr2_rw_imp_ctrl___imp_pu___lsb 0
#define reg_ddr2_rw_imp_ctrl___imp_pu___width 4
#define reg_ddr2_rw_imp_ctrl___imp_pd___lsb 4
#define reg_ddr2_rw_imp_ctrl___imp_pd___width 4
#define reg_ddr2_rw_imp_ctrl_offset 32

#define STRIDE_ddr2_rw_dll_ctrl 4
/* Register rw_dll_ctrl, scope ddr2, type rw */
#define reg_ddr2_rw_dll_ctrl___mode___lsb 0
#define reg_ddr2_rw_dll_ctrl___mode___width 1
#define reg_ddr2_rw_dll_ctrl___mode___bit 0
#define reg_ddr2_rw_dll_ctrl___clk_delay___lsb 1
#define reg_ddr2_rw_dll_ctrl___clk_delay___width 7
#define reg_ddr2_rw_dll_ctrl_offset 36

#define STRIDE_ddr2_rw_dqs_dll_ctrl 4
/* Register rw_dqs_dll_ctrl, scope ddr2, type rw */
#define reg_ddr2_rw_dqs_dll_ctrl___dqs90_delay___lsb 0
#define reg_ddr2_rw_dqs_dll_ctrl___dqs90_delay___width 7
#define reg_ddr2_rw_dqs_dll_ctrl___dqs180_delay___lsb 7
#define reg_ddr2_rw_dqs_dll_ctrl___dqs180_delay___width 7
#define reg_ddr2_rw_dqs_dll_ctrl___dqs270_delay___lsb 14
#define reg_ddr2_rw_dqs_dll_ctrl___dqs270_delay___width 7
#define reg_ddr2_rw_dqs_dll_ctrl___dqs360_delay___lsb 21
#define reg_ddr2_rw_dqs_dll_ctrl___dqs360_delay___width 7
#define reg_ddr2_rw_dqs_dll_ctrl_offset 52


/* Constants */
#define regk_ddr2_al0                             0x00000000
#define regk_ddr2_al1                             0x00000008
#define regk_ddr2_al2                             0x00000010
#define regk_ddr2_al3                             0x00000018
#define regk_ddr2_al4                             0x00000020
#define regk_ddr2_auto                            0x00000003
#define regk_ddr2_bank4                           0x00000000
#define regk_ddr2_bank8                           0x00000001
#define regk_ddr2_bl4                             0x00000002
#define regk_ddr2_bl8                             0x00000003
#define regk_ddr2_bt_il                           0x00000008
#define regk_ddr2_bt_seq                          0x00000000
#define regk_ddr2_bw16                            0x00000001
#define regk_ddr2_bw32                            0x00000000
#define regk_ddr2_cas2                            0x00000020
#define regk_ddr2_cas3                            0x00000030
#define regk_ddr2_cas4                            0x00000040
#define regk_ddr2_cas5                            0x00000050
#define regk_ddr2_deselect                        0x000000c0
#define regk_ddr2_dic_weak                        0x00000002
#define regk_ddr2_direct                          0x00000001
#define regk_ddr2_dis                             0x00000000
#define regk_ddr2_dll_dis                         0x00000001
#define regk_ddr2_dll_en                          0x00000000
#define regk_ddr2_dll_rst                         0x00000100
#define regk_ddr2_emrs                            0x00000081
#define regk_ddr2_emrs2                           0x00000082
#define regk_ddr2_emrs3                           0x00000083
#define regk_ddr2_full                            0x00000001
#define regk_ddr2_hi_ref_rate                     0x00000080
#define regk_ddr2_mrs                             0x00000080
#define regk_ddr2_no                              0x00000000
#define regk_ddr2_nop                             0x000000b8
#define regk_ddr2_ocd_adj                         0x00000200
#define regk_ddr2_ocd_default                     0x00000380
#define regk_ddr2_ocd_drive0                      0x00000100
#define regk_ddr2_ocd_drive1                      0x00000080
#define regk_ddr2_ocd_exit                        0x00000000
#define regk_ddr2_odt_dis                         0x00000000
#define regk_ddr2_offs                            0x00000000
#define regk_ddr2_pre                             0x00000090
#define regk_ddr2_pre_all                         0x00000400
#define regk_ddr2_pwr_down_fast                   0x00000000
#define regk_ddr2_pwr_down_slow                   0x00001000
#define regk_ddr2_ref                             0x00000088
#define regk_ddr2_rtt150                          0x00000040
#define regk_ddr2_rtt50                           0x00000044
#define regk_ddr2_rtt75                           0x00000004
#define regk_ddr2_rw_cfg_default                  0x00186000
#define regk_ddr2_rw_dll_ctrl_default             0x00000000
#define regk_ddr2_rw_dll_ctrl_size                0x00000004
#define regk_ddr2_rw_dqs_dll_ctrl_default         0x00000000
#define regk_ddr2_rw_dqs_dll_ctrl_size            0x00000004
#define regk_ddr2_rw_latency_default              0x00000000
#define regk_ddr2_rw_phy_cfg_default              0x00000000
#define regk_ddr2_rw_pwr_down_default             0x00000000
#define regk_ddr2_rw_timing_default               0x00000000
#define regk_ddr2_s1Gb                            0x0000001a
#define regk_ddr2_s256Mb                          0x0000000f
#define regk_ddr2_s2Gb                            0x00000027
#define regk_ddr2_s4Gb                            0x00000042
#define regk_ddr2_s512Mb                          0x00000015
#define regk_ddr2_temp0_85                        0x00000618
#define regk_ddr2_temp85_95                       0x0000030c
#define regk_ddr2_term150                         0x00000002
#define regk_ddr2_term50                          0x00000003
#define regk_ddr2_term75                          0x00000001
#define regk_ddr2_test                            0x00000080
#define regk_ddr2_weak                            0x00000000
#define regk_ddr2_wr2                             0x00000200
#define regk_ddr2_wr3                             0x00000400
#define regk_ddr2_yes                             0x00000001
#endif /* __ddr2_defs_asm_h */
