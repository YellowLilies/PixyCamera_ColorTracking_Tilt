#include <Pixy2.h>
#include<PIDLoop.h>

Pixy2 pixy;
PIDLoop panLoop(400, 0, 400, true);
PIDLoop tiltLoop(500, 0, 500, true);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.print("Starting...\n");
pixy.init();
pixy.changeProg("color_connected_components");
}

void loop() {
  // put your main code here, to run repeatedly:
 int numberBlock;
 char buf[64];
 int32_t panOffset; 
 int16_t m_angle;
 int k = 0;
 int servoarray;
 pixy.ccc.getBlocks();
 if (pixy.ccc.numBlocks){
  Serial.print("Detected ");
  numberBlock++;
  Serial.println(pixy.ccc.numBlocks);
  for (numberBlock=0; numberBlock<pixy.ccc.numBlocks; numberBlock++){
    Serial.print(" block ");
    Serial.print(numberBlock);
    Serial.print(": "); 
     Serial.print("Angle from Pixy:");
     Serial.print(pixy.ccc.blocks[0].m_angle);
       k++;
    //Serial.print(pixy.ccc.blocks[numberBlock].m_angle);
    Serial.print(" ");
    pixy.ccc.blocks[numberBlock].print();
  if (numberBlock % 60 == 0)
    Serial.println(numberBlock);
    panOffset = (int32_t)pixy.frameWidth / 2 - (int32_t)pixy.ccc.blocks[0].m_x;
    panLoop.update(panOffset);
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);

  /*if (0) 
    //sprintf(buf, "%ld %ld %ld %ld", rotateLoop.m_command, translateLoop.m_command, left, right);
    Serial.println(buf);
   //endif*/
  }
 }else{
    panLoop.reset();
     pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  }
  }
