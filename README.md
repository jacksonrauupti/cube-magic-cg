# Cubo Mágico 

O cubo mágico é um projeto de computação gráfica cujo objetivo é possibilitar
a interação do usuário com um protótipo 3D de um cubo 3x3. Permitindo as rotações 
necessárias para solucionar o problema - deixar todas as faces com uma mesma cor.

#### Teclas de movimentação da câmera 

1. tecla a : movimentação da câmera para a esquerda
2. tecla d : movimentação da câmera para a direita
3. tecla w : movimentação da câmera para cima 
4. tecla s : movimentação da câmera para baixo 
5. tecla z : aproximação da câmera 
6. tecla e : distanciamento da câmera 

### Teclas de movimentação do cubo

Por padrão as rotações são no sentido horário. Para alterar o sentido basta pressionar “o”. 

* u (up)
* d (down)
* l (left) 
* r (right)
* f (front)
* b (back) 

A tecla “v” possibilita a troca de visualização para 2d ou 3d.

#### Compilar e executar o projeto 

Compilação: 
g++ src/main.cpp src/Matrix.cpp src/Cube.cpp -o main -lGL -lGLU -lglut -g -std=c++11

Executar: ./main



