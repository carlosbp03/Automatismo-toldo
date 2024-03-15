/*
Programa para simular el funcionamiento de un toldo para poder 
plegarlo y desplegarlo usando un mismo pulsador.
 
Autor: Juan Carlos Breijo Pérez
Data: Febrero de 2024
*/
#define finalopen 3
#define finalclose 4
#define salidaldr 11
#define entradaldr A0
#define pulsador 2
#define motoropen 10
#define motorclose 9



bool estadoPulsador = 0;
bool ultimoMotor = 0;
bool estadoMotoropen = 0;
bool estadoMotorclose = 0;
int velocidade = 0;
int lecturaldr = 0;

void setup() {
  pinMode(motoropen, OUTPUT);
  pinMode(motorclose, OUTPUT);
  pinMode(pulsador, INPUT);
  pinMode(finalopen, INPUT);
  pinMode(finalclose, INPUT);
  Serial.begin(9600);
}

void loop() {
  lecturaldr = analogRead(entradaldr);
  velocidade = map(lecturaldr, 54, 974, 0, 5);
  Serial.println(velocidade);
  switch (velocidade){
    case 0: analogWrite(salidaldr, 255*0.05);break;
    case 1: analogWrite(salidaldr, 255*0.2);break;
    case 2: analogWrite(salidaldr, 255*0.4);break;
    case 3: analogWrite(salidaldr, 255*0.6);break;
    case 4: analogWrite(salidaldr, 255*0.8);break;
    case 5: analogWrite(salidaldr, 255);break;
  }
  if(digitalRead(pulsador)) {
    estadoPulsador = !estadoPulsador;
    estadoMotoropen = 0;
    estadoMotorclose = 0;
    while(digitalRead(pulsador)) {
      delay(20);
    }
    if(estadoPulsador == !0){
      ultimoMotor = !ultimoMotor;
    }
  }  
  if(estadoPulsador == 0 && ultimoMotor == !0) {
    digitalWrite(motoropen, 1);
    digitalWrite(motorclose, 0);
    estadoMotoropen = 1;
  }
  else if(estadoPulsador == 0 && ultimoMotor == 0){
    digitalWrite(motoropen, 0);
    digitalWrite(motorclose, 1);
    estadoMotorclose = 1;
  }else{
    digitalWrite(motoropen, 0);
    digitalWrite(motorclose, 0);
    estadoMotoropen = 0;
    estadoMotorclose = 0;
  }
  if(digitalRead(finalopen)) {
    if(estadoMotoropen == 1){
      digitalWrite(motoropen, 0);
      estadoPulsador = !estadoPulsador;
      estadoMotoropen = 0;
      ultimoMotor = !ultimoMotor;
    }
    while(digitalRead(finalopen)) {
      delay(20);
    }
  }
  if(digitalRead(finalclose)) {
    if(estadoMotorclose == 1){
      digitalWrite(motorclose, 0);
      estadoPulsador = !estadoPulsador;
      estadoMotorclose = 0;
      ultimoMotor = !ultimoMotor;
    }
    while(digitalRead(finalclose)) {
      delay(20);
    }
  }
}
