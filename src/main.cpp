#include "MikroEmulator.h"
using namespace std;

extern char input[];
extern char output[];

extern char buf[];
extern char pcBuffer[];
extern char microBuffer[];

#define aK(numer) input[(numer - 1)]
#define L(numer) output[(numer - 1)]

#define aK1 aK(1)
#define aK2 aK(2)
#define aK3 aK(3)
#define aK4 aK(4)
#define aK5 aK(5)
#define aK6 aK(6)
#define aK7 aK(7)
#define aK8 aK(8)
#define aK9 aK(9)
#define aK10 aK(10)

#define L1 L(1)
#define L2 L(2)
#define L3 L(3)
#define L4 L(4)
#define L5 L(5)
#define L6 L(6)
#define L7 L(7)
#define L8 L(8)
#define L9 L(9)
#define L10 L(10)

// Include Your Program here
#include "ProgramTest.cpp"

DWORD updatePeriod = 100;
bool inputMode;

int main(int argc, char* argv[])
{
  cout << "|---------------------------------------|\n";
  cout << "|-------------MikroEmulator-------------|\n";
  cout << "|---------------------------------------|\n\n";

  cout << "|---Copyright:-BieluntuBrek-Software----|\n\n";

  LCD_xy(0,0);
  sprintf(buf, "KrzakiKrzaki");
  LCD_puts(buf);

  LCD_xy(0,1);
  sprintf(buf, "KrzakiKrzaki");
  LCD_puts(buf);

  DWORD lastTickCount = GetTickCount();

  updateController();

  char lastPressedKey = 0;
  while(1)
  {

    char pressedKey = 0;

    while((GetTickCount() - lastTickCount ) < updatePeriod)
    {
      if(isKeyDown('Q') || isKeyDown(VK_ESCAPE)) break;

      if(isKeyDown(VK_OEM_1))
      {
	inputMode = true;
	pressedKey = ':';
      }

      if(isKeyDown('3') && isKeyDown(VK_SHIFT))
      {
	pressedKey = '#';
	inputMode = false;
      }

      if(inputMode)
      {
	for(char i = '0'; i <= '9'; i++)
	  if(GetKeyState(i) & (1 << 31)) pressedKey = i;

	for(char i = 'A'; i <= 'Z'; i++)
	  if(GetKeyState(i) & (1 << 31)) pressedKey = i;
      }
    }

    if((inputMode && pressedKey != 0 && lastPressedKey != pressedKey) || pressedKey == '#')
    {
      gotoxy(0, 28);
      cout << pressedKey << endl;
      COM_send(pressedKey, false);
    }

    lastPressedKey = pressedKey;

    if(isKeyDown('Q') || isKeyDown(VK_ESCAPE))
    {
      cout << "\n\n";
      break;
    }

    DWORD timeDelta = GetTickCount() - lastTickCount;
    lastTickCount = GetTickCount();

    while(timeDelta >= updatePeriod)
    {
      timeDelta -= updatePeriod;

      updateState();
      updateController();
    }

    drawResponsePanel(20, 22);
  }
  return 0;
}
