
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>
#include "kd_flashlight.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include "kd_camera_hw.h"
#ifndef TRUE
#define TRUE KAL_TRUE
#endif
#ifndef FALSE
#define FALSE KAL_FALSE
#endif
 
/* device name and major number */
#define STROBE_DEVNAME            "leds_strobe"

#define DELAY_MS(ms) {mdelay(ms);}//unit: ms(10^-3)
#define DELAY_US(us) {mdelay(us);}//unit: us(10^-6)
#define DELAY_NS(ns) {mdelay(ns);}//unit: ns(10^-9)
#define PFX "[LEDS_STROBE]"
#define PK_DBG_NONE(fmt, arg...)    do {} while (0)
#define PK_DBG_FUNC(fmt, arg...)    printk(KERN_INFO PFX "%s: " fmt, __FUNCTION__ ,##arg)

#define PK_WARN(fmt, arg...)        printk(KERN_WARNING PFX "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_NOTICE(fmt, arg...)      printk(KERN_NOTICE PFX "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_INFO(fmt, arg...)        printk(KERN_INFO PFX "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_TRC_FUNC(f)              printk(PFX "<%s>\n", __FUNCTION__);
#define PK_TRC_VERBOSE(fmt, arg...) printk(PFX fmt, ##arg)

//#define DEBUG_LEDS_STROBE
#ifdef DEBUG_LEDS_STROBE
#define PK_DBG PK_DBG_FUNC
#define PK_TRC PK_DBG_NONE //PK_TRC_FUNC
#define PK_VER PK_DBG_NONE //PK_TRC_VERBOSE
#define PK_ERR(fmt, arg...)         printk(KERN_ERR PFX "%s: " fmt, __FUNCTION__ ,##arg)
#else
#define PK_DBG(a,...)
#define PK_TRC(a,...)
#define PK_VER(a,...)
#define PK_ERR(a,...)
#endif

struct strobe_data{
    spinlock_t lock;
    wait_queue_head_t read_wait;
    struct semaphore sem;
};
static struct work_struct g_tExpEndWorkQ;      // --- Work queue ---
static struct work_struct g_tTimeOutWorkQ;      // --- Work queue ---
static XGPT_CONFIG	g_tStrobeXGPTConfig;		    // --- Interrupt Config ---

#if 0
static struct class *strobe_class = NULL;
static struct device *strobe_device = NULL;
static dev_t strobe_devno;
static struct cdev strobe_cdev;
#endif
static struct strobe_data strobe_private;

static u32 strobe_Res = 0;
static u32 strobe_Timeus = 0;
static BOOL g_strobe_On = FALSE;
static u32 strobe_width = 0; //0 is disable
static eFlashlightState strobe_eState = FLASHLIGHTDRV_STATE_PREVIEW;
#define GPIO_CAMERA_FLASH_MODE GPIO95
#define GPIO_CAMERA_FLASH_MODE_M_GPIO  GPIO_MODE_00
    //CAMERA-FLASH-T/F
        //H:flash mode
        //L:torch mode
#define GPIO_CAMERA_FLASH_EN GPIO46
#define GPIO_CAMERA_FLASH_EN_M_GPIO  GPIO_MODE_00
    //CAMERA-FLASH-EN


