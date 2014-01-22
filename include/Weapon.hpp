#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Bullet.hpp"
#include <stdlib.h>

class CWeapon
{
    public:
        CWeapon ();
        virtual ~CWeapon ();
        virtual void Init (sf::Texture *pTexture);
        void Shoot (std::vector<CBullet*> *vpBullets, std::vector<sf::Sprite*> *vpSprites, float fDirection, std::string strShootersName);
        void SetPos (float fxPos, float fyPos);
        string GetBulletTextureName ();
        bool IsShotAvailable (unsigned int Now);

    protected:
        unsigned int m_ShotDelay;
        unsigned int m_NbBulletsPerShot;
        unsigned int m_Damage;
        unsigned int m_BulletSpread;
        sf::Texture *m_pTexture;
        sf::Vector2<float> m_fPos;
        float m_fVelocity;
        string m_strBulletTextureName;
        unsigned int m_LastShotTime;
        float m_fBulletWidth;
        float m_fBulletHeight;
};

#endif
