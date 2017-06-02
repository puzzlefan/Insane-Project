#include <Wire.h>
 //I2C Adress of the Arduino Slave
#define SLAVE_ADDRESS 0x03
// I2C stuff

//recifed command, defines which register gets returned
int I2Ccommand = 0;
//The Register witch holds the data could nearly be any size you wish but one chapter is only 8 Bit long
int Register[256];//Altest Register beschränkt auf 20 Felder[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Flag for reset to safe position
bool reset = false;

class RotaryEncoder{
  private:
    //physical positions
    int lBOne = 0;//Ligth barrier one
    int lBTwo = 0;//Ligth barrier two

    //calculation values
    int toothCount = 20;//quantity of toothwheel tooth
    int maxSteps = toothCount * 4;//steps per round
    int Steps = 0;//allready taken steps of the round

//Values for velocity calculation
/*    int oldMillis = millis();
    int newMillis = millis();
    int lastSteps = 0;
    int lastRev = 0;*/
    //calculated Values
    int v = 0;//velocity
    int rotation = 0;//actual Angle in degree starts at every rotation at zero
    int revolutions = 0;//counts the revolution, revolutions backwards get substracted

    //bools for counting
    bool lBOneNewStat = false;//turns true if the first sensors actual state was activ
    bool lBTwoNewStat = false;//turns true if the second sensors actual state was activ
    bool lBOneStat = false;//turns true if the first sensors last state was activ
    bool lBTwoStat = false;//turns true if the second sensors last state was activ
    bool dir = false;//indicates the direction
    bool directions[4][2]={{false,true},{false,false},{true,false},{true,true}};//state first Sensor, state second Sensor
    bool * actStat[2]={&lBOneStat,&lBTwoStat};
    int pos = 0;//last combined state
    int maxPos = 3;
    int posi(int newPos);
    void determineDir();
  public:
    RotaryEncoder(int P1, int P2);//sets the encoder up
    void Check();//checks if any counting is necesary
    int getSteps(){return Steps;}//returns the actual count of steps
    int getDegree(){return (360/maxSteps * Steps);}
    int getRevs(){return revolutions;}
    int getV();
    int getMaxSteps(){return maxSteps;}
    void set_Revs(int revs){revolutions=revs;}
};

RotaryEncoder::RotaryEncoder(int P1, int P2){//constructor
  lBOne = P1;//copy pin number to class intern value
  lBTwo = P2;
  pinMode(lBOne,INPUT);//sets the used pins as inputs
  pinMode(lBTwo,INPUT);
  *actStat[0] = digitalRead(lBOne);
  *actStat[1] = digitalRead(lBTwo);
  for(int i = 0;;i++){//Tests all positions and determines through that the actual state
    if(directions[i][0]==*actStat[0] && directions[i][1]==*actStat[1]){
      pos = i;
      Steps = i;
      break;
    }
  }
}
int RotaryEncoder::posi(int newPos){//returns usefull next position
  int reture = newPos;
  if(newPos>maxPos){
    reture=0;
  }
  if(newPos<0){
    reture=maxPos;
  }
  return reture;
}
void RotaryEncoder::determineDir(){
  if(directions[posi(pos+1)][0]==*actStat[0]&&directions[posi(pos+1)][1]==*actStat[1]){
    Steps++;
    pos++;
    if(pos>maxPos){
      pos=0;
    }
    if(maxSteps<=Steps){
      Steps = 0;
      revolutions++;
    }
  }
  if(directions[posi(pos-1)][0]==*actStat[0]&&directions[posi(pos-1)][1]==*actStat[1]){
    Steps--;
    pos--;
    if(pos<0){
      pos=maxPos;
    }
    if(Steps<0){
      Steps = maxSteps;
      revolutions--;
    }
  }

}
void RotaryEncoder::Check(){
    lBOneNewStat=digitalRead(lBOne);
    if(lBOneNewStat!=lBOneStat){
      lBOneStat = lBOneNewStat;
    }
    determineDir();
    lBTwoNewStat=digitalRead(lBTwo);
    if(lBTwoNewStat!=lBTwoStat){
      lBTwoStat = lBTwoNewStat;
  }
  determineDir();
}

RotaryEncoder first(22,23);
RotaryEncoder second(24,25);
RotaryEncoder third(26,27);
RotaryEncoder fourth(28,29);
RotaryEncoder * tire[4]={&first,&second,&third,&fourth};
void setup() {
   //initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication / declare interrupt functions
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  //other

  Register[0] = first.getMaxSteps();
  for (int i = 1; i < 256; i++) {
    Register[i]=0;
  }

  Serial.begin(9600);// Serial Output for debugging
}

void debugOutput(){
    Serial.print(digitalRead(22));
    Serial.print(",");
    Serial.print(digitalRead(23));
    Serial.print(",");
    Serial.print(first.getSteps());
    //Serial.print(",");
    //Serial.print(second.getSteps());
    //Serial.print(",");
    //Serial.print(third.getSteps());
    //Serial.print(",");
    //Serial.println(fourth.getSteps());
    //  for(int i = 0; i<5;i++){
    //    Serial.print(Register[i]);
    //    Serial.print(",");
    // }
      Serial.println();
}

void loop() {
  for(int i = 0;i<4;i++){
    (*tire[i]).Check();
    Register[i*2+2]     =(*tire[i]).getDegree();//writes the Steps to I2C Register 0
    Register[i*2 + 1+2] =(*tire[i]).getRevs();//writes the Steps
  }
  if (reset) {//in the constructor you need to custom fit the start position so that on every fourth step is an opportunety to switch
      for (int i = 0; i < 4; i++) {
          tire[i].set_Revs(1000);
      }
      reset = false;
  }
}
