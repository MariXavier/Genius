/*
=================================================================================================================================================
      GENIUS
=================================================================================================================================================

* Descrição: Genius foi um brinquedo muito popular na década de 1980 e tinha como objetivo estimular a memorização de cores e sons.
* O jogo possui 4 botões que se iluminam em seqüência. Cabe ao jogador repetir o processo sem errar.

=================================================================================================================================================
      DECLARAÇÃO DAS VARIÁVEIS
=================================================================================================================================================
* vetSequenciaLeds: vetor para armazenar a sequência das luzes
* vetSequenciaJogadas: vetor para armazenar a sequência das jogadas
* LEDs azul, amarelo, verde e vermelho conectados nas entradas 2, 3, 4 e 5 do arduino, respectivamente.
* Botões: btnAzul, btnAmarelo, btnVerde e btnVermelho conectados nas entradas 8, 9, 10 e 11 do arduino, respectivamente.
* estadoBotaoAzul, estadoBotaoAmarelo, estadoBotaoVerde e estadoBotaoVermelho serão responsáveis por armazenar o estado do botão.
* aleatorio: variável para armazenar um número entre 0 e 3 que será gerado aleatoriamente.
* rodada: responsável pelo número de rodadas do jogo.
*/

int aleatorio=0;
int vetSequenciaLeds[30]; 
int vetSequenciaJogadas[30]; 
int azul = 2;
int amarelo = 3;
int verde = 4;
int vermelho = 5;
int rodada = 0;
int btnAzul = 8, btnAmarelo = 9, btnVerde = 10, btnVermelho = 11;
int estadoBotaoAzul = 0, estadoBotaoAmarelo = 0, estadoBotaoVerde = 0, estadoBotaoVermelho = 0;

