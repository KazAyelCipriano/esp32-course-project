#include "FS.h"
#include "SPIFFS.h"
#define FORMAT_SPIFFS_IF_FAILED true
void setup() {
    Serial.begin(115200);
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    } 
    readFile(SPIFFS, "/readme.txt");
    Serial.println();
    delay(2000);

    writeFile(SPIFFS, "/writetest.txt", "Hello ");
    Serial.println();
    delay(2000);

    readFile(SPIFFS, "/writetest.txt");
    Serial.println();
    delay(2000);

    appendFile(SPIFFS, "/writetest.txt", "World!\r\n");
    Serial.println();
    delay(2000);

    readFile(SPIFFS, "/writetest.txt");
    Serial.println();
    delay(2000);

    Serial.println("Demo finished.");
    
}

void loop() {
  
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- frite failed");
    }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
}
