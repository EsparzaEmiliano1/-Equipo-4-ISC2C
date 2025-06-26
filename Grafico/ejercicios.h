#ifndef EJERCICIOS_H  // para usar un archivo de cabecera 
#define EJERCICIOS_H

void EjecutarTrolls(){
    int fuerza, tam;
    const int max = 100;
    int fuerzas[max];
    int tams[max];
    int rompers[max];
    int count = 0;
    FILE* arch = fopen("registro_1.txt", "a");

    if (arch == NULL) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    cout << "--------------------------------------------\n";
    cout << "  Condicion de paro: fuerza = 0 y tamanio = 0\n";
    cout << "--------------------------------------------\n";
    Sleep(2000); 
    system("cls");
    
    while (true) {
    bool mostrarIteracion = true;

        while (true) {
            if (mostrarIteracion) {
                cout << "------------------------------\n";
                cout << "   Caso #" << count + 1 << "\n";
                cout << "------------------------------\n";
                mostrarIteracion = false;
            }

            cout << "Ingrese la fuerza deseada: ";
            cin >> fuerza;
            char extra;
            if (cin.fail() || fuerza < 0 || (cin.get(extra) && extra != '\n')) {
                cout << " Entrada invalida. Intente de nuevo.\n";
                cin.clear();
                Sleep(1000);
                system("cls");
                while (cin.get() != '\n');
                mostrarIteracion = true;
            } else {
                break;
            }
        }

        while (true) {
            cout << "Ingrese el tamano de la cadena: ";
            cin >> tam;
            char extra;
            if (cin.fail() || tam < 0 || (cin.get(extra) && extra != '\n')) {
                cout << " Entrada invalida. Intente de nuevo.\n";
                cin.clear();
                Sleep(1000);
                system("cls");
                cout << "------------------------------\n";
                cout << "   Caso #" << count + 1 << "\n";
                cout << "------------------------------\n";
                cout << "Ingrese la fuerza deseada: " << fuerza << "\n";
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

        Sleep(700);
        system("cls");

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
    cout << endl << "Suma: " << suma << endl;       
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
    int contador = 1; // Contador para numerar las cedulas

    cout << "-----------------------------\n";
    cout << "    Validacion de Cedulas    \n";
    cout << "-----------------------------\n\n";

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

        // Mostrar número de registro
        printf("Cedula #%d: ", contador++);

        // Imprime la cedula en formato XXX-XXX-XXX
        for(int i=0; i<10; i++){
            cout << ced[i];
            fprintf(salida,"%d" , ced[i]);
            if(i == 2 || i == 5){
                cout << "-";
                fprintf(salida, "-");
            }
        }

        // Imprime y guarda el resultado (SI/NO)
        if(valida){
            cout << "  ->  SI es valida\n";
            fprintf(salida, " si es valida\n");
        } else {
            cout << "  ->  NO es valida\n";
            fprintf(salida, " no es valida\n");
        }

        cout << "-----------------------------\n";

    }
    
    fclose(entrada);
    fclose(salida);
}


void EjecutarPlacas() {
    FILE* archivo = fopen("Matricula_4.txt", "w");
    if (!archivo) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }

    const int MAX = 1000;
    Placa* placas = new Placa[MAX];
    int total = 0;
    int iteracion = 1;

    // Mostrar condicion de paro
    cout << "--------------------------------------------\n";
    cout << "Condicion de paro: placa 9999 ZZZ\n";
    cout << "--------------------------------------------\n\n";
    Sleep(2000);
    system("cls");

    while (true) {
        Placa p;
        string numStr;
        string letrasStr;
        bool mostrarIteracion = true;

        // Pedir y validar numero
        while (true) {
            if (mostrarIteracion) {
                cout << "------------------------------\n";
                cout << "   Caso #" << iteracion << "\n";
                cout << "------------------------------\n";
                mostrarIteracion = false;
            }

            cout << "Ingrese el numero de placa (0-9999): ";
            cin >> numStr;

            bool numValido = true;
            if (numStr.empty() || numStr.length() > 4) numValido = false;
            for (char c : numStr) {
                if (!isdigit(c)) {
                    numValido = false;
                    break;
                }
            }

            if (!numValido) {
                cout << " Entrada invalida: solo 1 a 4 digitos\n";
                Sleep(1000);
                system("cls");
                mostrarIteracion = true;
                cin.clear();
                continue;
            }

            p.num = stoi(numStr);
            break;
        }

        // Pedir y validar letras
        while (true) {
            cout << "Ingrese las letras de la placa (3 letras mayusculas sin espacios): ";
            cin >> letrasStr;

            bool letrasValidas = letrasStr.length() == 3;
            for (char c : letrasStr) {
                if (c < 'A' || c > 'Z') {
                    letrasValidas = false;
                }
            }

            if (!letrasValidas) {
                cout << " Entrada invalida: se requieren 3 letras mayusculas\n";
                Sleep(1000);
                system("cls");
                cout << "------------------------------\n";
                cout << "   Caso #" << iteracion << "\n";
                cout << "------------------------------\n";
                cout << "Ingrese el numero de placa: " << p.num << "\n";
                cin.clear();
                continue;
            }

            p.l1 = letrasStr[0];
            p.l2 = letrasStr[1];
            p.l3 = letrasStr[2];
            break;
        }

        // Condicion de salida
        if (p.num == 9999 && p.l1 == 'Z' && p.l2 == 'Z' && p.l3 == 'Z') {
            break;
        }

        // Validar placa completa
        p.estado = esValida(p) ? VALIDA : INVALIDA;

        if (p.estado == INVALIDA) {
            cout << " Entrada invalida: ";
            printf("%04d %c%c%c\n", p.num, p.l1, p.l2, p.l3);
            Sleep(1000);
            system("cls");
            continue;
        }

        // Guardar en archivo
        fprintf(archivo, "entrada: %04d %c%c%c\n", p.num, p.l1, p.l2, p.l3);
        placas[total++] = p;
        iteracion++;

        if (total == MAX) {
            cout << "Se alcanzo el limite maximo\n";
            break;
        }

        Sleep(1000);
        system("cls");
    }

    // Mostrar resultados finales
    cout << "\nPlacas generadas:\n";
    for (int i = 0; i < total; i++) {
        avanzarPlaca(placas[i]);
        char resultado[30];
        sprintf(resultado, "placa: %04d %c%c%c", placas[i].num, placas[i].l1, placas[i].l2, placas[i].l3);
        cout << resultado << "\n";
        fprintf(archivo, "%s\n", resultado);
    }

    delete[] placas;
    fclose(archivo);
}


void EjecutarSaltos(){
    FILE* archivoEntrada = fopen("entrada_5.txt", "w");
    if(!archivoEntrada){
        cout << " Error al crear archivo de entrada.\n";
        return;
    }

    int casos = 0;
    bool mostrarIteracion = true;
    char entrada[100];

    // Solicita numero de casos con validacion
    while(true){
        if(mostrarIteracion){
            cout << "----------------------------------------\n";
            cout << "   Cantidad de casos de prueba (entero) \n";
            cout << "----------------------------------------\n";
            mostrarIteracion = false;
        }

        cout << " Numero de casos de prueba: ";
        cin.getline(entrada, 100);

        bool valido = true;
        for(int i=0; entrada[i]!='\0'; i++){
            if(!isdigit(entrada[i])){
                valido = false;
                break;
            }
        }

        if(valido && strlen(entrada) > 0){
            casos = atoi(entrada);
            if(casos > 0) break;
        }

        cout << " Entrada invalida. Intente de nuevo.\n";
        Sleep(1000);
        system("cls");
        mostrarIteracion = true;
    }

    fprintf(archivoEntrada, "%d\n", casos);

    for(int c=0; c<casos; ++c){
        int n = 0;
        mostrarIteracion = true;

        // Solicita cantidad de muros
        while(true){
            if(mostrarIteracion){
                cout << "----------------------------------------\n";
                cout << " Caso #" << c+1 << " - numero de muros \n";
                cout << "----------------------------------------\n";
                mostrarIteracion = false;
            }

            cout << " Ingrese numero de muros: ";
            cin.getline(entrada, 100);

            bool valido = true;
            for(int i=0; entrada[i]!='\0'; i++){
                if(!isdigit(entrada[i])){
                    valido = false;
                    break;
                }
            }

            if(valido && strlen(entrada) > 0){
                n = atoi(entrada);
                if(n > 0) break;
            }

            cout << " Entrada invalida. Intente de nuevo.\n";
            Sleep(1000);
            system("cls");
            mostrarIteracion = true;
        }

        fprintf(archivoEntrada, "%d ", n);

        int* alturas = new int[n];
        bool entradaValida = false;

        while(!entradaValida){
            cout << " Ingrese " << n << " alturas positivas separadas por espacios: ";
            cin.getline(entrada, 100);

            int indice = 0;
            int i = 0;
            while(entrada[i] != '\0' && indice < n){
                while(entrada[i] == ' ') i++;

                int numero = 0;
                bool hayNumero = false;
                while(isdigit(entrada[i])){
                    numero = numero * 10 + (entrada[i] - '0');
                    i++;
                    hayNumero = true;
                }

                if(hayNumero){
                    alturas[indice++] = numero;
                } else if(entrada[i] != '\0'){
                    break; // caracter no numerico
                }
            }

            while(entrada[i] == ' ') i++;

            if(indice == n && entrada[i] == '\0'){
                entradaValida = true;
            } else {
                cout << " Entrada invalida. Intente de nuevo.\n";
                delete[] alturas;
                alturas = new int[n];
                Sleep(1000);
                system("cls");
                cout << " Ingrese numero de muros: " << n << "\n";
            }
        }

        for(int i=0; i<n; i++){
            fprintf(archivoEntrada, "%d ", alturas[i]);
        }
        fprintf(archivoEntrada, "\n");
        delete[] alturas;
        Sleep(700);
        system("cls");
    }

    fclose(archivoEntrada);

    int numCasos;
    CasoPrueba* casosPrueba = leerCasosPrueba("entrada_5.txt", numCasos);

    if(casosPrueba){
        procesarCasos(casosPrueba, numCasos);
        escribirResultados(casosPrueba, numCasos, "salida_5.txt");
        liberarMemoria(casosPrueba, numCasos);
    }else{
        cout << " Error al procesar los casos de prueba.\n";
    }
}

void EjecutarCodigoBarras(){
    // Abrimos archivos de entrada y salida
    FILE* archEntrada = fopen("entrada_6.txt", "r");
    FILE* archSalida = fopen("salida_6.txt", "w");

    // Validamos que se hayan abierto correctamente
    if(!archEntrada || !archSalida){
        cout << "Error al abrir los archivos.\n";
        return;
    }

    cout << "-------------------------------------------\n";
    cout << "        VALIDADOR DE CODIGOS DE BARRAS     \n";
    cout << "-------------------------------------------\n\n";
    Sleep(1000);

    char linea[20];
    int contador = 1; // Lleva la cuenta de los codigos leidos

    // Leemos cada linea (codigo) del archivo
    while(fscanf(archEntrada, "%s", linea)==1){
        // Si se encuentra un "0", termina la lectura
        if(strcmp(linea, "0") == 0) break;

        int len = strlen(linea);
        char codigo[14];

        // Si el codigo es de menos de 8 digitos, se rellena con ceros a la izquierda
        if(len < 8){
            int ceros = 8 - len;
            for(int i = 0; i < ceros; i++) codigo[i] = '0';
            strcpy(codigo + ceros, linea);
            codigo[8] = '\0';
            len = 8;
        }
        // Si el codigo es entre 9 y 12 digitos, se ajusta a 13 con ceros
        else if(len > 8 && len < 13){
            int ceros = 13 - len;
            for(int i = 0; i < ceros; i++) codigo[i] = '0';
            strcpy(codigo + ceros, linea);
            codigo[13] = '\0';
            len = 13;
        }
        // Si ya esta completo (8 o 13), se copia tal cual
        else{
            strcpy(codigo, linea);
        }

        // Extraemos el digito real (el ultimo del codigo)
        int digitoReal = codigo[len - 1] - '0';

        // Calculamos el digito esperado
        int digitoEsperado = calcularDigitoControl(codigo, len);

        // Mostramos la informacion del codigo
        printf("Codigo #%d: %s\n", contador++, codigo);
        printf("Digito real    : %d\n", digitoReal);
        printf("Digito esperado: %d\n", digitoEsperado);

        // Validamos si el digito es correcto
        if(digitoReal == digitoEsperado){
            // Si es un codigo de 13 digitos, se muestra el pais
            if(len == 13){
                const char* pais = obtenerPais(codigo);
                printf("Resultado      : SI %s\n", pais);
                fprintf(archSalida, "SI %s\n", pais);
            } else {
                printf("Resultado      : SI\n");
                fprintf(archSalida, "SI\n");
            }
        } else {
            // Si no coincide el digito
            printf("Resultado      : NO\n");
            fprintf(archSalida, "NO\n");
        }

        cout << "-------------------------------------------\n";
        Sleep(800);
    }

    // Cerramos archivos
    fclose(archEntrada);
    fclose(archSalida);
}


#endif 
