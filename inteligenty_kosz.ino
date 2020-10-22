/* Kosz na smieci rozpoznajacy material, z ktorego wykonany jest produkt po kodzie kreskowym.
 *  
 *  ©2020, PBL1, grupa 5: Dasiewicz Julia, Duszczyk Karol, Kukla Michal, Twarowski Michal
 */

/* Kodowanie odpadow:
 * 0 - tworzywa sztuczne i metale
 * 1 - papier
 * 2 - szklo
 * -1 - nieznany typ
 */




//HARDWARE
//RED(+)->D5
//YELLOW(+)->D2
//GREEN(+)->D1



//biblioteki do wifi
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;

//dane do wifi
#define wifi_SSID "UPC4466B1C"
#define wifi_password "xxxxxxxxxxxx"

//sciezka do serwera
#define server_adress "http://192.168.0.39/pbl/codes.php?code="


//funkcja dostaje kod kreskowy produktu, a zwraca kod materialu dla tego produktu z serwera
int FindCode(String code){
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    //Serial.print("[HTTP] begin...\n");

    
    String url = server_adress + code;
    
    http.begin(url); //HTTP

    //Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) 
    {
      // HTTP header has been send and Server response header has been handled
      //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        http.end();
        return(payload.toInt());
      }
    } 
    else //gdy blad polaczenia z serwerem
    { 
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      http.end();
      return(-1);
    }

    http.end();
  }
  else //gdy nie laczy sie z wifi
    return(-1);
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


  //laczenie z wifi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(wifi_SSID, wifi_password); //zmienic na haslo i ssid ogolne

}

void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED)) { //gdy polaczono z wifi

    if(Serial.available() > 0) {                          //gdy dostarczono dane z monitora
      String inputCode = Serial.readStringUntil('\n');    //czytaj te dane
      int materialCode = FindCode(inputCode);             //szukanie kodu materialu w bazie
      Serial.println(MaterialName(materialCode));         //wypisanie kodu materialu
      SignalLED(materialCode);                            //swiecenie LED
    }
  }
}
