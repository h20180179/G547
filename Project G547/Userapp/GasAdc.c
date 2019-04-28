#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usb.h>    /* this is libusb, see http://libusb.sourceforge.net/*/
#define USBDEV_SHARED_VENDOR    0x16C0  /* VOTI */
#define USBDEV_SHARED_PRODUCT   0x05DC  /* Obdev's free shared PID */

static void usage(char *name)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s status\n", name);
    fprintf(stderr, "  %s on <port> [<duration>]\n", name);
    fprintf(stderr, "  %s off <port> [<duration>]\n", name);
    fprintf(stderr, "  %s test\n\n", name);
    fprintf(stderr, "Ports are single digits in the range 0...7\n");
    fprintf(stderr, "The pulse duration for switching temporarily is given in seconds.\n");
}


static int  usbGetStringAscii(usb_dev_handle *dev, int index, int langid, char *buf, int buflen)
{
char    buffer[256];
int     rval, i;

    if((rval = usb_control_msg(dev, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, langid, buffer, sizeof(buffer), 1000)) < 0)
        return rval;
    if(buffer[1] != USB_DT_STRING)
        return 0;
    if((unsigned char)buffer[0] < rval)
        rval = (unsigned char)buffer[0];
    rval /= 2;
   
    for(i=1;i<rval;i++){
        if(i > buflen)  /* destination buffer overflow */
            break;
        buf[i-1] = buffer[2 * i];
        if(buffer[2 * i + 1] != 0) 
            buf[i-1] = '?';
    }
    buf[i-1] = 0;
    return i-1;
}

#define USB_ERROR_NOTFOUND  1
#define USB_ERROR_ACCESS    2
#define USB_ERROR_IO        3

static int usb_adc_open(usb_dev_handle **device, int vendor, char *vendorName, int product, char *productName)
{
struct usb_bus      *bus;
struct usb_device   *dev;
usb_dev_handle      *handle = NULL;
int                 errorCode = USB_ERROR_NOTFOUND;
static int          didUsbInit = 0;

    if(!didUsbInit){
        didUsbInit = 1;
        usb_init();
    }
    usb_find_busses();
    usb_find_devices();
    for(bus=usb_get_busses(); bus; bus=bus->next){
        for(dev=bus->devices; dev; dev=dev->next){
            if(dev->descriptor.idVendor == vendor && dev->descriptor.idProduct == product){
                char    string[256];
                int     len;
                handle = usb_open(dev); /* we need to open the device in order to query strings */
                if(!handle){
                    errorCode = USB_ERROR_ACCESS;
                    fprintf(stderr, "Warning: cannot open USB device: %s\n", usb_strerror());
                    continue;
                }
                if(vendorName == NULL && productName == NULL){ 
                    break;
                }
                /* now check whether the names match: */
                len = usbGetStringAscii(handle, dev->descriptor.iManufacturer, 0x0409, string, sizeof(string));
                if(len < 0){
                    errorCode = USB_ERROR_IO;
                    fprintf(stderr, "Warning: cannot query manufacturer for device: %s\n", usb_strerror());
                }else{
                    errorCode = USB_ERROR_NOTFOUND;
                    /* fprintf(stderr, "seen device from vendor ->%s<-\n", string); */
                    if(strcmp(string, vendorName) == 0){
                        len = usbGetStringAscii(handle, dev->descriptor.iProduct, 0x0409, string, sizeof(string));
                        if(len < 0){
                            errorCode = USB_ERROR_IO;
                            fprintf(stderr, "Warning: cannot query product for device: %s\n", usb_strerror());
                        }else{
                            errorCode = USB_ERROR_NOTFOUND;
                            /* fprintf(stderr, "seen product ->%s<-\n", string); */
                            if(strcmp(string, productName) == 0)
                                break;
                        }
                    }
                }
                usb_close(handle);
                handle = NULL;
            }
        }
        if(handle)
            break;
    }
    if(handle != NULL){
        errorCode = 0;
        *device = handle;
    }
    return errorCode;
}


int main(int argc, char **argv)
{
usb_dev_handle      *handle = NULL;
unsigned char       buffer[8];
int                 nBytes;

    if(argc < 1){
        usage(argv[0]);
        exit(1);
    }
    usb_init();
    if(usb_adc_open(&handle, USBDEV_SHARED_VENDOR, "www.obdev.at", USBDEV_SHARED_PRODUCT, "GasSensor") != 0){
        fprintf(stderr, "Could not find USB device \"GasAdc with vid=0x%x pid=0x%x\n", USBDEV_SHARED_VENDOR, USBDEV_SHARED_PRODUCT);
        exit(1);
    }
        int r;

       while(1){
            nBytes = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 0, 0, 0, (char *)buffer, sizeof(buffer), 5000);
            r = buffer[0] | (buffer[1]<<8);
	    printf("value from ad0: %d \n",r);
        }
    usb_close(handle);
    return 0;
}