ssize_t gpio_FL_Init(void) {
    //set torch mode
    if(mt_set_gpio_mode(GPIO_CAMERA_FLASH_MODE,GPIO_CAMERA_FLASH_MODE_M_GPIO)){PK_DBG("[constant_flashlight] set gpio mode failed!! \n");}
    if(mt_set_gpio_dir(GPIO_CAMERA_FLASH_MODE,GPIO_DIR_OUT)){PK_DBG("[constant_flashlight] set gpio dir failed!! \n");}
    if(mt_set_gpio_out(GPIO_CAMERA_FLASH_MODE,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    //Init. to disable
    if(mt_set_gpio_mode(GPIO_CAMERA_FLASH_EN,GPIO_CAMERA_FLASH_MODE_M_GPIO)){PK_DBG("[constant_flashlight] set gpio mode failed!! \n");}
    if(mt_set_gpio_dir(GPIO_CAMERA_FLASH_EN,GPIO_DIR_OUT)){PK_DBG("[constant_flashlight] set gpio dir failed!! \n");}
    if(mt_set_gpio_out(GPIO_CAMERA_FLASH_EN,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    return 0;
}
ssize_t gpio_FL_Uninit(void) {
    //Uninit. to disable
    if(mt_set_gpio_mode(GPIO_CAMERA_FLASH_EN,GPIO_CAMERA_FLASH_MODE_M_GPIO)){PK_DBG("[constant_flashlight] set gpio mode failed!! \n");}
    if(mt_set_gpio_dir(GPIO_CAMERA_FLASH_EN,GPIO_DIR_OUT)){PK_DBG("[constant_flashlight] set gpio dir failed!! \n");}
    if(mt_set_gpio_out(GPIO_CAMERA_FLASH_EN,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    return 0;
}
ssize_t gpio_FL_Enable(void) {
    //Enable
    if(mt_set_gpio_out(GPIO_CAMERA_FLASH_EN,GPIO_OUT_ONE)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    return 0;
}
ssize_t gpio_FL_Disable(void) {
    //Enable
    if(mt_set_gpio_out(GPIO_CAMERA_FLASH_EN,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    return 0;
}
ssize_t gpio_FL_dim_duty(kal_uint8 duty) {
    //N/A
    
    return 0;
}

//abstract interface
#define FL_Init gpio_FL_Init
#define FL_Uninit gpio_FL_Uninit
#define FL_Enable gpio_FL_Enable
#define FL_Disable gpio_FL_Disable
#define FL_dim_duty gpio_FL_dim_duty

#define PREFLASH_PROFILE 0

#if PREFLASH_PROFILE
static void ledDrvProfile(unsigned int logID)
{
struct timeval tv1={0,0};
unsigned int u4MS;
    do_gettimeofday(&tv1);
    u4MS =  (unsigned int)(tv1.tv_sec * 1000 + tv1.tv_usec /1000);
    printk("[ledDrvProfile]state:[%d],time:[%d]ms \n",logID,u4MS);
}
#endif


static int strobe_WDTConfig(void)
{
    return 0;
}
static void strobe_WDTStart(void)
{
    //XGPT_Start(g_tStrobeXGPTConfig.num);
    //PK_DBG("[constant_flashlight] WDT start\n");
}
static void strobe_WDTStop(void)
{
    //XGPT_Stop(g_tStrobeXGPTConfig.num);
    //PK_DBG("[constant_flashlight] DT stop\n");
}

static int constant_flashlight_ioctl(MUINT32 cmd, MUINT32 arg)
{
    int i4RetValue = 0;
    int iFlashType = (int)FLASHLIGHT_NONE;
    
    PK_DBG("[constant_flashlight] start\n");

    //when ON state , only disable command is permitted.
    if ( (TRUE == g_strobe_On) && !((FLASHLIGHTIOC_T_ENABLE == cmd) && (0 == arg)) )

    {
        PK_DBG("[constant_flashlight]  is already ON OR check parameters!\n");
        //goto strobe_ioctl_error;
        return i4RetValue;
    }

    switch(cmd)
    {
    	case FLASHLIGHTIOC_T_ENABLE :
            if (arg&&strobe_width){
                //enable strobe watchDog timer.
                strobe_WDTConfig();
                strobe_WDTStart();
                if(FL_Enable()){
                    strobe_WDTStop();
                    PK_ERR("[constant_flashlight] FL_Enable fail!\n");
                    goto strobe_ioctl_error;
                }
                g_strobe_On = TRUE;
            }
            else{
                if(FL_Disable()){
                    PK_ERR("[constant_flashlight] FL_Disable fail!\n");
                    goto strobe_ioctl_error;
                }
                g_strobe_On = FALSE;

                //disable strobe watchDog timer.
                strobe_WDTStop();
            }
    		break;
        case FLASHLIGHTIOC_T_LEVEL:
            if(arg>32) {arg=32;}
            strobe_width = arg;
            PK_DBG("[constant_flashlight] level:%d \n",(int)arg);
            if (arg > 0)
            {
                if(FL_dim_duty((kal_int8)arg-1)){
                    //0(weak)~31(strong)
                    PK_ERR("[constant_flashlight] FL_dim_duty fail!\n");
                    //i4RetValue = -EINVAL;
                    goto strobe_ioctl_error;
                }
            }
            break;
        case FLASHLIGHTIOC_T_FLASHTIME:
            strobe_Timeus = (u32)arg;
            PK_DBG("[constant_flashlight] strobe_Timeus:%d \n",(int)strobe_Timeus);
            break;
        case FLASHLIGHTIOC_T_STATE:
            strobe_eState = (eFlashlightState)arg;
            break;
        case FLASHLIGHTIOC_G_FLASHTYPE:
            iFlashType = FLASHLIGHT_LED_CONSTANT;
            if(copy_to_user((void __user *) arg , (void*)&iFlashType , _IOC_SIZE(cmd)))
            {
                PK_DBG("[constant_flashlight] ioctl copy to user failed\n");
                return -EFAULT;
            }
            break;
            
    	default :
    		PK_DBG("[constant_flashlight] No such command \n");
    		i4RetValue = -EPERM;
    		break;
    }

    PK_DBG("[constant_flashlight] done\n");
    return i4RetValue;

strobe_ioctl_error:
    PK_DBG("[constant_flashlight] Error or ON state!\n");
    return -EPERM;
}


static void strobe_expEndWork(struct work_struct *work)
{
    constant_flashlight_ioctl(FLASHLIGHTIOC_T_ENABLE, 0);
    PK_DBG("[constant_flashlight] FLASHLIGHTIOC_T_ENABLE:0\n");
}

static void strobe_timeOutWork(struct work_struct *work)
{
    constant_flashlight_ioctl(FLASHLIGHTIOC_T_ENABLE, 0);
    PK_DBG("[constant_flashlight] Force OFF LED\n");
}

static int constant_flashlight_open(void *pArg)
{
    int i4RetValue = 0;
    PK_DBG("[constant_flashlight] start\n");

    if (0 == strobe_Res)
    {
        FL_Init();

		//enable HW here if necessary
        if(FL_dim_duty(0)){
            //0(weak)~31(strong)
            PK_ERR("[constant_flashlight] FL_dim_duty fail!\n");
            i4RetValue = -EINVAL;
        }
    }//

    spin_lock_irq(&strobe_private.lock);

    if(strobe_Res)
    {
        PK_ERR("[constant_flashlight] busy!\n");
        i4RetValue = -EBUSY;
    }
    else
    {
        strobe_Res += 1;
    }

    //LED On Status
    g_strobe_On = FALSE;

    spin_unlock_irq(&strobe_private.lock);

	// --- WorkQueue ---
    INIT_WORK(&g_tExpEndWorkQ,strobe_expEndWork);
    INIT_WORK(&g_tTimeOutWorkQ,strobe_timeOutWork);


#if 0
	// --- Config Interrupt ---
    XGPT_Reset(XGPT5);
    g_tStrobeXGPTConfig.num          = XGPT5;
    g_tStrobeXGPTConfig.mode         = XGPT_ONE_SHOT;
    g_tStrobeXGPTConfig.clkDiv       = XGPT_CLK_DIV_128;
    g_tStrobeXGPTConfig.bIrqEnable   = TRUE;
    g_tStrobeXGPTConfig.u4Compare    = 0;
	XGPT_Init(g_tStrobeXGPTConfig.num, strobe_xgptIsr);
	if (XGPT_Config(g_tStrobeXGPTConfig) == FALSE)
	{
        PK_ERR("[constant_flashlight] XGPTISR Config Fail\n");
		return -EPERM;
	}
#endif

#if 0
	XGPT_Start(g_tStrobeXGPTConfig.num);
	XGPT_Stop(g_tStrobeXGPTConfig.num);
    XGPT_Restart(g_tStrobeXGPTConfig.num);
#endif

    PK_DBG("[constant_flashlight] Done\n");

    return i4RetValue;

}

static int constant_flashlight_release(void *pArg)
{
    PK_DBG("[constant_flashlight] start\n");

    if (strobe_Res)
    {
        spin_lock_irq(&strobe_private.lock);

        strobe_Res = 0;
        strobe_Timeus = 0;

        //LED On Status
        g_strobe_On = FALSE;

        spin_unlock_irq(&strobe_private.lock);

    	//un-init. HW here if necessary
        if(FL_dim_duty(0)){
            PK_ERR("[constant_flashlight] FL_dim_duty fail!\n");
        }

    	FL_Uninit();
    	
        XGPT_Stop(g_tStrobeXGPTConfig.num);
    }

    PK_DBG("[constant_flashlight] Done\n");

    return 0;

}


FLASHLIGHT_FUNCTION_STRUCT	constantFlashlightFunc=
{
	constant_flashlight_open,
	constant_flashlight_release,
	constant_flashlight_ioctl
};

MUINT32 constantFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc) { 
    if (pfFunc!=NULL) {
        *pfFunc=&constantFlashlightFunc;
    }
    return 0;
}

#if 0
/*****************************************************************************/
/* Kernel interface */
static struct file_operations strobe_fops = {
    .owner      = THIS_MODULE,
    .ioctl      = strobe_ioctl,
    .open       = strobe_open,
    .release    = strobe_release,
};

#define ALLOC_DEVNO
static int strobe_probe(struct platform_device *dev)
{
    int ret = 0, err = 0;

	PK_DBG("[constant_flashlight] start\n");

#ifdef ALLOC_DEVNO
    ret = alloc_chrdev_region(&strobe_devno, 0, 1, STROBE_DEVNAME);
    if (ret) {
        PK_ERR("[constant_flashlight] alloc_chrdev_region fail: %d\n", ret);
        goto strobe_probe_error;
    } else {
        PK_DBG("[constant_flashlight] major: %d, minor: %d\n", MAJOR(strobe_devno), MINOR(strobe_devno));
    }
    cdev_init(&strobe_cdev, &strobe_fops);
    strobe_cdev.owner = THIS_MODULE;
    err = cdev_add(&strobe_cdev, strobe_devno, 1);
    if (err) {
        PK_ERR("[constant_flashlight] cdev_add fail: %d\n", err);
        goto strobe_probe_error;
    }
#else
    #define STROBE_MAJOR 242
    ret = register_chrdev(STROBE_MAJOR, STROBE_DEVNAME, &strobe_fops);
    if (ret != 0) {
        PK_ERR("[constant_flashlight] Unable to register chardev on major=%d (%d)\n", STROBE_MAJOR, ret);
        return ret;
    }
    strobe_devno = MKDEV(STROBE_MAJOR, 0);
#endif


    strobe_class = class_create(THIS_MODULE, "strobedrv");
    if (IS_ERR(strobe_class)) {
        PK_ERR("[constant_flashlight] Unable to create class, err = %d\n", (int)PTR_ERR(strobe_class));
        goto strobe_probe_error;
    }

    strobe_device = device_create(strobe_class, NULL, strobe_devno, NULL, STROBE_DEVNAME);
    if(NULL == strobe_device){
        PK_ERR("[constant_flashlight] device_create fail\n");
        goto strobe_probe_error;
    }

    /*initialize members*/
    spin_lock_init(&strobe_private.lock);
    init_waitqueue_head(&strobe_private.read_wait);
    init_MUTEX(&strobe_private.sem);

    //LED On Status
    g_strobe_On = FALSE;

    PK_DBG("[constant_flashlight] Done\n");
    return 0;

strobe_probe_error:
#ifdef ALLOC_DEVNO
    if (err == 0)
        cdev_del(&strobe_cdev);
    if (ret == 0)
        unregister_chrdev_region(strobe_devno, 1);
#else
    if (ret == 0)
        unregister_chrdev(MAJOR(strobe_devno), STROBE_DEVNAME);
#endif
    return -1;
}

static int strobe_remove(struct platform_device *dev)
{

    PK_DBG("[constant_flashlight] start\n");

#ifdef ALLOC_DEVNO
    cdev_del(&strobe_cdev);
    unregister_chrdev_region(strobe_devno, 1);
#else
    unregister_chrdev(MAJOR(strobe_devno), STROBE_DEVNAME);
#endif
    device_destroy(strobe_class, strobe_devno);
    class_destroy(strobe_class);

    //LED On Status
    g_strobe_On = FALSE;

    PK_DBG("[constant_flashlight] Done\n");
    return 0;
}


static struct platform_driver strobe_platform_driver =
{
    .probe      = strobe_probe,
    .remove     = strobe_remove,
    .driver     = {
        .name = STROBE_DEVNAME,
		.owner	= THIS_MODULE,
    },
};

static struct platform_device strobe_platform_device = {
    .name = STROBE_DEVNAME,
    .id = 0,
    .dev = {
    }
};

static int __init strobe_init(void)
{
    int ret = 0;
    PK_DBG("[constant_flashlight] start\n");

	ret = platform_device_register (&strobe_platform_device);
	if (ret) {
        PK_ERR("[constant_flashlight] platform_device_register fail\n");
        return ret;
	}

    ret = platform_driver_register(&strobe_platform_driver);
	if(ret){
		PK_ERR("[constant_flashlight] platform_driver_register fail\n");
		return ret;
	}

	PK_DBG("[constant_flashlight] done!\n");
    return ret;
}

static void __exit strobe_exit(void)
{
    PK_DBG("[constant_flashlight] start\n");
    platform_driver_unregister(&strobe_platform_driver);
    //to flush work queue
    //flush_scheduled_work();
    PK_DBG("[constant_flashlight] done!\n");
}

/*****************************************************************************/
module_init(strobe_init);
module_exit(strobe_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jackie Su <jackie.su@mediatek.com>");
MODULE_DESCRIPTION("LED strobe control Driver");


/* LED flash control for capture mode*/
ssize_t strobe_StillExpCfgStart(void)
{
    if (strobe_width&&(FLASHLIGHTDRV_STATE_STILL == strobe_eState))
    {
        strobe_ioctl(0,0,FLASHLIGHTIOC_T_ENABLE, 1);
        PK_DBG("[constant_flashlight] FLASHLIGHTIOC_T_ENABLE:1\n");
    }
#if PREFLASH_PROFILE
    ledDrvProfile(999);
#endif
    return 0;
}

ssize_t strobe_StillExpEndIrqCbf(void)
{
    if (strobe_width&&(FLASHLIGHTDRV_STATE_STILL == strobe_eState))
    {
        schedule_work(&g_tExpEndWorkQ);
        strobe_eState = FLASHLIGHTDRV_STATE_PREVIEW;
    }
    return 0;
}

EXPORT_SYMBOL(strobe_StillExpCfgStart);
EXPORT_SYMBOL(strobe_StillExpEndIrqCbf);
#endif

