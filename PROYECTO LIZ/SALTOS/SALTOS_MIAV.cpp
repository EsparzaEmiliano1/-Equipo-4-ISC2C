/*#include <iostream>
#include <stdio.h>   // para usar FILE, fopen, fscanf, fclose
using namespace std;

int main() {
    // 🐸 declaramos los archivos 🐸
    FILE *archEntrada, *archSalida;

    // 🐸 abrimos el archivo de entrada solo para lectura 🐸
    archEntrada = fopen("entrada.txt", "r");
    if (!archEntrada) {
        cout << "ERROR al abrir archivo de entrada!!" << endl;
        return 1;
    }

    // 🐸 abrimos el archivo de salida solo para lectura 🐸
    archSalida = fopen("salida.txt", "w");
    if (!archSalida) {
        cout << "ERROR al crear archivo de salida!!" << endl;
        fclose(archEntrada);
        return 1;
    }

    int casos;
    fscanf(archEntrada, "%d", &casos);

    for (int c = 0; c < casos; c++) {
        int n;
        fscanf(archEntrada, "%d", &n);

        int *muros = new int[n];
        for (int i = 0; i < n; i++) {
            fscanf(archEntrada, "%d", &muros[i]);
        }

        int arriba = 0, abajo = 0;
        for (int i = 0; i < n - 1; i++) {
            if (muros[i + 1] > muros[i])
                arriba++;
            else if (muros[i + 1] < muros[i])
                abajo++;
        }

        // 🐸 Mostramos el resultado en pantalla y tambien lo guardamos en el archivo 🐸
        printf("%d %d\n", arriba, abajo);
        fprintf(archSalida, "%d %d\n", arriba, abajo);

        delete[] muros;   // 🐸 liberamos memoria 🐸
    }

    // 🐸 cerramos los archivos 🐸
    fclose(archEntrada);
    fclose(archSalida);

    return 0;
}*/

#include <iostream>
#include <stdio.h> // para usar FILE, fopen, fscanf, fprintf, fclose
using namespace std;

int main() {
    // 🐸 creamos el archivo de entrada🐸
    FILE *archEntrada = fopen("entrada.txt", "w"); // modo: escritura. se crea o sobreescribe

    if (!archEntrada) { // 🐸 validamos que se abra correctamente 🐸
        cout << "ERROR al crear archivo de entrada!" << endl; 
        return 1;
    }

    int casos;
    cout << "Numero de casaos de prueba: ";
    cin >> casos;

    fprintf(archEntrada, "%d\n", casos); // 🐸 se guarda la cantidad de casos en el archivo 🐸

    for (int c = 0; c < casos; c++) {
        int n;
        cout << "\nCaso #" << c + 1 << " - numero de muros: ";
        cin >> n;

        fprintf(archEntrada, "%d\n", n); // 🐸 guarda en numero de muros en el archivo 🐸

        cout << "Alturas de los muros (para ingresar otra altura de un espacios): ";
        for (int i = 0; i < n; i++) {
            int altura;
            cin >> altura;
            fprintf(archEntrada, "%d ", altura); // 🐸 guarda las alturas separadas en el archivo 🐸
        }
        fprintf(archEntrada, "\n"); // 🐸 salto de linea por cada caso 🐸
    }

    fclose(archEntrada); // 🐸 cerramos el archivo entrada 🐸

    // 🐸 abrimos el archivo entrada solo en modo lectura 🐸

    FILE *archSalida = fopen("salida.txt", "w");
    archEntrada = fopen("entrada.txt", "r");

    if (!archEntrada || !archSalida) {
        cout << "Error al abrir archivos!" << endl;
        return 1;
    }

    fscanf(archEntrada, "%d", &casos);

    for (int c = 0; c < casos; c++) {
        int n;
        fscanf(archEntrada, "%d", &n);

        int *muros = new int[n];
        for (int i = 0; i < n; i++) {
            fscanf(archEntrada, "%d", &muros[i]);
        }

        int arriba = 0, abajo = 0;
        for (int i = 0; i < n - 1; i++) {
            if (muros[i + 1] > muros[i])
                arriba++;
            else if (muros[i + 1] < muros[i])
                abajo++;
        }

       // 🐸 mostramos los resultados en pantalla y se guardan en el archivo de salida 🐸
        printf("%d %d\n", arriba, abajo);
        fprintf(archSalida, "%d %d\n", arriba, abajo);

        delete[] muros; // 🐸 liberamos memoria 🐸
    }

    fclose(archEntrada);
    fclose(archSalida);

    return 0;
}

