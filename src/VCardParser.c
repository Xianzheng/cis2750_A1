#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "LinkedListAPI.h"
#include "VCardParser.h"
typedef struct val {
	char value[200];
}Value;

typedef struct line {
	char value[200];
}Line;

typedef struct St {
	char *name;
	char *value;
}Store;
int getFileLength(char* fileName);
int IfContainSemi(char *s);
int getPosition(char *s);
int getPosition1(char *s);
int getPosition2(char *s);
int checkifNumber(char *s);
void deleteTmp(Store *store[], char *Line[],int fileLength);
int findKeyWord(char *s);
char * p(char *s);
int ifCha(char *s);

void deleteProperty(void* toBeDeleted){
    Property* tmpProperty;

	if (toBeDeleted == NULL){
		return;
	}

	tmpProperty = (Property*)toBeDeleted;

	free(tmpProperty->name);
	free(tmpProperty->group);
	freeList(tmpProperty->parameters);
	freeList(tmpProperty->values);
	free(tmpProperty);
}
int compareProperties(const void* first,const void* second){
    Property* tmpProperty1;
	Property* tmpProperty2;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpProperty1 = (Property*)first;
	tmpProperty2 = (Property*)second;

	return strcmp((char*)tmpProperty1->name, (char*)tmpProperty2->name);
}
char* printProperty(void* toBePrinted){
    char* tmpStr;
	Property* tmpProperty;
	//int len;

	if (toBePrinted == NULL){
		return NULL;
	}

	tmpProperty = (Property*)toBePrinted;


	//len = strlen(tmpProperty->name)+strlen(tmpProperty->group)+28;
	tmpStr = (char*)malloc(sizeof(char)*10000);

	char * add;
	sprintf(tmpStr, "Property name:%s\nProperty group:%s ",tmpProperty->name,tmpProperty->group);
	add=toString(tmpProperty->parameters);
	strcat(tmpStr,add);
	free(add);
	add=toString(tmpProperty->values);
    strcat(tmpStr,add);
	strcat(tmpStr,"\n");
	free(add);
	//sprintf(tmpStr, "%s %s %s %s",tmpProperty->name,tmpProperty->group, toString(tmpProperty->parameters),toString(tmpProperty->values));
	return tmpStr;
}

void deleteDate(void* toBeDeleted){
    DateTime* tmpDateTime;

	if (toBeDeleted == NULL){
		return;
	}

	tmpDateTime = (DateTime*)toBeDeleted;

	free(tmpDateTime->date);
	free(tmpDateTime->time);
	free(tmpDateTime->text);
    free(tmpDateTime);
}
int compareDates(const void* first,const void* second){
    return 1;
}
char* printDate(void* toBePrinted){
    char* tmpStr;
	DateTime* tmpDateTime;
	int len;

	if (toBePrinted == NULL){
		return NULL;
	}

	tmpDateTime = (DateTime*)toBePrinted;

	len = strlen(tmpDateTime->date)+strlen(tmpDateTime->time)+strlen(tmpDateTime->text)+28;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "%s %s %s", tmpDateTime->date, tmpDateTime->time,tmpDateTime->text);

	return tmpStr;
}

