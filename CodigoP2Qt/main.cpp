#include <iostream>
#include <QString>
#include <QImage>
#include "imageresized.h"

using namespace std;


int main()
{

    ImageResized Objeto("../CodigoP2Qt/Images/estadosUnidos");
    Objeto.Deteccion_Tipo_Muestreo();

    return 0;
}
