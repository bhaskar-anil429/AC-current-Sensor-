///////////////// test code for current monitoring/////////////////////
//Include Wire I2C Library
#include  <Wire.h>
int address = 42; // I2C address
double voltage = 121.7;
void setup()
{
 
  Serial.begin(9600);  // Create Serial Object (9600 Baud)
  Wire.begin();
  
  newcalibration(1,6438); /////////////// use this function to set new calibration value//////////
 int t = channel();
 //delay(100);
    read_calibration_value(t);
}
///////////////////////////////////// no of ch //////////////////////

int channel ()
  {
    Wire.begin();
    Wire.beginTransmission(address); //Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(2);  // Command 2 is used to read no of sensor type,Max current,no of channel
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(254); // CheckSum
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(address, 6);
    int TypeOfSensor =  Wire.read();
    int MaxCurrent =  Wire.read();
    int NoOfChannel =  Wire.read();
    int ExtraByte1 =  Wire.read(); 
    int ExtraByte2 =  Wire.read(); 
    int ExtraByte3 =  Wire.read(); 
   // delay(100);
    Wire.endTransmission(); // Complete Transmission
    return NoOfChannel;
  }
  ///////////////////////////////////// type of ch //////////////////////

int type ()
  {
    Wire.begin();
    Wire.beginTransmission(address); //Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(2);  // Command 2 is used to read no of sensor type,Max current,no of channel
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(254); // CheckSum
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(address, 6);
    int TypeOfSensor =  Wire.read();
    int MaxCurrent =  Wire.read();
    int NoOfChannel =  Wire.read();
    int ExtraByte1 =  Wire.read(); 
    int ExtraByte2 =  Wire.read(); 
    int ExtraByte3 =  Wire.read(); 
   // delay(100);
    Wire.endTransmission(); // Complete Transmission
    return TypeOfSensor;
  }
  
/////////////////////////////////////// max current ///////////////////////
int MaxCurrent ()
  {
    Wire.begin();
    Wire.beginTransmission(address); // Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(2);  // Command 2 is used to read no of sensor type,Max current,no of channel
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(254); // CheckSum
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(address, 5);
    int TypeOfSensor =  Wire.read();
    int MaxCurrent =  Wire.read();
    int NoOfChannel =  Wire.read();
    int ExtraByte1 =  Wire.read();
    int ExtraByte2 =  Wire.read(); 
    int ExtraByte3 =  Wire.read(); 
   // delay(100);
    Wire.endTransmission(); // Complete Transmission
    return MaxCurrent;
  }
///////////////////////////////////// firmware version //////////////////////
int FirmwareVersion ()
  {
    Wire.begin();
    Wire.beginTransmission(address); //Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(2);  // Command 2 is used to read no of sensor type,Max current,no of channel
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write(254); // CheckSum
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(address, 6);
    int TypeOfSensor =  Wire.read();
    int MaxCurrent =  Wire.read();
    int NoOfChannel =  Wire.read();
    int FirmwareVersion =  Wire.read(); 
    int ExtraByte2 =  Wire.read(); 
    int ExtraByte3 =  Wire.read(); 
    //delay(100);
    Wire.endTransmission(); // Complete Transmission
    return FirmwareVersion;
  }
///////////////////////////////// set calibration//////////////////////////////////
int newcalibration(int Channelno, int calibration_value)
  { 
    Serial.print ("Writing new calibration value:  ");
    Wire.beginTransmission(address); // Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(4);  // Command 4 to write calibration value 
    Wire.write(Channelno);  // Channel no
    Wire.write(Channelno);  // Channel no
    int MSB = calibration_value/255;
    Wire.write(MSB);
    int LSB = calibration_value & 255;
    Wire.write(LSB);
    Wire.write((146 + 106 + 4 + Channelno + Channelno  + MSB + LSB) & 255); 
    Wire.endTransmission(); // Complete Transmission
    Serial.println ("\t");
    Serial.print("Calibration Done:  ");
    Serial.println ("\t");
  }
///////////////////////////////////////////////////////////////////////////
int read_calibration_value(int NoOfChannel)
{
  Serial.print ("Calibration values for all channels are:  ");
  Serial.println ("\t");
  int t = NoOfChannel;
  //////////////////////////////////////////////////////////// calibration value //////////////////////
  for ( byte i = 1; i< t+1; i++)
    { 
    Wire.beginTransmission(address); // Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(3);  // Command 3 to read calibration value 
    Wire.write(i);  // Channel no
    Wire.write(i);
    Wire.write(0); 
    Wire.write(0); 
    Wire.write((146 + 106 + 3 + i + i + 0 + 0) & 255); // CheckSum
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(address, 4); 
   // int g =Wire.read();
   // int h =Wire.read();
    Serial.print(i); 
    Serial.print("\t");
    int MSB = Wire.read();
    int LSB = Wire.read();
    int calibration = (MSB*256)+LSB;
    Serial.print(calibration);
    Serial.print("\t");
    Serial.print("\n");
   // delay(10);
    Wire.endTransmission(); // Complete Transmission
    }
}

/////////////////////////////////////////////////////////////////////

void loop()
{
  int t = channel();
  Serial.print ("No of channel in this product is:  ");
  Serial.print(t);
  Serial.println ("\t");
  int y = type();
  Serial.print ("Type of sensor in this product is:  ");
  Serial.print(y);
  Serial.println ("\t");
  int l = MaxCurrent();
  Serial.print ("Max Current Measured by this product is:  ");
  Serial.print(l);
  Serial.print(" ");
  Serial.print("Amp"); 
  Serial.println ("\t");
  int m = FirmwareVersion();
  Serial.print ("Firmware Version is: ");
  Serial.print ("REV_0.");
  Serial.print (m);
  Serial.println ("\t");
 
//////////////////////////////////////////////////////////// Current //////////////////////
  Serial.println("new updated current values are:  "); 
  for ( byte i = 1; i< t+1; i++)
    { 
    Wire.beginTransmission(address); // Start communication
    Wire.write(146); // Command header 
    Wire.write(106); // Command header 
    Wire.write(1);  // Command 1
    Wire.write(i);  // Start Channel no 
    Wire.write(i);  // End Channel no 
    Wire.write(0); 
    Wire.write(0); 
    Wire.write((146 + 106 + 1 + i + i + 0 + 0) & 255); // CheckSum
    Wire.endTransmission(); // Complete Transmission
    Wire.requestFrom(address, 5); 
   // int g =Wire.read();
   // int h =Wire.read();  
    Serial.print(i); 
    Serial.print("\t");
    unsigned long MSB1 = Wire.read();
     MSB1= MSB1*65536;
    unsigned long MSB = Wire.read();
    MSB=MSB*256;
    unsigned long LSB = Wire.read();
   MSB1=MSB1+MSB+LSB;
    double current = ((double)MSB1)/(double)1000; 
   // current = current/1000;
    
    Serial.print(current,3);
    Serial.print(" ");
    Serial.print("Amp"); 
    Serial.print("\t");
    
    double Power = voltage * current;
    Serial.print(Power,3);
    Serial.print(" ");
    Serial.print("Watt"); 
    Serial.print("\t");
    
    double kWh = 0.000833 * Power;
    Serial.print(kWh,4);
    Serial.print(" ");
    Serial.print("kWh"); 
    Serial.print("\t");


    
    Serial.print("\n");
   // delay(500);
    Wire.endTransmission(); // Complete Transmission
    }
  Serial.println ("\n");
  delay(3000);
}
