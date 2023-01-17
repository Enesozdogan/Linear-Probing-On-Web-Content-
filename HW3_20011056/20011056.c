#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max 400

typedef struct n{
	char links[max];
	char content[max];
}LINKS;

typedef struct z{
	char key_links[max];
	
}arr_of_links;

typedef struct m{
	char word_key[max];
	arr_of_links arr[5];
	int link_no;
	int open;
	int try_time;
	
}KEY_WORDS;

char **split(char *string, char *seperators, int *count);
void find_real_G(KEY_WORDS *key_words,KEY_WORDS *key_words2);
void create_hash_table(KEY_WORDS* hash,KEY_WORDS* key_words,float load_factor,int table_size );
int get_key_horner(char* s);
void find_key_in_struct(KEY_WORDS *key_words,int k);
void split_to_words(LINKS *str_l,KEY_WORDS *key_words);
void print_hashTable(KEY_WORDS* hash,int table_size);
void get_value(KEY_WORDS* hash,int table_size);
int find_table_length(int table_size);
int prime_bool(int size);
int main(){
	
	FILE *file;
	char buffer[max];
	char filename[max];
	
	KEY_WORDS key_words[100];
	
	KEY_WORDS key_words2[100];
	LINKS str_l[21];
	
	int oku_devam=1;
	int current_line=1;
	int read_line=1;
	
	float load_factor=0.1;
	int table_size=56*((float)1/load_factor);
	table_size=find_table_length(table_size);
	KEY_WORDS *hash=(KEY_WORDS *)malloc(sizeof(KEY_WORDS)*table_size);
	int i=0;
	int j,k=0,f=0;
	int cont=1;
	int mod=0;
	
	
	
  	
	file=fopen("Sample.txt","r");
	if(file==NULL){
		printf("Dosya acilamadi.\n");
		return 1;
	}
	do{
		fgets(buffer,max,file);
		if(buffer[0]=='h'){
			strcpy(str_l[i].links,buffer);
			i++;
			//printf("%s\n",str_l[i].links);
		}
		else{
			strcpy(str_l[i-1].content,buffer);
		
		}
		if(feof(file)){
			oku_devam=0;
		}
		
	}while(oku_devam==1);
	
	fclose(file);
	
	k=0;
	for ( i = 0; i < 100; i++)
    		key_words[i].link_no=0;
    		
	split_to_words(str_l,key_words);
	
	for(k=0;k<56;k++){
		find_key_in_struct(key_words,k);
	}
	
	create_hash_table(hash,key_words,load_factor,table_size);

	do{
		printf("Detay 0,Normal 1 :");
		scanf("%d",&mod);
		if(mod==1){
			get_value(hash,table_size);
		}
		else{
			print_hashTable(hash,table_size);
		}
		
		printf("Cikmak icin 0, devam icin 1 bas:");
		scanf("%d",&cont);	
	}while(cont);
	
	

	
	
	
	return 0;
}
void create_hash_table(KEY_WORDS* hash,KEY_WORDS* key_words,float load_factor,int table_size ){
	int i,key_index;
	int start;
	for(i=0;i<table_size;i++){
		hash[i].open=1;
		hash[i].try_time=0;
	}
	for(i=0;i<56;i++){
		key_index=get_key_horner(key_words[i].word_key);
		if(strcmp(key_words[i].word_key,hash[key_index].word_key)==0){
			if(key_words[i].link_no>hash[key_index].link_no){
				memcpy(&hash[key_index],&key_words[i],sizeof(KEY_WORDS));
				//printf("hash word: %s\n",hash[key_index].word_key);
				hash[key_index].open=-1;
				hash[key_index].try_time=1;
			}

		}
		else{
			if(hash[key_index].open==1){
				memcpy(&hash[key_index],&key_words[i],sizeof(KEY_WORDS));
				hash[key_index].try_time=1;
				hash[key_index].open=-1;
			}
			else{
				start=key_index;
				key_index++;
				while(hash[key_index].open!=1){
					key_index++;
					hash[key_index].try_time=key_index-start;
					if(key_index==table_size-1){
						key_index=0;
					}
				}
				memcpy(&hash[key_index],&key_words[i],sizeof(KEY_WORDS));
				//printf("hash word: %s\n",hash[key_index].word_key);
				hash[key_index].open=-1;				
			}

		}
		
	}
}
int get_key_horner(char* s) {
    int p = 31,tmp;
    int i,hash=0;
    
    for(i = 0; i < strlen(s); i++) {
    
    	if(s[i]-65>32){
    		tmp=s[i]-'a'+1;
    		hash=p*hash+tmp;
		}
		else{
			tmp=s[i]-'A'+1;
			hash=p*hash+tmp;
		}	
     
        
    }
    return abs(hash)%31;
}

