#include "Bullet.h"

Bullet::Bullet()
{
    m_BulletShape.setSize(sf::Vector2f(4, 2));
}

void Bullet::stop()
{
}

bool Bullet::isInFlight()
{
    return m_InFlight;
}

void Bullet::shoot(float startX, float startY, float xTarget, float yTarget)
{
    // Keep the strack of the bullet
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    // Calculate the gradient of the flight path
    float gradient = (startX - xTarget) / (startY - yTarget);

    // Any gradient less than 1 needs to be negative
    if (gradient < 0) {
        gradient *= -1;
    }

    // Calculate the ratio between x and y
    float ratioXY = m_BulletSpeed / (1 + gradient);

    // Set the "speed" horizontally and vertically
    m_BulletDistanceY = ratioXY;
    m_BulletDistanceX = ratioXY * gradient;

    // Point the bullet in the right direction
    if (xTarget < startX) {
        m_BulletDistanceX *= -1;
    }

    if (yTarget < startY) {
        m_BulletDistanceY *= -1;
    }

    // Set a max range of 1000 pixels
    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;

    // Position the bullet ready to be drawn
    m_BulletShape.setPosition(m_Position);


}

FloatRect Bullet::getPosition()
{
    return m_Position;
}

RectangleShape Bullet::getShape()
{
    return m_BulletShape;
}

void Bullet::update(float elapsedTime)
{
}
