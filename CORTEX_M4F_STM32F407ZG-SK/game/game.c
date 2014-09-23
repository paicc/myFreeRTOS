#include "game.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MESSAGE1   "Level  %d"   //提示信息
//Player1
int16_t player1X = 20;
int16_t player1Y = 35;
uint16_t player1W = 10;
uint16_t player1H = 10;
uint8_t player1IsReversed = 1;
int16_t player1XX;
int16_t i , j , k=0;
int16_t speed=1;

//Player2
int16_t player2X = LCD_PIXEL_WIDTH - 20;
int16_t player2Y = LCD_PIXEL_HEIGHT - 20;
uint16_t player2W = 60;
uint16_t player2H = 10;
uint8_t player2IsReversed = 0;

//Ball
uint16_t ballSize = 5;              //球的大小
//int16_t ballX = ( LCD_PIXEL_WIDTH - 5 ) /2;   //??
//int16_t ballY = ( LCD_PIXEL_HEIGHT - 5 ) /2; //??
int16_t ballX = 50;
int16_t ballY = 35;
int16_t ballVX = 5;
int16_t ballVY = 5;
uint8_t ballIsRun = 0;

//Mode
uint8_t demoMode = 3;

//score
uint8_t score1_0=48;
uint8_t score1_1=48;
uint8_t score2_0=48;
uint8_t score2_1=48;





void
BallReset()
{
    /*
	ballX = ( LCD_PIXEL_WIDTH - 5 ) / 2;
	ballY = ( LCD_PIXEL_HEIGHT - 5) / 2;
    ballX=10;
    ballY=1;

	ballVX = 5;
	ballVY = 5;
    	score2_0=47;
	ballIsRun = 1;
	*/


    ballX= (rand() % (LCD_PIXEL_WIDTH -30) ) ;
    ballY= (rand() % (LCD_PIXEL_HEIGHT-30 )) ;
}
//player1 is burron
void
GAME_EventHandler1()
{
	/*if( STM_EVAL_PBGetState( BUTTON_USER ) ){

		player1IsReversed = 0;

		while( STM_EVAL_PBGetState( BUTTON_USER ) );

		player1IsReversed = 1;
	}*/
}

//player2 is touch
void
GAME_EventHandler2()
{
/*
	if( IOE_TP_GetState()->TouchDetected ){

		player2IsReversed = 1;

		while( IOE_TP_GetState()->TouchDetected );

		player2IsReversed = 0;
	}*/
}

void
GAME_EventHandler3()
{
/*	if( ballIsRun == 0 ){
		BallReset();*/

}

