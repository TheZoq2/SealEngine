#include "line.h"

using namespace zen;

Line::Line()
{
    vertical = false;
}
Line::Line(Vec2f pos0, Vec2f pos1)
{
    create(pos0, pos1);
}
void Line::create(Vec2f pos0, Vec2f pos1)
{
    //Making sure that the x-coordinate of the first position is <= than the second
    this->pos[0] = pos0;
    this->pos[1] = pos1;

    //Calculate the k and m values
    this->calculateConstants();
}

float Line::getMValue()
{
    return this->mValue;
}
float Line::getKValue()
{
    return this->kValue;
}
Vec2f Line::getPosition(uint8_t index)
{
    return this->pos[index];
}
bool Line::isVertical()
{
    return this->vertical;
}
float Line::calculateYValue(float x)
{
    return x * kValue + mValue;
}

Line::IntersectResult Line::getIntersect(Line* other)
{
    IntersectResult result;
    result.intersected = false;

    //Make sure none of the lines is vertical
    if(this->vertical == true && other->isVertical() == true)
    {
        //Nothing to be done. Behaviour for perpendicular lines is considered undefined
    }
    else if(this->vertical == true)
    {
        //Call the intersect function of the other line to deal with this intersection. 
        return other->getIntersect(this);
    }
    else if(other->isVertical() == true)
    {
        float xPos = other->getPosition(0).x;
        if(xPos >= pos[0].x && xPos <= pos[1].x)
        {
            //Calculate the y-value of the point
            float yPos = xPos * kValue + mValue;
            
            if(yPos >= other->getPosition(0).y && yPos <= other->getPosition(1).y)
            {
                result.intersected = true;
                result.pos.x = xPos;
                result.pos.y = yPos;
            }
        }
    }
    else
    {
        //This is calculated using the formula y=kx+m <=> k1 * x + m1 = k2 * x + m2 <=> x=(m2-m1)/(k1-k2)
        float intersectX = (other->getMValue() - this->mValue)/(this->kValue - other->getKValue());
        
        //Make sure that x position is within both lines
        if(intersectX >= pos[0].x && intersectX <= pos[1].x && intersectX >= other->getPosition(0).x && intersectX <= other->getPosition(1).x)
        {
            result.intersected = true;
            result.pos.x = intersectX;
            result.pos.y = intersectX * this->kValue + this->mValue;
        }
    }

    return result;
}

void Line::draw(sf::RenderTarget* window)
{
    sf::Vertex line[] = 
    {
        sf::Vertex(pos[0]),
        sf::Vertex(pos[1])
    };

    window->draw(line, 2, sf::Lines);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//                              Private functions
//////////////////////////////////////////////////////////////////////////////////////////////////
void Line::calculateConstants()
{
    vertical = false;
    //Making sure the points are in the correct order.
    if(pos[1].x < pos[0].x)
    {
        Vec2f temp = pos[1];
        pos[1] = pos[0];
        pos[0] = temp;
    }
    //If the line is vertical
    if(pos[1].x == pos[0].x)
    {
        vertical = true;

        //Rearange the points so the one with the smallest y-value is placed first
        if(pos[1].y < pos[0].y)
        {
            Vec2f temp = pos[1];
            pos[1] = pos[0];
            pos[0] = temp;
        }
        //We can't calculate the m or k values if this is the case
    }
    else
    {
        kValue = (pos[1].y - pos[0].y) / (pos[1].x - pos[0].x);
        mValue = pos[0].y - pos[0].x * kValue;
    }
}

