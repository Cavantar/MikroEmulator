// Deklaracje
// --------------------------------------------

char LD1, LD2, KL, stan=1, tim=10;		
char stanLCD=1, timLCD=10, T1=10, T2=10, pK1, pK2;

// Funkcja G³ówna
// --------------------------------------------
void updateState()
{
  KL = aK1;
  
  switch(stan)
  {
  case 1:
    {
      LD1 = 1; LD2 = 0;
      if(!tim && !KL)
      {
	stan = 2;
	tim = T1;
      }
      else if(!tim && KL)
      {
	stan = 2;
	tim = T2;
      }
      
    } break;
    
  case 2:
    {
      LD1 = 0; LD2 = 1;
      if(!tim)
      {
	stan = 1;
	tim = T2;
      }
    } break;
  }
  if(tim) --tim;

  L1 = LD1;
  L2 = LD2;
  
  switch(stanLCD)
  {
  case 1:
    {
      LCD_xy(0, 0);
      LCD_puts("Mikrokontroler !");
      
      LCD_xy(0, 1);
      LCD_puts("Initializing");

      if(!timLCD)
      {
	stanLCD = 2;
      }
      
    } break;
  case 2:
    {
      LCD_xy(0, 0);
      LCD_puts("1 - ByUstawicT1 !");
      
      LCD_xy(0, 1);
      LCD_puts("2 - ByUstawicT2 !");

      if(aK1 && !pK1) stanLCD = 3;
      if(aK2 && !pK2) stanLCD = 4;
      
    } break;
  case 3:
    {
      LCD_xy(0, 0);
      sprintf(buffer, "T1: %2.1f       ", (float)T1/10.0f);
      LCD_puts(buffer);
      
      LCD_xy(0, 1); LCD_puts("1+, 2-, 3p       ");
      
      if(aK3) stanLCD = 2;
      
      if(aK1) T1 += 1; 
      if(aK2) T1 -= 1; if(T1 < 1) T1 = 1;
      
    } break;
  case 4:
    {
      LCD_xy(0, 0);
      sprintf(buffer, "T2: %2.1f       ", (float)T2/10.0f);
      LCD_puts(buffer);
      
      LCD_xy(0, 1); LCD_puts("1+, 2-, 3p       ");
      
      if(aK3) stanLCD = 2;
      
      if(aK1) T2 += 1; 
      if(aK2) T2 -= 1; if(T2 < 1) T2 = 1;
      
    } break;
  }
  if(timLCD) --timLCD;
  
  pK1 = aK1;
  pK2 = aK2;
}
