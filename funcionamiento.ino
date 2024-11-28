// Inicializacion de variables
// Buzzer
#define Sonido 7
// BOTONES
#define B1 13
#define B2 12
#define B3 11
#define B4 10
// LEDS
#define L1 2
#define L2 3
#define L3 4
#define L4 5
// Fur_Elisa Melodias para el buzzer
int Fur_Elisa [] ={24.50, 23.125, 41.2, 23.125, 24.50, 23.125, 41.2, 23.125, 24.50, 23.125, 41.2, 36.71, 38.89, 30.87 };
int Duracion[] = {4,4,4,4,4,4,4,4,4,4,4,4,4,4};

int NivelA = 1; //Nivel actual (es decir que es la primera luz)
int Vel = 500; //Tiempo entre luces
const int NivelM = 3; // Nivel máximo (máximo de luces mostradas)
int Sec[NivelM]; //Secuencia generada aleatoriamente
int SecU[NivelM]; //Secuencia ingresada por el jugador

void setup() {
 pinMode(B1, INPUT);
 pinMode(B2, INPUT);
 pinMode(B3, INPUT);
 pinMode(B4, INPUT);
 pinMode(L1, OUTPUT);
 pinMode(L2, OUTPUT);
 pinMode(L3, OUTPUT);
 pinMode(L4, OUTPUT);
 digitalWrite(L1, LOW);
 digitalWrite(L2, LOW);
 digitalWrite(L3, LOW);
 digitalWrite(L4, LOW);
}

void loop() {
  if(NivelA == 1){
    GeneraSec(); //en el nivel 1 ya se genera la secuencia completa
    MuestraSec();
    LeeSec();
   }
   if (NivelA != 1){
    MuestraSec();
    LeeSec();
   }

}

//Genera la secuencia aleatoria
void GeneraSec(){
    randomSeed(millis());
    for(int S = 0; S < NivelM; S++){//secuencia de 5 porque NivelM es 5
      Sec[S] = random(2,6); //pines de las luces
      }
    }

//Muestra la secuencia al jugdor en base a la secuencia generada
void MuestraSec(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  for(int S = 0; S < NivelA; S++){
    //cada botón tiene una frecuencia distinta
      if(Sec[S] == L1){
      tone(Sonido, 200);
      delay(200);
      noTone(Sonido);
      }
      if(Sec[S] == L2){
      tone(Sonido, 300);
      delay(200);
      noTone(Sonido);
      }
      if(Sec[S] == L3){
      tone(Sonido, 400);
      delay(200);
      noTone(Sonido);
      }
      if(Sec[S] == L4){
      tone(Sonido, 500);
      delay(200);
      noTone(Sonido);
      }
      digitalWrite(Sec[S], HIGH);
      delay(Vel);
      digitalWrite(Sec[S], LOW);
      delay(200);
   }
  }

//Lee la secuencia ingresada por el jugador
 void LeeSec(){
    int Fg = 0;
    for(int S = 0; S < NivelA; S++){ //Recorre la secuencia de leds
      Fg = 0; //el jugador aún no presiona un botóny se reinicia en cada iteración
      while(Fg == 0){ //esperando la respuesta del jugador
        if(digitalRead(B4) == LOW){ 
          digitalWrite(L4, HIGH);
          tone(Sonido, 500);
          delay(300);
          noTone(Sonido);
          SecU[S] = L4;
          Fg = 1;
          delay(200);
          if(SecU[S] != Sec[S]){
            SecE();
            return;
            }
            digitalWrite(L4, LOW);
        }
        if(digitalRead(B3) == LOW){
          digitalWrite(L3, HIGH);
          tone(Sonido, 400);
          delay(300);
          noTone(Sonido);
          SecU[S] = L3;
          Fg = 1;
          delay(200);
          if(SecU[S] != Sec[S]){
            SecE();
            return;
            }
            digitalWrite(L3, LOW);
        }
        if(digitalRead(B2) == LOW){
          digitalWrite(L2, HIGH);
          tone(Sonido, 300);
          delay(300);
          noTone(Sonido);
          SecU[S] = L2;
          Fg = 1;
          delay(200);
          if(SecU[S] != Sec[S]){
            SecE();
            return;
            }
            digitalWrite(L2, LOW);
        }
        if(digitalRead(B1) == LOW){
          digitalWrite(L1, HIGH);
          tone(Sonido, 200);
          delay(300);
          noTone(Sonido);
          SecU[S] = L1;
          Fg = 1;
          delay(200);
          if(SecU[S] != Sec[S]){
            SecE();
            return;
            }
            digitalWrite(L1, LOW);
        }
      }
    }
    SecC();
  }

//Sonido de equivocarse
  void Fur_ElisaE(){
    for(int S = 0; S < 8; S++){
      int DuracionF = 1000/Duracion[S];
      tone(Sonido,Fur_Elisa[S], DuracionF);
      int PauseN = DuracionF * 1.30;
      delay(PauseN);
      noTone(Sonido);
      }
   }

//Secuencia errónea, empieza de nuevo con una nueva secuencia
  void SecE(){
   digitalWrite(L1, HIGH);
   digitalWrite(L2, HIGH);
   digitalWrite(L3, HIGH);
   digitalWrite(L4, HIGH);
   delay(250);
   digitalWrite(L1, LOW);
   digitalWrite(L2, LOW);
   digitalWrite(L3, LOW);
   digitalWrite(L4, LOW);
   delay(250);
   Fur_ElisaE();
   NivelA = 1;
    }

//Secuencia Completa
 void SecC(){
	if (NivelA < NivelM) {
  	 NivelA++; //Aumenta un led más hasta llegar al máximo
    }
    delay(200);
 }
