#include <SoftwareSerial.h> //colocar en comentarios si vas usar el potenciometro
#include <TimerOne.h>              // Incluir Librería TimerOne 
SoftwareSerial BT(A0,A1);             //este igual en comentarios colocar        
volatile int i=0;                  // Variable usada por el contador.
volatile boolean cruce_cero=0;     // variable que actúa como switch al detectar cruce por cero.
int Triac = 3;                     // Salida conectada al optoacoplador MOC 3021.
int dim = 83;                      // Controla la intensidad de iluminación, 0 = ON ; 83 = OFF                
int T_int = 100;                   // Tiempo en el cual se producen la interrupciones en us. 
char dato2;
String comando;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);   
  pinMode(Triac, OUTPUT);                               // Configurar como salida.
  attachInterrupt(0, deteccion_Cruce_cero, RISING);    // Realiza una interrupción al detectar el crice por cero en el pin 2
  Timer1.initialize(T_int);                            //Inicializa la librería con el tiempo deseado.
  Timer1.attachInterrupt(Dimer, T_int);                // En cada interrupción ejecuta el codigo Dimer. 
}

void deteccion_Cruce_cero() 
{                                                      // Si existe un cruce por cero entonces la variable "cruce_cero" cambia a TRUE...
  cruce_cero = true;                                   //...reseteando el valor de "i", y colocando la salida conectada al Triac en estado...
  i=0;                                                 // ...bajo.
  digitalWrite(Triac, LOW);
}                                 

void Dimer() 
{                   
  if(cruce_cero == true) {                             // Al detectarse el cruce por cero inicia a correr un tiempo t = T_int*dim, en el cual...
    if(i>=dim) {                                       // ... el triac se dispara y empieza a conducir.
      digitalWrite(Triac, HIGH);                      
      i=0;                                              // Reseteo i.
      cruce_cero=false;                                   
    } 
    else {
      i++;                     
}}}     

void LeerPuertoSerie() {
  comando = "";
  while(BT.available()){
    delay(1);
    if (BT.available() > 0){
      dato2 = BT.read();
      comando += dato2;
    }
  }
}                                 
void loop() 
{  
    /*LeerPuertoSerie();
  if (comando.length() > 0){
    if ((comando.toInt()>=10)&&(comando.toInt()<=80))
    dim=comando.toInt();
    Serial.println(dim);
    //comando.parse();
    delay(1);
  }*/
  
    /////dimmer con potenciometro////
    /*int dato = analogRead(A0);//PIN 23
    if(dato>=12)
      {
        dato=dato/12;
        dim = dato;
        Serial.println(dim);
        delay(10);
      }*/
    ///////efecto Atenuacion///////   
    /*dim=83;
    for(int x=0;x<dim;dim--)
    delay(60);
    
    dim=0;
    for(int x=83;x>dim;dim++)
    delay(60);
*/  
}
