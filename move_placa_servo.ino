#include<Servo.h>

int luminosidade = 0;
int ldrPino = A0;
int botaoEsq = 7;
int botaoDir = 8;
int botaoReset = 6;
int anguloMotor = 0;

Servo servo; //instancia do objeto da classe Servo

//prototipos de função
void leBotaoEsq();
void leBotaoDir();
void leBotaoReset();
void imprimeDados();

void setup() {
  Serial.begin(115200);
  pinMode(botaoEsq, INPUT_PULLUP);
  pinMode(botaoDir, INPUT_PULLUP);
  pinMode(botaoReset, INPUT_PULLUP);
  servo.attach(9);
}

void loop() {
  luminosidade = analogRead(ldrPino);
  leBotaoEsq();
  leBotaoDir();
  leBotaoReset();
  if(isnan(luminosidade)){
    Serial.println("Leitura falhou!");
  }else{
    luminosidade = map(luminosidade, 0, 1023, 100, 0);
  }
  if(luminosidade < 50){
    anguloMotor += 1;
    if(anguloMotor > 179){
      anguloMotor = 179;
    }
  }
    servo.write(anguloMotor);
    delay(5);
  
  imprimeDados();
}

void leBotaoEsq(){
  if(digitalRead(botaoEsq) == LOW){
    delay(100);
    if(digitalRead(botaoEsq) == LOW){
      anguloMotor -= 1;
      if(anguloMotor < 0){
        anguloMotor = 0;
      }
    }
  }
}

void leBotaoDir(){
  if(digitalRead(botaoDir) == LOW){
    delay(100);
    if(digitalRead(botaoDir) == LOW){
      anguloMotor += 1;
      if(anguloMotor > 179){
        anguloMotor = 179;
      }
    }
  }
}

void leBotaoReset(){
  if(digitalRead(botaoReset) == LOW){
    delay(100);
    if(digitalRead(botaoReset) == LOW){
      anguloMotor = 0;
      Serial.print("Botão Vermelho: ");Serial.println(anguloMotor);
      delay(500);
    }
  }
}

void imprimeDados(){
  Serial.print("|Luminosidade: ");Serial.print((String)luminosidade);Serial.println(" L");
  Serial.print("|Angulo do Motor: ");Serial.print((String)anguloMotor);Serial.println(" º");
  delay(100);
}
