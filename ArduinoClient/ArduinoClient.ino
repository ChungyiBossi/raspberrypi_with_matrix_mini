#include <MatrixMini.h>
#include <string.h>

 
char bias_data[50];
const char delim[] = ",";
char* bias_data_token_ptr;
float bias_angle[2];
int rc1_angle = 0;
int rc2_angle = 0;
int usb_baud = 9600;
void setup() {
  Mini.begin(); 
  Serial.begin(usb_baud);
  Mini.RC1.set(rc1_angle);
  Mini.RC2.set(rc2_angle);
}

unsigned long messageTimestamp = 0;
void loop() {
  // }
  delay(1000);
  if (Serial.available() > 0)//判斷串口緩存區有沒有數據
  {
    delay(300);
    String string_data = Serial.readString(); // Read String from Serial port
    string_data.trim();
    // https://www.runoob.com/cprogramming/c-function-strcpy.html 
    // Copy string(convert to pointer) to char array. 
    // Be careful of destination array too small.
    strcpy(bias_data, string_data.c_str());      
    Serial.print("Data:"); Serial.print(bias_data); Serial.print("|Len:"); Serial.print(strlen(bias_data)); Serial.println("|");
    if (strlen(bias_data) > 0)
    {    
      // Get first & second element.
      bias_data_token_ptr = strtok(bias_data, delim);  // tokenize char array, using delim, return a pointer point to first token.
      int index = 0;
      while (bias_data_token_ptr != NULL) {
        bias_angle[index % 2] = atof(bias_data_token_ptr);
        Serial.print(index);Serial.print(":");Serial.println(atof(bias_data_token_ptr));
        bias_data_token_ptr = strtok(NULL, delim);
        index++;
      }

      rc1_angle = (rc1_angle + int(bias_angle[0]) + 360) % 180;
      rc2_angle = (rc2_angle + int(bias_angle[1]) + 360) % 180;
      Mini.RC1.set(rc1_angle);
      Mini.RC2.set(rc2_angle);
      Mini.RGB1.setRGB(0,255, 0);
      Mini.RGB2.setRGB(0,0,255);
      Serial.print("dX:"); Serial.print(bias_angle[0]); Serial.print(", dY:"); Serial.println(bias_angle[1]);
      delay(1000);
    } 
    else
    {
      Mini.RGB1.setRGB(255,0,0);
      Mini.RGB2.setRGB(255,0,0);
      delay(300);
    }

  } else {
    Serial.println("No Data In Serial.");
  }

  Serial.flush();

}
