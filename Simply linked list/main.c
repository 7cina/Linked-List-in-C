
#include<stdio.h>
#include<stdlib.h>

typedef struct maillon {
int valeur ;
struct maillon * suivant ;
}LSC;
//1°
LSC * AllouerNoeud()
{
    LSC * nv_elem;
    nv_elem=(LSC*)malloc(sizeof(LSC));
    if(nv_elem==NULL) {printf("Memoire insuffisante\n"); exit(-1);}
    else {nv_elem->suivant=NULL; 
         return nv_elem;
         }
         }
//2°
LSC * inserer_tete(LSC * L, int nv){

LSC * q;
q=AllouerNoeud();
q->valeur=nv ;
if(L==NULL){L=q;}
else {q->suivant=L ; L=q;}

return L;}
//3°
LSC * inserer_fin(LSC * L,int nv){

LSC * q ,*courant ;
q=AllouerNoeud();
q->valeur= nv;
if(L==NULL){L=q;}
else {
for(courant=L;courant->suivant!=NULL ;courant=courant->suivant);

courant->suivant=q ;}

return L;}
//4°
int somme(LSC *L)
{
    int S=0;
    LSC *courant;
    for(courant=L;courant;courant=courant->suivant)
    { S+=courant->valeur; }
    return S;
}
//5°
LSC *supprimer(LSC *L)
{
    LSC * courant=L,*Pred,*elem_supp;
    
    while(courant)
    {
                  if(courant->valeur>=0){Pred=courant;courant=courant->suivant;}
                  else {elem_supp=courant;
                       if(courant==L){L=courant->suivant;courant=L;}
                       else {Pred->suivant=courant->suivant; courant=courant->suivant;}
                       free(elem_supp);
                       }
                       }
                       return L;
                       }
    
//6°

void afficher(LSC *L)
{
     LSC *courant=L;
     while(courant!=NULL)
     { printf("%d  ",courant->valeur);
     courant=courant->suivant;
     }
     printf("\n");
}                        
//7°

void enregistrer(LSC *L, char *nom_fich)
{ FILE *F;LSC *q=L;
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
{ LSC *L; char nom_fichier[20];
      L=NULL;
      L=inserer_fin(L,10);
      L=inserer_fin(L,20);
      L=inserer_fin(L,30);
      L=inserer_fin(L,100);
      afficher(L);
      printf("La somme des element de la liste est %d.\n",somme(L));
      L=supprimer(L);
      printf("\n");
      afficher(L);
      printf("Donner le nom de fichier:");
      scanf("%s",nom_fichier);
      enregistrer(L,nom_fichier);
      
      system("pause");
      }
      
