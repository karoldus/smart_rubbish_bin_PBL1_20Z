#include <Keypad.h> //biblioteka od klawiatury

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
  }
}
