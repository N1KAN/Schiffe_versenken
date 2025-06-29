#include "part.h"

Part::Part(int row, int col):m_row(row),m_col(col){
    m_status = false;
}

//Positionen
int Part::getRow() const{
    return m_row;
}

int Part::getCol() const{
    return m_col;
}

bool Part::isDamaged() const{
    return m_status;
}

void Part::setDamaged(){
    m_status = true;
}
