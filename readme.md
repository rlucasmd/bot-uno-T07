# 🤖 BOT-UNO
Este é um projeto de um bot implementado em linguagem C, capaz de jogar essa [versão](https://github.com/amccampos/uno/blob/main/readme.md) do uno.

O projeto é uma das atividades da disciplina de **Introdução às Tecnicas de Programação**.
* **Instituição**: UFRN
* **Semestre**: 2022.2
* **Turma**: T07
* **Curso**: Bacharelado em Tecnologia da Informação
* **Docente**: Wellington Silva de Souza

## 🚀 Equipe
Dupla responsável pelo desenvolvimento do bot:
- Antonio Matheus
- Ranieri Lucas

## 💡 Ideia
Inicialmente, a ideia seria criar um bot executável para jogar uma partida inteira de UNO e ser capaz de tomar certas decisões com o objetivo de maximizar as chances de vitória 🏆️, utilizando o máximo de conhecimento adquirido durante a disciplina.

## 🧠 Estratégia 
Nosso bot atualmente segue a seguinte estratégia:
- A cada rodada nosso bot se encarrega de verificar as posições de quais cartas na nossa mão podem ser descartadas, a partir daí ele calcula qual a melhor jogada a ser realizada com base em alguns critérios.
- primeiramente verificamos dois dados(qual o próximo bot a jogar e quantas cartas ele tem), se a quantidade de cartas do próximo bot for menor que nossa então verificamos se há algum valete ou coringa que possa ser descartado, preferencialmente optamos por descartar um valete, guardando o coringa para último caso.
- logo após verificamos se há alguma rainha a ser jogada, se sim, verificamos se o bot anterior não tem o naipe da rainha (comparando o vetor de cartas que o bot anterior possivelmente não tem), se sim, jogamos ela para garantir que o jogador anterior compre uma carta.
- Em seguida, Verifica se há algum rei e se o próximo jogador tem menos cartas que o nosso, se sim o rei é descartado. 
- Por fim fazemos uma busca de alguma carta a qual o naipe ou o valor dela foi encontrada no array de possíveis cartas que o próximo bot não tenha, se em nenhum desses casos for encontrado uma carta, jogamos a primeira carta do array de possíveis cartas.



## 📂 Arquivos neste repositório

- `readme.md`: este arquivo.
- `bot_A` e `bot_B`: executáveis com um comportamento básico, sem nenhuma estratégia.
- `bot_C` e `bot_F`: executáveis com uma estratégia simples.
- `main.c`: programa principal, é quem inicializa as variáveis e chama as funções no momento adequado do jogo.
- `cards.c`: funções relacionadas às cartas.
- `hand.c`: funções relacionadas à mão do bot.
- `game.c`: funções que atualizam as informações do bot a partir dos acontecimentos do jogo.
- `strategy.c`: funções que definem as escolhas de jogadas do bot.
- `debbuger.c`: funções para debugarmos o código durante o desenvolvimento do bot.
- `Makefile`: conjunto de comandos para automatizar o processo de compilação e execução.
- `uno`: programa gerenciador do jogo Uno.

Os arquivos `.h` são cabeçalhos com definições ou assinaturas de funções.

## ▶️ Executando o bot
O gerenciador do jogo se encontra no formato binário do Linux, portanto você precisará executá-lo sobre esse sistema operacional ou em algum subsistema para Linux. Outra opção viável é executar o jogo via replit.

Após clonar o repositório, `compile` os arquivos, para isso basta digitar o comando:
```sh
make all
```
As instruções contidas no `Makefile` irão se encarregar de compilar todos os arquivos necessários para a criação do executável do bot. Note que o Makefile define o nome do executável como `bot_D`.

Após a criação do executável, para `iniciar` uma partida basta digitar o comando:
```sh
make run
```
Note que o `MakeFile` está executando uma partida de quatro jogadores, você pode alterar isso no arquivo, mudando quantos e quais bots estarão na partida (lembrando que é preciso ter entre 2 e 4 bots para jogar).
Caso não queira fazer a alteração no Makefile, basta digitar no terminal:
```sh
./uno bot_NAME1 bot_NAME2
```
