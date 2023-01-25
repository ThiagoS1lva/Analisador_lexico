# Analisador_lexico

# DESCRIÇÃO TEORICA DO ANALISADOR LÉXICO

  Um analisador léxico, também conhecido como scanner ou tokenizer, é uma
parte importante de um compilador ou interpretador de linguagem de programação.
Ele tem como função dividir o código fonte em uma sequência de tokens, que são
pequenos pedaços de código que representam palavras-chave, operadores,
identificadores e outros elementos sintáticos da linguagem.
  Para realizar essa tarefa, o analisador léxico utiliza uma tabela de símbolos,
que armazena as palavras-chave e outros elementos da linguagem, e expressões
regulares, que são usadas para reconhecer os diferentes tipos de tokens no código
fonte. Ele varre o código fonte caractere por caractere, procurando por padrões que
correspondam aos tokens previstos na tabela de símbolos. Quando um token é
reconhecido, ele é adicionado à lista de tokens gerada pelo analisador léxico.
  Em geral, o analisador léxico é a primeira etapa do processo de análise
sintática, e os tokens gerados são usados pelo analisador sintático para reconhecer
a estrutura gramatical do código e verificar se ele segue as regras da linguagem.

# DESCRIÇÃO DA ESTRUTURA DO ANALISADOR LÉXICO

  A estrutura de um analisador léxico geralmente é composta por três partes
principais: a tabela de símbolos, a máquina de estado, tratamento de erros e o
gerador de tokens.
● A tabela de símbolos é um banco de dados que armazena informações sobre
as palavras-chave, operadores, identificadores e outros elementos sintáticos
da linguagem. Ele é usado pelo analisador léxico para reconhecer os tokens
no código fonte e fornecer informações adicionais, como o tipo de token e o
valor associado a ele.
● A máquina de estado é a parte do analisador léxico responsável por varrer o
código fonte caractere por caractere e reconhecer os tokens. Ele funciona
com base em uma série de estados finitos, que são definidos pela tabela de
símbolos. Cada estado representa uma possível configuração do scanner e é
responsável por reconhecer um conjunto específico de tokens. A máquina de
estado muda de estado conforme os caracteres do código fonte são lidos.
● A máquina de estado também consegue identificar os erros no código fonte e
expressar qual foi o caractere que não pertence a linguagem para que
posteriormente seja removida.
● O gerador de tokens é responsável por gerar os tokens reconhecidos pela
máquina de estado e adicioná-los à lista de tokens gerada pelo analisador
léxico. Ele também pode realizar outras tarefas, como remover comentários e
espaços em branco do código fonte antes de dividi-lo em tokens.

# FUNCIONAMENTO DO ANALISADOR LÉXICO

  Neste trabalho foi utilizado a linguagem C++ para o desenvolvimento do
analisador léxico. A linguagem para qual construímos o analisador léxico é
constituída de 5 padrões:
- Palavras reservadas: program, var, begin, end, if, then, else, while, do, int.
- Números: apenas números inteiros.
- Identificadores: Qualquer combinação de letras e números, que comecem
por uma letra.
- Operadores de relação: = , <> , < , <= , >= , >.
- Operadores aritméticos: +, -, *, div.
  Para além disso, o analisador léxico é capaz de identificar o sinal de
atribuição (=:), vírgula, ponto e vírgula, dois pontos, ponto e parênteses.
O funcionamento é dividido em duas etapas: a análise léxica e a geração de
tokens.

Análise léxica: O analisador léxico começa lendo o código fonte caractere
por caractere. Ele utiliza a tabela de símbolos para reconhecer os tokens no código
fonte e a máquina de estado para determinar em que estado ele se encontra a cada
momento. A máquina de estado é controlada por expressões regulares que
correspondem aos diferentes tipos de tokens. Quando um token é reconhecido, o
analisador léxico armazena as informações relevantes, como o tipo de token e o
valor associado a ele.

Geração de tokens: Depois de ler o código fonte, o analisador léxico gera
uma lista de tokens que representam o código fonte. Essa lista é usada pelo
analisador sintático para reconhecer a estrutura gramatical do código e verificar se
ele segue as regras da linguagem. Cada token é composto por um tipo e um valor.

Para simular a máquina de estado foi utilizado a função “switch case” do C++,
onde cada case é um estado:

● Do case 0 até o 8 é para a análise dos operadores de relação.
● Case 9 até o 11 analisa os ID’s e as palavras reservadas.
● Case 12 até o 16 são os operadores aritméticos.
● Case 17 até o 19 são os números
● Do Case 20 até o 28 é os parênteses, vírgula, ponto e vírgula, dois pontos,
ponto e sinal de atribuição.
● O Case 29 é para o tratamento de erro para caso acontecer de no código
fonte estar presente algum caractere que não pertença a linguagem.

No “main” do programa, o código fonte é lido através da string “code” e depois a
função “proximo_token()” é chamada para rodar o analisador léxico.

# Trabalho realizado por Pedro Henrique, Pedro vítor e Thiago Oliveira do Curso de Ciência da Computação da UERJ no periodo de 2022.1 em Janeiro de 2023.
