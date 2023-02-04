#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


//-------------------------------------tree-------------------------------------------
void tree(char add[],int depth_input){
    int depth=-1;
    char add2[100];
    strcpy(add2,add);
    struct dirent *entry;
    char dot[10]=".";
    char d_dot[10]="..";
    char back_s='\\';
    DIR *dp=NULL;
    int length=strlen(add);
    for(int i=0;i<length;i++){
        if(add[i]=='\\'){
            depth++;
        }
    }
    dp=opendir(add);
    while(entry=readdir(dp)){
        if(strcmp(entry->d_name,dot)!=0 && strcmp(entry->d_name,d_dot)!=0){
            if(depth!=0){
                printf("|");
            }
            for(int i=1;i<=depth;i++){
                if(i==1){
                    printf(" ");
                }
                else{
                    printf("  ");
                }
            }
            printf("|___%s\n",entry->d_name);
            strcpy(add2,add);
            strncat(add2,&back_s,1);
            strcat(add2,entry->d_name);
            if(depth<=depth_input-1 || depth_input==-1){
                tree(add2,depth_input);
            }
        }
    }
}
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

int main(){
char order[10];
char cut_copy_string[10000];
scanf("%s",order);
 while(1){
//=================================================================================================
    if(!strcmp(order,"createfile")){ //-----------------------createfile---------------------------
        int ctr=1; //counter for making dir
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
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
                mkdir(undo_address);
                strcat(undo_address,dir);
                strcat(address,dir);
                create=fopen(address,"w");
                fclose(create);

                create=fopen(undo_address,"w");
                fclose(create);
                break;
            }
            ctr++;
         }
         printf("Success\n");
    }

//=============================================================================================
    else if(!strcmp(order,"insertstr")){ //---------------------insert-------------------------
        int line_pos;
        int char_pos;
        int ctr=1; //counter for making dir
        char sp2;
        char file_str[100000];
        char undo_file[100000];
        char str[1000]; //the string which we want to insert in to the file
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
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
                strcat(undo_address,dir);
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
            printf("Invalid file\n");
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
                    strcpy(undo_file,array_input);
                }
                else{
                    strcat(file_str,array_input);
                    strcat(undo_file,array_input);
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
            strcat(undo_file,array_input);
            printf("Success\n");
        }
        fclose(write);
        write=fopen(address,"w");
        fprintf(write,"%s",file_str);
        fclose(write);

        write=fopen(undo_address,"w");
        fprintf(write,"%s",undo_file);
        fclose(write);
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
            printf("Invalid file\n");
         }
         else{
          while(!feof(prt)){
            file_str[ctr]=fgetc(prt);
            ctr++;
          }
          fclose(prt);
          printf("%s\n",file_str);
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
        char undo_file[100000];
        char array_input[1000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
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
                strcat(undo_address,dir);
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
            printf("Invalid file\n");
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
                    strcpy(undo_file,array_input);
                }
                else{
                    strcat(file_str,array_input);
                    strcat(undo_file,array_input);
                }
                memset(array_input, 0, sizeof(array_input));
            }
            for(int i=0;i<num_char;i++){
                array_input[i]=fgetc(rmv);
            }
            strcat(undo_file,array_input);
            memset(array_input, 0, sizeof(array_input));
            ctr=0;
            while(!feof(rmv)){
                array_input[ctr]=fgetc(rmv);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
            strcat(undo_file,array_input);
            printf("Success\n");
         }
         else if(!strcmp(direction,"-b")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,rmv);
                }
                else{
                    fgets(array_input,char_pos+1,rmv);
                }
                if(i==1){
                    strcpy(file_str,array_input);
                    strcpy(undo_file,array_input);
                }
                else{
                    strcat(file_str,array_input);
                    strcat(undo_file,array_input);
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
            strcat(undo_file,array_input);
            printf("Success\n");
         }
         fclose(rmv);
         rmv=fopen(address,"w");
         fprintf(rmv,"%s",file_str);
         fclose(rmv);

         rmv=fopen(undo_address,"w");
         fprintf(rmv,"%s",undo_file);
         fclose(rmv);

  }
//=============================================================================================
else if(!strcmp(order,"copystr")){ //-------------------------copy------------------------------
        memset(cut_copy_string, 0, sizeof(cut_copy_string));
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
        FILE *cpy=NULL;
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
         cpy=fopen(address,"r");
         if(cpy==NULL){
            printf("Invalid file\n");
            break;
         }
         else if(!strcmp(direction,"-f")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,cpy);
                }
                else{
                    fgets(array_input,char_pos+1,cpy);
                }
                if(i==1){
                    strcpy(file_str,array_input);
                }
                else{
                    strcat(file_str,array_input);
                }
            }
            for(int i=0;i<num_char;i++){
                cut_copy_string[i]=fgetc(cpy);
            }
            strcat(file_str,cut_copy_string);
            memset(array_input, 0, sizeof(array_input));
            ctr=0;
            while(!feof(cpy)){
                array_input[ctr]=fgetc(cpy);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
            printf("Success\n");
         }
         else if(!strcmp(direction,"-b")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,cpy);
                }
                else{
                    fgets(array_input,char_pos+1,cpy);
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
                cut_copy_string[num_char-i]=file_str[length-i];
            }
            ctr=0;
            while(!feof(cpy)){
                array_input[ctr]=fgetc(cpy);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
            printf("Success\n");
         }
         fclose(cpy);
         cpy=fopen(address,"w");
         fprintf(cpy,"%s",file_str);
         fclose(cpy);

    }
