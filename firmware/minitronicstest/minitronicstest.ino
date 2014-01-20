#include "thermistortables.h"



 
 #define X_STEP_PIN 48
 #define X_DIR_PIN 47
 #define X_ENABLE_PIN 49
 #define X_MIN_PIN 5
 #define X_MAX_PIN -1 //2 //Max endstops default to disabled "-1", set to commented value to enable.
 
 #define Y_STEP_PIN 39 // A6
 #define Y_DIR_PIN 40 // A0
 #define Y_ENABLE_PIN 38
 #define Y_MIN_PIN 2
 #define Y_MAX_PIN -1 //15
 
 #define Z_STEP_PIN 42 // A2
 #define Z_DIR_PIN 43 // A6
 #define Z_ENABLE_PIN 41 // A1
 #define Z_MIN_PIN 6
 #define Z_MAX_PIN -1
 
#define E_STEP_PIN         45
#define E_DIR_PIN          44
#define E_ENABLE_PIN       27



#define SDPOWER            -1

#define EXTRUDERS 3

#define TEMP_SENSOR_AD595_OFFSET 0.0
#define TEMP_SENSOR_AD595_GAIN   1.0

#define THERMISTORHEATER_0 1
#define THERMISTORHEATER_1 1
#define THERMISTORHEATER_2 1

#define HEATER_0_USES_THERMISTOR 1
#define HEATER_1_USES_THERMISTOR 1
#define HEATER_2_USES_THERMISTOR 1

  static void *heater_ttbl_map[EXTRUDERS] = { (void *)heater_0_temptable
#if EXTRUDERS > 1
                                            , (void *)heater_1_temptable
#endif
#if EXTRUDERS > 2
                                            , (void *)heater_2_temptable
#endif
#if EXTRUDERS > 3
  #error Unsupported number of extruders
#endif
  };
  
    static int heater_ttbllen_map[EXTRUDERS] = { heater_0_temptable_len
#if EXTRUDERS > 1
                                             , heater_1_temptable_len
#endif
#if EXTRUDERS > 2
                                             , heater_2_temptable_len
#endif
#if EXTRUDERS > 3
  #error Unsupported number of extruders
#endif
  };
  
  #define PGM_RD_W(x)   (short)pgm_read_word(&x)

#define SDSS               53
#define LED_PIN            46




#define KILL_PIN           -1

#define HEATER_0_PIN       9
#define HEATER_1_PIN       8
#define HEATER_2_PIN       7
#define HEATER_3_PIN       3

#define TEMP_0_PIN         7  // ANALOG NUMBERING
#define TEMP_1_PIN         6   // ANALOG NUMBERING




void setup() {

  pinMode(TEMP_0_PIN  , INPUT);
  pinMode(TEMP_1_PIN  , INPUT);
  pinMode(X_MIN_PIN  , INPUT);
  pinMode(Y_MIN_PIN  , INPUT);
  pinMode(Z_MIN_PIN  , INPUT);
  


  pinMode(HEATER_0_PIN , OUTPUT);
  pinMode(HEATER_1_PIN , OUTPUT);
  pinMode(HEATER_2_PIN , OUTPUT);
  pinMode(HEATER_3_PIN , OUTPUT);
  pinMode(LED_PIN  , OUTPUT);
  
  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);
  
  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);
  
  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);
  
  pinMode(E_STEP_PIN  , OUTPUT);
  pinMode(E_DIR_PIN    , OUTPUT);
  pinMode(E_ENABLE_PIN    , OUTPUT);
  

  
   digitalWrite(X_ENABLE_PIN    , LOW);
    digitalWrite(Y_ENABLE_PIN    , LOW);
    digitalWrite(Z_ENABLE_PIN    , LOW);
    digitalWrite(E_ENABLE_PIN    , LOW);

    Serial.begin(115200);
    
      Serial.print("\nInitializing SD card...");
  
;


}



