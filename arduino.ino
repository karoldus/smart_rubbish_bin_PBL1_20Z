/* Kosz na smieci - kod dla Arduino - obsluga klawiatury i wyswietlacza
 * 
 * ©2020, PBL1, grupa 5: Dasiewicz Julia, Duszczyk Karol, Kukla Michal, Twarowski Michal
 * 
 * POLACZENIE
 * 
 * Arduino - klawiatura
 * 2,3,4,5,7,8,9 - 1,2,3,4,6,7,8 (liczac od dolu)
 * 
 * Arduino - wyswietlacz
 * A4 - SDA
 * A5 - SCL
 * GND - GND
 * 5V - VCC
 * 
 * Arduino - ESP8266
 * GND - GND
 * TX - RX
 */



#include <Keypad.h> //biblioteka od klawiatury
#include <LiquidCrystal_I2C.h> //biblioteka do wyswietlacza

LiquidCrystal_I2C lcd(0x27,16,2); //inicjalizacja wyswietlacza

const byte ROWS = 4; // ile wierszy
const byte COLS = 3; //ile kolumn

byte rowPins[ROWS] = {5, 4, 3, 2}; //piny wierszy
byte colPins[COLS] = {7, 8, 9}; //piny kolum

char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury


String kod = "";

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}
  
void loop(){
  
  char klawisz = klawiatura.getKey();
  
  if (klawisz){
    if(klawisz == '*' || klawisz == '#')
    {
      if(klawisz == '#') //zatwierdzanie kodu i wysylanie
      {
        Serial.println(kod);
        kod = "";
      }
      else if (kod.length()>0) //usuwanie ostatniego znaku
      {
        kod.remove(kod.length()-1);
      }
    }
    else //gdy wcisnieta liczba
    {
      kod = kod + klawisz;
    }

    // wyswietlanie na wyswietlaczu
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(kod);
  }
}
