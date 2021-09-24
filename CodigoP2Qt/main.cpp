#include <iostream>
#include <QString>
#include <QImage>

using namespace std;

int main()
{
    QString filename = "../CodigoP2Qt/Images/estadosUnidos.png";
    QImage Img(filename);

    int x=Img.width();
    int y=Img.height();
    int factorx=1,factory=1,faltantex=0,faltantey=0, tramox=0, tramoy=0, tramoFx=0, tramoFy=0;
    int contFx=0,contFy=0;
    short int matrizR[16][16], matrizG[16][16], matrizB[16][16];

    while (x*factorx<=16) {
        factorx+=1;
    }
    //factorx-=1;
    while (y*factory<=16) {
        factory+=1;
    }
    //factory-=1;
    faltantex=16-(x*(factorx-1));
    faltantey=16-(y*(factory-1));

    for(int i=0;i<y;i++){
        if(faltantey<0)
            contFy+=1;
        contFx=0;
        for(int j=0;j<x;j++){
            if(faltantey<0)
                tramoy=tramoFy+(factory*contFy);
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
                    tramox=tramoFx+(factorx*contFx);
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
    cout<<"{";
    for(int i=0;i<16;i++){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<matrizR[i][j];
            if(j!=15)
                cout<<",";
        }
        if(i==15)
            cout<<"}";
        else
            cout<<"},";
    }
    cout<<"}";
    cout<<endl;
    cout<<endl;

    cout<<"{";
    for(int i=0;i<16;i++){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<matrizG[i][j];
            if(j!=15)
                cout<<",";
        }
        if(i==15)
            cout<<"}";
        else
            cout<<"},";
    }
    cout<<"}";
    cout<<endl;
    cout<<endl;

    cout<<"{";
    for(int i=0;i<16;i++){
        cout<<"{";
        for(int j=0;j<16;j++){
            cout<<matrizB[i][j];
            if(j!=15)
                cout<<",";
        }
        if(i==15)
            cout<<"}";
        else
            cout<<"},";
    }
    cout<<"}";
    cout<<endl;
    cout<<endl;

    return 0;
}
