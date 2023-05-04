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

bool ifCollisionScie(Scie& scie)
{
    if (scie.getPosition().x > 700 - 32)
    {
        scie.setPosition(sf::Vector2f(700 - 32, scie.getPosition().y));
        return true;
    }

    else if (scie.getPosition().x < 100)
    {
        scie.setPosition(sf::Vector2f(100, scie.getPosition().y));
        return true;
    }

    else if (scie.getPosition().y > 500 - 32)
    {
        scie.setPosition(sf::Vector2f(scie.getPosition().x, 500 - 32));
        return true;
    }

    else if (scie.getPosition().y < 100)
    {
        scie.setPosition(sf::Vector2f(scie.getPosition().x, 100));
        return true;
    }

    return false;

}
