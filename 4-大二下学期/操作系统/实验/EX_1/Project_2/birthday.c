#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/printk.h>
#include<linux/list.h>
#include<linux/types.h>
#include<linux/slab.h>

/* Define a struct called birthday. */
struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};

/* Declear a list_head obeject, which we use as a reference to the head of the list by using the following macro. */
static LIST_HEAD(birthday_list);

/* The module entry point. */
int birthday_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	
	/* Create and initialize instances of struct birthday. */
	struct birthday *person[5];
	
	int i = 0;
	/* Insert 5 elements to the linked list. */
	for(i=0; i<5; i++)
	{
		/* Allocate kernel memory. */
		person[i] = kmalloc(sizeof(*person[i]), GFP_KERNEL);
		
		/* Set values. */
		person[i]->day = i;
		person[i]->month = i;
		person[i]->year = 2000+i;
		
		/* Initialize member list. */
		INIT_LIST_HEAD(&person[i]->list);
		
		/* Add this instance to the end of the liked list. */
		list_add_tail(&person[i]->list, &birthday_list);
	}
	
	/* Declear a pointer. */
	struct birthday *ptr;
	
	/* Traverse the linked list by using the following macro. */
	list_for_each_entry(ptr, &birthday_list, list)
	{
		/* Output to the kernel log buffer. */
		printk(KERN_INFO "%d/%d/%d\n", ptr->day, ptr->month, ptr->year);
	}
	
	return 0;
}

/* The module exit point. */
void birthday_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
	
	/* Declear two pointers. */
	struct birthday *ptr, *next;
	
	/* Traverse the linked list by using the following macro. */
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		/* Remove the elements from the linked list by using the following macro. */
		list_del(&ptr->list);
		
		/* Return the memory that was previously allocated back to the kernel. */
		kfree(ptr);
	}
}

/* Macros for registering module entry and exit points. */
module_init( birthday_init );
module_exit( birthday_exit) ;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Module");
MODULE_AUTHOR("Guangwei Li");
