#ifndef EXTERNE_HTTPREQUEST_INCLUDED
#define EXTERNE_HTTPREQUEST_INCLUDED
#include "externe.h"


static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
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

requestdata  doGet(uservice *service){
 
  requestdata data;
  CURL *curl_handle;
  data.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
  data.size = 0;    /* no data at this point */ 
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, getServiceAddr(service));
  curl_easy_setopt(curl_handle, CURLOPT_PORT, getServicePort(service));
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&data);
 
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
  
};


int doPost(uservice *service, requestdata data){
	
	struct curl_slist *headers=NULL;
	CURL *curl;
    CURLcode res;
    
	headers=curl_slist_append(headers, "Accept: application/json");
	headers=curl_slist_append(headers, "Content-Type: application/json");
	headers=curl_slist_append(headers, "charsets: utf-8");

 
  /* In windows, this will init the winsock stuff */
  res = curl_global_init(CURL_GLOBAL_DEFAULT);
  /* Check for errors */
  if(res != CURLE_OK) {
	fprintf(stderr, "curl_global_init() failed: %s\n",
			curl_easy_strerror(res));
	return 1;
  }

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. */
    curl_easy_setopt(curl, CURLOPT_URL, getServiceAddr(service));
	curl_easy_setopt(curl, CURLOPT_PORT, getServicePort(service));

    /* Now specify we want to POST data */
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    
    /* get verbose debug output please */
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);    
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.memory);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      return 1;
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
	return 0 ;
};	
	
#endif // EXTERNE_HTTPREQUEST_INCLUDED
