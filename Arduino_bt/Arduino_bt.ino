
#include <SoftwareSerial.h>

#define DEBUG true

int outPin = 53; // outPin is digital pin 53 on arduino mega
// used for debugging
int step1Pin = 2;
int step2Pin = 3;
int step3Pin = 4;
int step4Pin = 5;
int step5Pin = 6;


//int effectNumber = 0;
int effectNumber;


// connect the HC-06 TX to Arduino pin 10 RX;
// connect the HC-06 RX to Arduino pin 11 TX through a voltage divider created
// with three identical resistors;
SoftwareSerial hc05(10,11); // RX | TX

void setup() 
{

// debugging pins
  pinMode(step1Pin, OUTPUT);
//  pinMode(step2Pin, OUTPUT);
//  pinMode(step3Pin, OUTPUT);
//  pinMode(step4Pin, OUTPUT);
//  pinMode(step5Pin, OUTPUT);

// set testing pins to low
  digitalWrite(step1Pin, LOW); 
//  digitalWrite(step2Pin, LOW); 
//  digitalWrite(step3Pin, LOW); 
//  digitalWrite(step4Pin, LOW); 
//  digitalWrite(step5Pin, LOW); 

  // (1) stuff related to ESP8266 and Arduino's connection to host PC; 
  // hardware serial connects to host PC; software serial connects to ESP8266;
  
  Serial.begin(9600);
  hc05.begin(9600); // your esp's baud rate might be different;
  delay(2000);

// send three AT commands to the HC-06 module; the third one is 
  // the one that changes its name to "cristinel"; here, replace
  // “cristinel” with you own unique identifier! 
  sendCommand("AT",1000,DEBUG); 
  sendCommand("AT+VERSION",1000,DEBUG); 
  sendCommand("AT+NAMEtharun",1000,DEBUG);
  
  Serial.println("\r\n HC-05 module ready!");
digitalWrite(step1Pin, HIGH); // indication that HC-05 is ready                                   step 1

  pinMode(outPin, OUTPUT); // set digital pin 53 (outPin) as output
  digitalWrite(outPin, LOW); // set outPin to LOW

  hc05.listen();
}

void loop() 
{
    int effect;
  // receiving data from the master by the slave;
  while (1) 
  {
    if ( hc05.available() > 0) 
    {
//     print_bt_response();
//      effect = hc05.read() - 48;
      char c = hc05.read();
      Serial.print(c);
//      Serial.println(effect);
      if(effect == 6)
      {
        digitalWrite(outPin, HIGH);
      }
      break;
    }
    
  }

//      sendHTTPResponse(connectionId, content);

      // make close command
//      String closeCommand = "AT+CIPCLOSE="; 
//      closeCommand+=connectionId; // append connection id
//      closeCommand+="\r\n";
//
//      sendCommand(closeCommand,1000,DEBUG); // close connection
//    }
//  } 
}

///////////////////////////////////////////////////////////////////////////////
//
// functions related to handling the HC-06 bluetooth module;
//
///////////////////////////////////////////////////////////////////////////////

// Name: sendCommand
// Description: Function used to send AT commands to HC-06.
// Params: 
//    command - the data/command to send; 
//    timeout - the time to wait for a response; 
//    debug - print to Serial window? (true = yes, false = no);
// Returns: The response from the HC-06 bluetooth module (if there is a reponse);
String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
           
    hc05.print(command); // send the read character to the hc-06;
    
    long int time = millis();   
    while ( (time+timeout) > millis())
    {
      while (hc05.available())
      {      
        // hc-06 module has data; so display its output to the serial window; 
        char c = hc05.read(); // read the next character
        response+=c;
      }  
    }
    
    if (debug) {
      Serial.print(response);
      Serial.print("\n");
    }   
    return response;
}

//--------------------------------------------------------------------------------
// Function that reads BT received data and returns 1 if successfull and 0 otherwise
//--------------------------------------------------------------------------------
int print_bt_response()
{
  int response;
  char out, outprev = '$';
  while ( hc05.available() > 0) {
    out = (char)hc05.read();
    Serial.print(out);
    if ((outprev == 'O')&&(out == 'K')) {
      Serial.print("\n");
      response = 1;
      return response;
    }
    outprev = out;
  }
  response = 0;
  return response;
}
