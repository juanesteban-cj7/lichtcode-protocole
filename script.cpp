#include <iostream>
#include <string>
#include <thread> 

int encript() {}
int desencript() {}

int main() {
    std::string msgToCript;
    std::string binaryString = "";

    // Solicita al usuario que ingrese un valor
    std::cout << "Por favor, ingresa un valor: ";

    // Lee la entrada del usuario y almacénala en la variable
    std::cin >> msgToCript;

    for (char character : msgToCript) {
        // Obtener el valor ASCII del carácter actual y almacenarlo en una variable.
        int asciiValue = static_cast<int>(character); // Conversión explícita de un carácter a número entero
        int asciiCripted = asciiValue - 10;
        
        for (int i = 7; i >= 0; i--) {
            int bit = (asciiCripted >> i) & 1; // Desplazamiento de bits y máscara para obtener cada bit
            binaryString += std::to_string(bit);
        }

        // Muestra un byte encriptado
        std::cout << "Encriptación completa: " << binaryString << std::endl;
        // Pausa de 2 segundos
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Restablece la cadena binaria para el próximo carácter
        binaryString = "";
    }

    return 0;
}
