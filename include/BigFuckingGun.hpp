#ifndef BIGFUCKINGGUN_HPP
#define BIGFUCKINGGUN_HPP

#include "Weapon.hpp"

class CBigFuckingGun : public CWeapon
{
    public:
        CBigFuckingGun ();
        void Init (sf::Texture *pTexture);
};

#endif
