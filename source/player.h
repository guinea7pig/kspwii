/**
 * @file player.h
 * Contains the Player class.
 */

#ifndef PlayerH
#define PlayerH
//---------------------------------------------------------------------------

#include <gctypes.h>
#include <string>

/**
 * Types of player.
 */
enum class playerType : u8 {
    Human, /**< Identify a human player. */
    CPU    /**< Identify a computer player. */
};

/**
 * This class is used to managed players.
 * @author Crayon
 */
class Player
{
public:
    /**
     * Constructor for the Player class.
     */ 
    Player() = default;
    Player(Player const&) = delete;
    ~Player() = default;
    Player& operator=(Player const&) = delete;
    void SetName(const std::string &AName);
    [[nodiscard]] std::string GetName();
    void SetSign(u8 ASign);
    [[nodiscard]] u8 GetSign();
    [[nodiscard]] u16 GetScore();
    void IncScore();
    void ResetScore();
    void SetType(playerType AType);
    [[nodiscard]] playerType GetType();
private:
    u16 Score{0};
    std::string Name{};
    u8 Sign{0};
    playerType Type{playerType::Human};
};
//---------------------------------------------------------------------------
#endif
