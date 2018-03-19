DEBUG=y
CONFIG_MODULE_SIG=n
obj-m	:= e1000_jeff.o
e1000_jeff-objs:=e1000_main.o e1000_hw.o e1000_ethtool.o e1000_param.o
ifeq ($(DEBUG),y)
	MY_CFLAGS += -O0 -g -DDEBUG_SKB_TX
else
	MY_CFLAGS += -O2
	
endif
ccflags-y += $(MY_CFLAGS)
CC +=$(MY_CFLAGS)
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
default:	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 
	rm -rf e1000 .tmp_versions *odule* *.mod.c .*.cmd *.o 


