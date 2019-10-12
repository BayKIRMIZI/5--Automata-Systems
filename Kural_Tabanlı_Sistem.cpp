#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
typedef struct kelimeler
{
   char k[100];
   struct kelimeler *sonraki;
} klm;
klm *bas=NULL,*son=NULL,*gecici=NULL,*yeni;
FILE *dsy;
int tkr=0;

int arama(char gelen[100])
{
    gecici=bas;
    while(gecici!=son)
    {
           if(strcmp(gecici->k,gelen)==0)
                     return 1;      
                     gecici=gecici->sonraki;               
    }
    if(strcmp(son->k,gelen)==0)
              return 1;
    return 0;                     
}

void ekle(char gelen[100])
{
     if(bas==NULL)
     {
            yeni =(klm*)malloc(sizeof(klm));
            strcpy(yeni->k,gelen);
            bas=yeni;
            son=yeni;
     }
     else if(arama(gelen)==0)
     {
            yeni =(klm*)malloc(sizeof(klm));
            strcpy(yeni->k,gelen);
            son->sonraki=yeni;
            son=yeni;            
     } 

}

int kelimeuret(char basek[100],char trm ,int ustknm,int drn)
{
            char us,oku,ek[1],yn[100];
            int knm=0,kont,ust;
            fseek(dsy,0,SEEK_SET);
            oku=fgetc(dsy);           
            while(oku!=trm&&!feof(dsy))
            {      
                   while(oku!=','&&!feof(dsy))
                   {
                           knm=knm+1;             
                           oku=fgetc(dsy);
                   }     
                   knm=knm+1;             
                   oku=fgetc(dsy); 
                   if(oku==trm)
                           break;          
                     
            }
            if(oku!=trm)
            {
                    printf("\n %s terminali tanýmlanmamistir ",trm);
                    getch();
                    exit(1);
            }
            knm=knm+3;
            
            fseek(dsy,knm,SEEK_SET);
            oku=fgetc(dsy);
            while(oku!=','&&!feof(dsy))
            {
                    kont=0;
                    ust=ustknm;
                    strcpy(yn,basek);                    
                    while(oku!=','&&oku!='|'&&!feof(dsy))
                    {
                           if(drn>7)
                           {
                           
                                       ekle("...sonsuz dongu...");
                                       tkr=1;
                                       break;
                                       
                           }
                           else if(65<=oku&&oku<=90)
                           {
                                   knm=kelimeuret(yn,oku,knm,drn+1);
                                   kont=1;
                           }
                           else
                           {
                                   ek[0]=oku;
                                   ek[1]='\0'; 
                                   strcat(yn,ek);
                           }
                           knm=knm+1;
                           fseek(dsy,knm,SEEK_SET);
                           oku=fgetc(dsy);
                    } 
                    ust=ust+1;
                    fseek(dsy,ust,SEEK_SET);
                    us=fgetc(dsy);
                    while(us!=','&&us!='|'&&!feof(dsy)&&trm!='S'&&tkr==0)
                    {
                           if(65<=us&&us<=90)
                           {
                                   ust=kelimeuret(yn,us,ust,drn+1);
                                   kont=1;
                           }
                           else
                           {
                                   ek[0]=us;
                                   ek[1]='\0'; 
                                   strcat(yn,ek);
                           } 
                           ust=ust+1;
                           fseek(dsy,ust,SEEK_SET);
                           us=fgetc(dsy);
                    }                                         
                    if(kont==0&&tkr==0)
                           ekle(yn);
                    if(trm=='S')
                           basek[0]='\0';  
                    fseek(dsy,knm,SEEK_SET);
                    oku=fgetc(dsy);      
                    if(oku!=','&&!feof(dsy))
                    {
                           knm=knm+1;
                           fseek(dsy,knm,SEEK_SET);
                           oku=fgetc(dsy);
                    }                                       
            }
            return ust-1;    
}

int main()
{
    char basek[100];
    if((dsy=fopen("dosyam.txt", "r"))==NULL)
    {
          printf("dosya acilamiyor \n");
          getch();
          exit(1);
    }
    basek[0]='\0';

    kelimeuret(basek,'S',0,0);
    gecici=bas;
    while(gecici!=son)
    {
                      printf("\n - %s ",gecici->k);
                      gecici=gecici->sonraki;
    }
    if(son!=NULL)
          printf("\n - %s ",son->k);
    getch();    
}
