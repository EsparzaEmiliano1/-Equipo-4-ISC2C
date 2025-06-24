//Lectura en archivos de texto - fscanf

#include <iostream>
using namespace std;

int main(){
	//1.Declarar el archivo
	FILE *archMed;  //variable para manejar el archivo
	int codMed;
	float preMed;
	char *nomMed = new char[20],resp;
	
	//2.Abrir el archivo de texto en el Disco Duro
	archMed = fopen("farmacia.txt","r");
	
	//Validar la correcta apertura del archivo
	if (!archMed){
		cout << "Error de apertura! \n";
		return 1;
	}
	
	//3.Leer del archivo y enviar a pantalla los datos
	while(!feof(archMed)){
		fscanf(archMed,"%d\t%s\t%f\n",&codMed,nomMed,&preMed);
		cout << codMed << "\t" << nomMed << "\t" << preMed << endl;
	}	
	
	//4.Cerrar archivo
	fclose(archMed);
}

/* OTRAS FORMAS DE LEER EL ARCHIVO

	while(fscanf(archMed,"%d\t%s\t%f\n",&codMed,nomMed,&preMed)){
		cout << codMed << "\t" << nomMed << "\t" << preMed << endl;
	}	
	
	Con el ciclo for se debe tener primero el tamaño del archivo
	for(int i=0; i<tamArch; i++){
		fscanf(archMed,"%d\t%s\t%f\n",&codMed,nomMed,&preMed);
		cout << codMed << "\t" << nomMed << "\t" << preMed << endl;
	}
*/

	
	
