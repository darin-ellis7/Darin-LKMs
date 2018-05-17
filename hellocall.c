#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

extern void *sys_call_table[];

//to store remap_file_pages() so it can be restored after unloading
asmlinkage int (*original_call)(void*, size_t, int, size_t, int);

asmlinkage int hello(void)
{
	printk(KERN_INFO "hello\n");
	return 0;
}

static int __init hello_init(void)
{
	printk(KERN_INFO "LOADED\n");
	original_call = sys_call_table[__NR_remap_file_pages];
	sys_call_table[__NR_remap_file_pages] = hello;
        return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "UNLOADED\n");
	sys_call_table[__NR_remap_file_pages] = original_call;
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
