#ifndef SHOTGUN_HPP
#define SHOTGUN_HPP

#include "Weapon.hpp"

class CShotgun : public CWeapon
{
    public:
        CShotgun ();
        void Init (sf::Texture *pTexture);

};


#endif
