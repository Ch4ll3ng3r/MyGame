#include "../include/Weapon.hpp"

CWeapon::CWeapon()
{
    m_strBulletTextureName = "";
}

CWeapon::~CWeapon ()
{
}

void CWeapon::Init (sf::Texture *pTexture)
{
    m_pTexture = pTexture;
    m_ShotDelay = 1000;
    m_NbBulletsPerShot = 1;
    m_Damage = 88;
    m_BulletSpread = 0;
    m_fPos.x = 0;
    m_fPos.y = 0;
    m_fVelocity = 1.0f;
    m_LastShotTime = 0;
    m_fBulletWidth = 0.f;
    m_fBulletHeight = 0.f;
}

void CWeapon::Shoot (vector<CBullet*> *vpBullets, vector<sf::Sprite*> *vpSprites, float fDirection, string strShootersName)
{
    sf::Sprite *pSprite = nullptr;
    CBullet *pBullet = nullptr;
    float _fDirection;
    int BulletSpread = 0;
    for (unsigned int i = 0; i < m_NbBulletsPerShot; i++)
    {
        pSprite = new sf::Sprite;
        pSprite->setTexture (*m_pTexture);
        vpSprites->push_back (pSprite);
        BulletSpread = rand () % (m_BulletSpread * 2) - m_BulletSpread;;
        if (m_BulletSpread > 0)
            _fDirection = fDirection + static_cast<float> (BulletSpread);
        else
            _fDirection = fDirection;
        pBullet = new CBullet (pSprite, _fDirection, m_fVelocity, m_fPos, m_fBulletWidth, m_fBulletHeight, strShootersName, m_Damage);
        vpBullets->push_back (pBullet);
    }
}

void CWeapon::SetPos (float fxPos, float fyPos)
{
    m_fPos.x = fxPos;
    m_fPos.y = fyPos;
}

string CWeapon::GetBulletTextureName ()
{
    return m_strBulletTextureName;
}

bool CWeapon::IsShotAvailable (unsigned int Now)
{
    if (m_LastShotTime + m_ShotDelay <= Now)
    {
        m_LastShotTime = Now;
        return true;
    }
    return false;
}
