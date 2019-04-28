#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/input-polldev.h>
#include <linux/usb.h>
#include <linux/spinlock.h>

#define CTRL_EP_OUT 0x00
#define CTRL_EP_IN 0x80

#define AD0 0
#define AD1 1

MODULE_LICENSE("GPL");

struct input_polled_dev *p_dev;
struct usb_device *device;

int retval;
int ad0_val;
void read(void);

struct data {
unsigned int buffer[2];
};
struct data d;

spinlock_t lock;

void read(void)
{
spin_lock(&(lock));	
retval = usb_control_msg(device,usb_rcvctrlpipe(device,0),AD0,USB_TYPE_VENDOR|USB_DIR_IN,0,0,(unsigned int *)d.buffer,2,5000);
if(retval)
{
printk(KERN_INFO "Control Scan Msg AD0 returned %d\n",retval);
}

printk(KERN_INFO "Buffer AD0 %d %d\n",*d.buffer,*(d.buffer+1));

ad0_val = d.buffer[0] | (d.buffer[1]<<8);
spin_unlock(&(lock));

spin_lock_irq(&(lock));	

}

void gas_scan(struct input_polled_dev *p_dev)
{
struct input_dev *dev = p_dev->input;
read();
input_report_rel( dev , REL_X, ad0_val);

input_sync(dev);
}


static int gas_probe(struct usb_interface *interface,const struct usb_device_id *id)
{	
	struct input_dev *dev;
	device = interface_to_usbdev(interface);
	

	if(!p_dev){
	printk("not enough memory for Device\n");
	return -ENOMEM;
	}
	p_dev->poll = gas_scan;
	p_dev->poll_interval = 5000;  //polling interval in msec

	dev = p_dev->input;	
	dev->name = "Gas Sensor Device";
	input_set_capability(dev, EV_REL, REL_X);

	printk(KERN_INFO "Gas Sensor Device (%04X:%04X) Connected\n",id->idVendor,id->idProduct);
	
	/*finally register with the input core */

	return 0;
}
	
static void gas_disconnect(struct usb_interface *interface)
{

	printk(KERN_ALERT "Gas USB Disconnected");
}

static struct usb_device_id gas_table[] = 
{
	{ USB_DEVICE(0x16c0,0x05dc) },
	{} //terminating entry
};


MODULE_DEVICE_TABLE (usb,gas_table);

static struct usb_driver gas_usb =
{
	.name = "gas_usb",
	.id_table = gas_table,
	.probe = gas_probe,
	.disconnect = gas_disconnect,
	
};
	
static int __init gas_init(void)
{
return usb_register(&gas_usb); // Register USB Driver  
printk("Registered usb device");
}



static void __exit gas_exit(void)
{
 
 usb_deregister(&gas_usb);// Deregister USB Driver
printk("Unregister usb device");
}

module_init(gas_init);
module_exit(gas_exit);
