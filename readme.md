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

## 📂 Arquivos neste repositório

- `readme.md`: este arquivo.
- `bot_A` e `bot_B`: executáveis com um comportamento básico, sem nenhuma estratégia.
- `bot_C` e `bot_F`: executáveis com uma estratégia simples.
- `main.c`: programa principal, é quem inicializa as variáveis e chama as funções no momento adequado do jogo.
- `cards.c`: funções relacionadas às cartas.
- `hand.c`: funções relacionadas à mão do bot.
- `game.c`: funções que atualizam as informações do bot a partir dos acontecimentos do jogo.
- `strategy.c`: funções que definem as escolhas de jogadas do bot.
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
