
/**********************************************
* *AD convert driver test function
*  *date : created at 2008-01-03 by baijb
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

#define PATH  "/dev/adc/0"  //device file

static struct ADC_DEV
{
 int channel;
 int prescale;
}adc_infor;

int main(void)
{
  int fd;
  int result, data;
  unsigned char val;
  int times = 0;

  fd = open(PATH, O_RDWR);
  if (fd < 0)
  {
   printf("Failed to open ad_driver\n");
   exit(1);
  }
 
  printf("Please select which chanel to read....\n");
      printf("0 : chanel--0\n");
  printf("1 : chanel--1\n");
      scanf("%d", &val);

  if((val !=0) && (val !=1))
    val = 0;      //by default the chanel is 0

  adc_infor.channel = val;   //chanel 0 or 1
  adc_infor.prescale = 40;   
 
  do 
  {
    result = write(fd, (void *)&adc_infor, sizeof(adc_infor)) == sizeof(struct ADC_DEV); 
    if (!result)
    {
      printf("wrong when writing!\n");
      goto failed; 
    }
  
    result = read(fd, &data, sizeof(data)) == sizeof(data);
    if (!result) 
    {
      printf("Wrong size!\n");
      goto failed; 
    }

    printf("chanel %d --ad result=%d\n", val, data);
    sleep(1);
  }while((times++) < 10);
 
  failed:
   close(fd);
 
  return 0;
}
