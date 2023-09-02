#include "snake.hpp"

extern volatile buttonsdebounc buttons;

Snake::Snake(int size): m_head_x{0}, m_head_y{0}, m_size{size}, m_counter{0}
{
    for(int i = 0; i < 252; i++){
        m_body_x[i] = 0;
        m_body_y[i] = 0;
    }
};

bool Snake::isCounter(){
    if(m_counter > 0){
        return true;
    }
    else{
        return false;
    }
};

void Snake::shiftBody(){
    for(int i = m_counter; i > 0; i--){
        m_body_x[i] = m_body_x[i-1];
        m_body_y[i] = m_body_y[i-1];
    }
    m_body_x[0] = m_head_x;
    m_body_y[0] = m_head_y;
};

void Snake::incX(){
    m_head_x++;
    if(m_head_x > 20){m_head_x = 0;}
};
void Snake::decX(){
    m_head_x--;
    if(m_head_x < 0){m_head_x = 20;}
};
void Snake::incY(){
    m_head_y++;
    if(m_head_y > 11){m_head_y = 0;}
};
void Snake::decY(){
    m_head_y--;
    if(m_head_y < 0){m_head_y = 11;}
};

bool Snake::selfEat(){
    for(int i = 1; i <= m_counter; i++){
        if((m_head_x == m_body_x[i]) && (m_head_y == m_body_y[i])){
          return true;
        }
    }
    return false;
};

bool Snake::checkWin(){
    if(m_counter == 252){
        return true;
    }
    else{
        return false;
      }
};

Treat::Treat(int x, int y, int size): m_x{x}, m_y{y}, m_size{size}{};

int Treat::getX(){
    return m_x;
};
    
int Treat::getY(){
    return m_y;
};

void Treat::addTreat(Snake& snake){
    snake.m_counter++;
    m_x = random(0,21);
    m_y = random(0,12);
CheckAgain:
    for(int i = 0; i <= snake.m_counter; i++){
        if((m_x == snake.m_body_x[i]) && (m_y == snake.m_body_y[i])){
        m_x = random(0,21);
        m_y = random(0,12);
        goto CheckAgain;
        }
    }
};

bool treatCheck(const Snake& snake, const Treat& treat){
  if((snake.m_head_x == treat.m_x) && (snake.m_head_y == treat.m_y)){
    return true;
  }
  else{
    return false;
  }
};

Display_Functions::Display_Functions(){};

void Display_Functions::dispSnake(const Snake& snake, Nokia& display){

    for(int i = 0; i <= snake.m_counter; i++){
        display.LCD_Square((snake.m_body_x[i])*4, (snake.m_body_y[i])*4, snake.m_size, snake.m_size);
    }
};

void Display_Functions::dispTreat(const Treat& treat, Nokia& display){
    display.LCD_Square((treat.m_x*4) + 1, (treat.m_y*4) + 1, treat.m_size, treat.m_size);
};

void snakeMain(Nokia& display){
    display.LCD_Init();
    display.LCD_Clear();

    Display_Functions display_functions;

    Snake snake(4);
    display_functions.dispSnake(snake, display);

    randomSeed(analogRead(A0));
    Treat treat(random(0, 21), random(0, 12), 2);
    display_functions.dispTreat(treat, display);
    while(1){
        if(buttons.SwitchUpstate){
            display.LCD_Clear();
            snake.decY();
            if(treatCheck(snake, treat)){
                treat.addTreat(snake);
            }     

            snake.shiftBody();

            if(snake.selfEat()){if(wait_for_new_game_over(display)){return;}}
            if(snake.checkWin()){if(wait_for_new_game_win(display)){return;}}
            display_functions.dispSnake(snake, display);
            display_functions.dispTreat(treat, display);
            _delay_ms(del);
        }
        else if(buttons.SwitchDownState){
            display.LCD_Clear();
            snake.incY();
            if(treatCheck(snake, treat)){
                treat.addTreat(snake);
            }     

            snake.shiftBody();
            if(snake.selfEat()){if(wait_for_new_game_over(display)){return;}}
            if(snake.checkWin()){if(wait_for_new_game_win(display)){return;}}
            display_functions.dispSnake(snake, display);
            display_functions.dispTreat(treat, display);
            _delay_ms(del);     
        }
        else if(buttons.SwitchRightState){
            display.LCD_Clear();
            snake.incX();
            if(treatCheck(snake, treat)){
                treat.addTreat(snake);
            }     

            snake.shiftBody();
            if(snake.selfEat()){if(wait_for_new_game_over(display)){return;}}
            if(snake.checkWin()){if(wait_for_new_game_win(display)){return;}}
            display_functions.dispSnake(snake, display);
            display_functions.dispTreat(treat, display);
            _delay_ms(del);
        }
        else if(buttons.SwitchLeftState){
            display.LCD_Clear();
            snake.decX();
            if(treatCheck(snake, treat)){
                treat.addTreat(snake);
            }     

            snake.shiftBody();
            if(snake.selfEat()){if(wait_for_new_game_over(display)){return;}}
            if(snake.checkWin()){if(wait_for_new_game_win(display)){return;}}
            display_functions.dispSnake(snake, display);
            display_functions.dispTreat(treat, display);
            _delay_ms(del);
        } 
    }
};

int wait_for_new_game_over(Nokia& display){
    display.LCD_Clear();
    char data[] = "GAME OVER";
    display.LCD_String(data, 15, 2, 2);
    while(1){
        if(buttons.SwitchRightState){
            buttons.SwitchUpstate = 0;
            buttons.SwitchDownState = 0;
            buttons.SwitchRightState = 0;
            buttons.SwitchLeftState = 0;
            return 1;
        }
    }
};

int wait_for_new_game_win(Nokia& display){
    display.LCD_Clear();
    char data[] = "VICTORY";
    display.LCD_String(data, 15, 2, 2);
    while(1){
        if(buttons.SwitchRightState){
            buttons.SwitchUpstate = 0;
            buttons.SwitchDownState = 0;
            buttons.SwitchRightState = 0;
            buttons.SwitchLeftState = 0;
            return 1;
        }
    }
};
