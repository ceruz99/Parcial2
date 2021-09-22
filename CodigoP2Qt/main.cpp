#include <iostream>
#include <QString>
#include <QImage>

using namespace std;

int main()
{
    QString filename = "../untitled/Imagenes/Japon_G";
    QImage Img(filename);

    int Cntidad_c = 20,Cntidad_f = 20,filas_sumar = Img.width()/20,Columnas_sumar = Img.height()/20;
    long long unsigned int Arreglo[Img.width()][Img.height()];
    long long unsigned int cont_1 = 0, cont_2 = 0,suma = 0,cont_4 = 0,contador_suma = 0;
    long long unsigned int cont_3 = Columnas_sumar;


    for(int i = 0; i<Img.width(); ++i)
    {
        for(int j = 0; j<Img.height(); ++j)
        {
            Arreglo[i][j] = Img.pixelColor(i,j).green();
            //cout<<"["<<Img.pixelColor(i,j).red()<<"]";
        }
        //cout<<endl;
    }

    cout<<endl<<"Algoritmo de la media(especialmente para matrices cuadradas o pares)"<<endl;

    for(int t = 0; t<Cntidad_f;t++)
    {
        for(int k = 0; k<Cntidad_c;k++)
        {
            for( long long unsigned i = cont_2; i<cont_2+filas_sumar; i++)//el numero que se suma es el numero de filas que se estas sumando
            {
                for( long long unsigned j = cont_1; j < cont_3*(cont_4+1); j++)//cont_3 es el numero de columnas de el cuadro de datos para sacar la media y el cont_4 nos dara el limite hasta donde va el recuadro o area de datos para sacarla media
                {
                    suma+=Arreglo[i][j];
                    contador_suma++;
                }
            }
            suma = suma/contador_suma;//el numero de division es la suma de datos en el recuadro y sacar la media
            if(suma >= 100)
            {
                cout<<"["<<suma<<"]";
            }
            else if(suma >= 10)
            {
                cout<<"[0"<<suma<<"]";
            }
            else
            {
                cout<<"[00"<<suma<<"]";
            }
            cont_1 = Columnas_sumar*(cont_4+1);//el numero que multiplica la expresion (cont_4+1) es el desplazamiento de columnas
            cont_4++;
            suma = 0;
            contador_suma = 0;
        }
        cont_2+=filas_sumar;//el numero de filas que se desplaza
        cont_4 = 0;
        cont_1 =0;
        cout<<endl;
        }
    return 0;
}