float analog2temp(int raw, uint8_t e2) {

  #ifdef HEATER_0_USES_MAX6675
    if (e2 == 0)
    {
      return 0.25 * raw;
    }
  #endif

  if(heater_ttbl_map[e2] != 0)
  {
    float celsius = 0;
    byte i;  
    short (*tt)[][2] = (short (*)[][2])(heater_ttbl_map[e2]);

    raw = (1023 * OVERSAMPLENR) - raw;
    for (i=1; i<heater_ttbllen_map[e2]; i++)
    {
      if ((PGM_RD_W((*tt)[i][0]) > raw) && ((float)(PGM_RD_W((*tt)[i][0]) - PGM_RD_W((*tt)[i-1][0])) >0))
      {
        celsius = PGM_RD_W((*tt)[i-1][1]) + 
          (raw - PGM_RD_W((*tt)[i-1][0])) * 
          (float)(PGM_RD_W((*tt)[i][1]) - PGM_RD_W((*tt)[i-1][1])) /
          (float)(PGM_RD_W((*tt)[i][0]) - PGM_RD_W((*tt)[i-1][0]));
        break;
      }
    }

    // Overflow: Set to last value in the table
    if (i == heater_ttbllen_map[e2]) celsius = PGM_RD_W((*tt)[i-1][1]);

    return celsius;
  }
  return ((raw * ((5.0 * 100.0) / 1024.0) / OVERSAMPLENR) * TEMP_SENSOR_AD595_GAIN) + TEMP_SENSOR_AD595_OFFSET;
}

unsigned long prevMillis;

void loop () {
  

  
  if (millis() %1000 <500) 
    digitalWrite(LED_PIN, HIGH);
  else
   digitalWrite(LED_PIN, LOW);
  
  if (millis() %1000 <250) {
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(HEATER_2_PIN, LOW);
    digitalWrite(HEATER_3_PIN, HIGH);
  } else if (millis() %1000 <500) {
    digitalWrite(HEATER_0_PIN, HIGH);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(HEATER_2_PIN, LOW);
    digitalWrite(HEATER_3_PIN, LOW);
   } else if (millis() %1000 <750) {
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, HIGH);
    digitalWrite(HEATER_2_PIN, LOW);
    digitalWrite(HEATER_3_PIN, LOW);
  } else  {
    digitalWrite(HEATER_0_PIN, LOW);
    digitalWrite(HEATER_1_PIN, LOW);
    digitalWrite(HEATER_2_PIN, HIGH);
    digitalWrite(HEATER_3_PIN, LOW);
  }
  
  if (millis() %2000 <1000) {
    digitalWrite(X_DIR_PIN    , HIGH);
    digitalWrite(Y_DIR_PIN    , HIGH);
    digitalWrite(Z_DIR_PIN    , HIGH);
    digitalWrite(E_DIR_PIN    , HIGH);

  }
  else {
    digitalWrite(X_DIR_PIN    , LOW);
    digitalWrite(Y_DIR_PIN    , LOW);
    digitalWrite(Z_DIR_PIN    , LOW);
    digitalWrite(E_DIR_PIN    , LOW);

  }
  
  
    digitalWrite(X_STEP_PIN    , HIGH);
    digitalWrite(Y_STEP_PIN    , HIGH);
    digitalWrite(Z_STEP_PIN    , HIGH);
    digitalWrite(E_STEP_PIN    , HIGH);

  delay(1);
  
  
  
    
    digitalWrite(X_STEP_PIN    , LOW);
    digitalWrite(Y_STEP_PIN    , LOW);
    digitalWrite(Z_STEP_PIN    , LOW);
    digitalWrite(E_STEP_PIN    , LOW);

    
    if (millis() -prevMillis >100){
    prevMillis=millis();
    

    

    int t = analogRead( TEMP_0_PIN);
    Serial.print("T1 ");
    Serial.print(t);
    Serial.print("/");
    Serial.print(analog2temp(1024 - t,0),0);
    

    
    Serial.print(" T2 ");
    t = analogRead( TEMP_1_PIN);
    Serial.print(t);
    Serial.print("/");
    Serial.print(analog2temp(1024 - t,1),0);
    
    Serial.print(" E1 ");
    t = digitalRead( X_MIN_PIN);
    Serial.print(t);
    
    Serial.print(" E2 ");
    t = digitalRead( Y_MIN_PIN);
    Serial.print(t);
    
    Serial.print(" E3 ");
    t = digitalRead( Z_MIN_PIN);
    Serial.println(t);
 

    }



}
