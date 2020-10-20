/* Kosz na smieci rozpoznajacy material, z ktorego wykonany jest produkt po kodzie kreskowym.
 *  
 *  ©2020, PBL1, grupa 5: Dasiewicz Julia, Duszczyk Karol, Kukla Michal, Twarowski Michal
 */

/* Kodowanie odpadow:
 * 0 - tworzywa sztuczne i metale
 * 1 - papier
 * 2 - szklo
 */


// LISTA PRODUKTOW
// KOD_KRESKOWY | KATEGORIA_ODPADU

int listSize = 2; //ilosc produktow

String barCodes [][2] = {
  {"1234","0"},
  {"3456","1"}
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





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    String inputCode = Serial.readStringUntil('\n');
    Serial.println(MaterialName(FindCode(inputCode)));
  }
}
