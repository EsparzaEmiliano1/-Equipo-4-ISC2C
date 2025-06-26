#ifndef ARCHIVO_H  // para usar un archivo de cabecera 
#define ARCHIVO_H

using namespace std;

// Funciones de la interfaz de usuario
void gotoxy(int x, int y);
void pantallaInicio(int x1, int y1, int x2, int y2);
void menu(int x1, int y1, int x2, int y2);
int LeerTextoCentrado(string opc, int x1, int y1, int x2, int y2, int cant, int xEspecial);
void OpcionUno(int x1, int y1, int x2, int y2);
void OpcionDos(int x1, int y1, int x2, int y2);
void OpcionTres(int x1, int y1, int x2, int y2);
void OpcionCuatro(int x1, int y1, int x2, int y2);
void OpcionCinco(int x1, int y1, int x2, int y2);
void OpcionSeis(int x1, int y1, int x2, int y2);
void OpcionSiete(int x1, int y1, int x2, int y2);
void SalirOpc8(int x1, int y1, int x2, int y2);


// Funciones  Trolls
void guardar(FILE* arch, int fuerza, int tam, int romper){                                             //Guardamos las entradas y salidas en el archivo de texto
    if (fuerza == 0 && tam == 0) {
        fprintf(arch, "Fin del registro\n");
    } else {
        fprintf(arch, "Fuerza: %d Tamano: %d Romper: %d\n", fuerza, tam, romper);
    }
}
int calcRomper(int fuerza, int tam) {
    if (tam <= fuerza || tam <= 2 * fuerza) return 0;
    
    int parte_grande = (2 * tam + 2) / 3;  // 2/3 del total
    int parte_pequena = tam - parte_grande; // 1/3 del total
    
    return 1 + calcRomper(fuerza, parte_grande) + calcRomper(fuerza, parte_pequena);
}


// Funciones laberinto
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


void imprimirLaberintoVisual(int **M, int n, int posF, int posC) {
    cout << "\nVisualizacion del recorrido:\n";
    
    // Imprimir borde superior
    cout << "   +";
    for(int j = 0; j < n; j++) cout << "---";
    cout << "-+" << endl;
    
    for(int i = 0; i < n; i++){
        // Imprimir numero de fila y borde izquierdo
        printf("%2d |", i);
        
        for(int j = 0; j < n; j++) {
            // Verificar si es parte del camino recorrido
            bool esCamino = (i == j && i <= posF) || (j == n-1 && i <= posF && i <= posF);
            
            if(i == posF && j == posC){
                // Posicion final - resaltada
                cout << " P ";
            } else if(M[i][j] == 0) {
                // Chacal (0) - marcado diferente
                cout << " 0 ";
            }else if(esCamino) {
                // Camino recorrido
                cout << " X ";
            } else {
                // Valor normal de la matriz
                printf("%2d ", M[i][j]);
            }
        }
        
        cout << "|" << endl;
    }
    
    // Imprimir borde inferior
    cout << "   +";
    for(int j = 0; j < n; j++) cout << "---";
    cout << "-+" << endl;
    
    // Leyenda
    cout << "\nSignificados:\n";
    cout << "  P: Posicion final\n";
    cout << "  X: Camino recorrido\n";
    cout << "  0: Chacal encontrado\n";
}

// Funciones cedula valida

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


// Funciones Placas
enum EstadoPlaca { VALIDA, INVALIDA };  // Enumeracion que almacena si la placa es valida o no

struct Placa {                          // Estructura de la placa
    int num;
    char l1;
    char l2;
    char l3;
    EstadoPlaca estado;
};

// Verifica si la placa tiene formato correcto
bool esValida(const Placa& p) {
    if (p.num < 0 || p.num > 9999) return false;
    if (p.l1 < 'A' || p.l1 > 'Z') return false;
    if (p.l2 < 'A' || p.l2 > 'Z') return false;
    if (p.l3 < 'A' || p.l3 > 'Z') return false;
    return true;
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

// Avanza el numero y letras de la placa
void avanzarPlaca(Placa& p){
    p.num++;
    if (p.num == 10000) p.num = 0;
    avanzarLetra(p.l3, p.l2, p.l1);
}

// Funciones Saltos

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

    char* token = strtok(buffer, " ");    // Primer numero

    while(token){
        // Validar si el token es numero positivo
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
        token = strtok(nullptr, " ");     // Siguiente numero
    }

    if(count != numMuros){
        cout << " Error: Se esperaban " << numMuros << " alturas, pero se ingresaron " << count << ".\n";
        delete[] alturas;
        return false;
    }

    return true;
}

// Funciones codigo de barras

struct CodigoPais{
    const char* prefijo;
    const char* pais;
};

