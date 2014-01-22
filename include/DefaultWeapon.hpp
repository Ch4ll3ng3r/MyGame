#ifndef DEFAULTWEAPON_HPP
#define DEFAULTWEAPON_HPP

#include "Weapon.hpp"

class CDefaultWeapon : public CWeapon
{
    public:
        CDefaultWeapon ();
        void Init (sf::Texture *pTexture);
};

#endif
