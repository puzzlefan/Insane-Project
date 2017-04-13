// I2C callback for received data
void receiveData(int byteCount)
{
   //Outputs the complete Input for Debug
   /* while(Wire.available()){
      Serial.println(Wire.available());
      Serial.println(Wire.read());
    }
    Serial.println();
    */

    
    int bufferTwo = -1;
    // read I2C value
    int bufferOne = Wire.read();
    if(Wire.available()>0){  
      bufferTwo = Wire.read();
    }

    //Outputs all the two Buffer for debugging
    /*Serial.println(bufferOne);
    Serial.println(bufferTwo);
    Serial.println();
    */
    
    if(bufferTwo == -1){
      I2Ccommand = bufferOne;  
    }
    else{
     Register[bufferOne]=bufferTwo; 
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
      Wire.write(Register[I2Ccommand]);
      return;
    }
    Wire.write(0);
    //Outputs the complete Register for Debugging
    /*for(int i = 0;i<=19;i++){
      Serial.print(Register[i]);
    }
    Serial.println();
    */
}

