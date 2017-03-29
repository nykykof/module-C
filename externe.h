#ifndef EXTERNE_H_INCLUDED
#define EXTERNE_H_INCLUDED


typedef struct service {
    char *name;
    char *ipaddr;
    char * job;
    int port;
} service;

int getServicePort(service *s){

    return s->port;
}

char * getServiceJob(service *s){

    return s->job;
}

char * getServiceName(service *s){

    return s->name;
}
char * getServiceAddr(service *s){

    return s->ipaddr;
}

void affiche_info(service *s){

    printf("voici les information du service : \n\n");
    printf("\t - Nom : %s\n",getServiceName(s));
    printf("\t - Job : %s\n",getServiceJob(s));
    printf("\t - Adresse IP : %s\n",getServiceAddr(s));
    printf("\t - Port : %d\n",getServicePort(s));

}
service * newService(){
	
	service *s =NULL;
    s= (service *)malloc(sizeof(service));
    
    return s;
}
#endif // EXTERNE_H_INCLUDED
