#include <iostream>
#include <string>
#include <QImage>
#include "imageresized.h"

//Se define la macro que representa la ruta donde se encuentra la imagen
#define PATH_IMG "../CodigoP2Qt/Images/"
//Se define la macro para la extension
#define EXTENSION ".jpg"


using namespace std;

int main(){
    bool trabajando=true;
    while(trabajando==true){
        cout<<"Ingrese una de las opciones:"<<endl;
        cout<<"1.Redimensionar una nueva imagen."<<endl;
        cout<<"2.Salir del programa."<<endl;
        short int opcion=0;
        cin>>opcion;
        system("cls");
        switch (opcion) {
        case 1:{
            string nombre;
            cout<<"Ingrese el nombre de la imagen que desea redimensionar para la matriz de leds: ";
            cin.ignore();
            getline(cin,nombre);
            nombre=PATH_IMG+nombre+EXTENSION;
            system("cls");
            ImageResized imagen(nombre);
            imagen.Deteccion_Tipo_Muestreo();
            break;
        }
        case 2:{
            trabajando=false;
            break;
        }
        default:{
            break;
        }
        }
    }
    return 0;
}
