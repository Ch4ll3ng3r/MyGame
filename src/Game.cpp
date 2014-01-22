#include "../include/Game.hpp"
#include "../include/SafeDelete.hpp"

CGame::CGame ()
{
    // Create window
    m_pWindow = nullptr;
    m_pPlayer1 = nullptr;
    m_pPlayer2 = nullptr;
    m_pWindow = new sf::RenderWindow (sf::VideoMode::getDesktopMode (), "My Game", sf::Style::Fullscreen);

    LoadTextures ();
    LoadSprites ();

    // Create Players and Weapons
    SelectWeapons ();
    m_pPlayer1 = new CPlayer (m_vpSprites.at(1), m_pWeapon1, 0.f);
    m_pPlayer1->SetName ("Tim");
    m_pPlayer1->SetPos (31.f, 540.f);
    m_pPlayer2 = new CPlayer (m_vpSprites.at(2), m_pWeapon2, 180.f);
    m_pPlayer2->SetName ("Tom");
    m_pPlayer2->SetPos (1889.f, 540.f);

    // Init Time
    m_Elapsed = 0;
    m_LastRenderingTime = 0;
    m_CurEventElapsed = 0;
    m_LastEventHandlingTime = 0;
    m_bRun = true;
}

void CGame::Run ()
{
    while ((m_pWindow->isOpen()) && (m_bRun))
    {
        // Process events
        sf::Event event;
        while (m_pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_pWindow->close();
                m_bRun = false;
            }
        }

        // Clear screen
        m_pWindow->clear();

        // Render Sprites
        RenderSprites ();

        // Update the Window
        m_pWindow->display();

        // Waits for Frame Sync
        AwaitingFrameSync ();
    }

    cout << "Press esc to quit" << endl;

    while ((m_pWindow->isOpen()) && (!m_bRun))
    {
        // Process events
        sf::Event event;
        while (m_pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_pWindow->close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                m_pWindow->close();
        }

        // Clear screen
        m_pWindow->clear();

        // Render Sprites
        m_pWindow->draw (*m_pGameOverSprite);

        // Update the Window
        m_pWindow->display();
    }
}

CGame::~CGame ()
{
    vector<CBullet*>::iterator i;
    for (i = m_vpBullets.begin (); i < m_vpBullets.end (); i++)
    {
        if ((*i) != nullptr)
        {
            (*i)->Delete (&m_vpSprites);
            delete (*i);
            (*i) = nullptr;
        }
    }
    for (i = m_vpBulletsToDelete.begin (); i < m_vpBulletsToDelete.end (); i++)
    {
        if ((*i) != nullptr)
        {
            (*i)->Delete (&m_vpSprites);
            delete (*i);
            *i = nullptr;
            m_vpBulletsToDelete.erase (i);
        }
    }
    SAFE_DELETE (m_pPlayer1);
    SAFE_DELETE (m_pPlayer2);
    SAFE_DELETE (m_pGameOverSprite);
    SAFE_DELETE (m_pWeapon1);
    SAFE_DELETE (m_pWeapon2);
    vector<sf::Sprite*>::iterator j;
    for (j = m_vpSprites.begin (); j < m_vpSprites.end (); j++)
    {
        if ((*j) != nullptr)
        {
            delete (*i);
            (*j) = nullptr;
        }
    }
    SAFE_DELETE (m_pWindow);
}

void CGame::RenderSprites ()
{
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        m_pWindow->draw (*(*i));
    }
}

void CGame::AwaitingFrameSync ()
{
    float MaxFps = 60.f;
    m_Elapsed = m_Clock.getElapsedTime ().asMilliseconds () - m_LastRenderingTime;
    m_LastRenderingTime = m_Clock.getElapsedTime ().asMilliseconds ();
    while (static_cast<float> (m_Elapsed) < 1000.f / MaxFps)
    {
        m_CurEventElapsed = m_Clock.getElapsedTime ().asMilliseconds () - m_LastEventHandlingTime;
        m_LastEventHandlingTime = m_Clock.getElapsedTime ().asMilliseconds ();
        ProcessKeyboardEvents (m_CurEventElapsed, m_Clock.getElapsedTime ().asMilliseconds ());
        ProcessBulletsFlying (m_CurEventElapsed);
        CheckCollisions ();
        DeleteBullets ();
        UpdateGameEndConditions ();
        sf::sleep (sf::milliseconds (1));
        m_Elapsed = m_Clock.getElapsedTime ().asMilliseconds () - m_LastRenderingTime;
    }
}

