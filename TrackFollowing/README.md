
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



  
	
  
