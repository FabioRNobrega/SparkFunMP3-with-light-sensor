
#include <SPI.h>
#include <SoftwareSerial.h>
#include <MP3.h>
const int trigPin = 4;
const int echoPin = 5;
const int ledPin = 13;
long duracao;
int distancia;
int aprocimacaoMaxima;


MP3 mp3;

void setup() {
  
 /** Inicia MP3 */
  mp3.begin(MP3_SOFTWARE_SERIAL);    // Seleciona Sofware Serial
//  mp3.begin();                       // Seleciona  hardware Serial(or mp3.begin(MP3_HARDWARE_SERIAL);)
  
  /** Seleciona Volume Max */
  mp3.volume(0x1F);
  
  /** Seleciona MP3 Shield CYCLE mode */
  mp3.set_mode(MP3::CYCLE);
  
pinMode(trigPin, OUTPUT); // Seleciona a porta trigPin como Output(saida)
pinMode(echoPin, INPUT); // Seleciona a porta echoPin como Input(Entrada)
pinMode(ledPin, OUTPUT);// Conecção Led 13 Para Debug

Serial.begin(9600); // Inicia Comunicação Serial 
}


void loop() {
// Abre trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(5);

// Envia uma frequencia sonora atraves do  trigPin ligado por 10 micro segundos
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Lê o sinal devolta da frequencia em microsegundos
duracao = pulseIn(echoPin, HIGH);

// Calcula a distância entre a ida e a volda(trigPin / echoPin)
distancia= duracao*0.034/2;

aprocimacaoMaxima = distancia;
if (aprocimacaoMaxima <=20){
  mp3.play_usb_disk(0x000+random(1,42));// função random gera um numero aleatorio no range de 1 à 42 selecionando assim a musica na quela posição dentro do USB
  digitalWrite(ledPin, HIGH);
//  delay(3000);
}else {
  mp3.play_sd(0x0001);// entra na função SDcard GAMBIARRA para Stop
  digitalWrite(ledPin, LOW);
}

// Prints the distancia on the Serial Monitor
Serial.print("distancia: ");
Serial.print(distancia);
Serial.println(" cm");

delay(5000);
}
