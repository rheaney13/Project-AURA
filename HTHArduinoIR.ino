//Libraries
  #include <Servo.h>

  #include <IRLib.h>

  #include <Time.h>





//Defines the values that are tied to each IR button
  #define Protocol NEC

  #define ShadeUp 0x20DF40BF 
  #define ShadeDwn 0x20DFC03F
  #define LightUp 0x20DF00FF
  #define LightDwn 0x20DF807F


  
//Defines the pin for IR reciever, and defines the decoder
  int RECV_Pin = 9;

  IRrecv RCV(RECV_Pin);

  IRdecode DCD;


  
//Declares Servos A and B, and defines position variables for each
  Servo ServoA;

  Servo ServoB;

  int posA;

  int posB;



//Declares the time variable
  int Time;
  int currentHour = 5;
  int currentMinute = 59;
  int currentSecond = 50;
  int currentDay = 20;
  int currentMonth = 8;
  int currentYear = 2016;


//Declares display output variable, the 3 display pins, and here come datArray
  int valToWrite;
  
  const int latchPin = 12;

  const int clockPin = 8;

  const int dataPin = 11;

  int datArray[12] = {96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156};


//Defines LED Pin
  int PMLed = 6;
  int buttonPin = 2;

  int buttonState = 0;


void setup() {
  
  //Attaches each servo to a digital pin, and writes an inital position
    ServoA.attach(3);

    ServoB.attach(5);

    ServoA.write(3);

    ServoB.write(3);



  //Starts the IR reciever
    RCV.enableIRIn();



  //Starts serial monitor, and sets time
    Serial.begin(9600);

    setTime(currentHour, currentMinute, currentSecond, currentDay, currentMonth, currentYear);


  //Assigns the display pins as outputs
    pinMode (latchPin, OUTPUT);
    pinMode (clockPin, OUTPUT);
    pinMode (dataPin, OUTPUT);
    pinMode(buttonPin, INPUT);

  //Attaches LED to Pin
    pinMode(PMLed, OUTPUT);
      
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    currentHour += 1;
    setTime(currentHour, currentMinute, currentSecond, currentDay, currentMonth, currentYear);
  }
//Commands to write to Servo A
  if(RCV.GetResults(&DCD)) {
   
    DCD.decode();
    if(DCD.decode_type==Protocol) {
      
      switch(DCD.value) {
        
        case ShadeUp: posA = 177; break;
        case ShadeDwn: posA = 3; break;
        case LightUp: posB = 177; break;
        case LightDwn: posB = 3; break;
        
      }
      
     ServoB.write(posB);
     ServoA.write(posA);
    }

   //Resumes receiving IR signals
   RCV.resume(); 
    }
    
  

//At a certain hr/min/s, this command writes 180 to both servos
  //AM Command
  if(hour() == 6&&minute() == 0&&second() == 0) {
    ServoA.write(177);
    ServoB.write(177);
    
    
  }
 //PM Command
 if(hour() == 21&&minute() == 0&&second() == 0) {
    ServoA.write(3);
    ServoB.write(3);
    
  }


/*Prints the seconds to the serial monitor*/
  //Serial.print(second());


//Assigns a variable to the hour function
  int hr = hour();

//Prints the hour funtion for logging
  //Serial.print(hr);

 //Calls the parsing command within the loop 
  parseHour(hr);

 //Writes valToWrite to the display 
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valToWrite);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  if(hour() <= 10 && hour() >= 0){
    digitalWrite(PMLed, LOW);
  }else{
    digitalWrite(PMLed, HIGH);
  }
 
}

//Translates the hour digit into a writeable value
int parseHour(int hr){
  if (hr == 0){
    valToWrite = datArray[0];
    return valToWrite;
  }
   if (hr == 1) {
    valToWrite = datArray[1];
    return valToWrite;
   }
   if (hr == 2) {
    valToWrite = datArray[2];
    return valToWrite;
   }
   if (hr == 3) {
    valToWrite = datArray[3];
    return valToWrite;
   }    
  if (hr == 4){
    valToWrite = datArray[4];
    return valToWrite;
  }
   if (hr == 5) {
    valToWrite = datArray[5];
    return valToWrite;
   }
  if (hr == 6){
    valToWrite = datArray[6];
    return valToWrite;
  }
   if (hr == 7) {
    valToWrite = datArray[7];
    return valToWrite;
   }
   if (hr == 8) {
    valToWrite = datArray[8];
    return valToWrite;
   }
   if (hr == 9) {
    valToWrite = datArray[9];
    return valToWrite;
   }    
  if (hr == 10){
    valToWrite = datArray[10];
    return valToWrite;
  }
   if (hr == 11) {
    valToWrite = datArray[11];
    return valToWrite;
   }
   if (hr == 12) {
    valToWrite = datArray[0];
    return valToWrite;
   }
   if (hr == 13) {
    valToWrite = datArray[1];
    return valToWrite;
   }    
  if (hr == 14){
    valToWrite = datArray[2];
    return valToWrite;
  }
   if (hr == 15) {
    valToWrite = datArray[3];
    return valToWrite;
   }
   if (hr == 16) {
    valToWrite = datArray[4];
    return valToWrite;
   }
   if (hr == 17) {
    valToWrite = datArray[5];
    return valToWrite;
   }    
  if (hr == 18){
    valToWrite = datArray[6];
    return valToWrite;
  }
   if (hr == 19) {
    valToWrite = datArray[7];
    return valToWrite;
   }
   if (hr == 20) {
    valToWrite = datArray[8];
    return valToWrite;
   }
   if (hr == 21) {
    valToWrite = datArray[9];
    return valToWrite;
   }
   if (hr == 22) {
    valToWrite = datArray[10];
    return valToWrite;
   }
   if (hr == 23) {
    valToWrite = datArray[11];
    return valToWrite;
   }        
  }


