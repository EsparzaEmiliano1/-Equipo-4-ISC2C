#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int **leerMatrizDesdeArchivo(const char *nombreArchivo, int *n){  // Nombre de la matriz y tamaño de MAX
    
    FILE *archivo = fopen(nombreArchivo, "r");     // Abre el archivo en modo lectura
    if(archivo == NULL){
        cout << "Error: No se pudo abrir el archivo de entrada.\n";
        return NULL;
    }   // Si no se puede abrir marca un error y regresa null

    // Lee el tamaño del archivo 
    if(fscanf(archivo, "%d", n) != 1 || *n <= 0){  // verifica que solo lea un valor y que sea positivo     
        cout << "Error: Tamanio de matriz invalido.\n";
        fclose(archivo);
        return NULL;
    }   // Si hay error lo menciona y cierra el archivo y regresa null

    
    int **matriz = (int **)malloc(*n * sizeof(int *));  // Asigna memoria a una matriz dinamica para las filas de la matriz
    if(matriz == NULL){
        printf("Error: No se pudo reservar memoria para filas.\n");
        fclose(archivo);
        return NULL;
    }   // Verifica que se haya cumplido la anterior instruccion

  for(int i = 0; i < *n; i++){
        matriz[i] = (int *)malloc(*n * sizeof(int));   // Se asigna memora a matriz para cada fila creando las columnas 

        if(matriz[i] == NULL){
            cout << "Error: No se pudo reservar memoria para columnas.\n";
            // Liberar cualquier memoria previamente asignada
            for(int j = 0; j < i; j++){
                free(matriz[j]);
            }

            free(matriz);
            fclose(archivo);
            return NULL;
        }   // Si no se reserva memoria 
    }

    // Llena la matriz de tamaño n x n
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            if(fscanf(archivo, "%d", &matriz[i][j]) != 1){  // Si hay un error en la asignacion de valores de la matriz salta el error 
                cout <<"Error: Datos insuficientes o invalidos en el archivo.\n";
                // Libera memoria
                for (int k = 0; k <= i; k++) {
                    free(matriz[k]);
                }
                free(matriz);
                fclose(archivo);
                return NULL;
            }
        }
    }

    fclose(archivo);     // Cierra el archivo donde se leyeron los datos 
    return matriz;      // Manda matriz a main 

}

int laberinto(int **M, int n, int *posF, int *posC) {
    int suma = 0;
    int chacales = 0;

    // Recorrido por la diagonal
    for(int i = 0; i < n; i++){
        if(M[i][i] == 0){   // si encuentra un 0 aumenta el contador chacal
            chacales++;
        }

        suma += M[i][i];        // suma la diagonal
        
        *posF = i;      // Guarda posicion actual (renglon)
        *posC = i;      // Guarda posicion actual (columna)

        if (chacales == 3){     // si encuentra 3 "chacales" regresa suma
            return suma;
        }
    }

    // Recorrido por la ultima columna, omitiendo la esquina [n-1][n-1]
    for(int i = 0; i < n - 1; i++){
       
        if (M[i][n - 1] == 0){  // Si en cuentra un "chacal" incrementa el contador
            chacales++;
        }

        suma += M[i][n - 1];    //Suma las posiciones 
        *posF = i;
        *posC = n - 1;      // Guarda las posiciones 

        if (chacales == 3){    // Si encuentra 3 chacales regresa suma
            return suma;
        }
    }

    // Por si no se encuentran 3 chacales 
    return suma;
}


void liberarMatriz(int **M, int n){  // Libera memoria de matriz 
    for (int i = 0; i < n; i++){    
        free(M[i]);     // Libera memoria de cada renglon 
    }

    free(M);  // Libera completamente 
}

void escribirResultado(const char *nombreArchivo, int suma, int posF, int posC){
    
    FILE *archivo = fopen(nombreArchivo, "w");  // Crea un archivo en modo escritura
    
    if(archivo == NULL){
        cout << "Error: No se pudo crear el archivo de salida.\n";
        return;
    }       // Da error si no se pudo abrir/crear el archivo

    fprintf(archivo, "Suma: %d\n", suma);
    fprintf(archivo, "Posicion final: (%d, %d)\n", posF, posC);     // Se escribe en el archivo los resultados

    fclose(archivo);        // Cierra el archivo
}


int main(){

    int **matriz = NULL;    // Se crea una matriz vacia
    int n = 0;              // Tamaño de la matriz (MAX)

    matriz = leerMatrizDesdeArchivo("matriz_2.txt", &n);  // Se llena la matriz
    if(matriz == NULL){
        return 1; // Error ya mostrado
    }   // Por si no se llena la matriz

    int posF = 0, posC = 0;     // Declara las variables para las posiciones 
    int suma = laberinto(matriz, n, &posF, &posC);  // return suma

    // Se imprimen los datos en consola  
    cout << "Suma: " << suma << endl;       
    cout <<"Posicion final: (" << posF << ","<< posC << ")\n"; 

    // Se imprimen los datos en un documento txt  
    escribirResultado("salida_2.txt", suma, posF, posC);

    liberarMatriz(matriz, n);  // Libera memoria

    return 0;
}