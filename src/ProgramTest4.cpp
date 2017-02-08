// Deklaracje
// --------------------------------------------

// Pierwszy Binarny 

char x4, x3, Z1, Z2, tim1, T1 = 3, T2 = 1;

char t_PS1[] = {12, 10, 8, 5, 4, 4, 4, 10, 8, 12, 8, 0, 12};
char t_PW1[] = {2, 1, 3, 1, 4, 5, 3, 1, 6, 0, 7, 6, 0};
char t_PA1[] = {0, 0, 10, 0, 11, 0, 4, 0, 2, 0, 8, 11, 0};

char STT1, STT2;
char xw, pc1;

// Drugi Binarny 

char x2, x1, T, Z3, Z4, G, tim2, T3 = 10;

char t_PS2[] = {32, 36, 32, 9, 8, 8, 16, 32, 32, 2, 0, 36, 32, 8, 16};
char t_PW2[] = {2, 1, 3, 1, 4, 5, 6, 0, 7, 1, 7, 1, 0, 8, 0};
char t_PA2[] = {0, 0, 8, 0, 13, 5, 6, 0, 2, 0, 10, 0, 8, 4, 6};

char ST3, ST1, STT3;
char pc2;

// Komunikacyjny

char stank=1, znak, a, b, c, d, cs, tempLiczba;

// Funkcja G³ówna
// --------------------------------------------
void updateState()
{
  
  Z1 = (t_PS1[pc1] & 8) ? 1 : 0;
  Z2 = (t_PS1[pc1] & 4) ? 1 : 0;
  STT1 = (t_PS1[pc1] & 2) ? 1 : 0;
  STT2 = (t_PS1[pc1] & 1) ? 1 : 0;
  
  Z3 = (t_PS2[pc2] & 32) ? 1 : 0;
  Z4 = (t_PS2[pc2] & 16) ? 1 : 0;
  G = (t_PS2[pc2] & 8) ? 1 : 0;
  ST3 = (t_PS2[pc2] & 4) ? 1 : 0;
  ST1 = (t_PS2[pc2] & 2) ? 1 : 0;
  STT3 = (t_PS2[pc2] & 1) ? 1 : 0;
  
  switch(t_PW1[pc1])
  {
  case 0 : xw = 0;
    break;
  case 1 : xw = 1;
    break;
  case 2 : xw = x3;
    break;
  case 3 : xw = !tim1;
    break;
  case 4 : xw = !x4;
    break;
  case 5 : xw = x3;
    break;
  case 6 : xw = !x3;
    break;
  case 7 : xw = x4;
    break;
  }

  if(xw) ++pc1;
  else pc1 = t_PA1[pc1];

  if(STT1) tim1 = T1 * 10;
  if(STT2) tim1 = T2 * 10;
  
  if(tim1) --tim1;
  
  switch(t_PW2[pc2])
  {
  case 0 : xw = 0;
    break;
    
  case 1 : xw = 1;
    break;
    
  case 2 : xw = x1;
    break;
    
  case 3 : xw = x2;
    break;
        
  case 4 : xw = !tim2 && !T;
    break;
    
  case 5 : xw = T;
    break;
    
  case 6 : xw = !x1;
    break;
    
  case 7 : xw = !tim2;
    break;
    
  case 8 : xw = !tim2 && T;
    break;
  }
  
  if(xw) ++pc2;
  else pc2 = t_PA2[pc2];

  if(ST3) tim2 = 30;
  if(ST1) tim2 = 10;
  if(STT3) tim2 = T3 * 10;

  if(tim2) --tim2;

  znak = COM_recv() & 0x7F;

  if(znak != 0)
    switch(stank)
    {
    case 1:
      if(znak == ':') stank = 2;
      break;
      
    case 2:
      if(znak >= '0' && znak <= '9')
      {
	a = znak - '0';
	stank = 3;
      }
      else if(znak >= 'A' && znak <= 'C')
      {
	a = znak;
	stank = 9;
      }
      else stank = 1;
      break;
      
    case 3:
      if(znak >= '0' && znak <= '9')
      {
	b = znak - '0';
	stank = 4;
      }
      else stank = 1;
      break;
      
    case 4:
      if(znak >= '0' && znak <= '4')
      {
	c = znak - '0';
	stank = 5;
      }
      else stank = 1;
      break;
      
    case 5:
      if(znak >= '0'&& znak <= '3')
      {
	d = znak - '0';
	stank = 6;
      }
      else if(znak == 'A') stank = 7;
      else if(znak == '#')
      {
	if(a > 0 && b > 0 && (a+b+c)%5 == 0)
	{
	  T1 = a; T2 = b;
	}
	stank = 1;
      }
      else stank = 1;
      break;
    case 6:
      if(znak == '#')
      {
	if(a < 2 && b < 2 && c < 2 && (a+b+c+d) == 3)
	{
	  x1 = a; x2 = b; T = c;
	}
	stank = 1;
      }
      if(znak == 'A')
      {
	stank = 8;
      }
      else stank = 1;
      break;
    case 7:
      if(znak == '#')
      {
	if(a < 3)
	{
	  tempLiczba = a * 10 + b;
	  if(tempLiczba > 5 && tempLiczba <= 25 && (tempLiczba+c)%5 == 0)
	    T3 = tempLiczba;
	}
      }
      stank = 1;
      break;
    case 8:
      if(znak == '#')
      {
	if(a < 2 && b < 2 && c < 2 && d < 2 && a == !c && b == !d)
	{
	  x3 = a; x4 = b;
	}
      }
      stank = 1;
      break;
    case 9:
      if(znak == '#')
      {

	if(a == 'A')
	{
	  COM_send(':');
	  COM_send(x1 + '0');
	  COM_send(x2 + '0');
	  COM_send(x3 + '0');
	  COM_send(x4 + '0');
	  COM_send(T + '0');
	  cs = (2 - (x1 + x2 + x3 + x4 + T)%2)%2;
	  COM_send(cs + '0');
	  COM_send('#');
	}
	else if(a == 'B')
	{
	  COM_send(':');
	  COM_send(T1 + '0');
	  COM_send(T2 + '0');
	  cs = (5-(T1+T2)%5)%5;
	  COM_send(cs + '0');
	  COM_send('#');
	}
	else if(a == 'C')
	{
	  COM_send(':');
	  COM_send(T3/10 + '0');
	  COM_send(T3%10 + '0');
	  cs = (5-T3%5)%5;
	  COM_send(cs + '0');
	  COM_send('#');
	}
	
      }
      stank = 1;
      break;
    }
  
  L1 = Z1;
  L2 = Z2;
  L3 = Z3;
  L4 = Z4;
  L5 = G;
  
  LCD_xy(0, 0);
  sprintf(buf, "pc1:%d tim1:%2.1f  ", pc1, tim1/10.0f);
  //sprintf(buf, "s:%d x:%d%d%d%d ", stank, x1, x2, x3, x4);
  LCD_puts(buf);
  
  LCD_xy(0, 1);
  sprintf(buf, "pc2:%d tim2:%2.1f  ", pc2, tim2/10.0f);
  LCD_puts(buf);

}
