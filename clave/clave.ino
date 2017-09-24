//global context variables
String password = "robotica";
int attempts = 3;
bool printBlock = true;
bool isFirstTime = true;
String failMessage = "Contraseña incorrecta, verifique e intente de nuevo";
String successMessage = "Contraseña correcta";
String remainigMessage = "Intentos restantes: ";
String trueUpdate = "Si";
String falseUpdate = "No";
const int successLedPin = 2;
const int failLedPin = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(successLedPin, OUTPUT);
  pinMode(failLedPin, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (attempts > 0) {
    if (isFirstTime) {
      Serial.println("Bienvenido al sistema, Digite la contraseña:");
      isFirstTime = false;
    }
    else {
      Serial.println("Digite de nuevo la contraseña:");
    }
    
    while (Serial.available() == 0) {           //Wait for user input

    }
    String valor = Serial.readString();
    if (valor == password) {
      Serial.println(successMessage);
      Serial.println("La cantidad de intentos permitidos, ha sido reiniciada");
      attempts = 3;
      for (int k = 0; k < 3; k++) {
        for (int i = 255; i > 0; i--) {
          analogWrite(successLedPin, i);
          delay(5);
        }
      }
      String updateMessage = "Desea actualizar su contraseña ?, Digite: " + trueUpdate + " || " + falseUpdate;
      Serial.println(updateMessage);
      while (Serial.available() == 0) {           //Wait for user input

      }
      String updatePass = Serial.readString();
      if (updatePass == trueUpdate) {
        Serial.println("Digite la nueva contraseña:");
        while (Serial.available() == 0) {           //Wait for user input

        }
        password = Serial.readString();
        Serial.println("Contraseña actualizada con éxito");
      }
      Serial.println("--==Fin de la ejecución==--");
      isFirstTime = true;
    }
    else {
      //Encender bombillo rojo
      Serial.println(failMessage);
      attempts--;
      String message = remainigMessage + attempts;
      Serial.println(message);
      analogWrite(failLedPin, 255);
      delay(1500);
      analogWrite(failLedPin, 0);
    }
  }
  else {
    if (printBlock) {
      Serial.println("Máximo de intentos superados");
      Serial.println("BLOQUEO DE SISTEMA");
      printBlock = false;
    }
    analogWrite(successLedPin, 255);
    analogWrite(failLedPin, 255);
  }
}



