#include <iostream>
#include "cmath"
#include "SFML/Graphics.hpp"
#include "vector2f.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>



struct Ball
{
    vector2f position;
    vector2f velocity;

    float radius = 25;

    float R = 100;
    float G = 0;
    float B = 0;

    float dt  = 0.1;
};

void resistBall(Ball* ball)
{
    (*ball).velocity = mul((*ball).velocity, exp(-0.008*(*ball).dt ));
}


void antiBallsticker(Ball* ball1, Ball* ball2)
{
    vector2f tmp1 = (*ball1).position;
    vector2f tmp2 = (*ball2).position;
    vector2f Ox;
    Ox.x = 1;
    Ox.y = 0;
    vector2f Oy;
    Oy.x = 0;
    Oy.y = 1;
    (*ball1).position.x = (*ball2).position.x + ((*ball1).radius +(*ball2).radius)*scalarmul(normalize(sub(tmp1, tmp1)), Ox);
    (*ball1).position.y = (*ball2).position.y + ((*ball1).radius +(*ball2).radius)*scalarmul(normalize(sub(tmp1, tmp2)), Oy);
}


void moveBall(Ball* ball)
{
    if ((*ball).velocity.x > 1000 - (*ball).radius or (*ball).velocity.y < (*ball).radius)
        (*ball).velocity.y = - (*ball).velocity.y;
    if ((*ball).velocity.x > 1000 - (*ball).radius or (*ball).velocity.x < (*ball).radius)
        (*ball).velocity.x = - (*ball).velocity.x;

    resistBall(ball);

    (*ball).position = sub((*ball).velocity, mul((*ball).velocity, (*ball).dt));

}


void drawBall(Ball ball, sf::RenderWindow* window)
{
    int k = ball.radius;

    sf::CircleShape shape(ball.radius);

    for (ball.radius > 0; ball.radius += -1;)
    {
        int Red = ball.R - ball.R*0.7*ball.radius/k;
        int Green = ball.G - ball.G*0.7*ball.radius/k;
        int Blue = ball.B - ball.B*0.7*ball.radius/k;
        
        shape.setRadius(ball.radius);
        shape.setFillColor(sf::Color(Red, Green, Blue));
        shape.setPosition(ball.position.x - ball.radius, ball.position.y - ball.radius);
        (*window).draw(shape);
    }
}



void bumpBall(Ball* ball1, Ball* ball2)
{

    if (len((*ball1).position, (*ball2).position) < ((*ball1).radius + (*ball2).radius))
        antiBallsticker(ball1, ball2);

    if (len((*ball1).position, (*ball2).position) <= (*ball1).radius + (*ball2).radius)
        {
        vector2f tmpposition = normalize(sub((*ball2).position, (*ball1).position));
        vector2f Ox;
        Ox.x = 1;
        Ox.y = 0;
        vector2f Oy;
        Oy.x = 0;
        Oy.y = 1;
        float centralmassvelocity = (pow((*ball1).radius, 3)*scalarmul((*ball1).velocity, tmpposition) + pow((*ball2).radius, 3)*scalarmul((*ball2).velocity, tmpposition))/(pow((*ball1).radius, 3) + pow((*ball2).radius, 3));

        (*ball1).velocity.x = scalarmul((*ball1).velocity, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Ox) + (2*centralmassvelocity - scalarmul((*ball1).velocity, tmpposition))*scalarmul(tmpposition, Ox);
        (*ball1).velocity.y = scalarmul((*ball1).velocity, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Oy) + (2*centralmassvelocity - scalarmul((*ball1).velocity, tmpposition))*scalarmul(tmpposition, Oy);
        (*ball2).velocity.x = scalarmul((*ball2).velocity, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Ox) + (2*centralmassvelocity - scalarmul((*ball2).velocity, tmpposition))*scalarmul(tmpposition, Ox);
        (*ball2).velocity.y = scalarmul((*ball2).velocity, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Oy) + (2*centralmassvelocity - scalarmul((*ball2).velocity, tmpposition))*scalarmul(tmpposition, Oy);

        
        }
}


void createBalls(Ball* balls, int ballsQuantity)
{
    srand(time(NULL));
    for(int i = 0; i < ballsQuantity; i++)
    {
        balls[i].position.x = rand() % 100;
        balls[i].position.y = rand() % 100;
        balls[i].velocity.x = rand() % 150;
        balls[i].velocity.y = rand() % 150;
    } 
}


void bumpAllballs(Ball* balls, int ballsQuantity)
{
    for (int i = 0; i < ballsQuantity; i++)
    {
        for(int j = i + 1;  j < ballsQuantity; j++)
            bumpBall(&balls[i], &balls[j]);
    }
}


void moveAllballs(Ball* balls, int ballsQuantity)
{
    for(int i = 0; i < ballsQuantity; i++)
        moveBall(&balls[i]);
}



void drawAllballs(Ball* balls, int ballsQuantity, sf::RenderWindow* window)
{
    for(int i = 0; i < ballsQuantity; i++)
        drawBall(balls[i], &window);
}


int main()
{
    int ballsQuantity = 0;

    std::cout << "How many balls would you like to observe?" << '\n';
    std::cin >> ballsQuantity;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "idealGase");
    
    Ball* balls = new Ball[ballsQuantity];
    createBalls(balls, ballsQuantity);

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        moveAllballs(balls, ballsQuantity);
        bumpAllballs(balls, ballsQuantity);

        window.clear();
        drawAllballs(balls, ballsQuantity, &window);

        window.display();
    }

    delete[] balls;

    return 0;
}


