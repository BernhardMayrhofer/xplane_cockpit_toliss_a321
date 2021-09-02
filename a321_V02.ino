#include <arduino.h>
#include <Encoder.h>

//Init

//// Define Columns 0-8

int col00 = 22;
int col01 = 21;
int col02 = 20;
int col03 = 19;
int col04 = 18;
int col05 = 17;
int col06 = 16;
int col07 = 15;
int col08 = 14;

//// Define rows 0-4

int row00 = 4;
int row01 = 3;
int row02 = 2;
int row03 = 1;
int row04 = 0;

int arraycol;
int arrayrow;

int btnState[9][5] = {{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

int encBaroB = 10;
int baseBaro = 9;
int encBaroA = 8;
int encBrightB = 7;
int baseBright = 6;
int encBrightA = 5;

Encoder knobBaro(encBaroB, encBaroA);
Encoder knobBright(encBrightB, encBrightA);

//Button Array
FlightSimCommand cmdRef[9][5][4]; // = {NULL};
FlightSimInteger intRef[9][5][4]; // = {NULL};
FlightSimFloat floatEncBaro[2];
FlightSimFloat floatEncBright[8];

void setup() {

  //Setup XPlane Commands Toliss A321 1.3 CEO
  
  cmdRef[0][2][1] = XPlaneRef("toliss_airbus/lightcommands/BeaconOn");
  cmdRef[0][2][0] = XPlaneRef("toliss_airbus/lightcommands/BeaconOff");
  cmdRef[1][2][1] = XPlaneRef("toliss_airbus/lightcommands/StrobeLightUp");
  cmdRef[1][2][0] = XPlaneRef("toliss_airbus/lightcommands/StrobeLightDown");
  cmdRef[2][2][1] = XPlaneRef("toliss_airbus/lightcommands/WingLightOn");
  cmdRef[2][2][0] = XPlaneRef("toliss_airbus/lightcommands/WingLightOff");
  cmdRef[3][1][1] = XPlaneRef("toliss_airbus/lightcommands/NavLightUp");
  cmdRef[3][1][0] = XPlaneRef("toliss_airbus/lightcommands/NavLightDown");
  cmdRef[3][0][1] = XPlaneRef("toliss_airbus/lightcommands/NavLightDown");
  cmdRef[3][0][0] = XPlaneRef("toliss_airbus/lightcommands/NavLightUp");
  cmdRef[3][2][1] = XPlaneRef("toliss_airbus/lightcommands/TurnoffLightOn");
  cmdRef[3][2][0] = XPlaneRef("toliss_airbus/lightcommands/TurnoffLightOff");
  cmdRef[1][1][1] = XPlaneRef("toliss_airbus/lightcommands/LLandLightUp");
  cmdRef[1][1][0] = XPlaneRef("toliss_airbus/lightcommands/LLandLightDown");
  cmdRef[1][0][1] = XPlaneRef("toliss_airbus/lightcommands/LLandLightDown");
  cmdRef[1][0][0] = XPlaneRef("toliss_airbus/lightcommands/LLandLightUp");
  cmdRef[0][1][1] = XPlaneRef("toliss_airbus/lightcommands/RLandLightUp");
  cmdRef[0][1][0] = XPlaneRef("toliss_airbus/lightcommands/RLandLightDown");
  cmdRef[0][0][1] = XPlaneRef("toliss_airbus/lightcommands/RLandLightDown");
  cmdRef[0][0][0] = XPlaneRef("toliss_airbus/lightcommands/RLandLightUp");
  cmdRef[2][1][1] = XPlaneRef("toliss_airbus/lightcommands/NoseLightUp");
  cmdRef[2][1][0] = XPlaneRef("toliss_airbus/lightcommands/NoseLightDown");
  cmdRef[2][0][1] = XPlaneRef("toliss_airbus/lightcommands/NoseLightDown");
  cmdRef[2][0][0] = XPlaneRef("toliss_airbus/lightcommands/NoseLightUp");
  
  cmdRef[2][4][1] = XPlaneRef("AirbusFBW/CaptChronoButton");
  cmdRef[1][4][1] = XPlaneRef("sim/annunciator/clear_master_caution");
  cmdRef[0][4][1] = XPlaneRef("sim/annunciator/clear_master_warning");
  
  cmdRef[5][3][1] = XPlaneRef("AirbusFBW/LOCbutton");
  cmdRef[6][3][1] = XPlaneRef("AirbusFBW/APPRbutton");

  //Setup XPlane Refs Toliss A321 1.3 CEO
  
  intRef[4][2][1] = XPlaneRef("ckpt/oh/seatbelts/anim");
  intRef[4][2][0] = XPlaneRef("ckpt/oh/seatbelts/anim");
  
  intRef[5][2][1] = XPlaneRef("ckpt/oh/1/radioSwitch/anim");
  intRef[5][2][0] = XPlaneRef("ckpt/oh/1/radioSwitch/anim");
  intRef[5][2][3] = XPlaneRef("AirbusFBW/RMP1Switch");
  intRef[5][2][2] = XPlaneRef("AirbusFBW/RMP1Switch");
  intRef[6][2][1] = XPlaneRef("ckpt/oh/2/radioSwitch/anim");
  intRef[6][2][0] = XPlaneRef("ckpt/oh/2/radioSwitch/anim");
  intRef[6][2][3] = XPlaneRef("AirbusFBW/RMP2Switch");
  intRef[6][2][2] = XPlaneRef("AirbusFBW/RMP2Switch");
  
  intRef[6][4][1] = XPlaneRef("AirbusFBW/BaroUnitCapt");
  intRef[6][4][0] = XPlaneRef("AirbusFBW/BaroUnitCapt");
  intRef[6][4][3] = XPlaneRef("AirbusFBW/BaroUnitFO");
  intRef[6][4][2] = XPlaneRef("AirbusFBW/BaroUnitFO");
  intRef[5][4][1] = XPlaneRef("AirbusFBW/BaroStdCapt");
  intRef[5][4][0] = XPlaneRef("AirbusFBW/BaroStdCapt");
  intRef[5][4][3] = XPlaneRef("AirbusFBW/BaroStdFO");
  intRef[5][4][2] = XPlaneRef("AirbusFBW/BaroStdFO");
  
  intRef[0][3][1] = XPlaneRef("AirbusFBW/NDShowCSTRCapt");
  intRef[0][3][0] = XPlaneRef("AirbusFBW/NDShowCSTRCapt");
  intRef[1][3][1] = XPlaneRef("AirbusFBW/NDShowWPTCapt");
  intRef[1][3][0] = XPlaneRef("AirbusFBW/NDShowWPTCapt");
  intRef[2][3][1] = XPlaneRef("AirbusFBW/NDShowVORDCapt");
  intRef[2][3][0] = XPlaneRef("AirbusFBW/NDShowVORDCapt");
  intRef[3][3][1] = XPlaneRef("AirbusFBW/NDShowNDBCapt");
  intRef[3][3][0] = XPlaneRef("AirbusFBW/NDShowNDBCapt");
  intRef[4][3][1] = XPlaneRef("AirbusFBW/NDShowARPTCapt");
  intRef[4][3][0] = XPlaneRef("AirbusFBW/NDShowARPTCapt");
  
  intRef[3][4][1] = XPlaneRef("AirbusFBW/FD1Engage");
  intRef[3][4][0] = XPlaneRef("AirbusFBW/FD1Engage");
  intRef[4][4][1] = XPlaneRef("AirbusFBW/ILSonCapt");
  intRef[4][4][0] = XPlaneRef("AirbusFBW/ILSonCapt"); 

  intRef[7][4][1] = XPlaneRef("AirbusFBW/NDmodeCapt");
  intRef[7][4][0] = XPlaneRef("AirbusFBW/NDmodeCapt");
  intRef[7][3][1] = XPlaneRef("AirbusFBW/NDmodeCapt");
  intRef[7][2][1] = XPlaneRef("AirbusFBW/NDmodeCapt");
  intRef[7][1][1] = XPlaneRef("AirbusFBW/NDmodeCapt");

  intRef[8][4][1] = XPlaneRef("AirbusFBW/NDrangeCapt");
  intRef[8][4][0] = XPlaneRef("AirbusFBW/NDrangeCapt");
  intRef[8][3][1] = XPlaneRef("AirbusFBW/NDrangeCapt");
  intRef[8][2][1] = XPlaneRef("AirbusFBW/NDrangeCapt");
  intRef[8][1][1] = XPlaneRef("AirbusFBW/NDrangeCapt");
  intRef[8][0][1] = XPlaneRef("AirbusFBW/NDrangeCapt");

  // Setup Rotaray Refs
  floatEncBaro[1] = XPlaneRef("sim/cockpit/misc/barometer_setting");
  floatEncBaro[0] = XPlaneRef("sim/cockpit/misc/barometer_setting2");
    
  floatEncBright[0] = XPlaneRef("AirbusFBW/DUBrightness[0]");
  floatEncBright[1] = XPlaneRef("AirbusFBW/DUBrightness[1]");
  floatEncBright[2] = XPlaneRef("AirbusFBW/DUBrightness[2]");
  floatEncBright[3] = XPlaneRef("AirbusFBW/DUBrightness[3]");
  floatEncBright[4] = XPlaneRef("AirbusFBW/DUBrightness[4]");
  floatEncBright[5] = XPlaneRef("AirbusFBW/DUBrightness[5]");
  floatEncBright[6] = XPlaneRef("AirbusFBW/DUBrightness[6]");
  floatEncBright[7] = XPlaneRef("AirbusFBW/DUBrightness[7]");
  
  //Setup matrix columns pin 13 to 5
  for (int col = col00; col >= col08; col--) {
    pinMode(col, OUTPUT);
    digitalWrite(col, LOW);    
  }
  
  //Setup matrix rows pin 4 to 0
  for (int row = row00; row >= row04; row--) {
    pinMode(row, INPUT_PULLDOWN);
    //digitalWrite(row, LOW);    
  }

  //Setup Encoders
  pinMode(baseBaro, OUTPUT);
  digitalWrite(baseBaro, HIGH);
  pinMode (encBaroA, INPUT_PULLDOWN);
  pinMode (encBaroB, INPUT_PULLDOWN);

  pinMode(baseBright, OUTPUT);
  digitalWrite(baseBright, HIGH);
  pinMode (encBrightA, INPUT_PULLDOWN);
  pinMode (encBrightB, INPUT_PULLDOWN);

  //Setup internal LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

long positionBaro = -999;
long positionBright = -999;

void loop() {

  FlightSim.update();

  //Update Encoders
  
  long newBaro, newBright;
  
  newBaro = knobBaro.read();
  newBright = knobBright.read();
  
  delay(2);
  
  if (newBaro != positionBaro) {
    
    if (newBaro > positionBaro) {
      floatEncBaro[1] = floatEncBaro[1] + 0.01;
      floatEncBaro[0] = floatEncBaro[0] + 0.01;
    } else {
      floatEncBaro[1] = floatEncBaro[1] - 0.01;
      floatEncBaro[0] = floatEncBaro[0] - 0.01;  
    }

    Serial.println(floatEncBaro[1]);

    positionBaro = newBaro;
  }

  if (newBright != positionBright) {
    
    if (newBright > positionBright) {
      for (int brtCt = 0; brtCt <= 7; brtCt++) {
         floatEncBright[brtCt] = floatEncBright[brtCt] + 0.1;
      }
    } else {
      for (int brtCt = 0; brtCt <= 7; brtCt++) {
         floatEncBright[brtCt] = floatEncBright[brtCt] - 0.1;
      }
    }

    positionBright = newBright;
  }
  
  //Update Button States
  
  for (int col = col00; col >= col08; col--) { //col00 col08
  
      delay(1); //debouncing
  
      digitalWrite(col, HIGH);
  
      for (int row = row00; row >= row04; row--) {
  
        delay(1); //debouncing
  
        arraycol = col - col08;// + 1;
        arrayrow = row - row04;// + 1;
  
        if (digitalRead(row) == HIGH) {
          
          if (btnState[arraycol][arrayrow] == 0) {
  
            digitalWrite(LED_BUILTIN, HIGH);
            
            btnState[arraycol][arrayrow] = 1;

            if(arraycol == 4 && arrayrow == 2) { //Seatbeld Switch
              intRef[arraycol][arrayrow][1] = 1;
            } else if ((arraycol == 5 || arraycol == 6) && arrayrow == 2) { //Radio Switches
              intRef[arraycol][arrayrow][1] = 1;
              intRef[arraycol][arrayrow][3] = 1;
            } else if (arraycol == 1 && arrayrow == 2) { //Strobe
              cmdRef[arraycol][arrayrow][1] = 1;
              cmdRef[arraycol][arrayrow][1] = 1;
            } else if (arraycol == 6 && arrayrow == 4) { //Baro Units
              intRef[arraycol][arrayrow][1] = 1;
              intRef[arraycol][arrayrow][3] = 1;
            } else if (arraycol == 5 && arrayrow == 4) { //Baro STD
              if (intRef[arraycol][arrayrow][1] == 0) {
                intRef[arraycol][arrayrow][1] = 1;
                intRef[arraycol][arrayrow][3] = 1; 
              } else {
                intRef[arraycol][arrayrow][1] = 0;
                intRef[arraycol][arrayrow][3] = 0;
              }
            } else if ((arraycol >= 0 && arraycol <= 4) && arrayrow == 3) { //CSTR, WPT, VORD, NBD, ARPT
              if (intRef[arraycol][arrayrow][1] == 0) {
                intRef[arraycol][arrayrow][1] = 1;
              } else {
                intRef[arraycol][arrayrow][1] = 0;
              }
            } else if ((arraycol == 3 || arraycol == 4) && arrayrow == 4) { //FD, ILS
              if (intRef[arraycol][arrayrow][1] == 0) {
                intRef[arraycol][arrayrow][1] = 1;
              } else {
                intRef[arraycol][arrayrow][1] = 0;
              }
            } else if (arraycol == 7 && arrayrow == 4) { //ND VOR
              intRef[arraycol][arrayrow][1] = 1;
            } else if (arraycol == 7 && arrayrow == 3) { //ND NAV
              intRef[arraycol][arrayrow][1] = 2;
            } else if (arraycol == 7 && arrayrow == 2) { //ND ARC
              intRef[arraycol][arrayrow][1] = 3;
            } else if (arraycol == 7 && arrayrow == 1) { //ND PLAN
              intRef[arraycol][arrayrow][1] = 4;
            } else if (arraycol == 8 && arrayrow == 4) { //ND 20
              intRef[arraycol][arrayrow][1] = 1;
            } else if (arraycol == 8 && arrayrow == 3) { //ND 40
              intRef[arraycol][arrayrow][1] = 2;
            } else if (arraycol == 8 && arrayrow == 2) { //ND 80
              intRef[arraycol][arrayrow][1] = 3;
            } else if (arraycol == 8 && arrayrow == 1) { //ND 160
              intRef[arraycol][arrayrow][1] = 4;
            } else if (arraycol == 8 && arrayrow == 0) { //ND 320
              intRef[arraycol][arrayrow][1] = 5;
            } else { //All other Switches
              cmdRef[arraycol][arrayrow][1] = 1; 
            }
  
            Serial.print("C");
            Serial.print(arraycol);
            Serial.print("R");
            Serial.print(arrayrow);
            Serial.println("S1");
            
          }
          
        } else {
  
          digitalWrite(LED_BUILTIN, LOW);
          
          if (btnState[arraycol][arrayrow] == 1) {
            
            btnState[arraycol][arrayrow] = 0;

            if(arraycol == 4 && arrayrow == 2) { //Seatbeld Switch
              intRef[arraycol][arrayrow][0] = 0;
            } else if (arraycol == 1 && arrayrow == 2) { //Strobe
              cmdRef[arraycol][arrayrow][0] = 1;
              cmdRef[arraycol][arrayrow][0] = 1;
            } else if ((arraycol == 5 || arraycol == 6) && arrayrow == 2) { //Radio Switches
              intRef[arraycol][arrayrow][0] = 0;
              intRef[arraycol][arrayrow][2] = 0;
            } else if (arraycol == 6 && arrayrow == 4) { //Baro Units
              intRef[arraycol][arrayrow][0] = 0;
              intRef[arraycol][arrayrow][2] = 0;
            } else if (arraycol == 7 && arrayrow == 4 && intRef[arraycol][arrayrow][1] == 1) { //ND LS
              intRef[arraycol][arrayrow][1] = 0;
            } else if (arraycol == 8 && arrayrow == 4 && intRef[arraycol][arrayrow][1] == 1) { //ND 10
              intRef[arraycol][arrayrow][1] = 0;
            } else { //All other Switches
              cmdRef[arraycol][arrayrow][0] = 1; 
            }
  
            Serial.print("C");
            Serial.print(arraycol);
            Serial.print("R");
            Serial.print(arrayrow);
            Serial.println("S0");
            
          }      
        }
      }
  
      digitalWrite(col, LOW);
      
  } 
}
