#include <Adafruit_NeoPixel.h>

int contador = 0;
const int PinDato = 2;
const int N_Leds = 16*16;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_Leds, PinDato, NEO_GRB + NEO_KHZ400);

byte Arreglo_tridimesional[3][16][16]=
{
	{
      {186,192,199,203,206,212,148,17,23,29,43,101,174,191,182,175},{195,201,208,213,216,222,158,27,26,32,48,104,178,195,186,178,},{203,208,216,221,225,231,167,36,32,38,53,111,183,201,191,186},{205,209,216,222,227,235,170,39,34,42,57,114,187,205,196,190},{205,209,216,223,228,235,170,39,36,44,60,116,191,209,199,191},{209,211,218,224,229,238,172,38,36,44,60,118,190,210,201,193},{212,214,219,225,231,238,172,39,38,46,61,119,193,210,201,194},{213,214,219,224,230,237,170,37,38,46,61,119,193,210,201,195},{208,215,221,224,230,236,167,38,38,46,61,119,192,207,196,188},{207,214,220,224,230,234,166,37,38,46,61,117,188,204,192,184},{209,216,220,224,229,235,166,36,38,43,59,114,185,201,188,180},{209,216,221,224,230,234,164,33,36,43,57,112,182,197,184,175},{209,217,222,225,230,233,163,32,35,42,55,109,180,193,180,173},{207,215,220,223,228,231,161,28,33,38,51,106,175,190,178,169},{205,212,217,221,226,227,155,23,29,35,47,102,171,186,173,166},{202,210,214,217,222,224,151,18,27,31,45,98,169,184,171,163}
    },
	{
      {170,176,183,186,187,200,150,31,43,39,26,27,17,4,15,19},{179,185,192,196,197,210,160,41,46,42,28,30,21,8,19,22},{187,192,200,204,206,219,169,50,50,46,32,35,24,11,22,26},{189,193,200,205,208,221,170,50,52,48,34,36,27,13,25,28},{189,193,199,203,207,221,170,48,52,48,34,36,26,13,24,27},{193,195,201,204,208,221,170,47,52,48,34,35,25,12,23,27},{195,197,202,205,208,221,170,45,52,48,34,35,26,12,23,26},{196,197,202,204,207,220,168,43,52,48,34,35,26,12,23,27},{191,198,201,202,207,217,163,44,52,48,34,35,25,9,18,22},{190,197,200,202,207,217,164,43,52,48,34,34,23,8,17,20},{189,196,200,202,206,216,162,42,52,47,33,34,22,7,17,18},{189,196,201,202,207,217,162,42,52,49,34,34,22,7,15,18},{187,195,200,203,207,216,161,41,53,50,35,35,23,8,16,17},{185,193,198,201,205,214,159,39,53,48,34,34,23,6,15,18},{181,188,195,198,201,210,155,34,49,45,32,33,21,5,15,16},{178,186,192,195,199,207,151,32,47,43,30,30,19,5,13,16}
    },
	{
      {0,2,9,10,7,66,111,60,116,124,94,76,44,13,7,4},{5,11,18,20,17,76,121,70,119,127,97,79,48,17,11,7},{13,18,26,28,26,85,130,79,124,131,101,84,52,21,15,12},{15,19,26,29,28,88,132,80,126,134,104,86,55,24,18,15},{15,19,25,28,28,88,132,79,127,135,105,87,56,25,19,15},{19,21,27,29,29,89,132,78,127,135,105,87,55,25,19,15},{21,23,28,30,30,89,132,77,127,135,105,87,56,25,19,15},{22,23,28,29,29,88,130,75,127,135,105,87,56,25,19,16},{17,24,28,28,29,86,126,76,127,135,105,87,55,22,14,10},{16,23,27,28,29,85,126,75,127,135,105,86,53,20,12,8},{16,23,27,28,28,85,125,74,127,134,104,85,51,18,10,5},{16,23,28,28,29,85,124,73,127,135,104,84,50,17,8,3},{15,23,28,29,29,84,123,72,127,135,104,84,50,16,7,2},{13,21,26,27,27,82,121,69,126,133,102,82,48,14,6,1},{10,17,23,24,23,78,117,64,122,130,99,80,46,12,4,0},{7,15,20,21,21,75,113,61,120,127,97,77,44,11,2,0}
    }
};


void setup()
{  
  strip.begin();  
  for(int RGB = 0; RGB < 1; RGB++)
  {
		for(int Filas = 0; Filas < 16;Filas++)
        {
            for(int Columnas = 0; Columnas < 16;Columnas++)
            {                
				strip.setPixelColor(contador,Arreglo_tridimesional[RGB][Filas][Columnas],Arreglo_tridimesional[RGB+1][Filas][Columnas],Arreglo_tridimesional[RGB+2][Filas][Columnas]);
            	contador++;
            }
        }
    }
    strip.show();
}

void loop(){}