//======================================================================================
else if(!strcmp(order,"cutstr")){ //----------------------cut---------------------------
        memset(cut_copy_string, 0, sizeof(cut_copy_string));
        int length;
        int ctr=1; //counter for making dir
        int line_pos;
        int char_pos;
        int num_char; //number of char to remove
        char file_str[10000];
        char undo_file[100000];
        char array_input[1000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
        char sp; // space
        char sp2;
        char C; //for (:)in the pos section
        char direction[10];
        FILE *cut=NULL;
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
                strcat(undo_address,dir);
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
         cut=fopen(address,"r");
         if(cut==NULL){
            printf("Invalid file\n");
            break;
         }
         else if(!strcmp(direction,"-f")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,cut);
                }
                else{
                    fgets(array_input,char_pos+1,cut);
                }
                if(i==1){
                    strcpy(file_str,array_input);
                    strcpy(undo_file,array_input);
                }
                else{
                    strcat(file_str,array_input);
                    strcat(undo_file,array_input);
                }
            }
            for(int i=0;i<num_char;i++){
                cut_copy_string[i]=fgetc(cut);
            }
            strcat(undo_file,cut_copy_string);
            memset(array_input, 0, sizeof(array_input));
            ctr=0;
            while(!feof(cut)){
                array_input[ctr]=fgetc(cut);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
            strcat(undo_file,array_input);
            printf("Success\n");
         }
         else if(!strcmp(direction,"-b")){
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,cut);
                }
                else{
                    fgets(array_input,char_pos+1,cut);
                }
                if(i==1){
                    strcpy(file_str,array_input);
                    strcpy(undo_file,array_input);
                }
                else{
                    strcat(file_str,array_input);
                    strcat(undo_file,array_input);
                }
                memset(array_input, 0, sizeof(array_input));
            }
            length=strlen(file_str);
            for(int i=1;i<=num_char;i++){
                cut_copy_string[num_char-i]=file_str[length-i];
                file_str[length-i]='\0';
            }
            strcat(undo_file,cut_copy_string);
            ctr=0;
            while(!feof(cut)){
                array_input[ctr]=fgetc(cut);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
            strcat(undo_file,array_input);
            printf("Success\n");
         }
         fclose(cut);
         cut=fopen(address,"w");
         fprintf(cut,"%s",file_str);
         fclose(cut);

         cut=fopen(undo_address,"w");
         fprintf(cut,"%s",undo_file);
         fclose(cut);
 }
