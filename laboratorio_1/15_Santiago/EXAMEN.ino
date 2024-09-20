 #include <EEPROM.h>
#define BAUDRATE 9600
#define BTN1 2
#define BTN2 3
#define LED1 8
#define LED2 9
#define LED3 10
#define CELDA 0
#define TMAX 10
#define TMIN 1

uint8_t tiempo = EEPROM.read(CELDA);
volatile unsigned long lasttime1 = 0;
volatile unsigned long lasttime2 = 0;
volatile unsigned long debounceDelay = 80;
volatile bool pin1 = false;
volatile bool pin2 = false;
volatile bool ejecucion = false;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN1),mas,RISING);
  attachInterrupt(digitalPinToInterrupt(BTN2),menos,RISING);
  Serial.begin(BAUDRATE);
}

void loop() {
  if(ejecucion==false){
    digitalWrite(LED1,1);
  }
  if(pin1==true && pin2==true){
    ejecucion = true;
  }
  if(ejecucion==true){
    digitalWrite(LED2,1);
    delay(1000);
    tiempo--;
    if(tiempo==0){
      Serial.println("CURADO COMPLETADO");
      ejecucion = false;
    }
  }
}

void mas(){
  if (millis() - lasttime1 > debounceDelay) {
    pin1 = true;
    if(tiempo<TMAX){
      tiempo++;
      EEPROM.write(CELDA, tiempo);
      Serial.print("Tiempo de curado: ");
      Serial.print(tiempo);
      Serial.println(".");
    }
    lasttime1 = millis();
  }
}

void menos(){
  if (millis() - lasttime2 > debounceDelay) {
    pin2 = true;
    if(tiempo>TMIN){
      tiempo--;
      EEPROM.write(CELDA, tiempo);
      Serial.print("Tiempo de curado: ");
      Serial.print(tiempo);
      Serial.println(".");
    }
    lasttime2 = millis();
  }
}