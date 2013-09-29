/*Moreno Garza Oscar, "the moogerfucker" */
/* oscarmg99@gmail.com */
/* referencias: 
http://en.wikipedia.org/wiki/Scientific_pitch_notation 
http://arduino.cc/en/Tutorial/Tone
*/

int sensorNota = A0;
int sensorOctava = A1;
int sensorPitch = A2;
int sensorDelay = A3;

int bocinaOut = 8;

int notas[] = { 0, 16, 18, 20, 22, 25, 28, 31, 0};
          // nada, DO, RE, MI, FA, SOL, LA, SI, nada
          // son los valores de frecuencias para la octava 0.
              
void setup ( ) {
 // se ocupa :( 
 pinMode(bocinaOut, OUTPUT);
}


void loop() {
  int valorNota = map(analogRead(sensorNota), 0, 1024, 100, 800);
  // de 1 a 8 (con valores de 10^3), basados en el potenciometro de A0.
  // este caso va de silencio,do,re,mi,fa,sol,la,si,silencio  
  
  int numNota = valorNota/100; // magia
  //se toman rangos de 10^3 para tener una zona muerta de ~100~ en el softpot en lugar de ~1~
  //10% de margen de error en lugar de 1%
  
  int valorDelay = map(analogRead(sensorDelay), 0, 1024, 0, 250);
  //agarramos retraso de 0ms hasta 250ms

  int valorOctava = map(analogRead(sensorOctava), 0, 1024, 2, 7); 
  // agarramos valores de un segundo potenciometro para establecer la octava.
  // de 2 a 7 por que es lo que aguanta la bocina de rango :(   
  valorOctava = pow(2, valorOctava); // 2^octava.

  int tono = notas[numNota]*valorOctava ; // tono = valor_base_de_frec*(2^numero_de_octava)
  
  int rango = tono/4; 
  //un cuarto de tono, asi no sobrelapamos los tonos. 
  //los extremos serian un semi-tono abajo y medio semi-tono arriba.
  
  int pitchMod = map(analogRead(sensorPitch), 0, 1024, -rango, rango*2); 
  //tenemos la mitad de nuestro tono para rango hacia abajo para llegar a un semi-tono en el minimo.
  //para arriba tenemos el doble para llegar a un semi-tono arriba.

  

/*RUTINA PRINCIPAL: */
   if (valorNota < 800 && valorNota > 100 ) {
  // si esta en rango valido, de 1 a 7:
      if ( valorDelay <= 5 ) { 
            tone(bocinaOut, tono + pitchMod);
            // si es 0 no cortamos.
            //0.5% de margen de error
      } else {
            tone (bocinaOut, tono + pitchMod);
            delay(valorDelay);
            //mandamos sonido en tiempo basado en sensorDelay
            noTone(bocinaOut);
            //no mandamos sonido en el mismo tiemp.
            delay(valorDelay);
      }
            // silencio.
  } else {        
      //si no esta en rango valido:
      noTone(bocinaOut); // no mandamos nada.
  }
    
     delay(1); // por estabilidad esperamos 1 milisegundo.
}