void setup()
{
  pinMode(azul, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(btnAzul, INPUT_PULLUP);
  pinMode(btnAmarelo, INPUT_PULLUP);
  pinMode(btnVerde, INPUT_PULLUP);
  pinMode(btnVermelho, INPUT_PULLUP);
}

void loop()
{
  //função random gera um número aleatório de 0~3 e armazena na variável aleatorio.  
  aleatorio = random(4);
  
  //o valor gerado é armazenado no vetor vetSequenciaLeds
  vetSequenciaLeds[rodada] = aleatorio;
  
  //chama a função Sequencia_leds
  Sequencia_leds();
  
  //chama a função Vez_do_jogador
  Vez_do_Jogador();
    
  rodada++;
 
 //delay de 1.5 segundos para que a próxima rodada comece.
  delay(1500);
}
/*
=================================================================================================================================================
      FUNÇÕES
================================================================================================================================================= 
*/

/*A função Sequencia_leds é reponsável por acender os LEDS conforme os números aleatórios são gerados e armazenados no vetor vetSequenciaLeds[rodada].
 * Caso o número aleatório seja 0, o LED azul se acende por 0.5 segundos e apaga. 
 * Temos um delay de 0.5 segundos para que o próximo LED acenda.
 * Caso o número aleatório seja 1, o LED amarelo acende. Caso seja 2, o LED verde acende e, por fim, caso seja 3, acende o LED vermelho.
 */
void Sequencia_leds()
{
    for(int j=0;j<=rodada;j++)
    {      
      if(vetSequenciaLeds[j] == 0)        { piscaLedAzul(500);      }
      else if(vetSequenciaLeds[j] == 1)   { piscaLedAmarelo(500);   }
      else if(vetSequenciaLeds[j] == 2)   { piscaLedVerde(500);     }
      else                                { piscaLedVermelho(500);  }
    }
}

/*
 * A função Vez_do_Jogador inicia com uma booleana jogada = false para que o programa entre obrigatoriamente no while e só saia caso jogada retorne true, do contrário, continuará dentro do while até mudar essa condição.
 * Dentro do while temos a leitura dos botões e, caso um botão seja pressionado, o LED correspondente acende e o valor desse LED (0~3) é armazenado no vetor vetSequenciaJogadas.
 * Depois de pressionado, a booleana passa a ter valor true e o while termina.
 * A próxima etapa consiste em verificar se o LED que foi aceso na função Sequencia_leds corresponde ao led que foi aceso na função Vez_do_Jogador.
*/

void Vez_do_Jogador()
{
  for(int k=0;k<=rodada;k++)
  {
    bool jogada = false;
    
    while(jogada != true)
    {          
      estadoBotaoAzul = digitalRead(btnAzul);
      estadoBotaoAmarelo = digitalRead(btnAmarelo);
      estadoBotaoVerde = digitalRead(btnVerde);
      estadoBotaoVermelho = digitalRead(btnVermelho);

      if(estadoBotaoAzul == LOW)
      {
        piscaLedAzul(400);
        vetSequenciaJogadas[k] = 0;
        jogada = true;
      }

      if(estadoBotaoAmarelo == LOW)
      {
        piscaLedAmarelo(400);
        vetSequenciaJogadas[k] = 1;
        jogada = true;
      }
      
      if(estadoBotaoVerde == LOW)
      {
        piscaLedVerde(400);
        vetSequenciaJogadas[k] = 2;
        jogada = true;
      }
      
      if(estadoBotaoVermelho == LOW)
      {
        piscaLedVermelho(400);
        vetSequenciaJogadas[k] = 3;
        jogada = true;
      }  
    } //final while 
    
    /* Caso o valor do botão apertado seja diferente do LED reproduzido na sequência, todos os LEDS acendem e apagam 3 vezes sendo o de última de longa duração. 
     * Assim, o jogo termina e é necessário sair do for e zerar a rodada. 
     * Como estamos "zerando" a variável rodada na função vez_do_jogador e, logo após seu término temos um rodada++, foi necessário definir
     * rodada = - 1 para que o jogo reiniciasse na rodada 0 e não na rodada 1, caso aconteceria se definíssemos rodada como sendo 0 (rodada=0).
     */
    if(vetSequenciaJogadas[k]!= vetSequenciaLeds[k])
    {
      piscaTodosLeds(200);
      piscaTodosLeds(200);
      piscaTodosLeds(1000);
      rodada = -1;
      break;
    }
  } //final for    
} //final função Vez_do_Jogador

/*
 * A função piscaLedAzul é responsável por acender o LED azul e, após um tempo que será passado como parâmetro, o LED se apaga
 * @param tempoDelay usado para definir o tempo de delay do LED para acender e apagar
*/
void piscaLedAzul(int tempoDelay)
{
  digitalWrite(azul,HIGH);
  delay(tempoDelay);
  digitalWrite(azul,LOW);
  delay(tempoDelay);
}

/*
 * A função piscaLedAmarelo é responsável por acender o LED amarelo e, após um tempo que será passado como parâmetro, o LED se apaga
 * @param tempoDelay usado para definir o tempo de delay do LED para acender e apagar
*/
void piscaLedAmarelo(int tempoDelay)
{
  digitalWrite(amarelo,HIGH);
  delay(tempoDelay);
  digitalWrite(amarelo,LOW);
  delay(tempoDelay);
}

/*
 * A função piscaLedVervemlho é responsável por acender o LED vermelho e, após um tempo que será passado como parâmetro, o LED se apaga
 * @param tempoDelay usado para definir o tempo de delay do LED para acender e apagar
*/
void piscaLedVermelho(int tempoDelay)
{
  digitalWrite(vermelho,HIGH);
  delay(tempoDelay);
  digitalWrite(vermelho,LOW);
  delay(tempoDelay);
}

/*
 * A função piscaLedVerde é responsável por acender o LED verde e, após um tempo que será passado como parâmetro, o LED se apaga
 * @param tempoDelay usado para definir o tempo de delay do LED para acender e apagar
*/
void piscaLedVerde(int tempoDelay)
{
  digitalWrite(verde,HIGH);
  delay(tempoDelay);
  digitalWrite(verde,LOW);
  delay(tempoDelay);
}

/*
 * A função piscaTodosLeds é responsável por acender todos os LEDS e, após um tempo que será passado como parâmetro, todos os LEDs se apagam
 * @param tempoDelay usado para definir o tempo de delay do LED para acender e apagar
*/
void piscaTodosLeds(int tempoDelay)
{
  digitalWrite(azul,HIGH);
  digitalWrite(amarelo,HIGH);
  digitalWrite(verde,HIGH);
  digitalWrite(vermelho,HIGH);
  delay(tempoDelay);
  digitalWrite(azul,LOW);
  digitalWrite(amarelo,LOW);
  digitalWrite(verde,LOW);
  digitalWrite(vermelho,LOW);
  delay(tempoDelay);
}
 
       
/* ~~~~~~ IMPLEMENTAÇÕES FUTURAS ~~~~~~~~~~~~
 * Display LCD para marcar a rodada e o recorde;
 * Acrescentar um buzzer;
 * Níveis de dificuldade igual no brinquedo original;
 * Aumentar/diminuir a velocidade da reprodução da sequência dos LEDs
*/      
      
      
