// definiçao dos pinos de controle dos motores na ponte H
#define IN1A 13 // esq azul(jmp)
#define IN1B 12 // esq preto
#define IN2A 6  // dir laranja
#define IN2B 7  // dir verde

// definição dos pinos dos sensores
#define sensorDireita 2
#define sensorEsquerda 3
#define sensorMeio 4

// definiçao de constantes utilizadas nas estruturas de decisão
bool BRANCO = 0;
bool PRETO = 1;

// declaração de variáveis boleanas que controlam a coleta de dados dos sensores infravermelho
bool LeituraSensorDireita = 0;
bool LeituraSensorEsquerda = 0;
bool LeituraSensorCentral = 0;

// declaração dos pinos do ultrasonico
#define trig 9
#define echo 10

// declaração de variável da distancia coletada pelo ultrasonico
float distancia;

// declaração de variáveis de controle
int contpreto = 0;
int contbranco = 0;
int desafio = 1;

void setup()
{
    // moto 1
    pinMode(IN1A, OUTPUT);
    pinMode(IN1B, OUTPUT);

    // moto 2
    pinMode(IN2A, OUTPUT);
    pinMode(IN2B, OUTPUT);

    Serial.begin(9600);

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    Serial.begin(9600);

    // Pinos declarados como entrada dos sensores infravermelhos
    pinMode(sensorDireita, INPUT);
    pinMode(sensorEsquerda, INPUT);
    pinMode(sensorMeio, INPUT);
}

void loop()
{
    // 0 é branco
    // 1 é preto

    digitalWrite(trig, LOW);
    delay(0005);
    digitalWrite(trig, HIGH);
    delay(0010);
    digitalWrite(trig, LOW);

    distancia = pulseIn(echo, HIGH);
    distancia = distancia / 58;
    Serial.println(distancia);
    delay(100);

    LeituraSensorDireita = digitalRead(sensorDireita);
    LeituraSensorEsquerda = digitalRead(sensorEsquerda);
    LeituraSensorCentral = digitalRead(sensorMeio);

    if (desafio == 1)
    {
        giroCompleto();
        delay(200);
        giroCompleto();
        delay(100);
        correcaoEsquerda();
        delay(30);
        miniSamba();
        desafio = 0;
    }

    // Seguir a linha principal
    if ((LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO) && (LeituraSensorDireita == BRANCO))
    {
        frente(80);
        para(0);
        leituraSensor();
        contbranco = 0;
    }
    // Corrigir para esquerda
    if ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == BRANCO))
    {
        correcaoEsquerda();
        contbranco = 0;
    }
    // Corrigir para direita
    if ((LeituraSensorEsquerda == PRETO) && (LeituraSensorCentral == BRANCO))
    {
        correcaoDireita();
        contbranco = 0;
    }
    // Curva de 90° para direita
    if ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO))
    { // verificar se é curva ou intersecção
        para(500);
        frente(140);
        leituraSensor();
        if ((LeituraSensorEsquerda == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorDireita == BRANCO))
        { // Verificar se deve seguir reto
            frente(85);
        }
        else if (((LeituraSensorEsquerda == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorDireita == PRETO)) ||
                 ((LeituraSensorEsquerda == BRANCO) && (LeituraSensorCentral == BRANCO) && (LeituraSensorDireita == BRANCO)))
        { // Possibilidades para ocorrer curva
            curvaDireita();
            delay(300);
        }
        else if ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO))
        { // confirmação para seguir reto
            para(1000);
            frente(100);
            leituraSensor();
        }
        if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO))
        { // verificar se existe outra curva
            frente(150);
        }
        else if ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO))
        { // verificar se existe outra curva
            curvaDireita();
            delay(300);
        }
        else
        { // confirmação para seguir reto
            frente(130);
        }
    }
    // Curva de 90° para esquerda
    if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == PRETO))
    { // verificar se é curva ou intersecção
        para(500);
        frente(150);
        leituraSensor();
        if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO))
        { // confirmação da curva
            frente(85);
        }
        else if (((LeituraSensorEsquerda == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorDireita == PRETO)) ||
                 ((LeituraSensorEsquerda == BRANCO) && (LeituraSensorCentral == BRANCO) && (LeituraSensorDireita == BRANCO)))
        { // Possibilidades para ocorrer curva
            curvaEsquerda();
        }
        else if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == PRETO))
        { // verificar se existe outra curva
            para(1000);
            frente(125);
            leituraSensor();
        }
        if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO))
        { // se não tiver, seguir reto
            frente(150);
        }
        else if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == PRETO))
        { // se tiver outra, fazer curva
            curvaEsquerda();
            delay(100);
        }
        else
        { // confirmação para seguir reto
            frente(150);
        }
    }
    // Verificação do Cruzamento
    if ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == PRETO))
    {
        // Teste para identificar retorno
        para(1000);
        frente(150);
        leituraSensor();
        para(1000);
        if ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == PRETO))
        { // Confirmação do retorno
            giroCompleto();
            para(200);
        }
        else if (((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == BRANCO)) ||
                 ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == BRANCO) && (LeituraSensorEsquerda == BRANCO)) ||
                 ((LeituraSensorDireita == PRETO) && (LeituraSensorCentral == BRANCO) && (LeituraSensorEsquerda == BRANCO)) ||
                 ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == BRANCO) && (LeituraSensorEsquerda == PRETO)))
        {
            frente(170);
        }
    }
    // Situação de todos os sensores brancos
    if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == BRANCO) && (LeituraSensorEsquerda == BRANCO))
    {
        // Correção caso se perca no percurso
        if (contbranco < 16)
        { // Quando o contador chegar no 16 e não encontrar a linha, o carro volta para trás
            para(0);
            frente(90);
            leituraSensor();
            contbranco++; // Cada loop adiciona  + PRETO ao contador do branco
        }
        // Correção para trás
        else
        {
            correcaoTras();
        }
        if ((LeituraSensorDireita == BRANCO) && (LeituraSensorCentral == PRETO) && (LeituraSensorEsquerda == PRETO))
        {
            para(100);
            frente(90);
            rodaEsquerdaTras();
            rodaDireitaFrente();
            delay(450);
            para(450);
            leituraSensor();
            delay(20);
            contpreto = 0;
        }
        else
        {
            para(0);
        }
    }
}

