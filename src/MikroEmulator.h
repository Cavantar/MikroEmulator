#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <list>

using namespace std;

enum COLOR{
  COLOR_RED,
  COLOR_GREEN,
  COLOR_WHITE
};

bool isKeyDown(int nVirtKey);
void readInput();
void gotoxy(int x, int y);
void printInColor(std::string text, COLOR color);
void printColoredValue(char value, bool tabbed = true);
void printInputPanel(int x, int y);
void printOutputPanel(int x, int y);
void drawIOPanel(int x, int y);
void printCharacters(char character, int amount, bool newLine = true);
void drawDisplay(int x, int y);
void LCD_init();
void LCD_xy(char x, char y);
void LCD_puts(char* values);
void updateController();

void COM_send(char character, bool isMicro = true);
char COM_recv(bool isMicro = true);

void drawResponsePanel(char x, char y);
