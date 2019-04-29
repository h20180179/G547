
static const unsigned char PROGMEM  LOGO_WATCHEN[] =
{/* 0X00,0X01,0X80,0X00,0X18,0X00, */
0XE0,0X78,0X1C,0X0F,0X07,0XFF,0XE0,0XFF,0X81,0XC0,0X39,0XC7,0XFF,0XBF,0XC0,0X00,
0XE0,0X78,0X1C,0X0F,0X07,0XFF,0XE0,0XFF,0XC1,0XC0,0X39,0XF7,0XFF,0XBF,0XE0,0X00,
0X60,0X78,0X1C,0X1F,0X07,0XFF,0XE1,0XF3,0XE1,0XC0,0X39,0XF7,0XFF,0XFF,0XE0,0X3C,
0X70,0X7C,0X18,0X1F,0X00,0X18,0X03,0X80,0XE1,0XC0,0X39,0XE7,0XFF,0XFF,0XE0,0X3F,
0X70,0X7C,0X18,0X1F,0X80,0X18,0X03,0X80,0XF1,0XC0,0X39,0XCF,0XFF,0XFF,0XF0,0X7F,
0X70,0XFC,0X38,0X1B,0X80,0X18,0X07,0X00,0X71,0XC0,0X39,0XC8,0X00,0X7F,0XF0,0X7F,
0X70,0XCC,0X38,0X39,0X80,0X18,0X07,0X00,0X01,0XC0,0X39,0XD8,0X00,0X7F,0XF8,0X7E,
0X30,0XCE,0X38,0X39,0XC0,0X18,0X07,0X00,0X01,0XC0,0X39,0XFC,0X00,0X7F,0XF8,0X7E,
0X30,0XCE,0X38,0X31,0XC0,0X18,0X07,0X00,0X01,0XC0,0X39,0XBF,0XFF,0X7F,0XF8,0X7E,
0X39,0XCE,0X30,0X71,0XC0,0X18,0X07,0X00,0X01,0XFF,0XF9,0XBF,0XFE,0X7E,0XFC,0X7E,
0X39,0XC6,0X70,0X70,0XE0,0X18,0X07,0X00,0X01,0XFF,0XF9,0XBF,0XFE,0X7E,0XFC,0X7E,
0X39,0XC6,0X70,0X70,0XE0,0X18,0X07,0X00,0X01,0XFF,0XF9,0XBF,0XFE,0X7E,0X7C,0X7E,
0X19,0X87,0X70,0XFF,0XE0,0X18,0X07,0X00,0X01,0XC0,0X39,0XBF,0XDA,0X7C,0X32,0XFE,
0X19,0X87,0X60,0XFF,0XE0,0X18,0X07,0X00,0X01,0XC0,0X39,0X78,0X00,0X78,0X10,0XFE,
0X19,0X87,0X60,0XFF,0XF0,0X18,0X07,0X00,0X61,0XC0,0X3B,0X78,0X00,0XF6,0X01,0XFE,
0X1F,0X83,0XE1,0XC0,0X70,0X18,0X07,0X00,0X71,0XC0,0X38,0X78,0X00,0XCC,0X39,0XFC,
0X1F,0X03,0XE1,0XC0,0X70,0X18,0X03,0X80,0X71,0XC0,0X39,0X7F,0XFF,0XEC,0X1F,0XFC,
0X0F,0X03,0XE1,0XC0,0X38,0X18,0X03,0X80,0XF1,0XC0,0X39,0X3F,0XFF,0XFC,0X1F,0XFC,
0X0F,0X03,0XC1,0XC0,0X38,0X18,0X01,0XC1,0XE1,0XC0,0X39,0XBF,0XFF,0XFC,0X0F,0XFC,
0X0F,0X03,0XC3,0X80,0X38,0X18,0X01,0XFF,0XC1,0XC0,0X39,0X3F,0XFF,0XFC,0X0F,0XFC,
0X0F,0X01,0XC3,0X80,0X3C,0X18,0X00,0XFF,0XC1,0XC0,0X39,0X7F,0XFF,0XFC,0X0F,0XFC,
0X0E,0X01,0XC3,0X80,0X1C,0X18,0X00,0X7F,0X01,0XC0,0X38,0X00,0X00,0X00,0X07,0XFC,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XF8,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>
#include <TimeLib.h>
#include <math.h>
#include <Wire.h>
// If using software SPI (the default case):
#include <SPI.h>
#include <Snooze.h>
// Load drivers
SnoozeDigital digital;
unsigned long prevTime=0;
//boolean bflag=false;

// install drivers to a SnoozeBlock
SnoozeBlock config(digital);

unsigned long currentTime;
const int ledPin=21;
int countt=0;
const int buttonPin = 5;
const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_INPUT = A6;
const int PULSE_BLINK = 13;    // Pin 13 is the on-board LED
const int PULSE_FADE = 5;
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#define DISPLAY_MODE_IDLE 0
#define DISPLAY_MODE_CLOCK 1
#define DISPLAY_MODE_PULSE 2
#define DISPLAY_MODE_PEDO 3
#define DISPLAY_MODE_NOTIFICATION 4
//#define DISPLAY_MODE_IDLE 11
byte displayMode = DISPLAY_MODE_CLOCK;
boolean isClicked = false;
#define OLED_MOSI   12  // D1
#define OLED_CLK   13    // D0
#define OLED_DC    9    // DC
#define OLED_CS    10    // CS
#define OLED_RESET 8     // RES
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


      int xflag=0;
      int yfrontflag=0;
      int ybackflag=0;

#define XA_OFFSET_H      0x06 // User-defined trim values for accelerometer
#define XA_OFFSET_L_TC   0x07
#define YA_OFFSET_H      0x08
#define YA_OFFSET_L_TC   0x09
#define ZA_OFFSET_H      0x0A
#define ZA_OFFSET_L_TC   0x0B
#define SMPLRT_DIV       0x19
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define FF_THR           0x1D  // Free-fall
#define FF_DUR           0x1E  // Free-fall
#define MOT_THR          0x1F  // Motion detection threshold bits [7:0]
#define MOT_DUR          0x20  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
#define ZMOT_THR         0x21  // Zero-motion detection threshold bits [7:0]
#define FIFO_EN          0x23
#define I2C_MST_CTRL     0x24   
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define DMP_INT_STATUS   0x39  // Check DMP interrupt
#define INT_STATUS       0x3A
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define MOT_DETECT_STATUS 0x61
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define MOT_DETECT_CTRL   0x69
#define USER_CTRL        0x6A  // Bit 7 enable DMP, bit 3 reset DMP
#define PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
#define PWR_MGMT_2       0x6C
#define FIFO_COUNTH      0x72
#define FIFO_COUNTL      0x73
#define FIFO_R_W         0x74
#define WHO_AM_I_MPU6050 0x75 // Should return 0x68

#define MPU6050_ADDRESS 0x68  // Device address when ADO = 0

float aythfh,aythfl,aythbh,aythbl,axthh,axthl;
int step_count=0;

// Set initial input parameters
enum Ascale {
  AFS_2G = 0,
  AFS_4G,
  AFS_8G,
  AFS_16G
};

enum Gscale {
  GFS_250DPS = 0,
  GFS_500DPS,
    GFS_1000DPS,
  GFS_2000DPS
};

// Specify sensor full scale
int Gscale = GFS_250DPS;
int Ascale = AFS_2G;
float aRes, gRes; // scale resolutions per LSB for the sensors
  
// Pin definitions
int intPin = 17;  // This can be changed, 2 and 3 are the Arduinos ext int pins

int16_t accelCount[3];           // Stores the 16-bit signed accelerometer sensor output
float ax, ay, az;                // Stores the real accel value in g's
float axmg;
float aymg;
float azmg;
int16_t gyroCount[3];            // Stores the 16-bit signed gyro sensor output
float gx, gy, gz;                // Stores the real gyro value in degrees per seconds
float gyroBias[3], accelBias[3]; // Bias corrections for gyro and accelerometer
int16_t tempCount;               // Stores the internal chip temperature sensor output 
float temperature;               // Scaled temperature in degrees Celsius
float SelfTest[6];               // Gyro and accelerometer self-test sensor output
uint32_t count = 0;
byte Facebook_msgs = 0;
byte Whatsapp_msgs = 0;
byte Instagram_msgs = 0;
byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;
int myBPM=0; 
int x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
int ThisTime;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
#define UpperThreshold 560
#define LowerThreshold 500
 PulseSensorPlayground pulseSensor;

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
PROGMEM const char* weekString[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
byte iMonth;
byte iDay;
byte iHour;
byte iMinutes;
byte iWeek=6;
byte iSecond;
int iYear;
byte centerX = 64;
byte centerY = 32;
byte iRadius = 28;
byte centerY1=30;

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}


#define TIME_HEADER  "T"   // Header tag for serial time sync message

void startClockMode() {
  displayMode = DISPLAY_MODE_CLOCK;
}

void startIdleMode(){
  displayMode= DISPLAY_MODE_IDLE;
}
void startPulseMode() {
  displayMode = DISPLAY_MODE_PULSE;
}

void startPedoMode() {
  displayMode = DISPLAY_MODE_PEDO;
}

void startMessageMode() {
  displayMode = DISPLAY_MODE_NOTIFICATION;
}

//void DisplayTime(boolean Clicked) {
//    currentTime=millis();
//    
// //     digital.pinMode(21, INPUT_PUL,LOW);
//  if(Clicked == true) {
//    prevTime=currentTime;
//
//    display.display();
//  }
//
//  if(currentTime-prevTime>=60000)
//  {
//    display.clearDisplay();
//    //display.setCursor(0,0);
//    //display.print(currentTime);
//    //display.setCursor(0,10);
//     //display.print(prevTime);
//    display.display();
//   // Snooze.deepSleep( config );
//  }
//}

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void setTimeValue() {
  iMonth = month();
  iDay = day();
  iHour = hour();
  iMinutes = minute();
  iYear=year();
  iSecond=second();
}

void drawClock() {
  display.clearDisplay();
            display.setTextSize(1);
 if(iHour == 0) {
            iWeek++;
            if(iWeek > 6)
iWeek = 0;
 }
    // CLOCK_STYLE_SIMPLE_ANALOG.
    display.drawCircle(centerY1, centerY1, iRadius, WHITE);
    showTimePin(centerY1, centerY1, 0.1, 0.5, iHour*5 + (int)(iMinutes*5/60));
    showTimePin(centerY1, centerY1, 0.1, 0.78, iMinutes);
    showTimePin(centerY1, centerY1, 0.1, 0.9, iSecond);

    display.setTextColor(WHITE);
    display.setCursor(centerY*2 + 3, 13);
     display.print(iDay);
       display.print(".");
        display.print(iMonth);
  display.print(".");
        display.print(iYear); 
          display.setTextSize(2);
        display.setCursor(centerY*2 + 3, 24);    
   display.print(weekString[iWeek]);
   // display.setCursor(centerY*2 + 28, 23);
     display.setTextSize(2);
    display.setCursor(centerY*2, 42);
    if(iHour < 10)
      display.print("0");
    display.print(iHour);
    display.print(":");
    if(iMinutes < 10)
      display.print("0");
    display.println(iMinutes);
   display.display();
}

void calc_pulse()
{
   if(x>127)  
  {
          display.clearDisplay();
            display.setTextSize(1);
          x=0;
          lastx=x;
  }
 
  ThisTime=millis();
  int value=analogRead(A6);
  display.setTextColor(WHITE);
  int y=60-(value/16);
  display.writeLine(lastx,lasty,x,y,WHITE);
  lasty=y;
  lastx=x;
 

  if(value>UpperThreshold)
  {
        if(BeatComplete)
        {
          BPM=ThisTime-LastTime;
          BPM=int(60/(float(BPM)/1000));
          BPMTiming=false;
          BeatComplete=false;
         }
        if(BPMTiming==false)
        {
            LastTime=millis();
            BPMTiming=true;
        }
  }
  if((value<LowerThreshold)&(BPMTiming))
    BeatComplete=true;

   display.writeFillRect(0,50,128,16,BLACK);
  display.setCursor(0,50);
  
    if (pulseSensor.sawNewSample()) {

    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

      if (pulseSensor.sawStartOfBeat()) {
        pulseSensor.outputBeat();

       myBPM = pulseSensor.getBeatsPerMinute();
            
     }
    }
display.print(myBPM);
display.print(" ");
display.print(" BPM");
 Serial.println(myBPM);
  }

  display.display();
  x++;
}

