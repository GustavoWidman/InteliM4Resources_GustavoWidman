// #include <Arduino.h> // Library do arduino, nao necessaria quando usa-se o IDE do arduino mas necessaria quando usa-se o VSCode/PlatformIO

// Define que o pino 27 será usado para o LED
const int ledPin = 13;


void setup() {
	Serial.begin(115200);
	// Testando Serial
	Serial.println("Hello World!");
	Serial.println("This is a test to flash an LED on the ESP32.");

	// Inicializa o pino do LED
	pinMode(ledPin, OUTPUT);
}

void loop() {
	// Nada aqui, pois a tarefa flash_led_loop já está piscando o LED
	digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
}