# CG
Exercícios de Computação Gráfica feitos na Faculdade

## Exercício 1
Escreva um programa que imprima um ponto azul de
tamanho 5.0 na posicão em que houver um clique de
botão esquerdo do mouse. Inicialmente, o ponto deve
ficar nas coordenadas (0,0). (Este exercício será
fundamental para aprender: (a) a ajustar as coordenadas
do mouse e da janela; (b) a desenhar o ponto na função
correta; (c) a guardar as coordenadas lidas).

## Exercicio 2

Escreva um programa que realize duas funções: a de
imprimir o ponto nas coordenadas do mouse do exercício
1 e de alterar a cor do ponto. Novamente, o ponto inicial
é azul e está nas coordenadas (0,0). Para mudar a cor, o
usuário digitará as teclas de 0 a 9. Cada tecla deverá ter
cores indexadas previamente escolhidas. Escolha as cores
que desejar.

## Exercicio 3

Crie um programa com duas funções: a de imprimir uma linha entre 
dois pontos quaisquer e a de alterar a cor da linha. Uma linha inicial
entre os pontos (0,0) e (0,0), azul, deve ser traçada. A linha muda de 
posição de acordo com as coordenadas dadas por um clique inicial e um 
clique final com o botão esquerdo do mouse. As cores são selecionadas da 
mesma maneira que no exercício 2

## Exercicio 4

Escreva um programa que contenha três funções: as funções de traçar 
uma linha e de mudar a cor do exercício 3, e uma função de traçar 
triângulos. Inicialmente, deve ser impressa uma linha azul de 
coordenadas (0,0) - (0,0). Apenas uma figura deve ser apresentada 
de cada vez na tela. As figuras anteriores são apagadas. Caso o usuário 
clique na tecla 'r' ou 'R', a função de traçar retas é ativada. Caso o 
usuário clique na tecla 't' ou 'T', a função de traçar triângulos é 
ativada. O traçado da reta continua da mesma maneira do exercício 3. 
No traçado de triângulos, os três vértices são determinados por três 
cliques seguidos com o botão esquerdo do mouse

## Exercicio 5

Crie um programa com duas funções:

* A de imprimir uma linha entre dois pontos quaisquer.
* A de alterar a cor da linha.

Uma linha inicial entre os pontos (0, 0) e (0, 0) azul deve ser traçada.
A linha muda de posição de acordo com as coordenadas dadas por um clique inicial e um clique final com o botão esquerdo do mouse.
Utilize o algoritmo de Bresenham para traçar a linha (não utilizar GL_LINES).
Para mudar a cor, o usuário digitará as teclas de 0 a 9.
Cada tecla deverá ter cores indexadas previamente escolhidas. Escolha as cores que desejar.
A reta deve ser desenhada no centro da janela.

## Exercicio 8

Implementar o algoritmo de Bresenham para o traçado
de circunferências, considerando que estas podem estar
centralizadas na origem ou fora da origem

## Exercício 9

Neste exercício, nosso objetivo é criar três desenhos diferentes utilizando as funções do OpenGL, inicialmente sem o uso das funções glTranslatef, glRotatef e glScalef. Posteriormente, repetiremos os mesmos desenhos incorporando essas funções para aplicar transformações.

1. Flor com Pétalas Girando em Torno do Miolo:

    * Desenho inicial sem o uso de transformações.
    * Desenho final com glTranslatef, glRotatef e glScalef.

2. Carro com Movimento para Frente e para Trás, com Rodas Girando Conforme o Movimento:

    * Desenho inicial sem o uso de transformações.
    * Desenho final com glTranslatef, glRotatef e glScalef.

3. Robô com Movimento de Braços e Pernas:

    * Desenho inicial sem o uso de transformações.
    * Desenho final com glTranslatef, glRotatef e glScalef.

Esta abordagem nos permitirá explorar as transformações em OpenGL para criar animações e movimentos mais dinâmicos nos desenhos. Se você precisar de informações adicionais ou tiver alguma dúvida sobre como implementar esses desenhos, por favor, sinta-se à vontade para perguntar.

## Exercicio 14

**Implementar o algoritmo de recorte de linha 2D de Cohen-Sutherland**

Plotar um quadro semelhante ao exercício anterior. 

Dados um clique inicial e um clique final com o botão esquerdo do mouse, que darão os pontos inicial e final da linha, somente devem ser mostradas as partes da
linha que se encontram dentro do quadro.

O recorte deve ser feito seguindo o algoritmo de Cohen-Sutherland