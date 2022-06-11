#include <SoftwareSerial.h> //tillater bruk av rx/tx utenom med digtital pin 1 og 0, pluss litt mer brukervennlighet
#define tx 11 //setter tx til 11
#define rx 10 //setter rx til 10
              //viktig at tx er odde og rx er partall
#define BT_PWR 12 //setter strømmen til bluetooth til digital pin 12, dette skyldes testing samt det som forhåpentligvis var en workaround problemer med transceviern 

SoftwareSerial bt(rx, tx); //setter den eksterne seriellen bt til tx og rx pins

String c="placeholder"; //bare visuallisering av verdier brukt senere
int GRON = 4;
int ROOD=3;
int BLAA=5;
int LYD=6;
int x= 1;

void setup()
{
  
  Serial.begin(38400); //setter en serial til det baud rate som med bluetooth, ikke nødvendig men fint for testing
  bt.begin(38400);  //setter bt sin baud rate til 38400, som er det hc-06/06 bruker. dette finner man ved å bruke AT+UART? komandoen når hc-05 er i command mode. for nyere modeller er dette nesten alltid settet til 9600
  pinMode(tx, OUTPUT);  //setter tx til output
  pinMode(rx, INPUT);   //setter rx til input
  
  pinMode(GRON, OUTPUT);  //setter varsel til output
  pinMode(ROOD, OUTPUT);
  pinMode(BLAA, OUTPUT);
  pinMode(LYD, OUTPUT);
  pinMode(7, INPUT);      // denne er til knappen som setter den i "hvile modus"
  
  pinMode( BT_PWR, OUTPUT );  // setter at strømmen til bt vil være output
  
  digitalWrite(GRON,LOW); //setter varsel til å være inate low
  digitalWrite(ROOD,LOW);
  digitalWrite(BLAA,LOW);
  digitalWrite(LYD,LOW); 

  
}
void loop()
{
   Serial.println( "checking BT..." );  //dette er for visualisering/testing om tranciveren er i orden
  digitalWrite( BT_PWR, HIGH ); //skrur på bluetooth
  
  if( bt.available() > 0 )  //sjekker om bt er tilgjengelig
  {
  if( !bt.isListening() )   //sjekker om bluetooth tar inn signaler
  {
     Serial.println( "\nListening..." );
     bt.listen(); // dersom den ikke alt var det setter den inn i listening mode
  }
  if(bt.available()>0)//går videre med koden                                                                              ****
  {
    c=bt.read();  //setter c til å være lik hva bt sender
    Serial.print(c); //for testing printer den c samt en dobbel konfirmasjon med den under

    Serial.print(" c er: "+ c);
    
      
  }
    if (digitalRead(7)==HIGH){ //dersom knappen blir trykket på kjør pause()
       pause();
      }
    if (c=="0"){  //hvis c er 0 kjør gron
      gron();
      }
    if (c=="1"){  //hvis c er 1 kjør rood
      rood();
      }
    if (c=="2"){  //hvis c er 2 kjør blaa
      blaa();
      }
     else {       //ellers kjør feil
      feil();
      }  
  }                                                                                                                       ****
  //NOTE: mellom stjernene er koden, det som er over og under (i void loop) er ment som forsikring/testing. hele BT_PWR kan bli byttet ut med 5v pinnen på arduino
   digitalWrite( BT_PWR, LOW );  //skrur av strømmen til bt
  Serial.println( "resting..." );
  delay( 500 ); //liten delay før den prøver å kjøre loop igjen
}




void gron(){                    //setter på grønt lys og ingen lyd
      digitalWrite(GRON, HIGH);
      digitalWrite(ROOD, LOW);
      digitalWrite(BLAA, LOW);
      noTone(6);
  }
void rood(){                    //detter på rødt lys og lyd
      digitalWrite(GRON, LOW);
      digitalWrite(ROOD, HIGH);
      digitalWrite(BLAA, LOW);
      tone(6,800);
  }
void blaa(){                    //setter på blått lys og lyd
      digitalWrite(GRON, LOW);
      digitalWrite(ROOD, LOW);
      digitalWrite(BLAA, HIGH);
      tone(6,300);
  }
void feil(){                    //setter på all lys og ingen lyd
       digitalWrite(GRON, HIGH);
      digitalWrite(ROOD, HIGH);
      digitalWrite(BLAA, HIGH);
      noTone(6);
  }
void pause(){                   //setter på grønt lys og ingen lyd i 10 minutter
    digitalWrite(GRON, HIGH);
    digitalWrite(ROOD, LOW);
    digitalWrite(BLAA, LOW);
    noTone(6);
    delay(100000);
  }
