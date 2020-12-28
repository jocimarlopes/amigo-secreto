#include <Wire.h> //Inclusão de Biblioteca
#include <LiquidCrystal_I2C.h> //Inclusão de Biblioteca
 
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //Endereço do I2C e demais informações

const int pinoBotao = 7; //pino digital ativado pelo PushButton

// variáveis
int estado = 0; // variável para leitura do pushbutton
int guarda_estado = LOW; // variável para armazenar valores do pushbutton
String escolhido = "      ????      ";
int numEscolhido = 0;

// array de nomes sorteados - MÁXIMO 16 CARACTERES POR ELEMENTO
char *pessoas[] = {"    JOCIMAR     ", "    MAIKELEN    ", "    BARBARA     ","     PAULO      ", "     BIANCA     ","      JANE      ", "     PAMELA     ", "    JULIANO     "};

// funções
void setup(){
 lcd.begin (16,2); // quantidade de colunas (16) e o número de linhas (2) do display
 lcd.setBacklight(HIGH); // liga a luz de fundo (backlight)
 pinMode(pinoBotao, INPUT_PULLUP); //define o pino como entrada | "_PULLUP" é para ativar o resistor interno do arduino para garantir que não exista flutuação entre 0 (LOW) e 1 (HIGH)
}

void loop(){
  pressButton();// chamando função pressButton() que diz se HIGH ou LOW
  sorteio();// chamando função sorteio()
}

void sorteio () { //função que sorteia o amigo secreto
  
  if (guarda_estado == LOW) {
         
  }
  if (guarda_estado == LOW) { //começa a selecionar o sorteado do amigo secreto

      delay(900); //esperera o tempo de 500ms para evitar que haja várias vezes alterações
      
      lcd.setCursor(0,0);//seta a posição do cursor (início do texto)
      lcd.print("-AMIGO SECRETO- ");// imprime o texto na tela
      
      lcd.setCursor(0,1); //seta a posição do cursor (início do texto)
      lcd.print("    ESCOLHER    "); //imprime o texto no display
  }
  else {
      seleciona();// chamando a função seleciona() antes de mostrar o amigo secreto na tela
      
      lcd.setCursor(0,0); //seta a posição do cursor (início do texto)
      lcd.print("  FELIZ NATAL   "); //imprime o texto no display
      
      lcd.setCursor(0,1); //seta a posição do cursor (início do texto)
      lcd.print(pessoas[numEscolhido]); //imprime o texto no display
      
      if (pessoas[numEscolhido] == "  JA ESCOLHIDO  ") {
        pressButton();
        exit;
      }
      if (pessoas[numEscolhido] != "  JA ESCOLHIDO  " && digitalRead(pinoBotao) == HIGH) {
        pessoas[numEscolhido] = "  JA ESCOLHIDO  ";
        remove(pessoas[numEscolhido]);
        pressButton();
        while (digitalRead(pinoBotao) == HIGH) {
          lcd.setCursor(0,1); //seta a posição do cursor (início do texto)
          lcd.print("   AGUARDE...   "); //imprime o texto no display 
        }
      }
  }
}

void seleciona () {
  // seleciona o escolhido para o amigo secreto
  numEscolhido = random(0, 7);
}

void pressButton() {
  // le o estado pushbutton: ligado (HIGH) ou desligado (LOW)
  estado = digitalRead(pinoBotao);
  
  // verifica se o botão (pushbutton) está pressionado
  if (estado == HIGH) {
    guarda_estado = !guarda_estado; // inverte valor da variável variable_buttonEstado
    delay(500); //esperera o tempo de 500ms para evitar que haja várias vezes alterações
  }
}
