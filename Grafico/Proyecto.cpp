#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <cstring>
#include <conio.h>

#include "archivo.h"
#include "ejercicios.h" // Make sure this file exists in the same folder as Proyecto.cpp, or provide the correct relative path, e.g. #include "subfolder/ejercicios.h"

using namespace std;


int main(){
    system("mode con: cols=120 lines=40");    
    int x1 = 20, y1 = 0, x2 = 100, y2 = 27;  
    srand(time(0));
    //pantallaInicio(x1, y1, x2, y2);
    menu(x1, y1, x2, y2);

    return 0;
}


void pantallaInicio(int x1, int y1, int x2, int y2){
    
    int cont = 1;

    for (int x = x1; x <= x2; x++){
        gotoxy(x, y1);  
        cout << "-";
        Sleep(50);  
        gotoxy(x, y2);
        cout << "-";
        Sleep(50);  
    }

    for (int y = y1; y <= y2; y++){
        gotoxy(x1, y);
        cout << "|";
        Sleep(100);

        if (cont <= 30){
            switch (cont){
            case 2:
                ImprimirTextoCentrado("PROYECTO FINAL", x1, y1 + 2, x2, y2);
                break;
            case 3:
                ImprimirTextoCentrado("Ejercicios aplicados", x1, y1 + 3, x2, y2);
                break;
            case 4:
                ImprimirTextoCentrado("UAA", x1, y1 + 5, x2, y2);
                break;    
            case 5:
                ImprimirTextoCentrado("Ingenieria en Sistemas Computacionales", x1, y1 + 7, x2, y2);
                break;    
            case 8:
                ImprimirTextoCentrado("Programacion 1", x1, y1 + 9, x2, y2);
                break;    
            case 10:
                ImprimirTextoCentrado("2-C", x1, y1 + 12, x2, y2);
                break;    
            case 14:
                ImprimirTextoCentrado("Prof :", x1, y1 + 14, x2, y2);
                break;    
            case 15:
                ImprimirTextoCentrado("Estela Lizbeth Muñoz Andrade", x1, y1 + 15, x2, y2);
                break; 
            case 19:
                ImprimirTextoCentrado("Alum:", x1, y1 + 18, x2, y2);
                break;    
            case 20:
                ImprimirTextoCentrado("Melanny Itzel Alvarez Valadez", x1, y1 + 19, x2, y2);
                break;    
            case 21:
                ImprimirTextoCentrado("Ian Slash Contreras Garcia", x1, y1 + 20, x2, y2);
                break;    
            case 22:
                ImprimirTextoCentrado("Emiliano de Jesus Esparza Ramirez", x1, y1 + 21, x2, y2);
                break;    
            case 25:
                ImprimirTextoCentrado("Lunes 24 Junio 2024", x1, y1 + 23, x2, y2);
                break;    
            case 26:
                ImprimirTextoCentrado("Aguscalientes, Ags.", x1, y1 + 24, x2, y2);
                break;
            }
            Sleep(30);

            cont++;
        }

        gotoxy(x2, y);
        cout << "|";
        Sleep(100);
    }

    Esquinas(x1, y1 , x2, y2);

    gotoxy((x1+20), (y1+26));
    cout << "["; 
    gotoxy((x1+60), (y1+26));
    cout << "]"; 

    int xCopia = x1+21;
    int CopiadeCopia = xCopia;

    for (int i=0; i<= 38; i++){
        gotoxy(xCopia, y1+26);
        cout << ".";
        xCopia++;
    }
    for (int i=0; i<= 38; i++){
        gotoxy(CopiadeCopia, y1+26);
        Sleep(300);
        cout << "#";
        CopiadeCopia++;
    }

    
    system("cls");
}


