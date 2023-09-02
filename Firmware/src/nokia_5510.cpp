#include "nokia_5510.hpp"

uint8_t characters_big[27][5] = {
                                {0xFE, 0x13, 0x11, 0x13, 0xFE}, //A
                                {0xFF, 0x91, 0x91, 0x91, 0x6E}, //B
                                {0x7E, 0xC3, 0x81, 0xC3, 0x66}, //C
                                {0xFF, 0x81, 0x81, 0xC3, 0x7E}, //D
                                {0xFF, 0x89, 0x89, 0x89, 0x81}, //E
                                {0xFF, 0x09, 0x09, 0x01, 0x01}, //F
                                {0x7E, 0xC3, 0x81, 0xA1, 0xE3}, //G
                                {0xFF, 0x04, 0x04, 0x04, 0xFF}, //H
                                {0x81, 0x81, 0xFF, 0x81, 0x81}, //I
                                {0x60, 0xC0, 0x80, 0xC0, 0x7F}, //J
                                {0xFF, 0x1C, 0x36, 0x63, 0xC1}, //K
                                {0xFF, 0x80, 0x80, 0x80, 0x80}, //L
                                {0xFF, 0x06, 0x0C, 0x06, 0xFF}, //M
                                {0xFF, 0x06, 0x3C, 0x60, 0xFF}, //N
                                {0x7E, 0xC3, 0x81, 0xC3, 0x7E}, //O
                                {0xFF, 0x11, 0x11, 0x11, 0x0E}, //P
                                {0x7E, 0xC3, 0xA1, 0x43, 0xBE}, //Q
                                {0xFF, 0x31, 0x71, 0xDB, 0x8E}, //R
                                {0x46, 0xCF, 0x99, 0xF3, 0x62}, //S
                                {0x01, 0x01, 0xFF, 0x01, 0x01}, //T
                                {0x7F, 0xC0, 0x80, 0xC0, 0x7F}, //U
                                {0x3F, 0xE0, 0x80, 0xE0, 0x3F}, //V
                                {0xFF, 0x60, 0x30, 0x60, 0xFF}, //W
                                {0xC3, 0x76, 0x1C, 0x76, 0xC3}, //X
                                {0x0F, 0x18, 0xF0, 0x18, 0x0F}, //Y
                                {0xE1, 0xB1, 0x99, 0x8D, 0x87}, //Z
                                {0x00, 0x00, 0x00, 0x00, 0x00}, //Space
                                };

uint8_t characters_small[28][4] = {
                                    {0xF0, 0x28, 0x28, 0xF0},   //a
                                    {0xF8, 0xA8, 0xA8, 0x50},   //b
                                    {0x70, 0x88, 0x88, 0x50},   //c
                                    {0xF8, 0x88, 0x88, 0x70},   //d
                                    {0xF8, 0xA8, 0xA8, 0x88},   //e
                                    {0xF8, 0x28, 0x28, 0x08},   //f
                                    {0x70, 0x88, 0xC8, 0x50},   //g
                                    {0xF8, 0x20, 0x20, 0xF8},   //h
                                    {0x88, 0xF8, 0xF8, 0x88},   //i
                                    {0x40, 0x80, 0x80, 0x78},   //j
                                    {0xF8, 0x20, 0x50, 0x88},   //k
                                    {0xF8, 0x80, 0x80, 0x80},   //l
                                    {0xF8, 0x10, 0x10, 0xF8},   //m
                                    {0xF8, 0x30, 0x60, 0xF8},   //n
                                    {0x70, 0x88, 0x88, 0x70},   //o
                                    {0xF8, 0x28, 0x28, 0x10},   //p
                                    {0x70, 0x88, 0x48, 0xB0},   //q
                                    {0xF8, 0x68, 0xA8, 0x10},   //r
                                    {0x90, 0xA8, 0xA8, 0x48},   //s
                                    {0x08, 0xF8, 0xF8, 0x08},   //t
                                    {0x78, 0x80, 0x80, 0x78},   //u
                                    {0x38, 0xC0, 0xC0, 0x38},   //v
                                    {0xF8, 0x40, 0x40, 0xF8},   //w
                                    {0xC8, 0x30, 0x60, 0x98},   //x
                                    {0x18, 0xE0, 0xE0, 0x18},   //y
                                    {0xC8, 0xE8, 0xB8, 0x98},   //z
                                    {0x00, 0x00, 0x00, 0x00},   //space
                                    {0x50, 0x50, 0x50, 0x20},   //>
                                    };

uint8_t numbers[10][4] = {
                            {0x7E, 0x81, 0x81, 0x7E},   //0
                            {0x84, 0x86, 0xFF, 0x80},   //1
                            {0xE2, 0xB1, 0x99, 0x8E},   //2
                            {0x42, 0x81, 0x91, 0x6E},   //3
                            {0x1F, 0xF0, 0x18, 0x10},   //4
                            {0x4F, 0x89, 0x89, 0x71},   //5
                            {0x7E, 0x91, 0x91, 0x62},   //6
                            {0xE1, 0x31, 0x19, 0x0F},   //7
                            {0x76, 0x89, 0x89, 0x76},   //8
                            {0x46, 0x89, 0x89, 0x7E},   //9
                        };

