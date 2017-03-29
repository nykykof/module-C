#include <stdio.h>
#include <stdlib.h>
#include "externe.h"



int main()
{
    
   uservice *s= newService();
    
    s->ipaddr = "161.105.178.178";
    s->job = "authentification";
    s->name = "serveur authentification";
    s->port = 1010;

    affiche_info(s);
    return 0;
}
