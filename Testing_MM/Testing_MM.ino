int motorEN = 4;
int MotorLogic1 = 9;
int MotorLogic2 = 10;
int value;
int value2;
int Rec_Pin = 22;
int E_Pin = 23;
int Rec_Pin2 = 6;
int E_Pin2 = 5;

/*=======Motor Logic=======*/
void go(){
  Serial.write("Motor On\n");
  digitalWrite(motorEN, HIGH);
  digitalWrite(MotorLogic1, LOW);
  digitalWrite(MotorLogic2, HIGH);
  delay(1000); 
  
} 
/*=======Testing IR=======*/
void irReadTest(){
  digitalWrite(E_Pin, HIGH);
  value = analogRead(Rec_Pin);
  Serial.print("Reading 1:  ");
  Serial.println(value); 
//  delay(300);
//  digitalWrite(E_Pin, LOW);
  //two
//  digitalWrite(E_Pin2, HIGH);
//  value2 = analogRead(Rec_Pin2);
//  Serial.print("Reading 2:  ");
//  Serial.println(value2); 
//  delay(300);
//  digitalWrite(E_Pin2, LOW);
  
 
}

void setup() {
  //Motor Control
  pinMode(motorEN, OUTPUT);
  pinMode(MotorLogic1, OUTPUT);
  pinMode(MotorLogic2, OUTPUT);
  digitalWrite(motorEN, LOW);
  //IR Rec and Emitter
  pinMode(Rec_Pin, INPUT);
  pinMode(E_Pin, OUTPUT);
//  pinMode(Rec_Pin2, INPUT);
//  pinMode(E_Pin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //go();
  irReadTest();
}
  


