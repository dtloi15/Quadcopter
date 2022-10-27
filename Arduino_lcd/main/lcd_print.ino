void lcd_print()
{
  
  if(page==0)
  {
    if(!flag_ready)//cho cho den khi quadcopter setup xong
    {
      lcd.setCursor(0,0);
      lcd.print("Waiting");
      
    }
    else
    {
      if(clear_lcd)
      {
        lcd.clear();
        clear_lcd=false;
      }
      
      lcd.setCursor(0,0);
      lcd.print("DTL");
    }
  }
  if(page==1)
  {
    
    lcd.setCursor(0,0);
    lcd.print("WATER LEVEL: ");
    lcd.setCursor(0,1);
    lcd.print(Water_level,1);
    lcd.setCursor(6,1);
    lcd.print("%");
    
  }
  if(page==2)
  {
    
    lcd.setCursor(0,0);
    lcd.print("BATTERY VOLTAGE: ");
    lcd.setCursor(0,1);
    lcd.print(voltage);
    lcd.setCursor(6,1);
    lcd.print("V");
  }
  if(page==3)
  {
    
    lcd.setCursor(0,0);
    lcd.print("ALTITUDE: ");
    lcd.setCursor(0,1);
    lcd.print(height);
    lcd.setCursor(6,1);
    lcd.print("M");
  }
}
