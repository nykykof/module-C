#ifndef EXTERNE_HTTPREQUEST_INCLUDED
#define EXTERNE_HTTPREQUEST_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
#include "externe.h"



static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  requestdata *mem = (requestdata *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

requestdata * makeRequest(CURL *curl_handle, requestdata *data, uservice *service){
 
  data.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
  data.size = 0;    /* no data at this point */ 
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, service.getServiceAddr());
  curl_easy_setopt(curl_handle, CURLOPT_PORT, service.getServicePort());
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)data);
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */ 
  data.result = curl_easy_perform(curl_handle);
 
  
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  /* we're done with libcurl, so clean it up */ 
  curl_global_cleanup();
 
  return data;
  
}
	
	
	
#endif // EXTERNE_HTTPREQUEST_INCLUDED
