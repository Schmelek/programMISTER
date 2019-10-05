#include <iostream>
#include "cmath"
#include "SFML/Graphics.hpp"
#include "vector2f.h"



struct Ball
{
    vector2f position;
    vector2f velocity;

    float radius = 25;

    float R = 0;
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


void drawBall(Ball ball)
{
    int k = ball.radius;

    for (ball.radius > 0; ball.radius += -1;)
    {
        sf::CircleShape shape((*ball).radius);
        txSetColor(RGB(ball.R - ball.R*0.7*ball.radius/k, ball.G - ball.G*0.7*ball.radius/k, ball.B - ball.B*0.7*ball.radius/k));
        txSetFillColor(RGB(ball.R - ball.R*0.7*ball.radius/k, ball.G - ball.G*0.7*ball.radius/k, ball.B - ball.B*0.7*ball.radius/k));
        txCircle(ball.position.x, ball.position.y, ball.radius);
    }
    txSetFillColor(RGB(20, 100, 0));
}


void bumpBall(Ball* ball1, Ball* ball2)
{

    if (len((*ball1).position, (*ball2).position) < ((*ball1).radius + (*ball2).radius))
        antiBallsticker(ball1, ball2);

    if (len((*ball1).position, (*ball2).position) <= (*ball1).radius + (*ball2).radius)
        {
        vector2f tmpv = sub((*ball1).velocity, (*ball2).velocity);
        vector2f tmpposition = normalize(sub((*ball2).position, (*ball1).position));
        vector2f Ox;
        Ox.x = 1;
        Ox.y = 0;
        vector2f Oy;
        Oy.x = 0;
        Oy.y = 1;
        float masscoefficient1 = (pow((*ball2).radius, 3) - pow((*ball1).radius, 3))/(pow((*ball1).radius, 3) + pow((*ball2).radius, 3));
        float masscoefficient2 = 2*pow((*ball1).radius, 3)/(pow((*ball1).radius, 3) + pow((*ball2).radius, 3));

        (*ball1).velocity.x = scalarmul(tmpv, perpendicular(tmpposition))*scalarmul(Ox, perpendicular(tmpposition)) + scalarmul(tmpv, tmpposition)*masscoefficient1*scalarmul(tmpposition, Ox) + (*ball2).v.x;
        (*ball1).velocity.y = scalarmul(tmpv, perpendicular(tmpposition))*scalarmul(Oy, perpendicular(tmpposition)) + scalarmul(tmpv, tmpposition)*masscoefficient1*scalarmul(tmpposition, Oy) + (*ball2).v.y;
        (*ball2).velocity.x = masscoefficient2*scalarmul(tmpv, tmpposition)*scalarmul(tmpposition, Ox) +(*ball2).velocity.x;
        (*ball2).velocity.y = masscoefficient2*scalarmul(tmpv, tmpposition)*scalarmul(tmpposition, Oy) +(*ball2).velocity.y;
        }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "idealGase");
    Ball* balls = new Ball[50];

    for(int k = 0; k < 50; k++)
    {
        balls[k].radius = 5;
        balls[k].R = 100;
        balls[k].G = 0;
        balls[k].B = 0;
        balls[k].position.x = 10*k + 10;
        for(int i = 0; i < 50; i++)
            balls[i].position.y = 10*i + 10;
    }

    for(;;)
    {
        for(int i = 1; i < 50; i++)
        {
            drawBall(balls[i]);
            for(int p = 0; p < 50; p++)
                bumpBall(&balls[i], &balls[p]);
            moveBall(&balls[i]);
        }

        txSleep(0.01);
        txClear();
    }
}