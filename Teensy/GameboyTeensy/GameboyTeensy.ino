
#include <Bounce.h>


const int pinHkey=0;
const int pinTurbo=1;
const int pinExit=2;
const int pinMenu=3;
const int pinR=4;
const int pinL=5;
const int pinLoad=6;
const int pinRight=7;
const int pinUp=8;
const int pinLeft=9;
const int pinDown=10;
const int led=11;
const int pinB=12;
const int pinA=13;
const int pinX=14;
const int pinY=15;
const int pinSave=16;
const int pinOther0=17;
const int pinOther2=18;
const int pinOther1=19;
const int pinStart=22;
const int pinSelect=23;

Bounce btnHkey = Bounce(pinHkey, 10);
Bounce btnTurbo = Bounce(pinTurbo, 10);
Bounce btnExit = Bounce(pinExit, 10);
Bounce btnMenu = Bounce(pinMenu, 10);
Bounce btnR = Bounce(pinR, 10);
Bounce btnL = Bounce(pinL, 10);
Bounce btnLoad = Bounce(pinLoad, 10);
Bounce btnRight = Bounce(pinRight, 10);
Bounce btnUp = Bounce(pinUp, 10);
Bounce btnLeft = Bounce(pinLeft, 10);
Bounce btnDown = Bounce(pinDown, 10);
Bounce btnB = Bounce(pinB, 10);
Bounce btnA = Bounce(pinA, 10);
Bounce btnX = Bounce(pinX, 10);
Bounce btnY = Bounce(pinY, 10);
Bounce btnSave = Bounce(pinSave, 10);
Bounce btnOther0 = Bounce(pinOther0, 10);
Bounce btnOther2 = Bounce(pinOther2, 10);
Bounce btnOther1 = Bounce(pinOther1, 10);
Bounce btnStart = Bounce(pinStart, 10);
Bounce btnSelect = Bounce(pinSelect, 10);

const int analogX=1;
const int analogY=0;

const int mouseXMin = 470;
const int mouseXMax = 580;
const int mouseYMin = 390;
const int mouseYMax = 520;

void setup() {
//  Serial.begin(9600);
//  Serial.println("Start mouse tester");
  Joystick.useManualSend(true);
  for (int i=0; i<19; i++) {
    if(i!=11)
      pinMode(i, INPUT_PULLUP);
  }
  pinMode(pinStart, INPUT_PULLUP);
  pinMode(pinSelect, INPUT_PULLUP);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}

