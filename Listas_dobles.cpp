#include <iostream>
#include <string>
using namespace std;


struct Cancion {
    string nombre;
    string artista;
    int duracion; 
    Cancion* anterior;
    Cancion* siguiente;
};


class Playlist {
private:
    Cancion* cabeza;
    Cancion* actual;
    
public:
    Playlist() {
        cabeza = nullptr;
        actual = nullptr;
    }

    
    void agregarCancion(string nombre, string artista, int duracion) {
        Cancion* nueva = new Cancion{nombre, artista, duracion, nullptr, nullptr};
        if (!cabeza) {
            cabeza = nueva;
            actual = cabeza;
        } else {
            Cancion* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nueva;
            nueva->anterior = temp;
        }
        cout << "Cancion agregada: " << nombre << endl;
    }

    
    void mostrarPlaylist() {
        if (!cabeza) {
            cout << "La playlist esta vacia." << endl;
            return;
        }
        Cancion* temp = cabeza;
        cout << "--- Playlist ---" << endl;
        while (temp != nullptr) {
            cout << "Nombre: " << temp->nombre 
                 << ", Artista: " << temp->artista 
                 << ", Duracion: " << temp->duracion << " segundos" << endl;
            temp = temp->siguiente;
        }
        cout << "-----------------" << endl;
    }

    
    void eliminarCancion(string nombre) {
        if (!cabeza) {
            cout << "La playlist esta vacia." << endl;
            return;
        }
        Cancion* temp = cabeza;
        while (temp != nullptr && temp->nombre != nombre) {
            temp = temp->siguiente;
        }
        if (!temp) {
            cout << "Cancion no encontrada." << endl;
            return;
        }

        
        if (temp->anterior) {
            temp->anterior->siguiente = temp->siguiente;
        } else {
            cabeza = temp->siguiente; 
        }
        if (temp->siguiente) {
            temp->siguiente->anterior = temp->anterior;
        }

        delete temp;
        cout << "Cancion eliminada: " << nombre << endl;
    }

   
    void siguienteCancion() {
        if (actual && actual->siguiente) {
            actual = actual->siguiente;
            cout << "Reproduciendo: " << actual->nombre << " de " << actual->artista << endl;
        } else {
            cout << "No hay siguiente cancion." << endl;
        }
    }

    
    void anteriorCancion() {
        if (actual && actual->anterior) {
            actual = actual->anterior;
            cout << "Reproduciendo: " << actual->nombre << " de " << actual->artista << endl;
        } else {
            cout << "No hay cancion anterior." << endl;
        }
    }

    
    int contarCanciones() {
        int contador = 0;
        Cancion* temp = cabeza;
        while (temp != nullptr) {
            contador++;
            temp = temp->siguiente;
        }
        return contador;
    }
};


int main() {
    Playlist miPlaylist;
    int opcion;
    string nombre, artista;
    int duracion;

    do {
        cout << "\n--- MENU PLAYLIST ---\n";
        cout << "1. Agregar cancion\n";
        cout << "2. Mostrar playlist\n";
        cout << "3. Eliminar cancion\n";
        cout << "4. Siguiente cancion\n";
        cout << "5. Anterior cancion\n";
        cout << "6. Contar canciones\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                cout << "Nombre de la cancion: ";
                getline(cin, nombre);
                cout << "Artista: ";
                getline(cin, artista);
                cout << "Duracion (segundos): ";
                cin >> duracion;
                miPlaylist.agregarCancion(nombre, artista, duracion);
                break;
            case 2:
                miPlaylist.mostrarPlaylist();
                break;
            case 3:
                cout << "Nombre de la cancion a eliminar: ";
                getline(cin, nombre);
                miPlaylist.eliminarCancion(nombre);
                break;
            case 4:
                miPlaylist.siguienteCancion();
                break;
            case 5:
                miPlaylist.anteriorCancion();
                break;
            case 6:
                cout << "Total de canciones: " << miPlaylist.contarCanciones() << endl;
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);

    return 0;
}
