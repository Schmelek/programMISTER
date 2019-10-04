#include <iostream>
#include <cmath>

struct vector2f
{
    float x = 0;
    float y = 0;
};

vector2f add(vector2f v1, vector2f v2)
{
    vector2f result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    return result;
}

vector2f mul(vector2f v1, float scalar)
{
    vector2f result;
    result.x = scalar*v1.x;
    result.y = scalar*v1.y;
    return result;
}

vector2f sub(vector2f v1, vector2f v2)
{
    vector2f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}


float len(vector2f v1, vector2f v2)
{
    float result;
    vector2f subvect = sub(v1, v2);
    result = sqrt(pow(subvect.x, 2) + pow(subvect.y, 2));
    return result;
}

float scalarmul(vector2f v1, vector2f v2)
{
    float result;
    result = v1.x*v2.x + v1.y*v2.y;
    return result;
}


float angle(vector2f v1, vector2f v2)
{
    float result;
    if (len(v1, v2) != 0)
        {
        result = scalarmul(v1, v2)/len(v1, v2);
        return result;
        }
    else
        return result = 0;
}

float selflen(vector2f v)
{
    float result;
    vector2f zero;
    zero.x = 0;
    zero.y = 0;
    result = len(v, zero);
    return result;
}


vector2f normalize(vector2f v)
{
    vector2f result;
    result = mul(v, 1/selflen(v));
    return result;
}


vector2f perpendicular(vector2f v)
{
    vector2f result;
    result.x = -v.y;
    result.y = v.x;
    return result;
}



