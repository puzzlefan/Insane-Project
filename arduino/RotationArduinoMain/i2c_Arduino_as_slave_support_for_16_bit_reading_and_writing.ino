#include <Wire.h>
// I2C callback for received data
void receiveData(int byteCount)
{
   //Outputs the complete Input for Debug
//   Serial.println("Anfang Input");
//   while(Wire.available()){
      //Serial.println(Wire.available());
//      Serial.println(Wire.read());
//   }
//   Serial.println("Ende Input");



    int bufferTwo = -1;
    int bufferThree = -1;
    // read I2C value
    int bufferOne = Wire.read();
    if(Wire.available()>0){//reads second value if its exists
      bufferTwo = Wire.read();
    }
    if(Wire.available()>0){  //reads the third value if its exists
      bufferThree = Wire.read();
    }
//    Serial.println(bufferOne+" "+bufferTwo+" "+bufferThree);
    //Outputs all the two Buffer for debugging
    /*Serial.println(bufferOne);
    Serial.println(bufferTwo);
    Serial.println(bufferThree);
    Serial.println();
    */

    if(bufferTwo == -1){
      I2Ccommand = bufferOne;
      if (I2Ccommand == 255) {
          resetSteps = true;
      }
    }
    else{
      if(bufferThree == -1){
        Register[bufferOne]=bufferTwo;
      }
      else{
       TwoToOne(bufferTwo,bufferThree, bufferOne);
      }
      I2Ccommand = -1;
    }
}

// I2C callback for sending data
// This is called from the I2C master!
void sendData()
{
    // which command for Arduino?
    if (I2Ccommand != -1)
    {
      OneToTwo(I2Ccommand);
      //Wire.write(Register[I2Ccommand]);
      return;
    }
    //
    //Outputs the complete Register for Debugging
    /*for(int i = 0;i<=19;i++){
      Serial.print(Register[i]);
    }
    Serial.println();
    */
}

void OneToTwo(int Pos){//prints one regster as two 8 bit registers
  int buf = 0;//buf the buffer
  int bufi = Register[Pos];//buffers the value to the register, so that the value did nit get removed by reading it
  Serial.println(bufi);
  int siz = 16;//sizeof(target);
  bool source[16];
  for(int i = siz-1;i>=0;i--){
   buf = bufi-power(2,i);
   if(buf >=0){
      source[15-i]=1;
      bufi =buf;
   }
   else{
      source[15-i]=0;
   }
  }
  buf = 0;
  for(int i = 0;i<8;i++){
    buf = buf + source[15-i]*power(2,i);
  }
  //Serial.println(buf);
  int bufaa = buf;
  //Wire.write(buf);
  buf = 0;
  for(int i = 0;i<8;i++){
    buf = buf + source[7-i]*power(2,i);
  }
  byte bufie [2] = { byte(bufaa), byte(buf) };
  Wire.write(bufie,sizeof(bufie));
  //Serial.println(buf);
  //Serial.println(bufaa);
}

//takes two registers and combines them to one number
void TwoToOne(int Reg1,int Reg2, int Pos){
  bool one[8];
  bool two[8];
  int buf = 0;//buf the buffer
  int siz = 8;//size of one register
  for(int i = siz-1;i>=0;i--){
   buf = Reg1-power(2,i);
   if(buf >=0){
      one[i]=1;
      Reg1=buf;
   }
   else{
      one[i]=0;
   }
  }
  for(int i = siz-1;i>=0;i--){
   buf = Reg2-power(2,i);
   if(buf >=0){
      two[i]=1;
      Reg2=buf;
   }
   else{
      two[i]=0;
   }
  }
  unsigned int buffi = 0;
  for(int i = 0;i<8;i++){
      buffi = buffi+( one[i]*power(2,i));
  }
    for(int i = 0;i<8;i++){
      buffi = buffi+(two[i]*power(2,8+i));
  }
  Register[Pos]=buffi;
}


//takes a base to the power of the exponennt e
unsigned int power(int b, int e){
  if(e == 0){
    return 1;
  }
  else{
    unsigned int reture = 1;
    for(int i = 1;i<= e;i++){
      reture = reture*b;
    }
    //Debug
    //Serial.print("reture");
    //Serial.println(reture);
    //Serial.println(b);
    //Serial.println(e);
    return reture;
  }
}
