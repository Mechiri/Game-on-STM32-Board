/*--------------------------
Vinod Kumar Mechiri(vimech)
Partner: David Morrison
Final Project - Shooting Game
File - main.c
//--------------------------*/

//main.c for lab6
#include <f3d_uart.h>
#include <stm32f30x.h>
#include <stdio.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_mag.h>
#include <f3d_accel.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>
#include <math.h>

#define TIMER 20000
unsigned int enemy_block[100];

//-------------Lost function---------------
void you_lost()
{
  f3d_lcd_fillScreen(YELLOW);
  f3d_lcd_fillblock(10,60,120,140, BLACK);
  f3d_lcd_drawString(40,80,"You Lost!",YELLOW,BLACK );
  f3d_lcd_drawString(40,100,"Press Any",YELLOW,BLACK );
  f3d_lcd_drawString(20,110,"Keyboard Button",YELLOW,BLACK );
  f3d_led_all_off();
  getchar();
}

//-------------Won function---------------
void you_won()
{
  f3d_lcd_fillScreen(YELLOW);
  f3d_lcd_fillblock(10,60,120,140, BLACK);
  f3d_lcd_drawString(40,80,"You WON!",YELLOW,BLACK );
  f3d_lcd_drawString(20,100,"Congratulations",YELLOW,BLACK );
  f3d_lcd_drawString(13,110,"LED LIGHTS FOR YOU",YELLOW,BLACK );
  f3d_led_all_on();
  getchar();
}

//-------------level initialization function---------------
void level_initialization(int level)
{
  if(level)
  {
    if(level == 1)
    {
        int insert_blocks = 0;
        for (insert_blocks = 0; insert_blocks < 10; ++insert_blocks)
        {
          enemy_block[insert_blocks] = rand() % 117;
          if(!enemy_block[insert_blocks])
            enemy_block[insert_blocks] = 20;
          if(enemy_block[insert_blocks]>100)
            enemy_block[insert_blocks] = 90;
          if(enemy_block[insert_blocks]<15)
            enemy_block[insert_blocks] = 15;
        }
        f3d_lcd_fillScreen2(BLACK);
        f3d_lcd_drawString(40,80,"Level-1",YELLOW,BLACK );
        int i;
        for (i = 0; i < 30; i++) 
        {
          delay(20);
        }
        f3d_lcd_fillScreen2(WHITE);
    }
    else if(level == 2)
    {
        int insert_blocks = 0;
        for (insert_blocks = 0; insert_blocks < 20; ++insert_blocks)
        {
          enemy_block[insert_blocks] = rand() % 117;
          if(!enemy_block[insert_blocks])
            enemy_block[insert_blocks] = 20;
          if(enemy_block[insert_blocks]>100)
            enemy_block[insert_blocks] = 90;
          if(enemy_block[insert_blocks]<15)
            enemy_block[insert_blocks] = 15;
        }
        f3d_lcd_fillScreen2(BLACK);
        f3d_lcd_drawString(40,80,"Level-2",YELLOW,BLACK );
        int i;
        for (i = 0; i < 30; i++) 
        {
          delay(20);
        }
        f3d_lcd_fillScreen2(WHITE);
    }
    else if(level == 3)
    {
        int insert_blocks = 0;
        for (insert_blocks = 0; insert_blocks < 30; ++insert_blocks)
        {
          enemy_block[insert_blocks] = rand() % 117;
          if(!enemy_block[insert_blocks])
            enemy_block[insert_blocks] = 20;
          if(enemy_block[insert_blocks]>100)
            enemy_block[insert_blocks] = 90;
          if(enemy_block[insert_blocks]<15)
            enemy_block[insert_blocks] = 15;
        }
        f3d_lcd_fillScreen2(BLACK);
        f3d_lcd_drawString(40,80,"Level-3",YELLOW,BLACK );
        int i;
        for (i = 0; i < 30; i++) 
        {
          delay(20);
        }
        f3d_lcd_fillScreen2(WHITE);
    }
  }
    return;
}

