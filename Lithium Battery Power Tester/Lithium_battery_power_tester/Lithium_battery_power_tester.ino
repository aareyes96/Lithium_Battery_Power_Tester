
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 6, 7, 8, 9, 10, 11);

unsigned long ZERO = 0;
byte u=0;
bool flag=0;
long tmr0=0,tmr1=0,dt=0;
float wh=0;
int ledPin = 3; 
bool flag11 =0;

void setup() {

  Serial.begin(19200);
  
  lcd.begin( 16,2 );
  pinMode(12,INPUT_PULLUP); 
 
  pinMode(ledPin,OUTPUT); 
  digitalWrite(ledPin,1);
  lcd.setCursor( 0,0 );
  lcd.print ( "*  TO2CONTROL  *" );
  lcd.setCursor( 0,1 );
  lcd.print ( "Li-Ion PWR TEST" );
  delay(2000);
  
  
  lcd.clear();
  lcd.setCursor( 0,0 );
  lcd.print ( "* PRESS THE BUTTON TO SET ZERO *" );
  while(1)
  {
    lcd.scrollDisplayLeft();
    if(digitalRead(12) == 0) break;
    delay(50);
    if(digitalRead(12) == 0) break;
    delay(50);
    if(digitalRead(12) == 0) break;
    delay(50);
    if(digitalRead(12) == 0) break;
    delay(50);
  }

  while(u<10)
  {
    ZERO+=leer();
    u++;
  }
  ZERO/=10;
  Serial.print("ZERO ");
  Serial.println(ZERO);
}

void loop() {
  tmr0=millis();
  dt=tmr0-tmr1;
  //Serial.println(dt);
  unsigned long tmp0 = leer();
  float tmp1=convert(tmp0);
  float tmp2 = leerV(); 
  float power2 = power(tmp1,tmp2);
  Wh(power2);
  //Serial.print("A: ");
  //Serial.println(tmp1);
  //Serial.print("V: ");
  //Serial.println(tmp2);
  //Serial.print("P: ");
  //Serial.println(power2);
  //Serial.println(wh);
  //Serial.print("ZERO ");
  //Serial.println(ZERO);
  //Serial.println(" ");

  lcd.clear();
  lcd.setCursor( 0,0 );
  
  if(flag11 == 0)
  {
    byte v1 = tmp2;
    float tmp3 = tmp2-((byte)(tmp2));
    tmp3 = tmp3*10;
    byte v2 = tmp3;
    lcd.print(v1);
    lcd.print ( "." );
    lcd.print( v2 );
    lcd.print ( "V" );
  }

  else if (flag11 == 1)             
  {
    lcd.print(tmp2);
    lcd.print ( "V" );
  }
  
  lcd.setCursor( 0,1 );
  //if(flag==1)lcd.print ( "+" );
  //if(flag==0)lcd.print ( "-" );
  lcd.print ( abs(tmp1) );
  lcd.print ( "A" );
  
  int p1 = power2;
  float tmp4 = power2-((byte)(power2));
  tmp4 = tmp4*10;
  byte p2 = tmp4;
  
  lcd.setCursor( 9,0 );            
  lcd.print(p1);
  lcd.print ( "." );
  lcd.print( p2 );
  lcd.print("W");

  lcd.setCursor( 9,1 );
  lcd.print ( wh );
  lcd.print ( "Wh" );

  int o = analogRead(A3);
  int n = map(o,0,1023,0,255);
  
  Serial.println(n);
  delay(200);
  analogWrite(ledPin,n);
  tmr1 = tmr0;

  if( !digitalRead(12) )
  {
    flag11 = !flag11;
    while(digitalRead(12) == 0)
    {
      
    }
  }
}

float convert(long g)
{
  float t=0;
  signed int f=0;
  float r=0;
  
  f = g-ZERO;
  r = f*(5000/1023.0000);
  t = r/66.000;
  if( f >= 0 ) flag = 1;
  else flag = 0;

  return t; 
}

unsigned long leer()
{
  long o =0;
  for(int s=0; s<100; s++) 
  {
    o += analogRead(A0); 
    delayMicroseconds(100);
  }
  
  o /= 100;

  //Serial.print("LECTURA ");
  //Serial.println(o);
  return o;
}

float leerV ()
{
  long c =0;
  float b=0;
  for(int s=0; s<100; s++) 
  {
    c += analogRead(A1); 
    delayMicroseconds(100);
  }

  c/=100;
  b=c*(5/1023.000);
  if(flag11 == 0) 
  {
    b=b*21;
    return b;
  }
   else if (flag11)return b;
  
}

float power(float v1 , float a1)
{
  float power1 = v1*a1;
  return power1;
}

void Wh (float power3)
{
  float tm0 = power3*(dt/1000.000);
  tm0=tm0/3600;
  wh+=tm0;
}
