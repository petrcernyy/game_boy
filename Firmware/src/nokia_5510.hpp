#ifndef NOKIA_5510_H
#define NOKIA_5510_H

#include <Arduino.h>
#include <string.h>

constexpr int LCD_D = 1;
constexpr int LCD_CMD = 0;
constexpr int dummy = 0;

constexpr int LCD_WIDTH = 83;
constexpr int LCD_HEIGHT = 6;

constexpr int CHAR_WIDTH_BIG = 5;
constexpr int CHAR_WIDTH_SMALL = 4;


class Nokia{
    public:
        Nokia(int CLK, int DIN, int DC, int CE, int RST);
        void LCD_Init();
        void LCD_Write(uint8_t data, int dc_state, int x, int y);
        void LCD_Square(int X, int Y, int Size_X, int Size_Y);
        void LCD_SetX(int X);
        void LCD_SetY(int Y);
        void LCD_Clear();
        void LCD_String(char data[], int X, int Y, int Size_font);
        void LCD_Num(char data[], int X, int Y);
        void LCD_Char(int n, int X, int Y, int Size_font);
    private:
        int m_CLK;
        int m_DIN;
        int m_DC;
        int m_CE;
        int m_RST;
        uint8_t m_bank[83][6];

};

void SPI_Init();
void SPI_Write(uint8_t data);

#endif