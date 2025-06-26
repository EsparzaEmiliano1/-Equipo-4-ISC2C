#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

struct CasoPrueba{
    int numMuros;
    int* alturas;
    int saltosArriba;
    int saltosAbajo;
};

bool esNumeroValido(const char* str){
    // Verifica que el puntero no sea nulo y que no este vacio
    if(!str || strlen(str)==0) return false;

    // Recorre cada caracter y verifica que todos sean digitos
    for(int i=0; str[i]!='\0'; i++){
        if(!isdigit(str[i])) return false;
    }

    // Si pasa todas las condiciones, es un numero valido
    return true;
}

void liberarMemoria(CasoPrueba* casos, int numCasos){
    // Verifica que el puntero de casos no sea nulo
    if(casos){
        // Libera cada arreglo de alturas individualmente
        for(int i=0; i<numCasos; ++i){
            delete[] casos[i].alturas;
        }

        // Libera el arreglo principal de casos
        delete[] casos;
    }
}

int leerNumero(const char* mensaje){
    char entrada[100];
    int numero;

    while(true){
        // Muestra mensaje personalizado
        cout << mensaje;
        // Lee como cadena (no como entero) para validar manualmente
        cin >> entrada;

        cin.ignore(1000, '\n'); // Ignora hasta 1000 caracteres o hasta encontrar '\n'

        // Si la entrada es valida y mayor que 0, regresa el numero
        if(esNumeroValido(entrada)){
            numero = atoi(entrada);
            if(numero > 0) return numero;
        }

        // Si no fue valida, muestra error y vuelve a pedir
        cout << " Entrada invalida. Debe ser un numero entero positivo.\n";
    }
}

void contarSaltosRecursivo(const int alturas[], int numMuros, int index, int& arriba, int& abajo){
    // Caso base: ya no hay mas muros que comparar
    if(index >= numMuros-1) return;

    // Si el siguiente muro es mas alto, contar salto hacia arriba
    if(alturas[index+1] > alturas[index]) arriba++;
    // Si es mas bajo, contar salto hacia abajo
    else if(alturas[index+1] < alturas[index]) abajo++;

    // Llamada recursiva al siguiente par de muros
    contarSaltosRecursivo(alturas, numMuros, index+1, arriba, abajo);
}

CasoPrueba* leerCasosPrueba(const char* nombreArchivo, int& numCasos){
    FILE* archivo = fopen(nombreArchivo, "r");

    // Verifica si el archivo existe
    if(!archivo){
        fprintf(stderr, " Error al abrir archivo: %s\n", nombreArchivo);
        return nullptr;
    }

    char linea[100];

    // Lee la primera linea (cantidad de casos)
    if(fgets(linea, sizeof(linea), archivo)==nullptr){
        fprintf(stderr, " Error al leer numero de casos\n");
        fclose(archivo);
        return nullptr;
    }

    // Elimina el salto de linea
    linea[strcspn(linea, "\n")] = 0;

    // Verifica que sea un numero valido
    if(!esNumeroValido(linea)){
        fprintf(stderr, " Formato de archivo invalido\n");
        fclose(archivo);
        return nullptr;
    }

    numCasos = atoi(linea);
    CasoPrueba* casos = new CasoPrueba[numCasos];

    // Recorre cada caso
    for(int i=0; i<numCasos; ++i){
        // Lee cuantos muros hay
        if(fscanf(archivo, "%d", &casos[i].numMuros)!=1 || casos[i].numMuros <= 0){
            fprintf(stderr, " Formato invalido en numero de muros\n");
            liberarMemoria(casos, i);
            fclose(archivo);
            return nullptr;
        }

        // Crea arreglo dinamico para alturas de este caso
        casos[i].alturas = new int[casos[i].numMuros];

        // Lee las alturas de cada muro
        for(int j=0; j<casos[i].numMuros; ++j){
            if(fscanf(archivo, "%d", &casos[i].alturas[j])!=1 || casos[i].alturas[j] <= 0){
                fprintf(stderr, " Altura invalida en el caso #%d\n", i+1);
                liberarMemoria(casos, i+1);
                fclose(archivo);
                return nullptr;
            }
        }
    }

    fclose(archivo);
    return casos;
}

