/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library

#include <ESP8266WiFi.h>
#include "Snake.hpp"

#include "Table.hpp"
#include "Controler.hpp"
#include "WebControler.hpp"
#include "Utils.hpp"




// Variable to store the HTTP request
String header; 

static constexpr uint32_t rowsNumber = 20;
static constexpr uint32_t colsNumber = 20;
static constexpr uint32_t cellSize = 20;

Snake<rowsNumber * colsNumber> snake(std::make_pair(0U, 0U));
Table<rowsNumber, colsNumber> table(cellSize);
Controler<rowsNumber * colsNumber, rowsNumber, colsNumber> controler(snake, table);
WebControler webControler;

void setup() 
{
  #ifdef DEBUG_BUILD
    Serial.begin(115200);
  #endif
  controler.Init();
  webControler.InitConnection();
}


void loop()
{
  webControler.WaitForClient();
  String request = webControler.GetHTTPRequest();
  Direction dir = webControler.ParseResponse(request);
  webControler.SendResponse(dir, table.Parse());

}