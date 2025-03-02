#include <Keypad.h>
#include <LiquidCrystal.h>
#include <string.h>
#include <Servo.h>
#define SERVO 12


LiquidCrystal meu_display(7, 6, 5, 4, 3, 2);

Servo myServo;

//Deifinicao da quantidade de linhas e colunas
const byte LINHAS = 4;
const byte COLUNAS = 4;

//Definicao dos pinos das linhas
byte PinosLinhas[LINHAS] = {A1, A2, A3, A4};

//A0, A1, A2, A3, A4 e A5 são constantes pré-definidas
// No Arduino uno, elas valem 14(A0), 15, 16, 17, 18 e 19(A5)
//Deinicao dos pinos das colunas
byte PinosColunas[COLUNAS] = {8,9,10,11};
//Matriz de caracteres 
char matriz_teclas[LINHAS][COLUNAS] = 
{
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','d'}
};
//Inicializa o teclado
Keypad meu_teclado = Keypad( makeKeymap(matriz_teclas), PinosLinhas,
                             PinosColunas,LINHAS, COLUNAS);
int ColunaLCD = 6;
int LinhaLCD = 2;
int j = 0;
int i = 0;
int ver = 0;
char senha_registro[5];

void setup()
{
 Serial.begin(9600);
 meu_display.begin(16,2);
 meu_display.setCursor(0,0);
 meu_display.print("    TRANCADO"); 
 meu_display.setCursor(0,2);
 meu_display.print("senha:"); 
 myServo.attach(SERVO);
}

void loop()
{  
  char tecla = meu_teclado.getKey();
  if(tecla != NO_KEY)
  {  
     
    
     if(i<4 && j==0)
     {
	  meu_display.setCursor(ColunaLCD++,LinhaLCD);
   	  meu_display.print('*'); 
      senha_registro[i++] = tecla;
     }
     if(ColunaLCD==10)
     {
      delay(1000);
      ColunaLCD = 0; 
      meu_display.clear();
      delay(1000);
      meu_display.setCursor(0,0);
   	  meu_display.print("Confirme: "); 
     }
   
      
      else if(tecla == senha_registro[j] && i==4)
      {
       meu_display.setCursor(0,0);
   	   meu_display.print("Confirme: "); 
       meu_display.setCursor(ColunaLCD++,LinhaLCD);
       meu_display.print('*'); 
       ver += 1;   
       j++;
        
      }
      else if(tecla != senha_registro[j] && i==4 && tecla!='A')
       {
         meu_display.clear();
         meu_display.setCursor(0,0);
   	     meu_display.print("Senha errada");
         delay(2000); 
         meu_display.clear();
         meu_display.setCursor(0,0);
         meu_display.print("Confirme: ");
   
      }
      if(ver==4 && tecla != 'A')
        {
         meu_display.clear();
         meu_display.setCursor(0,0);
   	     meu_display.print("  DESTRANCADO");
         myServo.write(0);
         delay(5000); 
         meu_display.clear();
         meu_display.setCursor(0,0);
   	     meu_display.print("Aperte A");
         meu_display.setCursor(0,2); 
         meu_display.print("p/ trancar");
        }
        if(tecla == 'A')
       {
         	j = 0;
         	ver = 0;  
         	Serial.println(ver);
         	Serial.println(j);
         	delay(2000);
         	meu_display.clear();
            meu_display.setCursor(0,0);
   	     	meu_display.print(" TRANCANDO");
            delay(2000);
            myServo.write(90);
            meu_display.clear();
         	meu_display.setCursor(0,0);
   	     	meu_display.print("Confirme:");  
         	ColunaLCD = 0;
         }
     
   }
  } 

  