void loop() {
  int stickX, stickY;
  char scrollSpeed=1;
  boolean anyChange;
  boolean stateLed=HIGH;
  boolean mouseLeft=0, mouseRight=0, mouseMiddle=0;
  int mode = 0;  //0:Joystick, 1:Mouse, 2:Media
  while(true){
    stickX=analogRead(analogX);
    stickY=analogRead(analogY);

    btnA.update();
    btnB.update();
    btnX.update();
    btnY.update();
    btnRight.update();
    btnDown.update();
    btnLeft.update();
    btnUp.update();
    btnStart.update();
    btnSelect.update();
    btnL.update();
    btnR.update();
    btnSave.update();
    btnLoad.update();
    btnHkey.update();
    btnMenu.update();
    btnExit.update();
    btnTurbo.update();
    btnOther0.update();
    btnOther1.update();
    btnOther2.update();
    

    if (btnSelect.fallingEdge()) {
      mode = (mode+1)%3;
      ////Serial.print("mode=");
      ////Serial.println(mode);
      for (int i = 0; i <= mode; i  += 1) {
          digitalWrite(led, HIGH);
          delay(250);
          digitalWrite(led, LOW);
          delay(250);
      }
    }

    if(mode==0){  //Mode Joystick
      Joystick.X(stickX);
      Joystick.Y(stickY);
      
      Joystick.button(pinHkey, btnHkey.read());
      Joystick.button(pinTurbo, btnTurbo.read());
      Joystick.button(pinExit, btnExit.read());
      Joystick.button(pinMenu, btnMenu.read());
      Joystick.button(pinR, btnR.read());
      Joystick.button(pinL, btnL.read());
      Joystick.button(pinLoad, btnLoad.read());
      Joystick.button(pinRight, btnRight.read());
      Joystick.button(pinUp, btnUp.read());
      Joystick.button(pinLeft, btnLeft.read());
      Joystick.button(pinDown, btnDown.read());
      Joystick.button(pinB, btnB.read());
      Joystick.button(pinA, btnA.read());
      Joystick.button(pinX, btnX.read());
      Joystick.button(pinY, btnY.read());
      Joystick.button(pinSave, btnSave.read());
      Joystick.button(pinOther0, btnOther0.read());
      Joystick.button(pinOther2, btnOther2.read());
      Joystick.button(pinOther1, btnOther1.read());
      Joystick.button(pinStart, btnStart.read());
      Joystick.button(pinSelect, btnSelect.read());

      ////Serial.print("Joytisck:");
      ////Serial.println(btnSelect.read());
      
      Joystick.send_now();
      
    } else if(mode==1){ //Mode mouse
//      Serial.print("StickX=");
//      Serial.print(stickX);
//      Serial.print(",StickY=");
//      Serial.println(stickY);
      ////Serial.print(",A=");
      ////Serial.print(btnA.read());
      ////Serial.print(",B=");
      ////Serial.print(btnB.read());
      ////Serial.print(",X=");
      ////Serial.print(btnX.read());
      //Serial.print(",Y=");
      //Serial.print(btnY.read());
      //Serial.print(",Start=");
      //Serial.print(btnStart.read());
      //Serial.print(",Select=");
      //Serial.print(btnSelect.read());
      //Serial.print(",direction=");
      //Serial.print(btnRight.read());
      //Serial.print(btnDown.read());
      //Serial.print(btnLeft.read());
      //Serial.println(btnUp.read());

  //Move mouse with joystick
      if(stickX<mouseXMin || stickX>mouseXMax || stickY<mouseYMin || stickY>mouseYMax){
        Mouse.move((stickX-(mouseXMax+mouseXMin)/2)/100, (stickY-(mouseYMax+mouseYMin)/2)/100);
        //Serial.print("Move mouse X = ");
        //Serial.print((stickX-(mouseXMax+mouseXMin)/2)/100);
        //Serial.print("Move mouse Y = ");
        //Serial.println((stickY-(mouseYMax+mouseYMin)/2)/100);
      }
      //Move mouse or scroll with arrows
      if(btnY.read() == 1){
        if(btnRight.read()==0){
          Mouse.move(1,0);
        }
        if(btnLeft.read()==0){
          Mouse.move(-1,0);
        }
        if(btnUp.read()==0){
          Mouse.move(0,-1);
        }
        if(btnDown.read()==0){
          Mouse.move(0,1);
        }
      } else {
        if(btnLeft.fallingEdge() && scrollSpeed>1){
          scrollSpeed--;
        }
        if(btnRight.fallingEdge() && scrollSpeed<20){
          scrollSpeed++;
        }
        if(btnUp.fallingEdge()){
          Mouse.scroll(scrollSpeed);
          //Serial.println("Mouse scroll up!!!");
        }
        if(btnDown.fallingEdge()){
          Mouse.scroll(-scrollSpeed);
          //Serial.println("Mouse scroll down!!!");
        }
      }
  
      anyChange=false;
      if (btnA.fallingEdge()) {
        mouseLeft = 1;
        anyChange = 1;
      } else if (btnA.risingEdge()) {
        mouseLeft = 0;
        anyChange = 1;
      }
      if (btnB.fallingEdge()) {
        mouseRight = 1;
        anyChange = 1;
      } else if (btnB.risingEdge()) {
        mouseRight = 0;
        anyChange = 1;
      }
      if (btnX.fallingEdge()) {
        mouseMiddle = 1;
        anyChange = 1;
      } else if (btnX.risingEdge()) {
        mouseMiddle = 0;
        anyChange = 1;
      }
      // if any changes were made, update the Mouse buttons
      if (anyChange) {
        Mouse.set_buttons(mouseLeft, mouseMiddle, mouseRight);
      }
    } //End mode=0, mouse
    else if (mode == 2){  //Mode media
      if (btnA.fallingEdge()) {
        Keyboard.set_media(KEY_MEDIA_PLAY_PAUSE);
        Keyboard.send_now();
        Keyboard.set_media(0);
        Keyboard.send_now();
      }
      if (btnLeft.fallingEdge()) {
        Keyboard.set_media(KEY_MEDIA_PREV_TRACK);
        Keyboard.send_now();
        Keyboard.set_media(0);
        Keyboard.send_now();
      }
      if (btnRight.fallingEdge()) {
        Keyboard.set_media(KEY_MEDIA_NEXT_TRACK);
        Keyboard.send_now();
        Keyboard.set_media(0);
        Keyboard.send_now();
      }
      if (btnDown.fallingEdge()) {
        Keyboard.set_media(KEY_MEDIA_VOLUME_DEC);
        Keyboard.send_now();
        Keyboard.set_media(0);
        Keyboard.send_now();
      }
      if (btnUp.fallingEdge()) {
        Keyboard.set_media(KEY_MEDIA_VOLUME_INC);
        Keyboard.send_now();
        Keyboard.set_media(0);
        Keyboard.send_now();
      }
      if (btnX.fallingEdge()) {
        Keyboard.set_media(KEY_MEDIA_EJECT);
        Keyboard.send_now();
        delay(300);  // Mac OS-X will not recognize a very short eject press
        Keyboard.set_media(0);
        Keyboard.send_now();
      }
    }




    //200 times/s = 5
    delay(5);
  }
}
