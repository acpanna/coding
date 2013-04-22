obj-m += lkl.o

all:
	#make -C /usr/src/linux-`uname -r` SUBDIRS=$(PWD) modules -Werror=implicit-function-declaration
	make -C /usr/src/linux-`uname -r` SUBDIRS=$(PWD) modules

clean:
	rm Module.symvers modules.order *.mod.c *.ko *.o
