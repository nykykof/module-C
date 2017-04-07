#ifndef JSON_PARSER_INCLUDED
#define JSON_PARSER_INCLUDED
#include <json/json.h>
#define type_int 0
#define type_bool 1
#define type_char 2
#define type_array 3

struct json_object * fill_json_object_object(char *key, const char *value, int value_type, struct json_object *to_be_filled){
	struct json_object *tmp;
	//res = json_object_new_object();	
	switch(value_type){
		
		case type_int:
			tmp = json_object_new_int(*value);
			break;
		case type_bool:
			tmp = json_object_new_boolean(*value);
			break;
		case type_char:
			tmp = json_object_new_string(value);
			break;
	}	
	json_object_object_add(to_be_filled, key, tmp);	
	return to_be_filled;
}

void affiche_simple_object(struct json_object *jobj){
	int i=1;
	json_object_object_foreach(jobj, key, val){
		printf("\n\t\t*** element %d *** \n",i);
		printf("\n\t\t---\n");
		printf("\t\t clé : %s\n",key);
		printf("\t\t valeur : %s",json_object_to_json_string(val));
		printf("\n\t\t---\n");
		printf("\n\t\t*** Fin element %d ***\n",i);
		i++;
	};
	
}


void affiche_array(struct json_object *array,char *cle){
	struct json_object * val;
	
	printf("\n***Affichage de %s de type array***\n",cle);
	for(int i=0;i< json_object_array_length(array);i++){
		//val_type = json_object_get_type(array[i]);
		val = json_object_array_get_idx(array, i);
		if(json_object_get_type(val) == json_type_object){
			printf("\n\t*** Affichage sous objet %d *** \n",i);
			affiche_simple_object(val);
			printf("\n\t*** Fin affichage sous objet %d ***\n",i);
			
		}else{
			printf("array[%d] = %s\n", i, json_object_to_json_string(val));
		}
	};
	printf("\n***Fin affichage de %s de type array***\n",cle);
}


void affiche_object(struct json_object *jobj){
	json_object_object_foreach(jobj, key, val){
		
		if(json_object_get_type(val)==json_type_object){
			affiche_simple_object(val);
		};
		if(json_object_get_type(val)==json_type_array){
			affiche_array(val,key);
		}
		else{
			printf("\n---\n");
			printf("clé : %s\n",key);
			printf("valeur : %s",json_object_to_json_string(val));
			printf("\n--- \n");
		
		};
	};
 }
 
 
#endif 
