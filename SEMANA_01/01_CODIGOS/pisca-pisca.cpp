#include <Arduino.h>

// Define que o pino 27 será usado para o LED
const int ledPin = 27;


// Essa função é executada em uma tarefa separada para piscar o LED repetidamente
void flash_led_loop(void *parameter) {
	while (true) {
		digitalWrite(ledPin, HIGH);
		delay(300);
		digitalWrite(ledPin, LOW);
		delay(300);
	}
}

void setup() {
	Serial.begin(115200);
	// Testando Serial
	Serial.println("Hello World!");
	Serial.println("This is a test to flash an LED on the ESP32.");

	// Inicializa o pino do LED
	pinMode(ledPin, OUTPUT);

	// Cria uma tarefa para piscar o LED com SOS sem travar o loop principal
	xTaskCreatePinnedToCore(
		flash_led_loop,
		"flash_led_loop",
		10000,
		NULL,
		0,
		NULL,
		0
	);
}

void loop() {
	// Nada aqui, pois a tarefa flash_led_loop já está piscando o LED
	delay(10);
}