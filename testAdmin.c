#include "monbibliotheque.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int choix;
    int con;
    do{
        Classe classe={3, "L3", {}, 0};
       //enregistrerClasses( "classes.bin",classe);
    
    Etudiant etudiant = {124,"mouhamed","Diop", "Mouhamed", 1, 0, 0};
   // addEtudiant("etudiants.bin", etudiant);
     User user = {"etudiant", "etudiant", 0};


   // saveUserToFile(user);
    char password[20];
    int i = 0;
    char ch;
      
   do
   {
   con = connexion();
    if(con != 1 && con != 0) printf("\nIdentifiants incorrects Veuillez reessayer\n");
   } while (con != 1 && con != 0);
       
    
   if (con == 1){
      int choix = menuAdmin();
    switch(choix)
     {
        int choix2;
       case 1:  choix2 = menuGestionEtudiant();
       break;
    // //     printf("Choix : %d\n", choix2);
    // //     if(choix2 == 1) ajouterEtudiant();
    // //     if(choix2 == 2) modifierEtudiant();
    // //     if(choix2 == 3) supprimerEtudiant();
    // //     if(choix2 == 4) afficherEtudiants();
    // //     break;
    //     // case 2: genererFichiers();
    //     // break;
    //     // case 3: marquerPresence();
    //     // break;
    //     // case 4: envoyerMessage();
    //     // break;
    //     case 5: break;
    //     default : printf("Choix invalide\n");
    //     break;
    case 3: 
    choix2 = menuPresence();
    int i = 1;
    if (choix2 == 1){
        int idclasse = listeClasses("classes.bin");
        int idEleve = listeEtudiants("etudiants.bin", idclasse);



        
    }
     
        
          break; 
            
    }

   }
    
   else if (con == 0){
    int choix = menuEtudiant();

   }
    }while((con==1 && choix != 5) || (con == 0 && choix != 4));
  
    return 0;
}