void CGame::ProcessKeyboardEvents (unsigned int elapsed, unsigned int Now)
{
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))
        m_pPlayer1->MoveUp (elapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))
        m_pPlayer1->MoveDown (elapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))
        m_pPlayer1->MoveRight (elapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))
        m_pPlayer1->MoveLeft (elapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space))
        m_pPlayer1->Shoot (&m_vpBullets, &m_vpSprites, Now);
}

void CGame::CheckCollisions ()
{
    // Check, if Bullets has reached screen borders
    vector<CBullet*>::iterator i;
    for (i = m_vpBullets.begin (); i < m_vpBullets.end (); i++)
    {
        if (((*i)->GetPos ().x < -100.f) ||
            ((*i)->GetPos ().x > static_cast<float> (m_pWindow->getSize ().x) + 100.f) ||
            ((*i)->GetPos ().y < -100.f) ||
            ((*i)->GetPos ().y > static_cast<float> (m_pWindow->getSize ().y) + 100.f))
        {
            m_vpBulletsToDelete.push_back (*i);
            m_vpBullets.erase (i);
        }
    }

    // Check, if player has reached screen borders
    if (m_pPlayer1->GetPos ().x < 0.f)
        m_pPlayer1->SetPos (0.f, m_pPlayer1->GetPos ().y);
    if (m_pPlayer1->GetPos ().y < 0.f)
        m_pPlayer1->SetPos (m_pPlayer1->GetPos ().x, 0.f);
    if (m_pPlayer1->GetPos ().x > static_cast<float> (m_pWindow->getSize ().x))
        m_pPlayer1->SetPos (static_cast<float> (m_pWindow->getSize ().x), m_pPlayer1->GetPos ().y);
    if (m_pPlayer1->GetPos ().y > static_cast<float> (m_pWindow->getSize ().y))
        m_pPlayer1->SetPos (m_pPlayer1->GetPos ().x, static_cast<float> (m_pWindow->getSize ().y));

    if (m_pPlayer2->GetPos ().x < 0.f)
        m_pPlayer2->SetPos (0.f, m_pPlayer2->GetPos ().y);
    if (m_pPlayer2->GetPos ().y < 0.f)
        m_pPlayer2->SetPos (m_pPlayer2->GetPos ().x, 0.f);
    if (m_pPlayer2->GetPos ().x > static_cast<float> (m_pWindow->getSize ().x))
        m_pPlayer2->SetPos (static_cast<float> (m_pWindow->getSize ().x), m_pPlayer2->GetPos ().y);
    if (m_pPlayer2->GetPos ().y > static_cast<float> (m_pWindow->getSize ().y))
        m_pPlayer2->SetPos (m_pPlayer2->GetPos ().x, static_cast<float> (m_pWindow->getSize ().y));

    // Player vs Player Collisions

    // Player vs Bullet Collisions
    /*float Player1Direction = m_pPlayer1->GetDirection ();
    sf::Vector2<float> Player1Pos = m_pPlayer1->GetPos ();
    Player1Pos.x += 42.4264f * cos (DEG_TO_RAD (Player1Direction - 135.f));
    Player1Pos.y += 42.4264f * sin (DEG_TO_RAD (Player1Direction - 135.f));
    for (i = m_vpBullets.begin (); i < m_vpBullets.end (); i++)
    {
        bool HasBulletHit = false;
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 60; k++)
            {
                Player1Pos.x += cos (DEG_TO_RAD (Player1Direction));
                Player1Pos.y += sin (DEG_TO_RAD (Player1Direction));
                if ((*i)->CheckCollision (Player1Pos))
                    HasBulletHit = true;
            }
            Player1Direction += 90.f;
        }
        if (HasBulletHit)
        {
            m_pPlayer1->TakeDamage ((*i)->GetDamage (), (*i)->GetShootersName ());
            m_vpBulletsToDelete.push_back (*i);
            m_vpBullets.erase (i);
        }
    }

    float Player2Direction = m_pPlayer2->GetDirection ();
    sf::Vector2<float> Player2Pos = m_pPlayer2->GetPos ();
    Player2Pos.x += 42.4264f * cos (DEG_TO_RAD (Player2Direction - 135.f));
    Player2Pos.y += 42.4264f * sin (DEG_TO_RAD (Player2Direction - 135.f));
    for (i = m_vpBullets.begin (); i < m_vpBullets.end (); i++)
    {
        bool HasBulletHit = false;
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 60; k++)
            {
                Player2Pos.x += 1.f * cos (DEG_TO_RAD (Player2Direction));
                Player2Pos.y += 1.f * sin (DEG_TO_RAD (Player2Direction));
                if ((*i)->CheckCollision (Player2Pos))
                    HasBulletHit = true;
            }
            Player2Direction += 90.f;
        }
        if (HasBulletHit)
        {
            m_pPlayer2->TakeDamage ((*i)->GetDamage (), (*i)->GetShootersName ());
            m_vpBulletsToDelete.push_back (*i);
            m_vpBullets.erase (i);
        }
    }*/
}

