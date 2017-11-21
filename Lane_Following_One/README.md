
Procedimentos

Primeiramente no codigo foram definitas todas as portas do arduino as quais seriam usadas, sendo as portas pwn utilizadas para as ligações com o driver de ponte H utilizado para realizar os movimentos dos motores ligados as duas rodas do carro didático. As ligações entre o arduino e o driver podem ser vista na figura abaixo:

![image](https://user-images.githubusercontent.com/31252029/33086506-87ca34f0-cec6-11e7-8afc-34b9e8a2e0f5.png)


Figura 3 – Ligações do Arduino com o Driver ponte H.

A partir de testes foram encontrados valores ideais para as contantes kp, ki e kd, estas vistas no programa, definindo assim uma melhor resposta quando exigido o processamento do sensor.

As funções de movimento são definidas a partir do entendimento do driver de ponte H utilizado. Sendo cada uma dessas funções relacionadas ao movimento realizado pelos motores.

Sensor de Linha

O sensor de linha possui 3 portas distintas uma para as posições esquerda(L), centro(C) e direita(R), sendo elas associadas a um sensor que detecta a presença da linha e manda a informação caso a linha seja encontrada.

![image](https://user-images.githubusercontent.com/31252029/33086571-b46ebe0e-cec6-11e7-804a-1466cef5c574.png)

Figura 4 – Sensor de Linha utilizado.

No caso deste projeto as portas L, C e R foram associadas as portas 12, 2 e 4 respectivamente do arduino, como pode ser visto no programa.

Uso do Controlador PID

O uso do controlador PID se resumiu ao cálculo inserido no programa, o cálculo em questão é o V = (300* l + 200 * c + 100 * r)/(l+c+r), onde as variáveis l, r e c são as referidas do sensor de linha como abordato acima. As possibilidades de resultado de cada variável é HIGH ou LOW, resultando em um valor diferenciado para o V dependendo de qual sensor estiver ligado no momento do cálculo. O V então é diminuido de um SetPoint, este definido 200 a partir de testes, para então encontrar um erro.

O erro é utilizado para o cálculo das três variáveis do controlador PID, sendo elas P, I e D. Onde nesses cálculos então inseridos as constantes kp, ki e kd para o P, I e D respectivamente.

as fórmulas de cada variável são:

P = erro * kp

I += erro* dt * ki

D = (kd*(V - Va))/dt

As variáveis kp, ki e kd são definidas por testes realizados nas pistas de teste. O kp foi achado de maneira bem simples, sendo o mais fácil dos três de se encontrar um valor adequado para o propósito. O mais difícil foram as combinações ki e kd pois os dois são complementos e se não encontrado um valor razoável o carro tinha movimentos instáveis.

O resultado do cálculo da variável V é então subtraido do setPoint escolhido( no caso 200 ) para achar o valor do erro. Este erro encontrado será o utilizado nas equações acima para achar as variaveis P, I e D. Com os resultados definidos é realizado outro cálculo para definir os valores que irão alimentar as funções definidas para cada movimento, sendo elas: frente, direita, esquerda e trás. As variaveis x e y são calculadas com os valores encontrados para P, I e D:

x = constante + (P + I + D).

y = constante - (P + I + D).

Essa constante utilizada tambem foi definida a partir de testes realizados buscando melhor otimização na hora do deslocamento realizado pelo carro.

Com as variaveis x e y definidas, dependendo da situação imposta uma das funções ditas acima(frente, direita, esquerda ou trás) será utilizada.
