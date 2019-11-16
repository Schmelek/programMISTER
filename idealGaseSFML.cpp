#include <iostream>
#include "cmath"
#include "SFML/Graphics.hpp"
#include "vector2f.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>


const float dt = 0.001;

struct Ball
{
    vector2f position;
    vector2f velocity;

    float radius = 25;

    float R = 255;
    float G = 0;
    float B = 0;


    Ball(vector2f position, vector2f velocity, float radius, int R, int G, int B); //new consctructor 
    Ball();

    void draw(sf::RenderWindow* window)
    {
        sf::CircleShape shape(this->radius);

        for(int i = this->radius;i > 0; i = i - 2)
        {
            int currentRed = this->R - this->R*0.85*i/this->radius;
            int currentGreen = this->G - this->G*0.85*i/this->radius;
            int currentBlue = this->B - this->B*0.85*i/this->radius;

            shape.setRadius(i);
            shape.setFillColor(sf::Color(currentRed, currentGreen, currentBlue));
            shape.setPosition(this->position.x - i, this->position.y - i);
            window->draw(shape);
        }

    }

    void move(float dt)
    {
        if ( this->position.y > (1000 - this->radius) or this->position.y < this->radius)
            this->velocity.y = -this->velocity.y;
        if ( this->position.x > (1000 - this->radius) or this->position.x < this->radius)
            this->velocity.x = -this->velocity.x;

        this->position.x += this->velocity.x * dt;
        this->position.y += this->velocity.y * dt;
    }
     
};




Ball::Ball(vector2f position, vector2f velocity, float radius, int R, int G, int B) 
{
    this->position = position;
    this->velocity = velocity;
    this->radius = radius;
    this->R = R;
    this->G = G;
    this->B = B;
}

Ball::Ball()
{
}



void resistBall(Ball* ball)
{
    (*ball).velocity = mul((*ball).velocity, exp(-0.008*dt ));
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
    (*ball1).position.x = tmp2.x + ((*ball1).radius +(*ball2).radius)*scalarmul(normalize(sub(tmp1, tmp2)), Ox);
    (*ball1).position.y = tmp2.y + ((*ball1).radius +(*ball2).radius)*scalarmul(normalize(sub(tmp1, tmp2)), Oy);
}

void antiWallsticker(Ball* ball)
{
    srand(time(NULL));
    if ((*ball).position.x > 1000 - (*ball).radius or (*ball).position.x < (*ball).radius)
    {     
        (*ball).position.x = (*ball).radius + rand() % 1000 - (*ball).radius; 
        (*ball).position.y = (*ball).radius + rand() % 1000 - (*ball).radius;
    }

    if ((*ball).position.y > 1000 - (*ball).radius or (*ball).position.y < (*ball).radius)
    {
        (*ball).position.x = (*ball).radius + rand() % 1000 - (*ball).radius; 
        (*ball).position.y = (*ball).radius + rand() % 1000 - (*ball).radius;    
    }


}

void moveBall(Ball* ball)
{
    if ((*ball).position.x > 1000 - (*ball).radius or (*ball).position.x < (*ball).radius)
        (*ball).velocity.x = - (*ball).velocity.x;
    if ((*ball).position.y > 1000 - (*ball).radius or (*ball).position.y < (*ball).radius)
        (*ball).velocity.y = - (*ball).velocity.y;

    resistBall(ball);
    //antiWallsticker(ball);

    (*ball).position = mul((*ball).velocity, dt);

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
        vector2f v1 = (*ball1).velocity;
        vector2f v2 = (*ball2).velocity;
        float centralmassvelocity = (pow((*ball1).radius, 3)*scalarmul((*ball1).velocity, tmpposition) + pow((*ball2).radius, 3)*scalarmul((*ball2).velocity, tmpposition))/(pow((*ball1).radius, 3) + pow((*ball2).radius, 3));

        (*ball1).velocity.x = scalarmul(v1, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Ox) + (2*centralmassvelocity - scalarmul(v1, tmpposition))*scalarmul(tmpposition, Ox);
        (*ball1).velocity.y = scalarmul(v1, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Oy) + (2*centralmassvelocity - scalarmul(v1, tmpposition))*scalarmul(tmpposition, Oy);
        (*ball2).velocity.x = scalarmul(v2, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Ox) + (2*centralmassvelocity - scalarmul(v2, tmpposition))*scalarmul(tmpposition, Ox);
        (*ball2).velocity.y = scalarmul(v2, perpendicular(tmpposition))*scalarmul(perpendicular(tmpposition), Oy) + (2*centralmassvelocity - scalarmul(v2, tmpposition))*scalarmul(tmpposition, Oy);

    }
}


void createBalls(Ball* balls, int ballsQuantity)
{
    srand(time(NULL));
    for(int i = 0; i < ballsQuantity; i++)
    {
        balls[i].position.x = rand() % (1000 - 100) + 65;
        balls[i].position.y = rand() % (1000 - 100) + 65;
        balls[i].velocity.x = rand() % 100;
        balls[i].velocity.y = rand() % 100;
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
        balls[i].move(dt);
}



void drawAllballs(Ball* balls, int ballsQuantity, sf::RenderWindow* window)
{
    for(int i = 0; i < ballsQuantity; i++)
        balls[i].draw(window);
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

