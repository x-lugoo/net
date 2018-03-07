CONFIG_MODULE_SIG=n
obj-m	:= e1000_jeff.o
e1000_jeff-objs:=e1000_main.o e1000_hw.o e1000_ethtool.o e1000_param.o
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
default:	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 
	rm -r .tmp_versions *odule* *.mod.c .*.cmd *.o 


