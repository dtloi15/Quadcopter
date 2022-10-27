

#include <Wire.h>                         
TwoWire WIRE2 (2,I2C_FAST_MODE);
#define HWire WIRE2        

float pid_p_gain_roll = 1.3;              
float pid_i_gain_roll = 0.04;              
float pid_d_gain_roll = 18.0;             
int pid_max_roll = 400;                    

float pid_p_gain_pitch = pid_p_gain_roll;  
float pid_i_gain_pitch = pid_i_gain_roll;  
float pid_d_gain_pitch = pid_d_gain_roll;  
int pid_max_pitch = pid_max_roll;          

float pid_p_gain_yaw = 4.0;                
float pid_i_gain_yaw = 0.02;               
float pid_d_gain_yaw = 0.0;                
int pid_max_yaw = 400;                     

           


int16_t manual_acc_pitch_cal_value = 0;
int16_t manual_acc_roll_cal_value = 0;



int16_t manual_gyro_pitch_cal_value = 0;
int16_t manual_gyro_roll_cal_value = 0;
int16_t manual_gyro_yaw_cal_value = 0;

uint8_t gyro_address = 0x68;              



uint8_t last_channel_1, last_channel_2, last_channel_3, last_channel_4;
uint8_t highByte, lowByte, flip32, start;
uint8_t error, error_counter, error_led;

int16_t esc_1, esc_2, esc_3, esc_4;
int16_t throttle, cal_int;
int16_t temperature, count_var;
int16_t acc_x, acc_y, acc_z;
int16_t gyro_pitch, gyro_roll, gyro_yaw;


int32_t channel_1_start, channel_1;
int32_t channel_2_start, channel_2;
int32_t channel_3_start, channel_3;
int32_t channel_4_start, channel_4;
int32_t channel_5_start, channel_5;
int32_t channel_6_start, channel_6;
int32_t acc_total_vector;
int32_t gyro_roll_cal, gyro_pitch_cal, gyro_yaw_cal;

uint32_t loop_timer, error_timer;

float roll_level_adjust, pitch_level_adjust;
float pid_error_temp;
float pid_i_mem_roll, pid_roll_setpoint, gyro_roll_input, pid_output_roll, pid_last_roll_d_error;
float pid_i_mem_pitch, pid_pitch_setpoint, gyro_pitch_input, pid_output_pitch, pid_last_pitch_d_error;
float pid_i_mem_yaw, pid_yaw_setpoint, gyro_yaw_input, pid_output_yaw, pid_last_yaw_d_error;
float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll;
float battery_voltage;



