

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/mt65xx.h>
#include <cust_kpd.h>
 
/*=======================================================================*/
/* CONFIGURATION                                                         */
/*=======================================================================*/
#undef CFG_CLKS_IN_HZ           /* everything, incl board info, in Hz */ 
#include <./config.h>           /* Boot Medium is auto generated by building*/ 
#define CFG_RESERVE_MEM_FOR_RIL /* Jau add the option to reserve 6MB RAM space for RIL ARM7 MAUI image */
//#define CFG_PWM_LED             /* Jau add for William phase in LED light */
#define CFG_LCD                 /* Jau add to support lcd driver and show mkt logo */
#define CONFIG_CFB_CONSOLE      /* Shu-Hsin add to support console framebuffer driver */ 
#define CFB_CONSOLE_ON			/* Xuecheng Add for video-console */
#define CFG_POWER_CHARGING      /* power scheme add uboot charging mode   */
#define CFG_UBOOT_PROFILING     /* Jau add to profile UBoot boot time     */
#define CFG_NO_BOOTM
#define CFG_NO_GZIP 
//#define CFG_MMC_FACTORY         /* Support factory mode from MMC card */
#define CFG_HAS_USB  
#define CM3623                 /* for fix hw issue */

#ifndef CFG_NOR_BOOT
    #define CONFIG_SYS_NO_FLASH		/* no support for nor flash */
#endif 

//#undef CONFIG_USE_IRQ           /* no support for IRQs  */
/*Hong-Rong: enable interrupt*/
#define CONFIG_USE_IRQ
/*Hong-Rong: enable interrupt*/
#ifdef CONFIG_USE_IRQ
  #define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
  #define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

/*=======================================================================*/
/* BOOT MODE                                                             */
/*=======================================================================*/
#define CFG_META_MODE        

#define CFG_RECOVERY_MODE

#define CFG_FACTORY_MODE

#if 0 //Waiting for Driver...
  #define MONITOR_RECOVERY_MODE   
#endif

/*=======================================================================*/
/* POWER                                                                 */
/*=======================================================================*/
//#define NO_POWER_OFF

/*=======================================================================*/
/* Keypad                                                                */
/*=======================================================================*/
//#define MT65XX_META_KEY		9	/* KEY_HOME */
//#define MT65XX_RECOVERY_KEY	1	/* KEY_VOLUMEUP */
//#define MT65XX_FACTORY_KEY	2	/* KEY_VOLUMEDOWN */

/*=======================================================================*/
/* Partitions                                                            */
/*=======================================================================*/
#if defined(CFG_NAND_BOOT)
	#define CFG_USE_MBL_PARTITION
    #define CFG_USE_UBOOT_PARTITION
    #define CFG_USE_SECURE_PARTITION
    #define CFG_USE_LOGO_PARTITION

	//----------------------------------------
	// use Android Boot Image instead of kernel and rootfs
    #define CFG_USE_BOOTIMG_PARTITION
	//----------------------------------------

    #define CFG_USE_ANDROID_SYSIMG_PARTITION
    #define CFG_USE_CUSTPACK_PARTITION
    #define CFG_USE_RECOVERY_PARTITION
    #define CFG_USE_SECSTATIC_PARTITION
    #define CFG_USE_CACHE_PARTITION
	#define CFG_USE_NVRAM_PARTITION
	#define CFG_USE_RECOVERY_PARTITION	
	#define CFG_USE_MISC_PARTITION	
    #define CFG_USE_EXPDB_PARTITION
    #define CFG_USE_USER_PARTITION
#elif defined (CFG_MMC_BOOT)
	#define CFG_USE_MBL_PARTITION
    #define CFG_USE_UBOOT_PARTITION
    #define CFG_USE_CUSTOME_PARTITION
    #define CFG_USE_BOOTIMG_PARTITION    
    #define CFG_USE_KERNEL_PARTITION
    #define CFG_USE_ROOTFS_GZ_PARTITION
    #define CFG_USE_LOGO_PARTITION
    #define CFG_USE_USER_PARTITION
