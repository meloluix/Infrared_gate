#include <IRremote.h>

#define receptor 11
#define motorIN1 6
#define motorIN2 5

IRrecv receptorIR(receptor);
decode_results resultado;

void setup() {
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  Serial.begin(9600);
  receptorIR.enableIRIn();  // Inicia o receptor IR
  Serial.println("Aguardando sinal do controle...");
}

void loop() {
  if (receptorIR.decode(&resultado)) {
    unsigned long codigo = resultado.value;
    Serial.print("Código recebido: 0x");
    Serial.println(codigo, HEX);

    switch (codigo) {
      case 0xFFA25D:  // Tecla 1 - Abre o portão
      fecharMotor();
        break;

      case 0xFF629D:  // Tecla 2 - Fecha o portão
        abrirMotor();
        break;

      default:
        Serial.println("Botão não reconhecido.");
        break;
    }

    receptorIR.resume();  // Pronto para próximo sinal
  }
}

void abrirMotor() {
  analogWrite(motorIN1, 150);
  digitalWrite(motorIN2, 0);
  delay(300);
  pararMotor();
  // Serial.println("Portão aberto");
}

void fecharMotor() {
  digitalWrite(motorIN1, 0);
  analogWrite(motorIN2, 150);
  delay(300);
  pararMotor();
  // Serial.println("Portão fechado");
}

void pararMotor() {
  digitalWrite(motorIN1, 0);
  digitalWrite(motorIN2, 0);
}
