//Proyecto Final. Trolls

#include <iostream>
using namespace std;

int calcRomper(int fuerza, int tam);                                                                    //Creamos prototipos de las funciones
void guardar(FILE* arch, int fuerza, int tam, int romper);

int main(){                                                                                            //Inicio del programa
    int fuerza, tam;                                                                                   //Se crean las variables a usar en el codigo
    const int max = 100;
    int fuerzas[max];
    int tams[max];
    int rompers[max];
    int count = 0;
    FILE* arch = fopen("registro.txt", "a");                                                          //Abrimos o creamos el archivo de texto
    if (arch == NULL){
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    while (true){
        while (true){
            cout << "Ingrese la fuerza deseada: ";                                                    //Se ingresa la fuerza usando unicamente numeros enteros
            cin >> fuerza;                                                                            //ignorando negativos, letras y decimales
            char extra;
            if (cin.fail() || fuerza < 0 || (cin.get(extra) && extra != '\n')){
                cout << "Entrada invalida" << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else {
                break;
            }
        }
        while (true){                                                                                 //Usamos la misma logica para ingresae el tamaño
            cout << "Ingrese el tamano de la cadena: ";
            cin >> tam;
            char extra;
            if (cin.fail() || tam < 0 || (cin.get(extra) && extra != '\n')){
                cout << "Entrada invalida" << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else {
                break;
            }
        }
        int romper = calcRomper(fuerza, tam);                                                         //Se llaman a las funciones cada que se ingresan ambos datos
        guardar(arch, fuerza, tam, romper);                                                           //mientras no sea 00, en ese caso se termina el registro
        if (fuerza == 0 && tam == 0){
            break;
        }
        if (count < max){
            fuerzas[count] = fuerza;
            tams[count] = tam;
            rompers[count] = romper;
            count++;
        } else {
            cout << "Se alcanzo el limite maximo de casos guardados" << endl;
        }
    }
    fclose(arch);                                                                                      //Muestra la salida en la terminal
    cout << "Resultados FInales: " <<endl;
    for (int i = 0; i < count; i++){
        cout << "Fuerza: " << fuerzas[i]
             << " Tamano: " << tams[i]
             << " Eslabones a romper: " << rompers[i] << endl;
    }
    return 0;
}

int calcRomper(int fuerza, int tam) {
    if (tam <= fuerza || tam <= 2 * fuerza) return 0;
    
    int parte_grande = (2 * tam + 2) / 3;  // 2/3 del total
    int parte_pequena = tam - parte_grande; // 1/3 del total
    
    return 1 + calcRomper(fuerza, parte_grande) + calcRomper(fuerza, parte_pequena);
}


void guardar(FILE* arch, int fuerza, int tam, int romper){                                             //Guardamos las entradas y salidas en el archivo de texto
    if (fuerza == 0 && tam == 0) {
        fprintf(arch, "Fin del registro\n");
    } else {
        fprintf(arch, "Fuerza: %d Tamano: %d Romper: %d\n", fuerza, tam, romper);
    }
}