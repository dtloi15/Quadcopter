
void red_led(int8_t level) {
  if (flip32)digitalWrite(PB4, !level);    
  else digitalWrite(PB4, level);          
}
void green_led(int8_t level) {
  if (flip32)digitalWrite(PB3, !level);    
  else digitalWrite(PB3, level);          
}
