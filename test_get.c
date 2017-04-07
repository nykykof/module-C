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
    s->ipaddr = "192.168.0.3/hello";
    s->job = "authentification";
    s->name = "serveur authentification";
    s->port = 8080;
    //affiche_info(s);
    
    requestdata data;
    //doing GET request on the described server
    data = doGet(s);
    //convert the received data from string to json object
    json_object * jobj = json_tokener_parse(data.memory);
    //free the busied memory
    free (data.memory);
    //display the json data in a particular own format
	affiche_object(jobj);
	//destroy tje json variable
	json_object_put(jobj);
    return 0;
}
