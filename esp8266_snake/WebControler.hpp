#ifndef _WEB_CONTROLER_HPP
#define _WEB_CONTROLER_HPP

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <cstdio>

#include "Utils.hpp"
#include "Snake.hpp"
#include "Timer.hpp"

class WebControler
{
    public:
        WebControler();
        bool InitConnection();
        struct Config
        {
            static constexpr const char* SSID = "SSID";
            static constexpr const char* PASSWORD = "PASSWORD";
        };
        void WaitForClient();
        String GetHTTPRequest();
        Direction ParseResponse(const String& response);
        void SendResponse(Direction dir, const String& table);
        
    private:
    
        Timer timer;
        WiFiServer server;
        WiFiClient client;
        bool clientConnected = false;

        Direction lastDirection = Direction::RIGHT;
};


#endif