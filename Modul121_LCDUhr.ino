#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
/*Dieses Programm wurde von Dorian Stanojevic, Schüler der IBZ Schule Aarau, geschrieben.
 Version 0.01
 Geschrieben wurde es für die Leistungsbeurteilung des Moduls 121
*/
LiquidCrystal_PCF8574 lcd(0x3f); 

/* Hier werden alle Variabeln der Uhr definiert. 
 *  - Die Variabel hour ist für die Stundenzahl der Uhr. Minutes wurde für die Minutenzahl definiert
 *  Die Strings short_early und short_late werden für die Anzeige von AM morgens angezeigt und PM für Nachmittag und abends.

*/
int show = -1;
int hour = 0;
int minutes =0;
String short_early = "AM";
String short_late = "PM";
/* Nun wird die Funktion displaytime erstellt, welche die gesamte Logik der Uhr entaehlt. Als erstes wird sichergestellt, dass keine Zeichen mehr auf dem Display mehr angezeigt werden. Die
 *  Hintergrundbeleuchtung wird auf das Maximum gesetzt.  In der For-Schleife wird folgende Logik der Uhr vorgenommen:
 *  Sobald die Zählervariabel den Wert von 60 hat, wird die Variabel für die Minuten um eins erhöht. Danach wird der Wert von der Zählervariabel i wieder auf 0 gesetzt. 
 *  Wenn die Minuten Variabel den Wert 60 hat, wird der Wert der Stundenvariabel um eins erhöht und der Wert der Minuten auf 0 gesetzt. Wenn die Stundenvariabel den Wert 25 erreicht,
 *  wird diese durch 25 abgezogen, sodass diese auf 0 gesetzt wird. Danach wird der Wert um eins erhöht. Dies dient dazu, dass der Wert der Stundenvariabel wieder bei 0 anfängt, nachdem die 
 *  Uhrzeit 24 Uhr war. Wenn der Wert der Stundenanzahl und der Minutenanzahl 0 ist und der Wert kleiner oder gleich 9 ist, wird eine 0 vor dem Wert angezeigt, um jeweils 2 stellige
 *  Felder für je die Stunde und die Minute angezeigt wird. Wenn eine 0 angezeigt wird, wird eine andere Position für die Minute und die Stunde angezeigt, als wenn keine angezeigt wird,
 *  dies wird gemacht, damit die zweistelligen Zahlen an den gleichen Stellen auf dem Display sind wie einstellige Zahlen.
 */
void displaytime() {
  lcd.clear();
  
  lcd.setBacklight(255);
  
for (int i = 0; i < 61; i++)
   {
          if (i == 60)
        {
            minutes = minutes + 1;
            i = i - 60;
        }
          if (minutes == 60)
          {
              hour = hour + 1;
              minutes = 0;
          }
          if (hour == 25)
          {
              hour = hour - hour;
              hour = hour + 1;
          };      
          
 lcd.clear();
 if (hour<=11)  {
    lcd.setCursor(6, 0); // top left
   lcd.print(short_early);
  }

  if (hour>=12)  {
    lcd.setCursor(6, 0); // top left
   lcd.print(short_late);
  }
   if (hour<=9) 
   lcd.setCursor(0, 0);{
  lcd.print("0");
   }

      if (hour<=9) {
   lcd.setCursor(1, 0);
  lcd.print(hour);
   } else {
  lcd.setCursor(0, 0); // top left
 lcd.print(hour);
}
     if (minutes<=9) 
   lcd.setCursor(3, 0);{
  lcd.print("0");
   }


      if (minutes<=9) {
   lcd.setCursor(4, 0);
  lcd.print(minutes);
   } else {
  lcd.setCursor(3, 0); // top left
 lcd.print(minutes);
}
   
  lcd.setCursor(2, 0); // top left
  lcd.print(":");
 delay(1000);
  lcd.noBlink();
    lcd.noCursor();
  }

}
/*
Dieser Teil ist Teil des Examples und dient um zu sehen ob das LCD Display funktioniert und um es zu initialisieren.

*/
void setup() 
{
  int error;

  Serial.begin(115200);
  Serial.println("LCD...");

  // wait on Serial to be available on Leonardo
  while (!Serial)
    ;

  Serial.println("Dose: check for LCD");

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(16, 2); // initialize the lcd

  } else {
    Serial.println(": LCD not found.");
  } // if
 
} // setup()


void loop(){
 displaytime();
} // loop()
