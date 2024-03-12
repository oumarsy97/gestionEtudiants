#include "monbibliotheque.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  //cumulRetarsMois(3,2024);
  
    int choix;
    int con,decon=0;
    
        Classe classe={3, "Dev Data"};
       //enregistrerClasses( "classes.bin",classe);
       //listeClasses( "classes.bin");

      //  Classe c = diokhClasse(3);
      //  printf("%s\n", c.libelle);
       int tab[100],nb_etudiants=0;
       //les_mat(tab, &nb_etudiants);
      // rechercher_etudiants_par_id(2,tab, &nb_etudiants);
     //
     // messageClasse(1);
    // lireMessage(100);

    Etudiant etudiant = {104,"etudiant4","Ousmane", "Ndiaye", 2, 1, 0};
    //addEtudiant( "etudiants.txt", etudiant);
   //  User user = {"etudiant", "etudiant", 0};
   //  char hashedPassword[65];
   //      hashPassword(user.password, hashedPassword);
       
   //enregistrerUser(user);
    char password[20];
    int i = 0;
    char ch;
    char login[20];
   do{ 
      
   do
   {
    
   con = connexion(login);
    if(con != 1 && con != 0) printf("\nIdentifiants incorrects Veuillez reessayer\n");
   } while (con != 1 && con != 0);



do{

   if (con == 1){
    
      int choix = menuAdmin();
    if(choix == 1){
      int choix2;
     choix2 = menuGestionEtudiant();
     if(choix2 == 1){
       ajouterNouveauEtudiant();
       printf("Etudiant ajouté avec succes \n");
     }
     if (choix2 == 2){
      int mat;
      do{
      printf("Saisissez le matricule de l'apprenant que vous souhaitez modifier : \n");
      scanf("%d",&mat);
      if(!verifieMatricule(&mat)) printf("Matricule invalide \n");
      }while(!verifieMatricule(&mat));
       modifierApprenant("etudiants.txt", verifieMatricule(&mat), etudiant);
       printf("Etudiant modifié avec succes \n");
     }
     if (choix2 == 3){
      int mat,c;
      do{
        printf("Saisissez le matricule de l'apprenant que vous souhaitez supprimer : \n");
        scanf("%d",&mat);
        if(!verifieMatricule(&mat)) printf("Matricule invalide \n");

      }while(!verifieMatricule(&mat));
      printf(" vous etes sur de vouloir supprimer l'apprenant %d \n", mat);
      printf("Appuyer sur 1 pour confirmer ");
      scanf("%d",&c);
      if(c == 1)
       supprimerApprenant("etudiants.txt", mat);

     }
    }

     else if (choix == 2){
      int choix3 = menuFichier();
         if (choix3== 1) {afficherTous() ;
         printf(" fichier de presence generer avec succes  \n");
         }

       if(choix3 == 2) {
       afficherAuneDate( verifieDate());
       };
       if(choix3 == 3){
        cumulRetards();
       }
       
    }

     else if (choix == 3){
         addPresenceAdmin( login);
     }
     
      else if(choix == 4){
        int c4 = sousMenu4() ;
          if(c4 == 1){
            messageaTous();
          };
          if(c4 == 2){
            int idclasse = listeClasses( "classes.bin");
            messageClasse(idclasse);
          };
          if(c4 == 3){
            messageAdesEtudiants();
          };
          
     }

     else if (choix == 5){   
      decon = 1; break;    
    }

   }
    
   else if (con == 0){
    while(1){

  
      
    int matricule =getMatriculeFromFile(login, "etudiants.txt");
    //recuperer la matricule
  int a = 0;
    nbreMessages(matricule,&a);
    int choix = menuEtudiant(a);

     if(choix ==1){
        // addPresence( "presences.bin",matrice,1);
        if (verifierPresence(matricule))
            enregistrerPresence( matricule,1);
            else { printf( "\033[1;31m \u274C Presence deja marquée \n");
             printf("\033[0m");
            printf("appuyez sur une touche pour continuer...");
            getchar();
            }
     } if(choix == 2){
       liremesretards(matricule);
       printf("appuyez sur une touche pour continuer...");
       getchar();
     }

     if(choix == 3){
      lireMessage(matricule);
      printf("appuyez sur une touche pour continuer...");
      getchar();

      modifierEtatMessage(matricule);
       
     }
     if (choix == 4){
        decon =1;
        break;
     }

   }
     }
   
   }while(decon != 1);
  

}while(1);
    return 0;
}