//Proyecto Final. Placas

#include <iostream>
using namespace std;

bool esValida(int num, char pal, char pal2, char pal3);
void siguiente(int& num, char& pal, char& pal2, char& pal3);

int main(){
    FILE* archivo = fopen("matricula.txt", "w");
    if (!archivo){
        cout << "No se pudo abrir el archivo";
        return 1;
    }
    const int MAX = 100;
    int nums[MAX];
    char pals[MAX], pals2[MAX], pals3[MAX];
    int total = 0;
    while (true){
        int num;
        char pal, pal2, pal3;
        cout << "Ingrese el numero de placa: ";
        cin >> num;
        cout << "Ingrese las letras de la placa (3 mayusculas): ";
        cin >> pal >> pal2 >> pal3;
        if (num == 9999 && pal == 'Z' && pal2 == 'Z' && pal3 == 'Z'){
            break;
        }
        if (!esValida(num, pal, pal2, pal3)){
            cout << "entrada invalida: ";
            printf("%d %c%c%c\n", num, pal, pal2, pal3);
            continue;
        }
        fprintf(archivo, "entrada: %04d %c%c%c\n", num, pal, pal2, pal3);
        nums[total] = num;
        pals[total] = pal;
        pals2[total] = pal2;
        pals3[total] = pal3;
        total++;
    }
    for (int i = 0; i < total; i++){
        int num = nums[i];
        char pal = pals[i], pal2 = pals2[i], pal3 = pals3[i];
        siguiente(num, pal, pal2, pal3);
        char resultado[30];
        sprintf(resultado, "placa: %04d %c%c%c", num, pal, pal2, pal3);
        cout << resultado << endl;
        fprintf(archivo, "%s\n", resultado);
    }
    fclose(archivo);
    return 0;
}

bool esValida(int num, char pal, char pal2, char pal3){
    if (num < 0 || num > 9999) return false;
    if (pal < 'A' || pal > 'Z') return false;
    if (pal2 < 'A' || pal2 > 'Z') return false;
    if (pal3 < 'A' || pal3 > 'Z') return false;
    return true;
}

void siguiente(int& num, char& pal, char& pal2, char& pal3){
    num++;
    pal3++;
    if (pal3 > 'Z'){
        pal3 = 'A';
        pal2++;
        if (pal2 > 'Z'){
            pal2 = 'A';
            if (pal < 'Z'){
                pal++;
            } else {
                pal = 'A';
            }
        }
    }
    if (num == 10000){
        num = 0;
    }
}
