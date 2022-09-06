#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//1. les structures
typedef struct {
       char code[12];
       char nom[20];
       char prenom[20];
       float note;
       }Etudiant;

typedef struct element{
        Etudiant E;
        struct element * suivant;
        }Liste;
//Fonction auxiliare
Etudiant lire_etudiant()
{
         Etudiant e;
         printf("Donner le code :");scanf("%s",e.code);
         printf("Donner le nom :");scanf("%s",e.nom);
         printf("Donner le prenom :");scanf("%s",e.prenom);
         printf("Donner la note :");scanf("%f",&e.note);
         return e;
}

//2. Fonction pour PreparerNoeud
Liste * PreparerNoeud(Etudiant E1)
{
        Liste * Noeud ;
        Noeud=(Liste*)malloc(sizeof(Liste));
        if (Noeud==NULL) {printf("Memoire insuffisante\n");
        exit(-1);
        }else{
              Noeud->E=E1;
              Noeud->suivant=NULL;
              return Noeud;
              }

        }

// Fonction auxiliaire utilisée pour atteindre la fin de la liste
Liste * dernier(Liste *L)
{
        Liste *q=L;
        while (q->suivant!=NULL)
        {
              q=q->suivant;
              }
        return q;
}

//3. Fonction pour insérer en queue de la liste
Liste * inserer_fin(Liste *L, Etudiant e)
{
        Liste *q,*d;
        q=PreparerNoeud(e);
        if(L==NULL)  L=q;
        else {d=dernier(L); d->suivant=q;}
        return L;}

//4. Fonction qui dmodifie un étudiant dans la liste
Liste* modifier(char *Old_code,Etudiant e,Liste *L)
{
        Liste *q=L;
        while(q!=NULL) {
                       if(strcmp(q->E.code,Old_code)==0)   q->E=e;

                       q=q->suivant;}
    return L;
}
//5. Fonction diviser
void diviser(Liste *L, Liste **L1, Liste **L2)
{
 Liste *courant=L;

	  if (courant==NULL) printf("la classe est vide \n");
	  else {
	        while(courant!=NULL)
			{

	            if (courant->E.note>=10)
					*L1=inserer_fin(*L1,courant->E);
	            else
					*L2=inserer_fin(*L2,courant->E);
	            courant=courant->suivant;
	        }
	  }

}
//6. Trier les étudiants admis
Liste * Tri_liste(Liste * L){
if(L!=NULL)
   {
	    Liste *courant1,*courant2,*max;
		Etudiant aux;

for (courant1=L; courant1->suivant != NULL; courant1=courant1->suivant)
		{
		max=courant1;
for (courant2=courant1->suivant; courant2 != NULL; courant2=courant2->suivant)
			{
				if (max->E.note<courant2->E.note)
					max=courant2;
			}
			if (max != courant1)
			{
				aux=courant1->E;
				courant1->E=max->E;
				max->E=aux;
            }
		}
   }
   return L;
}
//7. affichage normale de la liste
void affichage(Liste *L)
{
     printf("Affichage de la liste :\n");
     Liste *q=L;
     while(q)
     {
printf("%s\t %s\t %s\t  %.2f\t \n",q->E.code,q->E.nom,q->E.prenom,q->E.note);
     q=q->suivant;}
}

main()
{
      Liste *L=NULL;
      Liste *L1=NULL,*L2=NULL;
      int choix;
      Etudiant e;char Old_code[12];
      do{
          //printf("Donner un entier");scanf("%d",&a);
          //scanf("%d",&a);
          fflush(stdin); //Vide le tampon clavier avant de poser la question\n
          printf("Saisir votre choix :\n");
          printf("1: pour inserer a la fin de la liste.\n");
          printf("2: Modifier les infos d un etudiant .\n");
          printf("3: Diviser la classe en deux groupes.\n");
          printf("4: Trier les etudiants admis.\n");
          printf("5: Affichage de la listes des etudiants.\n");
          printf("6: Pour arreter.\n");
          scanf("%d",&choix);
          switch(choix)
          {


case 1 : e=lire_etudiant();
         //N=PreparerNoeud(e);
         L=inserer_fin(L,e);break;
case 2 : printf("Donner le code de l etudiant a modifier :");
scanf("%s",Old_code);printf("Les infos du nouveau etudiant :");
         e=lire_etudiant();
L=modifier(Old_code,e,L);break;
case 3 : diviser(L,&L1,&L2);affichage(L1);affichage(L2);break;
case 4 : L1=Tri_liste(L1);affichage(L1);break;
case 5 : printf("Affichage de la liste : \n");
         if (L==NULL) printf("Liste vide\n");else affichage(L);break;
case 6 : printf("Fin programme.\n"); break;
default : printf("Choix invalide\n");
                       }

               }while(choix!=6);


      return 0;
      }