void deleteParameter(void* toBeDeleted){
    Parameter* tmpParameter;

	if (toBeDeleted == NULL){
		return;
	}

	tmpParameter = (Parameter*)toBeDeleted;

	//free(tmpParameter->value);
    free(tmpParameter);
}
int compareParameters(const void* first,const void* second){
    Parameter* tmpParameter1;
	Parameter* tmpParameter2;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpParameter1 = (Parameter*)first;
	tmpParameter2 = (Parameter*)second;

	return strcmp((char*)tmpParameter1->name, (char*)tmpParameter2->name);
}
char* printParameter(void* toBePrinted){
    char* tmpStr;
	Parameter* tmpParameter;
	//int len;

	if (toBePrinted == NULL){
		return NULL;
	}

	tmpParameter = (Parameter*)toBePrinted;

	//len = strlen(tmpParameter->value)+strlen(tmpParameter->name)+28;
	tmpStr = (char*)malloc(sizeof(char)*10000);

	sprintf(tmpStr, "Parameter name:%s\nParameter value:%s", tmpParameter->name, tmpParameter->value);
    //free(tmpStr);
    return tmpStr;
}
void deleteValue(void* toBeDeleted){
    Value* tmpValue;

	if (toBeDeleted == NULL){
		return;
	}

	tmpValue = (Value*)toBeDeleted;

	//free(tmpValue->value);
    free(tmpValue);
}
int compareValues(const void* first,const void* second){
    Value* tmpValue1;
	Value* tmpValue2;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpValue1 = (Value*)first;
	tmpValue2 = (Value*)second;

	return strcmp((char*)tmpValue1->value, (char*)tmpValue2->value);
}
char* printValue(void* toBePrinted){
    char* tmpStr;
	Value* tmpValue;
	//int len;

	if (toBePrinted == NULL){
		return NULL;
	}

	tmpValue = (Value*)toBePrinted;

	//len = strlen(tmpValue->value)+strlen(tmpValue->name)+28;
	tmpStr = (char*)malloc(sizeof(char)*10000);

	sprintf(tmpStr, "Property value:%s", tmpValue->value);
    //free(tmpStr);
    return tmpStr;
}
int getFileLength(char* fileName){
    FILE *fp=fopen(fileName,"r");
    char *temp=(char*)malloc(100);
    int i=0;
    while(fgets(temp,100, fp)!=NULL){
        i++;
    }
    free(temp);
    fclose(fp);
    return i;
}

int IfContainSemi(char *s){
    int i=0;

    //s=malloc(1000);
    //printf("%s\n",tmp);
    for(i=0;i<strlen(s);i++){
        if(s[i]==';')
        return 1;
    }


    return 0;
}

int getPosition(char *s){
	//printf("%s\n",s);
	int i=0;
	for(i=0;i<strlen(s);i++){
		if(s[i]=='=')
		return i;
	}
	return 0;
}

int getPosition1(char *s){
	//printf("%s\n",s);
	int i=0;
	for(i=0;i<strlen(s);i++){
		if(s[i]==':')
		return i;
	}
	return 0;
}
int getPosition2(char *s){
	//printf("%s\n",s);
	int i=0;
	for(i=0;i<strlen(s);i++){
		if(s[i]=='-')
		return i;
	}
	return 0;
}

int checkifNumber(char *s){
	//printf("%s\n",s);
	int i=0;
	for(i=0;i<strlen(s);i++){
		if(!isdigit(s[i]))
		return 0;
	}
	return 1;
}

int checkUTCvalid(char *s){
	int i=0;
	if(s[0]==1||s[0]==2)i=1;
	return i;
}
void deleteTmp(Store *store[], char *Line[],int fileLength){
	int i=0;
	for(i=0;i<fileLength;i++){
	free(store[i]->name);
	free(store[i]->value);
	free(store[i]);
	free(Line[i]);
	}
}
int findKeyWord(char *s){
	char *token1;
	int checkFN=0;
	char * tmp=malloc(100);
	strcpy(tmp,s);
	int c=0,count=0;
	for(c=0;c<strlen(tmp);c++)
	{
		if(tmp[c]=='.')
		count=1;
	}
	token1=strtok(tmp,";");
	while(token1!=NULL){
		if(count==1){
			char* sep=strchr(tmp,'.');
			if(strcmp((sep+1),"FN")==0)
			checkFN=1;
		}else{
			if(strcmp(token1,"FN")==0)
			checkFN=1;
		}
		token1=strtok(NULL,";");
		token1=NULL;
	}
	free(tmp);
	return checkFN;
}
int findKey(char *s, char *key){
	char *token1;
	int check=0;
	char * tmp=malloc(100);
	strcpy(tmp,s);
	int c=0,count=0;
	for(c=0;c<strlen(tmp);c++)
	{
		if(tmp[c]=='.')
		count=1;
	}
	token1=strtok(tmp,";");
	while(token1!=NULL){
		if(count==1){
			char* sep=strchr(tmp,'.');
			if(strcmp((sep+1),key)==0){
				check=1;
			}
		}else{
			if(strcmp(token1,key)==0){
				check=1;
			}
		}
		token1=strtok(NULL,";");
		token1=NULL;
	}
	free(tmp);
	return check;
}

