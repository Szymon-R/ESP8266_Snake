#include "WebControler.hpp"



WebControler::WebControler() : server(WiFiServer(80))
{

}

bool WebControler::InitConnection()
{
    DEBUG("Connecting to ");
    Serial.println(WebControler::Config::SSID);
    WiFi.begin(WebControler::Config::SSID, WebControler::Config::PASSWORD);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        DEBUG(".");
    }

    // Print local IP address and start web server
    DEBUG("");
    DEBUG("WiFi connected.");
    DEBUG("IP address: ");

    DEBUG(WiFi.localIP());
    this->server.begin();
}

void WebControler::WaitForClient()
{
    DEBUG("Waiting for client");
    while (!client)
    {
        this->client = server.available();   // Listen for incoming clients
    }
    DEBUG("Client present");
    this->clientConnected = true;
}

Direction WebControler::ParseResponse(const String& response)
{
    if (response.indexOf("GET /right") >= 0) 
    {
        DEBUG("Right clicked");
        this->lastDirection = Direction::RIGHT;
    } 
    else if (response.indexOf("GET /left") >= 0) 
    {
        DEBUG("Left clicked");
        this->lastDirection = Direction::LEFT;
    } 
    else if (response.indexOf("GET /up") >= 0) 
    {
        DEBUG("Up clicked");
        this->lastDirection = Direction::UP;
    } 
    else if (response.indexOf("GET /down") >= 0) 
    {
        DEBUG("Down clicked");
        this->lastDirection = Direction::DOWN;
    }
    else
    {
        DEBUG("Nothing clicked");
    }
    return  this->lastDirection;
}

void WebControler::SendResponse(Direction dir, const String& table)
{
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html><html>");

    client.println("<body><h1>ESP8266 Web Snake</h1>");
    client.println(table);
    client.println("<script>");
    String direction = String(static_cast<uint16_t>(dir));
    client.print("var keyPressed=");
    client.print(direction);
    client.println(";");
    client.println("document.addEventListener('keydown', function(event) {keyPressed = event.keyCode;});");
    client.println("var intervalID = setInterval(function(){");
    client.println("if(keyPressed == 37){ window.location.href = \"/left\";} ");
    client.println("else if(keyPressed == 38) { window.location.href = \"/up\";}");
    client.println("else if(keyPressed == 39) { window.location.href = \"/right\";}");
    client.println("else if(keyPressed == 40) {window.location.href = \"/down\";}");
    client.println("else {}");
    client.println("}, 5000);");

    client.println("</script>");
    client.println("</body></html>");
    
    // The HTTP response ends with another blank line
    client.println();

    // Close the connection
    client.stop();
    this->clientConnected = false;
    DEBUG("Client disconnected.");

}

String WebControler::GetHTTPRequest()
{
    this->timer.RunTimer();

    DEBUG("ServingClient");
    while (this->client.connected() && !this->timer.TimeoutOccured())
    {
        String header = "";
        String currentLine = "";
        
        if (this->client.available()) 
        {             // if there's bytes to read from the client,
            char c = client.read();             // read a byte, then
            header += c;
            if (c == '\n') 
            {                    
                // if the byte is a newline character
                // if the current line is blank, you got two newline characters in a row.
                // that's the end of the client HTTP request, so send a response:
                if (currentLine.length() == 0) 
                {
                    return currentLine;
                }
                else 
                { 
                    // if you got a newline, then clear currentLine
                    currentLine = "";
                }
            } 
            else if (c != '\r') 
            {  
                            // if you got anything else but a carriage return character,
                currentLine += c;      // add it to the end of the currentLine
            }
        }
    }
}