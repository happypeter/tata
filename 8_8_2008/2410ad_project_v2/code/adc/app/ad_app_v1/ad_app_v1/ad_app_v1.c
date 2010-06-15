#include<fcntl.h> //for O_RDWR


main()
{
int fd,result,data;
fd=open("/dev/adc/0",O_RDWR);
if(fd<0) printf("open failed");

result=read(fd, &data, sizeof(data));
close(fd);
return 0;
}
