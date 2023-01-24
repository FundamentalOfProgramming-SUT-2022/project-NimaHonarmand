#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
char order[10];
scanf("%s",order);
 while(1){
//=================================================================================================
    if(!strcmp(order,"createfile")){ //-----------------------createfile---------------------------
        int ctr=1; //counter for making dir
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char sp; // space
        char sp2;
        FILE *create=NULL;
        scanf("%s",c1); //--file
        scanf("%c",&sp);
        while(sp==' '){
            scanf("%c",&sp); //space between --file and /
        } //when the loop is over sp variable has captured the (/) char or the (") char
        if(sp=='"'){
            scanf("%c",&sp2); //get the (/) char
        }
         while(1){
            dir[0]='\\';
            dir[ctr]=getchar();
            if(dir[ctr]=='/'){
                dir[ctr]='\0';
                strcat(address,dir);
                mkdir(address);
                ctr=0;
                memset(dir, 0, sizeof(dir));
            }
            else if(dir[ctr]=='\n'){
                if(sp=='/'){
                    dir[ctr]='\0';
                }
                if(sp=='"'){
                    dir[ctr-1]='\0';
                }
                strcat(address,dir);
                create=fopen(address,"w");
                fclose(create);
                break;
            }
            ctr++;
         }
    }

//=============================================================================================
    else if(!strcmp(order,"insertstr")){ //---------------------insert-------------------------
        int line_pos;
        int char_pos;
        int ctr=1; //counter for making dir
        char sp2;
        char file_str[100000];
        char str[1000]; //the string which we want to insert in to the file
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char array_input[1000];
        char sp; // space
        char C; //for (:)in the pos section
        FILE *write=NULL;
        scanf("%s",c1); //--file
        scanf("%c",&sp);
        while(sp==' '){
            scanf("%c",&sp); //space between --file and /
        } //when the loop is over sp variable has captured the (/) char or the (") char
        if(sp=='"'){
            scanf("%c",&sp2); //get the (/) char
        }
         while(1){
            dir[0]='\\';
            dir[ctr]=getchar();
            if(dir[ctr]=='/'){
                dir[ctr]='\0';
                strcat(address,dir);
                ctr=0;
                memset(dir, 0, sizeof(dir));
            }
            else if(dir[ctr]=='-'){
                if(sp=='/'){
                    dir[ctr]='\0';
                }
                if(sp=='"'){
                    dir[ctr-1]='\0';
                }
                strcat(address,dir);
                break;
            }
            ctr++;
         }
         scanf("%s",c1); //-str(we just captured the (-) char in the last loop)
         scanf("%c",&sp);
         while(sp==' '){
            scanf("%c",&sp); //space between --file and /
        } //when the loop is over sp variable has captured the (") char or the first char of string
        if(sp=='"'){
            str[0]=getchar();
        }
        else{
            str[0]=sp;
        }
        ctr=1;
        while(1){
            str[ctr]=getchar();
            if(str[ctr-1]=='\\' && str[ctr]=='n'){
                str[ctr-1]='\n';
                ctr--;
            }
            if(str[ctr]=='-' && str[ctr-1]=='-'){
                str[ctr]='\0';
                str[ctr-1]='\0';
                if(sp=='"'){
                    int i=ctr-2;
                    for(i;str[i]==' ';i--){
                        str[i]='\0';
                    }
                    str[i]='\0';
                    break;
                }
                else{
                    for(int i=ctr-2;str[i]==' ';i--){
                        str[i]='\0';
                    }
                    break;
                }
            }
            ctr++;
        }//at the end of the loop we have gotten the sting by str array and the (--) chars
        scanf("%s",c1); //pos
        scanf("%d",&line_pos);
        scanf("%c",&C); // (:)between line_pos and char_pos
        scanf("%d",&char_pos);
        write=fopen(address,"r");
         if(write==NULL){
            printf("Invalid file");
            break;
         }
         else{
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,write);
                }
                else{
                    fgets(array_input,char_pos+1,write);
                }
                if(array_input[0]=='\0' && i!=1){
                    char enter='\n';
                    char space=' ';
                    strncat(array_input,&enter,1);
                    for(int i=0;i<char_pos;i++){
                        strncat(array_input,&space,1);
                    }
                }
                if(i==1){
                    strcpy(file_str,array_input);
                }
                else{
                    strcat(file_str,array_input);
                }
                memset(array_input, 0, sizeof(array_input));
            }
            strcat(file_str,str);
            ctr=0;
            while(!feof(write)){
                array_input[ctr]=fgetc(write);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
        }
        fclose(write);
        write=fopen(address,"w");
        fprintf(write,"%s",file_str);
        fclose(write);
        break;
    }
 //===================================================================================================
 else if(!strcmp(order,"cat")){ //-----------------------------cat-----------------------------------
        int ctr=1; //counter for making dir
        char file_str[10000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char sp; // space
        char sp2;
        FILE *prt=NULL;
        scanf("%s",c1); //--file
        scanf("%c",&sp);
        while(sp==' '){
            scanf("%c",&sp); //space between --file and /
        } //when the loop is over sp variable has captured the (/) char or the (") char
        if(sp=='"'){
            scanf("%c",&sp2); //get the (/) char
        }
         while(1){
            dir[0]='\\';
            dir[ctr]=getchar();
            if(dir[ctr]=='/'){
                dir[ctr]='\0';
                strcat(address,dir);
                ctr=0;
                memset(dir, 0, sizeof(dir));
            }
            else if(dir[ctr]=='\n'){
                if(sp=='/'){
                    dir[ctr]='\0';
                }
                if(sp=='"'){
                    dir[ctr-1]='\0';
                }
                strcat(address,dir);
                break;
            }
            ctr++;
         }
         ctr=0;
         prt=fopen(address,"r");
         if(prt==NULL){
            printf("Invalid file");
         }
         else{
          while(!feof(prt)){
            file_str[ctr]=fgetc(prt);
            ctr++;
          }
          fclose(prt);
          printf("%s",file_str);
          break;
         }
  }

 //==================================================================================================
 else if(!strcmp(order,"removestr")){ //-----------------------------remove--------------------------
        int length;
        int ctr=1; //counter for making dir
        int line_pos;
        int char_pos;
        int num_char; //number of char to remove
        char file_str[10000];
        char array_input[1000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char sp; // space
        char sp2;
        char C; //for (:)in the pos section
        char direction[10];
        FILE *rmv=NULL;
        scanf("%s",c1); //--file
        scanf("%c",&sp);
        while(sp==' '){
            scanf("%c",&sp); //space between --file and /
        } //when the loop is over sp variable has captured the (/) char or the (") char
        if(sp=='"'){
            scanf("%c",&sp2); //get the (/) char
        }
         while(1){
            dir[0]='\\';
            dir[ctr]=getchar();
            if(dir[ctr]=='/'){
                dir[ctr]='\0';
                strcat(address,dir);
                ctr=0;
                memset(dir, 0, sizeof(dir));
            }
            else if(dir[ctr]=='-'){
                if(sp=='/'){
                    dir[ctr]='\0';
                }
                if(sp=='"'){
                    dir[ctr-1]='\0';
                }
                strcat(address,dir);
                break;
            }
            ctr++;
         }
         scanf("%s",c1); //-pos(we just captured the (-) char in the last loop)
         scanf("%d",&line_pos);
         scanf("%c",&C);
         scanf("%d",&char_pos);
         scanf("%s",c1); //-size
         scanf("%d",&num_char);
         scanf("%s",direction); //-b(backward) or -f(forward)
         rmv=fopen(address,"r");
         if(rmv==NULL){
            printf("Invalid file");
            break;
         }
         else if(!strcmp(direction,"-f")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,rmv);
                }
                else{
                    fgets(array_input,char_pos+1,rmv);
                }
                if(i==1){
                    strcpy(file_str,array_input);
                }
                else{
                    strcat(file_str,array_input);
                }
                memset(array_input, 0, sizeof(array_input));
            }
            for(int i=0;i<num_char;i++){
                array_input[i]=fgetc(rmv);
            }
            memset(array_input, 0, sizeof(array_input));
            ctr=0;
            while(!feof(rmv)){
                array_input[ctr]=fgetc(rmv);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
         }
         else if(!strcmp(direction,"-b")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,rmv);
                }
                else{
                    fgets(array_input,char_pos+2,rmv);
                }
                if(i==1){
                    strcpy(file_str,array_input);
                }
                else{
                    strcat(file_str,array_input);
                }
                memset(array_input, 0, sizeof(array_input));
            }
            length=strlen(file_str);
            for(int i=1;i<=num_char;i++){
                file_str[length-i]='\0';
            }
            ctr=0;
            while(!feof(rmv)){
                array_input[ctr]=fgetc(rmv);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
         }
         fclose(rmv);
         rmv=fopen(address,"w");
         fprintf(rmv,"%s",file_str);
         fclose(rmv);
         break;

  }
 }
 return 0;
}
