#include "monbibliotheque.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

     
    

    int choix;
    int con,decon=0;
    
        Classe classe={3, "L3", {}, 0};
       //enregistrerClasses( "classes.bin",classe);
    
    Etudiant etudiant = {124,"mouhamed","Diop", "Mouhamed", 1, 0, 0};
   // addEtudiant("etudiants.bin", etudiant);
     User user = {"etudiant", "etudiant", 0};


    //saveUserToFile(user);
    char password[20];
    int i = 0;
    char ch;
   do{ 
      
   do
   {
   con = connexion();
    if(con != 1 && con != 0) printf("\nIdentifiants incorrects Veuillez reessayer\n");
   } while (con != 1 && con != 0);



do{
   if (con == 1){
    
      int choix = menuAdmin();
    switch(choix)
     {
        int choix2;
       case 1:  choix2 = menuGestionEtudiant();
       break;
    
    case 3: 
    choix2 = menuPresence();
    int matricule ;
    
    if (choix2 == 1){
        
        int idclasse = listeClasses("classes.bin");
        
         matricule = listeEtudiants("etudiants.bin", idclasse);
        addPresence( "presences.bin",matricule,1);

            }   
          break; 
       case 5: decon = 1;     
    }

   }
    
   else if (con == 0){
    
    int choix = menuEtudiant();

     if(choix ==1){
         addPresence( "presences.bin",124,1);
     }
     if (choix == 4){
        decon =1;
     }

   }
   
   }while(decon != 1);
  

}while(1);
    return 0;
}