/* Kosz na smieci rozpoznajacy material, z ktorego wykonany jest produkt po kodzie kreskowym.
 *  
 *  ©2020, PBL1, grupa 5: Dasiewicz Julia, Duszczyk Karol, Kukla Michal, Twarowski Michal
 */

/* Kodowanie odpadow:
 * 0 - tworzywa sztuczne i metale
 * 1 - papier
 * 2 - szklo
 */

//HARDWARE
//RED(+)->D5
//YELLOW(+)->D2
//GREEN(+)->D1

// LISTA PRODUKTOW
// KOD_KRESKOWY | KATEGORIA_ODPADU

int listSize = 4; //ilosc produktow

String barCodes [][2] = {
  {"1234","0"},
  {"3456","1"},
  {"5678","2"},
  {"90343766","1"}
};




// Funkcja przyjmujaca kod produktu i zwracajaca kategorie odpadu (kod)

int FindCode(String code){
  for(int i=0; i<listSize; i++)
  {
    if(barCodes[i][0]==code)
    {
      return(barCodes[i][1].toInt());
    }
  }
  return (-1);
}




// Funkcja zamieniajaca kod kategorii odpadu na jego nazwe

String MaterialName(int code){
  switch(code){
    case 0:
      return ("tworzywa sztuczne");
      break;
    case 1:
      return ("papier");
      break;
     case 2:
      return ("szklo");
      break;
  }
  return("nieznany typ odpadu");
}



// DIODY - DEFINICJA PINOW

#define LED0_PIN 4
#define LED1_PIN 14
#define LED2_PIN 5




// Funkcja zapalajaca odpowiednia diode, na wejscie kod kategorii odpadu

void SignalLED(int code){

  if(code == 0 || code == 1 || code == 2)
  {
    int pin = 0;
    
    switch(code){
      case 0:
        pin = LED0_PIN;
        break;
      case 1:
        pin = LED1_PIN;
        break;
      case 2:
        pin = LED2_PIN;
        break;
    }

    digitalWrite(pin,HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
  }
  else //gdy nie znaleziono kodu w bazie - migaj wszystkimi diodami
  {
    digitalWrite(LED0_PIN,HIGH);
    digitalWrite(LED1_PIN,HIGH);
    digitalWrite(LED2_PIN,HIGH);
    delay(400);
    digitalWrite(LED0_PIN,LOW);
    digitalWrite(LED1_PIN,LOW);
    digitalWrite(LED2_PIN,LOW);
    delay(400);
    digitalWrite(LED0_PIN,HIGH);
    digitalWrite(LED1_PIN,HIGH);
    digitalWrite(LED2_PIN,HIGH);
    delay(400);
    digitalWrite(LED0_PIN,LOW);
    digitalWrite(LED1_PIN,LOW);
    digitalWrite(LED2_PIN,LOW);
  }
}



void setup() {
  
  Serial.begin(9600);

  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED0_PIN, LOW); //inicjalne gaszenie diody
  digitalWrite(LED1_PIN, LOW); //inicjalne gaszenie diody
  digitalWrite(LED2_PIN, LOW); //inicjalne gaszenie diody

}

void loop() {
  
  if(Serial.available() > 0) {                          //gdy dostarczono dane z monitora
    String inputCode = Serial.readStringUntil('\n');    //czytaj te dane
    int materialCode = FindCode(inputCode);             //szukanie kodu materialu w bazie
    Serial.println(MaterialName(materialCode));         //wypisanie kodu materialu
    SignalLED(materialCode);                            //swiecenie LED
  }
}
