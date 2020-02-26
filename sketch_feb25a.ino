/*Sensor de distancia*/
int TRIG =2;
int ECO=3;
int DURACION;
int DISTANCIA;

/*Sensor de colores*/
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int actual_color=0;

int frequency = 0;

//Motores
bool esquivar=false;



void setup() {
  //Configuración general
  Serial.begin(9600);
  //Configuración sensor de distancia
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);

  //Configuración sensor de colores
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 100%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);  

}

void loop() {
  // put your main code here, to run repeatedly:

  switch(actual_color){
    case 1:
      Serial.print("digamos que es color rojo, debo moverme hacia adelante mientras muevo el motor de la barredora");
      break;
    case 2: 
      Serial.print("Digamos que es color Azul debo cambiar a modo manual");
      break;
    case 3:
      Serial.print("Digamos que hay ausencia de color Debo retroceder ya que me encontre con una grada");
      break;
    default:
      break;
  }
  
  digitalWrite(TRIG,HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  DURACION=pulseIn(ECO,HIGH);
  DISTANCIA=DURACION/58.2;
  Serial.println(DISTANCIA);

  if(DISTANCIA<25){
    if(esquivar){ //Condicion para que alterne el esquivar a la izquierda con esquivar hacia la derecha.
      Serial.print("Debo deterneme, girar el motor izuquierdo hacia atras y el motor derecho hacia adelante para girar a la izquierda");  
    }else{
      Serial.print("Debo deterneme, girar el motor derecho hacia atras y el motor izquierdo hacia adelante para girar a la derecha");
    }
    esquivar=!esquivar;
  }
  delay(200);
  color();
}

void color()  
{    
  /*digitalWrite(S2, LOW);  
  digitalWrite(S3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);  
  digitalWrite(S3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);  
  digitalWrite(S2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);  */
   // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30,90,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,70,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");

  //Dependiendo de la frecuencia decidiremos asignar un color.

}