//-------------Welcome Screen function---------------
void welcome_screen()
{
  //Welcome Screen
  f3d_lcd_fillScreen(YELLOW);
  f3d_lcd_drawString(20,40,"Final Project",RED,YELLOW );
  f3d_lcd_drawString(20,90,"SHOOTING GAME",RED,YELLOW );
  f3d_lcd_drawString(20,100,"-------------",RED,YELLOW );
  f3d_lcd_drawString(40,136,"Loading...",BLUE,YELLOW );

    int i;
    for (i = 0; i < 160; i++) 
    {
      delay(20);
      f3d_lcd_drawPixel(i, 145, BLUE);
    }
    f3d_lcd_fillScreen2(WHITE);
}

//-------------lost screen function---------------
void lost_screen_setup(int* start,int* level)
{
  *start = 0;
  you_lost();
  welcome_screen();
  *level = 1;
}

int main(void) 
{
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  //to store pitch_angle and roll_angle data
  float axis[3];

  float pitch_angle;
  float roll_angle;

  float compass;
  char data[8];
  int datapitch_angle;
  int dataroll_angle;


  // Set up your inits before you go ahead
  f3d_uart_init();
  ff3d_led_init();
  f3d_user_btn_init();
  f3d_lcd_init();

  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);

  int buttonState;

 
  welcome_screen();

  int movement_gun =0;
  int random = rand();
  int y1_enemy=0;
  int y2_enemy=10;

  //enemy_block[0] = 20;
  //enemy_block[1] = 60;

  int level = 1;
  int start = 0;
  int next_block = 0;
  int number_of_blocks = 0;
  int power_ups = 0;
  while(1)
  {
    if(level)
    {
      if(level == 1 || level == 2 || level == 3)
      {
        level_initialization(level);
        //level = 0;
        
        start = 1;
        y1_enemy=0;
        next_block = 0; 
        number_of_blocks = 0;
      }
      while(start)
      {
        //------------Levels-------------------//
        if(level == 1)
        {
          if(enemy_block[next_block] > 0)
          {
            if(y1_enemy == 140)
            {
              lost_screen_setup(&start,&level);
              break;
            }
            enemy_block_extra(enemy_block[next_block], y1_enemy);
            delay(5);
          }
        }
        if(level == 2)
        {
          if(enemy_block[next_block] > 0)
          {
            if(y1_enemy == 140)
            {
              lost_screen_setup(&start,&level);
              break;
            }
            enemy_block_extra(enemy_block[next_block], y1_enemy);
            //delay(5);
          }
          if(enemy_block[next_block+1] > 0)
          {
            if(y1_enemy == 140)
            {
              lost_screen_setup(&start,&level);
              break;
            }
            enemy_block_extra(enemy_block[next_block+1], y1_enemy);
            delay(2);
          }
        }
        if(level == 3)
        {
          if(enemy_block[next_block] > 0)
          {
            if(y1_enemy == 140)
            {
              lost_screen_setup(&start,&level);
              break;
            }
            enemy_block_extra(enemy_block[next_block], y1_enemy);
          }
          if(enemy_block[next_block+1] > 0)
          {
            if(y1_enemy == 140)
            {
              lost_screen_setup(&start,&level);
              break;
            }
            enemy_block_extra(enemy_block[next_block+1], y1_enemy);
          }
          if(enemy_block[next_block+2] > 0)
          {
            if(y1_enemy == 140)
            {
              lost_screen_setup(&start,&level);
              break;
            }
            enemy_block_extra(enemy_block[next_block+2], y1_enemy);
            //delay(5);
          }
        }
        //-------------------------------------//

        //-----------gun movement--------------//
        f3d_accel_read(axis);
        pitch_angle = atan2f(axis[0],(sqrtf (powf(axis[1], 2.0)) + (powf(axis[2], 2.0))));
        roll_angle = atan2f(axis[1],(sqrtf (powf(axis[0], 2.0)) + (powf(axis[2], 2.0))));
        movement_gun += (roll_angle *10); 
        gun(movement_gun%96, power_ups);
        //-------------------------------------//
        
        //-----------shooting part-------------//
        if (user_btn_read())
        {
          bullets(movement_gun%96, power_ups);

          //-----------Levels------------------//
          if(level == 1)
          {
            if( ((enemy_block[next_block]+1) <= ((movement_gun%96)+15+power_ups+2)) && (((movement_gun%96)+15-power_ups-2) <= (enemy_block[next_block]+10)) )
            {
              enemy_block_extra_clear(enemy_block[next_block] % 117, y1_enemy);
              enemy_block[next_block] = 0;
              next_block++;
              if(next_block == 10)
              {
                start = 0;
                ++level;
                f3d_led_on(GPIO_Pin_9);
              }
              y1_enemy=0;
            }
            if(next_block == 6)
              power_ups = 10;
            else
              power_ups = 0;
          }
          else if(level == 2)
          {
            if( ((enemy_block[next_block]+1) <= ((movement_gun%96)+15+power_ups+2)) && (((movement_gun%96)+15-power_ups-2) <= (enemy_block[next_block]+10)) )
            {
              enemy_block_extra_clear(enemy_block[next_block] % 117, y1_enemy);
              enemy_block[next_block] = 0;
              ++number_of_blocks;
            }
            if( ((enemy_block[next_block+1]+1) <= ((movement_gun%96)+15+power_ups+2)) && (((movement_gun%96)+15-power_ups-2) <= (enemy_block[next_block+1]+10)) )
            {
              enemy_block_extra_clear(enemy_block[next_block+1] % 117, y1_enemy);
              enemy_block[next_block+1] = 0;
              ++number_of_blocks;
            }
            if(number_of_blocks >= 9 && number_of_blocks <= 12)
              power_ups = 10;
            else
              power_ups = 0;

            if(number_of_blocks == 20)
            {
              start = 0;
              ++level;
              f3d_led_on(GPIO_Pin_10);
            }
            if( (enemy_block[next_block] == 0) && (enemy_block[next_block+1] == 0) )
            {
              next_block+=2;
              y1_enemy=0;
            }
          }
          else if(level == 3)
          {
            if( ((enemy_block[next_block]+1) <= ((movement_gun%96)+15+power_ups+2)) && (((movement_gun%96)+15-power_ups-2) <= (enemy_block[next_block]+10)) )
            {
              enemy_block_extra_clear(enemy_block[next_block] % 117, y1_enemy);
              enemy_block[next_block] = 0;
              ++number_of_blocks;
            }
            if( ((enemy_block[next_block+1]+1) <= ((movement_gun%96)+15+power_ups+2)) && (((movement_gun%96)+15-power_ups-2) <= (enemy_block[next_block+1]+10)) )
            {
              enemy_block_extra_clear(enemy_block[next_block+1] % 117, y1_enemy);
              enemy_block[next_block+1] = 0;
              ++number_of_blocks;
            }
            if( ((enemy_block[next_block+2]+1) <= ((movement_gun%96)+15+power_ups+2)) && (((movement_gun%96)+15-power_ups-2) <= (enemy_block[next_block+2]+10)) )
            {
              enemy_block_extra_clear(enemy_block[next_block+2] % 117, y1_enemy);
              enemy_block[next_block+2] = 0;
              ++number_of_blocks;
            }
            if(number_of_blocks >= 9 && number_of_blocks <= 16)
              power_ups = 10;
            else
              power_ups = 0;
            if(number_of_blocks == 30)
            {
              start=0;
              you_won();
              welcome_screen();
              level=1;
              f3d_led_all_off();
            }
            if( (enemy_block[next_block] == 0) && (enemy_block[next_block+1] == 0) && (enemy_block[next_block+2] == 0) )
            {
              next_block+=3;
              y1_enemy=0;
            }
          }
          //-------------------------------------//
        }
        //-------------------------------------//

        if(level == 1)
        {
          enemy_block_extra_clear(enemy_block[next_block], y1_enemy);
          if(y1_enemy++ >= 170)
            y1_enemy = 0;
        }
        else if(level == 2)
        {
          enemy_block_extra_clear(enemy_block[next_block], y1_enemy);
          enemy_block_extra_clear(enemy_block[next_block+1], y1_enemy);
          if(y1_enemy++ >= 170)
            y1_enemy = 0;
        }
        else if(level == 3)
        {
          enemy_block_extra_clear(enemy_block[next_block], y1_enemy);
          enemy_block_extra_clear(enemy_block[next_block+1], y1_enemy);
          enemy_block_extra_clear(enemy_block[next_block+2], y1_enemy);
          if(y1_enemy++ >= 170)
            y1_enemy = 0;
        }
      }
    }
  }
}



void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
