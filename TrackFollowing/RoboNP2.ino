/*
 * Definição das portas utilizadas pelo drive do motor.
 */
int ENA = 3;
int ENB = 5; 
int IN1 = 8;
int IN2 = 7;
int IN3 = 9;
int IN4 = 6;

/*
 * Definição das portas utilizadas pelos sensores de detecção de linha.
 */

int sensorCentroEsquerda = 12;
int sensorCentroDireita = 11;
int sensorEsquerda = 13;
int sensorDireita = 10;

/*
 * Variaveis de leitura de cada sensor utilizado.
 */
int leituraEsquerda;
int leituraDireita ;
int leituraCentroEsquerda;
int leituraCentroDireita;

/*
 * Outras variaveis utilizadas no programa.
 */

double erro = 0;
double input = 0;
double errSum, ultimoErro,dInput, kp, ki, kd;
double dT = 0;
long tempoFinal=0;
long tempo = 0 ;
double ultimaLeitura;

/*
 * x e y são variaveis dque definem a velocidade dos motores.
 */

int x,y;
int constante = 150;

/*
 * Funções que definem as ações realizadas pelo carrinho.
 */

void frente(int velocidadeMotor1, int velocidadeMotor2){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,velocidadeMotor1);
  analogWrite(ENB,velocidadeMotor2);
}

void esquerda(int velocidadeMotor1, int velocidadeMotor2){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,velocidadeMotor1);
  analogWrite(ENB,velocidadeMotor2);//70 65
    
}

void direita(int velocidadeMotor1, int velocidadeMotor2){
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,velocidadeMotor1);//
  analogWrite(ENB,velocidadeMotor2);
  
}
/*void re(int velocidadeMotor1, int velocidadeMotor2){
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,velocidadeMotor1);
  analogWrite(ENB,velocidadeMotor2);
}
void parar(){
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}*/

/*
 * Limitação dos valores recebidos pelas variaveis x e y, estes valores foram utilizados por base de testes
 * e para não resultar em movimentos bruscos na hora da movimentação do carrinho.
 */
void limiteXY(){
  if(x >= 230){
    x = 230;
  }
  if(y >= 230){
    y = 230;
  }  

  if(x < -180){
    x = -180;
  }
  if(y < -180){
   y = -180;
  }
}

/*
 * Função de controle do carrinho, onde será definido ,com base nos valores de x e y, qual função será realizada.(frente, esquerda ou direita).
 */
void control(){
  limiteXY();
  if(x >= 0 && y>= 0){
    frente(x,y);   
  }else if (x < 0 && y> 0){
    direita(-x,y);
  }else if(x > 0 && y< 0){ 
    esquerda(x,-y);
  }
}

/*
 * Função de definição de erro:
 * nesta função é realizado o calculo do input e é encontrado o erro, sendo este o input achado menos o valor do setpoint definido acima.
 * o erro é utilizado também para o calculo do kp, ki e kd.
 * Aqui tambem é chamado a função definir tempo que será detalhada mais a frente.
 */
int amostra = 1000; //1 sec
void definirErro(double setpoint){
  definirTempo();
  //Serial.println(dT);
  if(dT>=amostra){
    input = (150*leituraEsquerda + 250*leituraCentroDireita + 250*leituraCentroEsquerda + 150*leituraDireita);
    erro = setpoint - input;
    errSum += (erro);//* dT);
    dInput = (input - ultimaLeitura );//- ultimoErro) / dT;
    //Serial.println();
    x = constante + (kp * erro + ki * errSum - kd * dInput);
    y = constante - (kp * erro + ki * errSum -   kd * dInput);
    ultimoErro = erro;
    ultimaLeitura = input;
    dT = 0;
  }
}
/*
 * Função utilizada para mudar os valores de kp, ki e kd com base em uma amostra de tempo em segundos.
 */
void setTunings(double Kp, double Ki, double Kd){
    double amostraEmSeg = ((double)amostra)/1000;
    kp = Kp;
    ki = Ki * amostraEmSeg;
    kd = Kd / amostraEmSeg;
}

/*
 * função para definir o tamanho da amostra utilizada nos calculos das variaveis kp, ki e kd.
 */
void setAmostra(int novaAmostra){
  if (novaAmostra > 0){
    double ratio = (double)novaAmostra / (double)amostra;
    ki *= ratio;
    kd /= ratio;
    amostra = (unsigned long)novaAmostra;
  }
}
/*
 * Função de leitura dos sensores, onde as variaveis definidas abaixo receberam um valor referente a situação mostrada no sensor.
 */
void leitura(){
  leituraEsquerda = digitalRead(sensorEsquerda);
  leituraDireita = digitalRead(sensorDireita);
  leituraCentroDireita = digitalRead(sensorCentroDireita);
  leituraCentroEsquerda = digitalRead(sensorCentroEsquerda);
}
/*
 * Função para o calculo da variação do tempo utilizado na função DefinirErro().
 */
void definirTempo(){
  tempo = tempoFinal;
  tempoFinal = millis();
  dT += (double)(tempoFinal - tempo);
}

void setup() {
 pinMode(ENA,OUTPUT);
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(sensorCentroDireita,INPUT);
 pinMode(sensorCentroEsquerda,INPUT);
 pinMode(sensorEsquerda,INPUT);
 pinMode(sensorDireita,INPUT);
 
 digitalWrite(ENA,LOW);
 digitalWrite(ENB,LOW);
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
 tempoFinal = millis();
 setTunings(1.2, 0, 0);
 setAmostra(150);
 //Serial.begin(9600);
}

void loop() {
  leitura();
  definirErro(0);
  control();
  

}
