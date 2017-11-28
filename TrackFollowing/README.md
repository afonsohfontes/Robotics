![unifor_logo](https://user-images.githubusercontent.com/32148244/30723505-3ff3405a-9f0e-11e7-81fc-152139920f83.jpg)

# Integrantes

Jefferson Acioly

Jorge Renan

André Tavares

William Rodrigues

# Resumo

Este é um relatório da disciplina de Robótica do curso de graduação de Engenharia de Controle e Automação da Universidade de Fortaleza. Este consiste em elaborar um carro autonomo seguidor de pista, no qual irá participar da Feira do Conhecimento em uma competição estilo corrida. Para controle deste carro é foi utilizado o uso de controle PID (Proporcional, Integral, Derivativo).

# Materiais e equipamentos necessários:

1 Arduino Duemilanove

1 Drive ponte H

2 Motores cc 

1 Chassi de Carro didático 

1 Fonte 

1 Módulo Seguidor de Linha Infravermelho 4 Canais 

Cabos para conexão

# Procedimentos 
O primeiro passo para se conseguir um robô seguidor de pista é a montagem. Devemos acoplar ao chassi do carro os componententes por exemplo: Arduino, módulo seguidor de linha, ponte h e em seguida realizar as conexões.
Para acoplar os sensores, foi utilizado duas hastes em um ângulo de 45º, obedecendo ao edital da competição para não superarmos o limite de dimensões do carro, cada haste com dois sensores, um na extremidade e outro mais próximo ao robô, a lógica deste posicionamento será explicada mais adiante no tópico "Programação".

# Módulo Seguidor de linha infravermelho

Este módulo é baseado em quatro sensores seguidores de linha, seu diferencial está no fato dele otimizar o projeto, uma vez que o caminho pode ser ao mesmo tempo monitorado em quatro trechos distintos, facilitando dessa forma a estratégia adotada. Cada sensor é independente e possui um trimpot de ajuste de luminosidade de detecção.

Distância de detecção: 1mm ~ 60cm (Ajustável);

Sinal de saída: TTL (Pode ser conectado direto ao microcontrolador)

Tipo de saída: Nível lógico baixo (0) quando obstáculo detectado, nível lógico alto (1) quando sem obstáculo;

LED: LED indica quando o sensor foi ativado (Obstáculo detectado);

![image](https://user-images.githubusercontent.com/32148244/33348735-43b8efb2-d476-11e7-9acb-b79d2e4840c6.png)

# Ponte H

![image](https://user-images.githubusercontent.com/31252029/33325477-2577fc2c-d431-11e7-980c-33445c453579.png)

•	(Motor A) e (Motor B) se referem aos conectores para ligação de 2 motores DC ou 1 motor de passo

•	(Ativa MA) e (Ativa MB) – são os pinos responsáveis pelo controle PWM dos motores A e B. Se estiver com jumper, não haverá controle de velocidade, pois os pinos estarão ligados aos 5v. Esses pinos podem ser utilizados em conjunto com os pinos PWM do Arduino

•	(Ativa 5v) e (5v) – Este Driver Ponte H L298N possui um regulador de tensão integrado. Quando o driver está operando entre 6-35V, este regulador disponibiliza uma saída regulada de +5v no pino (5v) para um uso externo (com jumper), podendo alimentar por exemplo outro componente eletrônico. Portanto não alimente este pino (5v) com +5v do Arduino se estiver controlando um motor de 6-35v e jumper conectado, isto danificará a placa. O pino (5v) somente se tornará uma entrada caso esteja controlando um motor de 4-5,5v (sem jumper), assim poderá usar a saída +5v do Arduino.

•	(6-35v) e (GND) – Aqui será conectado a fonte de alimentação externa quando o driver estiver controlando um motor que opere entre 6-35v. Por exemplo se estiver usando um motor DC 12v, basta conectar a fonte externa de 12v neste pino e (GND).

•	(Entrada) – Este barramento é composto por IN1, IN2, IN3 e IN4. Sendo estes pinos responsáveis pela rotação do Motor A (IN1 e IN2) e Motor B (IN3 e IN4).

# Conectando a ponte H ao Arduino:

![image](https://user-images.githubusercontent.com/31252029/33325588-769bbddc-d431-11e7-9241-14416fe183e1.png)

Após ser realizada a montagem e conexão do robô será iniciada a programação:
 

# Código

 O código começa com a definição das portas do arduino que serão associadas com o driver do motor.
  ```
int ENA = 3;
int ENB = 5; 
int IN1 = 8;
int IN2 = 7;
int IN3 = 9;
int IN4 = 6;
  ```
Em seguida o mesmo é feito para as entradas dos sensores de linha utilizados.

```
int sensorCentroEsquerda = 12;
int sensorCentroDireita = 11;
int sensorEsquerda = 13;
int sensorDireita = 10;

```

Depois são definidas as variáveis que serão utilizadas durante o programa.

```
int leituraEsquerda;
int leituraDireita ;
int leituraCentroEsquerda;
int leituraCentroDireita;
double erro = 0;
double input = 0;
double errSum, ultimoErro,dInput, kp, ki, kd;
double dT = 0;
long tempoFinal=0;
long tempo = 0 ;
double ultimaLeitura;
int x,y;
int constante = 150;
```
As variáveis de leitura irão guardar a informação referente a visualização da linha pelos sensores. As variaveis seguintes são utilizadas nos calculos referentes ao controlador do robo que resultara na definição da ação que este irá realizar. Por último as variáveis x e y que são as referentes a velocidade dos motores e a constante que é utilizada para definir um padrão de velocidade nas ações exercidas pelo carrinho.

Estas são as ações que o carrinho pode realizar, recebendo como variáveis os valores de x e y que referem a velocidade do motor de cada roda.

```
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

```

As combinações de HIGH e LOW para cada tipo de ação são utilizadas com base na referências da ponte H utilizada no drive do motor, cada sequência utilizada resulta na ação realizada.

É realizada uma limitação nos valores de x e y

```
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

```
Essa limitação é realizada para não ocorrer casos de movimentos bruscos no carrinho e resultando numa desestabilização da movimentação exigida para a corrida.

A função controle é utilizada para definir a ação que será utilizada no momento pelo carrinho, levando em conta os valores atuais de x e y para definir que ação será realizada.

```

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

```

A função de definição de erro é onde ocorre a maioria dos calculos do controlador. Aqui é calculado o input e com base nele o erro que servira para os calculos de kp, ki e kd.

```
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

```

O calculo do input foi encontrado com discussões em sala e testes para melhor apropriar a movimentação do carrinho durante a movimentação na pista, os valores que multiplicam as variaveis de leitura são pesos associados defido a importância de cada acionamento durante a corrida.

A função leitura é onde são realizadas as leituras das informações dos sensores, estas são armazenadas nas variaveis.

```
void leitura(){
  leituraEsquerda = digitalRead(sensorEsquerda);
  leituraDireita = digitalRead(sensorDireita);
  leituraCentroDireita = digitalRead(sensorCentroDireita);
  leituraCentroEsquerda = digitalRead(sensorCentroEsquerda);
}

```

# Resultados

O robô foi construído com êxito e participando da competição, ficando na sexta posição de um total onze competidores. 

A dificuldade encontrada no projeto foi na regulagem do sensor em relação a pista, que apresentava ondulações, ocasionando erros de leitura.

![image](https://user-images.githubusercontent.com/32148244/33349010-23f888e4-d477-11e7-9096-6a8fcf3a6582.png)

Foram substituídos os sensores infravermelhos, que antes eram idênticos aos sensores do projeto do robô seguidor de linha, os sensores escolhidos foram este do módulo seguidor de linha, devido o seu range ser variado, conseguimos minimizar os erros de medição.

Segue imagens do robô concluído.

![image](https://user-images.githubusercontent.com/32148244/33348972-fe2960de-d476-11e7-9587-e7075e5023f4.png)

![image](https://user-images.githubusercontent.com/32148244/33348991-0fbbdce6-d477-11e7-96c8-4c1e0c239602.png)

![image](https://user-images.githubusercontent.com/32148244/33349010-23f888e4-d477-11e7-9096-6a8fcf3a6582.png)

