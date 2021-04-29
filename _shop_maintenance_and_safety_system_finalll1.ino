#include <Servo.h>

int output1Value = 0;
int sen1Value = 0;
int sen2Value = 0;
int const gas_sensor = A1;
int const LDR = A0;
int limit = 400;


int buzzer=11;
//int Forcesensor=A1;
int Forcevalue=0;
int forcePin=A1;



int LightSensorVal = 0; //Input SEnsor
int PIRSensorVal = 0;   //Input S
int RelayOutputVal = 0;  //Output Relay 



long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
// Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_7;

void setup()
{
   Serial.begin(9600);		//initialize serial communication
  pinMode(A0, INPUT);		//LDR
  pinMode(A1,INPUT);      	//gas sensor
  pinMode(13, OUTPUT);		//connected to relay
  servo_7.attach(7, 500, 2500); //servo motor

  pinMode(8,OUTPUT);     	//signal to piezo buzzer
  pinMode(9, INPUT);		//signal to PIR	
  pinMode(10, OUTPUT);		//signal to npn as switch
  pinMode(4, OUTPUT);		//Red LED
  pinMode(3, OUTPUT);		//Green LED

  pinMode(forcePin,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  
  pinMode(A0, INPUT); // Read the LDR sensor Value digital Input
  pinMode(2, INPUT);  // Read the PIR motion sensor value digital Input
  pinMode(8, OUTPUT); // Write the Relay output value, digital output
  Serial.begin(9600);
  
}

void loop()
{
  
     //------light intensity control------//

    int val1 = analogRead(LDR);
  if (val1 > 500) 
  	{
    	digitalWrite(13, LOW);
    Serial.print("Bulb ON = ");
    Serial.print(val1);
  	} 
  else 
  	{
    	digitalWrite(13, HIGH);
     Serial.print("Bulb OFF = ");
    Serial.print(val1);
  	}

//--------------------------------------------------------------  
        //------ light & fan control --------// 
//--------------------------------------------------------------
  sen2Value = digitalRead(9);
  if (sen2Value == 0) 
  	{
    	digitalWrite(10, LOW); //npn as switch OFF
    	digitalWrite(4, HIGH); // Red LED ON,indicating no motion
    	digitalWrite(3, LOW); //Green LED OFF, since no Motion detected
        Serial.print("\n");
        Serial.print("     || NO Motion Detected    " );
        Serial.print("\n");
  	}
 
  if (sen2Value == 1) 
  	{
    	digitalWrite(10, HIGH);//npn as switch ON
    delay(1000);
    	digitalWrite(4, LOW); // RED LED OFF 
    	digitalWrite(3, HIGH);//GREEN LED ON , indicating motion detected
     Serial.print("\n");
    Serial.print(" 	   || Motion Detected!      " );
    Serial.print("\n");
  	}
  delay(300);
  
//---------------------------------------------------------------
       // ------- Gas Sensor --------//
//---------------------------------------------------------------
int val = analogRead(gas_sensor);      //read sensor value
  Serial.print("\n");
  Serial.print("|| Gas Sensor Value = ");
  Serial.print(val);	 //Printing in serial monitor
  Serial.print("\n");
//val = map(val, 300, 750, 0, 100); 
  if (val > limit)
  	{
    	tone(8, 500);
  	}
 	delay(300);
 	noTone(8);

 //-------------------------------------------------------------- 
      //-------  servo motor  ---------//
 //------------------------------------------------------------- 
  sen1Value = 0.01723 * readUltrasonicDistance(6, 6);

  if (sen1Value < 100) 
  	{
    	servo_7.write(90);
    Serial.print("\n");
    Serial.print(" 	  || Door Open!  ; Distance = ");
    Serial.print(sen1Value);
   Serial.print("\n");
 
  	} 
  else 
  	{
    	servo_7.write(0);
    Serial.print("\n");
    Serial.print(" 	  || Door Closed! ; Distance =  ");
    Serial.print(sen1Value);
    Serial.print("\n");
  }
  delay(10); // Delay a little bit to improve simulation performance

//-------------------------------------------------
  //-----------------force sensor-------------
  //------------------------------------------
    Forcevalue =analogRead(forcePin);
    Serial.println(Forcevalue);
    noTone(buzzer);
    tone(buzzer,Forcevalue);
    Serial.print("||force value! ; Forcevalue");
    Serial.print(Forcevalue);
   Serial.print("\n");
    
  
  //-------------------------------------------------------
   //------------------light intensity-------------
  //----------------------------------------------------
  
  LightSensorVal = analogRead(A0);
  PIRSensorVal = digitalRead(2);
  RelayOutputVal = 8;
  if (LightSensorVal < 600) 
  {
    if (PIRSensorVal == HIGH) 
    {
      digitalWrite(8, HIGH);
      delay(300); // Wait for 300 millisecond(s)
      Serial.print("\n");
      Serial.print("Bulb OFF = ");
      Serial.print(RelayOutputVal);
    } else
    {
      digitalWrite(8, LOW);
      delay(300); // Wait for 300 millisecond(s)
      Serial.print("\n");
      Serial.print("Bulb OFF = ");
      Serial.print(RelayOutputVal);
    }
  }
  else 
  {
    digitalWrite(8, LOW);
    Serial.println(LightSensorVal);
    delay(300); // Wait for 300 millisecond(s)
    Serial.print("\n");
    Serial.print("Bulb ON = ");
    Serial.print(RelayOutputVal);
  }
  
}