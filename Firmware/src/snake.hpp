#ifndef SNAKE_H
#define SNAKE_H

#include <Arduino.h>
#include "hardware.hpp"
#include "nokia_5510.hpp"
#include "buttons.hpp"

int wait_for_new_game_over(Nokia& display);
int wait_for_new_game_win(Nokia& display);

class Treat;

class Snake{
  private:
    int m_head_x;
    int m_head_y;

    int m_body_x[252];
    int m_body_y[252];

    int m_size;

    int m_counter;

  public:
    Snake(int size);
    bool isCounter();
    void shiftBody();

    void incX();
    void decX();
    void incY();
    void decY();

    bool selfEat();
    bool checkWin();

    friend class Display_Functions;
    friend class Treat;

    friend bool treatCheck(const Snake& snake, const Treat& treat);

};

class Treat{
  private:
    int m_x;
    int m_y;

    int m_size;

  public:
    Treat(int x, int y, int size);

    int getX();
    int getY();

    void addTreat(Snake& snake);

    friend bool treatCheck(const Snake& snake, const Treat& treat);

    friend class Display_Functions;
};

class Display_Functions{

  public:
    Display_Functions();

    void dispSnake(const Snake& snake, Nokia& display);

    void dispTreat(const Treat& treat, Nokia& display);

};

void snakeMain(Nokia& display);

#endif