#include "MikroEmulator.h"

const int MAX_INPUT = 8;
const int MAX_OUTPUT = 5;

char input[MAX_INPUT] = {};
char output[MAX_OUTPUT] = {};

const int DISPLAY_WIDTH = 17;
const int DISPLAY_HEIGHT = 2;

int displayPointerX = 0;
int displayPointerY = 0;

char displayBuf[DISPLAY_HEIGHT][DISPLAY_WIDTH] = {};
char buf[128] = {};

//const int maxMessageSize = 20;

list<char> pcMessageQueue;
list<char> microMessageQueue;

bool isKeyDown(int nVirtKey)
{
  return bool(GetKeyState(nVirtKey) & (1 << 31));
}

void readInput()
{
  for(int i = 0; i < MAX_INPUT; i++)
  {
    input[i] = isKeyDown((int)'1' + i);
  }
}

void gotoxy(int x, int y) {
  COORD pos = {(SHORT)x, (SHORT)y};
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsole, pos);
}

void printInColor(string text, COLOR color)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  WORD colorValue = 0;

  switch(color)
  {
  case COLOR_RED:
    {
      colorValue =  FOREGROUND_RED | FOREGROUND_INTENSITY;
    }
    break;
  case COLOR_GREEN:
    {
      colorValue =  FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    }
    break;
  case COLOR_WHITE:
    {
      colorValue =  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
    break;
  }

  SetConsoleTextAttribute(hConsole, colorValue);
  cout << text;
  SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY ));
}

void printColoredValue(char value, bool tabbed)
{

  if(value) printInColor("  1", COLOR_GREEN);
  else printInColor("  0", COLOR_RED);

  if(tabbed) cout << "\t|";
}

void printInputPanel(int x, int y)
{
  gotoxy(x, y);

  cout << "Input: \n\n";
  cout << "|";
  for(int i = 0; i < MAX_INPUT; i++)
  {
    cout << " aK" << i + 1<< " \t|";
  }
  cout << endl;

  cout << "|";
  for(int i = 0; i < MAX_INPUT; i++)
  {
    cout << "-------|";
  }
  cout << endl;

  cout << "|";
  for(int i = 0; i < MAX_INPUT; i++)
  {
    printColoredValue(input[i]);

  }
  cout << endl;
}

void printOutputPanel(int x, int y)
{
  gotoxy(x, y);

  cout << "Output: \n\n";
  cout << "|";
  for(int i = 0; i < MAX_OUTPUT; i++)
  {
    cout << " L" << i + 1<< " \t|";
  }
  cout << endl;

  cout << "|";
  for(int i = 0; i < MAX_OUTPUT; i++)
  {
    cout << "-------|";
  }
  cout << endl;

  cout << "|";
  for(int i = 0; i < MAX_OUTPUT; i++)
  {
    printColoredValue(output[i]);
  }
  cout << endl;

}

void drawIOPanel(int x, int y)
{
  printInputPanel(x, y);
  printOutputPanel(x, y + 7);
}

void printCharacters(char character, int amount, bool newLine)
{
  for(int i = 0; i < amount; i++)
  {
    cout << character;
    if(newLine && i == (amount - 1)) cout << endl;
  }
}

void drawDisplay(int x, int y)
{
  gotoxy(x, y);

  cout << "LCD Display: \n\n";
  printCharacters('-', DISPLAY_WIDTH + 1);

  for(int i=0; i<DISPLAY_HEIGHT; i++)
  {
    int actualLineWidth = strlen(displayBuf[i]);
    cout <<"|" << displayBuf[i];
    if(actualLineWidth != DISPLAY_WIDTH - 1)
    {
      int charsToAdd = (DISPLAY_WIDTH - 1) - actualLineWidth;

      for(int j = 0; j < charsToAdd ; j++)
      {
	cout << " ";
      }
    }
    cout << "|\n";
  }
  printCharacters('-', DISPLAY_WIDTH + 1);
}

void LCD_init()
{

}

void LCD_xy(char x, char y)
{
  displayPointerX = x;
  displayPointerY = y;
}

void LCD_puts(char* values)
{
  int stringLength = strlen(values);
  char* currChar = &displayBuf[displayPointerY][displayPointerX];

  for(int i = 0; i < stringLength; i++)
  {
    if((i+displayPointerX) > DISPLAY_WIDTH-2) break;

    *currChar++ = values[i];
  }
}

void updateController()
{
  readInput();
  drawIOPanel(0, 8);
  drawDisplay(0, 22);
}

void COM_send(char character, bool isMicro)
{
  list<char>& buffer = isMicro ? pcMessageQueue : microMessageQueue;
  buffer.push_back(character);
}

char COM_recv(bool isMicro)
{
  list<char>& buffer = isMicro ? microMessageQueue : pcMessageQueue;
  char result = 0;

  if(buffer.size() > 0)
  {
    result = buffer.front();
    buffer.pop_front();
  }

  return result;
}

void drawResponsePanel(char x, char y)
{

  char znak = COM_recv(false) & 0x7F;
  if(znak != 0) {
    gotoxy(x, y);
    cout << "Last Response";
    gotoxy(x, y+2);
    cout << "-----------------";
    gotoxy(x, y+4);
    cout << "-----------------";
    gotoxy(x, y+3);
    cout << "|";
  }

  while(znak != 0){
    cout << znak;
    znak = COM_recv(false) & 0x7F;
    if(znak == 0)
    {
      cout << "                  ";
      gotoxy(x+16, y+3);
      cout << "|";
    }
  };

}
