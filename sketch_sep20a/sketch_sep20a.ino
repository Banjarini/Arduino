const int pwm = 2 ;  //initializing pin 2 as pwm
const int in_1 = 10 ;
const int in_2 = 9 ;

//For providing logic to L298 IC to choose the direction of the DC motor 

void setup()
{
pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_2,OUTPUT) ;
}

void loop()
{
//For Clock wise motion , in_1 = High , in_2 = Low
for(int i = 0; i <= 255; i++){
analogWrite(in_1,i) ;
digitalWrite(in_2,LOW) ;
delay(50);
}

for(int i =255; i > 0; i--){
//For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
analogWrite(in_1,i) ;
analogWrite(in_2,LOW) ;
delay(50);
}
for(int i = 0; i <= 255; i++){
analogWrite(in_2,i) ;
analogWrite(in_1,LOW) ;
delay(50);
}
for(int i =255; i > 0; i--){
//For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
analogWrite(in_1,LOW) ;
analogWrite(in_2,i) ;
delay(50);
}
}
