#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

int times_opened;

static int print_times_opened(struct seq_file *m, void *v)
{
	times_opened += 1;
	seq_printf(m, "%d\n", times_opened);
	return 0;
}

static int counter_open(struct inode *inode, struct  file *file)
{
	return single_open(file, print_times_opened, NULL);
}

static const struct file_operations counter_fops = {
	.owner = THIS_MODULE,
	.open = counter_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init counter_init(void)
{
	times_opened = 0;
	proc_create("counter", 0444, NULL, &counter_fops);
	printk(KERN_INFO "LOADED\n");
        return 0;
}

static void __exit counter_exit(void)
{
	remove_proc_entry("counter", NULL);
	printk(KERN_INFO "UNLOADED\n");
}

MODULE_LICENSE("GPL");
module_init(counter_init);
module_exit(counter_exit);
