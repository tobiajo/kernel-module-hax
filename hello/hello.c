#include <linux/module.h>	// Needed for all kernel modules
#include <linux/kernel.h>	// Needed for KERN_INFO
#include <linux/init.h>		// Needed for __init and __exit macros

static int __init hello_init(void) {
	printk(KERN_INFO "Hello from kernel!\n");
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_INFO "Goodbye from kernel.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tobias Johansson");
MODULE_DESCRIPTION("Hello kernel");