void procesarCasos(CasoPrueba* casos, int numCasos){
    // Procesa cada caso uno por uno
    for(int i=0; i<numCasos; ++i){
        // Inicializa contadores
        casos[i].saltosArriba = 0;
        casos[i].saltosAbajo = 0;

        // Cuenta los saltos usando funcion recursiva
        contarSaltosRecursivo(casos[i].alturas, casos[i].numMuros, 0,
                              casos[i].saltosArriba, casos[i].saltosAbajo);
    }
}

void escribirResultados(const CasoPrueba* casos, int numCasos, const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "w");

    // Verifica que el archivo se pueda abrir
    if(!archivo){
        fprintf(stderr, " Error al crear archivo: %s\n", nombreArchivo);
        return;
    }

    // Escribe resultados en consola y archivo
    for(int i=0; i<numCasos; ++i){
        printf(" Caso #%d: %d arriba, %d abajo\n", i+1, casos[i].saltosArriba, casos[i].saltosAbajo);
        fprintf(archivo, "%d %d\n", casos[i].saltosArriba, casos[i].saltosAbajo);
    }

    fclose(archivo);
}

bool validarYProcesarAlturas(const string& line, int numMuros, int*& alturas){
    char buffer[300];                     // Copia temporal
    strncpy(buffer, line.c_str(), sizeof(buffer)); 
    buffer[sizeof(buffer)-1] = '\0';      // Asegura que termine en nulo

    alturas = new int[numMuros];
    int count = 0;

    char* token = strtok(buffer, " ");    // Primer número

    while(token){
        // Validar si el token es número positivo
        bool valido = true;
        for(int i=0; token[i]!='\0'; i++){
            if(!isdigit(token[i])){
                valido = false;
                break;
            }
        }

        if(!valido){
            cout << " Error: '" << token << "' no es un numero valido.\n";
            delete[] alturas;
            return false;
        }

        int valor = atoi(token);
        if(valor <= 0){
            cout << " Error: La altura debe ser positiva (se recibio " << valor << ").\n";
            delete[] alturas;
            return false;
        }

        if(count >= numMuros){
            cout << " Error: Se ingresaron mas alturas de las esperadas.\n";
            delete[] alturas;
            return false;
        }

        alturas[count++] = valor;
        token = strtok(nullptr, " ");     // Siguiente número
    }

    if(count != numMuros){
        cout << " Error: Se esperaban " << numMuros << " alturas, pero se ingresaron " << count << ".\n";
        delete[] alturas;
        return false;
    }

    return true;
}


int main(){
    // Crea archivo de entrada
    FILE* archivoEntrada = fopen("entrada.txt", "w");
    if(!archivoEntrada){
        cout << " Error al crear archivo de entrada.\n";
        return 1;
    }

    // Solicita cantidad de casos al usuario
    int casos = leerNumero(" Numero de casos de prueba: ");
    fprintf(archivoEntrada, "%d\n", casos);

    // Repite el proceso para cada caso
    for(int c=0; c<casos; ++c){
        // Solicita cuantos muros tendra el caso actual
        int n = leerNumero(("\n Caso #" + to_string(c+1) + " - numero de muros: ").c_str());
        fprintf(archivoEntrada, "%d ", n);

        int* alturas = nullptr;
        bool entradaValida = false;
        string line;

        // Sigue pidiendo alturas hasta que la entrada sea valida
        while(!entradaValida){
            cout << " Ingrese " << n << " alturas positivas separadas por espacios: ";
            getline(cin, line);
            entradaValida = validarYProcesarAlturas(line, n, alturas);
            if(!entradaValida){
                cout << " Intente nuevamente.\n";
            }
        }

        // Guarda las alturas en el archivo
        for(int i=0; i<n; ++i){
            fprintf(archivoEntrada, "%d ", alturas[i]);
        }
        fprintf(archivoEntrada, "\n");

        delete[] alturas;
    }

    fclose(archivoEntrada);

    // Lee y procesa los datos del archivo
    int numCasos;
    CasoPrueba* casosPrueba = leerCasosPrueba("entrada.txt", numCasos);

    if(casosPrueba){
        procesarCasos(casosPrueba, numCasos);
        escribirResultados(casosPrueba, numCasos, "salida_5.txt");
        liberarMemoria(casosPrueba, numCasos);
    }else{
        cout << " Error al procesar los casos de prueba.\n";
        return 1;
    }

    return 0;
}
