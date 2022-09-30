#include <MatrixMini.h>
#include <string.h>

 
char bias_data[] = "0,0";
const char delim[] = ",";
char* bias_data_token_ptr;
void setup() {
  Mini.begin(); 
  Serial.begin(115200);
  Mini.RC1.set(0);
  Mini.RC2.set(0);
  Mini.RC3.set(0);
  Mini.RC4.set(0);
}

unsigned long messageTimestamp = 0;
void loop() {
  uint64_t now = millis();
  if(now - messageTimestamp > 2000) 
  {
    if (Serial.available())//判斷串口緩存區有沒有數據
    {
      messageTimestamp = now;
      // String string_data = Serial.readString(); // Read String from Serial port
      String string_data = "100,-250"; 
      strcpy(bias_data, string_data.c_str());      // copy string(convert to pointer) to char array. https://blog.csdn.net/xiexu911/article/details/79965330
      bias_data_token_ptr = strtok(bias_data, delim);  // tokenize char array, using delim, return a pointer point to first token.
      while (bias_data_token_ptr != NULL) {
        Serial.println(atof(bias_data_token_ptr));
        bias_data_token_ptr = strtok(NULL, delim);
      }
    }
  }
}
