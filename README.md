# Compilador C-

Este projeto implementa um compilador para a linguagem C-.

## Pré-requisitos
- Algum compilador C++11
- Make
- Bison e Flex
- CMake (para testes, se necessário)

## Compilação
No diretório raiz do projeto, execute:
```
make
```
Isto irá gerar o executável `compiler`.

Ou para compilar com clang:
```
make CC=clang CXX=clang++
```

## Execução
Para executar o compilador, use:
```
./compiler <arquivo de entrada>
```
*Exemplo:*
```
./compiler tests/sort.txt
```

## Testes
Para compilar e executar os testes usando googletest, execute:
```
make test
```

## Limpeza
Para remover arquivos objetos e binários, execute:
```
make clean
```
