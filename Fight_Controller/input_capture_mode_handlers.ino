void handler_channel_1(void) {                          
  if (0b1 & GPIOA_BASE->IDR  >> 0) {                  
    channel_1_start = TIMER2_BASE->CCR1;               
    TIMER2_BASE->CCER |= TIMER_CCER_CC1P;                
  }
  else {                                                 
    channel_1 = TIMER2_BASE->CCR1 - channel_1_start;     
    if (channel_1 < 0)channel_1 += 0xFFFF;               
    TIMER2_BASE->CCER &= ~TIMER_CCER_CC1P;              
  }
}

void handler_channel_2(void) {                           
  if (0b1 & GPIOA_BASE->IDR >> 1) {                     
    channel_2_start = TIMER2_BASE->CCR2;                
    TIMER2_BASE->CCER |= TIMER_CCER_CC2P;               
  }
  else {                                                 
    channel_2 = TIMER2_BASE->CCR2 - channel_2_start;     
    if (channel_2 < 0)channel_2 += 0xFFFF;              
    TIMER2_BASE->CCER &= ~TIMER_CCER_CC2P;               
  }
}

void handler_channel_3(void) {                          
  if (0b1 & GPIOA_BASE->IDR >> 2) {                     
    channel_3_start = TIMER2_BASE->CCR3;                
    TIMER2_BASE->CCER |= TIMER_CCER_CC3P;             
  }
  else {                                                
    channel_3 = TIMER2_BASE->CCR3 - channel_3_start;     
    if (channel_3 < 0)channel_3 += 0xFFFF;               
    TIMER2_BASE->CCER &= ~TIMER_CCER_CC3P;               
  }
}

void handler_channel_4(void) {                           
  if (0b1 & GPIOA_BASE->IDR >> 3) {                      
    channel_4_start = TIMER2_BASE->CCR4;                
    TIMER2_BASE->CCER |= TIMER_CCER_CC4P;               
  }
  else {                                                
    channel_4 = TIMER2_BASE->CCR4 - channel_4_start;     
    if (channel_4 < 0)channel_4 += 0xFFFF;               
    TIMER2_BASE->CCER &= ~TIMER_CCER_CC4P;               
}

void handler_channel_5(void) {                           
  if (0b1 & GPIOA_BASE->IDR >> 6) {                     
    channel_5_start = TIMER3_BASE->CCR1;               
    TIMER3_BASE->CCER |= TIMER_CCER_CC1P;               
  }
  else {                                                
    channel_5 = TIMER3_BASE->CCR1 - channel_5_start;     
    if (channel_5 < 0)channel_5 += 0xFFFF;               
    TIMER3_BASE->CCER &= ~TIMER_CCER_CC1P;               
  }
}

void handler_channel_6(void) {                           
  if (0b1 & GPIOA_BASE->IDR >> 7) {                      
    channel_6_start = TIMER3_BASE->CCR2;                 
    TIMER3_BASE->CCER |= TIMER_CCER_CC2P;                
  }
  else {                                                 
    channel_6 = TIMER3_BASE->CCR2 - channel_6_start;    
    if (channel_6 < 0)channel_6 += 0xFFFF;              
    TIMER3_BASE->CCER &= ~TIMER_CCER_CC2P;               
  }
}
