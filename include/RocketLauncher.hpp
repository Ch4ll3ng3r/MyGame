#ifndef ROCKETLAUNCHER_HPP_INCLUDED
#define ROCKETLAUNCHER_HPP_INCLUDED

#include "Weapon.hpp"

class CRocketLauncher : public CWeapon
{
    public:
        CRocketLauncher ();
        void Init (sf::Texture *pTexture);
};


#endif // ROCKETLAUNCHER_HPP_INCLUDED
