#include "../include/Bullet.hpp"

CBullet::CBullet (sf::Sprite *pSprite, float fDirection, float fVelocity, sf::Vector2<float> fPos, float fWidth, float fHeight, string strShootersName, unsigned int Damage)
{
    m_pSprite = nullptr;
    m_pSprite = pSprite;
    m_fDirection = fDirection;
    m_fVelocity = fVelocity;
    m_fPos = fPos;
    m_fWidth = fWidth;
    m_fHeight = fHeight;
    m_pSprite->setOrigin (0, m_fHeight / 2);
    m_pSprite->setRotation (m_fDirection);
    m_pSprite->setPosition (m_fPos);
    m_Damage = Damage;
    m_strShootersName = strShootersName;
}

CBullet::~CBullet ()
{
    delete m_pSprite;
    m_pSprite = nullptr;
}

void CBullet::Delete (vector<sf::Sprite*> *vpSprites)
{
    vector<sf::Sprite*>::iterator i;
    for (i = vpSprites->begin (); i < vpSprites->end (); i++)
    {
        if ((*i) == m_pSprite)
        {
            *i = nullptr;
            vpSprites->erase (i);
        }
    }
}

void CBullet::Fly (unsigned int elapsed)
{
    if (m_fDirection == 0.f)
        m_fPos.x += m_fVelocity * static_cast<float> (elapsed);
    else
        m_fPos.x -= m_fVelocity * static_cast<float> (elapsed);
    m_pSprite->setPosition (m_fPos);
}

sf::Vector2<float> CBullet::GetPos ()
{
    return m_fPos;
}

float CBullet::GetWidth ()
{
    return m_fWidth;
}

float CBullet::GetHeight ()
{
    return m_fHeight;
}

bool CBullet::CheckCollision (sf::Vector2<float> fSpot)
{
    if (m_fDirection == 180.f)
        return (fSpot.x >= m_fPos.x - m_fWidth) && (fSpot.x <= m_fPos.x) && (fSpot.y >= m_fPos.y - m_fHeight / 2) && (fSpot.y <= m_fPos.y + m_fHeight / 2);
    else
        return (fSpot.x <= m_fPos.x + m_fWidth) && (fSpot.x >= m_fPos.x) && (fSpot.y >= m_fPos.y - m_fHeight / 2) && (fSpot.y <= m_fPos.y + m_fHeight / 2);
}

unsigned int CBullet::GetDamage ()
{
    return m_Damage;
}

string CBullet::GetShootersName ()
{
    return m_strShootersName;
}
