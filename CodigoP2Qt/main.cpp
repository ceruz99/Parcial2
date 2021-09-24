#include <iostream>
#include <QString>
#include <QImage>

using namespace std;


int main()
{
    /*factorx y factory son el numero por el cual debe ser multiplicado el ancho y el alto
    de la imagen para acercarse al valor de 16 que es el numero de filas y columnas en la
    matriz de leds.
    faltantex y faltantey son el numero que falta en el ancho y el alto para redonder el
    sobremuestreo a 16.
    ejemplo:
    x=7, y=3
    7*2=14-> factorx=2, faltantex=16-14=2
    3*5=15-> factory=5, faltantey=16-15=1

    Este algoritmo funciona de sobremuestreo funciona tomando cada uno de los pixeles de la
    imagen y multiplicandolo por factorx+1*factory+1, por cada iteracion del algoritmo en cada pixel
    se le resta uno a faltantex o a faltantey, cuando faltantex y faltantey llegan a 0, el pixel se
    multiplica por factor1*factory.

    tramox y tramoy funcionan para separar los puntos en la matriz de 16*16 que le pertenecen a cada
    uno de los pixeles de la imagen. Una vez faltantex y faltantey llegan a 0, se empiezan a usar
    tramoFx y tramoFy, ya que las distancias entre los espacios de cada pixel cambian.

    contFx y contFy sirven para remplazar a los iteradores i y j cuando faltantex y faltantey llegan
    a 0.
    */

    QString filename = "../CodigoP2Qt/Images/estadosUnidos";
    QImage Img(filename);

    int x=Img.width();
    int y=Img.height();
    int factorx=1,factory=1,faltantex=0,faltantey=0, tramox=0, tramoy=0, tramoFx=0, tramoFy=0;
    int contFx=0,contFy=0;
    short int matrizR[16][16], matrizG[16][16], matrizB[16][16];

    while (x*factorx<=16) {
        factorx+=1;
    }
    while (y*factory<=16) {
        factory+=1;
    }
    faltantex=16-(x*(factorx-1));
    faltantey=16-(y*(factory-1));

    for(int i=0;i<y;i++){//se recorre primero el ancho de la imagen, y luego el alto...
        if(faltantey<0)
            contFy+=1;
        contFx=0;
        for(int j=0;j<x;j++){
            if(faltantey<0)
                tramoy=tramoFy+(factory*contFy);/*se toma el ultimo valor que tuvo tramoy en la
                iteracion antes de que faltantey fuera < 0 y  le suma los saltos que debe dar
                de acuerdo al valor final de factory*/
            else
                tramoy=(factory)*i;
            if(faltantey==0){
                tramoFy=(factory)*i;
                factory-=1;
                faltantey-=1;
            }
            if(faltantex<0)
                contFx+=1;
            for(int k=0;k<factory;k++){
                if(faltantex<0)
                    tramox=tramoFx+(factorx*contFx);/*se toma el ultimo valor que tuvo tramoy en la
                    iteracion antes de que faltantey fuera < 0 y  le suma los saltos que debe dar
                    de acuerdo al valor final de factory*/
                else
                    tramox=factorx*j;
                if(faltantex==0){
                    tramoFx=factorx*j;
                    factorx-=1;
                    faltantex-=1;
                }
                for(int l=0;l<factorx;l++){
                    matrizR[tramoy][tramox]=Img.pixelColor(j,i).red();
                    matrizG[tramoy][tramox]=Img.pixelColor(j,i).green();
                    matrizB[tramoy][tramox]=Img.pixelColor(j,i).blue();
                    tramox+=1;
                }
                tramoy+=1;
            }
            faltantex-=1;
        }
        faltantey-=1;
        faltantex=16-(x*factorx);
        factorx+=1;
    }
    /*A continuación se imprimen los diferentes valores RGB para la matriz de leds en Tinkercad,
    estos se imprimen desde la última fila hasta la primera.*/
    for(int i=15;i>-1;i--){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<matrizR[i][j];
            if(j!=15)
                cout<<",";
        }
        if(i==0)
            cout<<"}";
        else
            cout<<"},";
    }
    cout<<endl;
    cout<<endl;

    for(int i=15;i>-1;i--){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<matrizG[i][j];
            if(j!=15)
                cout<<",";
        }
        if(i==0)
            cout<<"}";
        else
            cout<<"},";
    }
    cout<<endl;
    cout<<endl;

    for(int i=15;i>-1;i--){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<matrizB[i][j];
            if(j!=15)
                cout<<",";
        }
        if(i==0)
            cout<<"}";
        else
            cout<<"},";
    }
    cout<<endl;
    cout<<endl;

    return 0;
}
