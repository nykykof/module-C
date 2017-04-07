#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "externe.h"
#include "rlm_externeHttpRquest.h"
#include "json_parser.h"
#include <json/json.h>
#include <curl/curl.h>

int main()
{
    
    //server informations  
    uservice *s= newService();  
    s->ipaddr = "192.168.0.3/foo";
    s->job = "authentification";
    s->name = "serveur authentification";
    s->port = 8080;

    //data to post  
    requestdata data;
     data.memory= R"anydelim({
  "services": [
    {
      "Is active": true, 
      "Job": "say hello", 
      "Port": 1001, 
      "Url": "192.168.0.3/hello"
    }, 
    {
      "Is active": true, 
      "Job": "Generate the first number", 
      "Port": 1002, 
      "Url": "192.168.0.3/first"
    }, 
    {
      "Is active": false, 
      "Job": "Generate the second number", 
      "Port": 1003, 
      "Url": "192.168.0.3/second"
    }, 
    {
      "Is active": true, 
      "Job": "Generate an operation to do", 
      "Port": 1004, 
      "Url": "192.168.0.3/operator"
    }, 
    {
      "Is active": true, 
      "Job": "compute an operation getting 2 generated numbers and an operator", 
      "Port": 1005, 
      "Url": "192.168.0.3/calculator"
    }
  ]
})anydelim";
    
   //call the post method to do POST request 
    doPost(s,data);

   
    return 0;
}
