# Regras Semânticas da Linguagem C-

A seguir, estão as principais regras da linguagem C-:

1. **Programa e Declarações**
   - Um programa é composto por uma lista de declarações, que podem ser de variáveis ou funções, em qualquer ordem.
   - Deve haver pelo menos uma declaração.

2. **Declaração de Variáveis**
   - As variáveis podem ser declaradas como simples ou como matrizes.
   - Matrizes devem ter um tamanho especificado por um número inteiro.

3. **Declaração de Funções**
   - Funções devem ser declaradas com um tipo de retorno (`int` ou `void`).
   - Podem ter parâmetros, que podem ser variáveis simples ou matrizes.

4. **Composto de Declarações**
   - Blocos de código são delimitados por chaves `{}`.
   - Podem conter declarações locais e uma lista de comandos.

5. **Comandos (Statements)**
   - **Expressão-declaração:** Uma expressão seguida por um ponto e vírgula (ex.: atribuições, chamadas de funções).
   - **Seleção-declaração (if-else):** Avalia uma expressão; se for diferente de zero, executa o primeiro comando; se for zero, executa o segundo, se existir.
   - **Iteração-declaração (while):** Repete a avaliação da expressão enquanto ela for diferente de zero, executando o comando associado.
   - **Retorno-declaração (return):** Pode retornar um valor ou não, conforme o tipo de retorno da função (funções `void` não retornam valor).

6. **Expressões**
   - **Atribuição:** A variável à esquerda recebe o valor da expressão à direita; o valor atribuído é o valor retornado pela expressão.
   - **Expressões Simples:** Podem incluir operadores relacionais (`<=, <, >, >=, ==, !=`), que retornam 1 se verdadeiros e 0 se falsos.
   - **Expressões Aditivas e Multiplicativas:** Seguem a precedência e associatividade dos operadores aritméticos (`+, -, *, /`), considerando divisão inteira (truncamento do resto).

7. **Fatores**
   - Podem ser expressões entre parênteses, variáveis, chamadas de funções ou números.
   - Variáveis de matriz devem ser indexadas, exceto quando usadas como argumentos para funções que esperam matrizes.

8. **Chamadas de Funções**
   - Funções devem ser declaradas antes de serem chamadas.
   - O número de argumentos na chamada deve corresponder ao número de parâmetros na declaração.
   - Parâmetros de matriz devem corresponder a variáveis de matriz.

9. **Funções Predefinidas**
   - `int input(void)`: Lê um valor inteiro da entrada padrão.
   - `void output(int x)`: Imprime um valor inteiro na saída padrão, seguido de uma nova linha.

10. **Restrições Adicionais**
    - Todas as variáveis e funções devem ser declaradas antes de serem usadas, exceto as funções predefinidas `input` e `output`.
    - Atribuições e operações devem obedecer às declarações de tipos (não é possível atribuir um valor a uma variável não declarada).
    - Índices de matrizes devem ser inteiros não negativos (índices negativos causam a interrupção do programa).

Essas regras garantem que o compilador C- possa verificar a correção dos programas em termos de tipos, escopo e uso correto de variáveis e funções.
