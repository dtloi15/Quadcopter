void setup_timer()
{
 Timer3.attachCompare1Interrupt(handler_channel_5);
  Timer3.attachCompare2Interrupt(handler_channel_6);
  TIMER3_BASE->CR1 = TIMER_CR1_CEN;
  TIMER3_BASE->CR2 = 0;
  TIMER3_BASE->SMCR = 0;
  TIMER3_BASE->DIER = TIMER_DIER_CC1IE | TIMER_DIER_CC2IE;
  TIMER3_BASE->EGR = 0;
  TIMER3_BASE->CCMR1 = 0b100000001; 
  TIMER3_BASE->CCMR2 = 0;
  TIMER3_BASE->CCER = TIMER_CCER_CC1E | TIMER_CCER_CC2E;
  TIMER3_BASE->PSC = 71;
  TIMER3_BASE->ARR = 0xFFFF;
  TIMER3_BASE->DCR = 0;
}

void handler_channel_5(void) {                           //
  if (0b1 & GPIOA_BASE->IDR >> 6) {                      //neu phat hien xung len thi luu lai thoi gian luc do
    channel_5_start = TIMER3_BASE->CCR1;                 //
    TIMER3_BASE->CCER |= TIMER_CCER_CC1P;                //chuyen phat hien ngat xung xuong
  }
  else {                                                 //
    channel_5 = TIMER3_BASE->CCR1 - channel_5_start;     //khi phat hien duoc xung xuong
    if (channel_5 < 0)channel_5 += 0xFFFF;               //se lay thoi gian luc do - di thoi gian khi nay se biet do rong cua xung
    TIMER3_BASE->CCER &= ~TIMER_CCER_CC1P;               //chuyen thanh phat hien ngat xung len
  }
    if(channel_5 >900&&channel_5<1300) relay_pump = false;
  if(channel_5>1600)relay_pump=true;
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
    //
  }
    if(channel_6>1600)
  {
    if(flag2==true)
    {
    flag=true;
    P_rev = P;
    }
  }
}
