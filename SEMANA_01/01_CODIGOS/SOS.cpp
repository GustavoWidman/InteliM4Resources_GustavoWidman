// #include <Arduino.h> // Library do arduino, nao necessaria quando usa-se o IDE do arduino mas necessaria quando usa-se o VSCode/PlatformIO
#include <unordered_map>

// Define que o pino 27 será usado para o LED
const int ledPin = 27;


// Mapa de caracteres para sua representação binária em código Morse
std::unordered_map<char, String> morse_binary_map = {
	{'A', "01"},     {'B', "1000"}, {'C', "1010"},
	{'D', "100"},    {'E', "0"},    {'F', "0010"},
	{'G', "110"},    {'H', "0000"}, {'I', "00"},
	{'J', "0111"},   {'K', "101"},  {'L', "0100"},
	{'M', "11"},     {'N', "10"},   {'O', "111"},
	{'P', "0110"},   {'Q', "1101"}, {'R', "010"},
	{'S', "000"},    {'T', "1"},    {'U', "001"},
	{'V', "0001"},   {'W', "011"},  {'X', "1001"},
	{'Y', "1011"},   {'Z', "1100"},

	{'0', "11111"},  {'1', "01111"},{'2', "00111"},
	{'3', "00011"},  {'4', "00001"},{'5', "00000"},
	{'6', "10000"},  {'7', "11000"},{'8', "11100"},
	{'9', "11110"}, {' ', " "},
};

// Essa função recebe um caractere e retorna sua representação binária em código Morse
String to_morse_binary(String character) {
	// Checa se o caractere existe no mapa
	if (morse_binary_map.find(character[0]) != morse_binary_map.end()) {
		// Retorna a representação binária do caractere
		return morse_binary_map[character[0]];
	} else {
		return "";
	}
}

// Essa função recebe uma string e retorna sua representação binária em código Morse
String string_to_morse_binary(String input) {
	String output = "";
	// Itera por todos os caracteres da string
	for (int i = 0; i < input.length(); i++) {
		// Adiciona a representação binária do caractere na string de saída
		output += to_morse_binary(input.substring(i, i + 1));
	}
	return output;
}

// Essa função recebe uma string e pisca o LED de acordo com a representação binária em código Morse
void flash_led_string(String input) {
	// Converte a string para sua representação binária em código Morse
	input = string_to_morse_binary(input);

	// Itera por todos os caracteres da string
	for (int i = 0; i < input.length(); i++) {
		// Checa se o caractere é um ponto ou traço (0 ou 1)
		if (input.substring(i, i + 1) == "0") {
			digitalWrite(ledPin, HIGH);
			delay(100);
			digitalWrite(ledPin, LOW);
		} else if (input.substring(i, i + 1) == "1") {
			digitalWrite(ledPin, HIGH);
			delay(600);
			digitalWrite(ledPin, LOW);
		} else if (input.substring(i, i + 1) == " ") {
			// Caso especial para espaços, que não são representados por 0 ou 1, mas sim por um atraso
			delay(600);
		}
		delay(1000);
	}
}


void setup() {
	Serial.begin(115200);
	// Testando Serial
	Serial.println("Hello World!");
	Serial.println("This is a test to flash an LED on the ESP32.");

	// Testando to_morse_binary
	Serial.println(to_morse_binary("S"));
	Serial.println("This should've printed 000.");

	// Testando string_to_morse_binary
	Serial.println(string_to_morse_binary("SOS"));
	Serial.println("This should've printed 000111000.");

	// Testando string_to_morse_binary com uma string maior
	Serial.println(string_to_morse_binary("EU SOU O GUSTAVO"));

	// Inicializa o pino do LED
	pinMode(ledPin, OUTPUT);
}

void loop() {
	// Nada aqui, pois a tarefa flash_led_loop já está piscando o LED
	flash_led_string("SOS");
	delay(1000);
}