//===========================================================================================
 else if(!strcmp(order,"pastestr")){ //----------------------paste---------------------------
        int ctr=1; //counter for making dir
        int line_pos;
        int char_pos;
        char file_str[10000];
        char undo_file[100000];
        char array_input[1000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
        char sp; // space
        char sp2;
        char C; //for (:)in the pos section
        FILE *paste=NULL;
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
                strcat(undo_address,dir);
                strcat(address,dir);
                break;
            }
            ctr++;
         }
         scanf("%s",c1); //-pos(we just captured the (-) char in the last loop)
         scanf("%d",&line_pos);
         scanf("%c",&C);
         scanf("%d",&char_pos);
         paste=fopen(address,"r");
         if(paste==NULL){
            printf("Invalid file\n");
            break;
         }
         else{
            for(int i=1;i<=line_pos;i++){
                if(i!=line_pos){
                    fgets(array_input,999,paste);
                }
                else{
                    fgets(array_input,char_pos+1,paste);
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
                    strcpy(undo_file,array_input);
                }
                else{
                    strcat(file_str,array_input);
                    strcat(undo_file,array_input);
                }
                memset(array_input, 0, sizeof(array_input));
            }
            strcat(file_str,cut_copy_string);
            ctr=0;
            while(!feof(paste)){
                array_input[ctr]=fgetc(paste);
                ctr++;
            }
            array_input[ctr-1]='\0';
            strcat(file_str,array_input);
            strcat(undo_file,array_input);
            printf("Success\n");
        }
        fclose(paste);
        paste=fopen(address,"w");
        fprintf(paste,"%s",file_str);
        fclose(paste);

        paste=fopen(undo_address,"w");
        fprintf(paste,"%s",undo_file);
        fclose(paste);

 }
 //==================================================================================================================================
 else if(!strcmp(order,"find") || !strcmp(order,"replace")){//---------------------------find/replace--------------------------------
        int ok=0;
        int lenght;
        int ctr=1; //counter for making dir
        int case_num=0; //(0:without '*') ... (1:with '*' at the begin) ... (2:with '*' at the end) ... (3:with '*' in the middle part)
        int sprvisr=0;
        int pos_line=1;
        int pos_char=-1;
        int pos_star;
        int pos_char_first;//it's for position of the first char in file_str which we want to use it for replace order
        int pos_char_end; //it's for position of the last char in file_str which we want to use it for replace order
        char sp2;
        char feature[20];
        char file_str[100000];
        char undo_file[100000];
        char file_str2[100000]; //it's for replace
        char str[1000]; //the string which we want to insert in to the file
        char str2[1000]; //it's for replace order which means the string we want to replace it with string 1
        char c1[50]; //--str
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
        char sp; // space
        char C; //the char which we use to understand do we have extra features or not
        FILE *find=NULL;
         scanf("%s",c1); //--str
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
        }//at the end of the loop we have gotten the string by str array and the (--) chars
        if(!strcmp(order,"replace")){ //it this loop we will get the str2 for replacement
            scanf("%s",c1); //--str2
            scanf("%c",&sp);
            while(sp==' '){
                scanf("%c",&sp); //space between --file and /
            } //when the loop is over sp variable has captured the (") char or the first char of string
            if(sp=='"'){
                str2[0]=getchar();
            }
            else{
                str2[0]=sp;
            }
            ctr=1;
            while(1){
                str2[ctr]=getchar();
                if(str2[ctr-1]=='\\' && str2[ctr]=='n'){
                    str2[ctr-1]='\n';
                    ctr--;
                }
                if(str2[ctr]=='-' && str2[ctr-1]=='-'){
                    str2[ctr]='\0';
                    str2[ctr-1]='\0';
                    if(sp=='"'){
                        int i=ctr-2;
                        for(i;str2[i]==' ';i--){
                            str2[i]='\0';
                        }
                        str2[i]='\0';
                        break;
                    }
                    else{
                        for(int i=ctr-2;str2[i]==' ';i--){
                            str2[i]='\0';
                        }
                        break;
                    }
                }
                ctr++;
            }//at the end of the loop we have gotten the string by str2 array and the (--) chars
        }
        scanf("%s",c1); //file
        scanf("%c",&sp);
        while(sp==' '){
            scanf("%c",&sp); //space between --file and /
        } //when the loop is over sp variable has captured the (/) char or the (") char
        if(sp=='"'){
            scanf("%c",&sp2); //get the (/) char
        }
        ctr=1;
         while(1){
            dir[0]='\\';
            dir[ctr]=getchar();
            if(dir[ctr]=='/'){
                dir[ctr]='\0';
                strcat(address,dir);
                ctr=0;
                memset(dir, 0, sizeof(dir));
            }
            else if(dir[ctr]=='-' || dir[ctr]=='\n'){
                C=dir[ctr];
                if(sp=='/'){
                    dir[ctr]='\0';
                }
                if(sp=='"'){
                    dir[ctr-1]='\0';
                }
                strcat(undo_address,dir);
                strcat(address,dir);
                break;
            }
            ctr++;
         }
         if(C=='-'){
            scanf("%s",feature);
         }
        ctr=0;
        find=fopen(address,"r");

        if(C=='\n'){ //we don't have any feature so we just have to find basic string
            lenght=strlen(str);
                if(str[0]=='*' && str[lenght-1]!='*'){ //the case with '*' at the begin
                    case_num=1;
                }
                else if(str[0]!='*' && str[lenght-1]=='*'){ //the case with '*' at the end
                    case_num=2;
                }
                else if(str[0]=='*' && str[lenght-1]=='*'){ //the case with '*' at the begin and another at the end
                    case_num=3;
                }
                else{
                    for(int i=0;i<lenght;i++){
                        if(str[i]=='*' && str[i-1]==' '){ //case:text *text
                            case_num=4;
                            pos_star=i;
                        }
                        else if(str[i]=='*' && str[i+1]==' '){ //case:text* text
                            case_num=5;
                            pos_star=i;
                        }
                        else if(str[i]=='*'){
                            case_num=4;
                            pos_star=i;
                        }
                    }
                }
            //0000000000000000000000000000000000000000000
            if(case_num==0){ //case number 0 which mean we don't have any '*' in the string
                while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        ok=1;
                        pos_char_first=i;
                        pos_char_end=i+lenght-1;
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                            break;
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            printf("Success\n");
                            break;
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr){
                    printf("Invalid string\n");
                }
            }
            //111111111111111111111111111111111111111111111111111
            ctr=0;
            if(case_num==1){ //the case with the '*' at the begin
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        ok=1;
                        pos_char_first=i;
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            pos_char_first--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                            break;
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            printf("Success\n");
                            break;
                        }
                    }
                    sprvisr=0;
                }
               if(i==ctr){
                    printf("Invalid string\n");
               }
            }
            //2222222222222222222222222222222222222222222
            ctr=0;
            if(case_num==2){//the case with the '*' at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        ok=1;
                        pos_char_first=i;
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                            break;
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            for(int j=pos_char_end;file_str[j]!=' ' && file_str[j]!='\n' && file_str[j]!=EOF;j++){
                                pos_char_end++;
                            }
                            pos_char_end--;
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            printf("Success\n");
                            break;
                        }
                    }
                    sprvisr=0;
                }
               if(i==ctr){
                    printf("Invalid string\n");
               }
            }
            //3333333333333333333333333333333333333333333333
            ctr=0;
            if(case_num==3){//the case with '*' at the begin and one another at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-2;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        ok=1;
                        pos_char_first=i;
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            pos_char_first--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                            break;
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            for(int j=pos_char_end;file_str[j]!=' ' && file_str[j]!='\n' && file_str[j]!=EOF;j++){
                                pos_char_end++;
                            }
                            pos_char_end--;
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            printf("Success\n");
                            break;
                        }
                    }
                    sprvisr=0;
                }
               if(i==ctr){
                    printf("Invalid string\n");
               }
            }
            //444444444444444444444444444444444444444444444
            ctr=0;
            if(case_num==4){//case:text *text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ' && file_str[j]!=EOF;j++){
                            pos_char_end++;
                             if(file_str[j]==str[pos_star+1]){
                                for(int z=1;z<=lenght-(pos_star+2);z++){
                                    pos_char_end++;
                                    if(file_str[j+z]!=str[pos_star+z+1]){
                                        sprvisr=1;
                                        break;
                                    }
                                }
                             }
                             if(sprvisr==0 && file_str[j]==str[pos_star+1]){
                                ok=1;
                                pos_char_first=i;
                                sprvisr=2;
                                break;
                             }
                        }
                        if(sprvisr==2){
                            if(!strcmp(order,"find")){
                                printf("pos: line:%d char:%d\n",pos_line,pos_char);
                                break;
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                printf("Success\n");
                                break;
                            }
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr){
                    printf("Invalid string\n");
                }
            }
            //5555555555555555555555555555555555555555555555
            ctr=0;
            if(case_num==5){ //case:test* text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ';j++){
                            pos_char_end++;
                        }
                        pos_char_end+=2;
                        j++;
                        if(file_str[j]==str[pos_star+2]){
                            for(int z=1;z<=lenght-(pos_star+3);z++){
                                pos_char_end++;
                                if(file_str[j+z]!=str[pos_star+2+z]){
                                    sprvisr=1;
                                    break;
                                }
                            }
                        }
                        if(sprvisr==0 && file_str[j]==str[pos_star+2]){
                            ok=1;
                            pos_char_first=i;
                            sprvisr=2;
                        }
                        if(sprvisr==2){
                            if(!strcmp(order,"find")){
                                printf("pos: line:%d char:%d\n",pos_line,pos_char);
                                break;
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                printf("Success\n");
                                break;
                            }
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr){
                    printf("Invalid string\n");
                }
            }
        }
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
        if(C=='-'){ //we just have feature items
            if(!strcmp(feature,"count")){ //feature: count
                int count=0;
                case_num=0;
                lenght=strlen(str);
                if(str[0]=='*' && str[lenght-1]!='*'){ //the case with '*' at the begin
                    case_num=1;
                }
                else if(str[0]!='*' && str[lenght-1]=='*'){ //the case with '*' at the end
                    case_num=2;
                }
                else if(str[0]=='*' && str[lenght-1]=='*'){ //the case with '*' at the begin and another at the end
                    case_num=3;
                }
                else{
                    for(int i=0;i<lenght;i++){
                        if(str[i]=='*' && str[i-1]==' '){ //case:text *text
                            case_num=4;
                            pos_star=i;
                        }
                        else if(str[i]=='*' && str[i+1]==' '){ //case:text* text
                            case_num=5;
                            pos_star=i;
                        }
                        else if(str[i]=='*'){
                            case_num=4;
                            pos_star=i;
                        }
                    }
                }
            //0000000000000000000000000000000000000000000
            if(case_num==0){ //case number 0 which mean we don't have any '*' in the string
                while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        count++;
                    }
                    sprvisr=0;
                }
                if(i==ctr && count==0){
                    printf("Invalid string\n");
                }
                else{
                    printf("count:%d\n",count);
                }
            }
            //111111111111111111111111111111111111111111111111111
            ctr=0;
            if(case_num==1){ //the case with the '*' at the begin
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        count++;
                    }
                    sprvisr=0;
                }
               if(i==ctr && count==0){
                    printf("Invalid string\n");
               }
               else{
                printf("count:%d\n",count);
               }
            }
            //2222222222222222222222222222222222222222222
            ctr=0;
            if(case_num==2){//the case with the '*' at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght-1;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        count++;
                    }
                    sprvisr=0;
                }
               if(i==ctr && count==0){
                    printf("Invalid string\n");
               }
               else{
                    printf("count:%d\n",count);
               }
            }
            //3333333333333333333333333333333333333333333333
            ctr=0;
            if(case_num==3){//the case with '*' at the begin and one another at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-2;j++){
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        count++;
                    }
                    sprvisr=0;
                }
               if(i==ctr && count==0){
                    printf("Invalid string\n");
               }
               else{
                printf("count:%d\n",count);
               }
            }
            //444444444444444444444444444444444444444444444
            ctr=0;
            if(case_num==4){//case:text *text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ' && file_str[j]!=EOF;j++){
                             if(file_str[j]==str[pos_star+1]){
                                for(int z=1;z<=lenght-(pos_star+2);z++){
                                    if(file_str[j+z]!=str[pos_star+z+1]){
                                        sprvisr=1;
                                        break;
                                    }
                                }
                             }
                             if(sprvisr==0 && file_str[j]==str[pos_star+1]){
                                sprvisr=2;
                                break;
                             }
                        }
                        if(sprvisr==2){
                            count++;
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr && count==0){
                    printf("Invalid string\n");
                }
                else{
                    printf("count:%d\n",count);
                }
            }
            //5555555555555555555555555555555555555555555555
            ctr=0;
            if(case_num==5){ //case:test* text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ';j++){
                        }
                        j++;
                        if(file_str[j]==str[pos_star+2]){
                            for(int z=1;z<=lenght-(pos_star+3);z++){
                                if(file_str[j+z]!=str[pos_star+2+z]){
                                    sprvisr=1;
                                    break;
                                }
                            }
                        }
                        if(sprvisr==0 && file_str[j]==str[pos_star+2]){
                            sprvisr=2;
                        }
                        if(sprvisr==2){
                            count++;
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr && count==0){
                    printf("Invalid string\n");
                }
                else{
                    printf("count:%d\n",count);
                }
            }
            }
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
            if(!strcmp(feature,"at")){ //feature: at
                int save;
                int at;
                int count=0;
                case_num=0;
                scanf("%d",&at);
                lenght=strlen(str);
                if(str[0]=='*' && str[lenght-1]!='*'){ //the case with '*' at the begin
                    case_num=1;
                }
                else if(str[0]!='*' && str[lenght-1]=='*'){ //the case with '*' at the end
                    case_num=2;
                }
                else if(str[0]=='*' && str[lenght-1]=='*'){ //the case with '*' at the begin and another at the end
                    case_num=3;
                }
                else{
                    for(int i=0;i<lenght;i++){
                        if(str[i]=='*' && str[i-1]==' '){ //case:text *text
                            case_num=4;
                            pos_star=i;
                        }
                        else if(str[i]=='*' && str[i+1]==' '){ //case:text* text
                            case_num=5;
                            pos_star=i;
                        }
                        else if(str[i]=='*'){
                            case_num=4;
                            pos_star=i;
                        }
                    }
                }
            //0000000000000000000000000000000000000000000
            if(case_num==0){ //case number 0 which mean we don't have any '*' in the string
                while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        count++;
                        if(count==at){
                            ok=1;
                            pos_char_first=i;
                            if(!strcmp(order,"find")){
                                printf("at:%d /pos: line:%d char:%d\n",at,pos_line,pos_char);
                                break;
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                printf("Success\n");
                                break;
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
                if(i==ctr && count!=at){
                    printf("Invalid string\n");
                }
            }
            //111111111111111111111111111111111111111111111111111
            ctr=0;
            if(case_num==1){ //the case with the '*' at the begin
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        pos_char_first=i;
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            pos_char_first--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        count++;
                        if(count==at){
                            ok=1;
                            if(!strcmp(order,"find")){
                                printf("at:%d /pos: line:%d char:%d\n",at,pos_line,pos_char);
                                break;
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                printf("Success\n");
                                break;
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
               if(i==ctr && count!=at){
                    printf("Invalid string\n");
               }
            }
            //2222222222222222222222222222222222222222222
            ctr=0;
            if(case_num==2){//the case with the '*' at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        pos_char_first=i;
                        count++;
                        if(count==at){
                            ok=1;
                            if(!strcmp(order,"find")){
                                printf("at:%d /pos: line:%d char:%d\n",at,pos_line,pos_char);
                                break;
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                for(int j=pos_char_end;file_str[j]!=' ' && file_str[j]!='\n' && file_str[j]!=EOF;j++){
                                    pos_char_end++;
                                }
                                pos_char_end--;
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                printf("Success\n");
                                break;
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
               if(i==ctr && count!=at){
                    printf("Invalid string\n");
               }
            }
            //3333333333333333333333333333333333333333333333
            ctr=0;
            if(case_num==3){//the case with '*' at the begin and one another at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-2;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        pos_char_first=i;
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            pos_char_first--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        count++;
                        if(count==at){
                            ok=1;
                            if(!strcmp(order,"find")){
                                printf("at:%d /pos: line:%d char:%d\n",at,pos_line,pos_char);
                                break;
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                for(int j=pos_char_end;file_str[j]!=' ' && file_str[j]!='\n' && file_str[j]!=EOF;j++){
                                    pos_char_end++;
                                }
                                pos_char_end--;
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                printf("Success\n");
                                break;
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
               if(i==ctr && count!=at){
                    printf("Invalid string\n");
               }
            }
            //444444444444444444444444444444444444444444444
            ctr=0;
            if(case_num==4){//case:text *text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ' && file_str[j]!=EOF;j++){
                            pos_char_end++;
                             if(file_str[j]==str[pos_star+1]){
                                for(int z=1;z<=lenght-(pos_star+2);z++){
                                    pos_char_end++;
                                    if(file_str[j+z]!=str[pos_star+z+1]){
                                        sprvisr=1;
                                        break;
                                    }
                                }
                             }
                             if(sprvisr==0 && file_str[j]==str[pos_star+1]){
                                pos_char_first=i;
                                sprvisr=2;
                                break;
                             }
                        }
                        if(sprvisr==2){
                            count++;
                            if(count==at){
                                ok=1;
                                if(!strcmp(order,"find")){
                                    printf("at:%d /pos: line:%d char:%d\n",at,pos_line,pos_char);
                                    break;
                                }
                                else if(!strcmp(order,"replace")){
                                    int z=0;
                                    char str_tmp[10000];
                                    for(int j=0;j<pos_char_first;j++){
                                        file_str2[j]=file_str[j];
                                    }
                                    strcat(file_str2,str2);
                                    for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                        str_tmp[z]=file_str[j];
                                        z++;
                                    }
                                    strcat(file_str2,str_tmp);
                                    printf("Success\n");
                                    break;
                                }
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
                if(i==ctr && count!=at){
                    printf("Invalid string\n");
                }
            }
            //5555555555555555555555555555555555555555555555
            ctr=0;
            if(case_num==5){ //case:test* text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ';j++){
                            pos_char_end++;
                        }
                        pos_char_end+=2;
                        j++;
                        if(file_str[j]==str[pos_star+2]){
                            for(int z=1;z<=lenght-(pos_star+3);z++){
                                pos_char_end++;
                                if(file_str[j+z]!=str[pos_star+2+z]){
                                    sprvisr=1;
                                    break;
                                }
                            }
                        }
                        if(sprvisr==0 && file_str[j]==str[pos_star+2]){
                            pos_char_first=i;
                            sprvisr=2;
                        }
                        if(sprvisr==2){
                            count++;
                            if(count==at){
                                ok=1;
                                if(!strcmp(order,"find")){
                                    printf("at:%d /pos: line:%d char:%d\n",at,pos_line,pos_char);
                                    break;
                                }
                                else if(!strcmp(order,"replace")){
                                    int z=0;
                                    char str_tmp[10000];
                                    for(int j=0;j<pos_char_first;j++){
                                        file_str2[j]=file_str[j];
                                    }
                                    strcat(file_str2,str2);
                                    for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                        str_tmp[z]=file_str[j];
                                        z++;
                                    }
                                    strcat(file_str2,str_tmp);
                                    printf("Success\n");
                                    break;
                                }
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
                if(i==ctr && count!=at){
                    printf("Invalid string\n");
                }
            }
            }
            //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
            if(!strcmp(feature,"byword")){
                int pos_word=1;
                lenght=strlen(str);
                if(str[0]=='*' && str[lenght-1]!='*'){ //the case with '*' at the begin
                    case_num=1;
                }
                else if(str[0]!='*' && str[lenght-1]=='*'){ //the case with '*' at the end
                    case_num=2;
                }
                else if(str[0]=='*' && str[lenght-1]=='*'){ //the case with '*' at the begin and another at the end
                    case_num=3;
                }
                else{
                    for(int i=0;i<lenght;i++){
                        if(str[i]=='*' && str[i-1]==' '){ //case:text *text
                            case_num=4;
                            pos_star=i;
                        }
                        else if(str[i]=='*' && str[i+1]==' '){ //case:text* text
                            case_num=5;
                            pos_star=i;
                        }
                        else if(str[i]=='*'){
                            case_num=4;
                            pos_star=i;
                        }
                    }
                }
            //0000000000000000000000000000000000000000000
            if(case_num==0){ //case number 0 which mean we don't have any '*' in the string
                while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]!=' ' && file_str[i-1]==' '){
                        pos_word++;
                    }
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        printf("byword: pos: line:%d word:%d\n",pos_line,pos_word);
                        break;
                    }
                    sprvisr=0;
                }
                if(i==ctr){
                    printf("Invalid string\n");
                }
            }
            //111111111111111111111111111111111111111111111111111
            ctr=0;
            if(case_num==1){ //the case with the '*' at the begin
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]!=' ' && file_str[i-1]==' '){
                        pos_word++;
                    }
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-1;j++){
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        printf("byword: pos: line:%d word:%d\n",pos_line,pos_word);
                        break;
                    }
                    sprvisr=0;
                }
               if(i==ctr){
                    printf("Invalid string\n");
               }
            }
            //2222222222222222222222222222222222222222222
            ctr=0;
            if(case_num==2){//the case with the '*' at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]!=' ' && file_str[i-1]==' '){
                        pos_word++;
                    }
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght-1;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        printf("byword: pos: line:%d word:%d\n",pos_line,pos_word);
                        break;
                    }
                    sprvisr=0;
                }
               if(i==ctr){
                    printf("Invalid string\n");
               }
            }
            //3333333333333333333333333333333333333333333333
            ctr=0;
            if(case_num==3){//the case with '*' at the begin and one another at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]!=' ' && file_str[i-1]==' '){
                        pos_word++;
                    }
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-2;j++){
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        printf("byword: pos: line:%d word:%d\n",pos_line,pos_word);
                        break;
                    }
                    sprvisr=0;
                }
               if(i==ctr){
                    printf("Invalid string\n");
               }
            }
            //444444444444444444444444444444444444444444444
            ctr=0;
            if(case_num==4){//case:text *text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]!=' ' && file_str[i-1]==' '){
                        pos_word++;
                    }
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ' && file_str[j]!=EOF;j++){
                             if(file_str[j]==str[pos_star+1]){
                                for(int z=1;z<=lenght-(pos_star+2);z++){
                                    if(file_str[j+z]!=str[pos_star+z+1]){
                                        sprvisr=1;
                                        break;
                                    }
                                }
                             }
                             if(sprvisr==0 && file_str[j]==str[pos_star+1]){
                                sprvisr=2;
                                break;
                             }
                        }
                        if(sprvisr==2){
                            printf("byword: pos: line:%d word:%d\n",pos_line,pos_word);
                            break;
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr){
                    printf("Invalid string\n");
                }
            }
            //5555555555555555555555555555555555555555555555
            ctr=0;
            if(case_num==5){ //case:test* text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char++;
                    if(file_str[i]!=' ' && file_str[i-1]==' '){
                        pos_word++;
                    }
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ';j++){
                        }
                        j++;
                        if(file_str[j]==str[pos_star+2]){
                            for(int z=1;z<=lenght-(pos_star+3);z++){
                                if(file_str[j+z]!=str[pos_star+2+z]){
                                    sprvisr=1;
                                    break;
                                }
                            }
                        }
                        if(sprvisr==0 && file_str[j]==str[pos_star+2]){
                            sprvisr=2;
                        }
                        if(sprvisr==2){
                            printf("byword: pos: line:%d word:%d\n",pos_line,pos_word);
                            break;
                        }
                    }
                    sprvisr=0;
                }
                if(i==ctr){
                    printf("Invalid string\n");
                }
            }
            }
            //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
            if(!strcmp(feature,"all")){//feature: all
                int count=0;
                int save;
                lenght=strlen(str);
                if(str[0]=='*' && str[lenght-1]!='*'){ //the case with '*' at the begin
                    case_num=1;
                }
                else if(str[0]!='*' && str[lenght-1]=='*'){ //the case with '*' at the end
                    case_num=2;
                }
                else if(str[0]=='*' && str[lenght-1]=='*'){ //the case with '*' at the begin and another at the end
                    case_num=3;
                }
                else{
                    for(int i=0;i<lenght;i++){
                        if(str[i]=='*' && str[i-1]==' '){ //case:text *text
                            case_num=4;
                            pos_star=i;
                        }
                        else if(str[i]=='*' && str[i+1]==' '){ //case:text* text
                            case_num=5;
                            pos_star=i;
                        }
                        else if(str[i]=='*'){
                            case_num=4;
                            pos_star=i;
                        }
                    }
                }
            //0000000000000000000000000000000000000000000
            if(case_num==0){ //case number 0 which mean we don't have any '*' in the string
                while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        count++;
                        ok=1;
                        pos_char_first=i;
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            memset(file_str2,0,sizeof(file_str2));
                            memset(str_tmp,0,sizeof(str_tmp));
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            strcpy(file_str,file_str2);
                            printf("Success\n");
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
                if(i==ctr && count==0){
                    printf("Invalid string\n");
                }
            }
            //111111111111111111111111111111111111111111111111111
            ctr=0;
            if(case_num==1){ //the case with the '*' at the begin
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        pos_char_first=i;
                        ok=1;
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            pos_char_first--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        count++;
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            memset(file_str2,0,sizeof(file_str2));
                            memset(str_tmp,0,sizeof(str_tmp));
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            strcpy(file_str,file_str2);
                            printf("Success\n");
                            i=i-(pos_char_end-pos_char_first+strlen(str2));
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
               if(i==ctr && count==0){
                    printf("Invalid string\n");
               }
            }
            //2222222222222222222222222222222222222222222
            ctr=0;
            if(case_num==2){//the case with the '*' at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<lenght-1;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        count++;
                        ok=1;
                        pos_char_first=i;
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            memset(file_str2,0,sizeof(file_str2));
                            memset(str_tmp,0,sizeof(str_tmp));
                            for(int j=pos_char_end;file_str[j]!=' ' && file_str[j]!='\n' && file_str[j]!=EOF;j++){
                                pos_char_end++;
                            }
                            pos_char_end--;
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            strcpy(file_str,file_str2);
                            printf("Success\n");
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
               if(i==ctr && count==0){
                    printf("Invalid string\n");
               }
            }
            //3333333333333333333333333333333333333333333333
            ctr=0;
            if(case_num==3){//the case with '*' at the begin and one another at the end
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[1]){
                        for(int j=1;j<lenght-2;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j+1]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[1]){
                        ok=1;
                        pos_char_first=i;
                        for(int z=i-1;file_str[z]!=' ' && file_str[z]!=EOF && file_str[z]!='\0' ;z--){
                            pos_char--;
                            pos_char_first--;
                            if(pos_char==0){
                                    break;
                            }
                        }
                        count++;
                        if(!strcmp(order,"find")){
                            printf("pos: line:%d char:%d\n",pos_line,pos_char);
                        }
                        else if(!strcmp(order,"replace")){
                            int z=0;
                            char str_tmp[10000];
                            memset(file_str2,0,sizeof(file_str2));
                            memset(str_tmp,0,sizeof(str_tmp));
                            for(int j=pos_char_end;file_str[j]!=' ' && file_str[j]!='\n' && file_str[j]!=EOF;j++){
                                pos_char_end++;
                            }
                            pos_char_end--;
                            for(int j=0;j<pos_char_first;j++){
                                file_str2[j]=file_str[j];
                            }
                            strcat(file_str2,str2);
                            for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                str_tmp[z]=file_str[j];
                                z++;
                            }
                            strcat(file_str2,str_tmp);
                            strcpy(file_str,file_str2);
                            printf("Success\n");
                            i=i-(pos_char_end-pos_char_first+strlen(str2));
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
               if(i==ctr && count==0){
                    printf("Invalid string\n");
               }
            }
            //444444444444444444444444444444444444444444444
            ctr=0;
            if(case_num==4){//case:text *text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ' && file_str[j]!=EOF;j++){
                             pos_char_end++;
                             if(file_str[j]==str[pos_star+1]){
                                for(int z=1;z<=lenght-(pos_star+2);z++){
                                    pos_char_end++;
                                    if(file_str[j+z]!=str[pos_star+z+1]){
                                        sprvisr=1;
                                        break;
                                    }
                                }
                             }
                             if(sprvisr==0 && file_str[j]==str[pos_star+1]){
                                sprvisr=2;
                                break;
                             }
                        }
                        if(sprvisr==2){
                            ok=1;
                            pos_char_first=i;
                            count++;
                            if(!strcmp(order,"find")){
                                printf("pos: line:%d char:%d\n",pos_line,pos_char);
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                memset(file_str2,0,sizeof(file_str2));
                                memset(str_tmp,0,sizeof(str_tmp));
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                strcpy(file_str,file_str2);
                                printf("Success\n");
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
                if(i==ctr && count==0){
                    printf("Invalid string\n");
                }
            }
            //5555555555555555555555555555555555555555555555
            ctr=0;
            if(case_num==5){ //case:test* text
               while(!feof(find)){
                    file_str[ctr]=fgetc(find);
                    ctr++;
                }
                file_str[ctr-1]='\0';
                strcpy(undo_file,file_str);
                int i=0;
                for(i;i<=ctr-1;i++){
                    pos_char_end=i;
                    pos_char++;
                    if(file_str[i]=='\n'){
                        pos_line++;
                        pos_char=-1;
                    }
                    save=pos_char;
                    if(file_str[i]==str[0]){
                        for(int j=1;j<pos_star;j++){
                            pos_char_end++;
                            if(file_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && file_str[i]==str[0]){
                        int j=i+pos_star;
                        for(j;file_str[j]!=' ';j++){
                            pos_char_end++;
                        }
                        pos_char_end+=2;
                        j++;
                        if(file_str[j]==str[pos_star+2]){
                            for(int z=1;z<=lenght-(pos_star+3);z++){
                                pos_char_end++;
                                if(file_str[j+z]!=str[pos_star+2+z]){
                                    sprvisr=1;
                                    break;
                                }
                            }
                        }
                        if(sprvisr==0 && file_str[j]==str[pos_star+2]){
                            sprvisr=2;
                        }
                        if(sprvisr==2){
                            count++;
                            pos_char_first=i;
                            ok=1;
                            if(!strcmp(order,"find")){
                                printf("pos: line:%d char:%d\n",pos_line,pos_char);
                            }
                            else if(!strcmp(order,"replace")){
                                int z=0;
                                char str_tmp[10000];
                                memset(file_str2,0,sizeof(file_str2));
                                memset(str_tmp,0,sizeof(str_tmp));
                                for(int j=0;j<pos_char_first;j++){
                                    file_str2[j]=file_str[j];
                                }
                                strcat(file_str2,str2);
                                for(int j=pos_char_end+1;file_str[j]!='\0';j++){
                                    str_tmp[z]=file_str[j];
                                    z++;
                                }
                                strcat(file_str2,str_tmp);
                                strcpy(file_str,file_str2);
                                printf("Success\n");
                            }
                        }
                    }
                    pos_char=save;
                    sprvisr=0;
                }
                if(i==ctr && count==0){
                    printf("Invalid string\n");
                }
            }
            }
        }
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
        fclose(find);
        if(!strcmp(order,"replace") && ok==1){
            find=fopen(address,"w");
            fprintf(find,"%s",file_str2);
            fclose(find);

            find=fopen(undo_address,"w");
            fprintf(find,"%s",undo_file);
            fclose(find);
        }
 }
//======================================================================================================
 else if(!strcmp(order,"grep")){//--------------------------------grep----------------------------------
        int count=0;
        int check=0;
        int lenght;
        int ctr=1; //counter for making dir
        int sprvisr=0;
        int feature=0;
        char sp2;
        char file_str[100000];
        char file_name[100];
        char str[1000]; //the string which we want to insert in to the file
        char line_str[1000]; //the string which we need to capture the array in a line
        char c1[50]; //--str
        char dir[50]; //dir
        char address[100]="C:";
        char sp; // space
        char C; //the char which we use to understand do we have extra features or not
        FILE *grep=NULL;
        scanf("%s",c1); //--str or -(feature)
        if(c1[0]=='-' && (c1[1]=='c' || c1[1]=='l')){
            if(c1[1]=='c'){
                feature=1;
            }
            else{
                feature=2;
            }
            memset(c1,0,sizeof(c1));
            scanf("%s",c1); //--str
        }
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
        }//at the end of the loop we have gotten the string by str array and the (--) chars
        scanf("%s",c1); //file
        while(1){
            scanf("%c",&sp);
            while(sp==' '){
                scanf("%c",&sp); //space between --file and /
            } //when the loop is over sp variable has captured the (/) char or the (") char
            if(sp=='"'){
                scanf("%c",&sp2); //get the (/) char
            }
            ctr=1;
            while(1){
                dir[0]='\\';
                dir[ctr]=getchar();
                if(dir[ctr]=='/'){
                    dir[ctr]='\0';
                    strcat(address,dir);
                    ctr=0;
                    memset(dir, 0, sizeof(dir));
                }
                else if(dir[ctr]=='-' || dir[ctr]=='\n'){
                    C=dir[ctr];
                    if(sp=='/'){
                        dir[ctr]='\0';
                    }
                    if(sp=='"'){
                        dir[ctr-1]='\0';
                    }
                    for(int i=0;dir[i]!='\0';i++){
                        file_name[i]=dir[i+1];
                    }
                    strcat(address,dir);
                    break;
                }
                ctr++;
            }
            grep=fopen(address,"r");
            lenght=strlen(str);
            ctr=0;
            while(!feof(grep)){
                while(1){
                    line_str[ctr]=fgetc(grep);
                    if(line_str[ctr]=='\n' || line_str[ctr]==EOF || line_str[ctr]=='\0'){
                        line_str[ctr]='\0';
                        break;
                    }
                    ctr++;
                }//we just captured a line in the file
                int i=0;
                for(i;i<=(ctr-1);i++){
                    if(line_str[i]==str[0]){
                        for(int j=1;j<lenght;j++){
                            if(line_str[i+j]!=str[j]){
                                sprvisr=1;
                                break;
                            }
                        }
                    }
                    if(sprvisr==0 && line_str[i]==str[0]){
                        check=1;
                        count++;
                        if(feature==0){
                            printf("%s: %s\n",file_name,line_str);
                        }
                        break;
                    }
                    sprvisr=0;
                }
                ctr=0;
            }
            if(check==0 && feature==0){
                printf("%s: Invalid string\n",file_name);
            }
            if(check==1 && feature==2){
                printf("%s\n",file_name);
            }
            fclose(grep);


            memset(address,0,sizeof(address));
            memset(file_name,0,sizeof(file_name));
            address[0]='C';
            address[1]=':';
            if(C=='\n'){
                break;
            }
            check=0;
        }
        if(feature==1){
            printf("%d\n",count);
        }
 }
