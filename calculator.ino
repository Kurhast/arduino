#include <IRremote.h>         
#include <LiquidCrystal.h>   

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long code0 = 0xFF6897;
unsigned long code1 = 0xFF30CF;
unsigned long code2 = 0xFF18E7;
unsigned long code3 = 0xFF7A85;
unsigned long code4 = 0xFF10EF;
unsigned long code5 = 0xFF38C7;
unsigned long code6 = 0xFF5AA5;
unsigned long code7 = 0xFF42BD;
unsigned long code8 = 0xFF4AB5;
unsigned long code9 = 0xFF52AD;
unsigned long codeAdd = 0xFF629D;  
unsigned long codeSub = 0xFFA857; 
unsigned long codeEqual = 0xFF9867;  
unsigned long codeReset = 0xFFB04F; 
unsigned long codeMul = 0xFFE01F;  
unsigned long codeDiv = 0xFF906F;   

float num1 = 0;
float num2 = 0;
char operation = 0;  
bool enteringSecondNumber = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.begin(16, 2);
  lcd.print("Calculatrice");
  delay(2000);  
  lcd.clear();
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned long codeReceived = results.value;
    Serial.print("Code reçu : ");
    Serial.println(codeReceived, HEX);  

    if (codeReceived == code0) {
      addDigit(0);
    } else if (codeReceived == code1) {
      addDigit(1);
    } else if (codeReceived == code2) {
      addDigit(2);
    } else if (codeReceived == code3) {
      addDigit(3);
    } else if (codeReceived == code4) {
      addDigit(4);
    } else if (codeReceived == code5) {
      addDigit(5);
    } else if (codeReceived == code6) {
      addDigit(6);
    } else if (codeReceived == code7) {
      addDigit(7);
    } else if (codeReceived == code8) {
      addDigit(8);
    } else if (codeReceived == code9) {
      addDigit(9);
    }
    
    else if (codeReceived == codeAdd) {
      setOperation('+');
    } else if (codeReceived == codeSub) {
      setOperation('-');
    } else if (codeReceived == codeMul) {
      setOperation('*');  // Multiplication
    } else if (codeReceived == codeDiv) {
      setOperation('/');  // Division
    }
    
    else if (codeReceived == codeEqual) {
      calculateResult();
    }
    
    else if (codeReceived == codeReset) {
      resetCalculator();
    }

    irrecv.resume();
  }
}

void addDigit(int digit) {
  if (!enteringSecondNumber) {
    num1 = num1 * 10 + digit;
    lcd.clear();
    lcd.print(int(num1));
  } else {
    num2 = num2 * 10 + digit;
    lcd.clear();
    lcd.print(int(num1));
    lcd.print(" ");
    lcd.print(operation);
    lcd.print(" ");
    lcd.print(int(num2));
  }
}

void setOperation(char op) {
  if (num1 != 0) {
    operation = op;
    enteringSecondNumber = true;
    lcd.clear();
    lcd.print(int(num1));
    lcd.print(" ");
    lcd.print(operation);
  }
}

void calculateResult() {
  float result = 0;
  
  if (operation == '+') {
    result = num1 + num2;
  } else if (operation == '-') {
    result = num1 - num2;
  } else if (operation == '*') {
    result = num1 * num2;
  } else if (operation == '/') {
    if (num2 != 0) {
      result = num1 / num2;
    } else {
      // Division par zéro
      lcd.clear();
      lcd.print("Erreur: Div par 0");
      delay(2000); 
      lcd.clear();
      return;
    }
  } else {
    lcd.clear();
    lcd.print("Erreur: Op ?");
    delay(2000); 
    lcd.clear();
    return;
  }

  lcd.clear();
  lcd.print("Result: ");
  lcd.print(result);
  delay(2000);

  num1 = result; 
  num2 = 0;
  operation = 0;
  enteringSecondNumber = false;
  lcd.clear();
  lcd.print(num1); 
}

void resetCalculator() {
  num1 = 0;
  num2 = 0;
  operation = 0;
  enteringSecondNumber = false;
  lcd.clear();
  lcd.print("Reset");
  delay(1000); 
  lcd.clear();
} 
