#include <iostream>
#include <string>

int main() {
    std::string msgToCript;
    std::string binaryString = "";
    // Solicita al usuario que ingrese un valor
    std::cout << "Por favor, ingresa un valor: ";
    
    // Lee la entrada del usuario y almacénala en la variable
    std::cin >> msgToCript;

    for (char character : msgToCript) {
        // Obtener el valor ASCII del carácter actual y almacenarlo en una variable.
        int asciiValue = static_cast<int>(character); // Conversión explicita de un caracter a número entero
        int asciiCripted = asciiValue - 10;
        // Mostrar el carácter y su valor ASCII en la salida estándar.
        std::cout << "El carácter '" << character << "' tiene un valor ASCII de " << asciiValue << std::endl;
        std::cout << "El carácter '" << character << "' tiene un valor modificado de " << asciiCripted << std::endl;
        for (int i = 7; i >= 0; i--) {
            int bit = (asciiCripted >> i) & 1; // Desplazamiento de bits y máscara para obtener cada bit
            binaryString += std::to_string(bit);
            std::cout << "Encriptación completa: " << binaryString << std::endl;
        }
    }

    return 0;
}
