![unifor_logo](https://user-images.githubusercontent.com/32148244/30723505-3ff3405a-9f0e-11e7-81fc-152139920f83.jpg)

# Resumo 

O objetivo deste trabalho é  mostrar a aplicação de conhecimentos adquiridos durante ao longo do curso de Engenharia de  Controle e Automação para construção de um robô seguidor de linhas utilizando controladores PID na programação. 

# Contribuidores

Jefferson Acioly

Jorge Renan

André Tavares

William Rodrigues

# Fundamentação Teórica.

 Controlador PID -  Controlador proporcional integral derivativo, é uma técnica de controle de processos que une as ações derivativa, integral e proporcional, fazendo assim com que o sinal de erro seja minimizado pela ação proporcional, zerado pela ação integral e obtido com uma velocidade antecipativa pela ação derivativa. 

 O algoritmo PID pode ser definido por : 
 
 
 ![image](https://user-images.githubusercontent.com/31252029/33325261-8a781572-d430-11e7-8862-d25ff87f90b7.png)

   Figura 1- Expressão para o controlador PID
   
# Ação proporcional 
A ação proporcional  produz um sinal de saída que é proporcional à amplitude do erro e(t), sendo Kp a constante de proporcionalidade.

# Ação Integral
A ação integral produz um sinal de saída que é proporcional à magnitude e à duração do erro, ou seja, o erro acumulado. Isso fornece uma alternativa para corrigir o erro de off-set gerado pela ação integral e acelera a resposta do sistema, permitindo-o chegar ao valor de referência mais rapidamente.

# Ação Derivatira 
A ação derivativa produz um sinal de saída que é proporcional à velocidade de variação do erro, fornece uma correção antecipada diminuindo o tempo de resposta e melhorando a estabilidade do sistema.

![image](https://user-images.githubusercontent.com/31252029/33325371-d1d51e2e-d430-11e7-8f4b-0bcb3905ed58.png)

Figura 2 – Controlador PID


# Materiais e equipamentos necessários:

1 Arduino Duemilanove

1 Drive ponte H

2 Motores cc 

1 Chassi de Carro didático 

1 Fonte 

1 Modulo sensor de linha 

Cabos para conexão 

# Procedimentos 
O primeiro passo para se conseguir um robô seguidor de linha é a montagem. Devemos acoplar ao chassi do carro os componententes por exemplo: Arduino, sensores de linha, ponte h e em seguida realizar as conexões.

# SENSOR DE LINHA 

Vcc -> Pino de alimentação do sensor.

Gnd -> Pino de referência 0 para alimentação do sensor.

L ->  Pino que recebe as informações do lado esquerdo.

C -> Pino que recebe as informações do centro.

R -> Pino que recebe as informações do lado direito.

![image](https://user-images.githubusercontent.com/31252029/33325452-144deca4-d431-11e7-9eed-6868f31a94a7.png)


# Ponte H

![image](https://user-images.githubusercontent.com/31252029/33325477-2577fc2c-d431-11e7-980c-33445c453579.png)

•	(Motor A) e (Motor B) se referem aos conectores para ligação de 2 motores DC ou 1 motor de passo

•	(Ativa MA) e (Ativa MB) – são os pinos responsáveis pelo controle PWM dos motores A e B. Se estiver com jumper, não haverá controle de velocidade, pois os pinos estarão ligados aos 5v. Esses pinos podem ser utilizados em conjunto com os pinos PWM do Arduino

•	(Ativa 5v) e (5v) – Este Driver Ponte H L298N possui um regulador de tensão integrado. Quando o driver está operando entre 6-35V, este regulador disponibiliza uma saída regulada de +5v no pino (5v) para um uso externo (com jumper), podendo alimentar por exemplo outro componente eletrônico. Portanto não alimente este pino (5v) com +5v do Arduino se estiver controlando um motor de 6-35v e jumper conectado, isto danificará a placa. O pino (5v) somente se tornará uma entrada caso esteja controlando um motor de 4-5,5v (sem jumper), assim poderá usar a saída +5v do Arduino.

•	(6-35v) e (GND) – Aqui será conectado a fonte de alimentação externa quando o driver estiver controlando um motor que opere entre 6-35v. Por exemplo se estiver usando um motor DC 12v, basta conectar a fonte externa de 12v neste pino e (GND).

•	(Entrada) – Este barramento é composto por IN1, IN2, IN3 e IN4. Sendo estes pinos responsáveis pela rotação do Motor A (IN1 e IN2) e Motor B (IN3 e IN4).

# CONECTANDO A PONTE H AO ARDUINO:

![image](https://user-images.githubusercontent.com/31252029/33325588-769bbddc-d431-11e7-9241-14416fe183e1.png)

Após ser realizada a montagem e conexão do robô será iniciada a programação:

# Programação


# 1° - Definição dos pinos conectados e das  variáveis

```
 /////Definição dos pinos/////o programa q ta certo, ajuste so no ki e kd
  int L = 2; //Pino do sensor esquerdo
  int C = 12; //Pino do sensor central
  int R = 4; //Pino do sensor direito
 /////Pinos do Drive
  int ENA = 3; // Pino pra PWM
  int IN1 = 5; // Pinos pra controlar o sentido de rotação do motor
  int IN2 = 6;
  int IN3 = 9;
  int IN4 = 10;
  int ENB = 11; // Pino pra PWM
  ////////////////////////////

  ///Declaração das Variáveis////
  int V = 180; // Valor da equação para achar o setpoint
  int constante = 110; //Constante usada para definir a velocidade dos motores
  int setPoint = 200; // Velocidade ideal dos motores
  int motorA; //Variável responsável pela velocidade dos motores
  int motorB;
  float kp = 2 , ki = 0.0015, kd = 110; //Variáveis de controle Proporcional, Integrativo e Derivativo
  int erro; // Variável do erro
  int Va; //Valor anterior da equação
  int t = 0, ta = 0, dt = 0; //Variáveis para obter o tempo, tempo anterior e diferença entre os tempos
  float P,I,D; //Variáveis que recebem os calculos dos controladores
///////////////////////////////////////


```

# 2° -  Inicialização do Programa

```
void setup() {

 pinMode(L, INPUT);
 pinMode(C, INPUT);
 pinMode(R, INPUT);
 pinMode(ENA, OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENB, OUTPUT);

 digitalWrite(ENA, LOW);
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
 digitalWrite(ENB, LOW);
}

```

# 3° - Funções utilizadas para movimentação dos motores.

```
////Funções/////
void Frente(int a, int b){
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  analogWrite(ENA, a);
  analogWrite(ENB, b);
}

void esquerda(int a, int b){
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  analogWrite(ENA, a+70);
  analogWrite(ENB, b);
}

void direita(int a, int b){

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  analogWrite(ENA, a);//-20
  analogWrite(ENB, b+70);//+50
  
}

void parar(){
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}

```

# 4° - Progama Principal.

```
void loop() {
  ta = t;
  t = millis();
  dt = t - ta;
  int r = digitalRead(L); //Recebi as leituras do sensor infravermelho
  int c = digitalRead(C);
  int l = digitalRead(R);
   
//Inversão dos dados////
  if(l == 1){
    l = 0;
  } else {
    l = 1;
  }

  if(c == 1){
    c = 0;
  } else{
    c = 1;
  }

  if(r == 1){
    r = 0;
  } else {
    r = 1;
  }
//////////////////////////////////
  Va = V;
///Equação da Resultante/////
  if((l+r+c)!=0){
    
   V = (300*l + 200*c + 100*r)/(l+c+r);
  }
////////////////    

  erro = setPoint - V; //Calculo do erro

  P = erro*kp; //Controlador Proporcional
  I+= erro*dt*ki; //Controlador Integrativo
  D = (kd*(V - Va))/dt; //Controlador Derivativo

  motorA = constante + (P + I + D); //Calculo para a velocidade dos motores
  motorB = constante - (P + I + D);

///Comandos////
  if(motorA > 220){
    motorA = 220;
  }

  if(motorB < -170){
    motorB = -170;
  }
  
  if(motorA < -170){
    motorA = -170;
  }

  if(motorB > 200){
    motorB = 200;
  }
  if (motorA>0 && motorB>0)
  Frente(motorA,motorB);
  if((motorA<0) && (motorB>0)){
    esquerda(-motorA,motorB);
    
  } 
  if((motorA>0) && (motorB<0)){
    direita(motorA,-motorB);
    
  }
  
}

```














