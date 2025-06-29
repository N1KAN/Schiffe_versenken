#include "battleship.h"
#include "random.h"
#include <iostream>

Battleship::Battleship(const string& player1Name, const string& player2Name) : m_players{Player(player1Name), Player(player2Name)}{
    play();
}
void Battleship::play(){

    do {
        GameBoard gameboardP1;
        GameBoard gameboardP2;
        m_boards.at(0) = gameboardP1;
        m_boards.at(1) = gameboardP2;
        cointoss = getRandom(0, m_players.size() - 1);
        std::cout<<m_players.at(cointoss).getName()<<" fängt an..."<<std::endl;

            while(!(m_boards.at(0).allShipsSunk() || m_boards.at(1).allShipsSunk())) {
            m_boards.at(cointoss).printBoard(); //Eigenes Board mit Schiffen
            m_boards.at(cointoss).printEnemyBoard(); //Schmierzettel -> Board vom Gegner
            do {
                error = false;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "Geben Sie die Koordinaten ein" << std::endl;

                // Benutzer nach Koordinaten fragen
                if (!(std::cin >> x >> y)) {
                    // Fehlerbehandlung: Eingabe war keine Zahl
                    std::cin.clear(); // Fehlerzustand zurücksetzen

                    // Hier wird die Eingabe bis zum Zeilenumbruch verworfen
                    while (std::cin.get() != '\n') continue;

                    error = true;
                    std::cout << "Ungültige Eingabe. Bitte geben Sie gültige Koordinaten ein." << std::endl;
                            std::cout << std::endl;
                } else {
                    x--; // Koordinaten anpassen
                    y--;

                    if (x < 0 || x > 9 || y < 0 || y > 9) {
                        error = true; // Koordinaten sind ungültig
                        std::cout << "Ungültige Eingabe. Bitte geben Sie Koordinaten im Bereich von 1 bis 10 ein." << std::endl;
                                std::cout << std::endl;
                    }
                }
            } while (error);

            if(cointoss == 0){
                m_boards.at(0).mark(x, y, m_boards.at(1).hit(x,y));
                cointoss ++;
            }
            else if(cointoss == 1){
                m_boards.at(1).mark(x, y, m_boards.at(0).hit(x,y));
                cointoss --;
            }
        }
        //Prüfen welcher Spieler gewonnen hat
        if(m_boards.at(0).allShipsSunk()){
            m_players.at(0).addGameLost();
            m_players.at(1).addGameWon();
            std::cout<<m_players.at(1).getName()<<" hat gewonnen"<<std::endl;
        }
        else if(m_boards.at(1).allShipsSunk()){
            m_players.at(1).addGameLost();
            m_players.at(0).addGameWon();
            std::cout<<m_players.at(1).getName()<<" hat gewonnen"<<std::endl;
        }
        //Ausgabe der Spieler Statistiken
        for(int i = 0; i<m_players.size(); i++){
            std::cout<<m_players.at(i).getName()<<std::endl;
            std::cout<<"Gewonnen Spiele: "<<m_players.at(i).getGamesWon()<<std::endl;
            std::cout<<"Verlorene Spiele: "<<m_players.at(i).getGamesLost()<<std::endl;
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"Anzahl der Spiele: "<<m_players.at(0).getGamesPlayed()<<std::endl;
        std::cout<<std::endl;

        //Eingabe, ob der Spieler weiter spielen möchte
        do {
            std::cout<<"Wollen Sie nochmal spielen?"<<std::endl;
            std::cout<<"y für Ja"<<std::endl;
            std::cout<<"n für Nein"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"Eingabe: ";
            std::cin>>contin;

            if(contin != 'y' && contin != 'n'){
                std::cout<<"Falsche Eingabe. Versuchen Sie es erneut...."<<std::endl;
            }
        }while(contin != 'y' && contin != 'n');
    }while(contin == 'y');

    std::cout<<"Spiel wird beendet..."<<std::endl;
}
