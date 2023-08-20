obj-m += kernel_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o set_params set_params.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f set_params
load:
	sudo insmod kernel_module.ko

unload:
	sudo rmmod kernel_module
