/* MAIN CONTROL LOOP - INTELLIGENT IRRIGATION CONTROLLER
 * @Author max marischen
 * 2/10/19
 * Main control loop and setup for irrigation controller. 
 * Waits for an array of data with the weather and time to make a watering decision
 * Output is activated relays connected to solenoid valves
 * These outputs are set to high to activate the relay and dispense water to the area of interest. 
 * Helper functions at the bottom include watering and a serial listener to wait for the data array
 */
#include <SoftwareSerial.h>
#define DEBUG false
                                                                //Variable declarations
const int timer = 57;                                           //57 minutes of watering per day, 400 minutes per week, for 2 inches of water per week
                                                                //Myakka, Antigo, Drummer, Houston Black soil types
const double zoneType[4] = {1, 1, 0.916, 1.083};                //Modifying ratio for soil type. Found 
                                                                //values found by saturation rate in mean soil moisture readings from testing rig. 
const int threshhold[5] = {825,860,870,875,880};                //10%,20%,30%,40%,50% threshholds
const int sensorPin[6] = {A0,A1,A2,A3,A4,A5};                   //Moisture sensor pinouts
const int relayPin[6] = {41,42,43,44,45,46};                    //Relay pinouts
int watered[6] = {0,0,0,0,0,0};
int zone[6] = {0,0,0,0,0,0};                                    //Zone type code
int percentage[6] = {0,0,0,0,0,0};                              //Saturation percentage input
int weather = 0, hour = 0;                                      //weather code, time code
bool stringComplete = false;                                    //for serial listener
String inputString = "";                                        
char inputChars[35] = "";                                       //reformatting input string
char * strtokIndx;                                              //index for string separation
int second = 1000;                                              //1000ms in 1 second
int minute = second*60;                                         //60s in 1 minute
int configFlag = 0;

SoftwareSerial hc05(10,11);                                     //RX , TX

void setup() {
  hc05.begin(9600);
  delay(2000);
  Serial.begin(9600);                                           //begin serial on debug port
  inputString.reserve(35);                                      //allow enough space for input string
  for(int x = 0; x<6; x++){                                     //set relay pins as OUTPUTs
    pinMode(relayPin[x],OUTPUT);
  }

  sendCommand("AT",1000,DEBUG);
  sendCommand("AT+VERSION",1000,DEBUG); 
  sendCommand("AT+NAMEtharun",1000,DEBUG);
  Serial.println("HC-05 module ready");
  hc05.listen();

//fint arr[8] = {104,13,15,14,00,00,00,00};                        //hard-coded input array for debug
//inputString = "[104,13,15,14,00,00,00,00]";
Serial.print("Setup Finished\r\n");                   

}

void loop() {

if(stringComplete){                                             //If a string is received by the listener
  Serial.println("String Received");
  //format string received to array.
 // inputString.remove(inputString.length()-1);                 //crop the brackets of the array string
  inputString.remove(0,1);                 
  inputString.toCharArray(inputChars,inputString.length());     //convert input string to character array 
  
  strtokIndx = strtok(inputChars,",");                          //find weather code
  weather = atoi(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");                               //find hour value
  hour = atoi(strtokIndx);
  
  for(int i = 0;i<5;i++){                                       //find zone configurations
    strtokIndx=strtok(NULL,",");                                //separate zone config from saturation percentage
    percentage[i] = (atoi(strtokIndx)%10);
    Serial.println("Percentage, Zone type");
    Serial.println(percentage[i]);
    zone[i]=((atoi(strtokIndx))/10)%10;
    Serial.println(zone[i]);
  }
  strtokIndx=strtok(NULL,"]");                                  //last value has a different delimiter from a comma
  zone[5]=atoi(strtokIndx);                                 

  Serial.println("Configuration finished");
  for(int i =0;i<sizeof(inputChars);i++){                       //DEBUG print input character array
    Serial.println(inputChars[i]);
  }
  Serial.println(weather);
  Serial.println(((weather>=200 && weather<400) ||
                  (weather>=500 && weather<600)));              
                                                                //Main watering loop
  if(!((weather>=200 && weather<400) || 
  (weather>=500 && weather<600))){                              //weather codes for thunderstorm, rain, and drizzle
    Serial.println("Weather check passed");
    if((hour>=7) && (hour <=21)){                               //check time of day
      Serial.println("Time check passed");
      for(int i = 0;i<6;i++){                                   //for each zone
        if(zone[i]!=0){                                         //check if zone is disabled
          Serial.println("Zone check passed");
          //sensors                                             //if not, enter watering decision loop
          int sensorValue = analogRead(sensorPin[i]);
          Serial.print("Sensor Val = ");
          Serial.print(sensorValue);
          if(sensorValue<threshhold[percentage[i]-1]){          //check moisture sensor level
            Serial.println("Moisture Sensor check passed");
            Serial.println("WATERING"); 
            if(!watered[i]){
              watered[i]=1;
              water(i);                                         //water zone i
            }
          } 
        }
      }
    }
    else{
      for(int i=0;i<6;i++){
        watered[i]=0;
      }
    }
  }
  else{
    for(int i =0;i<6;i++){
      watered[i]=1;
    }  
  }
  inputString="";                                               //Reset input string
  stringComplete=false;                                         //Reset flag
  }
}

//Serial Listener
void serialEvent(){
  Serial.println("Serial event");
  while(hc05.available()){
    char inChar = (char)hc05.read();
    inputString+=inChar;
    if(inChar =='\n'){                                          //Newline defines the end of the string
      stringComplete = true;
    }
  }
}

//Watering function. Takes zone as input.
void water(int x){
  digitalWrite(relayPin[x],HIGH);                               //Open the valve
  int totalDelay = timer*minute*zoneType[zone[x]];              //57 minutes * zone type ratio modifier
  delay(totalDelay);                                            //Wait for delay time
  digitalWrite(relayPin[x],LOW);                                //Close the valve
}




                                                                //sendCommand - used to send AT commands to the hc-06
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