void
GAME_Update()
{
	//Player1
     LCD_SetTextColor( LCD_COLOR_BLACK );
	//LCD_DrawFullRect( player1X+10, player1Y, player1W, player1H );
	//LCD_DrawFullRect( player1X+10, player1Y, player1W, player1H );
	//LCD_DrawFullRect( player2X, player2Y, player2W, player2H );
    //LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );
  LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

    /*demomode3=左向右*/
    if (demoMode==3)
    {
        LCD_SetTextColor( LCD_COLOR_BLACK );
        //LCD_DisplayChar(10,20,LCD_PIXEL_WIDTH);
       // LCD_DrawFullRect( 0, 0,LCD_PIXEL_WIDTH , 10 );
        //LCD_DrawFullRect( 0, 0,10 , LCD_PIXEL_HEIGHT );
        //LCD_DrawFullRect(0, LCD_PIXEL_HEIGHT, LCD_PIXEL_WIDTH , 10 );
        //LCD_DrawFullRect(LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,10 , LCD_PIXEL_HEIGHT );
        LCD_DrawFullRect( player1X, player1Y, player1W, player1H );/*橫的長方形*/
        player1X+=speed;

        if (player1X +j == LCD_PIXEL_WIDTH -10)
        {
            demoMode=7;
        }
        //按下按鈕
        if( STM_EVAL_PBGetState( BUTTON_USER ) )
        {
        /*    for(i=1;i<=(player1H%10+1);i++)
            {
                LCD_DrawFullRect( player1X+j, player1Y, player1H, player1W-j+i*10 );//直的長方形
                LCD_DrawFullRect( player1X, player1Y, player1W-i*10-j, player1H );
            }*/
            player1X=player1X+j;
            demoMode=4;
            while( STM_EVAL_PBGetState( BUTTON_USER ) );
        }

        //按下螢幕
        if( IOE_TP_GetState()->TouchDetected )
        {
            player1Y=player1Y-j;
            demoMode=6;
            while( IOE_TP_GetState()->TouchDetected );
        }

        if( (  (player1X+j  >= ballX -5 ) && (player1X+j <= ballX +5 ) ) && ( ( player1Y >= ballY -5 ) ) && ( player1Y <= ballY +5) )
        {
          BallReset();
          player1W+=5;
          j+=10;
          score2_0++;
            if(score2_0 ==58)
            {
                score2_0=48;
                score2_1++;
                speed+=1;
            }
        }

    }

    /*demomode4=上向下*/
    if (demoMode==4)
    {
        LCD_SetTextColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( player1X, player1Y, player1H, player1W );
        player1Y+=speed;

        if (player1Y + j== LCD_PIXEL_HEIGHT-10)
            demoMode =7 ;

        if( STM_EVAL_PBGetState( BUTTON_USER ) )
        {
            player1Y=player1Y+j;
            demoMode=5;
            while( STM_EVAL_PBGetState( BUTTON_USER ) );
        }

        if( IOE_TP_GetState()->TouchDetected )
        {
            player1X=player1X-j;
            demoMode=3;
            while( IOE_TP_GetState()->TouchDetected );
        }

        if( (  (player1X  >= ballX -5 ) && (player1X <= ballX +5 ) ) && ( ( player1Y+j >= ballY -5 ) ) && ( player1Y+j <= ballY +5) )
        {
            BallReset();
            player1W+=5;
            j+=10;
            score2_0++;
            if(score2_0 ==58)
            {
                score2_0=48;
                score2_1++;
                speed+=1;
            }
        }

    }

    /*右向左*/
    if (demoMode==5)
    {
        LCD_SetTextColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( player1X, player1Y, player1W, player1H );
        player1X-=speed;

        if (player1X -j == 10)
            demoMode=7;

        if( STM_EVAL_PBGetState( BUTTON_USER ) )
        {
            player1Y=player1Y-j;
            demoMode=6;
            while( STM_EVAL_PBGetState( BUTTON_USER ) );
        }

        if( IOE_TP_GetState()->TouchDetected )
        {
            player1X=player1X+j;
            demoMode=4;
            while( IOE_TP_GetState()->TouchDetected );
        }

        if( (  (player1X   >= ballX -5 ) && (player1X  <= ballX +5 ) ) && ( ( player1Y >= ballY -5 ) ) && ( player1Y <= ballY +5) )
        {
            BallReset();
            player1W+=5;
            j+=10;
            score2_0++;
            if(score2_0 ==58)
            {
                score2_0=48;
                score2_1++;
                speed+=1;
            }
        }
    }

    /*下到上*/
     if (demoMode==6)
    {
        LCD_SetTextColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( player1X, player1Y, player1H, player1W );
        player1Y-=speed;

        if (player1Y = j ==  25)
            demoMode = 7;
        if( STM_EVAL_PBGetState( BUTTON_USER ) )
        {
            player1X=player1X;
            demoMode=3;
            while( STM_EVAL_PBGetState( BUTTON_USER ) );
        }

        if( IOE_TP_GetState()->TouchDetected )
        {
            player1Y=player1Y+j;
            demoMode=5;
            while( IOE_TP_GetState()->TouchDetected );
        }

        if( (  (player1X  >= ballX -5 ) && (player1X  <= ballX +5 ) ) && ( ( player1Y  >= ballY -5 ) ) && ( player1Y   <= ballY +5) )
        {
            BallReset();
            player1W+=5;
            j+=10;
            score2_0++;
            if(score2_0 ==58)
            {
                score2_0=48;
                score2_1++;
                speed+=1;
            }
        }
    }

 if (demoMode==7)
{

}


/*
     if( STM_EVAL_PBGetState( BUTTON_USER ) && (demoMode == 5) ){
        demoMode=6;
        }

     if( STM_EVAL_PBGetState( BUTTON_USER ) && (demoMode == 6) ){
        demoMode=3;
        }

*/
	if( demoMode == 0 ){
		/*
		if( player1IsReversed )
			player1X -= 5;
		else
			player1X += 5;

		if( player1X <= 10 )
			player1X -= 5;
		//else if( player1X >= LCD_PIXEL_WIDTH - 20 )
			//player1X += 5;

		if( player1X <= 0 )
			player1X = 0;
		else if( player1X + player1W >= LCD_PIXEL_WIDTH )
			player1X = LCD_PIXEL_WIDTH - player1W;*/
		if( ballVY < 0 ){
			if( player1X + player1W/2 < ballX + ballSize/2 ){
				player1X += 8;
				//player2X += 8;
				}
			else{
				player1X -= 8;
				//player2X -= 8;
				}
			}
			if( player1X <= 0 )
				player1X = 0;
			else if( player1X + player1W >= LCD_PIXEL_WIDTH )
				player1X = LCD_PIXEL_WIDTH - player1W;
		//Player2
		if( player2IsReversed )
			player2X -= 5;
		else
			player2X += 5;

		if( player2X <= 0 )
			player2X = 0;
		else if( player2X + player2W >= LCD_PIXEL_WIDTH )
			player2X = LCD_PIXEL_WIDTH - player2W;

		//Ball
		if( ballIsRun == 1 ){

			LCD_SetTextColor( LCD_COLOR_BLACK );
			LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

			//Touch wall
			ballX += ballVX;
			if( ballX <= 0 ){
				ballX = 0;
				ballVX *= -1;
			}
			else if( ballX + ballSize >= LCD_PIXEL_WIDTH ){
				ballX = LCD_PIXEL_WIDTH - ballSize;
				ballVX *= -1;
			}

			//PONG!
			ballY += ballVY;
			if( ballY + ballSize >= player2Y ){
				if( ballX + ballSize >= player2X && ballX <= player2X + player2W ){
					if( ballX - ballSize <= player2Y + player2W/4 ){
						ballVY =-3;
						ballVX =-7;
					}
					else if( ballX >= player2Y + player2W - player2W/4 ){
						ballVY =-3;
						ballVX = 7;
					}
					else if( ballX + ballSize < player2Y + player2W/2 ){
						ballVY =-7;
						ballVX =-3;
					}
					else if( ballX > player2Y + player2W/2 ){
						ballVY =-7;
						ballVX = 3;
					}
					else{
						ballVY =-9;
						ballVX = 0;
					}
				}
				else
					BallReset();
					 score2_0++;
					 if(score2_0 ==58){
                        			score2_0=48;
                        			score2_1++;
                        			}
			}

			if( ballY <= player1Y + player1H ){
					if( ballX + ballSize >= player1X && ballX <= player1X + player1W ){
						if( ballX - ballSize <= player1Y + player1W/4 ){
							ballVY = 3;
							ballVX =-7;
						}
						else if( ballX >= player1Y + player1W - player1W/4 ){
							ballVY = 3;
							ballVX = 7;
						}
						else if( ballX + ballSize < player1Y + player1W/2 ){
							ballVY = 7;
							ballVX =-3;
						}
						else if( ballX > player1Y + player1W/2 ){
							ballVY = 7;
							ballVX = 3;
						}
						else{
							ballVY = 9;
							ballVX = 0;
						}
					}
					else
						BallReset();
						 score1_0++;
						 if(score1_0 ==58){
                        score1_0=48;
                        score1_1++;
                        }
				}
			}
		}
		if (demoMode == 1)
{
			//Player1 move
			if( ballVY < 0 ){
				if( player1X + player1W/2 < ballX + ballSize/2 ){
					player1X += 8;
					player2X += 2;
				}
				else{
					player1X -= 8;
					player2X -= 2;
				}
			}

			//Player2 move
			if( ballVY > 0 ){
				if( player2X + player2W/2 < ballX + ballSize/2 ){
					player1X += 2;
					player2X += 8;
				}
				else{
					player1X -= 2;
					player2X -= 8;
				}

			}

			if( player1X <= 0 )
				player1X = 0;
			else if( player1X + player1W >= LCD_PIXEL_WIDTH )
				player1X = LCD_PIXEL_WIDTH - player1W;

			if( player2X <= 0 )
				player2X = 0;
			else if( player2X + player2W >= LCD_PIXEL_WIDTH )
				player2X = LCD_PIXEL_WIDTH - player2W;


			//Ball
			if( ballIsRun == 1 ){

				LCD_SetTextColor( LCD_COLOR_BLACK );
				LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

				//Touch wall
				ballX += ballVX;
				if( ballX <= 0 ){
					ballX = 0;
					ballVX *= -1;
				}
				else if( ballX + ballSize >= LCD_PIXEL_WIDTH ){
					ballX = LCD_PIXEL_WIDTH - ballSize;
					ballVX *= -1;
				}

				//PONG!
				ballY += ballVY;
				if( ballY + ballSize >= player2Y ){

					if( ballX + ballSize >= player2X && ballX <= player2X + player2W ){
					if( ballX - ballSize <= player2Y + player2W/4 ){
						ballVY =-3;
						ballVX =-7;
					}
					else if( ballX >= player2Y + player2W - player2W/4 ){
						ballVY =-3;
						ballVX = 7;
					}
					else if( ballX + ballSize < player2Y + player2W/2 ){
						ballVY =-7;
						ballVX =-3;
					}
					else if( ballX > player2Y + player2W/2 ){
						ballVY =-7;
						ballVX = 3;
					}
					else{
						ballVY =-9;
						ballVX = 0;
					}

				}
				else

					BallReset();
			}

			if( ballY <= player1Y + player1H ){
				if( ballX + ballSize >= player1X && ballX <= player1X + player1W ){
                    if( ballX - ballSize <= player1Y + player1W/4 ){
						ballVY = 3;
						ballVX =-7;
					}
					else if( ballX >= player1Y + player1W - player1W/4 ){
						ballVY = 3;
						ballVX = 7;
					}
					else if( ballX + ballSize < player1Y + player1W/2 ){
						ballVY = 7;
						ballVX =-3;
					}
					else if( ballX > player1Y + player1W/2 ){
						ballVY = 7;
						ballVX = 3;
					}
					else{
						ballVY = 9;
						ballVX = 0;
					}

				}

				else
					BallReset();
			}
		}
	}
}

	void