void step_calc()
{

      axthl=-1000.0;
      axthh=-500.0;
      aythfl=500.0;
      aythfh=900.0;
      aythbh=-400.0;
      aythbl=-800.0;
      
      if((axthl<=axmg)and(axmg<=axthh))
      {
            xflag=1;
      }
      else if((aymg>=aythfl)and (aymg<=aythfh) and (xflag==1))
            {
                  yfrontflag=1;
            }

      else if((aythbl<=aymg)and (aymg<=aythbh)and (yfrontflag==1))
            {
                  ybackflag=1;
            }

      else if((yfrontflag==1) and (ybackflag==1) and (ybackflag==1))
            {
                xflag=0;
                yfrontflag=0;
                ybackflag=0;
                step_count=step_count+1;
                
            }
      
}

void pedometer_print()
{
      if(readByte(MPU6050_ADDRESS, INT_STATUS) & 0x01) {  // check if data ready interrupt

    readAccelData(accelCount);  // Read the x/y/z adc values
    getAres();
    
    // Now we'll calculate the accleration value into actual g's
    ax = (float)accelCount[0]*aRes - accelBias[0];  // get actual g value, this depends on scale being set
    ay = (float)accelCount[1]*aRes - accelBias[1];   
    az = (float)accelCount[2]*aRes - accelBias[2];  
   
    readGyroData(gyroCount);  // Read the x/y/z adc values
    getGres();
 
    // Calculate the gyro value into actual degrees per second
    gx = (float)gyroCount[0]*gRes - gyroBias[0];  // get actual gyro value, this depends on scale being set
    gy = (float)gyroCount[1]*gRes - gyroBias[1];  
    gz = (float)gyroCount[2]*gRes - gyroBias[2];   

    tempCount = readTempData();  // Read the x/y/z adc values
    temperature = ((float) tempCount) / 340. + 36.53; // Temperature in degrees Centigrade
   }  
   
    uint32_t deltat = millis() - count;
    if(deltat > 500) {
    axmg=1000*ax;
    aymg=1000*ay;
    azmg=1000*az;

    display.clearDisplay();
     
    display.setCursor(30, 0); display.print("PEDOMETER");
    display.setCursor(0, 8); display.print(" x   y   z  ");
    display.setCursor(0,  16); display.print((int16_t)(1000*ax)); 
    display.setCursor(28, 16); display.print((int16_t)(1000*ay)); 
    display.setCursor(52, 16); display.print((int16_t)(1000*az)); 
    display.setCursor(80, 16); display.print("  mg");
    
    display.setCursor(0,  24); display.print((int16_t)(gx)); 
    display.setCursor(28, 24); display.print((int16_t)(gy)); 
    display.setCursor(52, 24); display.print((int16_t)(gz)); 
    display.setCursor(80, 24); display.print("o/s");    
    display.setCursor(0,  45); display.print("Step Count= "); 
           display.setCursor(65,  45); display.print(step_count);
                   display.setCursor(0,  50); display.print("Flags= ");  
                display.setCursor(0, 55 ); display.print(xflag); 
                display.setCursor(15,  55); display.print(yfrontflag);
                display.setCursor(30,  55); display.print(ybackflag); 
              //  display.display(); 
    
//    display.setCursor(0,  40); display.print("Gyro T  "); 
//    display.setCursor(50, 40); display.print(temperature, 1); display.print(" C");
    display.display();
    
    count = millis();
    }

}

