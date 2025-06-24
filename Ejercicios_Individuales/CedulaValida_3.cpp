#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int calcularVerificador(int ced[]){

    int coeficientes[] = {2, 1, 2, 1, 2, 1, 2, 1, 2};       // Paso 1 
    int suma = 0;
    int verificador = 0;
    
    //  Paso 2
    for (int i = 0; i < 9; i++){    // Recorre las primeras 9 posiciones
        int valor = ced[i] * coeficientes[i];  // Multiplica por el coeficiente correspondiente
        
        // Si el resultado es mayor que 9, suma sus digitos
        if (valor > 9){
            valor = (valor / 10) + (valor % 10);  // Suma de digitos
        }
        suma += valor;  // Paso 3
    }
    
    int residuo = suma % 10;     // Paso 4   

    if (residuo == 0){      // Paso 5
        verificador = 0;
    } else {
        verificador = 10 - residuo;
    }  
    
    return verificador;
}


bool cedulaValida(int ced[]){
   
    // Validar provincia
    int provincia = ced[0] * 10 + ced[1]; // Suma de posicion 0 con posicion 2
    if (provincia < 1 || provincia > 24){   // Que no sea mayor que 24 y menor que 1
        return false;  
    }
    // Tercer digito es menor que 6
    if (ced[2] >= 6){   //Si pocicion 2 es mayor que 6 la cedula no es valida
        return false;
    }
    // Si se cumplen las anteriores condiciones se verifica que el verificador (:o) sea igual que la ultima posicion
    int verificador = calcularVerificador(ced);    
    return verificador == ced[9];
}

int main(){

    FILE *entrada = fopen("cedulas_3.txt", "r");       // Se abre el archivo cedula en modo lectura 
    FILE *salida = fopen("salida_cedulas_3.txt", "w"); // Se abre o se crea el archivo salida_cedula  
    
    if (!entrada || !salida){       // Por si alguno de los 2 archivos falla al abrirse
        cout << "Error al abrir archivos.\n";
        return 1;
    }
    
    char linea[32];
    
    while (fgets(linea, sizeof(linea), entrada)){  // Lee una linea del archivo de entrada
    
        int ced[10];  
        int len = strlen(linea);  // Longitud de la linea leida
        
        // Ignorar lineas vacias o con menos de 10 caracteres (no validas)
        if (len < 10) continue;
        
        int digitosLeidos = 0;  // Contador de digitos encontrados
        
        for (int i = 0; i < len && digitosLeidos < 10; i++){        // Recorre la linea para extraer los primeros 10 digitos numericos
            if (linea[i] >= '0' && linea[i] <= '9'){                // Si es un digito numerico
                ced[digitosLeidos++] = linea[i] - '0';              // Almacena el digito (convertido a int)
            }
        }
        
        // Si no se encontraron 10 digitos, ignora la linea
        if (digitosLeidos < 10) continue;
        
        // Verifica si la cedula es valida usando la funcion cedulaValida()
        bool valida = cedulaValida(ced);

        // Imprime y guarda el resultado (SI/NO)
        for (int i = 0; i < 10 ;i++){
            cout << ced[i];
            fprintf(salida,"%d" , ced[i]);
        } 
        
        if(valida){
            cout << " si es valida\n";
            fprintf(salida, " si es valida\n");
        } else {
            cout << " no es valida\n";
            fprintf(salida, " no es valida\n");
        }

    }
    
    fclose(entrada);
    fclose(salida);
    return 0;
}