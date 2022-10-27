void read_barometer()//doc ap suat dua vao datasheet
{
  barometer_counter++;
if(barometer_counter == 1)
{
  if(temperature_counter ==0)
  {
  Wire.beginTransmission(MS5611_address);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(MS5611_address,3);
  
  raw_temperature = Wire.read() << 16 | Wire.read() << 8 | Wire.read();//D2
  }
  else
  {
  Wire.beginTransmission(MS5611_address);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(MS5611_address,3);
  raw_pressure = Wire.read()<<16 | Wire.read()<<8| Wire.read();//D1
  }
  temperature_counter++;
 if(temperature_counter == 20)
 {
  temperature_counter =0;
  Wire.beginTransmission(MS5611_address);
  Wire.write(0x58);
  Wire.endTransmission();
 }
 else
 {
  Wire.beginTransmission(MS5611_address);
  Wire.write(0x48);
  Wire.endTransmission();
 }
}
if(barometer_counter ==2)
{
  dT =raw_temperature - C[5]*pow(2,8);
  OFF = OFF_C2*pow(2,16)+(((int64_t)dT*(int64_t)C[4])/pow(2,7));
  SENS = SENS_C1*pow(2,15)+(((int64_t)C[3]*(int64_t)dT)/pow(2,8));
  P = ((raw_pressure*SENS)/pow(2,21)-OFF)/pow(2,15);
}
if(barometer_counter == 3)
{
  barometer_counter = 0;

}
  if(flag2 ==true)
  {
  if(flag == true)
  {
    height = (P_rev/12.0 - P/12.0);
    Serial2.println(height);
    Serial2.println('H');
  }
}
}