void menu(int x1, int y1, int x2, int y2){


    int cont = 1;

    for (int x = x1; x <= x2-15; x++){
        gotoxy(x, y1);  
        cout << "-";
        Sleep(50);  
        gotoxy(x, y2-5);
        cout << "-";
        Sleep(50);  
    } 

    for (int y = y1; y <= y2-5; y++){
        gotoxy(x1, y);
        cout << "|";
        Sleep(100);

        if (cont <= 25){
            switch (cont){
            case 1:
                ImprimirTextoCentrado("MENU", x1, y1 + 2, x2-15, y2-5);
                break;
            case 2:
                ImprimirTextoCentrado("Seleccione el ejercicio que desea ejecutar", x1, y1 + 3, x2-15, y2-5);
                break;
            case 7:
                ImprimirTextoCentrado("1. Trolls", x1, y1 + 6, x2-15, y2-5);
                break;    
            case 8:
                ImprimirTextoCentrado("2. Laberinto", x1, y1 + 7, x2-15, y2-5);
                break;    
            case 9:
                ImprimirTextoCentrado("3. Cedula", x1, y1 + 8, x2-15, y2-5);
                break;    
            case 10:
                ImprimirTextoCentrado("4. Placas", x1, y1 + 9, x2-15, y2-5);
                break;    
            case 12:
                ImprimirTextoCentrado("5. Saltos", x1, y1 + 10, x2-15, y2-5);
                break;    
            case 13:
                ImprimirTextoCentrado("6. Codigo de barras", x1, y1 + 11, x2-15, y2-5);
                break;    
            case 15:
                ImprimirTextoCentrado("7. Ayuda", x1, y1 + 12, x2-15, y2-5);
                break;    
            case 16:
                ImprimirTextoCentrado("8. Salir", x1, y1 + 13, x2-15, y2-5);
                break;    
            case 19:
                ImprimirTextoCentrado("Opcion a elegir:  ", x1, y1 + 15, x2-15, y2-5);
                break; 
            case 23:
                gotoxy(x1+27, y1+17);
                cout << "_________";
                break;
   
            }
            Sleep(30);

            cont++;
        }

        gotoxy(x2-15, y);
        cout << "|";
      Sleep(100);
    }

    Esquinas(x1, y1 , x2-15, y2-5);
    string opc;
    int num;
    bool SalirDelDo ;
    int cant= 55;
    int xEspecial = x1+27;

    do{

            borrarLinea(x1+5, y1+18,cant);

            cin.clear();
            num = LeerTextoCentrado(opc, x1, y1 + 17, x2-15, y2-5, cant, xEspecial);
            borrarLinea(x1+5, y1+20,cant);
            borrarLinea(x1+5, y1+19,cant);


            if(num <=0 || num >= 9){
                borrarLinea(x1+5, y1+17,cant);
                borrarLinea(x1+5, y1+19,cant);
                borrarLinea(x1+5, y1+20,cant);
                gotoxy(x1+27, y1+17);
                cout << "_________";
                ImprimirTextoCentrado("Entrada no valida. Intente nuevamente", x1, y1 + 19, x2-15, y2-5);

            }else{                           
                borrarLinea(x1+5, y1+19,cant);
                borrarLinea(x1+5, y1+20,cant);
            
                SalirDelDo = true; 


                switch (num){
                    case 1:
                        OpcionUno(x1, y1, x2, y2);                                        
                        break;
                    case 2:
                        OpcionDos(x1, y1, x2, y2);                    
                        break;
                    case 3:
                        OpcionTres(x1, y1, x2, y2);
                        break;
                    case 4:
                        OpcionCuatro(x1, y1, x2, y2);
                        break;
                    case 5:
                        OpcionCinco(x1, y1, x2, y2);                    
                        break;
                    case 6:
                        OpcionSeis(x1, y1, x2, y2);                    
                        break;
                    case 7:
                        OpcionSiete(x1, y1 , x2, y2);
                        break;
                    case 8:
                        SalirOpc8(x1, y1 , x2, y2);    
                        break;              
                }

            }
    }while(SalirDelDo==false);
}


void OpcionUno(int x1, int y1, int x2, int y2){

    BarraDeCarga(x1, y1, x2, y2);
  
    EjecutarTrolls(); // <- esta es la integración real
    system("pause");
    system("cls");
    menu(x1, y1, x2, y2);


}

void OpcionDos(int x1, int y1, int x2, int y2){

        BarraDeCarga(x1, y1, x2, y2);


    EjecutarLaberinto();
    system("pause");
    system("cls");

    menu(x1, y1, x2, y2);

}

