#include <linux/config.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/arch-s3c2410/regs-gpio.h>
//Please configure your kernel first to use the following headers, because the directory "asm" is a short cut to your arch's "asm" directory.
//So do the headers in the "hardware" sub directory.
#include <asm-arm/io.h>  //This header is for ioremap(), iounmap().
#include <asm-arm/uaccess.h>  //This header is for get_user(), put_user().
#define NAME "led_test"
static int major = 231;  //Define device major
unsigned long * pREG;  //Definition of register base.
static ssize_t led_test_write(struct file *file, const char __user *data, size_t len, loff_t *ppos)
{
 char buf[256];
 size_t i;
 for (i = 0; i < len && i < 254; i++)
  if (get_user(buf[i], data + i))
   return -EFAULT;
   
 buf[i] = '\0';
 printk("peter_LED Test - write: user_data %s\n", buf);
 return (len < 255 ? len : 255);
}
static ssize_t led_test_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
 char rbuf[4];
 size_t i;
 long tmp;
 
 tmp = * (volatile unsigned long *)(pREG + 1);
 rbuf[0] = tmp % 256;
 rbuf[1] = (tmp >> 8) % 256;
 rbuf[2] = (tmp >> 16) % 256;
 rbuf[3] = (tmp >> 24) % 256;
 
 if (len > 4)
  return 0;
 for (i = 0; i < len && i < 4; i++)
  if (put_user(rbuf[i], buf + i))
   return -EFAULT;
 printk("LED Test - read\n");
 return (len < 4 ? len : 4);
}
static int led_test_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
 unsigned long tmp;
 printk("LED Test - ioctl: param %u %lu\n", cmd, arg);
 switch (cmd)
 {
  case 0:
  case 1:
   if (arg > 3)
    return -EINVAL;
   if (!cmd)
    * (volatile unsigned long *)(pREG + 1) |= (0x10 << arg);//peter change
   else
    * (volatile unsigned long *)(pREG + 1) &= ~(0x10 << arg);
   tmp = * (volatile unsigned long *)pREG;
   printk("GPBCON = 0x%lx\n", tmp);
   tmp = * (volatile unsigned long *)(pREG + 1);
   printk("GPBDAT = 0x%lx\n", tmp);
   break;
  default:
   return -EINVAL;
 }
 return 1;
}
static int led_test_open(struct inode *inode, struct file *file)
{
 unsigned m = iminor(inode);
 if (m > 63)
  return -EINVAL;
 printk("LED Test driver opened!\n");
 return nonseekable_open(inode, file);
}
static int led_test_release(struct inode *inode, struct file *file)
{
 printk("LED Test driver released!\n");
 return 0;
}
static struct file_operations led_test_fops = {
 .owner   = THIS_MODULE,
 .ioctl   = led_test_ioctl,
 .write   = led_test_write,
 .read    = led_test_read,
 .open    = led_test_open,
 .release = led_test_release,
};
static int __init led_test_init(void)
{
 int ret;
 unsigned long tmp;
 
 printk("LXZ LED Test Driver.\n");
 ret = register_chrdev(major, NAME, &led_test_fops);
 if (ret < 0) {
  printk("Unable to register character device!\n");
  return ret;
 }
 pREG = ioremap(0x56000050, 0x20);
 printk("Virtual addr base = 0x%lx\n", (unsigned long)pREG);
 tmp = * (volatile unsigned long *)pREG;
 printk("GPBCON = 0x%lx\n", tmp);
 tmp = * (volatile unsigned long *)(pREG + 1);
 printk("GPBDAT = 0x%lx\n", tmp);
 printk("Seting LED Test Driver...\n"); 
 * (volatile unsigned long *)pREG = 0x155555;
// * (volatile unsigned long *)(pREG + 1) = 0xf10;//led4=1, led7=0;
__raw_writel(0xf10,S3C2410_GPFDAT);

tmp=__raw_readl(S3C2410_GPFDAT);
 
//tmp = * (volatile unsigned long *)pREG;
 printk("changed000000000S3C2410_GPFDAT = 0x%lx\n", tmp);
 tmp = * (volatile unsigned long *)(pREG + 1);
 printk("GPFDAT = 0x%lx\n", tmp);
 printk("LED Test Driver initiated.\n"); 
 return 0;
}
static void __exit led_test_cleanup(void)
{
 int ret;
 
 iounmap(pREG);
 
 ret = unregister_chrdev(major, NAME); 
 if (ret < 0)
  printk("Unable to register character device!\n");
 else
  printk("LED Test Driver unloaded!");
}
module_init(led_test_init);
module_exit(led_test_cleanup);
 
