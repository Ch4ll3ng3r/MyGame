#include "../include/DefaultWeapon.hpp"

CDefaultWeapon::CDefaultWeapon ()
{
    m_strBulletTextureName = "BulletDefault";
}

void CDefaultWeapon::Init (sf::Texture *pTexture)
{
    m_pTexture = pTexture;
    m_ShotDelay = 1000;
    m_NbBulletsPerShot = 1;
    m_Damage = 88;
    m_BulletSpread = 0;
    m_fPos.x = 0;
    m_fPos.y = 0;
    m_fVelocity = 0.1f;
    m_LastShotTime = 0;
}
