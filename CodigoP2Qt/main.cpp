#include <iostream>
#include <QString>
#include <QImage>

using namespace std;

int main()
{
    QString filename = "../CodigoP2Qt/Images/japon.png";
    QImage Img(filename);

    int x=Img.width();
    int y=Img.height();
    int factorx=1,factory=1,faltantex=0,faltantey=0, tramox=0, tramoy=0;
    short int matrizR[20][20], matrizG[20][20], matrizB[20][20];
    while (x*factorx<=20) {
        factorx+=1;
    }
    //factorx-=1;
    while (y*factory<=20) {
        factory+=1;
    }
    //factory-=1;
    faltantex=20-(x*factorx-1);
    faltantey=20-(y*factory-1);

    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(faltantey==0){
                factory-=1;
                faltantey-=1;
            }
            tramoy=(factory)*i;
            for(int k=0;k<factory;k++){
                if(faltantex==0){
                    factorx-=1;
                    faltantex-=1;
                }
                tramox=factorx*j;
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
        faltantex=20-(x*factorx);
        factorx+=1;
    }

    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            cout<<"["<<matrizR[i][j]<<"]";
        }
        cout<<endl;
    }
    return 0;
}