void getGres() {
  switch (Gscale)
  {
   // Possible gyro scales (and their register bit settings) are:
  // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11). 
    case GFS_250DPS:
          gRes = 250.0/32768.0;
          break;
    case GFS_500DPS:
          gRes = 500.0/32768.0;
          break;
    case GFS_1000DPS:
          gRes = 1000.0/32768.0;
          break;
    case GFS_2000DPS:
          gRes = 2000.0/32768.0;
          break;
  }
}

void getAres() {
  switch (Ascale)
  {
  // Possible accelerometer scales (and their register bit settings) are:
  // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11). 
    case AFS_2G:
          aRes = 2.0/32768.0;
          break;
    case AFS_4G:
          aRes = 4.0/32768.0;
          break;
    case AFS_8G:
          aRes = 8.0/32768.0;
          break;
    case AFS_16G:
          aRes = 16.0/32768.0;
          break;
  }
}

void bluetooth_data()
{   
 if(Serial1.available() == 0 /*and bflag==true*/)
 {
  display.clearDisplay();
  display.setTextSize(1);    
      display.setTextColor(WHITE);
      display.setCursor(30,12); 
      display.print("Notification");
      display.display();

 }
   if(Serial1.available() > 0)
    {
      //Received = Serial.readString();
      int Received_int = Serial1.parseInt();
     // Serial.print(Received_int); 

      if(Received_int == 11)
      {
      Facebook_msgs = Facebook_msgs + 1;
      Serial.print(Facebook_msgs);  Serial.print("x ");  Serial.println("FB"); 
      display.clearDisplay();
      display.setTextSize(1);    
      display.setTextColor(WHITE);
      display.setCursor(40,12); 
           
      display.print(Facebook_msgs);      
      display.print("x Twits");  
      display.display();
      delay(5000);
      } 

      if(Received_int == 33)
      {
      Whatsapp_msgs = Whatsapp_msgs + 1;
     Serial.print(Whatsapp_msgs);  Serial.print("x ");  Serial.println("WhatsApp"); 
      display.clearDisplay();
      display.setTextSize(1);    
      display.setTextColor(WHITE);
      display.setCursor(40,12);      
      display.print(Whatsapp_msgs);      
      display.print("x WhatsApp");  
      display.display();
      delay(5000);
      } 

      
      if(Received_int == 22)
      {
      Instagram_msgs = Instagram_msgs + 1;
      Serial.print(Instagram_msgs);  Serial.print("x ");  Serial.println("Instagram"); 
     display.clearDisplay();
      display.setTextSize(1);    
      display.setTextColor(WHITE);
      display.setCursor(40,12);      
      display.print(Instagram_msgs);      
      display.print("x Instagram");  
      display.display();
      delay(5000);
      }    
      
    }    
}