void OpcionTres(int x1, int y1, int x2, int y2){

        BarraDeCarga(x1, y1, x2, y2);

    EjecutarCedulaValida();
    system("pause");
    system("cls");

    menu(x1, y1, x2, y2);
 

}

void OpcionCuatro(int x1, int y1, int x2, int y2){

    BarraDeCarga(x1, y1, x2, y2);
    EjecutarPlacas();
    system("pause");
    system("cls");

    menu(x1, y1, x2, y2);
 
}

void OpcionCinco(int x1, int y1, int x2, int y2){

    BarraDeCarga(x1, y1, x2, y2);



    EjecutarSaltos();
    system("pause");
    system("cls");

    menu(x1, y1, x2, y2);

}

void OpcionSeis(int x1, int y1, int x2, int y2){

    BarraDeCarga(x1, y1, x2, y2);



    EjecutarCodigoBarras();
    system("pause");
    system("cls");

    menu(x1, y1, x2, y2);

}


void OpcionSiete(int x1, int y1, int x2, int y2) {

    BarraDeCarga(x1, y1, x2, y2);

    // Marco y contenido de la ayuda
    int cont = 1;


    for (int x = (x1-5); x <= (x2 + 5); x++) {
        gotoxy(x, y1);  
        cout << "-";
        Sleep(50);  
        gotoxy(x, y2+3 );
        cout << "-";
        Sleep(50);  
    } 

    for (int y = y1; y <= (y2+3); y++) {
        gotoxy(x1-5, y);
        cout << "|";
        Sleep(100);

        if (cont <= 25) {
            switch (cont) {
                case 3:
                    ImprimirTextoCentrado("AYUDA", x1, y1 + 2, x2, y2 );
                    break;
                case 5:
                    ImprimirTextoCentrado("1.Trolls: Calcula cuantas veces se debe romper una cadena de eslabones ", x1, y1 + 4, x2, y2 - 5);
                    ImprimirTextoCentrado("para que hobbits y enanos puedan transportarla,", x1, y1 + 5, x2, y2 - 5);
                    ImprimirTextoCentrado("dividiendola recursivamente segun su fuerza", x1, y1 + 6, x2, y2 - 5);
                    break;
                case 10:
                    ImprimirTextoCentrado("2.Laberinto: Suma una matriz siguiendo la diagonal y la ultima columna", x1, y1 + 8, x2, y2 - 5);
                    ImprimirTextoCentrado("Se detiene al encontrar tres chacales (cero) y reporta la posicion final", x1, y1 + 9, x2, y2 - 5);
                    break;
                case 13:
                    ImprimirTextoCentrado("3.Cedula valida: Valida una cedula de 10 digitos. Verifica provincia", x1, y1 + 11, x2, y2 - 5);
                    ImprimirTextoCentrado("tercer digito, y el verificador con el algoritmo del registro civil.", x1, y1 + 12, x2, y2 - 5);
                    break;
                case 15:
                    ImprimirTextoCentrado("4.Placas: Simula el avance de una matricula espaniola, al llegar a 9999", x1, y1 + 14, x2, y2 - 5);
                    ImprimirTextoCentrado("reinicia los numeros y actualiza las letras", x1, y1 + 15, x2, y2 - 5);
                    ImprimirTextoCentrado("omitiendo vocales y la ni", x1, y1 + 16, x2, y2 - 5);
                    break;
                case 17:
                    ImprimirTextoCentrado("5.Saltos: Dado un conjunto de muros, calcula cuantos saltos hace Mario", x1, y1 + 18, x2, y2 - 5);
                    ImprimirTextoCentrado("hacia arriba y cuantos hacia abajo al avanzar de uno a otro.", x1, y1 + 19, x2, y2 - 5);
                    break;
                case 20:
                    ImprimirTextoCentrado("6.Codigo de barras: Valida codigos de barras usando el digito de control ", x1, y1 + 21, x2, y2 - 5);
                    ImprimirTextoCentrado("Si es EAN-13 valido, muestra el pais correspondiente si es reconocido. ", x1, y1 + 22, x2, y2 - 5);
                    break;
            }
            Sleep(30);
            cont++;
        }

        gotoxy(x2+5, y);
        cout << "|";
        Sleep(100);
    }
    Esquinas(x1-5, y1, x2+5, y2+3 );

    int tiempo = 750;
    temporizador(x1+7, y1+8, tiempo);
    system("cls");
    menu(x1, y1, x2, y2);

}