int ifCha(char *s){
	//printf("%s\n",s);
	int i=0;
	//int count=0;
	for(i=0;i<strlen(s);i++){
		if(isalpha(s[i])){
			if(s[i]!='Z')
			return 1;
		}

	}
	//printf("%d\n",count);
	return 0;
}

char * p(char *s){
    char try[100];
	char try2[100];
	char* new;
	int i=0;
	int j=0;
	strcpy(try,s);
	new = malloc(sizeof(char)*100);
	while(try[i]!='\0'){
		if(try[i]!=' '||i==1){
			while(try[i]!='\0'){
				try2[j]=try[i];
				i++;
				j++;
			}
			try2[j]='\0';
			strcpy(new,try2);
			return new;
		}
		i++;
	}
	free(new);
	return NULL;
}

VCardErrorCode createCard(char* fileName, Card** newCardObject){
//printf("----------------------/////////\n");
    int i=0,z=0,k=0;
	VCardErrorCode err;
    char *token,*token1;

	if(fileName==NULL){
		err=INV_FILE;
		//fclose(fp);
		return err;
	}
	if(strcmp(fileName,"")==0){
		err=INV_FILE;
		return err;
	}

	FILE *fp=fopen(fileName,"r");
	//const char s[2]=":";
	//char *tmp=malloc(100);

	if(fp==NULL){

		err=INV_FILE;
		return err;
	}
	else{
		int count=0;
		int c=0;
		for(c=0;c<strlen(fileName);c++)
		{
			if(fileName[c]=='.')
			count=1;
		}
		if(count==1){
			char *sep=strchr(fileName,'.');
			if(!(strcmp((sep+1),"vcf")==0)&&!(strcmp((sep+1),"vcard")==0))
			{
				fclose(fp);
				err=INV_FILE;
				return err;
			}

		}
	}

    int fileLength = getFileLength(fileName);

    Card *obj=(Card*)malloc(sizeof(Card));
    obj->fn=(Property*)malloc(sizeof(Property));
    obj->fn->name=(char*)malloc(sizeof(char*)*100);
    obj->fn->group=(char*)malloc(sizeof(char*)*100);
    //List* list_pro = initializeList(&printProperty, &deleteProperty, &compareProperties);

    obj->fn->parameters = initializeList(&printParameter, &deleteParameter, &compareParameters);
    //obj->fn->parameters = list_par;

    obj->fn->values= initializeList(&printValue, &deleteValue, &compareValues);
    obj->optionalProperties = initializeList(&printProperty, &deleteProperty, &compareProperties);
    obj->birthday = NULL;

    obj->anniversary = NULL;

	//Parameter *store[fileLength];
	char *temp=(char*)malloc(100);
	Store *store[fileLength];
	//char *tmpPar[fileLength][];
	char *Line[fileLength];
	//char *p_store[fileLength];

	for(i=0;i<fileLength;i++){
		store[i]=malloc(300);
		store[i]->name = malloc(300);
		store[i]->value = malloc(300);
		Line[i]=malloc(300);
		//p_store[i]=malloc(1000);
	}

	z=0;
	i=0;
    while(fgets(temp,100, fp)!=NULL){
		//printf("%s\n",temp);
        strcpy(Line[z],temp);
		z++;

    }
	free(temp);
	fclose(fp);


	for(z=0;z<fileLength;z++){
		if(Line[z][strlen(Line[z])-1]!='\n'||Line[z][strlen(Line[z])-2]!='\r'){
			err=INV_CARD;
			return err;
		}

		token = strtok (Line[z],"\n\r");
         while(token!=NULL){

         	token = strtok (NULL, "\n\r");

        }

	}

	for(z=0;z<fileLength;z++){// if first is white space


		if(Line[z][0]==' '){

			char *tmpStr;
			tmpStr= (char*)malloc(sizeof(char)*100);

			strcpy(tmpStr,Line[z-1]);
			//////////////////////
		    char * asd;
			char * back;
			asd=malloc(100);
			strcpy(asd,Line[z]);
			back=p(asd);
			free(asd);

			////////////////

			strcat(tmpStr,back);
			free(back);

			//tmpStr[0]='\0';//possible wrong;
			strcpy(Line[z-1],tmpStr);


			free(tmpStr);
		}
	}



	for(z=0;z<fileLength;z++){// begin to store
		//printf("%s\n",temp);
		if(Line[z][0]==' '){

			strcpy(store[z]->name," ");
			strcpy(store[z]->value," ");
		}else{

		//token = strtok (Line[z],s);
			int c=0,countDQ=0;
			for(c=0;c<strlen(Line[z]);c++){
				if(Line[z][c]==':'){
				    //if :exist
					countDQ=1;
				}
			}
			if(countDQ==0){
				//printf("%s\n",strlen(Line[z]));
				if(strlen(Line[z])==2)
				{

				}else{
					deleteTmp(store,Line,fileLength);
					deleteCard(obj);
		  		  	err=INV_PROP;
		  		  	return err;
				}
			}

			if(countDQ==1){

				char *sep = strchr(Line[z], ':');
				*sep='\0';
                strcpy(store[z]->name,Line[z]);

				strcpy(store[z]->value,sep+1);
				//printf("%s\n",(sep+1));
				if(strcmp((sep+1),"")==0){
					deleteTmp(store,Line,fileLength);
					deleteCard(obj);
		  		  	err=INV_PROP;
		  		  	return err;
				}
				if(strcmp(Line[z],"")==0){
					deleteTmp(store,Line,fileLength);
					deleteCard(obj);
		  		  	err=INV_PROP;
		  		  	return err;
				}
	   		}else{
				strcpy(store[z]->name," ");
				strcpy(store[z]->value," ");
			}
        }


	}
	  int checkBegin=0, checkEnd=0,checkVersion=0,checkFN=0;
	  for(z=0;z<fileLength;z++){//check is card is invalid
		  if(strcmp(store[z]->name,"BEGIN")==0){
			checkBegin=1;
		  }
		  if(strcmp(store[z]->name,"END")==0){
			checkEnd=1;
		  }
		  if(strcmp(store[z]->name,"VERSION")==0){
			checkVersion=1;
			if(strcmp(store[z]->value,"4.0")!=0)
			checkVersion=0;
		  }
		  if(strcmp(store[z]->name,"FN")==0){
			checkFN=1;
		  }
		  if(findKeyWord(store[z]->name)==1)
		  checkFN=1;
	  }
	  if(checkBegin==0||checkEnd==0||checkVersion==0||checkFN==0){

		  deleteTmp(store,Line,fileLength);
		  deleteCard(obj);
		  err=INV_CARD;
		  return err;
	  }

    z=0;

    for(i=0;i<fileLength;i++){
		if(strcmp(store[i]->name,"ANNIVERSARY")==0||findKey(store[i]->name,"ANNIVERSARY")==1)
		{
			//printf("\n----------------------come-------------------\n");
		    obj->anniversary = malloc(sizeof(DateTime)+sizeof(char)*1000);
			strcpy(obj->anniversary->text,"");
			strcpy(obj->anniversary->date,"");
			strcpy(obj->anniversary->time,"");
			memset(obj->anniversary->date,'\0',sizeof(obj->anniversary->date)+1);
			memset(obj->anniversary->time,'\0',sizeof(obj->anniversary->time)+1);
			//printf("\n%s\n",store[i]->value);

			if(store[i]->value[strlen(store[i]->value)-1]=='Z'){
				obj->anniversary->UTC=true;
			}else{
				obj->anniversary->UTC=false;
			}
			//printf("chang du shi %d",strlen(store[i]->value));


				//printf("fdsadsafasfadsfa");
			int c=0,count=0;
			for(c=0;c<strlen(store[i]->value);c++)
			{
				if(store[i]->value[c]=='T')
				count=1;

			}
			if(count==1&&store[i]->value[0]!='T'){
				char *sep = strchr(store[i]->value, 'T');
				*sep='\0';

				if(ifCha(store[i]->value)==1||ifCha((sep+1))==1){
					obj->anniversary->isText=false;
					strcpy(obj->anniversary->date,"");
					strcpy(obj->anniversary->time,"");
					strcpy(obj->anniversary->text,store[i]->value);
					strcat(obj->anniversary->text,(sep+1));
				}else{
					obj->anniversary->isText=false;
					strcpy(obj->anniversary->date,(store[i]->value));
				//printf("%s\n",obj->anniversary->date);
					strncpy(obj->anniversary->time,(sep+1),6);
					strcpy(obj->anniversary->text,"");
				}
			}
			if(count==1&&store[i]->value[0]=='T'){
				char *sep = strchr(store[i]->value, 'T');
				*sep='\0';
				if(ifCha((sep+1))==1){
					obj->anniversary->isText=true;
					strcpy(obj->anniversary->date,"");
					strcpy(obj->anniversary->time,"");
					strcpy(obj->anniversary->text,(sep+1));
				}else{
					obj->anniversary->isText=false;
					strcpy(obj->anniversary->time,(sep+1));
					strcpy(obj->anniversary->date,"");
					strcpy(obj->anniversary->text,"");
				}
			}
			if(count==0){
				if(ifCha(store[i]->value)==1){
					obj->anniversary->isText=true;
					strcpy(obj->anniversary->date,"");
					strcpy(obj->anniversary->time,"");
					strcpy(obj->anniversary->text,store[i]->value);
				}else{
					obj->anniversary->isText=false;
					strcpy(obj->anniversary->date,store[i]->value);
					strcpy(obj->anniversary->time,"");
					strcpy(obj->anniversary->text,"");
				}
			}

		//printf("\nssssssssssssssssss%s\n",obj->anniversary->date);
			//printf("%d\n",obj->anniversary->isTect);
			//printf("\n%d\n",count);
			//printf("\n%s\n",obj->anniversary->date)
			//printf("\n%s\n",obj->anniversary->date)


		}
		else if(strcmp(store[i]->name,"BDAY")==0||findKey(store[i]->name,"BDAY")==1)
		{
			//printf("----------------------/////////-------------\n");
			//obj->birthday=NULL;

			obj->birthday = malloc(sizeof(DateTime)+sizeof(char)*20);
			strcpy(obj->birthday->text,"");
			strcpy(obj->birthday->date,"");
			strcpy(obj->birthday->time,"");

			memset(obj->birthday->date,'\0',sizeof(obj->birthday->date)+1);
			memset(obj->birthday->time,'\0',sizeof(obj->birthday->time)+1);

			if(store[i]->value[strlen(store[i]->value)-1]=='Z'){
				obj->birthday->UTC=true;
			}else{
				obj->birthday->UTC=false;
			}

			int c=0,count=0;
			for(c=0;c<strlen(store[i]->value);c++)
			{
				if(store[i]->value[c]=='T')
				count=1;

			}
			if(count==1&&store[i]->value[0]!='T'){
				char *sep = strchr(store[i]->value, 'T');
				*sep='\0';
				if(ifCha(store[i]->value)==1||ifCha((sep+1))==1){
					obj->birthday->isText=true;
					strcpy(obj->birthday->date,"");
					strcpy(obj->birthday->time,"");
					strcpy(obj->birthday->text,store[i]->value);
					strcat(obj->birthday->text,(sep+1));
				}else{
					obj->birthday->isText=false;
					strcpy(obj->birthday->date,(store[i]->value));
				//printf("%s\n",obj->anniversary->date);
					strncpy(obj->birthday->time,(sep+1),6);
					strcpy(obj->birthday->text,"");
				}
			}
			if(count==1&&store[i]->value[0]=='T'){
				char *sep = strchr(store[i]->value, 'T');
				*sep='\0';
				if(ifCha((sep+1))==1){
					obj->birthday->isText=true;
					strcpy(obj->birthday->date,"");
					strcpy(obj->birthday->time,"");
					strcpy(obj->birthday->text,(sep+1));
				}else{
					obj->birthday->isText=false;
					strcpy(obj->birthday->time,(sep+1));
					strcpy(obj->birthday->date,"");
					strcpy(obj->birthday->text,"");
				}
			}
			if(count==0){
				if(ifCha(store[i]->value)==1){
					obj->birthday->isText=true;
					strcpy(obj->birthday->date,"");
					strcpy(obj->birthday->time,"");
					strcpy(obj->birthday->text,store[i]->value);
				}else{
					obj->birthday->isText=false;
					strcpy(obj->birthday->date,store[i]->value);
					strcpy(obj->birthday->time,"");
					strcpy(obj->birthday->text,"");
				}
			}
			//printf("%c",store[i]->value[strlen(store[i]->value)]);

		}

		else if(strcmp(store[i]->name,"FN")==0||findKey(store[i]->name,"FN")==1)
		{

			int countSemi=0;
			for(k=0;k<strlen(store[i]->value);k++){
	   			if(store[i]->value[k]==';'){
					countSemi++;
				}
			}
						//printf("%d %d\n",i,countSemi);
			if(countSemi==0){
				Value *val =(Value*)malloc(sizeof(Value));
				if(val!=NULL){
				memset(val->value,'\0',sizeof(val->value));
				strcpy(val->value,store[i]->value);
				}
				insertBack(obj->fn->values,val);
			}else{
				for(k=0;k<countSemi;k++)
				{
							//char *tmpPar=store[i]->value;
					char *tmpPar = malloc(300);
					strcpy(tmpPar,"");
					char *sep = strchr(store[i]->value, ';');
					*sep='\0';
					Value *val =(Value*)malloc(sizeof(Value));
					if(val!=NULL)
					strcpy(val->value,store[i]->value);
					store[i]->value[strlen(val->value)]='\0';
							//printf("%d %d %s\n",i,z,val->value);
					insertBack(obj->fn->values,val);
					strcpy(tmpPar,(sep+1));
							//store[i]->value[strlen(store[i]->value)]=' ';
							//memset(store[i]->value,'\0',strlen(store[i]->value));
					strcpy(store[i]->value,"");
							//memset(store[i]->value,'/0',strlen((sep+1)));
					store[i]->value[strlen(store[i]->value)]=' ';
					memcpy(store[i]->value , tmpPar,strlen(tmpPar)+1);
					free(tmpPar);

				}
					Value *val =(Value*)malloc(sizeof(Value));
					if(val!=NULL)
					strcpy(val->value,store[i]->value);
							//printf("%d %d %s\n",i,z,val->value);
					insertBack(obj->fn->values,val);

			}



			     token1 = strtok (store[i]->name,";");//seperate property name and parameter
			     while(token1!=NULL){
							//strcpy(tmpStr,token1);
							//printf("%d %d %s\n",i,z,token1);
					if(z==0){//z==0 insert Property name
						int c=0;
						int countPeriod=0;
						for(c=0;c<strlen(token1);c++){
						if(token1[c]=='.')//count is group exist
							countPeriod=1;
						}
						if(countPeriod==1){
							char *sep=strchr(token1,'.');
							*sep='\0';
							strcpy(obj->fn->group,token1);
							//printf("%s\n",optional->group);
							strcpy(obj->fn->name,(sep+1));
							//printf("%s\n",optional->name);
						}else{
							strcpy(obj->fn->name,token1);
							strcpy(obj->fn->group,"");
						}
						//strcpy(obj->fn->,"");


					}else if(z>0){//z>0 insert Parameter name and value
								//printf("%d %d %s ",i,z,token1);
						Parameter *par =malloc(sizeof(Parameter)+sizeof(char)*200);
						//if(par!=NULL)
						memset(par->name,'\0',sizeof(par->name));
			            int c=0;
						int count=0;
						for(c=0;c<strlen(token1);c++){
							if(token1[c]=='=')
							count=1;
						}
						if(count==1){
							strncpy(par->name,token1,getPosition(token1));//get Position of =
							strncpy(par->value,token1+getPosition(token1)+1,strlen(token1)-getPosition(token1));
						}else{
							deleteTmp(store,Line,fileLength);
							deleteCard(obj);
						  	err=INV_PROP;
						  	return err;
						}
						insertBack(obj->fn->parameters,par);
					}
			        token1 = strtok (NULL, ";");
			        z++;

			}
				z=0;
						//printf("%d %d\n",i,getLength(optional->parameters));
			/*if(getLength(obj->fn->parameters)==0){
				Parameter *par =malloc(sizeof(Parameter)+sizeof(char)*200);
				if(par!=NULL)
				memset(par->name,'\0',sizeof(par->name));
				strcpy(par->name,"");
				strcpy(par->value,"");
				insertBack(obj->fn->parameters,par);
			}*/

		}
		else if(strcmp(store[i]->name,"BEGIN")==0){

		}
		else if(strcmp(store[i]->name,"VERSION")==0){

		}
		else if(strcmp(store[i]->name,"END")==0){

		}
		else if(store[i]->name[0]!=' '){

			//printf("%d\n",i);
			Property *optional=(Property*)malloc(sizeof(Property));

			optional->name=(char*)malloc(sizeof(char)*100);

			optional->group=(char*)malloc(sizeof(char)*100);

			optional->parameters=initializeList(&printParameter, &deleteParameter, &compareParameters);

			optional->values= initializeList(&printValue, &deleteValue, &compareValues);

			/*The next block used to store Property value
			* store
			*
			*/
			int countSemi=0;
			for(k=0;k<strlen(store[i]->value);k++){
				if(store[i]->value[k]==';'){
					countSemi++;
				}
			}
			//printf("%d %d\n",i,countSemi);
			if(countSemi==0){
				Value *val =(Value*)malloc(sizeof(Value));
				if(val!=NULL)
				memset(val->value,'\0',sizeof(val->value));
				strcpy(val->value,store[i]->value);
				insertBack(optional->values,val);
			}else{

			for(k=0;k<countSemi;k++)
			{
				//char *tmpPar=store[i]->value;
				char *tmpPar = malloc(300);
				strcpy(tmpPar,"");
				char *sep = strchr(store[i]->value, ';');
				*sep='\0';
				Value *val =(Value*)malloc(sizeof(Value));
				if(val!=NULL)
				strcpy(val->value,store[i]->value);
				store[i]->value[strlen(val->value)]='\0';
				//printf("%d %d %s\n",i,z,val->value);
				insertBack(optional->values,val);
				strcpy(tmpPar,(sep+1));
				//store[i]->value[strlen(store[i]->value)]=' ';
				//memset(store[i]->value,'\0',strlen(store[i]->value));
				strcpy(store[i]->value,"");
				//memset(store[i]->value,'/0',strlen((sep+1)));
				store[i]->value[strlen(store[i]->value)]=' ';
				memcpy(store[i]->value , tmpPar,strlen(tmpPar)+1);
				free(tmpPar);

			}
				Value *val =(Value*)malloc(sizeof(Value));
			//printf("%d %d %s\n",i,z,token2);
			//memset(val->value,'\0',sizeof(val->value));
				if(val!=NULL)
				strcpy(val->value,store[i]->value);
				//printf("%d %d %s\n",i,z,val->value);
				insertBack(optional->values,val);

			}

			/*
			*insert property name, pamameter name and parameter value
			}*/

        	token1 = strtok (store[i]->name," ;");//seperate property name and parameter
        	while(token1!=NULL){
				//strcpy(tmpStr,token1);
				//printf("%d %d %s\n",i,z,token1);
				if(z==0){//z==0 insert Property name
					int c=0;
					int countPeriod=0;
					for(c=0;c<strlen(token1);c++){
						if(token1[c]=='.')//count is group exist
						countPeriod=1;
					}
					if(countPeriod==1){
						char *sep=strchr(token1,'.');
						*sep='\0';
						strcpy(optional->group,token1);
						//printf("%s\n",optional->group);
						strcpy(optional->name,(sep+1));
						//printf("%s\n",optional->name);
					}else{
						strcpy(optional->name,token1);
						strcpy(optional->group,"");
					}

				}else if(z>0){//z>0 insert Parameter name and value
					//printf("%d %d %s ",i,z,token1);
					Parameter *par =malloc(sizeof(Parameter)+sizeof(char)*200);
					if(par!=NULL)
					memset(par->name,'\0',sizeof(par->name));
                    int c=0;
					int count=0;
					for(c=0;c<strlen(token1);c++){
						if(token1[c]=='=')
						count=1;
					}
					if(count==1){
						strncpy(par->name,token1,getPosition(token1));//get Position of =
						strncpy(par->value,token1+getPosition(token1)+1,strlen(token1)-getPosition(token1));
						if(strcmp(par->name,"")==0){
							deleteTmp(store,Line,fileLength);
							deleteCard(obj);
				  		  	err=INV_PROP;
				  		  	return err;
						}
						if(strcmp(par->value,"")==0){
							deleteTmp(store,Line,fileLength);
							deleteCard(obj);
				  		  	err=INV_PROP;
				  		  	return err;
						}
					}else{
						deleteTmp(store,Line,fileLength);
						deleteCard(obj);
			  		  	err=INV_PROP;
			  		  	return err;
					}
					//c=0;
					//count=0;
					insertBack(optional->parameters,par);
					//printf("%s\n",par->name);
				}
        		token1 = strtok (NULL, ";");
         		z++;

			}
			z=0;
			//printf("%d %d\n",i,getLength(optional->parameters));
		   /* if(getLength(optional->parameters)==0){
				printf("\nrfsavdavgfsbsgassfgsavgfdyes\n");
				Parameter *par =malloc(sizeof(Parameter)+sizeof(char)*200);
				if(par!=NULL)
				memset(par->name,'\0',sizeof(par->name));
				strcpy(par->name,"");
				strcpy(par->value,"");
				insertBack(optional->parameters,par);
			}*/
			insertBack(obj->optionalProperties,optional);
		}


    }
	//printf("%s\n",obj->anniversary->date);
	*newCardObject=obj;
    deleteTmp(store,Line,fileLength);
	//printf("dfghjsdfg\n");
	err=OK;
    return err;

}
void deleteCard(Card* obj){
	if(obj==NULL){

	}else{
    free(obj->fn->name);
    free(obj->fn->group);
    free(obj->birthday);
    free(obj->anniversary);
	freeList(obj->fn->parameters);
    freeList(obj->fn->values);
	freeList(obj->optionalProperties);
    free(obj->fn);
    free(obj);
	}
}
char* printCard(const Card* obj){
	char* tmpStr;
	//printf("%s\n",obj->anniversary->text);
	//int len;

	if (obj == NULL){
		return NULL;
	}

	tmpStr = (char*)malloc(sizeof(char)*10000);

	char * add;
	sprintf(tmpStr, "Property name:%s\nProperty group:%s ",obj->fn->name,obj->fn->group);
	//strcpy(tmpStr,"Property group:");
	//strcat(tmpStr,obj->fn->group);
	add=toString(obj->fn->parameters);
	strcat(tmpStr,add);
	free(add);
	add=toString(obj->fn->values);
    strcat(tmpStr,add);
	strcat(tmpStr,"\n");
	free(add);
	add=toString(obj->optionalProperties);
    strcat(tmpStr,add);
	free(add);
	strcat(tmpStr,"\n");


	return tmpStr;
}
char* printError(VCardErrorCode err){
	//OK, INV_FILE, INV_CARD, INV_PROP, WRITE_ERROR, OTHER_ERROR
	char* tmpStr =malloc(20);

	if(err==OK){
		strcpy(tmpStr,"OK");
	}else if(err==INV_FILE){
		strcpy(tmpStr,"Invalid File");
	}else if(err==INV_CARD){
		strcpy(tmpStr,"Invalid Card");
	}else if(err==INV_PROP){
		strcpy(tmpStr,"Invalid Property");
	}else if(err==WRITE_ERROR){
		strcpy(tmpStr,"Write error");
	}else if(err==OTHER_ERROR){
		strcpy(tmpStr,"Other error");
	}
	//strcat(tmpStr,"\n");

	return tmpStr;
}