void readAccelData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  readBytes(MPU6050_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
  destination[0] = (int16_t)((rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = (int16_t)((rawData[2] << 8) | rawData[3]) ;  
  destination[2] = (int16_t)((rawData[4] << 8) | rawData[5]) ; 
}

void readGyroData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z gyro register data stored here
  readBytes(MPU6050_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = (int16_t)((rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = (int16_t)((rawData[2] << 8) | rawData[3]) ;  
  destination[2] = (int16_t)((rawData[4] << 8) | rawData[5]) ; 
}

int16_t readTempData()
{
  uint8_t rawData[2];  // x/y/z gyro register data stored herefff
  readBytes(MPU6050_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array 
  return ((int16_t)rawData[0]) << 8 | rawData[1] ;  // Turn the MSB and LSB into a 16-bit value
}

// Configure the motion detection control for low power accelerometer mode
void LowPowerAccelOnlyMPU6050()
{
  uint8_t c = readByte(MPU6050_ADDRESS, PWR_MGMT_1);
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, c & ~0x30); // Clear sleep and cycle bits [5:6]
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, c |  0x30); // Set sleep and cycle bits [5:6] to zero to make sure accelerometer is running

  c = readByte(MPU6050_ADDRESS, PWR_MGMT_2);
  writeByte(MPU6050_ADDRESS, PWR_MGMT_2, c & ~0x38); // Clear standby XA, YA, and ZA bits [3:5]
  writeByte(MPU6050_ADDRESS, PWR_MGMT_2, c |  0x00); // Set XA, YA, and ZA bits [3:5] to zero to make sure accelerometer is running
    
  c = readByte(MPU6050_ADDRESS, ACCEL_CONFIG);
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, c & ~0x07); // Clear high-pass filter bits [2:0]
// Set high-pass filter to 0) reset (disable), 1) 5 Hz, 2) 2.5 Hz, 3) 1.25 Hz, 4) 0.63 Hz, or 7) Hold
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG,  c | 0x00);  // Set ACCEL_HPF to 0; reset mode disbaling high-pass filter

  c = readByte(MPU6050_ADDRESS, CONFIG);
  writeByte(MPU6050_ADDRESS, CONFIG, c & ~0x07); // Clear low-pass filter bits [2:0]
  writeByte(MPU6050_ADDRESS, CONFIG, c |  0x00);  // Set DLPD_CFG to 0; 260 Hz bandwidth, 1 kHz rate
    
  c = readByte(MPU6050_ADDRESS, INT_ENABLE);
  writeByte(MPU6050_ADDRESS, INT_ENABLE, c & ~0xFF);  // Clear all interrupts
  writeByte(MPU6050_ADDRESS, INT_ENABLE, 0x40);  // Enable motion threshold (bits 5) interrupt only
  
// Motion detection interrupt requires the absolute value of any axis to lie above the detection threshold
// for at least the counter duration
  writeByte(MPU6050_ADDRESS, MOT_THR, 0x80); // Set motion detection to 0.256 g; LSB = 2 mg
  writeByte(MPU6050_ADDRESS, MOT_DUR, 0x01); // Set motion detect duration to 1  ms; LSB is 1 ms @ 1 kHz rate
  
  delay (100);  // Add delay for accumulation of samples
  
  c = readByte(MPU6050_ADDRESS, ACCEL_CONFIG);
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, c & ~0x07); // Clear high-pass filter bits [2:0]
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, c |  0x07);  // Set ACCEL_HPF to 7; hold the initial accleration value as a referance
   
  c = readByte(MPU6050_ADDRESS, PWR_MGMT_2);
  writeByte(MPU6050_ADDRESS, PWR_MGMT_2, c & ~0xC7); // Clear standby XA, YA, and ZA bits [3:5] and LP_WAKE_CTRL bits [6:7]
  writeByte(MPU6050_ADDRESS, PWR_MGMT_2, c |  0x47); // Set wakeup frequency to 5 Hz, and disable XG, YG, and ZG gyros (bits [0:2])  

  c = readByte(MPU6050_ADDRESS, PWR_MGMT_1);
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, c & ~0x20); // Clear sleep and cycle bit 5
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, c |  0x20); // Set cycle bit 5 to begin low power accelerometer motion interrupts

}


