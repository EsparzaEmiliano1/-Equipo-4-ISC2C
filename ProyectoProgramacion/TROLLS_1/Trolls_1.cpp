//Proyecto Final. Trolls

#include <iostream>
#include <cstdio>
using namespace std;

enum EstadoEslabon { ACTIVO, FIN };                                                                     //Enumeracion lara saber si se continua con la entrada

struct Eslabon{                                                                                         //Estructutra del programa con los datos de fuerza, tamaño y
    int fuerza;                                                                                         //la cantidad a romper asi como su estado
    int tamano;
    int romper;
    EstadoEslabon estado;
};

int calcRomper(int fuerza, int tam);                                                                    //Prototipos del programa
void guardar(FILE* arch, const Eslabon& esl);

int main(){                                                                                             //Inicio del programa y abrimos el archivo "registro"
    const int MAX = 100;                                                                                //Numero maximo de casos posibles a registrar
    Eslabon* eslabones = new Eslabon[MAX];
    int count = 0;
    FILE* arch = fopen("registro.txt", "a");
    if (!arch){
        cout << "No se pudo abrir el archivo" << endl;
        delete[] eslabones;
        return 1;
    }
    while (true){
        Eslabon esl;
        while (true){
            cout << "Ingrese la fuerza deseada: ";                                                      //Llenamos los datos de fuerza validando solo datos de tipo numero entero
            cin >> esl.fuerza;
            char extra;
            if (cin.fail() || esl.fuerza < 0 || (cin.get(extra) && extra != '\n')){
                cout << "Entrada invalida" << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else {
                break;
            }
        }
        while (true){
            cout << "Ingrese el tamano de la cadena: ";                                                 //Llenamos los datos de tamaño validando solo datos de tipo numero entero
            cin >> esl.tamano;
            char extra;
            if (cin.fail() || esl.tamano < 0 || (cin.get(extra) && extra != '\n')){
                cout << "Entrada invalida" << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else {
                break;
            }
        }
        if (esl.fuerza == 0 && esl.tamano == 0){                                                      //Terminamos las entradas cuando el tamaño y fuerza sean 00
            esl.estado = FIN;
            guardar(arch, esl);
            break;
        } else{                                                                                       //Guardamos los datos dados por el usuario
            esl.estado = ACTIVO;
            esl.romper = calcRomper(esl.fuerza, esl.tamano);
            guardar(arch, esl);
        }
        if (count < MAX){
            eslabones[count++] = esl;
        } else {
            cout << "Se alcanzo el limite maximo de casos guardados" << endl;
            break;
        }
    }
    fclose(arch);                                                                                      //Cierra el archivo e imprime los resultados en la terminal
    for (int i = 0; i < count; i++){
        cout << "Fuerza: " << eslabones[i].fuerza
             << " Tamano: " << eslabones[i].tamano
             << " Eslabones a romper: " << eslabones[i].romper << endl;
    }
    delete[] eslabones;
    return 0;
}

int calcRomper(int fuerza, int tam){                                                                 //Calcula en cuantas partes romper la cadena con base al tamaño y fuerza
    if (tam <= fuerza) return 0;                                                                      //antes dados por el usuario
    return 1 + calcRomper(fuerza, tam - fuerza);
}

void guardar(FILE* arch, const Eslabon& esl){                                                        //Guarda los datos en el archivo
    if (esl.estado == FIN) {
        fprintf(arch, "Fin del registro\n");
    } else {
        fprintf(arch, "Fuerza: %d Tamano: %d Romper: %d\n", esl.fuerza, esl.tamano, esl.romper);
    }
}