void setup() {
  pinMode(4, INPUT_ANALOG);                                  

  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);                    


  pinMode(PB3, INPUT);                                         
  pinMode(PB4, INPUT);                                         
  if (digitalRead(PB3) || digitalRead(PB3))flip32 = 1;         
  else flip32 = 0;

  pinMode(PB3, OUTPUT);                                         
  pinMode(PB4, OUTPUT);                                         

  green_led(LOW);                                              
  red_led(HIGH);                                                


  timer_setup();                                                
  delay(50);                                                   

  HWire.begin();                                              
  HWire.beginTransmission(gyro_address);                        
  error = HWire.endTransmission();                             
  while (error != 0) {                                         .
    error = 2;                                                 
    error_signal();                                            
    delay(4);
  }

  gyro_setup();                                                

  if (!use_manual_calibration) {

    for (count_var = 0; count_var < 1250; count_var++) {        
      if (count_var % 125 == 0) {                              
        digitalWrite(PB4, !digitalRead(PB4));                 
      }
      delay(4);                                                 
    }
    count_var = 0;                                              
  }

  calibrate_gyro();                                             


  while (channel_1 < 990 || channel_2 < 990 || channel_3 < 990 || channel_4 < 990)  {
    error = 3;                                                  
    error_signal();                                             
    delay(4);
  }
  error = 0;                                                   

  while (channel_3 < 990 || channel_3 > 1050)  {
    error = 4;                                                 
    error_signal();                                            
    delay(4);
  }
  error = 0;                                                   

  red_led(LOW);                                                 


  battery_voltage = (float)analogRead(4) / 112.81;

  loop_timer = micros();                                       

  green_led(HIGH);                                              
}


  error_signal();                                                                
  gyro_signalen();                                                                
  gyro_roll_input = (gyro_roll_input * 0.7) + (((float)gyro_roll / 65.5) * 0.3);  
  gyro_pitch_input = (gyro_pitch_input * 0.7) + (((float)gyro_pitch / 65.5) * 0.3);.
  gyro_yaw_input = (gyro_yaw_input * 0.7) + (((float)gyro_yaw / 65.5) * 0.3);      





  angle_pitch += (float)gyro_pitch * 0.0000611;                                   
  angle_roll += (float)gyro_roll * 0.0000611;                                     


  angle_pitch -= angle_roll * sin((float)gyro_yaw * 0.000001066);                  
  angle_roll += angle_pitch * sin((float)gyro_yaw * 0.000001066);                 


  acc_total_vector = sqrt((acc_x * acc_x) + (acc_y * acc_y) + (acc_z * acc_z));    

  if (abs(acc_y) < acc_total_vector) {                                            
    angle_pitch_acc = asin((float)acc_y / acc_total_vector) * 57.296;              
  }
  if (abs(acc_x) < acc_total_vector) {                                            
    angle_roll_acc = asin((float)acc_x / acc_total_vector) * 57.296;               
  }

  angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;                  
  angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;                     

  pitch_level_adjust = angle_pitch * 15;                                          
  roll_level_adjust = angle_roll * 15;                                             



  if (channel_3 < 1050 && channel_4 < 1050)start = 1;

  if (start == 1 && channel_3 < 1050 && channel_4 > 1450) {
    start = 2;

    green_led(LOW);                                                                

    angle_pitch = angle_pitch_acc;                                                 
    angle_roll = angle_roll_acc;                                                   


    pid_i_mem_roll = 0;
    pid_last_roll_d_error = 0;
    pid_i_mem_pitch = 0;
    pid_last_pitch_d_error = 0;
    pid_i_mem_yaw = 0;
    pid_last_yaw_d_error = 0;
  }

  if (start == 2 && channel_3 < 1050 && channel_4 > 1950) {
    start = 0;
    green_led(HIGH);                                                              
  }


  pid_roll_setpoint = 0;

  if (channel_1 > 1508)pid_roll_setpoint = channel_1 - 1508;
  else if (channel_1 < 1492)pid_roll_setpoint = channel_1 - 1492;

  pid_roll_setpoint -= roll_level_adjust;                                          
  pid_roll_setpoint /= 3.0;                                                        



  pid_pitch_setpoint = 0;

  if (channel_2 > 1508)pid_pitch_setpoint = channel_2 - 1508;
  else if (channel_2 < 1492)pid_pitch_setpoint = channel_2 - 1492;

  pid_pitch_setpoint -= pitch_level_adjust;                                       
  pid_pitch_setpoint /= 3.0;                                                     


  pid_yaw_setpoint = 0;

  if (channel_3 > 1050) {
    if (channel_4 > 1508)pid_yaw_setpoint = (channel_4 - 1508) / 3.0;
    else if (channel_4 < 1492)pid_yaw_setpoint = (channel_4 - 1492) / 3.0;
  }

  calculate_pid();                                                                 

  battery_voltage = battery_voltage * 0.92 + ((float)analogRead(4) / 1410.1);


  if (battery_voltage < 10.0 && error == 0)error = 1;
  

  throttle = channel_3;                                                            
  if (start == 2) {                                                                
    if (throttle > 1800) throttle = 1800;                                          
    esc_1 = throttle - pid_output_pitch + pid_output_roll - pid_output_yaw;        
    esc_2 = throttle + pid_output_pitch + pid_output_roll + pid_output_yaw;        
    esc_3 = throttle + pid_output_pitch - pid_output_roll - pid_output_yaw;       
    esc_4 = throttle - pid_output_pitch - pid_output_roll + pid_output_yaw;       

    if (esc_1 < 1100) esc_1 = 1100;                                               
    if (esc_2 < 1100) esc_2 = 1100;                                               
    if (esc_3 < 1100) esc_3 = 1100;                                                
    if (esc_4 < 1100) esc_4 = 1100;                                                

    if (esc_1 > 2000)esc_1 = 2000;                                              
    if (esc_2 > 2000)esc_2 = 2000;                                                 
    if (esc_3 > 2000)esc_3 = 2000;                                               
    if (esc_4 > 2000)esc_4 = 2000;                                                 
  }

  else {
    esc_1 = 1000;                                                                 
    esc_2 = 1000;                                                            
    esc_3 = 1000;                                                                
    esc_4 = 1000;                                                                 
  }

  TIMER4_BASE->CCR1 = esc_1;                                                      
  TIMER4_BASE->CCR2 = esc_2;                                                       
  TIMER4_BASE->CCR3 = esc_3;                                                      
  TIMER4_BASE->CCR4 = esc_4;                                                    
  TIMER4_BASE->CNT = 5000;                                                       





  if (micros() - loop_timer > 4050)error = 5;                                      
  while (micros() - loop_timer < 4000);                                          
  loop_timer = micros();                                                         
}
