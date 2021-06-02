#include <Keypad.h>
#include <Servo.h>

/* LABMATT DASAFE CODE
 * Keypad Libray: https://playground.arduino.cc/Code/Keypad/#Download
 * Keypad Libray also includes example skech on how to use the keypad that this skech was based on.
 */

Servo latch;

String currentCode = "";
String keycode = "1234";

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  latch.attach(10);
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key){
    Serial.println(key);

    // A switch statment is one LARGE if statment. 
    switch(key) 
    {
      
      // If hash, check if code is correct. If CORRECT open the safe. Else clear the current code and Beep angarly.
      case '#': 
      if(currentCode == keycode)
      {
        // Unlock DaSafe
        Serial.println("Code Correct");
        latch.attach(10);
        latch.write(90);
        delay(1000);
        latch.detach();
        currentCode = "";
      } else
      {
        currentCode = "";
      }
      break;

      // If astix key is hit, lock the safe and clear the current code entery.
      case '*':
      latch.attach(10);
      latch.write(0);
      delay(1000);
      latch.detach();
      break;

      // If(key == 'C') Then clear the currentCode. If we made a mistake 
      case 'C':
      currentCode = "";
      break;
      
      default:
      currentCode = String(currentCode + key);
      Serial.println(currentCode);
      break;
    }
    
  }
}
