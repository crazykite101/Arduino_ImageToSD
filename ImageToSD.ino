
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>

File myFile;
int cnt=0;
int i=0,j=239;
uint8_t r,g,b,c;
int header=54;

void setup() {

  Serial.begin(115200);

  if (!SD.begin(SS1)) {
    return;
  }

  myFile = SD.open("img2Txt.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println("Cazzarola");
    // close the file:
  } 
}

void loop()
{
  while(Serial.available())  
  {
    c = Serial.read();
    if(header>0) { 
      header--; 
      continue; 
    }
    if(cnt==0)
      b = c;
    else if(cnt==1)
      g = c;
    else if(cnt==2) {
      r = c;
      cnt=-1;
      if (myFile) 
      { 
        myFile.println("R: " + String(r) + "  G: " + String(g) +"  B : " + String(b)); 
        myFile.println(String(RGBto565(r,g,b))); 
      }
      i++;
      if(i>=240) {
        i=0; j--;
        if(j<0) {
          j=239; 
          header=54; 
        }
      }
    }
    cnt++;
  }
  myFile.close();
}
