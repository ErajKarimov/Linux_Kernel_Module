obj-m += infotecs_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o set_params set_params.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f set_params
load:
	sudo insmod infotecs_module.ko

unload:
	sudo rmmod infotecs_module
