#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class CBullet
{
    public:
        CBullet (sf::Sprite *pSprite, float fDirection, float fVelocity, sf::Vector2<float> fPos,
                 float fWidth, float fHeight, string strShootersName, unsigned int Damage);
        ~CBullet ();
        void Delete (vector<sf::Sprite*> *vpSprites);
        void Fly (unsigned int elapsed);
        sf::Vector2<float> GetPos ();
        float GetWidth ();
        float GetHeight ();
        int GetShootersTeam ();
        string GetShootersName ();
        bool CheckCollision (sf::Vector2<float> fSpot);
        unsigned int GetDamage ();

    private:
        float m_fVelocity;
        float m_fDirection;
        sf::Vector2<float> m_fPos;
        sf::Sprite *m_pSprite;
        float m_fWidth;
        float m_fHeight;
        unsigned int m_Damage;
        string m_strShootersName;
};

#endif
