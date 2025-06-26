#ifndef EJERCICIOS_H  // para usar un archivo de cabecera 
#define EJERCICIOS_H


void EjecutarTrolls(){
    int fuerza, tam;
    const int max = 100;
    int fuerzas[max];
    int tams[max];
    int rompers[max];
    int count = 0;
    FILE* arch = fopen("registro.txt", "a");

    if (arch == NULL) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    while (true) {
        while (true) {
            cout << "Ingrese la fuerza deseada: ";
            cin >> fuerza;
            char extra;
            if (cin.fail() || fuerza < 0 || (cin.get(extra) && extra != '\n')) {
                cout << "Entrada invalida" << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else {
                break;
            }
        }

        while (true) {
            cout << "Ingrese el tamano de la cadena: ";
            cin >> tam;
            char extra;
            if (cin.fail() || tam < 0 || (cin.get(extra) && extra != '\n')) {
                cout << "Entrada invalida" << endl;
                cin.clear();
                while (cin.get() != '\n');
            } else {
                break;
            }
        }

        int romper = calcRomper(fuerza, tam);
        guardar(arch, fuerza, tam, romper);

        if (fuerza == 0 && tam == 0) {
            break;
        }

        if (count < max) {
            fuerzas[count] = fuerza;
            tams[count] = tam;
            rompers[count] = romper;
            count++;
        } else {
            cout << "Se alcanzo el limite maximo de casos guardados" << endl;
        }
    }

    fclose(arch);

    cout << "\nResultados Finales: " << endl;
    for (int i = 0; i < count; i++) {
        cout << "Fuerza: " << fuerzas[i]
             << " Tamano: " << tams[i]
             << " Eslabones a romper: " << rompers[i] << endl;
    }
}

int EjecutarLaberinto(){
    
    int **matriz = NULL;    // Se crea una matriz vacia
    int n = 0;              // Tamaño de la matriz (MAX)

    matriz = leerMatrizDesdeArchivo("matriz_2.txt", &n);  // Se llena la matriz

    if(matriz == NULL){
        return 1; // Error ya mostrado
    }   // Por si no se llena la matriz

    int posF = 0, posC = 0;     // Declara las variables para las posiciones 
    int suma = laberinto(matriz, n, &posF, &posC);  // return suma

    imprimirLaberintoVisual(matriz, n, posF, posC);

    // Se imprimen los datos en consola  
    cout << "Suma: " << suma << endl;       
    cout <<"Posicion final: (" << posF << ","<< posC << ")\n"; 

    // Se imprimen los datos en un documento txt  
    escribirResultado("salida_2.txt", suma, posF, posC);

    liberarMatriz(matriz, n);  // Libera memoria
}

void EjecutarCedulaValida(){

    FILE *entrada = fopen("cedulas_3.txt", "r");       // Se abre el archivo cedula en modo lectura 
    FILE *salida = fopen("salida_cedulas_3.txt", "w"); // Se abre o se crea el archivo salida_cedula  
    
    if (!entrada || !salida){       // Por si alguno de los 2 archivos falla al abrirse
        cout << "Error al abrir archivos.\n";
        return;
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
}

void EjecutarPlacas(){
    
    FILE* archivo = fopen("Matricula_4.txt", "w");
    if (!archivo) {
        cout << "No se pudo abrir el archivo";
        return ;
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
    return ;
}

void EjecutarSaltos(){
    // Crea archivo de entrada
    FILE* archivoEntrada = fopen("entrada.txt", "w");
    if(!archivoEntrada){
        cout << " Error al crear archivo de entrada.\n";
        return ;
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
        return ;
    }

}

void EjecutarCodigoBarras(){
      // Abrimos archivos de entrada y salida
    FILE* archEntrada = fopen("entrada_6.txt", "r");
    FILE* archSalida = fopen("salida_6.txt", "w");

    if(!archEntrada || !archSalida){
        cout << "Error al abrir los archivos." << endl;
        return ;
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

}

#endif 
