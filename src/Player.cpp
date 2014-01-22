#include "../include/Player.hpp"

CPlayer::CPlayer (sf::Sprite *pPlayerSprite, CWeapon *pWeapon, float fDirection)
{
    m_pPlayerSprite = nullptr;
    m_pPlayerSprite = pPlayerSprite;
    m_fPos.x = 0.f;
    m_fPos.y = 0.f;
    m_Armor = 200;
    m_bIsAlive = true;
    m_strName = "1337";
    m_fVelocity = 0.5f;
    m_fDirection = fDirection;
    m_pPlayerSprite->setOrigin (30, 30);
    m_pPlayerSprite->setRotation (m_fDirection);
    m_pCurrentWeapon = pWeapon;
}

CPlayer::~CPlayer ()
{
    m_pPlayerSprite = nullptr;
}

void CPlayer::SetPos (sf::Vector2<float> fPos)
{
    m_fPos = fPos;
    m_pPlayerSprite->setPosition (m_fPos);
}

void CPlayer::SetPos (float fxPos, float fyPos)
{
    m_fPos.x = fxPos;
    m_fPos.y = fyPos;
    m_pPlayerSprite->setPosition (m_fPos);
}

void CPlayer::SetName ()
{
    char chName[30];
    cout << "Please type in your name" << endl;
    cin.get (chName, 29);
    m_strName = chName;
}

void CPlayer::SetName (string strName)
{
    m_strName = strName;
}

void CPlayer::SetAlive (bool bIsAlive)
{
    m_bIsAlive = bIsAlive;
}

void CPlayer::SetArmor (int Armor)
{
    m_Armor = Armor;
}

int CPlayer::GetArmor ()
{
    return m_Armor;
}

bool CPlayer::IsAlive ()
{
    return m_bIsAlive;
}

sf::Vector2<float> CPlayer::GetPos ()
{
    return m_fPos;
}

void CPlayer::MoveUp (unsigned int elapsed)
{
    m_fPos.y -= m_fVelocity * static_cast<float> (elapsed);
    m_pPlayerSprite->setPosition (m_fPos);
}

void CPlayer::MoveDown (unsigned int elapsed)
{
    m_fPos.y += m_fVelocity * static_cast<float> (elapsed);
    m_pPlayerSprite->setPosition (m_fPos);
}

void CPlayer::MoveRight (unsigned int elapsed)
{
    m_fPos.x += m_fVelocity * static_cast<float> (elapsed);
    m_pPlayerSprite->setPosition (m_fPos);
}

void CPlayer::MoveLeft (unsigned int elapsed)
{
    m_fPos.x -= m_fVelocity * static_cast<float> (elapsed);
    m_pPlayerSprite->setPosition (m_fPos);
}

void CPlayer::Shoot (vector<CBullet*> *vpBullets, vector<sf::Sprite*> *vpSprites, unsigned int Now)
{
    if (m_pCurrentWeapon->IsShotAvailable (Now))
    {
        if (m_fDirection == 0.f)
            m_pCurrentWeapon->SetPos (m_fPos.x + 40.f, m_fPos.y);
        else
            m_pCurrentWeapon->SetPos (m_fPos.x - 40.f, m_fPos.y);
        m_pCurrentWeapon->Shoot (vpBullets, vpSprites, m_fDirection, m_strName);
    }
}

string CPlayer::GetName ()
{
    return m_strName;
}

void CPlayer::TakeDamage (unsigned int Damage, string strShooterName)
{
    m_Armor -= Damage;
    cout << m_strName << " took " << Damage << " Damage from " << strShooterName << endl;
    if (m_Armor < 0)
        m_Armor = 0;
}

bool CPlayer::IsWithoutArmor ()
{
    return m_Armor == 0;
}

bool CPlayer::CheckCollision (sf::Vector2<float> fSpot)
{
    if (m_fDirection == 180.f)
        return (fSpot.x >= m_fPos.x - 30.f) && (fSpot.x <= m_fPos.x + 30.f) && (fSpot.y >= m_fPos.y - 30.f) && (fSpot.y <= m_fPos.y + 30.f);
    else
        return (fSpot.x <= m_fPos.x + 30.f) && (fSpot.x >= m_fPos.x - 30.f) && (fSpot.y >= m_fPos.y - 30.f) && (fSpot.y <= m_fPos.y + 30.f);
}

float CPlayer::GetDirection ()
{
    return m_fDirection;
}
