const int motorA1 = 7;
const int motorA2 = 8;
const int motorB1 = 9;
const int motorB2 = 10;

const int motorSpeedA = 5;
const int motorSpeedB = 3;

const int leftSwitch = 2;
const int rightSwitch = 4;

const int lightSensor = A0;
const int tempSensor = A1;
const int voltageSensor = A2;
const int currentSensor = A3;

int direction = 1;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(motorSpeedA, OUTPUT);
  pinMode(motorSpeedB, OUTPUT);

  pinMode(leftSwitch, INPUT_PULLUP);
  pinMode(rightSwitch, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // Концевые выключатели
  if (digitalRead(rightSwitch) == LOW) {
    direction = -1;
    stopMotors();
    delay(300);
  }

  if (digitalRead(leftSwitch) == LOW) {
    direction = 1;
    stopMotors();
    delay(300);
  }

  // Движение платформы
  if (direction == 1) {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
  } else {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
  }

  analogWrite(motorSpeedA, 170);

  // Вращение мягкого валика
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(motorSpeedB, 170);

  // Освещённость
  int light = analogRead(lightSensor);

  // Температура TMP36
  float voltage = analogRead(tempSensor) * 5.0 / 1023.0;
  float temperature = (voltage - 0.5) * 100.0;

  // Условная имитация INA219
  float panelVoltage =
    analogRead(voltageSensor) * 6.0 / 1023.0;

  float panelCurrent =
    analogRead(currentSensor) * 500.0 / 1023.0;

  float power = panelVoltage * panelCurrent / 1000.0;

  Serial.print("Освещенность: ");
  Serial.println(light);

  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Напряжение: ");
  Serial.print(panelVoltage);
  Serial.println(" V");

  Serial.print("Ток: ");
  Serial.print(panelCurrent);
  Serial.println(" mA");

  Serial.print("Мощность: ");
  Serial.print(power);
  Serial.println(" W");

  Serial.println("----------------");

  delay(500);
}

void stopMotors() {
  analogWrite(motorSpeedA, 0);
  analogWrite(motorSpeedB, 0);
}