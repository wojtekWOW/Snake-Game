// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
int tailX[100];
int tailY[100];
int tailLength;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection direction;

void Setup()
{
    gameOver = false;
    direction = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    //Clear console
    system("cls");

    //Draw upper border
    for (int i = 0; i < width+1; i++)
         cout << "-";    
    cout << endl;

    //Draw left and right borders, snake and fruits
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            //Draw left and right borders
            if (i == 0 || i == width - 1)
                cout << "|";

            //Draw Snake head
            if (i == headX && j == headY)
                cout << "O";

            //Draw fruit
            else if (i == fruitX && j == fruitY)
                cout << "x";
            else
            {
                bool print = false;
                for (int k = 0; k < tailLength; k++)
                {

                    if (tailX[k] == i && tailY[k] == j)
                    {
                        cout << "o";
                        print = true;
                    }                    
                }

                //Draw empty field
                if (!print)
                    cout << " ";
            }            
        }
        cout << endl;
                   
              
    }

    //Draw bottom border
    for (int i = 0; i < width+1; i++)
        cout << "-";
    cout << endl;

    //Display score
    cout << "Score = " << score << endl;
}

void Input()
{
    //Read key to change snake movement direction
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            direction = LEFT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    //Calculate each elenten of a tail
    int prevHeadX = tailX[0];
    int prevHeadY = tailY[0];
    int prevTailX, prevTailY;
    tailX[0] = headX;
    tailY[0] = headY;
    for (int i = 1; i < tailLength; i++)
    {
        prevTailX = tailX[i];
        prevTailY = tailY[i];
        tailX[i] = prevHeadX;
        tailY[i] = prevHeadY;
        prevHeadX = prevTailX;
        prevHeadY = prevTailY;

    }

    //Change snake movenemt direction
    switch (direction)  
    {
    case LEFT:
        headX--;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    case RIGHT:
        headX++;
        break;
    default:
        break;
    }
    //Kill the snake in case of collision with wall
    //if (headX<0 || headX>width || headY<0 || headY>height)
    //{
    //    cout << "Game Over!";
    //        gameOver = true;
    //}

    //Allow the snake to go trough the walls
    if (headX < 0) headX = width - 2; if (headX > width-2) headX = 0;
    if (headY < 0) headY = height - 1; if (headY > height-1) headY = 0;

    //Kill the snake in case of collision with the tail
    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;

    //In case of eating a fruit increase tail length, add points and place new fruit
    if (headX == fruitX && headY == fruitY)
    {
        score += 10;
        tailLength++;
        fruitX = rand() % width;
        fruitY = rand() % height;        
    }
}

int main()
{
    Setup();
    while(!gameOver)
    {        
        Draw();
        Input();
        Logic();
        Sleep(300);
    }
    return 0;    
}