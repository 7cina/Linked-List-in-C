#include<stdio.h>
#include<stdlib.h>

typedef struct maillon {
int valeur ;
struct maillon * suivant ;
struct maillon * precedent ;
}LDC;
//1°
LDC * AllouerNoeud()
{
    LDC * nv_elem;
    nv_elem=(LDC*)malloc(sizeof(LDC));
    if(nv_elem==NULL) {printf("Memoire insuffisante\n"); exit(-1);}
    else {nv_elem->suivant=NULL; 
          nv_elem->precedent=NULL;
         return nv_elem;
         }
         }
         
//2°
LDC * inserer_tete(LDC * L, int nv){

LDC * q;
q=AllouerNoeud();
q->valeur=nv ;
if(L==NULL){L=q;}
else {q->suivant=L ; L->precedent=q;L=q;}

return L;}

//6°

void afficher(LDC *L)
{
     LDC *courant=L;
     while(courant!=NULL)
     { printf("%d  ",courant->valeur);
     courant=courant->suivant;
     }
     printf("\n");
}   

//3°
LDC * inserer_fin(LDC * L,int nv){

LDC * q ,*courant ;
q=AllouerNoeud();
q->valeur= nv;
if(L==NULL){L=q;}
else {
for(courant=L;courant->suivant!=NULL ;courant=courant->suivant);

courant->suivant=q ;q->precedent=courant;}

return L;}


//5°
LDC *supprimer(LDC *L)
{
    LDC * courant=L,*elem_supp;
    
    while(courant)
    {
                  if(courant->valeur>=0){courant=courant->suivant;}
                  else {elem_supp=courant;
                       if(courant==L){ if(courant->suivant!=NULL) {
                                       courant->suivant->precedent=NULL;
                                       L=courant->suivant;
                                       courant=L;}
                                       else{free(elem_supp); return NULL;}
                                       }
                       else if (courant->suivant==NULL) {courant->precedent->suivant=NULL;
                       courant=courant->precedent;
                       }
                  else {
                       courant->precedent->suivant=courant->suivant;
                       courant->suivant->precedent=courant->precedent;
                       courant=courant->suivant;
                       }
                                                           
                       
                       free(elem_supp);
                       }
                       }
                  return L;
                  }
    
                  
//7°

void enregistrer(LDC *L, char *nom_fich)
{ FILE *F;LDC *q=L;
F=fopen(nom_fich,"w");
if(F==NULL) printf("probleme d overture de fichier\n");
else {

while(q)
{
        fprintf(F,"%d\t",q->valeur);
        q=q->suivant;
        }

fclose(F);}
}


                              
                  
main()
{ LDC *L; char nom_fichier[20];
      L=NULL;
     
      L=inserer_fin(L,11);
      L=inserer_fin(L,222);
      L=inserer_fin(L,4444);
      L=inserer_fin(L,333);
      afficher(L);
      
      
      L=supprimer(L);
      printf("\n");
      afficher(L);
      printf("Donner le nom de fichier:");
      scanf("%s",nom_fichier);
      enregistrer(L,nom_fichier);
      
      system("pause");
      }
      
