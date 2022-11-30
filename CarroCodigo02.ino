#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <VarSpeedServo.h>
#include <Dabble.h>



SoftwareSerial DebugSerial(2, 3); // rx e tx
VarSpeedServo meuservo;
const int motorA1 = 12;
const int motorA2 = 10;
const int motorB1 = 13;
const int motorB2 = 11;
int servoPos = 93; //posiciona servo em alinhamento inicial da barra de direção

void setup() {
  Serial.begin(250000);
  Dabble.begin(38400);  
  meuservo.attach(5);

 pinMode(motorA1, OUTPUT);
 pinMode(motorA2, OUTPUT);
 pinMode(motorB1, OUTPUT);
 pinMode(motorB2, OUTPUT);
}

void loop() {
  
  Dabble.processInput();// leitura do Input enviado pelo aplicativo
 
  if (GamePad.isUpPressed()){ // mover para frente
    Serial.print("UP");
    moveFrente();
  }

  else if (GamePad.isDownPressed()){ // mover para atrás
    Serial.print("DOWN");
    moveAtras();
   }

  else  if (GamePad.isLeftPressed()){ // virar servo/direção para esquerda
    Serial.print("ESQUERDA");
    viraEsquerda(servoPos);
  }

  else  if (GamePad.isRightPressed()){ // virar servo/direção para direita
    Serial.print("DIREITA");
    viraDireita(servoPos);
  }

  else{
    Serial.println("PARADO"); // para o carro / 'freio'
    parado();
  }
 
}


void moveFrente(){
      analogWrite(motorA1, 0);
      analogWrite(motorB1, 255);
      analogWrite(motorB2, 0);
      analogWrite(motorA2, 255);
}

void moveAtras(){
      analogWrite(motorB1, 0);
      analogWrite(motorA1, 255);
      analogWrite(motorA2, 0);
      analogWrite(motorB2, 255);
}
void viraDireita(int x){
    // variavel x recebe o servoPos. Condicional aumenta o angulo em 5 graus com o máximo de 15 graus. De 93 até 108 para direita.
    if(x < 108){  
      servoPos = servoPos + 5;
      meuservo.write(servoPos); 
      
    }else{
      servoPos = 108;
      meuservo.write(servoPos);
    }  
}

void viraEsquerda(int x){
     // variavel x recebe o servoPos. Condicional diminui o angulo em 5 graus com o máximo de 15 graus. De 93 até 78 para esquerda.
      if(x > 78){  
      servoPos = servoPos - 5;
      meuservo.write(servoPos); 
      
    }else{
      servoPos = 78;
      meuservo.write(servoPos);
    } 
}

void parado(){
      analogWrite(motorA1, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
      analogWrite(motorA2, 0);
}