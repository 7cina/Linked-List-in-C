#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct{
        float coef;
        int exp;
        }Monome;

typedef struct element{
        Monome M;
        struct element * suivant;
        struct element * precedent;
                       }Poly;

//Q1
Monome lire_monome()
{
       Monome A;
       printf("Donner le coef"); scanf("%f",&A.coef);
       printf("Donner l exposant"); scanf("%d",&A.exp);
       return A;
       }

//Q2
Poly * AllouerNoeud()
{Poly *q;
q=(Poly*)malloc(sizeof(Poly));
if(q==NULL) {printf("Memoire insuffisante\n");
                             exit(-1);
                             }
else { q->suivant=NULL;
	   q->precedent=NULL;
       return q;
       }
}

//Q3
Poly * supprimer_monome_null( Poly *P)
 {
 Poly * elem_supp ;
 Poly * courant =P; // parcouririre la liste

while ( courant != NULL )
 {
 	if ( courant ->M.coef !=0) { courant = courant -> suivant ;}
 	else { elem_supp = courant ;
 				// suppression au debut
 					if( courant ==P){ if( courant -> suivant != NULL )
 								{ courant -> suivant -> precedent = NULL ;
 									P= courant -> suivant ; courant =P;}
									else { free ( elem_supp ); return NULL;}
 									}
 					else if ( courant -> suivant == NULL )// suppression à la fin
 					{ courant -> precedent -> suivant = NULL ; courant = courant ->precedent ;}
 							// suppression a une position quelconque
 						else { courant -> precedent -> suivant = courant -> suivant ;
 							courant -> suivant -> precedent = courant -> precedent ;
 							courant = courant -> suivant ;
 							}
 		free ( elem_supp );
		 }
	}
 return P;
}

//Q4
Poly * ajouterMonome(Poly * P ,Monome m1){
     Poly *q;
     q=AllouerNoeud();
     q->M=m1;

    if (P==NULL ) return q;
    else {
                if ( m1.exp > P->M.exp ) { // insertion au debut du polynome
                q->suivant=P;P-> precedent =q;
                P=q;
                return P;
                }
                if ( m1.exp == P->M.exp ) { // insertion au debut du polynome avec exp du monome egal expo debut
                P->M.coef += m1.coef;
                P=supprimer_monome_null(P);return P;
                }
        else { // insertion ailleurs
                Poly * courant = P;
                while ( courant->suivant != NULL && courant->suivant->M.exp > m1.exp )
                        courant = courant->suivant;

                if ( courant->suivant != NULL && courant->suivant->M.exp == m1.exp )
                {courant->suivant->M.coef += m1.coef;P=supprimer_monome_null(P);}
                else { if ( courant->suivant == NULL) {// insertion fin
						q->precedent=courant; courant->suivant = q;}
                		else{ // insertion milieu
                    		q->suivant=courant->suivant;
                    		q->precedent=courant;
                    		courant->suivant = q;
                    		courant->suivant->precedent=q;
                    		}
                     }
                return P;
            }
}
}


//Q5 ==> P(1)=30
float evaluer(Poly * P, float x)
{
      Poly * courant=P;
      float S=0;
      while(courant)
      {
                    S+=(courant->M.coef)*pow(x,courant->M.exp);
                    courant=courant->suivant;
      }
return S;
}


//Q6 ==> affichage polynome
void affichage_polynome(Poly * P) {
     if (P==NULL) printf("vide.\n");
     Poly *p=P;
while (p != NULL) {
      if (p->M.exp > 1) {
                   printf("%.2fX^%d", p->M.coef, p->M.exp);
      } else {
             if (p->M.exp == 1)
             printf("%.2fX", p->M.coef);
             else
                 printf("%.2f", p->M.coef);
             }
      p = p->suivant;
if (p != NULL) printf(" + ");

}
printf("\n");
}


// Q7==> calculer le dérivé
Poly * deriver_Polynome( Poly * P ){

    Poly * courant = P;
    Poly * derive = NULL;

    Monome m;

    while ( courant != NULL ) {

        m.coef= (courant->M.coef) *(courant->M.exp);
        m.exp= courant->M.exp-1;

        if ( courant->M.exp != 0 ) derive=ajouterMonome(derive,m);

        courant = courant->suivant;

        }
    return derive;
}

// Q8 ==>détruire
Poly* detruire_polynome(Poly * P) {
     Poly *elem_supp,*courant=P;
     while (courant != NULL) {
              elem_supp = courant;
              courant=courant->suivant;
              free(elem_supp);
              }
     return courant;
}

// Q9
main()
{
Poly *P1=NULL,*D1=NULL;
float r;
Monome m1={15,6};
Monome m2={7,4};
Monome m3={5,2};
Monome m4={3,0};

P1=ajouterMonome(P1,m1);
P1=ajouterMonome(P1,m2);
P1=ajouterMonome(P1,m3);
P1=ajouterMonome(P1,m4);



affichage_polynome(P1);

D1=deriver_Polynome(P1);
affichage_polynome(D1);

r=evaluer(P1,1);
printf("P(1)=%.2f\n",r);

P1=detruire_polynome(P1);
affichage_polynome(P1);

system("pause");
}