void SalirOpc8(int x1, int y1, int x2, int y2){
    
    BarraDeCarga(x1, y1, x2, y2);

    int cont = 1;

    for (int x = x1; x <= (x2-35); x++){
        gotoxy(x, y1);  
        cout << "-";
        Sleep(50);  
        gotoxy(x, y2-12);
        cout << "-";
        Sleep(50);  
    } 

    for (int y = y1; y <= (y2-12); y++){
        gotoxy(x1, y);
        cout << "|";
        Sleep(100);

        if (cont <= 15){
            switch (cont){
            case 1:
                ImprimirTextoCentrado("Salir", x1, y1 + 2, x2-35, y2-12);
                break;
            case 2:
                ImprimirTextoCentrado("1. Salir del programa", x1, y1 + 4, x2-35, y2-12);
                break;
            case 3:
                ImprimirTextoCentrado("2. Regresar", x1, y1 + 5, x2-35, y2-12);
                break;
            case 8:
                ImprimirTextoCentrado("Opcion a elegir:  ", x1, y1 + 8, x2-35, y2-12);
                break;
            case 10:
                gotoxy(x1+17,y1+10);
                cout << "_________";
                break;
            }
            Sleep(30);

            cont++;
        }

        gotoxy(x2-35, y);
        cout << "|";
        Sleep(100);
    }

    Esquinas(x1, y1 , x2-35, y2-12);

    int option;
    bool SalirDelDo = false;
    string opc;
    int cant = 44;
    int xEspecial = x1+17;

    do {
        option = LeerTextoCentrado(opc, x1, y1+10 , x2-35, y2-12,cant, xEspecial);

        if (option <= 0 || option >= 3) {
            borrarLinea(x1+1,y1+10,cant);
            ImprimirTextoCentrado("Entrada no valida. Intente nuevamente", x1, y1+12 , x2-35, y2-12);
            gotoxy(x1+17,y1+10);
            cout << "_________";
            
        } else {

            if (option == 1) {

                borrarLinea(x1+1,y1+12,cant);
                ImprimirTextoCentrado("        Fin del programa        ", x1, y1+14 , x2-35, y2-12);

                gotoxy((x1+13), (y1+12));
                cout << "["; 
                gotoxy((x1+31), (y1+12));
                cout << "]      "; 

                int xCopia = x1 + 14;
                int CopiadeCopia = xCopia;

                for (int i=0; i<= 16; i++){
                    gotoxy(xCopia, y1+12);
                    //Sleep(200);
                    cout << ".";
                    xCopia++;
                }
                for (int i=0; i<= 16 ; i++){
                    gotoxy(CopiadeCopia, y1+12);
                    Sleep(300);
                    cout << "#";
                    CopiadeCopia++;
                }
                
                SalirDelDo = true;

                //gotoxy((x2),(y1));        
                //      gotoxy(x1 +3, y1 + 14);
                //        system("pause");
                exit(0);
            } else if (option == 2) {
                borrarLinea(x1+1,y1+12,cant);

                gotoxy((x1+13), (y1+12));
                cout << "["; 
                gotoxy((x1+31), (y1+12));
                cout << "]      "; 

                int xCopia = x1+14;
                int CopiadeCopia = xCopia;

                for (int i=0; i<= 16; i++){
                    gotoxy(xCopia, y1+12);
                    //Sleep(200);
                    cout << ".";
                    xCopia++;
                }
                for (int i=0; i<= 16 ; i++){
                    gotoxy(CopiadeCopia, y1+12);
                    Sleep(300);
                    cout << "#";
                    CopiadeCopia++;
                }
                system("cls");
                menu(x1, y1, x2, y2);
                
                SalirDelDo = true;

            }else{

            }
        }
    } while (!SalirDelDo);

}