void initMPU6050()
{  
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, 0x01);  // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001

  writeByte(MPU6050_ADDRESS, CONFIG, 0x03);  
 
 // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
  writeByte(MPU6050_ADDRESS, SMPLRT_DIV, 0x04);  // Use a 200 Hz sample rate 
 
 // Set gyroscope full scale range
 // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
  uint8_t c =  readByte(MPU6050_ADDRESS, GYRO_CONFIG);
  writeByte(MPU6050_ADDRESS, GYRO_CONFIG, c & ~0xE0); // Clear self-test bits [7:5] 
  writeByte(MPU6050_ADDRESS, GYRO_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
  writeByte(MPU6050_ADDRESS, GYRO_CONFIG, c | Gscale << 3); // Set full scale range for the gyro
   
 // Set accelerometer configuration
  c =  readByte(MPU6050_ADDRESS, ACCEL_CONFIG);
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, c & ~0xE0); // Clear self-test bits [7:5] 
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, c | Ascale << 3); // Set full scale range for the accelerometer 

  // Configure Interrupts and Bypass Enable
  // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips 
  // can join the I2C bus and all can be controlled by the Arduino as master
   writeByte(MPU6050_ADDRESS, INT_PIN_CFG, 0x02);    
   writeByte(MPU6050_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
}