void CGame::ProcessBulletsFlying (unsigned int elapsed)
{
    vector<CBullet*>::iterator i;
    for (i = m_vpBullets.begin (); i < m_vpBullets.end (); i++)
    {
        (*i)->Fly (elapsed);
    }
}

void CGame::LoadTextures ()
{
    pair<string, sf::Texture> Texture;
    sf::Texture Textures[7];
    Textures[0].loadFromFile ("Graphics/Background.bmp");
    Textures[1].loadFromFile ("Graphics/Player.bmp");
    Textures[2].loadFromFile ("Graphics/PlayerWithoutArmor.bmp");
    Textures[3].loadFromFile ("Graphics/BulletShotgun.bmp");
    Textures[4].loadFromFile ("Graphics/BulletBigFuckingGun.bmp");
    Textures[5].loadFromFile ("Graphics/BulletRocketLauncher.bmp");
    Textures[6].loadFromFile ("Graphics/GameOver.bmp");
    Texture = make_pair ("Background", Textures[0]);
    m_Textures.insert (Texture);
    Texture = make_pair ("Player", Textures[1]);
    m_Textures.insert (Texture);
    Texture = make_pair ("PlayerWithoutArmor", Textures[2]);
    m_Textures.insert (Texture);
    Texture = make_pair ("BulletShotgun", Textures[3]);
    m_Textures.insert (Texture);
    Texture = make_pair ("BulletBigFuckingGun", Textures[4]);
    m_Textures.insert (Texture);
    Texture = make_pair ("BulletRocketLauncher", Textures[5]);
    m_Textures.insert (Texture);
    Texture = make_pair ("GameOver", Textures[6]);
    m_Textures.insert (Texture);
}

void CGame::LoadSprites ()
{
    sf::Sprite *pSprites = new sf::Sprite [3] ();
    pSprites[0].setTexture (m_Textures["Background"]);
    m_vpSprites.push_back (&pSprites[0]);
    pSprites[1].setTexture (m_Textures["Player"]);
    m_vpSprites.push_back (&pSprites[1]);
    pSprites[2].setTexture (m_Textures["Player"]);
    m_vpSprites.push_back (&pSprites[2]);
    m_pGameOverSprite = new sf::Sprite ();
    m_pGameOverSprite->setTexture (m_Textures["GameOver"]);
}

void CGame::DeleteBullets ()
{
    vector<CBullet*>::iterator i;
    for (i = m_vpBulletsToDelete.begin (); i < m_vpBulletsToDelete.end (); i++)
    {
        if ((*i) != nullptr)
        {
            (*i)->Delete (&m_vpSprites);
            delete (*i);
            *i = nullptr;
            m_vpBulletsToDelete.erase (i);
        }
    }
}

void CGame::UpdateGameEndConditions ()
{
    if (m_pPlayer1->IsWithoutArmor ())
    {
        cout << m_pPlayer2->GetName () << " has won" << endl;
        m_bRun = false;
    }
    else if (m_pPlayer2->IsWithoutArmor ())
    {
        cout << m_pPlayer1->GetName () << " has won" << endl;
        m_bRun = false;
    }
}

void CGame::SelectWeapons ()
{
    unsigned int Choice = 0;
    m_pWeapon2 = new CShotgun ();
    m_pWeapon2->Init (&m_Textures[m_pWeapon2->GetBulletTextureName ()]);

    // Weapon 1
    cout << "[1] Big Fucking Gun" << endl;
    cout << "[2] Shotgun" << endl;
    cout << "[3] Rocket Launcher" << endl;
    cout << "Choose your weapon" << endl;
    cin >> Choice;

    switch (Choice)
    {
        case 1:
        {
            m_pWeapon1 = new CBigFuckingGun ();
            m_pWeapon1->Init (&m_Textures[m_pWeapon1->GetBulletTextureName ()]);
        } break;

        case 2:
        {
            m_pWeapon1 = new CShotgun ();
            m_pWeapon1->Init (&m_Textures[m_pWeapon1->GetBulletTextureName ()]);
        } break;

        case 3:
        {
            m_pWeapon1 = new CRocketLauncher;
            m_pWeapon1->Init (&m_Textures[m_pWeapon1->GetBulletTextureName ()]);
        } break;

        default:
        {
            cout << "Invalid value. Weapon is set to default." << endl;
            m_pWeapon1 = new CBigFuckingGun;
            m_pWeapon1->Init (&m_Textures[m_pWeapon1->GetBulletTextureName ()]);
        }

    }
    cout << "----------------------" << endl;
}
