#include <iostream>
#include <stdlib.h>
 
using namespace std;
 

#define NFILAS 8
#define NCOLUMNAS 8
int main(int argc, char* argv[])
{
    int parqueadero[8][8]={{2,0,0,5,5,0,0,2},
                           {3,0,0,0,0,0,0,3},
                           {3,0,0,0,0,0,0,3},
                           {3,0,0,0,0,0,0,3},
                           {3,0,0,0,0,0,0,3},
                           {3,0,0,0,0,0,0,3},
                           {3,0,0,0,0,0,0,3},
                           {2,3,3,4,4,3,3,2}};
                          
 
 
    
    int fila,columna,nLibres=0,nOcupadas=0,op;
    for(fila=0;fila<NFILAS;fila++)
        for(columna=0;columna<NCOLUMNAS;columna++)
            if(parqueadero[fila][columna]== 0)
                nLibres++;
                
   int horaE,horaEM,horaS,horaSM,minutosE,minutosS, tiempoM,tiempoH,valorM, tiempoT,valorP,Vtarifa ;
   int i=1;
    do{
      
        system("CLS");
        cout <<"\n**********************************************************\t "<< endl;
        cout <<"\n*                  PARQUEADERO RC                       *\t "<< endl;
        cout <<"\n*                                                       *\t "<< endl;
        cout <<"\n*                        MENU                           *\t "<< endl;
        cout <<"\n*********************************************************\t "<< endl;
        cout <<"---Parqueadero abierto desde las 6 hasta las 21 horas.---- " << endl;;
        cout<<endl;
        cout<< "____________________________________"<< endl;
        cout<< "RECUERDE REGISTAR LA TARIFA DEL DIA."<<endl;
        cout<< "____________________________________"<< endl;
        cout<<endl;
        cout << "1-Ingresar un carro al parqueadero." << endl;
        cout << "2-Dar salida a un carro del parqueadero." << endl;
        cout << "3-Consultar puestos disponibles." << endl;
        cout << "4-Consultar porcentaje de disponibilidad."<< endl;
        cout << "5-Informar los ingresos totales del parqueadero."<< endl;
        cout << "6-Cambiar la tarifa del parqueadero."<< endl;
        cout << "0-Salir" << endl;
        cout << "-------------- Seleccione una opcion ------------------- ";
        cin >> op;
 
        bool ocupado,libre;
 
        switch(op){
            case 0:
                break;
            case 1:
                if(nLibres > 0){
                    do{
                        ocupado = false;
                        cout << "Introduce el numero de la fila: ";
                        cin >> fila;
                        cout << "Introduce el numero de la columna: ";
                        cin >> columna;
                        cout<< "Digitela hora de entrada:";
 	                    cin>>horaE;
                        cout<< "Digigite los minutos de entrada:";
                         cin>>minutosE;
						if(horaE<6){
                        	cout<< "la hora ingresada no es correcta"<<endl;	
                        }
                        if(horaE>21){
                        cout<< "la hora ingresada no es correcta"<<endl;
                        }
                        
                        switch(parqueadero[fila][columna])
                        {
                            case 0:
                                parqueadero[fila][columna]=1;
                                nLibres--;
                                nOcupadas++;
                                ocupado= true;
                                cout << "Vehiculo parqueado." << endl;
                                break;
                            case 1:
                                cout << "Puesto ocupado." << endl;
                                break;
                            case 2:
                                cout << "No se puede parquear en las esquinas" << endl;
                                break;
                            case 3:
                                cout << "No se puede parquear en las paredes" << endl;
                                break;
                            case 4:
                                cout << "No se puede parquear en las entradas" << endl;
                                break;
                            case 5:
                                cout << "No se puede parquear en las salidas" << endl;
                                break;
								
								   
                            default:
                                cout << "Valor inesperado en esa posicion" << endl;
                        }
                    }while(ocupado != true);
                }else{
                    cout << "No quedan puestos libres" << endl;
                }
                
                system("PAUSE");
                break;
            case 2:
                if(nOcupadas > 0){
                    do{
                        libre = false;
                        cout << "Introduce el numero de la fila: ";
                        cin >> fila;
                        cout << "Introduce el numero de la columna: ";
                        cin >> columna;
                        if(parqueadero[fila][columna]==1){
                            parqueadero[fila][columna]=0;
                            libre=true;
                            nLibres++;
                            nOcupadas--;
                            cout << "El vehiculo se puede retirar" << endl;
                        }else{
                            cout << "La posicion indicada no esta ocupada, intentelo de nuevo" << endl;
                        }
                    }while(libre == false);
                }else{
                    cout << "No hay puestos ocupados" << endl;
                }
                
                 cout<<" Digite la hora de salida :";
                 cin>>horaS;
                 cout << "Digite los minutos de salida:";
                 cin>>minutosS;
                if(horaE<6){
                cout<< "la hora ingresada no es correcta"<<endl;	
                }
                if(horaE>21){
                cout<< "la hora ingresada no es correcta"<<endl;
                 }
                
                 tiempoH=24;
	             tiempoM=1440;
	             horaEM=horaE*60;
                 horaEM= horaEM+minutosE;
 
                  horaSM=horaS*60;
                  horaSM=horaSM+minutosS;
 
                 tiempoT=horaSM-horaEM;
 
 
                  valorP= tiempoT*Vtarifa;
 
                  cout<< "\nEl El valor a pagar es de :" <<valorP<<endl;
                 
                  cout<<"Tiempo  que estuvo el carro parquedo:"<< tiempoT  << "minutos"<<endl;
                  cout<< "La hora de entrada del carro:"<< horaE<<":"<< minutosE<<endl;
                  cout<< "La hora de salida del carro:"<< horaS<<":"<< minutosS<<endl;
                  system("PAUSE");
                break;
                
                
                
                
            case 3:
            	
                for(fila=0;fila<NFILAS;fila++)
                    for(columna=0;columna<NCOLUMNAS;columna++)
                        if(parqueadero[fila][columna]==1)
                            cout << "Puesto en fila " << fila << " columna " << columna << " ocupado" << endl;
                        else if(parqueadero[fila][columna]==0)
                            cout <<  "Puesto en fila " << fila << " columna " << columna << " libre" << endl;
                system("PAUSE");
                break;
            default:
                cout << "Opcion incorrecta, vuelva a intentarlo" << endl;
                system("PAUSE");
                break;
            case 4:
			case 5:
			case 6:
				cout << "Ingrese el valor de la tarifa por minuto"<< endl;
				cin >>Vtarifa;
				system("PAUSE");
                break;
				
			
    
        }
    }while(op != 0);
    return 0;
}
