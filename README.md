# SEGUIDOR DE PISTA


## RESUMO

O objetivo deste trabalho é implementar a lógica de programação e a montagem mecânica de um robô móvel para se mover de maneira autônoma completando qualquer circuito sem sair da pista.

## FUNDAMENTAÇÃO TEÓRICA

Controlador PID - Controlador proporcional integral derivativo, é uma técnica de controle de processos que une as ações derivativa, integral e proporcional, fazendo assim com que o sinal de erro seja minimizado pela ação proporcional, zerado pela ação integral e obtido com uma velocidade antecipativa pela ação derivativa.
Hoje em dia há várias maneiras de melhorar o desempenho e o tempo de realização de atividades na área da automação. Uma das formas bem conhecidas no ramo industrial é através do algoritmo PID (Proporcional-Integral-Derivativo). “O sucesso dos controladores PID também é reforçado pelo fato de que muitas vezes representam o componente fundamental para os sistemas de controle mais sofisticados que podem ser implementados quando a lei básica de controle não é suficiente para obter os desempenhos requeridos [VISIOLI, 2006]”.
O controlador PID e seus componentes na forma de controles PD e PI representam formas de controladores que utilizam operações de derivadas e integrais na compensação dos sistemas de controle. Em geral, pode-se considerar o projeto dos controladores dos sistemas de controle como um problema de projeto de filtros; portanto, existe uma grande quantidade de possíveis esquemas. Do ponto de vista da filtragem, o controlador PD é um filtro passa-alta e o controlador PI é um filtro passa- baixa. [GOLNARAGHI, 2012].



O algoritmo PID pode ser definido por:

![image](https://user-images.githubusercontent.com/32208559/33318226-1a7998e0-d421-11e7-9aaf-709a7f0278fa.png)

Figura 1- Expressão para o controlador PID

### MATERIAIS E EQUIPAMENTOS NECESSÁRIOS:

Foram usados motores, ponte H, sensores do tipo infravermelho, arduino duemilanove como controlador e para ajustar a malha PID foi usada a técnica “tentativa e erro”.

### ATUADORES

• Motores.
 
 Motor é um atuador rotativo ou linear que garante o controle, velocidade e precisão
em aplicações de controle de posição em malha fechada.

• Ponte h
 
 Ponte H é um circuito electrónico que permite variar velocidades de um motor DC,
assim como comutar o sentido de rotação dos motores, através de um sinal PWM. Estes
circuitos são muito utilizados em robótica e estão disponíveis em circuitos prontos ou
podem ser construídos por componentes.

### SENSORES

• Sensores infravermelho
 
 Os sensores infravermelhos são amplamente utilizados para a percepção do ambiente
e detecção de objetos ou pessoas em muitas aplicações robóticas e residêncial. Estes
sensores são muito bem-sucedidos em termos de eficiência de custos, tempo de
processamento e precisão.

### CONTROLADOR

• Arduino duemilanove.
 
 O arduino é nada mais que um microcontrolador com várias modificações voltado
para prototipação de projetos interativos, sendo o mesmo open (hardware e software) de
fácil manuseio, baixo custo e flexível.

## LISTA DE MATERIAIS

• Chapa metálica ou plástico.

• Rodas para o motor.

• Protoboard, fiação e bateria 9v.

• 4 Motores.

• 4 Sensores infravermelho.

1 Arduino Duemilanove

1 Drive ponte H

1 Chassi de Carro didático

1 Modulo sensor de linha

Cabos para conexão


## BIBLIOGRAFIA

GOLNARAGHI, M. F; KUO, Benjamin C. Sistemas de controle automático. Tradução e revisão técnica: Fernando Ribeiro da Silva.  9.Ed. Rio de Janeiro, 2012
VISIOLI, Antonio. Practical PID control. Springer, 2006.






