// Define que o pino 13 será usado para o LED
const int ledPin = 13;


void setup() {
	// Inicializa o pino do LED
	pinMode(ledPin, OUTPUT);
}

void loop() {
  	// Escreve output alto no pino do LED (liga)
	digitalWrite(ledPin, HIGH);
  	// Espera 300ms
    delay(300);
  	// Escreve output baixo no pino do LED (desliga)
    digitalWrite(ledPin, LOW);
  	// Espera 300ms
    delay(300);
}