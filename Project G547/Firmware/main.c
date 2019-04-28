#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"
#include "oddebug.h"        /* This is also an example for using debug macros */
#include "requests.h"       /* The custom request numbers we use */

#define adc_channel 0


uint8_t gas_ad0b,gas_ad0h;
int adc_value;
static uint8_t    replyBuf[2]; 
/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

void adc_init(void)
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

int get_adc_data(unsigned char channel)
{
	int adc_value;
	unsigned char temp;
	ADCSRA |= (1<<ADSC);//start_conversion
	while((ADCSRA&(1<<ADSC)));//wait till end of conversion
	ADMUX=(1<<REFS0)|channel;
	_delay_ms(1);
	temp=ADCL;
	adc_value=ADCH;
	adc_value=(adc_value<<8)|temp;
	return adc_value;
}

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;
int length;

    if(rq->bRequest == 0){  
	PORTB^=(1<<1);
	replyBuf[0]=gas_ad0b;
	replyBuf[1]=gas_ad0h;
	usbMsgPtr = (unsigned char *)replyBuf;	
        return 2;
    }

        
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

int __attribute__((noreturn)) main(void)
{
uchar   i;
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//init_adc
    DDRB=(1<<1)|(1<<2);
    wdt_enable(WDTO_1S);
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;
    while(--i){             /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();
    for(;;){                /* main event loop */
        wdt_reset();
        usbPoll();
	adc_value=get_adc_data(adc_channel);
	gas_ad0b=adc_value%256;
	gas_ad0h=adc_value/256;

    }
}

