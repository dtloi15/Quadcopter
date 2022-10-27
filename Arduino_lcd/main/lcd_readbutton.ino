void lcd_readbutton()
{
  int x;
  x = analogRead(0);//doc gia tri de xac dinh dang nhan nut nao
  
  if(x<60) 
  {
    if(page==1)Water_level=100;//right
  }
  else if (x<200
  {
    delay(100);
    if(analogRead(0)<200)//up
    {
      lcd.clear();
      page++;
    }
     
  }
  else if(x<400) 
  {
    delay(100);
    if(analogRead(0)<400)
    {
      lcd.clear();
      page--;//down
    }
  }
  else if(x<600) 
  { 
    lcd.clear();
    lcd.print("left");//left
  }
  else if(x<800) 
  {
    lcd.clear();
    lcd.print("select");}
  }
