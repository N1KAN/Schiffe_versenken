#include "player.h"

Player::Player(const string& playerName):m_playerName(playerName), m_gamesWon(0), m_gamesLost(0){
}
string Player::getName() {
    return m_playerName;
}
int Player::getGamesWon() const{
    return m_gamesWon;
}
int Player::getGamesLost() const{
    return m_gamesLost;
}

void Player::addGameWon(){
    m_gamesWon+=1;
}

void Player::addGameLost(){
    m_gamesLost+=1;
}

int Player::getGamesPlayed()const{
    return getGamesLost() + getGamesWon();
}
