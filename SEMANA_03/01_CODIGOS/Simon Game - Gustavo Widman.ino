/**
 * Jogo Simon Says para Arduino e ESP32
 * Autor: Gustavo Wagon Widman
 *
 * Este código é destinado a criar uma versão do jogo de memória Simon Says.
 * Utiliza-se um ESP32 e uma protoboard, com 5 botões (azul, vermelho, verde, amarelo e preto),
 * 4 LEDs (associados a cada um dos primeiros 4 botões por cor correspondente) e 4 resistores,
 * um para cada LED
 *
 * Botões:
 *  - Azul:    Pino 17
 *  - Vermelho: Pino 12
 *  - Verde:    Pino 27
 *  - Amarelo:  Pino 4
 *  - Preto (Reset): Pino 13
 *
 * LEDs:
 *  - Azul: Pino 5
 *  - Vermelho: Pino 14
 *  - Verde: Pino 26
 *  - Amarelo: Pino 16
 *
 * O jogo:
 *  - A sequência do jogo é exibida acendendo sequencialmente os LEDs.
 *  - O jogador deve reproduzir a sequência pressionando os botões correspondentes.
 *  - Se a sequência estiver correta, um novo elemento é adicionado à sequência.
 *  - Se a sequência estiver errada, o jogo termina e a sequência é reiniciada.
 *  - O botão preto é usado para reiniciar o jogo a qualquer momento.
 *  - O jogo continua até que a sequência atinja a quantidade máxima de passos (MAX_GAME_LENGTH).
 *  - A variavel MAX_GAME_LENGTH pode ser alterada para dificultar o jogo.
 *
 * Instruções:
 *  - Conectar os LEDs e botões de acordo com as definições dos pinos.
 *  - Carregar o código para o ESP32 usando o Arduino IDE.
 *  - Seguir as instruções do jogo conforme aparecem no Serial Monitor.
 */


// Definição dos pinos para LEDs e botões
const uint8_t ledPins[] = {16, 5, 26, 14};
const uint8_t buttonPins[] = {4, 17, 27, 12};
const uint8_t resetButtonPin = 13; // Pino para o botão de reset

// Define o comprimento máximo da sequência do jogo
#define MAX_GAME_LENGTH 4

// Estado atual do jogo
uint8_t gameSequence[MAX_GAME_LENGTH] = {0};
uint8_t gameIndex = 0;

// Inicialização do sistema
void setup() {
  Serial.begin(9600);
  // Configuração dos pinos dos LEDs e botões
  for (byte i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(resetButtonPin, INPUT_PULLUP);
  randomSeed(analogRead(18));
}

// Função para acender o LED correspondente
void lightLed(byte ledIndex) {
  unsigned long startTime = millis();
  digitalWrite(ledPins[ledIndex], HIGH);
  while (millis() - startTime < 300) {
    if (digitalRead(resetButtonPin) == LOW) {
      resetGame();
      while (digitalRead(resetButtonPin) == LOW) delay(10);
      return;
    }
    delay(1);
  }
  digitalWrite(ledPins[ledIndex], LOW);
}

// Função para tocar a sequência de LEDs
void playSequence() {
  for (int i = 0; i < gameIndex; i++) {
    lightLed(gameSequence[i]);
    delay(150);
  }
}

// Função para ler a entrada dos botões
byte readButtons() {
  byte buttonState = 255;
  while (buttonState == 255) {
    for (byte i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        buttonState = i;
        break;
      }
    }
    if (digitalRead(resetButtonPin) == LOW) {
      resetGame();
      while (digitalRead(resetButtonPin) == LOW) delay(10);
      return 255;
    }
    delay(1);
  }
  return buttonState;
}

// Função para resetar o jogo
void resetGame() {
  gameIndex = 0;
  for (int i = 0; i < MAX_GAME_LENGTH; i++) gameSequence[i] = 0;
  Serial.println("Jogo resetado!");
  for (byte i = 0; i < 4; i++) digitalWrite(ledPins[i], HIGH);
  delay(300);
  for (byte i = 0; i < 4; i++) digitalWrite(ledPins[i], LOW);
}

// Função chamada quando o jogador perde o jogo
void gameOver() {
  Serial.print("Fim de jogo! Sua pontuação: ");
  Serial.println(gameIndex - 1);
  resetGame();
}

// Função chamada quando o jogador vence o jogo
void victory() {
  Serial.println("Parabéns, você venceu!");
  for (int i = 0; i < 3; i++) {
    for (byte j = 0; j < 4; j++) digitalWrite(ledPins[j], HIGH);
    delay(100);
    for (byte j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
    delay(100);
  }
  resetGame();
}

// Função para verificar se a sequência do usuário está correta
bool checkUserSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte expectedButton = gameSequence[i];
    byte actualButton = readButtons();
    if (actualButton == 255) return false;
    lightLed(actualButton);
    if (expectedButton != actualButton) return false;
  }
  return true;
}

// Loop principal do jogo
void loop() {
  if (gameIndex < MAX_GAME_LENGTH) {
    gameSequence[gameIndex++] = random(0, 4);
    playSequence();
    if (!checkUserSequence()) gameOver();
  } else {
    victory();
  }
  delay(500);
}
