#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// Calcula el digito de control usando el algoritmo EAN
int calcularDigitoControl(const char*, int);

// Determina el pais segun el prefijo del codigo
const char* obtenerPais(const char*);

// Estructura para asociar prefijos con países
struct CodigoPais{
    const char* prefijo;
    const char* pais;
};

// Lista de países con sus prefijos
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

int totalPaises = sizeof(paises)/sizeof(paises[0]);

// Esta función calcula el dígito de control según el estándar EAN
int calcularDigitoControl(const char* codigo, int longitud){
    int suma = 0;
    int factor;

    // Se recorre el código desde el penúltimo dígito hacia atrás
    for(int i=longitud-2, pos=1; i>=0; i--, pos++){
        int dig = codigo[i]-'0';                         // Se convierte el carácter a número
        factor = (pos%2==1) ? 3 : 1;                      // Posiciones impares *3, pares *1
        suma += dig*factor;
    }

    int resto = suma%10;
    return (resto==0) ? 0 : (10-resto);                  // Dígito de control final
}

// Busca el país al que pertenece el código EAN
const char* obtenerPais(const char* codigo){
    char prefijo[4];                                     // Prefijo de hasta 3 dígitos

    // Se prueba con prefijos de longitud 3, 2 y 1
    for(int len=3; len>=1; len--){
        strncpy(prefijo, codigo, len);                   // Copia los primeros "len" dígitos
        prefijo[len] = '\0';

        for(int i=0; i<totalPaises; i++){
            if(strcmp(prefijo, paises[i].prefijo)==0){
                return paises[i].pais;
            }
        }
    }

    return "Desconocido";                                // Si no coincide ningún prefijo
}

int main(){
    // Abrimos archivos de entrada y salida
    FILE* archEntrada = fopen("entrada_6.txt", "r");
    FILE* archSalida = fopen("salida_6.txt", "w");

    if(!archEntrada || !archSalida){
        cout << "Error al abrir los archivos." << endl;
        return 1;
    }

    char linea[20];

    // Leemos cada línea (código) del archivo
    while(fscanf(archEntrada, "%s", linea)==1){
        // Si se encuentra un "0", termina la lectura
        if(strcmp(linea, "0")==0) break;

        int len = strlen(linea);
        char codigo[14];

        // Si el código es de menos de 8 dígitos, se rellena con ceros a la izquierda
        if(len<8){
            int ceros = 8-len;
            for(int i=0; i<ceros; i++) codigo[i] = '0';
            strcpy(codigo+ceros, linea);
            codigo[8] = '\0';
            len = 8;

            cout << "Codigo de 8 digitos ajustado: " << codigo << endl;
        }
        // Si el código es entre 9 y 12 dígitos, se ajusta a 13 con ceros
        else if(len>8 && len<13){
            int ceros = 13-len;
            for(int i=0; i<ceros; i++) codigo[i] = '0';
            strcpy(codigo+ceros, linea);
            codigo[13] = '\0';
            len = 13;

            cout << "Codigo de 13 digitos ajustado: " << codigo << endl;
        }
        // Si ya está completo (8 o 13), se copia tal cual
        else{
            strcpy(codigo, linea);
            cout << "Codigo recibido: " << codigo << endl;
        }

        // Extraemos el dígito real (el último del código)
        int digitoReal = codigo[len-1]-'0';

        // Calculamos el dígito esperado
        int digitoEsperado = calcularDigitoControl(codigo, len);

        cout << "Digito real: " << digitoReal << ", digito esperado: " << digitoEsperado << endl;

        // Validamos si el dígito es correcto
        if(digitoReal == digitoEsperado){
            // Si es un código de 13, también se muestra el país
            if(len == 13){
                const char* pais = obtenerPais(codigo);
                cout << "SI " << pais << endl;
                fprintf(archSalida, "SI %s\n", pais);
            }else{
                cout << "SI" << endl;
                fprintf(archSalida, "SI\n");
            }
        }else{
            cout << "NO" << endl;
            fprintf(archSalida, "NO\n");
        }
    }

    fclose(archEntrada);
    fclose(archSalida);

    return 0;
}
