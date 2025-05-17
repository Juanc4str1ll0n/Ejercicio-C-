#include <iostream>
#include <string>
using namespace std;


struct Player {
    string name;
    Player* next;

    Player(string _name) : name(_name), next(nullptr) {}
};


class Game {
private:
    Player* current;  

public:
    Game() : current(nullptr) {}

    // Agregar jugador al final
    void addPlayer(const string& name) {
        Player* newPlayer = new Player(name);
        if (!current) {
            current = newPlayer;
            current->next = current; //<-
        } else {
            Player* temp = current;
            while (temp->next != current)
                temp = temp->next;
            temp->next = newPlayer;
            newPlayer->next = current;//<-
        }
    }


    void showPlayers() const {
        if (!current) {
            cout << "No hay jugadores.\n";
            return;
        }
        cout << "Jugadores: ";
        Player* temp = current;
        do {
            cout << temp->name << " ";
            temp = temp->next;
        } while (temp != current);
        cout << "\n";
    }

    void playTurns(int totalTurns) {
        if (!current) {
            cout << "No hay jugadores para jugar.\n";
            return;
        }
        cout << "Iniciando el juego...\n";
        for (int i = 1; i <= totalTurns; ++i) {
            cout << "Turno " << i << ": " << current->name << endl;
            current = current->next;  
        }
    }

    ~Game() {
        if (!current) return;
        Player* temp = current->next;
        while (temp != current) {
            Player* next = temp->next;//<-
            delete temp;
            temp = next;
        }
        delete current;
    }
};


int main() {
    Game game;


    game.addPlayer("Camilo");
    game.addPlayer("Castrillon");
    game.addPlayer("Jhon");
    game.addPlayer("William");
     game.addPlayer("Chiristian");

    game.showPlayers();

    game.playTurns(20);

    return 0;
}