void get_value(KEY_WORDS* hash,int table_size){
	char buffer[100];
	KEY_WORDS tmp;
	char word1[20];
	char *word1_y;
	char word2[20];
	char *word2_y;
	char baglac[20];
	char *bag_y;
	int key_index;
	int i,j, a;;
	printf("Aramak istediginiz kelime/kelimeler:");
	fflush(stdin);
	scanf("%[^\n]s",buffer);
	
	sscanf(buffer,"%s %s %s;",word1,baglac,word2);
	
	a=strlen(word1)+1;
	word1_y=(char*)malloc(sizeof(char)*a);
	strcpy(word1_y,word1);
	a=strlen(word2)+1;
	word2_y=(char*)malloc(sizeof(char)*a);
	strcpy(word2_y,word2);
	a=strlen(baglac)+1;
	bag_y=(char*)malloc(sizeof(char)*a);
	strcpy(bag_y,baglac);
//	printf("kel1=%s, bag=%s, kel2=%s",word1,baglac,word2);
	
	if(strcmp(baglac,"ve")==0){
		key_index=get_key_horner(word1_y);
		while(strcmp(hash[key_index].word_key,word1_y)!=0 && key_index<table_size){
			key_index++;
		}
		if(key_index!=table_size){
			memcpy(&tmp,&hash[key_index],sizeof(KEY_WORDS));
		
			key_index=get_key_horner(word2_y);
			while(strcmp(hash[key_index].word_key,word2_y)!=0  && key_index<table_size){
				key_index++;
			}
			if(key_index!=table_size){
				if(tmp.link_no==1){
					printf("Ortak link yok\n");
				}
				else{
					for(i=0;i<tmp.link_no;i++){
						for(j=0;j<hash[key_index].link_no;j++){
							if(strcmp(tmp.arr[i].key_links,hash[key_index].arr[j].key_links)==0){
								printf("%d.link: %s",i+1,tmp.arr[i]);
							}
						}
					}			
				}			
			}
			else{
				printf("Ikinci kelime bulunamadi\n");	
			}			
		}
		else{
			printf("Kelimeler bulunamadi\n");
		}

	

		
	}
	else if(strcmp(bag_y,"veya")==0){
		
		key_index=get_key_horner(word1_y);
		while(strcmp(hash[key_index].word_key,word1_y)!=0 && key_index<table_size){
			key_index++;
		}
		if(key_index!=table_size){
			for(j=0;j<hash[key_index].link_no;j++){
				printf("%d. link: %s",j+1,hash[key_index].arr[j]);
			}			
		}
		else{
			printf("Birinci kelime bulunamadi\n");
		}

		
		
		key_index=get_key_horner(word2_y);
		while(strcmp(hash[key_index].word_key,word2_y)!=0 && key_index<table_size){
			key_index++;
		}
		if(key_index!=table_size){
			for(j=0;j<hash[key_index].link_no;j++){
				printf("%d. link: %s",j+1,hash[key_index].arr[j]);
			}
		}
		else{
			printf("ikinci kelime bulunamadi\n");
		}

		
	}
	else{
		key_index=get_key_horner(word1);
		while(strcmp(hash[key_index].word_key,buffer)!=0 && key_index<table_size){
			key_index++;
		}
		if(key_index!=table_size){
			for(j=0;j<hash[key_index].link_no;j++){
				printf("%d. link: %s",j+1,hash[key_index].arr[j]);
			}
		}
		else{
			printf("Kelime yok\n");
		}
			
	}
	
	

	
}

