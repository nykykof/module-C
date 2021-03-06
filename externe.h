#ifndef EXTERNE_H_INCLUDED
#define EXTERNE_H_INCLUDED
#include <curl/curl.h>
#include <stdlib.h>
#include <json/json.h>

typedef struct uservice {
    char *name ;
    char *ipaddr;
    char *job;
    int port;
} uservice;

typedef struct WriteThis {
  const char *readptr;
  long sizeleft;
}WriteThis;
 
typedef struct requestdata {
	CURLcode result;
	char *memory;
    size_t size;
	
} requestdata ;

int getServicePort(uservice *s){

    return s->port;
}

char * getServiceJob(uservice *s){

    return s->job;
}

char * getServiceName(uservice *s){

    return s->name;
}
char * getServiceAddr(uservice *s){

    return s->ipaddr;
}

void affiche_info(uservice *s){

    printf("voici les information du service : \n\n");
    printf("\t - Nom : %s\n",getServiceName(s));
    printf("\t - Job : %s\n",getServiceJob(s));
    printf("\t - Adresse IP : %s\n",getServiceAddr(s));
    printf("\t - Port : %d\n",getServicePort(s));

}
uservice * newService(){
	
	uservice *s =NULL;
    s= (uservice *)malloc(sizeof(uservice));
    
    return s;
}




#endif // EXTERNE_H_INCLUDED
