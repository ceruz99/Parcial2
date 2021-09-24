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


    cout<<"DESDE AQUI EMPIEZA EL ALGOTIRMO DE SUBMUESTREO"<<endl;

    QString filename_2 = "../untitled/Imagenes/Minion";
    QImage Img_2(filename_2);

    //FALTA AGREGAR DOCUMENTACION DEL CODIGO

    //Variables que se necesitaran para el algoritmo
    int Cntidad_c = 16,Cntidad_f = 16,filas_sumar = Img_2.width()/16,Columnas_sumar = Img_2.height()/16,residuo_1 = Img_2.height()%16,residuo_2 = Img_2.width()%16;
    int cont_1 = 0, cont_2 = 0,cont_3 = 0,cont_4 = 0,suma = 0,contador_suma = 0,flag = 1, flag_2 = 1;

    //Se crea los arreglos para el almacenamiento de datos y se les da la cantidad de memoria
    int ArregloAux[16][16],ArregloOriginal[16][16];
    int **ArregloD;
    ArregloD = new int*[Img_2.width()];

    for(int i = 0;i<Img_2.width();i++)
    {
       ArregloD[i] = new int[Img_2.height()];
    }

    for(int i = 0; i<Img_2.width(); ++i)
    {
        for(int j = 0; j<Img_2.height(); ++j)
        {
            *(*(ArregloD+i)+j) = Img_2.pixelColor(i,j).blue();
        }
    }


    //Explicacion --> ...
    if(residuo_2 > 0)
    {
        cont_4++;
    }
    if(residuo_1 > 0)
    {
        cont_3++;
    }


    for(int t = 0; t<Cntidad_f;t++)
    {
        for(int k = 0; k<Cntidad_c;k++)
        {
            for(int  i = cont_2; i<cont_4+filas_sumar; i++)
            {
                for(int  j = cont_1; j < cont_3+Columnas_sumar; j++)
                {
                    suma+=*(*(ArregloD+i)+j);
                    contador_suma++;
                }
            }
            if(contador_suma > 0)
            {
                ArregloAux[t][k] = suma/contador_suma;
            }
            if(residuo_1-1 == 0 && k+1 == Cntidad_c)
            {
                cont_1+= (Columnas_sumar+flag);
                cont_3+= (Columnas_sumar+flag);
                suma = 0;
                contador_suma = 0;
                residuo_1--;
            }
            else if(residuo_1-1 == 0 && k+1 != Cntidad_c)
            {
                cont_1+= (Columnas_sumar+flag);
                cont_3+= Columnas_sumar;
                suma = 0;
                contador_suma = 0;
                residuo_1--;
            }
            else if(residuo_1 > 0 && ((residuo_1-1)!=0))
            {
                cont_1+= (Columnas_sumar+flag);
                cont_3+= (Columnas_sumar+flag);
                suma = 0;
                contador_suma = 0;
                residuo_1--;
            }
            else
            {
                cont_1+= Columnas_sumar;
                cont_3+= Columnas_sumar;
                suma = 0;
                contador_suma = 0;
            }
        }
        if(residuo_1 > 0 )
        {
            cont_3 = 1;
        }
        else
        {
            cont_3 = 0;
        }

        if(residuo_2 > 0 && residuo_2-1 != 0)
        {
            cont_2+=(filas_sumar+flag_2);
            cont_4+=(filas_sumar+flag_2);
            cont_1 =0;
            residuo_2--;
        }
        else if(residuo_2-1 == 0)
        {
            cont_2+=(filas_sumar+flag_2);
            cont_4+=(filas_sumar);
            cont_1 =0;
            residuo_2--;
        }
        else
        {
            cont_2+=filas_sumar;
            cont_4+=filas_sumar;
            cont_1 =0;
        }
    }

    cout<<endl<<endl;
    for(int i = 0; i <16; i++)
    {
        for(int j = 0; j <16; j++)
        {
            ArregloOriginal[i][j] = ArregloAux[j][i];
            //cout<<"["<<ArregloOriginal[i][j]<<"]";
        }
        //cout<<endl;
    }

    cout<<endl<<endl;


    for(int i=15;i>-1;i--){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<ArregloOriginal[i][j];
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

    delete [] ArregloD;


    return 0;
}
