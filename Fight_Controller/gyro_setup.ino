void gyro_setup(void){
  HWire.beginTransmission(gyro_address);                        
  HWire.write(0x6B);                                           
  HWire.write(0x00);                                          
  HWire.endTransmission();                                      

  HWire.beginTransmission(gyro_address);                        
  HWire.write(0x1B);                                           
  HWire.write(0x08);                                           
  HWire.endTransmission();                                     

  HWire.beginTransmission(gyro_address);                        
  HWire.write(0x1C);                                           
  HWire.write(0x10);                                         
  HWire.endTransmission();                                    

  HWire.beginTransmission(gyro_address);                       
  HWire.write(0x1A);                                           
  HWire.write(0x03);                                          
  HWire.endTransmission();                                     
}
