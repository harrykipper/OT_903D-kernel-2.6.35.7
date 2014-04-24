

#ifndef __ASM_MIPS_MACH_PNX833X_IRQ_H
#define __ASM_MIPS_MACH_PNX833X_IRQ_H
#if defined(CONFIG_SOC_PNX8335)
	#define PNX833X_PIC_NUM_IRQ			58
#else
	#define PNX833X_PIC_NUM_IRQ			37
#endif

#define MIPS_CPU_NUM_IRQ				8
#define PNX833X_GPIO_NUM_IRQ			16

#define MIPS_CPU_IRQ_BASE				0
#define PNX833X_PIC_IRQ_BASE			(MIPS_CPU_IRQ_BASE + MIPS_CPU_NUM_IRQ)
#define PNX833X_GPIO_IRQ_BASE			(PNX833X_PIC_IRQ_BASE + PNX833X_PIC_NUM_IRQ)
#define NR_IRQS							(MIPS_CPU_NUM_IRQ + PNX833X_PIC_NUM_IRQ + PNX833X_GPIO_NUM_IRQ)

#endif
