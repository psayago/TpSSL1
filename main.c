#include <stdio.h>
#include <stdlib.h>

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);



int main(void){
    char command[] = ".\\GnuWin32\\bin\\wget -q --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O - http://52.67.191.9/SSL/lideres-bcba.html";
    printf("%s\n", command);
    FILE *cmd = popen(command, "r");
    FILE *fpuntero;
    char sig;
    char cadena[]="<table id=\"tbAcciones\"";
    char cadena2[]="</table>";
    int i=0;
    int flag=0;

    char result[1024]; //1 MB de buffer
    fpuntero = fopen("test.html","w");
    int T;
    char *str = (char *) malloc(sizeof(char)*T);

    fprintf(fpuntero,"%s","<html><head></head><body>");
//
    sig=getc(cmd);
    while(sig!=EOF){

        while(((cadena[i])==sig)&&(flag==0)){
            i++;
            if((cadena[i])=='\0'){
               flag=1;
               printf("%s",cadena);
               fprintf(fpuntero,"%s",cadena);
            }
            sig=getc(cmd);
        }/**INICIO DE LA TABLA**/
        i=0;
        while(((cadena2[i])==sig)&&(flag==1)){
            if ((cadena2[i])==sig){
               i++;
               if((cadena2[i])=='\0'){
                     flag=0;
               }
             }
             printf("%c",sig);
             putc(sig,fpuntero);
             sig=getc(cmd);
        }if(flag==1){
             printf("%c",sig);
             putc(sig,fpuntero);
        }
        sig=getc(cmd);
    }
    fprintf(fpuntero,"%s","</body></html>");

    printf("%d\n",flag);

    fclose(fpuntero);
    pclose(cmd);

    fpuntero= fopen("test.html","r");
    if (fpuntero==NULL){
        printf("Error al intentar abrir el archovo");
        return 1;
    }
    fclose(fpuntero);
    return 0;
}

