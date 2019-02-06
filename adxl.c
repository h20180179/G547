#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/device.h>

MODULE_LICENSE("Dual BSD/GPL");

unsigned char binary_string[11]={0,0,0,0,0,0,0,0,0,0,0};


static dev_t first; //variable for device number

static struct cdev c_dev;

static struct class *cls;

int snprintf(char *buf, size_t size, const char *fmt,...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsnprintf(buf, size, fmt, args);
    va_end(args);

    return i;
}


// driver callback functions

static int my_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "ADXL: open()\n");
	return 0;
}

static int my_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "ADXL: close()\n");
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{

int binary_int=0;
int base=1;

int rem;
//int i;
//unsigned char print_string[10]={0,0,0,0,0,0,0,0,0,0};
int rand;
int rand_temp;
	
//generate random 10 bit value
	get_random_bytes(&rand,2);
	rand &=0x03FF;
	rand_temp=rand;

	while(rand_temp)
	{
		rem=rand_temp%2;
		binary_int=binary_int+rem*base;
		rand_temp=rand_temp/2;
		base=base*10;
	}
			
snprintf(binary_string,sizeof(binary_string),"%d",binary_int);
	
	
	printk(KERN_ALERT "Binary integer is %d \n",binary_int);
	printk(KERN_ALERT "Binary integer string is %s \n",binary_string);
	
	printk(KERN_INFO "ADXL: read()\n");

	if(copy_to_user(buf,binary_string,sizeof(binary_string)))
	printk(KERN_INFO "some data missing \n");
	
	return sizeof(binary_string);

}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{

	printk(KERN_INFO "ADXL: write()\n");
	return 0;
}

static struct file_operations fops =
					{
						.owner=THIS_MODULE,
						.open =my_open,
						.release=my_close,
						.read=my_read,
						.write=my_write
					};
static int __init mychar_init(void)
{
	
	

	// reserve major and minor numbers
	printk(KERN_INFO "ADXL registered\n\n");
	if (alloc_chrdev_region(&first, 0, 3, "my device")<0)
	{
		return -1;
	}

	// creation of device file
	if((cls=class_create(THIS_MODULE, "chardrv"))==NULL)
	{
		unregister_chrdev_region(first,3);		
		return -1;
	}

	
	if(device_create(cls , NULL, MKDEV(MAJOR(first),MINOR(first)), NULL, "Xdevice")==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}	
	if(device_create(cls , NULL, MKDEV(MAJOR(first),MINOR(first)+1), NULL, "Ydevice")==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}	
	if(device_create(cls , NULL, MKDEV(MAJOR(first),MINOR(first)+2), NULL, "Zdevice")==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}	
	// link fops and cdev to device node 

	cdev_init(&c_dev,&fops);


	if(cdev_add(&c_dev, first,3)==-1)
	{

		device_destroy(cls,MKDEV(MAJOR(first),0));
		device_destroy(cls,MKDEV(MAJOR(first),1));
		device_destroy(cls,MKDEV(MAJOR(first),2));
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}


	return 0;
}

static void __exit mychar_exit(void)
{
	printk(KERN_INFO "ADXL unregistered");
	cdev_del(&c_dev);

	device_destroy(cls,MKDEV(MAJOR(first),0));
	device_destroy(cls,MKDEV(MAJOR(first),1));
	device_destroy(cls,MKDEV(MAJOR(first),2));

	class_destroy(cls);
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "ADXL unregistered");
}

module_init(mychar_init);
module_exit(mychar_exit);


