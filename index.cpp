/*
 * Código para o Desafio Maze Runner - Simulação no TinkerCad
 * ADAPTADO PARA O CHIP PONTE H L293D
*/


const int PINO_TRIGGER = 12;
const int PINO_ECHO = 11;

const int ENABLE_ESQUERDO = 9;  
const int INPUT1 = 7;          
const int INPUT2 = 6;          

const int ENABLE_DIREITO = 10;  
const int INPUT3 = 5;          
const int INPUT4 = 4;          


int velocidadeRobo = 150; 
int distanciaSegura = 20;
int viradas = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Simulador Robô Maze Runner Iniciado! (Usando L293D)");

  pinMode(PINO_TRIGGER, OUTPUT);
  pinMode(PINO_ECHO, INPUT);

  pinMode(ENABLE_ESQUERDO, OUTPUT);
  pinMode(INPUT1, OUTPUT);
  pinMode(INPUT2, OUTPUT);
  pinMode(ENABLE_DIREITO, OUTPUT);
  pinMode(INPUT3, OUTPUT);
  pinMode(INPUT4, OUTPUT);
}

void loop() { 
  long distancia = lerDistancia();
  if (distancia < distanciaSegura) {
    Serial.println("!! Obstaculo a frente !!");
    parar();
    delay(500); 
    if (viradas > 0) {
      	virarDireita();      	      	
    	delay(1000); 
    	parar();
    	delay(500);
      	virarDireita();
      	delay(1000); 
    	parar();
    	delay(500);
		viradas = 0;
      	Serial.print(viradas);
      	if (distancia < distanciaSegura) {
          virarDireita();      	      	
          delay(1000); 
          parar();
          delay(500);
          Serial.print(viradas);
      	}
    } else {
      	virarEsquerda();		
    	delay(1000); 
    	parar();
    	delay(500);
      	viradas = viradas + 1;
      	Serial.print(viradas);
    }        
  }else {
    moverFrente();
    viradas = 0;
    Serial.print("Distancia a frente: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }
  delay(100);
}

void moverFrente() {
  Serial.println("Acao: Movendo para frente...");
  digitalWrite(INPUT1, HIGH);
  digitalWrite(INPUT2, LOW);
  digitalWrite(INPUT3, LOW);
  digitalWrite(INPUT4, HIGH);
  analogWrite(ENABLE_ESQUERDO, velocidadeRobo);
  analogWrite(ENABLE_DIREITO, velocidadeRobo);
}

void parar() {
  Serial.println("Acao: Parando.");
  digitalWrite(INPUT1, LOW);
  digitalWrite(INPUT2, LOW);
  digitalWrite(INPUT3, LOW);
  digitalWrite(INPUT4, LOW);
}

void virarEsquerda() {
  Serial.println("Acao: Virando a esquerda...");
  digitalWrite(INPUT1, LOW);
  digitalWrite(INPUT2, HIGH);
  digitalWrite(INPUT3, LOW);
  digitalWrite(INPUT4, HIGH);
  analogWrite(ENABLE_ESQUERDO, velocidadeRobo);
  analogWrite(ENABLE_DIREITO, velocidadeRobo);
}

void virarDireita() {
    Serial.println("Acao: Virando a direita...");
    digitalWrite(INPUT1, HIGH);
    digitalWrite(INPUT2, LOW);
    digitalWrite(INPUT3, HIGH);
    digitalWrite(INPUT4, LOW);
    analogWrite(ENABLE_ESQUERDO, velocidadeRobo);
    analogWrite(ENABLE_DIREITO, velocidadeRobo);
}

long lerDistancia() {
  digitalWrite(PINO_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIGGER, LOW);
  long duracao = pulseIn(PINO_ECHO, HIGH);
  return duracao * 0.034 / 2;
}