// Espaço destinado para as funções do robô
void frente(int d)
{
    rodaEsquerdaFrente();
    rodaDireitaFrente();
    delay(d);
}

void desvio()
{
    para(500);
    rodaDireitaTras();
    rodaEsquerdaFrente();
    delay(400);
    para(500);
    frente(500);
    rodaDireitaFrente();
    rodaEsquerdaTras();
    delay(400);
    frente(500);
    rodaDireitaFrente();
    rodaEsquerdaTras();
    delay(400);
    frente(500);
}

void para(int D)
{
    digitalWrite(IN1B, LOW);
    digitalWrite(IN1A, LOW);
    digitalWrite(IN2A, LOW);
    digitalWrite(IN2B, LOW);
    delay(D);
}

void tras()
{
    digitalWrite(IN1A, HIGH);
    digitalWrite(IN2A, LOW);
    digitalWrite(IN2A, HIGH);
    digitalWrite(IN2B, LOW);
}

void rodaEsquerdaFrente()
{
    analogWrite(IN1B, 160);
    analogWrite(IN1A, 0);
}

void rodaEsquerdaTras()
{
    analogWrite(IN1B, 0);
    analogWrite(IN1A, 160);
}

void rodaDireitaFrente()
{
    analogWrite(IN2A, 0);
    analogWrite(IN2B, 170);
}

void rodaDireitaTras()
{
    analogWrite(IN2A, 170);
    analogWrite(IN2B, 0);
}

void sensorUltrassonico()
{
}

void leituraSensor()
{
    digitalRead(LeituraSensorDireita);
    digitalRead(LeituraSensorEsquerda);
    digitalRead(LeituraSensorCentral);
}

void correcaoEsquerda()
{
    rodaEsquerdaFrente();
    delay(180);
    para(0);
    leituraSensor();
    delay(150);
}

void correcaoDireita()
{
    rodaDireitaFrente();
    delay(210);
    para(0);
    leituraSensor();
}

void curvaEsquerda()
{
    para(100);
    frente(90);
    rodaEsquerdaTras();
    rodaDireitaFrente();
    delay(410);
    para(410);
    leituraSensor();
    delay(20);
    contpreto = 0;
    contbranco = 0;
}

void curvaDireita()
{
    para(100);
    frente(90);
    rodaEsquerdaFrente();
    rodaDireitaTras();
    delay(610);
    para(430);
    leituraSensor();
    delay(20);
    contpreto = 0;
    contbranco = 0;
}

void correcaoTras()
{
    leituraSensor();
    tras();
    delay(490);
    para(30);
    leituraSensor();
    contbranco = 0;
}

void giroCompleto()
{
    rodaDireitaFrente();
    rodaEsquerdaTras();
    delay(943);
}

void miniSamba()
{
    rodaEsquerdaFrente();
    rodaDireitaTras();
    delay(100);
    rodaEsquerdaTras();
    rodaDireitaFrente();
    delay(100);
    rodaEsquerdaFrente();
    rodaDireitaTras();
    delay(100);
    rodaEsquerdaTras();
    rodaDireitaFrente();
    delay(100);
    para(200);
}
