#include "gameboard.h"
#include <iostream>
#include "random.h"
GameBoard::GameBoard(){
    //Gameboard initialisieren
    randomPlaceShips();
    for(int i = 0; i<m_ownBoard.size(); i++){
        for(int j = 0; j<m_ownBoard.size(); j++){
            m_ownBoard.at(i).at(j) = '.';
            for(int k = 0; k<m_ships.size(); k++){
                if(m_ships.at(k).hasPartIn(i,j)){
                    if(k==0) {
                        m_ownBoard.at(i).at(j) = '5';
                    }
                    else if(k==1 || k==2){
                        m_ownBoard.at(i).at(j) = '4';
                    }
                    else if(k==3 || k==4 || k==5){
                        m_ownBoard.at(i).at(j) = '3';
                    }
                    else if(k==6 || k==7 || k==8|| k==9){
                        m_ownBoard.at(i).at(j) = '2';
                    }
                    break;
                }
            }
        }
    }

    //Schmierzettel initialisieren
    for (int i = 0; i < m_enemyBoard.size(); i++) {
        for(int j = 0; j < m_enemyBoard.size(); j++){
            m_enemyBoard.at(i).at(j) = '.';
        }
    }

}


void GameBoard::printBoard(){
    //Ganzes Gameboard mit * initialisieren
    for(int i = 0; i<m_ownBoard.size(); i++){
        //Spalte
        if(i+1<m_enemyBoard.size()) {
            std::cout<<"0"<<i+1<<"|";
        }
        else {
            std::cout<<i+1<<"|";
        }
        for(int j = 0; j<m_ownBoard.size(); j++){
            std::cout<<m_ownBoard.at(i).at(j);
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }

    for(int i = 0; i<m_ownBoard.size()+1; i++) {
        if(i == 0) {
            std::cout<<"   ";
        }
        else {
            std::cout<<"--";
        }
    }
    std::cout<<std::endl;
    for(int i = 0; i<m_ownBoard.size()+1; i++) {
        if(i == 0) {
            std::cout<<"   ";
        }
        else if (i>9){
            std::cout<<i;
        }
        else {
            std::cout<<i<<" ";
        }
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
}

void GameBoard::printEnemyBoard(){ //Schmierzettel

    for(int i = 0; i<m_enemyBoard.size(); i++){
        //Spalte
        if(i+1<m_enemyBoard.size()) {
            std::cout<<"0"<<i+1<<"|";
        }
        else {
            std::cout<<i+1<<"|";
        }
        for(int j = 0; j<m_enemyBoard.size(); j++){

            std::cout<<m_enemyBoard.at(i).at(j);
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }
    for(int i = 0; i<m_enemyBoard.size()+1; i++) {
        if(i == 0) {
            std::cout<<"   ";
        }
        else {
            std::cout<<"--";
        }
    }
    std::cout<<std::endl;
    for(int i = 0; i<m_enemyBoard.size()+1; i++) {
        if(i == 0) {
            std::cout<<"   ";
        }
        else if (i>9){
            std::cout<<i;
        }
        else {
            std::cout<<i<<" ";
        }
    }

}

bool GameBoard::hit(int row, int col){
    if(m_ownBoard.at(row).at(col) == '.' || m_ownBoard.at(row).at(col) == 'O'){
        m_ownBoard.at(row).at(col) = 'O';
        return false;
    }
    else {
        //Prüfen welches Schiff getroffen wurde
        for(int i = 0; i<m_ships.size(); i++){
            if(m_ships.at(i).hasPartIn(row , col)){
                m_ships.at(i).getPartIn(row, col); //Schiffsteil auf setdamaged setzen
                //Prüfen ob Schiff versenkt wurde
                if(m_ships.at(i).isSunk()){

                    //Durch das Spielfeld durchgehen und alle Teile finden die zum Schiff gehören
                    for(int j = 0; j < m_ownBoard.size(); j++){
                        for(int k = 0; k < m_ownBoard.size(); k++){
                            //Schiffsteile auf versenkt setzen S
                            if(m_ships.at(i).hasPartIn(j, k)){
                                m_ownBoard.at(j).at(k) = 'S';
                            }
                        }
                    }
                }
                else {
                    m_ownBoard.at(row).at(col) = 'X';
                }
            }
        }
        return true;
    }
}

void GameBoard::mark(int row, int col, bool wasHit){
    if(wasHit){
        m_enemyBoard.at(row).at(col) = 'X';
    }
    else{
        m_enemyBoard.at(row).at(col) = 'O';
    }

}

void GameBoard::randomPlaceShips(){
    bool overlap;
    int length;

    //   The following ships shall be placed:
    //   - 1 'Dreadnought' with 5 parts
    //   - 2 'Cruisers' with 4 parts
    //   - 3 'Destroyers' with 3 parts
    //   - 4 'Submarines' with 2 parts
    Ship dreadnought(getRandom(0, 9), getRandom(0, 9), 5, Direction(getRandom(0, 3)));

    Ship cruisers1(getRandom(0, 9), getRandom(0, 9), 4, Direction(getRandom(0, 3)));
    Ship cruiser2(getRandom(0, 9), getRandom(0, 9), 4, Direction(getRandom(0, 3)));

    Ship destroyer1(getRandom(0, 9), getRandom(0, 9), 3, Direction(getRandom(0, 3)));
    Ship destroyer2(getRandom(0, 9), getRandom(0, 9), 3, Direction(getRandom(0, 3)));
    Ship destroyer3(getRandom(0, 9), getRandom(0, 9), 3, Direction(getRandom(0, 3)));

    Ship submarine1(getRandom(0, 9), getRandom(0, 9), 2, Direction(getRandom(0, 3)));
    Ship submarine2(getRandom(0, 9), getRandom(0, 9), 2, Direction(getRandom(0, 3)));
    Ship submarine3(getRandom(0, 9), getRandom(0, 9), 2, Direction(getRandom(0, 3)));
    Ship submarine4(getRandom(0, 9), getRandom(0, 9), 2, Direction(getRandom(0, 3)));


    m_ships.at(0) = dreadnought;
    m_ships.at(1) = cruisers1;
    m_ships.at(2) = cruiser2;
    m_ships.at(3) = destroyer1;
    m_ships.at(4) = destroyer2;
    m_ships.at(5) = destroyer3;
    m_ships.at(6) = submarine1;
    m_ships.at(7) = submarine2;
    m_ships.at(8) = submarine3;
    m_ships.at(9) = submarine4;
    do {
        overlap = false;
        for(int i = 1; i<m_ships.size(); i++){
            for(int j = 0; j<m_ships.size(); j++){
                if(i == j){
                    continue;
                }
                //Durch das Spielfeld gehen um zu prüfen ob es Überlappungen gibt
                for(int k = 0; k<m_enemyBoard.size(); k++){
                    for(int l = 0; l<m_enemyBoard.size(); l++){
                        if(m_ships.at(i).hasPartIn(k, l) && m_ships.at(j).hasPartIn(k, l)){
                            if(i==0) {
                                length = 5;
                            }
                            else if(i==1 || i==2){
                                length = 4;
                            }
                            else if(i==3 || i==4 || i==5){
                                length = 3;
                            }
                            else if(i==6 || i==7 || i==8|| i==9){
                                length = 2;
                            }
                            m_ships.at(i) = Ship(getRandom(0, 9), getRandom(0, 9), length, Direction(getRandom(0, 3)));
                            overlap = true;
                            break;
                        }
                    }
                }
            }
        }
    }while(overlap);

}

bool GameBoard::allShipsSunk(){
    //Prüfen ob alle Schiffe versenkt wurden
    for(int i = 0; i<m_ships.size(); i++){
        if(!m_ships.at(i).isSunk()){
            return false;
        }
    }
    return true;
}
