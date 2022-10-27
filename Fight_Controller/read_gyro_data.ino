///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gyro_signalen(void) {
  HWire.beginTransmission(gyro_address);                       
  HWire.write(0x3B);                                           
  HWire.endTransmission();                                    
  HWire.requestFrom(gyro_address, 14);                        
  acc_y = HWire.read() << 8 | HWire.read();                    
  acc_x = HWire.read() << 8 | HWire.read();                    
  acc_z = HWire.read() << 8 | HWire.read();                    
  temperature = HWire.read() << 8 | HWire.read();              
  gyro_roll = HWire.read() << 8 | HWire.read();                
  gyro_pitch = HWire.read() << 8 | HWire.read();             
  gyro_yaw = HWire.read() << 8 | HWire.read();                
  gyro_pitch *= -1;                                            
  gyro_yaw *= -1;                                              .

  acc_y -= manual_acc_pitch_cal_value;                         
  acc_x -= manual_acc_roll_cal_value;                          
  gyro_roll -= manual_gyro_roll_cal_value;                    
  gyro_pitch -= manual_gyro_pitch_cal_value;                   
  gyro_yaw -= manual_gyro_yaw_cal_value;                       
}
