#include <SoftwareSerial.h>     //tillater bruk av tx/rx utenom pin 0 og 1 samt litt mer brukervennlighet
#include <OneWire.h>            //lar temperaturmåleren kunne bli lest (DS18B20) 
#include <DallasTemperature.h>  //tillater å regne om verdien gitt av termometeret til celsius eller farenheit


#define tx 11 //setter tx til 11
#define rx 10 //setter rx til 10 || viktig at tx er oddetall og rx partall
SoftwareSerial bt(rx,tx); //åpner en serial bt over koblingen og bruker rx og tx pinene

int maxTemp= 31;  //setter en maksimum og minimum temperatur  (disse er brukt til å teste og hadde vært mye større i reelt bruk
int minTemp= -10;

#define ONE_WIRE_BUS 3  //velger data intake for termometeret
OneWire oneWire(ONE_WIRE_BUS);  //gjør så d3 kan utnytte seg av termometeret
DallasTemperature sensors(&oneWire);  //tillater regining av dataen gitt

String husk;  //variabler som er brukt for å ikke sende for mye unyttig informasjon over
String husk2 = "placeholder";

void setup() 
{
  sensors.begin();      //starter termometeret
  Serial.begin(38400);  //starter en serial 
  bt.begin(38400);      //starter bt serial || ikke nødvendig at serial og bt er 38400, men bt må siden det er baud raten på hc-05/06, se reciver koden for mer info
  pinMode(tx, OUTPUT);  //setter tx til output
  pinMode(rx, INPUT);   //setter rx til input
}
void loop() {
  sensors.requestTemperatures();  //starter termometer funksjonen
  float tempC = sensors.getTempCByIndex(0); //setter tempC til å være tilsvarende den første instrumentet (termometer). dette går på array system så 0 er tilsvarende 1 osv
  Serial.println(tempC);  //printer temperaturen, bare for testing og demonstrasjon under fremvisning

  if (tempC >= maxTemp){  //kjører husk_1
      husk_1(); 
      }
  if (tempC < maxTemp && tempC > minTemp){  //kjører husk_0
      husk_0();
      }
  if (tempC <= minTemp){  //kjører husk_2
      husk_2();
      }
      
  if ( husk != husk2){  //kjører sende
      sende();
      }
  delay(250);
}

void husk_1(){  //alle husk_ endrer verdien til husk og printer ut " husk= " og verdien til husk
  husk = "1";
  Serial.println(" husk= "+husk);
}

  void husk_0(){
    husk = "0";
    Serial.println(" husk= "+husk);
    }
  void husk_2(){
    husk = "2";
    Serial.print(" husk= "+husk);
    }
  void sende(){ //sende gjør at husk2 er lik husk, printer husk verdien i serial monitor og bruker write av husk som en c string. 
    husk2=husk;
    Serial.println(" husk= "+ husk);
    bt.write( husk.c_str() ); //grunnen for write istedet for print er at write sender en byte som fører til mindre problemer samt at
    }                         //softwareserial.h tillater at det ikke må regnes om fra ascii o.l som gjør at når 1 blir sendt, dukker det opp som 1 og ikke 48
                              //som er det tilsvarende ascii verdien.
