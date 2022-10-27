#include <Wire.h>
#define MS5611_address 0x77
#define gyro_address 0x68
uint16_t C[7];
int64_t OFF,OFF_C2,SENS,SENS_C1,P;
int32_t dT,dT_C5;
 
uint32_t raw_temperature,raw_pressure;
int64_t P_rev,P_fill;
int64_t h,h_pa;
double height;
uint8_t barometer_counter, temperature_counter;
int8_t error;
bool flag=false;
bool flag2=false;
int32_t nhietdo;
double docao;
//pump water
int32_t channel_5, channel_5_start,channel_6,channel_6_start;
bool relay_pump;
//battery
float battery_voltage;
//serial
char bien_press;

#define pump PB15
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(4,INPUT_ANALOG);
  pinMode(pump,OUTPUT);
  digitalWrite(pump,1);
  setup_timer();
  Wire.beginTransmission(MS5611_address);
  Wire.write(0x1E);
  Wire.endTransmission();
  delay(500);
  for(int i =1; i <= 6; i++ )
  {
    Wire.beginTransmission(MS5611_address);
    Wire.write(0xA0+i*2);
    Wire.endTransmission();
    delay(50);
    Wire.requestFrom(MS5611_address, 2);
    C[i]= Wire.read()<<8 | Wire.read();

  }
  OFF_C2 = C[2];
  SENS_C1 = C[1];
  for(int i=1;i<=5000;i++)
  {
    read_barometer();
    delay(4);
  }
  flag2 =true;
//  flag = true;
//  P_rev = P;
  Serial2.println('R');
  battery_voltage = (float)analogRead(4)/112.81;
}


void loop() {

  
  read_barometer();
  
  
//  Serial2.println(height);
//  Serial2.println('H');

  battery_vol();
  Serial2.println(battery_voltage);
  Serial2.println('V');
  if(relay_pump)
  {
    Serial2.println('W');
    digitalWrite(pump,0);
  }
  else
  {
    digitalWrite(pump,1);
  }
delay(1000);
  
}
