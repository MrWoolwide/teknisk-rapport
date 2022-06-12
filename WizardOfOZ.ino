//på grunn av simplisiteten skrives ikke mange komentarer. koden tar inn 0 state fra knapp en, 2 state fra knapp to og en tre state fra knapp en og to sammen.
//dette ble gjort ved at to knapper er enklere å skjule en tre
int gron = 0;
int blaa = 0;
int test=0;
void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  gron = digitalRead(2); 
  blaa = digitalRead(4);
  
  if(gron == HIGH)
  {
    test = 1;
    Serial.print(test);
    delay(500);
  } 
  if (blaa == HIGH){
    test = 2;
    Serial.print(test);
    digitalWrite(12, HIGH);
    delay(500);

  }
  if (blaa == HIGH && gron == HIGH){
    test = 3;
    Serial.print(test);
    digitalWrite(13, HIGH);
    delay(500);

  }
  if (test == 1){
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    noTone(10);

  }
  if (test == 2){
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    tone(10,300);

  }
  if (test == 3){
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    tone(10,800);

  }
  
  delay(15);
}