GAME_Render()
{
   /* if((score2_0%2)==0)
        LCD_SetTextColor( LCD_COLOR_BLUE );
     if((score2_0%2)==1)
        LCD_SetTextColor( LCD_COLOR_GREEN );*/
	/*LCD_SetTextColor( LCD_COLOR_GREEN );
	LCD_SetBackColor( LCD_COLOR_BLACK );
	LCD_DrawFullRect( player1X, player1Y, player1W, player1H );*/

/*while(player1X!=100)
    {
                LCD_SetTextColor( LCD_COLOR_GREEN );
               LCD_SetBackColor( LCD_COLOR_BLACK );
               LCD_DrawFullRect( player1X, player1Y, player1W+i, player1H );//直的長方形
               LCD_DrawFullRect( player1X+10, player1Y, player1H, player1W+i );

    }*/

    if (demoMode==3)
    {
        LCD_SetTextColor( LCD_COLOR_GREEN );
        LCD_SetBackColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( 0, 25,LCD_PIXEL_WIDTH , 10 );//橫
        LCD_DrawFullRect( 0, 25,10 , LCD_PIXEL_HEIGHT );//直
        LCD_DrawFullRect(0, LCD_PIXEL_HEIGHT-10, LCD_PIXEL_WIDTH , 10 );
        LCD_DrawFullRect( LCD_PIXEL_WIDTH-10, 25,10 , LCD_PIXEL_HEIGHT-25 );
        LCD_SetTextColor( LCD_COLOR_BLUE );
        LCD_DrawFullRect( player1X, player1Y, player1W, player1H );
        //LCD_DrawFullRect( player1X, player1Y+50, player1H, player1W );
        LCD_SetTextColor( LCD_COLOR_RED );
        LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );
        if( (  (player1X  >= ballX -5 ) && (player1X <= ballX +5 ) ) && ( ( player1Y >= ballY -5 ) ) && ( player1Y <= ballY +5) )
        {
          BallReset();
          score2_0++;
        }
        if (player1X +j == LCD_PIXEL_WIDTH -10)
           demoMode =7;

  /*      if( STM_EVAL_PBGetState( BUTTON_USER ) )
        {
            for(i=1;i<=(player1H%10+1);i++)
            {
                LCD_DrawFullRect( player1X+j, player1Y, player1H, player1W-j+i*10 );//直的長方形
                LCD_DrawFullRect( player1X, player1Y, player1W-i*10-j, player1H );
            }
            demoMode=4;
            while( STM_EVAL_PBGetState( BUTTON_USER ) );
        }
*/

    }
    if (demoMode==4)
    {
        LCD_SetTextColor( LCD_COLOR_GREEN );
        LCD_SetBackColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( 0, 25,LCD_PIXEL_WIDTH , 10 );//上線
        LCD_DrawFullRect( 0, 25,10 , LCD_PIXEL_HEIGHT-25 );//左線
        LCD_DrawFullRect(0, LCD_PIXEL_HEIGHT-10, LCD_PIXEL_WIDTH , 10 );//下線
        LCD_DrawFullRect( LCD_PIXEL_WIDTH-10, 25,10 , LCD_PIXEL_HEIGHT-25 );//右線
        LCD_SetTextColor( LCD_COLOR_BLUE );
        LCD_DrawFullRect( player1X, player1Y, player1H, player1W );
        //LCD_DrawFullRect( player1X, player1Y+50, player1H, player1W );
        LCD_SetTextColor( LCD_COLOR_RED );
        LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

        if( (  (player1X  >= ballX -5 ) && (player1X <= ballX +5 ) ) && ( ( player1Y+j >= ballY -5 ) ) && ( player1Y+j <= ballY +5) )
          BallReset();

        if (player1Y + j == LCD_PIXEL_HEIGHT-10)
            demoMode =7 ;
    }


    if (demoMode==5)
    {
        LCD_SetTextColor( LCD_COLOR_GREEN );
        LCD_SetBackColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( 0, 25,LCD_PIXEL_WIDTH , 10 );//橫
        LCD_DrawFullRect( 0, 25,10 , LCD_PIXEL_HEIGHT );//直
        LCD_DrawFullRect(0, LCD_PIXEL_HEIGHT-10, LCD_PIXEL_WIDTH , 10 );
        LCD_DrawFullRect( LCD_PIXEL_WIDTH-10, 25,10 , LCD_PIXEL_HEIGHT-25 );
        LCD_SetTextColor( LCD_COLOR_BLUE );
        //LCD_DrawFullRect( player1X, player1Y+50, player1H, player1W );
        LCD_DrawFullRect( player1X, player1Y, player1W, player1H );
        LCD_SetTextColor( LCD_COLOR_RED );
        LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

        if( (  (player1X   >= ballX -5 ) && (player1X  <= ballX +5 ) ) && ( ( player1Y >= ballY -5 ) ) && ( player1Y <= ballY +5) )
            BallReset();

        if (player1X - j==10)
            demoMode=7;
    }

    if (demoMode==6)
    {
        LCD_SetTextColor( LCD_COLOR_GREEN );
        LCD_SetBackColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( 0, 25,LCD_PIXEL_WIDTH , 10 );//橫
        LCD_DrawFullRect( 0, 25,10 , LCD_PIXEL_HEIGHT );//直
        LCD_DrawFullRect(0, LCD_PIXEL_HEIGHT-10, LCD_PIXEL_WIDTH , 10 );
        LCD_DrawFullRect( LCD_PIXEL_WIDTH-10, 25,10 , LCD_PIXEL_HEIGHT-25 );
        LCD_SetTextColor( LCD_COLOR_BLUE );
        LCD_DrawFullRect( player1X, player1Y, player1H, player1W );
        //LCD_DrawFullRect( player1X, player1Y+50, player1H, player1W );
        LCD_SetTextColor( LCD_COLOR_RED );
        LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

        if( (  (player1X  >= ballX -5 ) && (player1X <= ballX +5 ) ) && ( ( player1Y >= ballY -5 ) ) && ( player1Y <= ballY +5) )
          BallReset();

        if (player1Y -j ==25)
            demoMode=7;

    }

    if (demoMode == 7)
    {
        LCD_SetTextColor( LCD_COLOR_RED );
        LCD_DisplayStringLine(LINE(10), "   GAME OVER");
        LCD_SetTextColor( LCD_COLOR_GREEN );
        LCD_SetBackColor( LCD_COLOR_BLACK );
        LCD_DrawFullRect( 0, 25,LCD_PIXEL_WIDTH , 10 );//橫
        LCD_DrawFullRect( 0, 25,10 , LCD_PIXEL_HEIGHT );//直
        LCD_DrawFullRect(0, LCD_PIXEL_HEIGHT-10, LCD_PIXEL_WIDTH , 10 );
        LCD_DrawFullRect( LCD_PIXEL_WIDTH-10, 25,10 , LCD_PIXEL_HEIGHT-25 );

    }
	//LCD_DrawFullRect( player1X+10, player1Y, player1W, player1H );
	//LCD_DrawFullRect( player2X, player2Y, player2W, player2H );

	//LCD_DrawLine( 10, LCD_PIXEL_HEIGHT / 2, LCD_PIXEL_WIDTH - 20, LCD_DIR_HORIZONTAL );
    //LCD_SetBackColor(LCD_COLOR_GREEN);
    //LCD_DisplayStringLine(LINE(1), "level %d" , speed);
    //sprintf((char*) score1, MESSAGE1 , score2);
    //LCD_DisplayStringLine(LINE(10), (uint8_t*)score2);
   if (score2_0 == 47)
        score2_0 =48;

    LCD_DisplayChar(0,30, score2_0);
    LCD_DisplayChar(0,15, score2_1);
    //LCD_DisplayStringLine(LINE(10), "HELLO");

    //LCD_DrawRect(30,40,50,50);
    //LCD_DrawFullRect(31, 41, 179, 149);
}

