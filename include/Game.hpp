#ifndef GAME_HPP
#define GAME_HPP

//#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class CGame
{
    public:
        CGame ();
        void Run ();
        ~CGame ();

    private:
        sf::RenderWindow *m_pWindow;
        vector<sf::Sprite*> m_vpSprites;
        map<string, sf::Texture> m_Textures;
        vector<CBullet*> m_vpBullets;
        vector<CBullet*> m_vpBulletsToDelete;
        CPlayer *m_pPlayer1;
        CPlayer *m_pPlayer2;
        CWeapon *m_pWeapon1;
        CWeapon *m_pWeapon2;
        sf::Clock m_Clock;
        sf::Sprite* m_pGameOverSprite;
        bool m_bRun;
        unsigned int m_Elapsed;
        unsigned int m_LastRenderingTime;
        unsigned int m_CurEventElapsed;
        unsigned int m_LastEventHandlingTime;
        void RenderSprites ();
        void AwaitingFrameSync ();
        void ProcessKeyboardEvents (unsigned int elapsed, unsigned int Now);
        void CheckCollisions ();
        void ProcessBulletsFlying (unsigned int elapsed);
        void LoadTextures ();
        void LoadSprites ();
        void DeleteBullets ();
        void UpdateGameEndConditions ();
        void SelectWeapons ();
};

#endif
