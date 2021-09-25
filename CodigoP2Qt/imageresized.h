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
    string Filename;
    QImage Img;
    ofstream Archivo;

public:    
    ImageResized();
    ImageResized(string Nombre);

    void PonerNombre(string Nombre);
    string ObtenerNombre();

    void Deteccion_Tipo_Muestreo();

    void Sobremuestreo();
    void submuestreo();
    void EnvioDatos(short int MatrizR[][16],short int MatrizG[][16],short int MatrizB[][16]);
};

#endif // IMAGERESIZED_H
