
ifneq	($(KERNELRELEASE),)
obj-m	:=nicports.o 

else
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
default:	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 
	rm -r .tmp_versions *.mod.c .*.cmd *.o 

endif

