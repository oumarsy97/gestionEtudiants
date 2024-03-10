#include "monbibliotheque.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

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
    }

     else if (choix == 2){
      int choix3 = menuFichier();
         if (choix3== 1) ;

       if(choix3 == 2) afficherTous();
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
            Messageaetudiant();
          };
     }

     else if (choix == 5){   
      decon = 1; break;    
    }

   }
    
   else if (con == 0){
      
    int matricule =getMatriculeFromFile(login, "etudiants.txt");
    //recuperer la matricule
  int a = 0;
    nbreMessages(matricule,&a);
    int choix = menuEtudiant(a);

     if(choix ==1){
        // addPresence( "presences.bin",matrice,1);
        if (verifierPresence(matricule))
            enregistrerPresence( matricule,1);
            else  printf("Presence deja marquee \n");
     }

     if(choix == 3){
      lireMessage(matricule);
      printf("appuyez sur une touche pour continuer...");
      getchar();

      modifierEtatMessage(matricule);
       
     }
     if (choix == 4){
        decon =1;
     }

   }
   
   }while(decon != 1);
  

}while(1);
    return 0;
}