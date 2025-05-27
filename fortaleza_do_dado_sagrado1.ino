#include <Servo.h>

Servo porta;

int ledVerde = 10;
int ledVermelho = 7;
int ledAzul1 = 4;
int ledAzul2 = 3;
int ledAzul3 = 2;
int servoPin = 12;

int acertos = 0;
int numeroSagrado;

int ledsAzuis[] = {ledAzul1, ledAzul2, ledAzul3};

void setup() {
  Serial.begin(9600);

  porta.attach(servoPin);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul1, OUTPUT);
  pinMode(ledAzul2, OUTPUT);
  pinMode(ledAzul3, OUTPUT);
  
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledsAzuis[i], LOW);
  }

  porta.write(0);

  Serial.println("Bem-vindo a Fortaleza do Dado Sagrado! ");
  Serial.println("Adivinhe o numero sagrado (1 a 6): ");
  Serial.println();
  randomSeed(analogRead(0));
  novoDesafio();
}

void loop() {
  if (Serial.available() > 0) {
    int palpite = Serial.parseInt();
    if (palpite >= 1 && palpite <= 6) {
      if (palpite == numeroSagrado) {
        digitalWrite(ledVerde, HIGH);
        delay(500);
        digitalWrite(ledVerde, LOW);

        if (acertos < 3) {
          digitalWrite(ledsAzuis[acertos], HIGH);
        }

        acertos++;
        Serial.println("Voce acertou! Joia conquistada. ");
        Serial.println();
      } else {
        digitalWrite(ledVermelho, HIGH);
        delay(500);
        digitalWrite(ledVermelho, LOW);
        Serial.print("Errou! O numero era: ");
        Serial.println();
        Serial.println(numeroSagrado);
      }

      if (acertos >= 3) {
        Serial.println("Todas as joias foram conquistadas! ");
        abrirPorta();
      } else {
        novoDesafio();
      }
  
    }
  }
}

void novoDesafio() {
  numeroSagrado = random(1, 7);
  Serial.println("Novo desafio: Adivinhe o numero sagrado (1 a 6): ");
  Serial.println();
}

void abrirPorta() {
  Serial.println("A Porta da Sabedoria esta se abrindo... ");
  for (int i = 0; i <= 90; i += 5) {
    porta.write(i);
    delay(1000);
  }
}