#endif


/*=======================================================================*/
/* BOARD/CPU                                                             */
/*=======================================================================*/
#define CFG_CPU					"ARM1176"

/*=======================================================================*/
/* CPU/MEM CLK and TIMER                                                 */
/*=======================================================================*/
#define MT65XX_HW_VER_E1        0x8a00
#define MT65XX_HW_VER_E2        0x8a01


#define CFG_HZ		     		(100)
#define CFG_BOARD_FREQ          (CPU_416MHZ_EMI_104MHZ)
    #define CFG_CPU_CLK          416000000
    #define CFG_EMI_CLK          EMI_104MHZ
    #define CFG_PLL_CLK          APLL_416
    #define CFG_MCU_MODE	     MCU_SYNC_MODE
    #define CFG_ARM_DIVISOR		 ARM_DIV_1
    #define CFG_EMI_DIVISOR		 EMI_DIV_2
    
#if 0 //Waiting for driver...
  #define CONFIG_DISPLAY_CPUINFO   1  /* display cpu info (and speed) */
  #define CONFIG_DISPLAY_BOARDINFO 1	/* display board info		*/
#endif
/*=======================================================================*/
/* LCM DISPLAY                                                           */
/*=======================================================================*/
#define CFG_DISPLAY_WIDTH       (DISP_GetScreenWidth())
#define CFG_DISPLAY_HEIGHT      (DISP_GetScreenHeight())
#define CFG_DISPLAY_BPP         (16)

/*=======================================================================*/
/* UART/SERIAL                                                           */
/*=======================================================================*/
#define CONFIG_SERIAL1           1
#define CONFIG_CONS_INDEX        1
#define CONFIG_BAUDRATE          921600
#define CONFIG_SYS_BAUDRATE_TABLE       {115200, 921600}

/*=======================================================================*/
/* DRAM                                                                  */
/*=======================================================================*/

#ifdef CFG_RESERVE_MEM_FOR_RIL
  #if defined (MODEM_3G)    
    #define RIL_SIZE                0x1600000
  #elif defined (MODEM_2G)
    #define RIL_SIZE                0x0A00000
  #endif  
#else
    #define RIL_SIZE  0    
#endif


#define CONFIG_NR_DRAM_BANKS        DRAM_BANKS_NR

#define SDRAM_BASE					0x00000000
#define CONFIG_SYS_MEMTEST_START           (SDRAM_BASE+SZ_8M)
#define CONFIG_SYS_MEMTEST_END             (SDRAM_BASE+SZ_16M)

/*=======================================================================*/
/* NAND FLASH                                                            */
/*=======================================================================*/
#ifdef CFG_NAND_BOOT
#define CONFIG_SYS_MAX_NAND_DEVICE 	 1	/* max. number of NAND devices */
#define CONFIG_SYS_NAND_CS				 1
#define CONFIG_SYS_NAND_ADDR 			 0x80032000
#define CONFIG_SYS_NAND_BASE			 CONFIG_SYS_NAND_ADDR
#define CONFIG_SYS_NAND_SELECT_DEVICE   1

#define CFG_NAND_WP
#define NAND_MAX_CHIPS			 1

#define CFG_MT65XX_NAND_ID       0x4E414E44
/* CC: modify for MT6573 poring temporarily. Need Koshi to fix it. */
#define CFG_MT6573_NAND_ID       0x4E414E44
#endif

/*=======================================================================*/
/* JFFS2 PARTITIONS                                                      */
/*=======================================================================*/
#undef CONFIG_JFFS2_CMDLINE			/* will increase a lot of size */

