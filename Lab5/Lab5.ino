bool playing = false;
uint8_t countP1 = 0;
uint8_t countP2 = 0;

int estadoprev1 = 0;
int estadoprev2 = 0;
int estadoBoton1 = 0;
int estadoBoton2 = 0;

int ledsP1[] = {2,3,4,5,6,7,8,9};
int ledsP2[] = {23,24,25,26,27,28,29,10};

void setup() {
  Serial.begin(9600);
  //Semaforo
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  //Botones
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  //Leds Player 1  2
  for(int i = 0; i < 8; i++){
    pinMode(ledsP1[i], OUTPUT);
    pinMode(ledsP2[i], OUTPUT);
    }

}

void loop() {
  //Read buttons
  estadoBoton1 = !digitalRead(PUSH1);
  estadoBoton2 = !digitalRead(PUSH2);

  //Game started
  if (estadoBoton1 && estadoBoton2) {
    //Reset game
    for(int i = 0; i <= 8; i++){
      digitalWrite(ledsP1[i],LOW);
      digitalWrite(ledsP2[i],LOW);
    }
    countP1 = 0;
    countP2 = 0;
    playing = true;
    //Start sequence
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("3...");
    delay(1500);
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("2...");
    delay(1500);
    digitalWrite(RED_LED, LOW);
    Serial.println("1...");
    delay(1500);
    Serial.println("GO!!!");
  }

  while (playing){
    estadoBoton1 = singlePulse(PUSH1,&estadoprev1);
    estadoBoton2 = singlePulse(PUSH2,&estadoprev2);
        
    if(estadoBoton1){
      countP1++;      
      Serial.print("P1: ");
      Serial.println(countP1);
      if(countP1 >= 8){
        playing = false;
        Serial.println("Player 1 Wins");
      }
    }
    if(estadoBoton2){
      countP2++;
      Serial.print("P2: ");
      Serial.println(countP2);
      if(countP2 >= 8){
        playing = false;
        Serial.println("Player 2 Wins");
      }
    }
    //encender el LED correspondiente al contador
    for(int i = 0; i <= 8; i++){
      if (countP1-1 == i) digitalWrite(ledsP1[i],HIGH);
      else digitalWrite(ledsP1[i],LOW);

      if (countP2-1 == i) digitalWrite(ledsP2[i],HIGH);
      else digitalWrite(ledsP2[i],LOW);
    }
  }
  digitalWrite(GREEN_LED, LOW);
}

//Debouncer
int singlePulse(int buttonPin, int *prevState){
  int input = !digitalRead(buttonPin);
  if ((input == 1) && (input != *prevState)){
    *prevState = input;
    return 1;
  }
  else {
    *prevState = input;
    return 0;
  }
}