// Function which accumulates gyro and accelerometer data after device initialization. It calculates the average
// of the at-rest readings and then loads the resulting offsets into accelerometer and gyro bias registers.
void calibrateMPU6050(float * dest1, float * dest2)
{  
  uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
  uint16_t ii, packet_count, fifo_count;
  int32_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};
  
// reset device, reset all registers, clear gyro and accelerometer bias registers
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
  delay(100);  
   
// get stable time source
// Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, 0x01);  
  writeByte(MPU6050_ADDRESS, PWR_MGMT_2, 0x00); 
  delay(200);
  
// Configure device for bias calculation
  writeByte(MPU6050_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
  writeByte(MPU6050_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
  writeByte(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
  writeByte(MPU6050_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
  writeByte(MPU6050_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
  writeByte(MPU6050_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
  delay(15);
  
// Configure MPU6050 gyro and accelerometer for bias calculation
  writeByte(MPU6050_ADDRESS, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
  writeByte(MPU6050_ADDRESS, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
  writeByte(MPU6050_ADDRESS, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
  writeByte(MPU6050_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity
 
  uint16_t  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
  uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g

// Configure FIFO to capture accelerometer and gyro data for bias calculation
  writeByte(MPU6050_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO  
  writeByte(MPU6050_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO  (max size 1024 bytes in MPU-6050)
  delay(80); // accumulate 80 samples in 80 milliseconds = 960 bytes

// At end of sample accumulation, turn off FIFO sensor read
  writeByte(MPU6050_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
  readBytes(MPU6050_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
  fifo_count = ((uint16_t)data[0] << 8) | data[1];
  packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

  for (ii = 0; ii < packet_count; ii++) {
    int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
    readBytes(MPU6050_ADDRESS, FIFO_R_W, 12, &data[0]); // read data for averaging
    accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;  // Form signed 16-bit integer for each sample in FIFO
    accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
    accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;    
    gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
    gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
    gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;
    
    accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
    accel_bias[1] += (int32_t) accel_temp[1];
    accel_bias[2] += (int32_t) accel_temp[2];
    gyro_bias[0]  += (int32_t) gyro_temp[0];
    gyro_bias[1]  += (int32_t) gyro_temp[1];
    gyro_bias[2]  += (int32_t) gyro_temp[2];           
}
    accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
    accel_bias[1] /= (int32_t) packet_count;
    accel_bias[2] /= (int32_t) packet_count;
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;
    
  if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
  else {accel_bias[2] += (int32_t) accelsensitivity;}
 
// Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
  data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
  data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
  data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
  data[3] = (-gyro_bias[1]/4)       & 0xFF;
  data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
  data[5] = (-gyro_bias[2]/4)       & 0xFF;

  dest1[0] = (float) gyro_bias[0]/(float) gyrosensitivity; // construct gyro bias in deg/s for later manual subtraction
  dest1[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
  dest1[2] = (float) gyro_bias[2]/(float) gyrosensitivity;

  int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
  readBytes(MPU6050_ADDRESS, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
  accel_bias_reg[0] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  readBytes(MPU6050_ADDRESS, YA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[1] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  readBytes(MPU6050_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[2] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  
  uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
  uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis
  
  for(ii = 0; ii < 3; ii++) {
    if(accel_bias_reg[ii] & mask) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
  }

  // Construct total accelerometer bias, including calculated average accelerometer bias from above
  accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
  accel_bias_reg[1] -= (accel_bias[1]/8);
  accel_bias_reg[2] -= (accel_bias[2]/8);
 
  data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
  data[1] = (accel_bias_reg[0])      & 0xFF;
  data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
  data[3] = (accel_bias_reg[1])      & 0xFF;
  data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
  data[5] = (accel_bias_reg[2])      & 0xFF;
  data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

// Output scaled accelerometer biases for manual subtraction in the main program
   dest2[0] = (float)accel_bias[0]/(float)accelsensitivity; 
   dest2[1] = (float)accel_bias[1]/(float)accelsensitivity;
   dest2[2] = (float)accel_bias[2]/(float)accelsensitivity;
}

  void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
  Wire.beginTransmission(address);  // Initialize the Tx buffer
  Wire.write(subAddress);           // Put slave register address in Tx buffer
  Wire.write(data);                 // Put data in Tx buffer
  Wire.endTransmission();           // Send the Tx buffer
}

  uint8_t readByte(uint8_t address, uint8_t subAddress)
{
  uint8_t data; // `data` will store the register data   
  Wire.beginTransmission(address);         // Initialize the Tx buffer
  Wire.write(subAddress);                  // Put slave register address in Tx buffer
  Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
  Wire.requestFrom(address, (uint8_t) 1);  // Read one byte from slave register address 
  data = Wire.read();                      // Fill Rx buffer with result
  return data;                             // Return data read from slave register
}

  void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{  
  Wire.beginTransmission(address);   // Initialize the Tx buffer
  Wire.write(subAddress);            // Put slave register address in Tx buffer
  Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
  uint8_t i = 0;
        Wire.requestFrom(address, count);  // Read bytes from slave register address 
  while (Wire.available()) {
        dest[i++] = Wire.read(); }         // Put read results in the Rx buffer
}

void switch_display(boolean Clicked)
{
  if(Clicked==true) {
          countt=countt+1;
          display.clearDisplay();
          display.setTextSize(1);
          analogWrite(ledPin,255);
          delay(500);
          analogWrite(ledPin,0);
  }
    if(countt==0) startIdleMode();
    else if(countt==1) startClockMode();
    else if(countt==2) startPulseMode();
    else if(countt==3) startPedoMode();
    else if(countt==4) {
      startMessageMode();
    }
   // bflag=true;
   // }
    else if(countt==5) countt=0;
}

double RAD=3.141592/180;
double LR = 89.99;
void showTimePin(int center_x, int center_y, double pl1, double pl2, double pl3) {
  double x1, x2, y1, y2;
  x1 = center_x + (iRadius * pl1) * cos((6 * pl3 + LR) * RAD);
  y1 = center_y + (iRadius * pl1) * sin((6 * pl3 + LR) * RAD);
  x2 = center_x + (iRadius * pl2) * cos((6 * pl3 - LR) * RAD);
  y2 = center_y + (iRadius * pl2) * sin((6 * pl3 - LR) * RAD);
  
  display.drawLine((int)x1, (int)y1, (int)x2, (int)y2, WHITE);
}

void setup()  {
 Wire.begin();
  pinMode(intPin, INPUT);
  digitalWrite(intPin, LOW);
  pinMode(buttonPin, INPUT);

  setSyncProvider(getTeensy3Time);

  Serial.begin(115200);
  Serial1.begin(9600);
   pulseSensor.analogInput(PULSE_INPUT);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);
  

  // Skip the first SAMPLES_PER_SERIAL_SAMPLE in the loop().
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
  while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(100);
  display.begin(SSD1306_SWITCHCAPVCC);  // initialize display (for the 128x64)
  display.display();    // show splashscreen
  delay(1000);
  centerX = display.width() / 2;
  centerY = display.height() / 2;
  iRadius = centerY - 2;    

   uint8_t c = readByte(MPU6050_ADDRESS, WHO_AM_I_MPU6050);  // Read WHO_AM_I register for MPU-6050
  if (c == 0x68) // WHO_AM_I should always be 0x68
  {  
    if(SelfTest[0] < 1.0f && SelfTest[1] < 1.0f && SelfTest[2] < 1.0f && SelfTest[3] < 1.0f && SelfTest[4] < 1.0f && SelfTest[5] < 1.0f) {
    display.clearDisplay(); 
    display.display();
    delay(1000);
  
    calibrateMPU6050(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
    initMPU6050(); Serial.println("MPU6050 initialized for active data mode...."); // Initialize device for active mode read of acclerometer, gyroscope, and temperature

   }
   else
   {
    Serial.print("Could not connect to MPU6050: 0x");
    Serial.println(c, HEX);
    while(1) ; // Loop forever if communication doesn't happen
   }
  }
}

void loop()
{
  if(digitalRead(buttonPin) == LOW) isClicked = true;
  else if(digitalRead(buttonPin) == HIGH) isClicked = false;
  
   if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
//    digitalClockDisplay();

    
    switch_display(isClicked);
    setTimeValue();
    step_calc();
    //DisplayTime(isClicked);
        if(displayMode == DISPLAY_MODE_CLOCK)
    {
              drawClock();
              //DisplayTime(isClicked);
    }
    
// pulsedisplay
    else if(displayMode == DISPLAY_MODE_PULSE)
    {
              calc_pulse();
              //DisplayTime(isClicked);
    }

    else if(displayMode == DISPLAY_MODE_PEDO)
    {
            
            pedometer_print();
            //DisplayTime(isClicked);
    }

    else if(displayMode == DISPLAY_MODE_NOTIFICATION)
    {
            bluetooth_data();
            
    }

    else if(displayMode == DISPLAY_MODE_IDLE)
    {
           display.clearDisplay();
     display.display();
    }

}



