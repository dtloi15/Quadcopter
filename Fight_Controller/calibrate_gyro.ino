void calibrate_gyro(void) {
                                     
    cal_int = 0;                                                                    
    manual_gyro_pitch_cal_value = 0;                                                  
    manual_gyro_roll_cal_value = 0;                                                   
    manual_gyro_yaw_cal_value = 0;                                                    

  if (cal_int != 2000) {

    for (cal_int = 0; cal_int < 2000 ; cal_int ++) {                                  
      if (cal_int % 25 == 0) digitalWrite(PB4, !digitalRead(PB4));                    
      gyro_signalen();                                                                
      gyro_roll_cal += gyro_roll;                                                    
      gyro_pitch_cal += gyro_pitch;                                                   
      gyro_yaw_cal += gyro_yaw;                                                       
      delay(4);                                                                      
    }
    red_led(HIGH);                                                                    

    gyro_roll_cal /= 2000;                                                           
    gyro_pitch_cal /= 2000;                                                          
    gyro_yaw_cal /= 2000;                                                             
    manual_gyro_pitch_cal_value = gyro_pitch_cal;                                     
    manual_gyro_roll_cal_value = gyro_roll_cal;                                       
    manual_gyro_yaw_cal_value = gyro_yaw_cal;                                         
  }
}
