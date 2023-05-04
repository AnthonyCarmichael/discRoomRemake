#include <SFML/Graphics.hpp>
#include "Bonhomme.h"
#include"Scie.h"
#include "mesFonctions.h"


bool ifCollisionBonhomme(Bonhomme& bob)
{
    if (bob.getPosition().x > 700 - 32)
    {
        bob.setPosition(sf::Vector2f(700 - 32, bob.getPosition().y));
        return true;
    }

    else if (bob.getPosition().x < 100)
    {
        bob.setPosition(sf::Vector2f(100, bob.getPosition().y));
        return true;
    }

    else if (bob.getPosition().y > 500 - 32)
    {
        bob.setPosition(sf::Vector2f(bob.getPosition().x, 500 - 32));
        return true;
    }

    else if (bob.getPosition().y < 100)
    {
        bob.setPosition(sf::Vector2f(bob.getPosition().x, 100));
        return true;
    }

    return false;

}

bool ifCollisionScie(Scie& scie,bool& move, int& moveX, int& moveY)
{
    if (scie.getPosition().x > 700 - 32)
    {
        moveX = moveX / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    else if (scie.getPosition().x < 100)
    {
        moveX = moveX / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    else if (scie.getPosition().y > 500 - 32)
    {
        moveY = moveY / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    else if (scie.getPosition().y < 100)
    {
        moveY = moveY / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    return false;

}
