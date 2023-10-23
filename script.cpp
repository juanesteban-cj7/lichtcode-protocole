#include <iostream>
#include <string>
#include <bitset>
#include <chrono>
#include <thread>
#include <iostream>
#include <Windows.h>


int encrypt(){
    std::string msgToCrypt;
    std::string binaryString = "";
    std::string encryptedMessage = ""; // Almacenará el mensaje encriptado en forma de texto

    // Solicita al usuario que ingrese un valor
    std::cout << "Por favor, ingresa una palabra: ";

    // Lee la entrada del usuario y almacénala en la variable
    std::cin >> msgToCrypt;

    for (char character : msgToCrypt) {
        // Obtener el valor ASCII del carácter actual y almacenarlo en una variable.
        int asciiValue = static_cast<int>(character); // Conversión explícita de un carácter a número entero
        int asciiEncrypted = asciiValue - 10;

        std::cout << "Carácter original: " << character << std::endl;
        std::cout << "Carácter encriptado: " << static_cast<char>(asciiEncrypted) << std::endl;

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
int desencrypt() {
    std::string mensaje;
    std::cout << "Por favor, ingresa un mensaje de caracteres: ";
    std::cin.ignore(); // Limpiamos el búfer de entrada antes de pedir el mensaje
    std::getline(std::cin, mensaje);

    std::cout << "Códigos ASCII de los caracteres del mensaje + 10 y su representación en binario:" << std::endl;

    std::string mensajeOriginal = ""; // Inicializamos el mensaje original

    for (char caracter : mensaje) {
        int codigoASCII = static_cast<int>(caracter);
        int nuevoCodigoASCII = codigoASCII + 10; // Sumamos 10 a los códigos ASCII

        std::cout << caracter << " : " << nuevoCodigoASCII << " en binario: ";
        std::bitset<8> binary(nuevoCodigoASCII); // Convierte a binario
        std::cout << binary << " en letra: " << static_cast<char>(binary.to_ulong()) << std::endl;

        mensajeOriginal += static_cast<char>(nuevoCodigoASCII); // Agregamos el caracter modificado al mensaje original

        if (caracter != mensaje.back()) {
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Espera 2 segundos, excepto en el último carácter
        }
    }

    std::cout << "El mensaje original es: " << mensajeOriginal << std::endl;

    return 0;
}




int main() {
    HANDLE hSerial;
    hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cerr << "El puerto COM no existe. Asegúrate de que el Arduino esté conectado y que has seleccionado el puerto COM correcto." << std::endl;
        } else {
            std::cerr << "Error inesperado al abrir el puerto COM." << std::endl;
        }
    } else {
        DCB dcbSerialParams = {0};
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "Error al obtener los parámetros del puerto COM." << std::endl;
        } else {
            dcbSerialParams.BaudRate = CBR_9600; // Velocidad de comunicación (debe coincidir con la configuración en el Arduino)
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;

            if (!SetCommState(hSerial, &dcbSerialParams)) {
                std::cerr << "Error al configurar los parámetros del puerto COM." << std::endl;
            } else {
                char command;
                while (true) {
                    std::cout << "Ingresa '1' para encender el LED o '0' para apagarlo: ";
                    std::cin >> command;

                    DWORD bytesWritten;
                    if (!WriteFile(hSerial, &command, 1, &bytesWritten, NULL)) {
                        std::cerr << "Error al enviar datos al puerto COM." << std::endl;
                        break;
                    }

                    // Es importante añadir un pequeño retraso antes de leer la respuesta
                    // para permitir que Arduino procese y responda adecuadamente.
                    Sleep(100);

                    char response;
                    DWORD bytesRead;
                    if (ReadFile(hSerial, &response, 1, &bytesRead, NULL)) {
                        std::cout << "Respuesta del Arduino: " << response << std::endl;
                    } else {
                        std::cerr << "Error al recibir respuesta del Arduino." << std::endl;
                        break;
                    }
                }
            }
        }

        CloseHandle(hSerial);
    }

    
    std::string initialChoose;
    std::cout << "¿Desea desencriptar (d) o encriptar (e) un mensaje? ";
    std::cin >> initialChoose;
    if(initialChoose == "d"){
      desencrypt();
    }
    else if(initialChoose == "e")
    {
      encrypt();
    }
    else {
      std::cout << "ERROR";
    }
    
    
    
    return 0;
}

