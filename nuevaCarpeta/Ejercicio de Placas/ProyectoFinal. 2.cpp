//Proyecto Final. Placas

#include <iostream>
#include <cstdio>
using namespace std;

enum EstadoPlaca { VALIDA, INVALIDA };                                                              //Enumeracion que almacena si la placa es valida o no

struct Placa{                                                                                       //Estructura de la placa que consta de un numero y 3 letras, a su vez se 
    int num;                                                                                        //agrega su estado 
    char l1;
    char l2;
    char l3;
    EstadoPlaca estado;
};

bool esValida(const Placa& p);                                                                      //Prototipos de la funcion
void avanzarPlaca(Placa& p);
void avanzarLetra(char& l3, char& l2, char& l1);

int main(){                                                                                         //Inicio del programa con la creacion del archivo "matricula"
    FILE* archivo = fopen("matricula.txt", "w");
    if (!archivo){
        cout << "No se pudo abrir el archivo";
        return 1;
    }
    const int MAX = 1000;
    Placa* placas = new Placa[MAX];                                                                 //Numero maximo de placas a registrar
    int total = 0;
    while (true){
        Placa p;
        cout << "Ingrese el numero de placa: ";                                                     //Se solicita al usuario el llenado de la placa 
        cin >> p.num;
        cout << "Ingrese las letras de la placa (3 mayusculas): ";
        cin >> p.l1 >> p.l2 >> p.l3;
        if (p.num == 9999 && p.l1 == 'Z' && p.l2 == 'Z' && p.l3 == 'Z'){                            //Termina el programa al ingresar la matricula 9999 ZZZ
            break;
        }
        p.estado = esValida(p) ? VALIDA : INVALIDA;                                                 //Llama a la funcion esValida que valida los datos ingresados por el usuario
        if (p.estado == INVALIDA){
            cout << "entrada invalida: ";
            printf("%04d %c%c%c\n", p.num, p.l1, p.l2, p.l3);
            continue;
        }
        fprintf(archivo, "entrada: %04d %c%c%c\n", p.num, p.l1, p.l2, p.l3);                        //Guarda los datos de la placa dada por el usuario en el archivo
        placas[total++] = p;
        if (total == MAX){
            cout << "Se alcanzo el limite maximo de placas." << endl;
            break;
        }
    }
    for (int i = 0; i < total; i++){                                                                
        avanzarPlaca(placas[i]);
        char resultado[30];
        sprintf(resultado, "placa: %04d %c%c%c", placas[i].num, placas[i].l1, placas[i].l2, placas[i].l3);
        cout << resultado << endl;
        fprintf(archivo, "%s\n", resultado);
    }
    delete[] placas;
    fclose(archivo);
    return 0;
}

bool esValida(const Placa& p){                                                                      //Funcion para evitar el llenado de forma erroena de la placa 
    if (p.num < 0 || p.num > 9999) return false;
    if (p.l1 < 'A' || p.l1 > 'Z') return false;
    if (p.l2 < 'A' || p.l2 > 'Z') return false;
    if (p.l3 < 'A' || p.l3 > 'Z') return false;
    return true;
}

void avanzarPlaca(Placa& p){                                                                        //Funcion que avanza al siguiente numero
    p.num++;
    if (p.num == 10000) p.num = 0;
    avanzarLetra(p.l3, p.l2, p.l1);
}

void avanzarLetra(char& l3, char& l2, char& l1){                                                   //Funcion para avanzar de letra de forma recursiva
    if (l3 < 'Z'){
        l3++;
    } else {
        l3 = 'A';
        if (l2 < 'Z'){
            avanzarLetra(l2, l1, l1);
        } else {
            l2 = 'A';
            if (l1 < 'Z'){
                l1++;
            } else {
                l1 = 'A';
            }
        }
    }
}


