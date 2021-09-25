#include <iostream>
#include <QString>
#include <QImage>
#include "imageresized.h"

using namespace std;


int main()
{

    //factorx y factory son el numero por el cual debe ser multiplicado el ancho y el alto
     //de la imagen para acercarse al valor de 16 que es el numero de filas y columnas en la
     //matriz de leds.
     //faltantex y faltantey son el numero que falta en el ancho y el alto para redonder el
     //sobremuestreo a 16.
     //ejemplo:
     //x=7, y=3
     //7*2=14-> factorx=2, faltantex=16-14=2
     //3*5=15-> factory=5, faltantey=16-15=1

     //Este algoritmo funciona de sobremuestreo funciona tomando cada uno de los pixeles de la
     //imagen y multiplicandolo por factorx+1*factory+1, por cada iteracion del algoritmo en cada pixel
     //se le resta uno a faltantex o a faltantey, cuando faltantex y faltantey llegan a 0, el pixel se
     //multiplica por factor1*factory.

     //tramox y tramoy funcionan para separar los puntos en la matriz de 16*16 que le pertenecen a cada
     //uno de los pixeles de la imagen. Una vez faltantex y faltantey llegan a 0, se empiezan a usar
     //tramoFx y tramoFy, ya que las distancias entre los espacios de cada pixel cambian.

     //contFx y contFy sirven para remplazar a los iteradores i y j cuando faltantex y faltantey llegan
     //a 0.


    //si el numero de filas es mayor que la matriz de leds


    QString filename = "../CodigoP2Qt/Images/brasil22x15";
    QImage Img(filename);

    int MatrizR[16][Img.height()],MatrizG[16][Img.height()],MatrizB[16][Img.height()];

    for(int principal = 0; principal<3; principal++)
    {
        int Ancho = Img.width(),Minimo = 0,Residuo = 0,saltador = 0;
        int Arreglo[Img.width()][Img.height()];

        Minimo = Ancho/16;
        Residuo = Ancho%16;
        int Arreglo_muestre[16][Img.height()];

        for(int i = 0; i<Img.width();i++)
        {
            for(int j = 0; j<Img.height();j++)
            {
                if(principal == 0)
                {
                    Arreglo[i][j] = Img.pixelColor(i,j).red();
                }
                else if(principal == 1)
                {
                    Arreglo[i][j] = Img.pixelColor(i,j).green();
                }
                else if(principal)
                {
                    Arreglo[i][j] = Img.pixelColor(i,j).blue();
                }
            }
        }

        for(int i = 0; i<16;i++)
        {
            for(int j = 0; j<Img.height();j++)
            {
                Arreglo_muestre[i][j] = Arreglo[i+saltador][j];
            }
            if(Residuo>0)
            {
                saltador+=Minimo;
                Residuo--;
            }
            else
            {
                saltador+=(Minimo-1);
            }
        }

        //cout<<endl<<endl;

        for(int i = 0; i<16;i++)
        {
            for(int j = 0; j<Img.height();j++)
            {
                if(principal == 0)
                {
                    MatrizR[i][j] = Arreglo_muestre[i][j];
                    //cout<<"["<<MatrizR[i][j]<<"]";
                }
                else if(principal == 1)
                {
                    MatrizG[i][j] = Arreglo_muestre[i][j];
                    //cout<<"["<<MatrizG[i][j]<<"]";
                }
                else if(principal == 2)
                {
                    MatrizB[i][j] = Arreglo_muestre[i][j];
                    //cout<<"["<<MatrizB[i][j]<<"]";
                }


            }
            //cout<<endl;

        }
        //cout<<endl<<endl;
    }


    /*
    //si el numero de columnas es mayor que la matriz de leds


    QString filename = "../CodigoP2Qt/Images/camerun19x7";
    QImage Img(filename);

    int Widht = Img.width();
    int MatrizR[Widht][16],MatrizG[Widht][16],MatrizB[Widht][16];

    for(int primero = 0; primero < 3; primero++)
    {
        int Alto = Img.height(),Minimo = 0,Residuo = 0,saltador = 0,Residuo_Aux = 0;
        int Arreglo[Img.width()][Img.height()];

        Minimo = Alto/16;
        Residuo = Alto%16;
        Residuo_Aux = Alto%16;
        int Arreglo_muestre[Img.width()][16];

        for(int i = 0; i<Img.width();i++)
        {
            for(int j = 0; j<Img.height();j++)
            {
                if(primero == 0)
                {
                    Arreglo[i][j] = Img.pixelColor(i,j).red();
                }
                else if(primero == 1)
                {
                    Arreglo[i][j] = Img.pixelColor(i,j).green();
                }
                else if(primero == 2)
                {
                     Arreglo[i][j] = Img.pixelColor(i,j).blue();
                }
            }
        }

        for(int i = 0; i<Img.width();i++)
        {
            for(int j = 0;j<16;j++)
            {
                Arreglo_muestre[i][j] = Arreglo[i][j+saltador];
                if(Residuo > 0 )
                {
                    saltador+=((Minimo+Residuo)-1);
                    Residuo--;
                }
                else
                {
                    saltador+=(Minimo-1);
                }
            }
            saltador = 0;
            Residuo = Residuo_Aux;
        }

        for(int i = 0; i<Img.width();i++)
        {
            for(int j = 0; j<16;j++)
            {
                if(primero == 0)
                {
                    MatrizR[i][j] = Arreglo_muestre[i][j];
                }
                else if(primero == 1)
                {
                    MatrizG[i][j] = Arreglo_muestre[i][j];
                }
                else if(primero == 2)
                {
                    MatrizB[i][j] = Arreglo_muestre[i][j];
                }
            }
            cout<<endl;
        }
    }*/



     //QString filename = "../CodigoP2Qt/Images/nigeria16x8";
     //QImage Img(filename);

     int x=16;
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
                 tramoy=tramoFy+(factory*contFy);//se toma el ultimo valor que tuvo tramoy en la
                 //iteracion antes de que faltantey fuera < 0 y  le suma los saltos que debe dar
                 //de acuerdo al valor final de factory
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
                     tramox=tramoFx+(factorx*contFx);//se toma el ultimo valor que tuvo tramoy en la
                     //iteracion antes de que faltantey fuera < 0 y  le suma los saltos que debe dar
                     //de acuerdo al valor final de factory
                 else
                     tramox=factorx*j;
                 if(faltantex==0){
                     tramoFx=factorx*j;
                     factorx-=1;
                     faltantex-=1;
                 }
                 for(int l=0;l<factorx;l++){
                     matrizR[tramoy][tramox]=MatrizR[j][i];
                     matrizG[tramoy][tramox]=MatrizG[j][i];
                     matrizB[tramoy][tramox]=MatrizB[j][i];
                     //if que validan para evitar la inestabilidad en Tinkercad con el 255.
                     if(matrizR[tramoy][tramox]==255)
                         matrizR[tramoy][tramox]-=1;
                     if(matrizG[tramoy][tramox]==255)
                         matrizG[tramoy][tramox]-=1;
                     if(matrizB[tramoy][tramox]==255)
                         matrizB[tramoy][tramox]-=1;
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
     //A continuación se imprimen los diferentes valores RGB para la matriz de leds en Tinkercad,
     //estos se imprimen desde la última fila hasta la primera.
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



    //ImageResized Objeto("../CodigoP2Qt/Images/estadosUnidos");
    //Objeto.Deteccion_Tipo_Muestreo();

    cout<<"hola"<<endl;

    return 0;
}
