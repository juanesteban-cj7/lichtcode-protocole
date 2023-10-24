String encryptedMessage = ""; // Variable para almacenar el mensaje codificado
String principalMessage = "";  // Variable para almacenar el mensaje
int ledsPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pines donde están conectados los LEDs

void setup() {
  Serial.begin(9600);  // Iniciar la comunicación serie a 9600 baudios
  for (int i = 0; i < 8; i++) {
    pinMode(ledsPins[i], OUTPUT); // Configurar pines de LEDs como salidas
  }
}

void loop() {
  desencrypt();  
}

void desencrypt(){
    Serial.println("Por favor, ingresa un mensaje encriptado: ");
    while(Serial.available() == 0){
        // Esperar ingreso de un mensaje
    }

    encryptedMessage = Serial.readString();

    Serial.print("Mensaje Ingresado: ");
    Serial.println(encryptedMessage);

    String originalMessage = "";

    // Iteración de cada caracter
    for(int i = 0; i < encryptedMessage.length(); i++){
        char currentChar = encryptedMessage.charAt(i);
        int CriptAsciiValue = int(currentChar); 

        // Operación inversa para desencriptación
        int originalASCIIValue = CriptAsciiValue + 10; 

        Serial.print("Código ASCII de la letra '");
        Serial.print(currentChar);
        Serial.print("':");
        Serial.println(originalASCIIValue);

        String binaryValue = intToBinary(originalASCIIValue);
        Serial.print("Valor en binario: ");
        Serial.println(binaryValue);

        // llama la función de control de leds para controlarlos según secuencia binaria
        controlarLEDs(binaryValue);

        // Agrega cada caracter al mensaje original completo
        originalMessage += char(originalASCIIValue);

        delay(2000);
    }
    Serial.print("El mensaje original es: ");
    Serial.println(originalMessage);
}

void encrypt() {
  // Solicitar un mensaje al usuario
  Serial.println("Por favor, ingresa un mensaje: ");

  while (Serial.available() == 0) {
    // Esperar hasta que se ingrese un mensaje
  }

  principalMessage = Serial.readString();  // Almacenar el mensaje ingresado en principalMessage

  // Mostrar el mensaje en el monitor en serie
  Serial.print("Mensaje ingresado: ");
  Serial.println(principalMessage);
  
  String encryptedMessage = "";

  // Procesar cada letra del mensaje
  for (int i = 0; i < principalMessage.length(); i++) {
    char currentChar = principalMessage.charAt(i);
    int asciiValue = int(currentChar);
    
    // Restar 10 al valor ASCII
    int modifiedAsciiValue = asciiValue - 10;
    
    Serial.print("Código ASCII de la letra '");
    Serial.print(currentChar);
    Serial.print("': ");
    Serial.println(modifiedAsciiValue);
    
    // Convertir el valor ASCII modificado a binario
    String binaryValue = intToBinary(modifiedAsciiValue);
    Serial.print("Valor en binario: ");
    Serial.println(binaryValue);

    // Controlar los LEDs según la secuencia binaria
    controlarLEDs(binaryValue);

    // // Agregar el carácter encriptado al mensaje encriptado
    encryptedMessage += char(modifiedAsciiValue);

    delay(2000);
  }
  Serial.print("Mensaje encriptado: ");
  Serial.println(encryptedMessage);
}

String intToBinary(int n) {
  String binaryString = "";
  for (int i = 7; i >= 0; i--) {
    int bit = (n >> i) & 1;
    binaryString += String(bit);
  }
  return binaryString;
}

void controlarLEDs(String binaryValue) {
  for (int i = 0; i < 8; i++) {
    int estadoLED = binaryValue.charAt(i) - '0'; // Convertir el carácter binario en un valor entero
    digitalWrite(ledsPins[i], estadoLED);
  }
}
