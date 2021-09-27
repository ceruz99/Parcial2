#ifndef IMAGERESIZED_H
#define IMAGERESIZED_H

#include <QImage>
#include <QDebug>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class ImageResized
{
private:
    string Filename;
    QImage Img;
    ofstream Archivo;

    void Sobremuestreo();
    void submuestreo();
    void EnvioDatos(short int MatrizR[][16],short int MatrizG[][16],short int MatrizB[][16]);

    void sobresubFilas();
    void sobresubColumn();

public:    
    ImageResized(string Nombre);

    void Deteccion_Tipo_Muestreo();


};

#endif // IMAGERESIZED_H
