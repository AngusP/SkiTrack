/**
 * Kinda stupid but why not
 * A P M    2    S K I    T R A C K E R
 *
**/
 
 
 
void setup() {
  
  Serial.begin(38400);
  Serial1.begin(38400);
  
  /* Put the MT3329 GPS into NMEA Sentence mode: */
  Serial1.print("$PGCMD,16,1,1,1,1,1*6B\r\n");
  
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  
}

void loop() {

  while( Serial1.available() ){
    Serial.write(Serial1.read());
  }

}
