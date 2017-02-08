// Deklaracje
// --------------------------------------------

char trybPracy=1;

// Tryb 1 i 2
char T1=30, T2=20;

// Tryb 3
char iloscSam=10;

// Ogólne
char Z1, Z2;
char KL1, KL2;
char stan1 = 1, stan2 = 1, stan4 = 1, tim=T2;

// Tryb 3
char stan3_g = 1, stan3_p1 = 1, stan3_p2 = 1, stan3_p3 = 1, stan3_p4 = 1;
char liczSam = iloscSam;

char X2, X6, X4, X8; 

// LCD
char stanLCD=1, timLCD=10, pK1, pK2, pK3, pK4;

// Funkcja G³ówna
// --------------------------------------------
void updateState()
{
  KL1 = aK1;
  KL2 = aK2;
  
  X2 = aK5;
  X6 = aK6;
  X4 = aK7;
  X8 = aK8;
  
  switch(trybPracy)
  {
  case 1:
    {
      switch(stan1)
      {
      case 1:
	{
	  Z1 = 0; Z2 = 0;
	  if(!tim)
	  {
	    stan1 = 2;
	    tim = T1;
	  }
	} break;
      case 2:
	{
	  Z1 = 1; Z2 = 0;
	  if(!tim)
	  {
	    stan1 = 3;
	    tim = T2;
	  }
	} break;
      case 3:
	{
	  Z1 = 0; Z2 = 0;
	  if(!tim)
	  {
	    stan1 = 4;
	    tim = T1;
	  }
	} break;
      case 4:
	{
	  Z1 = 0; Z2 = 1;
	  if(!tim)
	  {
	    stan1 = 1;
	    tim = T2;
	  }
	} break;
      }
      if(tim) --tim;
      
    } break;
  case 2:
    {
      switch(stan2)
      {
      case 1:
	{
	  Z1 = 0; Z2 = 0;
	  if(!tim)
	  {
	    stan2 = 2;
	    tim = T1;
	  }
	} break;
      case 2:
	{
	  Z1 = 1; Z2 = 0;
	  if(!tim && !X2 && !X6) stan2 = 3;
	  else if(!tim && (X2 || X6))
	  {
	    stan2 = 4;
	    tim = T2;
	  }
	} break;
      case 3:
	{
	  Z1 = 1; Z2 = 0;
	  if(X2 || X6)
	  {
	    stan2 = 4;
	    tim = T2;
	  }
	} break;
      case 4:
	{
	  Z1 = 0; Z2 = 0;
	  if(!tim)
	  {
	    stan2 = 5;
	    tim = T1;
	  }
	} break;
      case 5:
	{
	  Z1 = 0; Z2 = 1;
	  if(!tim && !X4 && !X8) stan2 = 6;
	  else if(!tim && (X4 || X8))
	  {
	    stan2 = 1;
	    tim = T2;
	  }
	} break;
      case 6:
	{
	  Z1 = 0; Z2 = 1;
	  if(X4 || X8)
	  {
	    stan2 = 1;
	    tim = T2;
	  }
	} break;
      }
      if(tim) --tim;
      
    } break;
  case 3:
    {
      // Przy Z2
      switch(stan3_p1)
      {
      case 1:
	{
	  if(X2) stan3_p1 = 2;
	} break;
      case 2:
	{
	  if(!X2)
	  {
	    // TODO Make Sure we won't wrap when 2 cars move at the same time
	    // ^^^^
	    // Not Sure Though 
	    --liczSam;
	    stan3_p1 = 1;
	  }
	}
	break;
      }
      
      // Przy Z2
      switch(stan3_p2)
      {
      case 1:
	{
	  if(X6) stan3_p2 = 2;
	} break;
      case 2:
	{
	  if(!X6)
	  {
	    --liczSam;
	    stan3_p2 = 1;
	  }
	} break;
      }
      
      // Przy Z1
      switch(stan3_p3)
      {
      case 1:
	{
	  if(X4) stan3_p3 = 2;
	} break;
      case 2:
	{
	  if(!X4)
	  {
	    --liczSam;
	    stan3_p3 = 1;
	  }
	} break;
      }
      
      // Przy Z1
      switch(stan3_p4)
      {
      case 1:
	{
	  if(X8) stan3_p4 = 2;
	} break;
      case 2:
	{
	  if(!X8)
	  {
	    --liczSam;
	    stan3_p4 = 1;
	  }
	} break;
      }
      
      switch(stan3_g)
      {
      case 1:
	{
	  Z1=0; Z2=0;
	  if(!tim){
	    stan3_g = 2;
	    liczSam = iloscSam;
	  } 
	} break;
      case 2:
	{
	  Z1=1; Z2=0;
	  gotoxy(0,0);
	  std::cout <<(int)liczSam << std::endl;
	  
	  if(liczSam <= 0)
	  {
	    stan3_g = 3;
	    tim = T2;
	  }
	} break;
      case 3:
	{
	  Z1=0; Z2=0;
	  if(!tim){
	    stan3_g = 4;
	    liczSam = iloscSam;
	  } 
	} break;
      case 4:
	{
	  Z1=0; Z2=1;
	  if(liczSam <= 0)
	  {
	    stan3_g = 1;
	    tim = T2;
	  }
	} break;
      }
      
      if(tim) --tim;
      
    } break;
  case 4:
    {
      switch(stan4)
      {
      case 1:
	{
	  Z1 = 0; Z2 = 0;
	  if(!tim)
	  {
	    stan4 = 2;
	    tim = T1;
	  }
	  else if(KL2) stan4 = 3;
	} break;
      case 2:
	{
	  Z1 = 1; Z2 = 0;
	  if(KL2)
	  {
	    stan4 = 3;
	    tim = T2;
	  }
	} break;
      case 3:
	{
	  Z1 = 0; Z2 = 0;
	  if(!tim)
	  {
	    stan4 = 4;
	    tim = T1;
	  }
	  else if(KL2) stan4 = 1;
	} break;
      case 4:
	{
	  Z1 = 0; Z2 = 1;
	  if(KL1)
	  {
	    stan4 = 1;
	    tim = T2;
	  }
	} break;
      }
      if(tim) --tim;
      
    } break;
  }
  
  L1 = Z1; L2 = Z2;
  
  switch(stanLCD)
  {
  case 1:
    {
      LCD_xy(0, 0); LCD_puts("Mikrokontroler !");
      LCD_xy(0, 1); LCD_puts("Inicjalizacja");
      
      if(!timLCD)
      {
	stanLCD = 2;
      }
      
    } break;
  case 2:
    {
      LCD_xy(0, 0);
      sprintf(buffer, "Wybierz TrybO(%d)       ", trybPracy);
      LCD_puts(buffer);
      LCD_xy(0, 1);
      LCD_puts("1, 2, 3, 4        ");
      
      if(aK1 && !pK1)
      {
	stanLCD = 3;
	trybPracy = 1;
      }
      else if(aK2 && !pK2)
      {
	stanLCD = 3;
	trybPracy = 2;
      }
      else if(aK3 && !pK3)
      {
	stanLCD = 6;
	stan3_g = 1;
	trybPracy = 3;
      }
      else if(aK4 && !pK4)
      {
	stanLCD = 7;
	trybPracy = 4;
      }
    } break;
    
    // Tryb 1,2 
    //-----------------------------
  case 3:
    {
      LCD_xy(0, 0); LCD_puts("Wybierz Czas     ");
      LCD_xy(0, 1); LCD_puts("1-Swie,2-Ocz,3-P   ");
      
      if(aK3 && !pK3) stanLCD = 2;
      
      if(aK1 && !pK1) stanLCD = 4;
      if(aK2 && !pK2) stanLCD = 5;
      
    } break;
  case 4:
    {
      LCD_xy(0, 0);
      sprintf(buffer, "CzasSw: %2.1f       ", (float)T1/10.0f);
      LCD_puts(buffer);
      
      LCD_xy(0, 1); LCD_puts("1+, 2-, 3-P       ");
      
      if(aK3 && !pK3) stanLCD = 3;
      
      if(aK1) T1 += 1; 
      if(aK2) T1 -= 1; if(T1 < 30) T1 = 1;
      
    } break;
  case 5:
    {
      LCD_xy(0, 0);
      sprintf(buffer, "CzasOcz: %2.1f       ", (float)T2/10.0f);
      LCD_puts(buffer);
      
      LCD_xy(0, 1); LCD_puts("1+, 2-, 3-P       ");
      
      if(aK3 && !pK3) stanLCD = 3;
      
      if(aK1) T2 += 1; 
      if(aK2) T2 -= 1; if(T2 < 20) T2 = 20;
      
    } break;
        
    // Tryb 3 
    //-----------------------------
  case 6:
    {
      LCD_xy(0, 0);
      sprintf(buffer, "IloscSamo: %d       ", iloscSam);
      LCD_puts(buffer);
      
      LCD_xy(0, 1); LCD_puts("1+, 2-, 3-P       ");
      
      if(aK3 && !pK3) stanLCD = 2;
      
      if(aK1) iloscSam += 1; 
      if(aK2) iloscSam -= 1; if(iloscSam < 5) iloscSam = 5;
      
    } break;
            
    // Tryb 4 
    //-----------------------------
  case 7:
    {
      LCD_xy(0, 0);
      LCD_puts("WlaczSwiatla         ");
      LCD_xy(0, 1); LCD_puts("1-S1, 2-S2, 3-P       ");
      
      if(aK3 && !pK3) stanLCD = 2;
      
      if(aK1 && !pK1) 
      {
	// Przejdz do jakies stanu je¿eli dane ¶wiat³a nie s± otwarte
      }
      if(aK2 && !pK2)
      {
	// Przejdz do jakies stanu je¿eli dane ¶wiat³a nie s± otwarte
      }
    } break;
    
  }
  if(timLCD) --timLCD;
  
  pK1 = aK1;
  pK2 = aK2;
  pK3 = aK3;
  pK4 = aK4;
}