#ifdef CFG_NAND_BOOT
    //#define CONFIG_JFFS2_CMDLINE
    //#define CONFIG_JFFS2_NAND
    #ifdef CONFIG_JFFS2_NAND
    	#define CONFIG_JFFS2_DEV			"uboot"
    	#define CONFIG_JFFS2_PART_SIZE		0x00080000
    	#define CONFIG_JFFS2_PART_OFFSET	0x00000000
    #endif
#endif /* CFG_NAND_BOOT */

/*=======================================================================*/
/* MMC/SD CARD                                                           */
/*=======================================================================*/
#if defined(CFG_MMC_BOOT) || defined(CFG_MMC_FACTORY)
#define CONFIG_MMC					1
#endif

#define CONFIG_DOS_PARTITION		1
#define CFG_MMC_BASE				0xF0000000

#define CFG_MMC_HOST_NUM            1
#define CFG_MMC_HOST                {                                    \
                                        {.base = MSDC1_BASE,             \
                                         .boot_type = FAT_BOOT,          \
                                         .caps = MMC_CAP_4_BIT_DATA |    \
                                                 MMC_CAP_MULTIWRITE,     \
                                        },                               \
                                    }

/*=======================================================================*/
/* U-BOOT ENVIRONMENT                                                    */
/*=======================================================================*/
#define CONFIG_MISC_INIT_R
#define BOARD_LATE_INIT          (1)

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_LOAD_ADDR			 0x00000000

/* Size of malloc() pool */
#define CONFIG_ENV_SIZE             (SZ_128K)
#define CONFIG_SYS_MALLOC_LEN           (CONFIG_ENV_SIZE + SZ_512K)
#define CONFIG_SYS_GBL_DATA_SIZE        (128)

