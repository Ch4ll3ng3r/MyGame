#ifndef PLAYER_HPP
#define PLAYER_HPP

//#include <SFML/Graphics.hpp>
#include "Shotgun.hpp"
#include "BigFuckingGun.hpp"
#include "RocketLauncher.hpp"
#include <map>
#include <iostream>

class CPlayer
{
    public:
        CPlayer (sf::Sprite *pPlayerSprite, CWeapon *pWeapon, float fDirection);
        ~CPlayer ();
        void SetPos (sf::Vector2<float> fPos);
        void SetPos (float fxPos, float fyPos);
        void SetName ();
        void SetName (string strName);
        void SetAlive (bool bIsAlive);
        int GetArmor ();
        void SetArmor (int Armor);
        void TakeDamage (unsigned int Damage, string strShooterName);
        bool IsAlive ();
        sf::Vector2<float> GetPos ();
        void MoveUp (unsigned int elapsed);
        void MoveDown (unsigned int elapsed);
        void MoveRight (unsigned int elapsed);
        void MoveLeft (unsigned int elapsed);
        void Shoot (vector<CBullet*> *vpBullets, vector<sf::Sprite*> *vpSprites, unsigned int Now);
        string GetName ();
        bool IsWithoutArmor ();
        bool CheckCollision (sf::Vector2<float> fSpot);
        float GetDirection ();

    private:
        sf::Vector2<float> m_fPos;
        string m_strName;
        int m_Armor;
        bool m_bIsAlive;
        sf::Sprite *m_pPlayerSprite;
        float m_fVelocity;
        float m_fDirection;
        CWeapon *m_pCurrentWeapon;
};

#endif
