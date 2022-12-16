# 🤖 BOT-UNO
Este é um projeto de um bot implementado em linguagem C, capaz de jogar essa [versão](https://github.com/amccampos/uno/blob/main/readme.md) do uno.

# 💡 Ideia
Inicialmente, a ideia seria criar um bot executável para jogar uma partida inteira de UNO e ser capaz de tomar certas decisões com o objetivo de maximizar as chances de vitória 🏆️, utilizando o máximo de conhecimento adquirido durante a disciplina.

# 🚀 Equipe
Dupla responsável pelo desenvolvimento do bot:
- Antonio Matheus
- Ranieri Lucas

## ▶️ Executando o bot
O gerenciador do jogo se encontra no formato binário do Linux, portanto você precisará executá-lo sobre esse sistema operacional ou em algum subsistema para Linux. Outra opção viável é executar o jogo via replit.

Após clonar o repositório, `compile` os arquivos, para isso basta digitar o comando:
```sh
make all
```
As instruções contidas no `Makefile` irão se encarregar de compilar todos os arquivos necessários para a criação do executável do bot. 

Após a criação do executável, para `iniciar` uma partida basta digitar o comando:
```sh
make run
```
Note que o `MakeFile` está executando uma partida de quatro jogadores, você pode alterar isso no arquivo, mudando quantos e quais bots estarão na partida (lembrando que é preciso ter entre 2 e 4 bots para jogar).
Caso não queira fazer a alteração no Makefile, basta digitar no terminal:
```sh
./uno bot_NAME1 bot_NAME2
```
