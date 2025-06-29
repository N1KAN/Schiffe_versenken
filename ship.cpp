#include "ship.h"
#include <stdexcept>
#include "random.h"
#include <iostream>
Ship::Ship(){

}
Ship::Ship(int row, int col, int lengthOfShip, Direction direction) {

    //Überprüfen, ob sich das Schiff im Spielfeld befindet
    do {
        outOfRange = false;
        if (direction == Direction::north && (row - lengthOfShip) >= 0) {
            break;
        } else if (direction == Direction::east && (col + lengthOfShip) <= 9) {
            break;
        } else if (direction == Direction::south && (row + lengthOfShip) <= 9) {
            break;
        } else if (direction == Direction::west && (col - lengthOfShip) >= 0) {
            break;
        }
        else {
            direction = Direction(getRandom(0,3));
            col = getRandom(0, 9);
            row = getRandom(0, 9);
            outOfRange = true;
        }
    } while (outOfRange);

    //Schiff platzieren
    for(int i = 0; i<lengthOfShip; i++){
        if(direction == Direction::north){
            m_parts.push_back(Part(row-i, col));
        }
        else if(direction == Direction::east){
            m_parts.push_back(Part(row, col+i));
        }
        else if(direction == Direction::south){
            m_parts.push_back(Part(row+i,col));
        }
        else if(direction == Direction::west){
            m_parts.push_back(Part(row, col-i));
        }
    }

}
bool Ship::hasPartIn(int row, int col){
        for (int i = 0; i < m_parts.size(); ++i) {
        if (m_parts.at(i).getRow() == row && m_parts.at(i).getCol() == col) {
                // Teil an der gegebenen Position gefunden
                return true;
            }
        }
        // Kein Teil an der gegebenen Position gefunden
        return false;
    }


Part& Ship::getPartIn(int row, int col){
        for (int i = 0; i < m_parts.size(); ++i) {
            if (m_parts.at(i).getRow() == row && m_parts.at(i).getCol() == col) {
                m_parts.at(i).setDamaged();
                // Referenz auf das Schiffsteil an der angegebenen Position zurückgeben
                return m_parts.at(i);
            }
        }
        throw std::invalid_argument("Error");
}

bool Ship::isDamaged() {
    for (int i = 0; i < m_parts.size(); ++i) {
        if (m_parts.at(i).isDamaged()) {
            // Das Schiff ist beschädigt, wenn mindestens ein Teil beschädigt ist
            return true;
        }
    }
    // Das Schiff ist nicht beschädigt, wenn kein Teil beschädigt ist
    return false;
}


bool Ship::isSunk() {
    for (int i = 0; i < m_parts.size(); i++) {
        // Das Schiff ist nicht versenkt, wenn mindestens ein Teil nicht beschädigt ist
        if (!m_parts.at(i).isDamaged()) {
            return false;
        }
    }
    // Das Schiff ist versenkt, wenn alle Teile beschädigt sind
    return true;
}




