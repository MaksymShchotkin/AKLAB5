#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/slab.h>
#include <linux/ktime.h>


MODULE_AUTHOR("Maksym Shchotkin <maksym.shchotkin@gmail.com>");
MODULE_DESCRIPTION("Lab5");
MODULE_LICENSE("Dual BSD/GPL");

struct list_head_ {
	struct list_head_ *next;
	ktime_t time;
	};

static int num = 1;
static struct list_head_ *head;

module_param(num, uint, 0444);
MODULE_PARM_DESC(num, "'hello world' will be printed this amount of times");

uint i;
static int __init hello_init(void)
{
	struct list_head_ *var1, *var2;
	head = kmalloc(sizeof(struct list_head_ *), GFP_KERNEL);
	var1 = head;
	
	if (num == 0) {
		pr_warn("num is 0");
		}
	else if (num >= 5 && num <= 10) {
		pr_warn("5 < num < 10");
		}
	else if (num > 10) {
		pr_warn("10 < num");
		return -EINVAL;
		}

	for (i = 0; i < num; i++){
		var1->next = kmalloc(sizeof(struct list_head_), GFP_KERNEL);
		var1->time = ktime_get(); 
		pr_info("hello world\n");
		var2 = var1;
		var1 = var1->next;
	}
	
	if (num != 0) {
		kfree(var2->next);
		var2->next = NULL;
	}
	
	return 0;
}

static void __exit hello_exit(void)
{
	struct list_head_ *var;
	while (num != 0 && head != NULL) {
		var = head;
		pr_info("Time - %lld", var->time);
		head = var->next;
		kfree(var);
	}
pr_info("\n");
}

module_init(hello_init);
module_exit(hello_exit);
