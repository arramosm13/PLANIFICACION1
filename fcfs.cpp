#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Proceso {
    string id;
    int llegada;
    int servicio;
    int comienzo;
    int finalizacion;
    int espera;
    int estancia;
    double estanciaNormalizada;
};

int main() {
    int n;
    cout << "=== SIMULADOR DE PLANIFICACIÓN FCFS ===" << endl;
    do {
        cout << "Ingrese el número de procesos (entre 3 y 5): ";
        cin >> n;
    } while (n < 3 || n > 5);

    vector<Proceso> procesos(n);

    for (int i = 0; i < n; ++i) {
        cout << "\n--- Proceso " << (i + 1) << " ---" << endl;
        cout << "ID del proceso: ";
        cin >> procesos[i].id;
        
        do {
            cout << "Tiempo de llegada (>= 0): ";
            cin >> procesos[i].llegada;
        } while (procesos[i].llegada < 0);

        do {
            cout << "Tiempo de servicio (> 0): ";
            cin >> procesos[i].servicio;
        } while (procesos[i].servicio <= 0);
    }

    stable_sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
        return a.llegada < b.llegada;
    });

    int tiempoActual = 0;
    double sumaEspera = 0;
    double sumaEstancia = 0;

    for (int i = 0; i < n; ++i) {
        if (tiempoActual < procesos[i].llegada) {
            tiempoActual = procesos[i].llegada; 
        }

        procesos[i].comienzo = tiempoActual;
        procesos[i].finalizacion = procesos[i].comienzo + procesos[i].servicio;
        procesos[i].espera = procesos[i].comienzo - procesos[i].llegada;
        procesos[i].estancia = procesos[i].finalizacion - procesos[i].llegada;
        procesos[i].estanciaNormalizada = static_cast<double>(procesos[i].estancia) / procesos[i].servicio;

        tiempoActual = procesos[i].finalizacion;

        sumaEspera += procesos[i].espera;
        sumaEstancia += procesos[i].estancia;
    }

    cout << "\n" << string(70, '=') << endl;
    cout << left << setw(10) << "Proceso"
         << setw(8) << "TL"
         << setw(8) << "Ts"
         << setw(8) << "TC"
         << setw(8) << "TF"
         << setw(8) << "TE"
         << setw(8) << "Tr"
         << setw(10) << "Tr/Ts" << endl;
    cout << string(70, '-') << endl;

    cout << fixed << setprecision(2);
    for (const auto& p : procesos) {
        cout << left << setw(10) << p.id
             << setw(8) << p.llegada
             << setw(8) << p.servicio
             << setw(8) << p.comienzo
             << setw(8) << p.finalizacion
             << setw(8) << p.espera
             << setw(8) << p.estancia
             << setw(10) << p.estanciaNormalizada << endl;
    }
    cout << string(70, '=') << endl;

    cout << "Tiempo de espera promedio (TE promedio): " << (sumaEspera / n) << endl;
    cout << "Tiempo de estancia promedio (Tr promedio): " << (sumaEstancia / n) << endl;

    return 0;
}
