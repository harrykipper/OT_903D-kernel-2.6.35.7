
#ifndef __strmux_defs_h
#define __strmux_defs_h

/* Main access macros */
#ifndef REG_RD
#define REG_RD( scope, inst, reg ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR
#define REG_WR( scope, inst, reg, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_VECT
#define REG_RD_VECT( scope, inst, reg, index ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_VECT
#define REG_WR_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT
#define REG_RD_INT( scope, inst, reg ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR_INT
#define REG_WR_INT( scope, inst, reg, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT_VECT
#define REG_RD_INT_VECT( scope, inst, reg, index ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_INT_VECT
#define REG_WR_INT_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_TYPE_CONV
#define REG_TYPE_CONV( type, orgtype, val ) \
  ( { union { orgtype o; type n; } r; r.o = val; r.n; } )
#endif

#ifndef reg_page_size
#define reg_page_size 8192
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg + \
    (index) * STRIDE_##scope##_##reg )
#endif

/* C-code for register scope strmux */

/* Register rw_cfg, scope strmux, type rw */
typedef struct {
  unsigned int dma0  : 2;
  unsigned int dma1  : 2;
  unsigned int dma2  : 2;
  unsigned int dma3  : 2;
  unsigned int dma4  : 2;
  unsigned int dma5  : 2;
  unsigned int dma6  : 2;
  unsigned int dma7  : 2;
  unsigned int dummy1 : 2;
  unsigned int dma9  : 2;
  unsigned int dummy2 : 2;
  unsigned int dma11 : 2;
  unsigned int dummy3 : 8;
} reg_strmux_rw_cfg;
#define REG_RD_ADDR_strmux_rw_cfg 0
#define REG_WR_ADDR_strmux_rw_cfg 0


/* Constants */
enum {
  regk_strmux_eth                          = 0x00000001,
  regk_strmux_h264                         = 0x00000001,
  regk_strmux_iop                          = 0x00000001,
  regk_strmux_jpeg                         = 0x00000001,
  regk_strmux_off                          = 0x00000000,
  regk_strmux_rw_cfg_default               = 0x00000000,
  regk_strmux_ser0                         = 0x00000002,
  regk_strmux_ser1                         = 0x00000002,
  regk_strmux_ser2                         = 0x00000002,
  regk_strmux_ser3                         = 0x00000002,
  regk_strmux_ser4                         = 0x00000002,
  regk_strmux_sser                         = 0x00000001,
  regk_strmux_strcop                       = 0x00000001
};
#endif /* __strmux_defs_h */