void find_key_in_struct(KEY_WORDS *key_words,int k){
	//printf(" in func: %s",key_words[k].word_key);
	int i=0,j=0;
	for(i=0;i<56;i++){
		if(strcmp(key_words[i].word_key,key_words[k].word_key)==0 && i!=k && key_words[k].open!=-1){
			if(key_words[i].link_no<3){
				strcpy(key_words[i].arr[key_words[i].link_no++].key_links,key_words[k].arr[0].key_links);
				key_words[k].open=-1;
			}
			
		}
	}
		
}

void find_real_G(KEY_WORDS *key_words,KEY_WORDS *key_words2){
	int i,j,z;
	int k=0;
	for(i=0;i<56;i++){
		for(j=0;j<56;j++){
			if(strcmp(key_words[i].word_key,key_words[j].word_key)==0 && i!=j && key_words[j].open!=4){
				if(key_words[i].link_no>key_words[j].link_no){
				  	memcpy(&key_words2[k],&key_words[i],sizeof(KEY_WORDS));
					key_words[i].open=4;	
				}
				else{
					memcpy(&key_words2[k],&key_words[j],sizeof(KEY_WORDS));
					key_words[j].open=4;			
				}
				k++;
			}
			
		}
	}
}

void split_to_words(LINKS *str_l,KEY_WORDS *key_words){
		int i,k=0,link_no,j;
		int count_strings = 0;
		char **split_strings;
		for(i=0;i<21;i++){
			split_strings=split(str_l[i].content, " ", &count_strings);

			for(j=0;j<count_strings;j++){
				link_no=key_words[k].link_no;
				strcpy(key_words[k].word_key,split_strings[j]);
				strcpy(key_words[k].arr[link_no].key_links,str_l[i].links);
				key_words[k].link_no++;
				k++;	
			
		
		}
	
	}
}

char **split(char *string, char *seperators, int *count)
{
  int len = strlen(string);
  *count = 0;
  int i = 0;
  int flag=0,flag1=0,flag2=0;
  int old_i;
  int j;
  char **strings;
  char buffer[16384];
  int string_index = 0;
  while (i < len)
  {
   
    while (i < len && flag1==0)
    {
      
      if (strchr(seperators, string[i]) == NULL){
      	flag1=1;
      	
	  }
      if(flag1!=1){
      	i++;
	  }
      
    }
    
	old_i = i;
    while (i < len && flag2==0)
    {
      if (strchr(seperators, string[i]) != NULL){
      	flag2=1;
      	
	  }
      if(flag2!=1){
      	i++;
	  }  
      
    }
    flag1=flag2=0;
    
    if (i > old_i) *count = *count + 1;
  }
  
  strings = malloc(sizeof(char *) * *count);
  flag=flag1=flag2=0;
  i = 0;
  string_index = 0;
  
  while (i < len)
  {
    while (i < len && flag1==0)
    {
      if (strchr(seperators, string[i]) == NULL){
      	flag1=1;
      	
	  }
      if(flag1!=1){
      	i++;
	  }  
      
    }
    
     j = 0;
    while (i < len && flag2==0)
    {
      if (strchr(seperators, string[i]) != NULL){
      	flag2=1;
	  }
	  if(flag2!=1){

     	buffer[j] = string[i];
     	i++;
      	j++;  
	  }


    }
	flag1=flag2=0;
    if (j > 0)
    {
      buffer[j] = '\0';
      int to_allocate = sizeof(char) *
                        (strlen(buffer) + 1);
      strings[string_index] = malloc(to_allocate);
      strcpy(strings[string_index], buffer);
      string_index++;
    }
    
  }
  return strings;
}

int prime_bool(int size){
	int i=2;
	while((i<=(size)/2) && size%i!=0){
		i++;
	}
	if(i==(size)/2+1){
		return 1;
	}
	else{
		return 0;
	}
}
int find_table_length(int table_size){
	int size=table_size;
	while(prime_bool(size)==0){
		size++;
	}
	return size;
}
void print_hashTable(KEY_WORDS* hash,int table_size){
	int i,j;
	printf("--TABLE SIZE:%d--\n",table_size);
	for(i=0;i<table_size;i++){
		
		printf("%d.Anahtar:%s ",i+1,hash[i].word_key);
		printf("Deneme:%d\n\n",hash[i].try_time);
		if(hash[i].link_no>0){
			for(j=0;j<hash[i].link_no;j++){
				printf("%d.link: %s\n",j+1,hash[i].arr[j].key_links);
			}	
		}
		
	}
}



















