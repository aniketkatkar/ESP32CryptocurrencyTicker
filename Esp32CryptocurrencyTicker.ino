#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

//Your Domain name with URL path or IP address with path
//Dogecoin API from coingecko
const char* api1 = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=inr&ids=dogecoin";
//Bitcoin API from coingecko
const char* api2 = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=inr&ids=bitcoin";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String getDoge;
float getDogeArr[3];

String getBtc;
float getBtcArr[3];

String doge_coinname="";
double doge_currentprice=0;

String btc_coinname="";
double btc_currentprice=0;

/* Declare LCD object for SPI
 Adafruit_PCD8544(CLK,DIN,D/C,CE,RST); */
Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 4, 15, 2);
int contrastValue = 60; // Default Contrast Value
const int adcPin = 34;
int adcValue = 0;

//get current TS as per IST
const char* ntpServer = "in.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void setup()
{
  Serial.begin(115200);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  /* Initialize the Display*/
  display.begin();

  /* Change the contrast using the following API*/
  display.setContrast(contrastValue);

  /* Clear the buffer */
  display.clearDisplay();
  display.display();
  delay(1000);
}

void loop()
{
  //for timestamp
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  
  /* You can implement your own display logic here*/  
  //Send an HTTP POST request every 6 secs
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      getDoge = httpGETRequest(api1);
      getBtc = httpGETRequest(api2);
      Serial.println(getDoge);
      Serial.println(getBtc);
      JSONVar doge_obj = JSON.parse(getDoge);
      JSONVar btc_obj = JSON.parse(getBtc);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(doge_obj) == "undefined" && JSON.typeof(btc_obj) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(doge_obj);
      Serial.println(btc_obj);
    
      // doge_obj.keys() can be used to get an array of all the keys in the object
      JSONVar doge_keys = doge_obj.keys();
      JSONVar btc_keys = btc_obj.keys();

      //doge
      for (int i = 0; i < doge_keys.length(); i++) {
        JSONVar doge_value = doge_obj[doge_keys[i]];
        Serial.print(doge_keys[i]);
        Serial.print(" = ");
        Serial.println(doge_value);
        getDogeArr[i] = double(doge_value);
      }
      //btc
      for (int i = 0; i < btc_keys.length(); i++) {
        JSONVar btc_value = btc_obj[btc_keys[i]];
        Serial.print(btc_keys[i]);
        Serial.print(" = ");
        Serial.println(btc_value);
        getBtcArr[i] = double(btc_value);
      }

      //doge
      Serial.print("Name = ");
      Serial.println(doge_obj[0]["name"]);
      doge_coinname = doge_obj[0]["name"];
      Serial.print("INR = ");
      Serial.println(doge_obj[0]["current_price"]);
      doge_currentprice=doge_obj[0]["current_price"];
      //btc
      Serial.print("Name = ");
      Serial.println(btc_obj[0]["name"]);
      btc_coinname = btc_obj[0]["name"];
      Serial.print("INR = ");
      Serial.println(btc_obj[0]["current_price"]);
      btc_currentprice=btc_obj[0]["current_price"];
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  /* Now let us display some text */
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println(doge_coinname);
  display.println(doge_currentprice);
  display.println(btc_coinname);
  display.println(btc_currentprice);
  display.println("");
  display.println(&timeinfo, "%H:%M:%S");
  display.display();
//  delay(2000);
  display.clearDisplay();

  
}

String httpGETRequest(const char* api1) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(api1);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
