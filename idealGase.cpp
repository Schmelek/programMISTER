#include <iostream>
#include "cmath"
#include "txLib.h"
#include "vector2f.h"



struct Ball
{
    vector2f q;

    vector2f v;

    float r = 25;

    float R = 0;
    float G = 0;
    float B = 0;

    float dt  = 0.1;
};

void resistBall(Ball* ball)
{
    (*ball).v = mul((*ball).v, exp(-0.008*(*ball).dt ));
}


void antiBallsticker(Ball* ball1, Ball* ball2)
{
    vector2f tmp1 = (*ball1).q;
    vector2f tmp2 = (*ball2).q;
    vector2f Ox;
    Ox.x = 1;
    Ox.y = 0;
    vector2f Oy;
    Oy.x = 0;
    Oy.y = 1;
    (*ball1).q.x = (*ball2).q.x + ((*ball1).r +(*ball2).r)*scalarmul(normalize(sub(tmp1, tmp1)), Ox);
    (*ball1).q.y = (*ball2).q.y + ((*ball1).r +(*ball2).r)*scalarmul(normalize(sub(tmp1, tmp2)), Oy);
}


void moveBall(Ball* ball)
{
    if ((*ball).v.x > 1000 - (*ball).r or (*ball).v.y < (*ball).r)
        (*ball).v.y = - (*ball).v.y;
    if ((*ball).v.x > 1000 - (*ball).r or (*ball).v.x < (*ball).r)
        (*ball).v.x = - (*ball).v.x;

    resistBall(ball);

    (*ball).q = sub((*ball).v, mul((*ball).v, (*ball).dt));

}


void drawBall(Ball ball)
{
    int k = ball.r;

    for (ball.r > 0; ball.r += -1;)
    {
        txSetColor(RGB(ball.R - ball.R*0.7*ball.r/k, ball.G - ball.G*0.7*ball.r/k, ball.B - ball.B*0.7*ball.r/k));
        txSetFillColor(RGB(ball.R - ball.R*0.7*ball.r/k, ball.G - ball.G*0.7*ball.r/k, ball.B - ball.B*0.7*ball.r/k));
        txCircle(ball.q.x, ball.q.y, ball.r);
    }
    txSetFillColor(RGB(20, 100, 0));
}


void bumpBall(Ball* ball1, Ball* ball2)
{

    if (len((*ball1).q, (*ball2).q) < ((*ball1).r + (*ball2).r))
        antiBallsticker(ball1, ball2);

    if (len((*ball1).q, (*ball2).q) <= (*ball1).r + (*ball2).r)
        {
        vector2f tmpv = sub((*ball1).v, (*ball2).v);
        vector2f tmpq = normalize(sub((*ball2).q, (*ball1).q));
        vector2f Ox;
        Ox.x = 1;
        Ox.y = 0;
        vector2f Oy;
        Oy.x = 0;
        Oy.y = 1;
        float masscoefficient1 = (pow((*ball2).r, 3) - pow((*ball1).r, 3))/(pow((*ball1).r, 3) + pow((*ball2).r, 3));
        float masscoefficient2 = 2*pow((*ball1).r, 3)/(pow((*ball1).r, 3) + pow((*ball2).r, 3));

        (*ball1).v.x = scalarmul(tmpv, perpendicular(tmpq))*scalarmul(Ox, perpendicular(tmpq)) + scalarmul(tmpv, tmpq)*masscoefficient1*scalarmul(tmpq, Ox) + (*ball2).v.x;
        (*ball1).v.y = scalarmul(tmpv, perpendicular(tmpq))*scalarmul(Oy, perpendicular(tmpq)) + scalarmul(tmpv, tmpq)*masscoefficient1*scalarmul(tmpq, Oy) + (*ball2).v.y;
        (*ball2).v.x = masscoefficient2*scalarmul(tmpv, tmpq)*scalarmul(tmpq, Ox) +(*ball2).v.x;
        (*ball2).v.y = masscoefficient2*scalarmul(tmpv, tmpq)*scalarmul(tmpq, Oy) +(*ball2).v.y;
        }
}

int main()
{
    txCreateWindow(1000, 1000);
    Ball* balls = new Ball[50];
    for(int k = 0; k += 1; k <= 50)
    {
        balls[k].r = 5;
        balls[k].R = 100;
        balls[k].G = 0;
        balls[k].B = 0;
        balls[k].q.x = 10*k + 10;
        for(int i = 0; i += 1; i <= 50)
            balls[i].q.y = 10*i + 10;
    }
    for(;;)
    {
        for(int i = 1; i += 1; i <= 50)
        {
            drawBall(balls[i]);
            for(int p = 0; p += 1; p <= 50)
                bumpBall(&balls[i], &balls[p]);
            moveBall(&balls[i]);
        }
    txSleep(0.01);
    txClear();
    }
}

