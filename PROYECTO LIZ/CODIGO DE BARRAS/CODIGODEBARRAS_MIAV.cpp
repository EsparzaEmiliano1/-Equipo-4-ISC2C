#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int calcularDigitoControl(const char*, int);
const char* obtenerPais(const char*);

// 🐸 Estructura para asociar prefijos con países
struct CodigoPais {
    const char* prefijo;
    const char* pais;
};

// 🐸 Lista de países con sus prefijos
CodigoPais paises[] = {
    {"0", "EEUU"},
    {"380", "Bulgaria"},
    {"50", "Inglaterra"},
    {"539", "Irlanda"},
    {"560", "Portugal"},
    {"70", "Noruega"},
    {"759", "Venezuela"},
    {"850", "Cuba"},
    {"890", "India"}
};

int totalPaises = sizeof(paises) / sizeof(paises[0]);

// 🐸 Calcula el dígito de control de un código EAN
int calcularDigitoControl(const char* codigo, int longitud) {
    int suma = 0;
    int factor;

    for (int i = longitud - 2, pos = 1; i >= 0; i--, pos++) {
        int dig = codigo[i] - '0';
        factor = (pos % 2 == 1) ? 3 : 1;
        suma += dig * factor;
    }

    int resto = suma % 10;
    return (resto == 0) ? 0 : (10 - resto);
}

// 🐸 Busca el país asociado al código
const char* obtenerPais(const char* codigo) {
    char prefijo[4];

    for (int len = 3; len >= 1; len--) {
        strncpy(prefijo, codigo, len);
        prefijo[len] = '\0';

        for (int i = 0; i < totalPaises; i++) {
            if (strcmp(prefijo, paises[i].prefijo) == 0)
                return paises[i].pais;
        }
    }

    return "Desconocido";
}

int main() {
    // 🐸 Abrimos los archivos de entrada y salida
    FILE* archEntrada = fopen("entrada.txt", "r");
    FILE* archSalida = fopen("salida.txt", "w");

    if (!archEntrada || !archSalida) {
        cout << "Error al abrir los archivos." << endl;
        return 1;
    }

    char linea[20];

    // 🐸 Procesamos cada línea del archivo
    while (fscanf(archEntrada, "%s", linea) == 1) {
        if (strcmp(linea, "0") == 0)
            break;

        int len = strlen(linea);
        char codigo[14];

        // 🟡 Rellenar con ceros si es necesario
        if (len < 8) {
            int ceros = 8 - len;
            for (int i = 0; i < ceros; i++) codigo[i] = '0';
            strcpy(codigo + ceros, linea);
            codigo[8] = '\0';
            len = 8;
        } else if (len > 8 && len < 13) {
            int ceros = 13 - len;
            for (int i = 0; i < ceros; i++) codigo[i] = '0';
            strcpy(codigo + ceros, linea);
            codigo[13] = '\0';
            len = 13;
        } else {
            strcpy(codigo, linea);
        }

        // 🐸 Validación del dígito
        int digitoReal = codigo[len - 1] - '0';
        int digitoEsperado = calcularDigitoControl(codigo, len);

        if (digitoReal == digitoEsperado) {
            if (len == 13) {
                const char* pais = obtenerPais(codigo);
                printf("SI%s\n", pais);
                fprintf(archSalida, "SI%s\n", pais);
            } else {
                printf("SI\n");
                fprintf(archSalida, "SI\n");
            }
        } else {
            printf("NO\n");
            fprintf(archSalida, "NO\n");
        }
    }

    fclose(archEntrada);
    fclose(archSalida);
    return 0;
}
