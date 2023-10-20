#include <iostream>
#include <string>
#include <thread>  
#include <chrono>
#include <Arduino.h>

const int numberLEDS = 8;
int ledPIN[numberLEDS] = {2,3,4,5,6,7,8,9};

void setup(){
    // Configuración de pines, inicialización, etc.
    Serial.begin(9600); // Inicia la comunicación serie
    for(int i = 0; i < numberLEDS; i++){
        pinMode(ledPIN[i], OUTPUT); // Configura los pines de los LEDs como output
    }
}
void loop(){
    // Loop de Arduino, controla los LEDs y recibe datos
  if (Serial.available() > 0) {
    char receivedByte = Serial.read();
    // Control de LEDs según los datos recibidos
    if (receivedByte >= '1' && receivedByte <= '8') {
      int byteValue = receivedByte - '0'; // Convierte el carácter a un valor numérico
      for (int bit = 0; bit < numLEDs; bit++) {
        // Enciende o apaga el LED según el bit correspondiente del byte
        digitalWrite(ledPins[bit], (byteValue & (1 << bit)) ? HIGH : LOW);
      }
    } else if (receivedByte == '0') {
      // Apaga todos los LEDs
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    }
    delay(2000); 
  }
}

int encrypt() {}
int desencrypt() {}


int main() {
    std::string msgToCrypt;
    std::string binaryString = "";
    std::string encryptedMessage = ""; // Almacenará el mensaje encriptado en forma de texto

    // Solicita al usuario que ingrese un valor
    std::cout << "Por favor, ingresa un valor: ";

    // Lee la entrada del usuario y almacénala en la variable
    std::cin >> msgToCrypt;

    for (char character : msgToCrypt) {
        // Obtener el valor ASCII del carácter actual y almacenarlo en una variable.
        int asciiValue = static_cast<int>(character); // Conversión explícita de un carácter a número entero
        int asciiEncrypted = asciiValue - 10;

        for (int i = 7; i >= 0; i--) {
            int bit = (asciiEncrypted >> i) & 1; // Desplazamiento de bits y máscara para obtener cada bit
            binaryString += std::to_string(bit);
        }

        // Muestra un byte encriptado
        std::cout << "Encriptación byte a byte: " << binaryString << std::endl;
        
        // Pausa de 2 segundos
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Agrega el byte encriptado al mensaje encriptado
        encryptedMessage += binaryString;

        // Restablece la cadena binaria para el próximo byte
        binaryString = "";
    }

    // Muestra el mensaje encriptado completo en su forma binaria
    std::cout << "Mensaje encriptado (binario): " << encryptedMessage << std::endl;

    // Convierte el mensaje binario a texto
    std::string encryptedText = "";
    for (size_t i = 0; i < encryptedMessage.length(); i += 8) {
        std::string byte = encryptedMessage.substr(i, 8);
        int asciiValue = std::stoi(byte, nullptr, 2); // Convierte el byte binario a un valor entero
        encryptedText += static_cast<char>(asciiValue);
    }

    // Muestra el mensaje encriptado en forma de texto
    std::cout << "Mensaje encriptado (texto): " << encryptedText << std::endl;

    return 0;
}

