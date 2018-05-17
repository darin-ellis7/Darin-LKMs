obj-m += hellocall.o counter.o 

all:
	make ARCH=um -C ./ELINUX/lib/modules/4.4.108/build M=$(PWD) modules

clean:
	make ARCH=um -C ./ELINUX/lib/modules/4.4.108/build M=$(PWD) clean
