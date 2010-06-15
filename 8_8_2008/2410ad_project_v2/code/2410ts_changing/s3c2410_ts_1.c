

#include <linux/config.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/irq.h>

#include <asm/arch-s3c2410/regs-adc.h>
#include <asm/arch/regs-gpio.h>
#include <asm/arch-s3c2410/s3c2410_ts.h>
#include <asm/hardware/clock.h>





static char *s3c2410ts_name = "s3c2410 TouchScreen";

/*
 * Per-touchscreen data.
 */

struct s3c2410ts {
	struct input_dev dev;
	long xp;
	long yp;
	int count;
	int shift;
	char phys[32];
};

static struct s3c2410ts ts;
static void __iomem *base_addr;





static struct clk	*adc_clock;

/*
 * The functions for inserting/removing us as a module.
 */


static int __init s3c2410ts_probe(struct device *dev)
{
	struct s3c2410_ts_mach_info *info;

	info = ( struct s3c2410_ts_mach_info *)dev->platform_data;

	if (!info)
	{
		printk(KERN_ERR "Hm... too bad : no platform data for ts\n");
		return -EINVAL;
	}

	adc_clock = clk_get(NULL, "adc");
	if (!adc_clock) {
		printk(KERN_ERR "failed to get adc clock source\n");
		return -ENOENT;
	}
	clk_use(adc_clock);
	clk_enable(adc_clock);


	base_addr=ioremap(S3C2410_PA_ADC,0x20);
	if (base_addr == NULL) {
		printk(KERN_ERR "Failed to remap register block\n");
		return -ENOMEM;
	}

	

	/* Initialise registers */
	if ((info->presc&0xff) > 0)
		writel(S3C2410_ADCCON_PRSCEN | S3C2410_ADCCON_PRSCVL(info->presc&0xFF),\
			     base_addr+S3C2410_ADCCON);
	else
		writel(0,base_addr+S3C2410_ADCCON);
	

	/* Initialise registers */
	if ((info->delay&0xffff) > 0)
		writel(info->delay & 0xffff,  base_addr+S3C2410_ADCDLY);




	/* Initialise input stuff */
	memset(&ts, 0, sizeof(struct s3c2410ts));
	init_input_dev(&ts.dev);
	ts.dev.evbit[0] = ts.dev.evbit[0] = BIT(EV_SYN) | BIT(EV_KEY) | BIT(EV_ABS);
	ts.dev.keybit[LONG(BTN_TOUCH)] = BIT(BTN_TOUCH);

	input_set_abs_params(&ts.dev, ABS_X, 0, 0x3FF, 0, 0);
	input_set_abs_params(&ts.dev, ABS_Y, 0, 0x3FF, 0, 0);
	input_set_abs_params(&ts.dev, ABS_PRESSURE, 0, 1, 0, 0);

	sprintf(ts.phys, "ts0");

	ts.dev.private = &ts;
	ts.dev.name = s3c2410ts_name;
	ts.dev.phys = ts.phys;
	ts.dev.id.bustype = BUS_RS232;
	ts.dev.id.vendor = 0xDEAD;
	ts.dev.id.product = 0xBEEF;
	ts.dev.id.version = S3C2410TSVERSION;

	ts.shift = info->oversampling_shift;

	

	/* All went ok, so register to the input system */
	input_register_device(&ts.dev);

	return 0;
}

static int s3c2410ts_remove(struct device *dev)
{
	disable_irq(IRQ_ADC);
	disable_irq(IRQ_TC);
	free_irq(IRQ_TC,&ts.dev);
	free_irq(IRQ_ADC,&ts.dev);

	if (adc_clock) {
		clk_disable(adc_clock);
		clk_unuse(adc_clock);
		clk_put(adc_clock);
		adc_clock = NULL;
	}

	input_unregister_device(&ts.dev);
	iounmap(base_addr);

	return 0;
}

static struct device_driver s3c2410ts_driver = {
       .name           = "s3c2410-ts",
       .bus            = &platform_bus_type,
       .probe          = s3c2410ts_probe,
       .remove         = s3c2410ts_remove,
};


int __init s3c2410ts_init(void)
{
	return driver_register(&s3c2410ts_driver);
}

void __exit s3c2410ts_exit(void)
{
	driver_unregister(&s3c2410ts_driver);
}

module_init(s3c2410ts_init);
module_exit(s3c2410ts_exit);
