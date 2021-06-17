// the direction of the car's movement
//ENA   ENB   IN1   IN2   IN3   IN4    description
//HIGH  HIGH  HIGH  LOW   LOW   HIGH   car is running forward
//HIGH  HIGH  LOW   HIGH  HIGH  LOW    car is running back 
//HIGH  HIGH  LOW   HIGH  LOW   HIGH   car is turning left
//HIGH  HIGH  HIGH  LOW   HIGH  LOW    car is turning right
//HIGH  HIGH  LOW   LOW   LOW   LOW    car is stoped
//HIGH  HIGH  HIGH  HIGH  HIGH  HIGH   car is stoped
//LOW   LOW   N/A   N/A   N/A   N/A    car is stoped

//define L298n module IO Pin
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

char value;
boolean avance=false;
boolean recule=false;

int Echo = A4;
int Trig = A5;

int Echo2 = A1;
int Trig2 = A0;

void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  Serial.println("forward-Arduino");
  delay(50);
}

void back() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  Serial.println("Back-Arduino");
  delay(50);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA,220);
  analogWrite(ENB,220);
  Serial.println("left-Arduino");
  delay(50);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,220);
  analogWrite(ENB,220);
  Serial.println("right-Arduino");
delay(50);
}

void stop() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("stop-Arduino");
  delay(50);}
  
long lecture_echo;
long cm;
//Ultrasonic distance measurement Sub function
int getDistance() {
    digitalWrite(Trig, HIGH);
 delayMicroseconds(40);
 digitalWrite(Trig, LOW);
 lecture_echo = pulseIn(Echo, HIGH);
 cm = lecture_echo / 58;
  Serial.println("bbbbbbbb");

   Serial.println(cm);
  
    return cm;
    
}

long lecture_echo2;
long CM2;
//Ultrasonic distance measurement Sub function
int getDistance2() {
    digitalWrite(Trig2, HIGH);
 delayMicroseconds(50);
 digitalWrite(Trig2, LOW);
 lecture_echo2 = pulseIn(Echo2, HIGH);
 
 CM2 = lecture_echo2 / 58;
 Serial.println("aaaaaaaaaaa");

   Serial.println(CM2);

    return CM2;
   
}



void setup() {
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);


}

void loop() {
 
    value=Serial.read();
     
    if (value == 'L') {
      left();
      delay(10);
      }
      
    if (value == 'R') {
      right();
     // delay(10);
      }



        if (value == 'B'){
     if ((getDistance() > 20)||(getDistance()==0)) {
      back();
      recule=true;
      //delay(10); 
      }   }
      
  if((getDistance() < 20)&&(recule==true))
  {
  
    stop();  
   Serial.println("stop-1");
      recule=false;
      //delay(10);
      }


      
        if (value == 'F'){
     if ((getDistance2() > 20)||(getDistance2()==0)) {
      forward();
      avance=true;
      //delay(10); 
      }
      }
      
  if((getDistance2() < 20)&&(avance==true)&&(getDistance2() >0))
  {
    stop();  
      avance=false;
      //delay(10); 
      }

      
    
      if (value == 's') {
     stop();
     //delay(10);
     }
delay(100);
}
