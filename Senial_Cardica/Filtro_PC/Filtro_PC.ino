/*
 * CÓDIGO: PROYECTO 1B SISTEMAS EMBEBIDOS
 * OBJETIVO: Generar un filtro FIR pasa bajo.
 * INTEGRANTES: Flores Erik, Martinez Juan Diego.
 */

#define tamSE 74
#define tamF 21

//Llamado de señales de la otra ventana.
extern double senialE[tamSE];       //Se llama a la señal de pulso cardiaco
extern double senialFP[tamF];       //Se llama a la señal del filtro con su tamaño
double tamSS[tamSE+tamF];         //Se define el tamaño de la señal de salida y donde va a ir la señal
void convolution(double *Senial_E, double *senial_S, double *imp, int tam_SE, int tam_F);
void grafica(void);                 //Defino el metodo de graficacion
double snr[tamSE];

void setup() {
  Serial.begin(9600);
}

void loop() {
  convolution((double *)&senialE[0], (double *)&tamSS[0], (double *)&senialFP[0], (int)tamSE, (int) tamF);
  grafica();                        //Inicializo el metodo de graficacion
  ruido();
  delay(100);
}

//CREACION DE METODOS

void convolution(double *senial_E, double *senial_S, double *imp, int tam_SE, int tam_F){
  int i,j;
  for(i=0;i<(tam_SE+tam_F);i++)       //Ciclo para llenar los vectroes con 0.
  {
    senial_S[i]=0;                  //Relleno de vectores.
  }

  //CONVOLUCION
  for(i=0;i<tam_SE;i++)             //Recorrido para la señal de pulsos
  {
    for(j=0;j<tam_F;j++)            //Recorrido para la señal filtros     
    {
      senial_S[i+j]=senial_S[i+j]+senial_E[i]*imp[j];   //Se realiza la convolucion.
    }
  }
}


void ruido(){
  double ruido1 [tamSE];
  double ruido2 [tamSE];
  for(int i=0;i<tamSE;i++){
    ruido1[i]=pow(senialE[i],2);
    ruido2[i]=pow((senialE[i]-tamSS[i]),2);
    snr[i]=10*log(ruido1[i]/ruido2[i]); 
    }
  }


//Graficacion de la señal
void grafica (void){
  int i;
  for(i=0;i<tamSE;i++)
  {
    Serial.print(senialE[i]+1000);     //1000 para visualizacion
    Serial.print(",");
    Serial.print(tamSS[i]+500);        //Se imprime la señal final
    Serial.print(",");
    Serial.println(snr[i]-10);         //Se imprime la señal SNR
    delay(5);
  }
}
