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

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  Serial.println("forward");
}

void back() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,80);
  analogWrite(ENB,80);
  Serial.println("back");
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA,150);
  analogWrite(ENB,150);
  Serial.println("left");
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,150);
  analogWrite(ENB,150);
  Serial.println("right");
}

void pause() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("pause");
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop() {
   
    value = Serial.read();

    if (value == 'L') {
      Serial.println("Left");
      left();
    }
    if (value == 'R') {
      Serial.println("Right");
      right();
    }
    if (value == 'F') {
      Serial.println("Forward");
      forward();
    }
    if (value == 'B') {
      Serial.println("Backward");
      back();
    }
      if (value == 'P') {
      Serial.println("pause");
     pause();
    }
}