//============================================================================================
 else if(!strcmp(order,"undo")){ //---------------------------undo----------------------------
        int ctr=1; //counter for making dir
        char sp2;
        char file_str[100000];
        char undo_file[100000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char undo_address[100]="C:\\Undo";
        char array_input[1000];
        char sp; // space
        char C; //for (:)in the pos section
        FILE *undo=NULL;
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
                strcat(undo_address,dir);
                strcat(address,dir);
                break;
            }
            ctr++;
         }
         ctr=0;
         undo=fopen(undo_address,"r");
         while(!feof(undo)){
             undo_file[ctr]=fgetc(undo);
             ctr++;
         }
         undo_file[ctr-1]='\0';
         fclose(undo);

         fopen(address,"w");
         fprintf(undo,"%s",undo_file);
         fclose(undo);
         printf("Success\n");
 }
//=================================================================================================
 else if(!strcmp(order,"auto-indent")){ //---------------------auto-indent-------------------------
        int ctr=1; //counter for making dir
        int count_tab=0;
        int line=1;
        char tab='\t';
        char aq='}';
        char enter='\n';
        char sp2;
        char file_str[100000];
        char file_str2[100000];
        char c1[50]; //--file
        char dir[50]; //dir
        char address[100]="C:";
        char array_input[1000];
        char sp; // space
        char C; //for (:)in the pos section
        FILE *auto_ind=NULL;
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
         auto_ind=fopen(address,"r");
         while(!feof(auto_ind)){
             file_str[ctr]=fgetc(auto_ind);
             ctr++;
         }
         file_str[ctr-1]='\0';
         fclose(auto_ind);
         int z=0;
         for(int i=0;i<=(ctr-1);i++){
            if(z==0){
                for(i;file_str[i]==' ';i++){
                }
            }
            array_input[z]=file_str[i];
            if(file_str[i]=='{'){
                array_input[z]='\0';
                int j=i-1;
                for(j;file_str[j]==' ';j--){
                    array_input[j-(i-z)]='\0';
                }
                if(file_str[j]=='{' || file_str[j]=='}' || file_str[j]=='\0'){
                    array_input[j-(i-z)+1]='{';
                    array_input[j-(i-z)+2]='\n';
                    array_input[j-(i-z)+3]='\0';
                }
                else{
                    array_input[j-(i-z)+1]=' ';
                    array_input[j-(i-z)+2]='{';
                    array_input[j-(i-z)+3]='\n';
                    array_input[j-(i-z)+4]='\0';
                }
                int k=i+1;
                for(k;k<=(ctr-1) && file_str[k]==' ';k++){
                }
                if(file_str[k]!='}'){
                    count_tab++;
                }
                for(int k=1;k<=count_tab;k++){
                    strncat(array_input,&tab,1);
                }
                if(line==1){
                    strcpy(file_str2,array_input);
                }
                else{
                    strcat(file_str2,array_input);
                }
                memset(array_input,0,sizeof(array_input));
                line++;
                z=-1;
            }
            else if(file_str[i]=='}'){
                array_input[z]='\0';
                int j=i-1;
                for(j;file_str[j]==' ';j--){
                    array_input[j-(i-z)]='\0';
                }
                if(file_str[j]=='{'){
                    array_input[j-(i-z)+1]='\0';
                }
                else{
                    array_input[j-(i-z)+1]='\n';
                    array_input[j-(i-z)+2]='\0';

                    count_tab--;
                    for(int k=1;k<=count_tab;k++){
                        strncat(array_input,&tab,1);
                    }
                }
                strncat(array_input,&aq,1);
                strncat(array_input,&enter,1);
                strcat(file_str2,array_input);
                memset(array_input,0,sizeof(array_input));
                line+=2;
                z=-1;
            }
            if(file_str[i]=='\n'){
                for(int j=1;j<=count_tab;j++){
                    strncat(array_input,&tab,1);
                }
                strcat(file_str2,array_input);
                memset(array_input,0,sizeof(array_input));
                z=-1;
                line++;
            }
            z++;
         }
         auto_ind=fopen(address,"w");
         fprintf(auto_ind,"%s",file_str2);
         fclose(auto_ind);
         printf("Success\n");
 }
