#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	    int mois;
	    int annee;
} Edition;

typedef struct {
	    int code;
	    char titre[30];
	    char specialite[30];
	    char auteur[30];
	    Edition edit;
} Livre;

typedef struct element{
        Livre Liv;
        struct element *suivant;
        } Liste;
// Cette fonction permet de lire les données d'un livre puis le retourner
Livre Lire_livre(){
		Livre A;
		printf("Code : ");
		scanf("%d",&A.code);
		printf("Titre :");
		scanf("%s",A.titre);
		printf("Specialite : ");
		scanf("%s",A.specialite);
		printf("Auteur :");
		scanf("%s",A.auteur);
		printf("Edition (mois/annee) : ");
		scanf("%d %d",&A.edit.mois,&A.edit.annee);
	return A;
}
// Cette fonction permet d'allouer de l'espace mémoire pour un element de liste
Liste * AllouerNoeud()
{
        Liste * L;
        L=(Liste*)malloc(sizeof(Liste));
        if (L==NULL) {printf("Memoire insuffisante\n");
        exit(-1);
        }else{
              L->suivant=NULL;

              return L;
              }

        }

// inserer au début de la liste
Liste * inserer_debut(Liste *L, Livre nv)
{
        Liste *q;
        q=AllouerNoeud();
        q->Liv=nv;
        if(L==NULL)  L=q;
        else {q->suivant=L; L=q;}
        return L;}
// Cette fonction permet de retourner le dernier element de la liste
Liste * dernier(Liste *L)
{
        Liste *q=L;
        while (q->suivant!=NULL)
        {
              q=q->suivant;
              }
        return q;
}
// inserer à la fin de la liste
Liste * inserer_fin(Liste *L, Livre nv)
{
        Liste *q,*d;
        q=AllouerNoeud();
        q->Liv=nv;
        if(L==NULL)  L=q;
        else {d=dernier(L); d->suivant=q;}
        return L;
}

void affichage(Liste *L)
{
     if (L==NULL) printf("Liste vide.\n");
     else {
     Liste *q=L; // pour parcourire la liste en avant
     printf("Affichage de la liste en avant:\n");

     while(q)
     {
printf("%d\t %s\t %s\t  %s\t edition %d\t %d\n",q->Liv.code,q->Liv.titre,
q->Liv.specialite,q->Liv.auteur,q->Liv.edit.mois,q->Liv.edit.annee);
     q=q->suivant;}

  }
}

//Suppression des livres dont l'auteur = nom_auteur
Liste * supprimer(Liste * L,char * nom_auteur){
Liste *courant,*elem_supp;
Liste *Pred; // Garder l'adresse de l'element precedent, pendant le parcours
courant=L;

 	while(courant!=NULL)
 	{
 	if(strcmp(courant->Liv.auteur,nom_auteur)!=0) courant=courant->suivant;
 	else {elem_supp=courant;
              if(courant==L){L=courant->suivant; courant=L;}
              else {Pred->suivant=courant->suivant;
                    courant=courant->suivant;
                    }

            free(elem_supp);
            }
 	}

 	return L;
}

//comparer 2 edition selon l'année et le mois
int comparer_edit(Edition X, Edition Y){
	if (X.annee<Y.annee) return -1;
	else
	{
		if (X.annee>Y.annee) return 1;
		else
		{
			if(X.mois<Y.mois) return -1;
	   		else
	      		if (X.mois>Y.mois) return 1;
	      	    else return 0	;
		}
	}
}

//parcourir la liste courant1 et courant2
Liste * Tri_liste(Liste * L){
if(L!=NULL)
   {
	    Liste *courant1,*courant2,*min;
		Livre aux;

for (courant1=L; courant1->suivant != NULL; courant1=courant1->suivant)
		{
		min=courant1;
for (courant2=courant1->suivant; courant2 != NULL; courant2=courant2->suivant)
			{
				if (comparer_edit(min->Liv.edit,courant2->Liv.edit)==1)
					min=courant2;
			}
			if (min != courant1)
			{
				aux=courant1->Liv;
				courant1->Liv=min->Liv;
				min->Liv=aux;
            }
		}
   }
   return L;
}

void diviser(Liste * L, Liste ** L1, Liste ** L2) {

     if(L!=NULL)
     {
		 Liste *courant=L;

	     while(courant!=NULL)
	     {

   if(strcmp(courant->Liv.specialite,"mathematique")==0)
	                  {
   *L1=inserer_debut(*L1, courant->Liv);//ou utiliser inserer_fin;
	                  }
   if(strcmp(courant->Liv.specialite,"physique")==0)
	                  {
   *L2=inserer_debut(*L2, courant->Liv);//ou utiliser inserer_fin;
	                  }

	            courant=courant->suivant;
	     }
     }
}

void enregistrer(Liste *L, char *nom_fichier)
{
     FILE * F;
     F=fopen(nom_fichier,"w");
     Liste *q=L;
    while(q!=NULL )
    {
    fprintf(F,"%d %s %s %s edition %d %d\n",q->Liv.code,q->Liv.titre,
    q->Liv.specialite,q->Liv.auteur,q->Liv.edit.mois,q->Liv.edit.annee);
                           q=q->suivant;
                           }
    fclose(F);
 }
 main()
{
      Liste *L=NULL,*L1=NULL,*L2=NULL;
      char nom_fichier[30],nom_auteur[20];
      Livre A;
      int choix;


      do{

fflush(stdin); //Vide le tampon clavier avant de poser la question
          printf("Saisir votre choix :\n");
          printf("1 : pour inserer debut.\n");
          printf("2 : pour inserer fin.\n");
          printf("3 : pour Afficher.\n");
          printf("4 : pour supprimer un livre donner.\n");
          printf("5 : pour Diviser en 2 sous listes.\n");
          printf("6 : pour un tri croissant des livres.\n");
          printf("7 : pour Enregistrer la liste dans un fichier texte.\n");
          printf("8 : pour arreter.\n");

          scanf("%d",&choix);
          switch(choix)
          {
case 1 : A=Lire_livre();L=inserer_debut(L,A); break;
case 2 : A=Lire_livre(); L=inserer_fin(L,A); break;
case 3 : affichage(L); break;
case 4 : printf("Donner le nom d auteur du livre a supprimer:\n");
         scanf("%s",nom_auteur);L=supprimer(L,nom_auteur); break;
case 5 : diviser(L,&L1,&L2);
         printf("liste L1 Mathematique :\n");affichage(L1);
         printf("liste L2 Physique :\n");affichage(L2);break;
case 6 : L=Tri_liste(L);affichage(L); break;
case 7 : printf("Enregistrement dans un fichier.\n");
         printf("Donner le nom de fichier :");
         scanf("%s",nom_fichier);enregistrer(L,nom_fichier); break;
case 8 : printf("Fin programme.\n"); break;
default : printf("Choix invalide\n");
                       }

               }while(choix!=8);
      system("pause");
      }
