#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "battleship.h"

int main()
{
    std::string name1, name2;
    cout<<"Spieler 1: Geben Sie ihren Namen ein"<<endl;
    cin>>name1;
    cout<<endl;
    cout<<"Spieler 2: Geben Sie ihren Namen ein"<<endl;
    cin>>name2;
    cout<<endl;
    Battleship battleship(name1, name2);


    return 0;
}