//============================================================================================
 else if(!strcmp(order,"compare")){ //----------------------compare---------------------------
        int line=1;
        int check=0;
        int lenght;
        int ctr=1; //counter for making dir
        int sprvisr=0;
        int line_num1=1;
        int line_num2=1;
        int line_max;
        char sp2;
        char file_str1[100000];
        char file_str2[100000];
        char file_name1[100];
        char file_name2[100];
        char str[1000]; //the string which we want to insert in to the file
        char line_str1[1000]; //the string which we need to capture the array in a line
        char line_str2[1000];
        char c1[50]; //--str
        char dir[50]; //dir
        char address1[100]="C:";
        char address2[100]="C:";
        char sp; // space
        char C; //the char which we use to understand do we have extra features or not
        FILE *comp=NULL;
        scanf("%s",c1); //--file
        ctr=1;
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
                strcat(address1,dir);
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
                for(int i=0;dir[i]!='\0';i++){
                    file_name1[i]=dir[i+1];
                }
                strcat(address1,dir);
                break;
            }
            ctr++;
         }//at the end of the loop we have captured the address of first file
         ctr=1;
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
                strcat(address2,dir);
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
                for(int i=0;dir[i]!='\0';i++){
                    file_name2[i]=dir[i+1];
                }
                strcat(address2,dir);
                break;
            }
            ctr++;
         }//at the end of the loop we have captured the address of second file
        comp=fopen(address1,"r");
        ctr=0;
        while(!feof(comp)){
            file_str1[ctr]=fgetc(comp);
            ctr++;
        }
        file_str1[ctr-1]='\0';
        fclose(comp);
        for(int i=0;i<=(ctr-1);i++){
            if(file_str1[i]=='\n'){
                line_num1++;
            }
        }

        comp=fopen(address2,"r");
        ctr=0;
        while(!feof(comp)){
            file_str2[ctr]=fgetc(comp);
            ctr++;
        }
        file_str2[ctr-1]='\0';
        fclose(comp);
        for(int i=0;i<=(ctr-1);i++){
            if(file_str2[i]=='\n'){
                line_num2++;
            }
        }
        if(line_num1>line_num2){
            line_max=line_num1;
        }
        else{
            line_max=line_num2;
        }
        int z1=0;
        int z2=0;
        int i=0;
        int j=0;
        while(line<=line_max){
            for(i;file_str1[i]!='\n' && file_str1[i]!='\0';i++){
                line_str1[z1]=file_str1[i];
                z1++;
            }
            i++;
            line_str1[z1]='\0';
            z1=0;
            for(j;file_str2[j]!='\n' && file_str2[j]!='\0';j++){
                line_str2[z2]=file_str2[j];
                z2++;
            }
            j++;
            line_str2[z2]='\0';
            z2=0;
            if((line_num1>line_num2 && line>line_num2) ||(line_num1<line_num2 && line>line_num1)){
                if(check==0){
                    if(line_num1>line_num2){
                        printf("<<<<<<<<<<<<<<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<<<<<<<<<<<<<<\n",line_num2+1,line_num1);
                    }
                    else if(line_num2>line_num1){
                        printf(">>>>>>>>>>>>>>>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>>>>>>>>>>>>>>\n",line_num1+1,line_num2);
                    }
                    check=1;
                }
                if(line_num2==line_max){
                    printf("%s\n",line_str2);
                }
                else if(line_num1==line_max){
                    printf("%s\n",line_str1);
                }
            }
            if(strcmp(line_str1,line_str2)!=0 && line_str1[0]!='\0' && line_str2[0]!='\0'){
                printf("========================= #%d ========================= \n%s:%s\n%s:%s\n",line,file_name1,line_str1,file_name2,line_str2);
            }
            memset(line_str1,0,sizeof(line_str1));
            memset(line_str2,0,sizeof(line_str2));
            line++;
        }
 }
//============================================================================================
 else if(!strcmp(order,"tree")){//-------------------------tree-------------------------------
    int depth_input;
    char address[100]="C:\\root";
    scanf("%d",&depth_input);
    if(depth_input<-1){
        printf("Invalid depth\n");
    }
    else{
        tree(address,depth_input);
    }
 }
//============================================================================================
 else if(!strcmp(order,"exit")){//--------------------------exit------------------------------
    printf("The program ended");
    break;
 }
//============================================================================================
 else{ //-----------------------------------Invalid order-------------------------------------
    char chert[100];
    gets(chert);
    printf("Invalid order\n");
 }
//===========================================================================================
scanf("%s",order);
}
 return 0;
}
