#define pinB1 9
#define pinB2 8
#define pinB3 7
#define pinB4 6
#define pinB5 5
#define pinB6 4
#define pinB7 3
#define pinB8 2
#define pinB9 A0
#define pinB10 A1
#define pinB11 A2
#define pinB12 A3

#define pinL1 A4
#define pinL2 A5
#define pinL3 10
#define pinL4 11
#define pinL5 12

#define minTime 300

struct button {
  long long Time = 0;
  bool on = false;
  int note;
};

button data[4][12];
int octave = 3;
bool octaveButtonPushed = false;

void setup() {
  pinMode(pinB1 , OUTPUT);  
  pinMode(pinB2 , OUTPUT); 
  pinMode(pinB3 , OUTPUT); 
  pinMode(pinB4 , OUTPUT); 
  pinMode(pinB5 , OUTPUT); 
  pinMode(pinB6 , OUTPUT); 
  pinMode(pinB7 , OUTPUT); 
  pinMode(pinB8 , OUTPUT); 
  pinMode(pinB9 , OUTPUT); 
  pinMode(pinB10 , OUTPUT); 
  pinMode(pinB11 , OUTPUT); 
  pinMode(pinB12 , OUTPUT); 
  pinMode(pinL1 , INPUT);  
  pinMode(pinL2 , INPUT); 
  pinMode(pinL3 , INPUT);
  pinMode(pinL4 , INPUT);
  pinMode(pinL5 , INPUT);

   pinMode(13 , OUTPUT);
   Serial.begin(115200);
}

void checkButtonsState(int i) {
  if(digitalRead(pinL1) != 0) {
    if(octaveButtonPushed == false) {
      if(octave < 7) {
        octave++;
      } else {
        octave = 0;
      }
      on((octave+0)*12 , 127);
      on((octave+0)*12 + 11 , 127);
      delay(1000);
      off((octave+0)*12 , 0);
      off((octave+0)*12 + 11 , 0);
      octaveButtonPushed = true;
    }
  } else {
    octaveButtonPushed = false;
  }
  
  if(digitalRead(pinL2) != 0) {
    if( (millis() - data[0][i].Time) > minTime , data[0][i].on == false ) {
      data[0][i].note = (octave+0)*12 + i-1;
      data[0][i].on = true;
      data[0][i].Time = millis();
      on(data[0][i].note , 127);
    }
  } else {
    if(data[0][i].on == true) {
      data[0][i].on = false;
      off(data[0][i].note , 0);
      data[0][i].Time = millis();
    }
  }

  if(digitalRead(pinL3) != 0) {
    if( (millis() - data[1][i].Time) > minTime , data[1][i].on == false ) {
      data[1][i].note = (octave+1)*12 + i-1;
      data[1][i].on = true;
      data[1][i].Time = millis();
      on(data[1][i].note , 127);
    }
  } else {
    if(data[1][i].on == true) {
      data[1][i].on = false;
      off(data[1][i].note , 0);
      data[1][i].Time = millis();
    }
  }

  if(digitalRead(pinL4) != 0) {
    if( (millis() - data[2][i].Time) > minTime , data[2][i].on == false ) {
      data[2][i].note = (octave+2)*12 + i-1;
      data[2][i].on = true;
      data[2][i].Time = millis();
      on(data[2][i].note , 127);
    }
  } else {
    if(data[2][i].on == true) {
      data[2][i].on = false;
      off(data[2][i].note , 0);
      data[2][i].Time = millis();
    }
  }

  if(digitalRead(pinL5) != 0) {
    if( (millis() - data[3][i].Time) > minTime , data[3][i].on == false ) {
      data[3][i].note = (octave+3)*12 + i-1;
      data[3][i].on = true;
      data[3][i].Time = millis();
      on(data[3][i].note , 127);
    }
  } else {
    if(data[3][i].on == true) {
      data[3][i].on = false;
      off(data[3][i].note , 0);
      data[3][i].Time = millis();
    }
  }
}

void loop () {
  digitalWrite(pinB1 , HIGH);
  checkButtonsState(1);
  digitalWrite(pinB1 , LOW);
  
  digitalWrite(pinB2 , HIGH);
  checkButtonsState(2);
  digitalWrite(pinB2 , LOW);
  
  digitalWrite(pinB3 , HIGH);
  checkButtonsState(3);
  digitalWrite(pinB3 , LOW);
  
  digitalWrite(pinB4 , HIGH);
  checkButtonsState(4);
  digitalWrite(pinB4 , LOW);
  
  digitalWrite(pinB5 , HIGH);
  checkButtonsState(5);
  digitalWrite(pinB5 , LOW);
  
  digitalWrite(pinB6 , HIGH);
  checkButtonsState(6);
  digitalWrite(pinB6 , LOW);
  
  digitalWrite(pinB7 , HIGH);
  checkButtonsState(7);
  digitalWrite(pinB7 , LOW);
  
  digitalWrite(pinB8 , HIGH);
  checkButtonsState(8);
  digitalWrite(pinB8 , LOW);
  
  digitalWrite(pinB9 , HIGH);
  checkButtonsState(9);
  digitalWrite(pinB9 , LOW);
  
  digitalWrite(pinB10 , HIGH);
  checkButtonsState(10);
  digitalWrite(pinB10 , LOW);
  
  digitalWrite(pinB11 , HIGH);
  checkButtonsState(11);
  digitalWrite(pinB11 , LOW);

  digitalWrite(pinB12 , HIGH);
  checkButtonsState(12);
  digitalWrite(pinB12 , LOW);
}


void on(byte PITCH, byte VELOCITY)
{
  Serial.write(0x90 ); // 9 - номер MIDI канала для перкуссии
  Serial.write(PITCH);       // Нота
  Serial.write(VELOCITY);    // Громкость
}

void off( byte PITCH, byte VELOCITY)
{
  Serial.write(0x80 ); // 9 - номер MIDI канала для перкуссии
  Serial.write(PITCH);       // Нота
  Serial.write(VELOCITY);    // Громкость
}
