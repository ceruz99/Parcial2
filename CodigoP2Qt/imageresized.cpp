#include "imageresized.h"

ImageResized::ImageResized()
{

}

ImageResized::ImageResized(string Nombre)
{
    Filename = Nombre;
}

void ImageResized::PonerNombre(string Nombre)
{
    Filename = Nombre;
}

string ImageResized::ObtenerNombre()
{
    return Filename;
}

void ImageResized::Deteccion_Tipo_Muestreo()
{
    QImage Imagen(Filename.c_str());

    int Ancho = Imagen.width(), Alto = Imagen.height();

    if(Ancho > 16 && Alto > 16)
    {
        qDebug()<<"Se entra al submuestreo \n";
        submuestreo();
    }
    else if(Ancho < 16 && Alto < 16)
    {
        qDebug()<<"Se entra al sobremuestreo\n";
        Sobremuestreo();
    }
    else if(Ancho > 16 && Alto <16 ){
        sobresubFilas();
    }
    else if(Ancho < 16 && Alto > 16){
        sobresubColumn();
    }

}

void ImageResized::Sobremuestreo()
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

    QImage Img(Filename.c_str());

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
                    matrizR[tramoy][tramox]=Img.pixelColor(j,i).red();
                    matrizG[tramoy][tramox]=Img.pixelColor(j,i).green();
                    matrizB[tramoy][tramox]=Img.pixelColor(j,i).blue();
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

    EnvioDatos(matrizR,matrizG,matrizB);

}

void ImageResized::submuestreo()
{
    QImage Img_2(Filename.c_str());

    //FALTA AGREGAR DOCUMENTACION DEL CODIGO

    int short MatrizR[16][16],MatrizG[16][16],MatrizB[16][16];

    for(int primario = 0; primario<3;primario++ )
    {
        //Variables que se necesitaran para el algoritmo
        int Cntidad_c = 16,Cntidad_f = 16,filas_sumar = Img_2.width()/16,Columnas_sumar = Img_2.height()/16,residuo_1 = Img_2.height()%16,residuo_2 = Img_2.width()%16;
        int cont_1 = 0, cont_2 = 0,cont_3 = 0,cont_4 = 0,suma = 0,contador_suma = 0,flag = 1, flag_2 = 1;

        //Se crea los arreglos para el almacenamiento de datos y se les da la cantidad de memoria
        int ArregloAux[16][16];
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
                if(primario  == 0)
                {
                    *(*(ArregloD+i)+j) = Img_2.pixelColor(i,j).red();
                }
                else if(primario  == 1)
                {
                    *(*(ArregloD+i)+j) = Img_2.pixelColor(i,j).green();
                }
                if(primario  == 2)
                {
                    *(*(ArregloD+i)+j) = Img_2.pixelColor(i,j).blue();
                }
            }
        }


        //Explicacion --> ...
        if(residuo_2 > 0)
        {
            cont_4++;
        }

        for(int t = 0; t<Cntidad_f;t++)
        {
            residuo_1 = (Img.height()%16);
            if(residuo_1 > 0)
            {
                cont_3++;
            }
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

        for(int i = 0; i <16; i++)
        {
            for(int j = 0; j <16; j++)
            {
                if(primario == 0)
                {
                    MatrizR[i][j] = ArregloAux[j][i];
                }
                else if(primario == 1)
                {
                    MatrizG[i][j] = ArregloAux[j][i];
                }
                else if(primario == 2)
                {
                     MatrizB[i][j] = ArregloAux[j][i];
                }

            }
        }


        delete [] ArregloD;
    }

    EnvioDatos(MatrizR,MatrizG,MatrizB);
}

void ImageResized::EnvioDatos(short int MatrizR[][16],short int MatrizG[][16],short int MatrizB[][16])
{

    Archivo.open("../CodigoP2Qt/Datos.txt",ios::out);

    if(Archivo.fail())
    {
        cout<<"Alerta Error \n";
    }

    Archivo<<"byte Arreglo_tridimesional[3][16][16]="<<endl<<"{"<<endl<<"    {"<<endl<<"        ";

    for(int i=15;i>-1;i--)
    {
       Archivo<<"{";
        for(int j=0;j<16;j++)
        {
            Archivo<<MatrizR[i][j];
            if(j!=15)
            {
                Archivo<<",";
            }
        }
        if(i==0)
        {
            Archivo<<"}";
        }
        else
        {
            Archivo<<"},";
        }
    }
    Archivo<<endl<<"    },"<<endl<<"    {"<<endl;
    for(int i=15;i>-1;i--)
    {
       Archivo<<"{";
        for(int j=0;j<16;j++)
        {
            Archivo<<MatrizG[i][j];
            if(j!=15)
            {
                Archivo<<",";
            }
        }
        if(i==0)
        {
            Archivo<<"}";
        }
        else
        {
            Archivo<<"},";
        }
    }
    Archivo<<endl<<"    },"<<endl<<"    {"<<endl;
    for(int i=15;i>-1;i--)
    {
       Archivo<<"{";
        for(int j=0;j<16;j++)
        {
            Archivo<<MatrizB[i][j];
            if(j!=15)
            {
                Archivo<<",";
            }
        }
        if(i==0)
        {
            Archivo<<"}";
        }
        else
        {
            Archivo<<"},";
        }
    }
    Archivo<<endl<<"    }"<<endl<<"};"<<endl;

    Archivo.close();
}

void ImageResized::sobresubFilas(){
    QImage Img(Filename.c_str());

    short int MatrizR[16][Img.height()],MatrizG[16][Img.height()],MatrizB[16][Img.height()];

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

        for(int i = 0; i<16;i++)
        {
            for(int j = 0; j<Img.height();j++)
            {
                if(principal == 0)
                {
                    MatrizR[i][j] = Arreglo_muestre[i][j];
                }
                else if(principal == 1)
                {
                    MatrizG[i][j] = Arreglo_muestre[i][j];
                }
                else if(principal == 2)
                {
                    MatrizB[i][j] = Arreglo_muestre[i][j];
                }


            }
        }
    }
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
    /*
    A continuación se imprimen los diferentes valores RGB para la matriz de leds en Tinkercad,
    estos se imprimen desde la última fila hasta la primera.
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
    cout<<endl;*/
    EnvioDatos(matrizR,matrizG,matrizB);
}

void ImageResized::sobresubColumn()
{
    QImage Img(Filename.c_str());

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
    }
    int x=Img.width();
    int y=16;
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
}