// Lista de paises con sus prefijos
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

// Esta funcion calcula el digito de control segun el estandar EAN
int calcularDigitoControl(const char* codigo, int longitud){
    int suma = 0;
    int factor;

    // Se recorre el codigo desde el penultimo digito hacia atras
    for(int i=longitud-2, pos=1; i>=0; i--, pos++){
        int dig = codigo[i]-'0';                         // Se convierte el caracter a numero
        factor = (pos%2==1) ? 3 : 1;                      // Posiciones impares *3, pares *1
        suma += dig*factor;
    }

    int resto = suma%10;
    return (resto==0) ? 0 : (10-resto);                  // Digito de control final
}

// Busca el pais al que pertenece el codigo EAN
const char* obtenerPais(const char* codigo){
    char prefijo[4];                                     // Prefijo de hasta 3 digitos

    // Se prueba con prefijos de longitud 3, 2 y 1
    for(int len=3; len>=1; len--){
        strncpy(prefijo, codigo, len);                   // Copia los primeros "len" digitos
        prefijo[len] = '\0';

        for(int i=0; i<totalPaises; i++){
            if(strcmp(prefijo, paises[i].prefijo)==0){
                return paises[i].pais;
            }
        }
    }

    return "Desconocido";                                // Si no coincide ningun prefijo
}



void BarraDeCarga(int x1, int y1, int x2, int y2){
    
    gotoxy((x1 + 13), (y1 + 19));
    cout << "      ["; 
    gotoxy((x1 + 46), (y1 + 19));
    cout << "]      "; 

    int xCopia = x1 + 20;
    int CopiadeCopia = xCopia;

    for (int i = 0; i <= 25; i++) {
        gotoxy(xCopia, y1 + 19);
        cout << ".";
        xCopia++;
    }
    for (int i = 0; i <= 25; i++) {
        gotoxy(CopiadeCopia, y1 + 19);
        Sleep(300);
        cout << "#";
        CopiadeCopia++;
    }

   system("cls");

}

void borrarLinea(int x, int y, int cant) {
    gotoxy(x, y);
    cout << string(cant, ' '); // Ajusta el tamaño cant dependiendo de la funcion 
    gotoxy(x, y); // Vuelve el cursor al inicio de la linea para volver a escribir centrado
}

void temporizador(int x1, int y1, int tiempo){
    gotoxy((x1+13), (y1+19));
    cout << "      ["; 
    gotoxy((x1+46), (y1+19));
    cout << "]      "; 

    int xCopia = x1+20;
    int CopiadeCopia = xCopia;

    for (int i=0; i<= 25; i++){
        gotoxy(xCopia, y1+19);
        //Sleep(200);
        cout << ".";
        xCopia++;
    }
    for (int i=0; i<= 25 ; i++){
        gotoxy(CopiadeCopia, y1+19);
        Sleep(tiempo);
        cout << "#";
        CopiadeCopia++;
    }
}

void Esquinas(int x1, int y1, int x2, int y2){
    gotoxy(x1, y1);
    cout << "+";
    gotoxy(x1, y2);
    cout << "+";
    gotoxy(x2, y1);
    cout << "+";
    gotoxy(x2, y2);
    cout << "+";
}

void ImprimirTextoCentrado(string texto, int x1, int y1, int x2, int y2){
    
    int anchoRectangulo = x2 - x1 + 1;
    int xCentrado = x1 + (anchoRectangulo - texto.length()) / 2;
    
    gotoxy(xCentrado, y1);
    cout << texto;
}

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}   // para usar coordenadas

int LeerTextoCentrado(string opc, int x1, int y1, int x2, int y2, int cant, int xEspecial){

    int anchoRectangulo = x2 - x1 + 1;
    int xCentrado = x1 + (anchoRectangulo - 4) / 2;
    int num;

    gotoxy(xCentrado, y1);
    getline(cin, opc);

   bool esNumero = true;
    for (int i = 0; i < opc.length(); i++) {
        if (!isdigit(opc[i])) {
            esNumero = false;
            break;
        }
    }

    if (!esNumero) {
        borrarLinea(x1+1, y1,cant);
        //gotoxy(x1+27,y1);
        gotoxy(xEspecial,y1);
        cout << "_________";

        //ImprimirTextoCentrado("_______",x1, y1  , x2, y2);
        ImprimirTextoCentrado("Entrada no valida. Intente nuevamente",x1, y1 + 2 , x2, y2);
        borrarLinea(x1+1, y1+3,cant);

        LeerTextoCentrado(opc, x1, y1, x2, y2, cant, xEspecial);  
    } else {
        num = stoi(opc); 
    }

    return num;
}

#endif 
