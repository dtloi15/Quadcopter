#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//LCD pin
const int pin_rs = 8;
const int pin_en = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
SoftwareSerial Serial2(2,3);//rx2 tx3//tao them 1 cong serial dung de ket noi voi lora
LiquidCrystal lcd(pin_rs,pin_en,pin_d4,pin_d5,pin_d6,pin_d7);
char read_serial;
float Water_level=100;
int page=0;
String data,height,voltage;
bool flag_ready= false;
bool clear_lcd = true;

void setup()
{
  Serial2.begin(9600);//
  Serial.begin(9600);
  lcd.begin(16,2);
// 
}
void loop()
{
  while(Serial2.available()>0)
  {

    read_serial = Serial2.read();
    Serial.println(read_serial);
    switch (read_serial)
    {
      case 'R':
        flag_ready = true;
        break;
      case 'H':
        height = "";
        height = data;
        data="";
        Serial.println(height);
        lcd.clear();
        break;
      case 'V':
        voltage="";
        voltage = data;
        Serial.println(voltage);
        data="";
        lcd.clear();
        break;
      case 'W':
        Water_level-=1.5;
        data="";
        break;
       default:
        data+=read_serial;
        Serial.println(data);
    }
  }
  lcd_readbutton();
  if(page<0)page=3;
  if(page>3)page=0;
  lcd_print();
}
