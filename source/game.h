/**
 * @file game.h
 * Contains the Game class.
 */

#ifndef GameH
#define GameH
//---------------------------------------------------------------------------

#include <array>
#include <string>
#include <memory>
#include "cursor.h"
#include "player.h"
#include "button.h"
#include "symbol.h"

// Forward declarations
class Grid;
class Language;
class Audio;
struct GRRLIB_Font;

/**
 * This is the main class of this project. This is where the magic happens.
 * @author Crayon
 */
class Game
{
public:
    Game(u16 GameScreenWidth, u16 GameScreenHeight);
    Game(Game const&) = delete;
    ~Game();
    Game& operator=(Game const&) = delete;
    void Paint();
    bool ControllerManager();
private:
    /**
     * Types of game.
     */
    enum class gameMode : u8 {
        VsAI,       /**< Play vs AI. */
        VsHuman1,   /**< Play vs a human with 1 Wii Remote. */
        VsHuman2    /**< Play vs a human with 2 Wii Remote. */
    };

    /**
     * Types of screen available in the game.
     */
    enum class gameScreen : u8 {
        Start,  /**< Start screen. */
        Game,   /**< Game screen. */
        Home,   /**< Home screen. */
        Menu    /**< Menu screen. */
    };

    void StartScreen();
    void MenuScreen(bool CopyScreen);
    void GameScreen(bool CopyScreen);
    void ExitScreen();
    void Clear();
    void TurnIsOver();
    void NewGame();
    void PrintWrapText(u16 x, u16 y, u16 maxLineWidth, const std::string &input,
        u32 fontSize, u32 TextColor, u32 ShadowColor, s8 OffsetX, s8 OffsetY);
    void ChangeScreen(gameScreen NewScreen, bool PlaySound = true);
    void ButtonOn(s8 NewFocusedButton);
    bool SelectZone();
    void ChangeCursor();
    void CalculateFrameRate();

    std::array<Cursor, 4> Hand;
    s8 HandX{0};
    s8 HandY{0};

    bool CurrentPlayer{false};
    bool PlayerToStart{false};
    std::array<Player, 2> WTTPlayer;
    gameScreen CurrentScreen{};
    gameScreen LastScreen{};
    s8 FocusedButton{-1};
    std::string text{};

    u16 TieGame{0};
    bool RoundFinished{false};
    u8 FPS{0};
    bool ShowFPS{false};

    std::array<Button *, 3> ExitButton;
    std::array<Button *, 3> MenuButton;
    Grid *GameGrid{nullptr};
    Language *Lang{nullptr};
    std::array<std::array<Symbol, 3>, 3> GridSign;
    std::unique_ptr<Audio> GameAudio;

    std::unique_ptr<Texture> GameImg; /**< Background texture for the game. */
    std::unique_ptr<Texture> GameHoverImg; /**< Hover texture for the game buttons. */
    std::unique_ptr<Texture> SplashImg; /**< Splash screen texture. */
    std::unique_ptr<Texture> SplashArmImg; /**< Arm texture for splash screen. */
    std::unique_ptr<Texture> HoverImg; /**< Texture to put over a symbol when selected. */
    std::unique_ptr<Texture> CopiedImg; /**< Texture to store a temporary copy of the screen. */
    std::unique_ptr<Texture> GameText; /**< Game text that does not changed including background. */

    bool Copied{false};

    u16 ScreenWidth{0};
    u16 ScreenHeight{0};

    u8 AIThinkLoop{0};
    gameMode GameMode{gameMode::VsHuman1};

    u8 SymbolAlpha{5};
    bool AlphaDirection{false};

    GRRLIB_Font *DefaultFont{nullptr};
};
//---------------------------------------------------------------------------
#endif
