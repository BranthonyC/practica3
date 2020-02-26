
/*Motores*/
// Motor A
int ENA = 10;
int IN1 = 9;
int IN2 = 8;
// Motor B
int ENB = 5;
int IN3 = 7;
int IN4 = 6;

/*Sensor de distancia*/
int TRIG =2;
int ECO=3;
int DURACION;
int DISTANCIA;


#define S0 22
#define S1 23
#define S2 24
#define S3 25
#define sensorOut 26

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

  //Salidas de los motores Declaramos todos los pines como salidas
   pinMode (ENA, OUTPUT);
   pinMode (ENB, OUTPUT);
   pinMode (IN1, OUTPUT);
   pinMode (IN2, OUTPUT);
   pinMode (IN3, OUTPUT);
   pinMode (IN4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TRIG,HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  DURACION=pulseIn(ECO,HIGH);
  DISTANCIA=DURACION/58.2;
  Serial.println(DISTANCIA);
  
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

  if(DISTANCIA<25){
    if(esquivar){ //Condicion para que alterne el esquivar a la izquierda con esquivar hacia la derecha.
      Serial.print("Debo deterneme, girar el motor izuquierdo hacia atras y el motor derecho hacia adelante para girar a la izquierda");  
    }else{
      Serial.print("Debo deterneme, girar el motor derecho hacia atras y el motor izquierdo hacia adelante para girar a la derecha");
    }
    esquivar=!esquivar;
  }

  //Esto va fuera 
  delay(200);
  color();
}

void color(){  // Setting red filtered photodiodes to be read
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


//Metodo para los motores
void Adelante (){
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor B
}

void Atras (){
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 128); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 128); //Velocidad motor B
}

void Derecha (){
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 200); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 100); //Velocidad motor A
}

void Izquierda (){
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 50); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 150); //Velocidad motor A
}

void Parar (){
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}