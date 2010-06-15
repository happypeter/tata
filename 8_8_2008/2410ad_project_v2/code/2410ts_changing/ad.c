/**************************************************
*  *GEC2410B  AD convert driver
*  *date: created at 2008-01-03 by baijb
**************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/miscdevice.h> 
#include <linux/sched.h> 
#include <linux/delay.h> 
#include <linux/poll.h> 
#include <linux/spinlock.h> 
#include <linux/delay.h> 
#include <linux/wait.h>
#include <linux/device.h> 
#include <linux/devfs_fs_kernel.h> 
#include <linux/types.h> 
#include <linux/cdev.h> 
#include <linux/errno.h> 

#include <asm/uaccess.h> 
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/arch-s3c2410/regs-adc.h>
#include <asm/arch-s3c2410/regs-clock.h>

#include "adc.h"

#define DEVICE_NAME  "adc" 
static int adc_major = 0;

static void __iomem *peter_base_addr;

/****************************************************
*  *start AD convert and read the value
****************************************************/
static ssize_t adc_read(struct file *file, char  *buf, size_t count, loff_t *ppos)
{
 unsigned long wgz,data,tmp;
 wgz=0;
writel(wgz,peter_base_addr+S3C2410_ADCTSC);
tmp = readl(peter_base_addr+S3C2410_ADCTSC);
printk("0, ADCTSC=0x%lx\n\n",tmp);
data = readl(peter_base_addr+S3C2410_ADCDAT0);
printk("before everything, ADCDAT0=0x%lx\n\n",data); 
tmp = readl(peter_base_addr+S3C2410_ADCCON) |S3C2410_ADCCON_ENABLE_START|S3C2410_ADCCON_PRSCEN;
printk("ADCCON=0x%lx\n\n",tmp);
//write 1 to ENABLE_START to activate ADC
writel( tmp,peter_base_addr+S3C2410_ADCCON);
printk("now,ADCCON=0x%lx\n\n",tmp);
 do{
  tmp = readl(peter_base_addr+S3C2410_ADCCON);
 }while(((unsigned int)tmp) & 0x01); 
printk("then,ADCCON=0x%lx\n\n",tmp);
//check if Enable_start is low, if it is low that means startup is finished
tmp = readl(peter_base_addr+S3C2410_ADCTSC);
printk("then,0, ADCTSC=0x%lx\n\n",tmp);
  
do{
  tmp = readl(peter_base_addr+S3C2410_ADCCON);
 }while(!(((unsigned int)tmp)&0x8000));

//check wether conversion is finished, 
//if yes, jump out this loop to ready the output data
 data = readl(peter_base_addr+S3C2410_ADCDAT0) & 0x3ff;
//only the lower 10 bits is meaningful
 printk("hey i am printk, the output data=0x%lx\n\n", data);
 if(copy_to_user(buf, &data, sizeof(data)))
   return -EFAULT;

 return (sizeof(int));
}

/*****************************************************
*  *set clock prescaler and AD chanel ----0 or 1
*****************************************************/



static ssize_t adc_write(struct file * file, const char  * buf, size_t count, loff_t * off)
{
 unsigned long tmp;

 struct ADC_DEV adcdev;
 
 copy_from_user(&adcdev, (struct ADC_DEV *)buf, count);

 printk("write number=%d, adcdev.prescale=%d, adcdev.chanel=%d\n", 
  sizeof(struct ADC_DEV), adcdev.prescale, adcdev.channel);
 
 //S3C2410_ADCTSC

printk("hello, i am adc_write, if you see me, error occurs!");
/*
 tmp = readl(S3C2410_ADCTSC);
 tmp &= (~S3C2410_ADCTSC_AUTO_PST) | S3C2410_ADCTSC_XY_PST(S3C2410_NOP_MODE);
 writel(tmp , S3C2410_ADCTSC);
 */

//here we do nothing to ADCTSC



 //S3C2410_ADCCON----set chanel and prescaler
// tmp = readl(S3C2410_ADCCON);
// tmp = PRESCALE_ENDIS | PRSCVL(adcdev.prescale) | ADC_INPUT(adcdev.channel);
tmp=0;
 writel( tmp, peter_base_addr+S3C2410_ADCCON);

 return sizeof(struct ADC_DEV);
}


static int adc_open(struct inode * inode, struct file * filp)
{
 //S3C2410_CLKCON---enable the adc clock
 //writel((readl(S3C2410_CLKCON) | 1 << 15),S3C2410_CLKCON);
 printk("ad convert opened!\n");
 
 return 0;
}

static int adc_release(struct inode * inode, struct file * filp)
{
 //S3C2410_CLKCON---disable the adc clock
 //writel(readl(S3C2410_CLKCON) & (~(1 << 15)) ,S3C2410_CLKCON);
 printk("ad convert closed!\n");
 
 return 0;
}

static struct file_operations adc_fops = {  
 .owner = THIS_MODULE,
 .write = adc_write, 
 .read = adc_read,
 .open  = adc_open, 
 .release=adc_release,
}; 

static int __init adc_init(void)
{
 int ret;
 
 ret = register_chrdev(0,DEVICE_NAME,&adc_fops);
   if(ret < 0) {  
  printk("adc: can't get major number\n");
        return ret;
 }
 
 adc_major = ret;

 peter_base_addr= ioremap(S3C2410_PA_ADC,0x20);

 #ifdef CONFIG_DEVFS_FS
  devfs_mk_dir("adc");
  devfs_mk_cdev(MKDEV(adc_major, 0), S_IFCHR|S_IRUGO|S_IWUSR, "adc/%d", 0);
 #endif
    
     printk("s3c2410_adc driver initial\n");
    
 return 0;
}

static void __exit adc_exit(void)
{
#ifdef CONFIG_DEVFS_FS 
 devfs_remove("adc/%d", 0); 
 devfs_remove("adc");   
#endif 
iounmap(peter_base_addr);
 unregister_chrdev(adc_major,DEVICE_NAME); 
 
printk("i am adc_exit, you see me, which means the module is rmmoved\n"); 
}

module_init(adc_init);
module_exit(adc_exit);

MODULE_ALIAS("ad_convert"); 
MODULE_LICENSE("GPL");

