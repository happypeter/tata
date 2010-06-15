#include<fcntl.h> //for O_RDWR

main()
{
int fd, result, data;

int times=0;

fd=open("/dev/adc/0",O_RDWR);
if(fd<0) printf("printf: open failed");
while((times++)<10)
  {
   //we do not call read() here, that means chanel and prescal value
   //are not set, it's ok, the default value 0 and 0xff works well
   //but that also means TSC and everything in driver read() is left undone
   //maybe that is a reason for bug...
    result=read(fd,&data,sizeof(data));
    printf("printf: output data=%d-----0x%x\n",data,data);
  }
close(fd);
return 0;
}
