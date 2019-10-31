#include <Ultrasonic.h> // Sensor ultrassom
#include <LiquidCrystal_I2C.h> // Biblioteca do LCD
#include <Wire.h> // Biblioteca para o funcionamento do LCD

//Define os pinos para o echo e trigger
#define echo 6
#define trigger 7

Ultrasonic ultrassom(trigger, echo); //Inicializa o sensor nos pinos definidos acima
LiquidCrystal_I2C Display(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

byte a[8]= {B00110,B01001,B00110,B00000,B00000,B00000,B00000,B00000,}; // Array que desenha '°' no display.

int contadorDePessoas = 0;
bool passou = false;
long distancia;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  // Display
  Display.begin(16,2);
  Display.createChar(1, a); 
  Display.setCursor(2,0); // Coloca o cursor na coluna 7, linha 1
  Display.write(1); // Escreve o simbolo de grau 
}

void loop() {
  
  // Escreve no Display
  Display.setBacklight(HIGH);
  Display.setCursor(1,0);
  Display.print("N");
  Display.setCursor(3,0);
  Display.print(" de pessoas:");
  Display.setCursor(7,1);
  Display.print(contadorDePessoas);

  // Sensor Ultrassom
  long microsec = ultrassom.timing();
  distancia = ultrassom.convert(microsec, Ultrasonic::CM); // ultrassom.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC)
  // distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC)
  Serial.print(distancia); //imprime o valor da variável distancia
  Serial.println("cm");
  delay(200);

  // Verifica se a porta está fechada ou aberta
  if(distancia >= 13 && distancia <= 110){
    // Verifica se tem alguem passando
    if(distancia >= 25 && distancia <= 65){
      // A variavel passou vira 'true' para evitar que continue contando quando alguem estiver parado em frente ao sensor
      passou = true;
    }else{ // Entra no else quando não estiver ninguem passando
      if(passou == true){
        // Se a passou for 'true' ele incrementa no contador e muda o estado de passou para 'false'
        contadorDePessoas++;
        passou = false;
      }
     }
  }

  // Repete o codigo.
}
