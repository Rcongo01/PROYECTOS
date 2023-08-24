#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace std;

void LimpiarPantalla();
void Configuracion();
void JugarPartida();
void MostrarEstadisticas();
bool ComprobarCasillas();
void MostrarTablero(bool mostrarBombas);
int DescubrirCasilla();
void LlenarTablero();
void VaciarSector(int y, int x);
void GuardarEstadisticas(const string& nombreUsuario, bool gano, bool cancelo, int nivel);

vector<vector<int>> tablero;
ofstream archivo;
char eleccion;
vector<int> tamTablero(2);
vector<int> posCasilla(2);
int cantMinas = 0;
int cantBanderas = 0;
bool tableroConBombas = false;
vector<vector<int>> operaciones = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

int main() {
    archivo.open("estadisticas.txt", ios::app);
    bool mostrarEstadisticas = false;
    while (true) {
        LimpiarPantalla();
        if (mostrarEstadisticas) {
            MostrarEstadisticas();
            mostrarEstadisticas = false; 
        }
        cout <<"_________________________________"<< endl;
        cout <<"                                  "<< endl;
        cout <<"       ✧✧BUSCAMINAS✧✧           "<< endl;
        cout <<"          ◝⁠(⁠⁰⁠▿⁠⁰⁠)⁠◜               "<< endl;
        cout <<"                                  "<< endl;
        cout <<"                                  "<< endl;
        cout <<"           1) Jugar               "<< endl;
        cout <<"       2) Estadisticas            "<< endl;
        cout <<"           3) Salir               "<< endl;
        cout <<"                                  "<< endl;
        cout <<"           Eleccion:              "<< endl;
        cout <<"                                  "<<endl;
        cout <<"_______________________________   "<<endl;
        cin >> eleccion;
        switch (eleccion) {
            case '1':
                Configuracion();
                JugarPartida();
                break;
            case '2':
                mostrarEstadisticas = true;
                MostrarEstadisticas();
                
                break;
            case '3':
                archivo.close(); 
                return 0;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    }
    archivo.close(); 
    return 0;
}


void LimpiarPantalla() {
    if (system("clear") == -1) {
        cout << "Error al borrar pantalla" << endl;
    }
}

void Configuracion() {
    LimpiarPantalla();
    cout << "-----CONFIGURACION------" << endl;
    string nombreUsuario;
    cout << "Ingrese su nombre de usuario: ";
    cin >> nombreUsuario;

    cout << "Seleccione el nivel de dificultad:" << endl;
    cout << "1. Facil" << endl;
    cout << "2. Medio" << endl;
    cout << "3. Dificil" << endl;
    cout <<"Eleccion:"<< endl;
    int nivel;
    cin >> nivel;

    while (cin.fail()) {
        cout << "Error. Ingresa un numero valido: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> nivel;
    }

    switch (nivel) {
        case 1:
            tamTablero[0] = 10;
            tamTablero[1] = 8;
            cantMinas = 10;
            break;
        case 2:
            tamTablero[0] = 18;
            tamTablero[1] = 14;
            cantMinas = 40;
            break;
        case 3:
            tamTablero[0] = 20;
            tamTablero[1] = 20;
            cantMinas = 99;
            break;
        default:
            cout << "Opcion invalida. Se seleccionara el nivel de dificultad facil por defecto." << endl;
            tamTablero[0] = 10;
            tamTablero[1] = 8;
            cantMinas = 10;
            break;
    }

    tablero.resize(tamTablero[0], vector<int>(tamTablero[1], -1));

    for (int i = 0; i < tamTablero[0]; i++) {
        for (int j = 0; j < tamTablero[1]; j++) {
            tablero[i][j] = -1;
        }
    }
    archivo << "Nombre de Usuario: " << nombreUsuario << endl;
}

void JugarPartida() {
    tableroConBombas = false;
    cantBanderas = cantMinas;
    bool partidaCancelada = false;
    while (ComprobarCasillas()) {
        MostrarTablero(false);
        cout << "\nBanderas disponibles: " << cantBanderas << endl;
        cout << "1) Descubrir Casilla" << endl;
        cout << "2) Marcar Casilla" << endl;
        cout << "3) Desmarcar Casilla" << endl;
        cout << "4) Cancelar Partida" << endl;
        cout << "Eleccion: ";
        cin >> eleccion;
        int retorno;
        switch (eleccion) {
            case '1':
                cout << "Ingrese la posicion de la casilla a descubrir: ";
                cin >> posCasilla[0] >> posCasilla[1];
                retorno = DescubrirCasilla();
                if (retorno == -1) {
                    GuardarEstadisticas("Nombre de Usuario", false, false, tamTablero[0]);
                    return;
                } else if (retorno == 2 && tableroConBombas) {
                    VaciarSector(posCasilla[0], posCasilla[1]);
                }
                if (!tableroConBombas) {
                    LlenarTablero();
                    tablero[posCasilla[0]][posCasilla[1]] = -1;
                    tableroConBombas = true;
                    retorno = DescubrirCasilla();
                    if (retorno == -1) {
                        GuardarEstadisticas("Nombre de Usuario", false, false, tamTablero[0]);
                        return;
                    } else if (retorno == 2 && tableroConBombas) {
                        VaciarSector(posCasilla[0], posCasilla[1]);
                    }
                }
                break;
            case '2':
                cout << "Ingrese la posicion de la casilla a marcar: ";
                cin >> posCasilla[0] >> posCasilla[1];
                if (tablero[posCasilla[0]][posCasilla[1]] == 10) {
                    tablero[posCasilla[0]][posCasilla[1]] = 1011;
                    cantBanderas--;
                } else if (tablero[posCasilla[0]][posCasilla[1]] == -1) {
                    tablero[posCasilla[0]][posCasilla[1]] = 11;
                    cantBanderas--;
                } else {
                    cout << "Casilla ya marcada." << endl;
                }
                break;
            case '3':
                cout << "Ingrese la posicion de la casilla a desmarcar: ";
                cin >> posCasilla[0] >> posCasilla[1];
                if (tablero[posCasilla[0]][posCasilla[1]] == 11) {
                    tablero[posCasilla[0]][posCasilla[1]] = -1;
                    cantBanderas++;
                } else if (tablero[posCasilla[0]][posCasilla[1]] == 1011) {
                    tablero[posCasilla[0]][posCasilla[1]] = 10;
                    cantBanderas++;
                } else {
                    cout << "Casilla no marcada." << endl;
                }
                break;
            case '4':
                partidaCancelada = true;
                GuardarEstadisticas("Nombre de Usuario", false, true, tamTablero[0]);
                return;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    }
    if (!partidaCancelada) {
        MostrarTablero(true);
        GuardarEstadisticas("Nombre de Usuario", true, false, tamTablero[0]);
        cout << "\n¡Felicidades! Has ganado el juego." << endl;
    }
}
void MostrarEstadisticas() {
    LimpiarPantalla();
    cout<<"-----ESTADISTICAS--------"<<endl;
    ifstream archivo("estadisticas.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
void GuardarEstadisticas(const string& nombreUsuario, bool gano, bool cancelo, int nivel) {
    archivo << "Resultado: " << (gano ? "Gano" : "Perdio") << endl;
    archivo << "Nivel: " << nivel << endl;
    if (cancelo) {
        archivo << "Partida Cancelada" << endl;
    }
    archivo << "--------------------------------------" << endl;
}

bool ComprobarCasillas() {
    for (int i = 0; i < tamTablero[0]; i++) {
        for (int j = 0; j < tamTablero[1]; j++) {
            if (tablero[i][j] == -1) {
                return true;
            }
        }
    }
    return false;
}
void MostrarTablero(bool mostrarBombas) {
    LimpiarPantalla();
    cout << "   ";
    for (int i = 0; i < tamTablero[1]; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
    for (int i = 0; i < tamTablero[0]; i++) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < tamTablero[1]; j++) {
            switch (tablero[i][j]) {
                case -1:
                    cout << " . ";
                    break;
                case 0:
                    cout << "   ";
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    cout << " " << tablero[i][j] << " ";
                    break;
                case 10:
                    if (mostrarBombas) {
                        cout << " # ";
                    } else {
                        cout << " . ";
                    }
                    break;
                case 1011:
                    if (mostrarBombas) {
                        cout << " # ";
                    } else {
                        cout << " F ";
                    }
                    break;
                case 11:
                    cout << " F ";
                    break;
            }
        }
        
        cout << endl;
    }
}
int DescubrirCasilla(){
    int cont = 0;
    switch(tablero[posCasilla[0]][posCasilla[1]]){
        case 11:
        case 1011:
        cout<<"Casilla marcada, no es posible descubrirla. Ingrese OK: ";
        cin>>eleccion;
        break;
        case 10:
        MostrarTablero(true);
        cout<<"\n Perdiste Ingrese OK: ";
        cin>>eleccion;
        return -1;
        break;
        case -1:
        for(int i = 0; i < 8; i++){
            if(posCasilla[0]+ operaciones[i][0] >= 0 && posCasilla[0]+ operaciones[i][0] < tamTablero[0]){
                if(posCasilla[1]+ operaciones[i][1] >= 0 && posCasilla[1]+ operaciones[i][1] < tamTablero[1]){
                    if(tablero[posCasilla[0]+operaciones[i][0]][posCasilla[1]+operaciones[i][1]] == 10 || tablero[posCasilla[0]+operaciones[i][0]][posCasilla[1]+operaciones[i][1]] == 1011){
                        cont++;
                    }
                }   
            }
        }
        tablero[posCasilla[0]][posCasilla[1]] = cont;
        return 2;
        break;
        default:
        cout<<"Esa casilla ya fue descubierta. Ingrese OK: ";
        cin>>eleccion;
        break;
    }
    return 0;
}

void LlenarTablero(){
    srand(time(NULL));
    for(int i = 0; i < cantMinas; i++){
        int x,y;
        do{
            y = rand() % tamTablero[0];
            x = rand() % tamTablero[1];
        }while(tablero[y][x] == 0 || tablero[y][x] == 10);

        tablero[y][x] = 10;
    }
}

void VaciarSector(int y,int x){
    int cont = 0;
    for(int i = 0; i < 8; i++){
        if(y + operaciones[i][0] >= 0 && y+ operaciones[i][0] < tamTablero[0]){
            if(x+ operaciones[i][1] >= 0 && x + operaciones[i][1] < tamTablero[1]){
                if(tablero[y+operaciones[i][0]][x+operaciones[i][1]] == 10 || tablero[y+operaciones[i][0]][x+operaciones[i][1]] == 1011){
                    cont++;
                }
            }   
        }
    }
    if(cont == 0){
        tablero[y][x] = 0;
        for(int i = 0; i < 8; i++){
            if(y + operaciones[i][0] >= 0 && y+ operaciones[i][0] < tamTablero[0]){
                if(x+ operaciones[i][1] >= 0 && x + operaciones[i][1] < tamTablero[1]){
                    if(tablero[y+operaciones[i][0]][x+operaciones[i][1]] == -1){
                        VaciarSector(y+operaciones[i][0],x+operaciones[i][1]);
                    }
                }
            }
        }
    }else{
        tablero[y][x] = cont;
        return;
    }
}