#define CONFIG_SYS_LONGHELP			 1
#define CONFIG_SYS_PROMPT               "u-boot> "
#define CONFIG_SYS_CBSIZE               256  		 /* Console I/O Buffer Size */

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE               (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS              16          /* max number of command args */
#define CONFIG_SYS_BARGSIZE             CONFIG_SYS_CBSIZE  /* Boot Argument Buffer Size */

#define CONFIG_SYS_MONITOR_BASE		 TEXT_BASE
#define CONFIG_SYS_MONITOR_LEN			 SZ_128K      /* Reserve 1 sector */

#ifdef CFG_NAND_BOOT
#define CONFIG_ENV_ADDR             (CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN)
#define CONFIG_ENV_OFFSET			 (CONFIG_ENV_ADDR + CONFIG_SYS_MONITOR_LEN) /* Environment after Monitor */
#define CONFIG_ENV_IS_NOWHERE		 1
#else
#define CONFIG_ENV_ADDR             (CONFIG_ENV_ADDR + CONFIG_SYS_MONITOR_LEN)
#define CONFIG_ENV_OFFSET			 (CONFIG_ENV_ADDR + CONFIG_SYS_MONITOR_LEN) /* Environment after Monitor */
#define CONFIG_ENV_IS_NOWHERE		 1
#endif

//#define LOW_LEVEL_SRAM_STACK	 (0x40020600) // Jau modify for E1 Chip
                                              // E1 & E2 can't access this address
/* CC: temporarily use system FlexL2 as the low_lovel SRAM stack for MT6573 porting*/
#define LOW_LEVEL_SRAM_STACK	 (0x90002000)                                              

/*=======================================================================*/
/* U-BOOT AUTOBOOT                                                       */
/*=======================================================================*/
#define CONFIG_BOOTDELAY		 1			    /* autoboot after in secs */
/* Remove for mt6573 porting */
#define CONFIG_BOOTCOMMAND		 "msdc_boot;nand_boot"	/* autoboot command */

/* CC: add temporarily for MT6573 UT */
//#define CFG_BASIC_CMDS CONFIG_CMD_MEMORY

/*=======================================================================*/
/* U-BOOT COMMANDS                                                       */
/*=======================================================================*/
/* Basic Command */
#define CONFIG_CMD_NAND //Hong-Rong: Open to develope nand driver
#define CONFIG_SYS_HZ   1000


/* additional commands */

/* this must be included AFTER the definition of CONFIG_COMMANDS (if any) */
//Hong-Rong: comment for porting
//#if 0
//#include <cmd_confdefs.h>
//#endif

/*=======================================================================*/
/* LINUX KERNEL ENVIRONMENT                                              */
/*=======================================================================*/
#define CFG_ZIMAGE_BOOT				0

#if CFG_ZIMAGE_BOOT
	#define CFG_KIMAGE_NAME			"zImage"
	#define CFG_KIMAGE_LOAD_ADDR	0x00508000
#else
	#define CFG_KIMAGE_NAME			"Image"
    
	#define CFG_KIMAGE_LOAD_ADDR	 (RIL_SIZE + 0x8000)
	//---------------------------------------------------
    #define CFG_BOOTIMG_LOAD_ADDR    (RIL_SIZE + 0x8000) 
	//---------------------------------------------------
	
#endif



#define CFG_RAMDISK_NAME			"rd6573.gz"
#define CFG_RECOVERY_RAMDISK_NAME   "recoevry_rd6573.gz"
#define CFG_FACTORY_NAME            "factory.img"

#define CFG_RAMDISK_LOAD_ADDR		(RIL_SIZE + 0x0D00000)

#define CFG_BOOTARGS_ADDR			(RIL_SIZE + 0x100)

#define CFG_IMAGE_NAME              "ttsystem"
#define CFG_IMAGE_LOAD_ADDR         0x01000000

#define CFG_LOGO_NAME               "logo"
#define CFG_META_LOGO_NAME          "meta_logo"

/*=======================================================================*/
/* LINUX KERNEL BOOTARGS                                                 */
/*=======================================================================*/
#define CONFIG_CMDLINE_TAG       1    /* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG        1
#define CONFIG_REVISION_TAG      1
#define CONFIG_VIDEOLFB_TAG		 1

//Hong-Rong: remove for mt6573 porting; [03/13/11,zaikuo,add passing video LFB param to kernel]
#if CFG_LCM_DUMMY 
#define CONFIG_VIDEOLFB_TAG		 0    /* if lcm is NOT inited, don't pass video LFB param to kernel */
#else
#define CONFIG_VIDEOLFB_TAG		 1
#endif

/* Jau Modify  64M -> 128M --> 122M */

#ifdef CFG_NET_BOOT
#define CONFIG_BOOTARGS	         "mem=32M console=ttyMT0,921600n8 noinitrd root=/dev/nfs rw nfsroot=128.247.77.158:/home/a0384864/wtbu/rootfs ip=dhcp"
#else
    #define CONFIG_BOOTARGS "console=tty0 console=ttyMT3,921600n1 root=/dev/ram" /* Hong-Rong: modify for MT6573 IT */
#endif

/*=======================================================================*/
/* USB                                                                   */
/*=======================================================================*/
#define CONFIG_USBD_LANG            "0409"
#define CONFIG_USBD_MANUFACTURER    "MediaTek"
#define CONFIG_USBD_PRODUCT_NAME    "MT6573"
#if 1   //MT6573 VCOM
#define CONFIG_USBD_VENDORID        0x0E8D
#define CONFIG_USBD_PRODUCTID       0x2000
#endif

/*======================================================================*/
/*New Configurations in u-boot-2010.06                                  */
/*======================================================================*/
#define CONFIG_SYS_MAX_FLASH_BANKS	1	  /* Max number of flash banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	 128	/* Max number of sectors per flash	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	    /* Timeout for Flash Write (in ms) */
//#define CONFIG_SYS_FLASH_CFI
//#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_ENV_IS_IN_FLASH	0

/*======================================================================*/
/* MMU / Cache Operation                                                */
/*======================================================================*/
#define CONFIG_SYS_NO_DCACHE


#endif							/* __CONFIG_H */
