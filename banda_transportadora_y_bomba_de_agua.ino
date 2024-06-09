//Declaraciones variables
#define TRIG_PIN 11
#define ECHO_PIN 10
#define GEARMOTOR_PIN 12
#define PUMP_PIN1 3
#define GREEN_LED_PIN1 6
#define GREEN_LED_PIN2 8
#define RED_LED_PIN1 7
#define RED_LED_PIN2 9
int contador;
void setup() {
  //Declaraciones de funcionamiento
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GEARMOTOR_PIN, OUTPUT);
  pinMode(PUMP_PIN1, OUTPUT);
  pinMode(GREEN_LED_PIN1, OUTPUT);
  pinMode(GREEN_LED_PIN2, OUTPUT);
  pinMode(RED_LED_PIN1, OUTPUT);
  pinMode(RED_LED_PIN2, OUTPUT);

  digitalWrite(GEARMOTOR_PIN, LOW);
  digitalWrite(PUMP_PIN1, HIGH);
  digitalWrite(GREEN_LED_PIN1, LOW);
  digitalWrite(GREEN_LED_PIN2, LOW);
  digitalWrite(RED_LED_PIN1, LOW);
  digitalWrite(RED_LED_PIN2, LOW);
}

void loop() {
  //Funcionamiento del ejecutable

  //Sensor ultrasonico
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  //Primera condicional: DISTANCIA/RANGO
  if (distance <= 15) {
    // Detener el motorreductor y encender la bomba de agua
    digitalWrite(GEARMOTOR_PIN, HIGH);
    digitalWrite(PUMP_PIN1, LOW);

    //Tiempo de llenado
    delay(6000);

    //LED de "aprovado-funcional"
    digitalWrite(GREEN_LED_PIN1, HIGH);
    digitalWrite(GREEN_LED_PIN2, HIGH);
    delay(3000);

    //Apagar LED y bomba de agua, enciende motorreductor
    digitalWrite(PUMP_PIN1, HIGH);
    digitalWrite(GREEN_LED_PIN1, LOW);
    digitalWrite(GREEN_LED_PIN2, LOW);
    digitalWrite(GEARMOTOR_PIN, LOW);
    delay(3000);

    //Contador de vueltas de trabajo
    contador ++;

    // Segunda condicional: PRIMER ERROR llenado insuficiente
    if (contador == 2) {
      // Detener el motorreductor y encender la bomba de agua
      digitalWrite(GEARMOTOR_PIN, HIGH);
      digitalWrite(PUMP_PIN1, LOW);
      //Tiempo de llenado
      delay(2000);

      //LED de "ERROR"
      digitalWrite(RED_LED_PIN1, HIGH);
      digitalWrite(RED_LED_PIN2, HIGH);
      delay(3000);

      //Apagar LED y bomba de agua, enciende motorreductor
      digitalWrite(PUMP_PIN1, HIGH);
      digitalWrite(RED_LED_PIN1, LOW);
      digitalWrite(RED_LED_PIN2, LOW);
      digitalWrite(GEARMOTOR_PIN, LOW);
      delay(3000);

    }

    // Tercera condicional: SEGUNDO ERROR exceso llenado
    if (contador == 5) {
      // Detener el motorreductor y encender la bomba de agua
      digitalWrite(GEARMOTOR_PIN, HIGH);
      digitalWrite(PUMP_PIN1, LOW);
      delay(8200);

      //LED de "ERROR"
      digitalWrite(RED_LED_PIN1, HIGH);
      digitalWrite(RED_LED_PIN2, HIGH);
      delay(3000);

      //Apagar LED y bomba de agua, enciende motorreductor
      digitalWrite(PUMP_PIN1, HIGH);
      digitalWrite(GREEN_LED_PIN1, LOW);
      digitalWrite(RED_LED_PIN2, LOW);
      digitalWrite(GEARMOTOR_PIN, LOW);
      delay(3000);

      //Reinicia contador
      contador = 0;
    }
  } else {
    digitalWrite(GEARMOTOR_PIN, LOW);
  }
  delay(500);

}
