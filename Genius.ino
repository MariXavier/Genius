/* ============ GENIUS ============


 * Descrição: Genius foi um brinquedo muito popular na década de 1980 e tinha como objetivo estimular a memorização de cores e sons.
 * O jogo possui 4 botões que se iluminam em seqüência. Cabe ao jogador repetir o processo sem errar.


 
 ~~~~~~ DECLARAÇÃO DAS VARIÁVEIS ~~~~~~~~~~~~
Vs: vetor para armazenar a sequência das luzes
Vj: vetor para armazenar a sequência das jogadas
LEDs azul, amarelo, verde e vermelho conectados nas entradas 2, 3, 4 e 5 do arduino, respectivamente.
Botões azul, amarelo, verde e vermelho conectados nas entradas 8, 9, 10 e 11 do arduino, respectivamente.
btnAzul, btnAmarelo, btnVerde e btnVermelho serão responsáveis por armazenar o estado do botão.
*/

int aleatorio1=0;
int Vs[30]; 
int Vj[30]; 
int azul = 2;
int amarelo = 3;
int verde = 4;
int vermelho = 5;
int rodada = 0;
int bAzul = 8;
int bAmarelo = 9, bVerde = 10, bVermelho = 11;
int btnAzul = 0, btnAmarelo = 0, btnVerde = 0, btnVermelho = 0;

void setup()
{
  pinMode(azul, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(bAzul, INPUT_PULLUP);
  pinMode(bAmarelo, INPUT_PULLUP);
  pinMode(bVerde, INPUT_PULLUP);
  pinMode(bVermelho, INPUT_PULLUP);
}

void loop()
{
  //função random gera um número aleatório de 0~3 e armazena na variável aleatorio1.  
  aleatorio1 = random(4);
  
  //o valor gerado é armazenado no vetor Vs
  Vs[rodada] = aleatorio1;
  
  //chama a função Sequencia_leds
  Sequencia_leds();
  
  //chama a função Vez_do_jogador
  Vez_do_Jogador();
    
  rodada++;
 
 //delay de 1,5 segundos para que a próxima rodada comece.
  delay(1500);
}

void Sequencia_leds()
{
  /*A função Sequencia_leds é reponsável por acender os LEDS conforme os números aleatórios são gerados e armazenados no vetor Vs[rodada].
 * Caso o número aleatório seja 0, o LED azul se acende por 0,5 segundos e apaga. 
 * Temos um delay de 0,5 segundos para que o próximo LED acenda.
 * Caso o número aleatório seja 1, o LED amarelo acende. Caso seja 2, o LED verde acende e, por fim, caso seja 3, acende o LED vermelho.
 */
    for(int j=0;j<=rodada;j++)
    {      
      if(Vs[j] == 0)
      {
        digitalWrite(azul,HIGH);
        delay(500);
        digitalWrite(azul,LOW);
        delay(500);
      }
      else if(Vs[j] == 1)
      {
        digitalWrite(amarelo,HIGH);
        delay(500);
        digitalWrite(amarelo,LOW);
        delay(500);
      }
      else if(Vs[j] == 2)
      {
        digitalWrite(verde,HIGH);
        delay(500);
        digitalWrite(verde,LOW);
        delay(500);
      }
      else
      {    
        digitalWrite(vermelho,HIGH);
        delay(500);
        digitalWrite(vermelho,LOW);
        delay(500);
      }
      
    } //final do for
 
}

/*
 * A função Vez_do_Jogador inicia com uma booleana jogada = false para que o programa entre obrigatoriamente no while e só saia caso jogada retorne true,
 * do contrário, continuará dentro do while até mudar essa condição.
 * Dentro do while temos a leitura dos botões e, caso um botão seja pressionado, o LED correspondente acende e o valor desse LED (0~3) é armazenado no vetor Vj.
 * Depois de pressionado, a booleana passa a ter valor true e o while termina.
 * A próxima etapa consiste em verificar se o LED que foi aceso na função Sequencia_leds corresponde ao led que foi aceso na função Vez_do_Jogador.
*/

void Vez_do_Jogador()
{
  for(int k=0;k<=rodada;k++)
  {
    bool jogada = false;
    
    while(!jogada)
    {          
      btnAzul = digitalRead(bAzul);
      btnAmarelo = digitalRead(bAmarelo);
      btnVerde = digitalRead(bVerde);
      btnVermelho = digitalRead(bVermelho);

      if(btnAzul == LOW)
      {
        digitalWrite(azul,HIGH);
        delay(400);
        digitalWrite(azul,LOW);
        Vj[k] = 0;
        jogada = true;
      }

      if(btnAmarelo == LOW)
      {
        digitalWrite(amarelo,HIGH);    
        delay(400);
        digitalWrite(amarelo,LOW);
        Vj[k] = 1;
        jogada = true;
      }
      
      if(btnVerde == LOW)
      {
        digitalWrite(verde,HIGH);
        delay(400);
        digitalWrite(verde,LOW);
        Vj[k] = 2;
        jogada = true;
      }
      
      if(btnVermelho == LOW)
      {
        digitalWrite(vermelho,HIGH);
        delay(400);
        digitalWrite(vermelho,LOW);
        Vj[k] = 3;
        jogada = true;
      }  
      
     
    } //final while 
    
    /*Caso o valor do botão apertado seja diferente do LED reproduzido na sequência, todos os LEDS 
     * acendem e apagam 3 vezes sendo o de última de longa duração
     */
    if(Vj[k]!= Vs[k])
    {
      digitalWrite(azul,HIGH);
      digitalWrite(amarelo,HIGH);
      digitalWrite(verde,HIGH);
      digitalWrite(vermelho,HIGH);
      delay(200);
      digitalWrite(azul,LOW);
      digitalWrite(amarelo,LOW);
      digitalWrite(verde,LOW);
      digitalWrite(vermelho,LOW);
      delay(200);
      digitalWrite(azul,HIGH);
      digitalWrite(amarelo,HIGH);
      digitalWrite(verde,HIGH);
      digitalWrite(vermelho,HIGH);
      delay(200);
      digitalWrite(azul,LOW);
      digitalWrite(amarelo,LOW);
      digitalWrite(verde,LOW);
      digitalWrite(vermelho,LOW);
      delay(200);
       digitalWrite(azul,HIGH);
      digitalWrite(amarelo,HIGH);
      digitalWrite(verde,HIGH);
      digitalWrite(vermelho,HIGH);
      delay(1000);
      digitalWrite(azul,LOW);
      digitalWrite(amarelo,LOW);
      digitalWrite(verde,LOW);
      digitalWrite(vermelho,LOW);
      delay(1000);

      /*O jogo termina e é necessário sair do for e zerar a rodada. 
       * Como estamos "zerando" a variável rodada na função vez_do_jogador e, logo após seu término temos um rodada++, foi necessário definir
       * rodada = - 1 para que o jogo reiniciasse na rodada 0 e não na rodada 1, caso aconteceria se definíssemos rodada como sendo 0 (rodada=0).
       */
      rodada = -1;
      break;
    } //final do if  
  } //final for    
} //final função Vez_do_Jogador
      
      
/* ~~~~~~ IMPLEMENTAÇÕES FUTURAS ~~~~~~~~~~~~
 * Display LCD para marcar a rodada e o recorde;
 * Acrescentar um buzzer;
 * Níveis de dificuldade igual no brinquedo original;
 * Aumentar/diminuir a velocidade da reprodução da sequência dos LEDs
*/      
      
      
