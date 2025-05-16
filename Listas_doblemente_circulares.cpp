#include <iostream>
#include <string>
using namespace std;

struct Tarea {
    string descripcion;
    int prioridad; 
    bool completada;
    Tarea* anterior;
    Tarea* siguiente;
};

class ListaTareas {
private:
    Tarea* cabeza;

public:
    ListaTareas() : cabeza(nullptr) {}

    
    void agregarTarea(string desc, int prioridad) {
        Tarea* nueva = new Tarea{desc, prioridad, false, nullptr, nullptr};
        
        if (!cabeza) {
            cabeza = nueva;
            cabeza->anterior = cabeza;
            cabeza->siguiente = cabeza;
        } else {
            Tarea* temp = cabeza;
            do {
                if (prioridad > temp->prioridad) break;
                temp = temp->siguiente;
            } while (temp != cabeza);

            nueva->anterior = temp->anterior;
            nueva->siguiente = temp;
            temp->anterior->siguiente = nueva;
            temp->anterior = nueva;

            if (temp == cabeza && prioridad > cabeza->prioridad) {
                cabeza = nueva;
            }
        }
        cout << "Tarea agregada: \"" << desc << "\" (Prioridad " << prioridad << ")" << endl;
    }

    
    void mostrarTareas() {
        if (!cabeza) {
            cout << "No hay tareas pendientes." << endl;
            return;
        }

        cout << "\n--- Tareas Pendientes ---" << endl;
        Tarea* temp = cabeza;
        do {
            string estado = temp->completada ? "✓" : "✗";
            cout << "[" << estado << "] " << temp->descripcion 
                 << " (Prioridad: " << temp->prioridad << ")" << endl;
            temp = temp->siguiente;
        } while (temp != cabeza);
        cout << "-------------------------" << endl;
    }

    
    void completarTarea(string desc) {
        if (!cabeza) return;

        Tarea* temp = cabeza;
        do {
            if (temp->descripcion == desc) {
                temp->completada = true;
                cout << "Tarea completada: \"" << desc << "\"" << endl;
                return;
            }
            temp = temp->siguiente;
        } while (temp != cabeza);

        cout << "Tarea no encontrada." << endl;
    }

    
    void navegarTareas() {
        if (!cabeza) {
            cout << "No hay tareas para navegar." << endl;
            return;
        }

        Tarea* actual = cabeza;
        int opcion;
        do {
            cout << "\nTarea actual: \"" << actual->descripcion << "\" (Prioridad " 
                 << actual->prioridad << ")" << endl;
            cout << "1. Siguiente tarea\n2. Tarea anterior\n3. Salir\nOpcion: ";
            cin >> opcion;

            if (opcion == 1) actual = actual->siguiente;
            else if (opcion == 2) actual = actual->anterior;
        } while (opcion != 3);
    }
};

int main() {
    ListaTareas lista;
    int opcion, prioridad;
    string descripcion;

    do {
        cout << "\n--- MENU DE TAREAS ---" << endl;
        cout << "1. Agregar tarea\n2. Mostrar tareas\n3. Completar tarea\n4. Navegar tareas\n0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Descripcion: ";
                getline(cin, descripcion);
                cout << "Prioridad (1-5): ";
                cin >> prioridad;
                lista.agregarTarea(descripcion, prioridad);
                break;
            case 2:
                lista.mostrarTareas();
                break;
            case 3:
                cout << "Tarea a completar: ";
                getline(cin, descripcion);
                lista.completarTarea(descripcion);
                break;
            case 4:
                lista.navegarTareas();
                break;
            case 0:
                cout << "¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}