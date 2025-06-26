#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
using namespace std;

enum EstadoPlaca { VALIDA, INVALIDA };  // Enumeracion que almacena si la placa es valida o no

struct Placa {                          // Estructura de la placa
    int num;
    char l1;
    char l2;
    char l3;
    EstadoPlaca estado;
};

// Prototipos
bool esValida(const Placa& p);
void avanzarPlaca(Placa& p);
void avanzarLetra(char& l3, char& l2, char& l1);

int main() {
    FILE* archivo = fopen("Matricula_4.txt", "w");
    if (!archivo) {
        cout << "No se pudo abrir el archivo";
        return 1;
    }

    const int MAX = 1000;
    Placa* placas = new Placa[MAX];
    int total = 0;

    while (true) {
        Placa p;
        string numStr, letrasStr;

        // --- Pedir y validar número ---
        while (true) {
            cout << "Ingrese el numero de placa (0-9999): ";
            cin >> numStr;

            bool numValido = !numStr.empty() && numStr.length() <= 4;
            for (char c : numStr) {
                if (!isdigit(c)) {
                    numValido = false;
                    break;
                }
            }

            if (!numValido) {
                cout << "Entrada invalida: el numero debe tener hasta 4 digitos numericos.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            p.num = stoi(numStr);
            break;
        }

        // --- Pedir y validar letras ---
        while (true) {
            cout << "Ingrese las letras de la placa (exactamente 3 mayusculas sin espacios): ";
            cin >> letrasStr;

            bool letrasValidas = letrasStr.length() == 3;
            for (char c : letrasStr) {
                if (c < 'A' || c > 'Z') {
                    letrasValidas = false;
                    break;
                }
            }

            if (!letrasValidas) {
                cout << "Entrada invalida: debe ingresar exactamente 3 letras mayusculas.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            p.l1 = letrasStr[0];
            p.l2 = letrasStr[1];
            p.l3 = letrasStr[2];
            break;
        }

        // --- Condición de salida ---
        if (p.num == 9999 && p.l1 == 'Z' && p.l2 == 'Z' && p.l3 == 'Z') {
            break;
        }

        // --- Validar placa completa ---
        p.estado = esValida(p) ? VALIDA : INVALIDA;

        if (p.estado == INVALIDA) {
            cout << "entrada invalida: ";
            printf("%04d %c%c%c\n", p.num, p.l1, p.l2, p.l3);
            continue;
        }

        // --- Guardar placa válida ---
        fprintf(archivo, "entrada: %04d %c%c%c\n", p.num, p.l1, p.l2, p.l3);
        placas[total++] = p;

        if (total == MAX) {
            cout << "Se alcanzo el limite maximo de placas." << endl;
            break;
        }
    }

    // --- Avanzar placas y escribir resultados ---
    for (int i = 0; i < total; i++) {
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

// Verifica si la placa tiene formato correcto
bool esValida(const Placa& p) {
    if (p.num < 0 || p.num > 9999) return false;
    if (p.l1 < 'A' || p.l1 > 'Z') return false;
    if (p.l2 < 'A' || p.l2 > 'Z') return false;
    if (p.l3 < 'A' || p.l3 > 'Z') return false;
    return true;
}

// Avanza el número y letras de la placa
void avanzarPlaca(Placa& p) {
    p.num++;
    if (p.num == 10000) p.num = 0;
    avanzarLetra(p.l3, p.l2, p.l1);
}

// Avanza las letras de derecha a izquierda
void avanzarLetra(char& l3, char& l2, char& l1) {
    if (l3 < 'Z') {
        l3++;
    } else {
        l3 = 'A';
        if (l2 < 'Z') {
            l2++;
        } else {
            l2 = 'A';
            if (l1 < 'Z') {
                l1++;
            } else {
                l1 = 'A';
            }
        }
    }
}