void SPI_Init(){
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1);
}

void SPI_Write(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
}

void Nokia::LCD_Init(){

    pinMode(m_CLK, OUTPUT);
    pinMode(m_DIN, OUTPUT);
    pinMode(m_DC, OUTPUT);
    pinMode(m_CE, OUTPUT);
    pinMode(m_RST, OUTPUT);

    SPI_Init();
 
    digitalWrite(m_RST, LOW);
    digitalWrite(m_RST, HIGH);

    LCD_Write(0x21, LCD_CMD, dummy, dummy);
    LCD_Write(0x9F, LCD_CMD, dummy, dummy);
    LCD_Write(0x04, LCD_CMD, dummy, dummy);
    LCD_Write(0x16, LCD_CMD, dummy, dummy);
    LCD_Write(0x0C, LCD_CMD, dummy, dummy);
    LCD_Write(0x20, LCD_CMD, dummy, dummy);
    LCD_Write(0x0C, LCD_CMD, dummy, dummy);
}

void Nokia::LCD_Write(uint8_t data, int dc_state, int x, int y){

    if(dc_state){
        m_bank[x][y] = m_bank[x][y] | data;
    }

    digitalWrite(m_DC, dc_state);
    digitalWrite(m_CE,LOW);
    SPI_Write(data);
    digitalWrite(m_CE, HIGH);
}

void Nokia::LCD_Square(int X, int Y, int Size_X, int Size_Y){

    uint16_t data_Y_0 = 0;
    uint16_t data_Y_1 = 0;
    uint16_t data_Y_2 = 0;

    for(int y = Y; y < (Y + Size_Y); y++){
        if(y > 31){
            data_Y_2 |= (1 << (y - 32));
        }
        else if(y > 15){
            data_Y_1 |= (1 << (y - 16));
        }
        else{
            data_Y_0 |= (1 << y);
        }
    }

    uint8_t banks[6];

    banks[0] = (data_Y_0 & 0xFF);
    banks[1] = ((data_Y_0 >> 8) & 0xFF);
    banks[2] = ((data_Y_1) & 0xFF);
    banks[3] = ((data_Y_1 >> 8) & 0xFF);
    banks[4] = ((data_Y_2) & 0xFF);
    banks[5] = ((data_Y_2 >> 8) & 0xFF);

    for(int y = 0; y < 6; y++){
        LCD_SetX(X);
        LCD_SetY(y);
        for(int x = X; x < (X + Size_X); x++){
            LCD_Write((banks[y] | m_bank[x][y]), LCD_D, x, y);
        }
    }
    
}

void Nokia::LCD_SetX(int X){
    uint8_t data = (X) | (1 << 7);
    LCD_Write(data, LCD_CMD, dummy, dummy);
}

void Nokia::LCD_SetY(int Y){
    uint8_t data = (Y) | (1 << 6);
    LCD_Write(data, LCD_CMD, dummy, dummy);
}

void Nokia::LCD_Clear(){
    for(int i = 0; i < (LCD_WIDTH * LCD_HEIGHT); i++){
        LCD_Write(0x00, LCD_D, dummy, dummy);
    }
    for(int x = 0; x < LCD_WIDTH; x++){
        for(int y = 0; y < LCD_HEIGHT; y++){
            m_bank[x][y] = 0x00;
        }
    }
}

void Nokia::LCD_String(char data[], int X, int Y, int Size_font){

    int x = X;
    int y = Y;
    for(unsigned int i = 0; i < strlen(data); i++){
        int n = (int)data[i] - 65;
        if(data[i] == ' '){
            n = 26;
        }
        else if(data[i] == '>'){
            n = 27;
        }
        LCD_Char(n, x, y, Size_font);
        if(Size_font == 1){
            x = x + 5;
        }
        else if(Size_font == 2){
            x = x + 6;
        }
    }
}

void Nokia::LCD_Num(char data[], int X, int Y){

    int x = X;
    int y = Y;
    for(unsigned int i = 0; i < strlen(data); i++){
        int n = (int)data[i] - 48;
        LCD_Char(n, x, y, 3);
        x = x + 5;
    }
}

void Nokia::LCD_Char(int n, int X, int Y, int Size_font){
    LCD_SetX(X);
    LCD_SetY(Y);
    if(Size_font == 1){
        for(int i = 0; i < CHAR_WIDTH_SMALL; i++){
            LCD_Write(characters_small[n][i], 1, X++, Y);
        }
    }
    else if(Size_font == 2){
        for(int i = 0; i < CHAR_WIDTH_BIG; i++){
            LCD_Write(characters_big[n][i], 1, X++, Y);
        }
    }
    else if(Size_font == 3){
        for(int i = 0; i < CHAR_WIDTH_SMALL; i++){
            LCD_Write(numbers[n][i], 1, X++, Y);
        }
    }
}

Nokia::Nokia(int clk, int din, int dc, int ce, int rst): m_CLK{clk}, m_DIN{din}, m_DC{dc}, m_CE{ce}, m_RST{rst}{};
