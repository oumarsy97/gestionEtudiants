#include "monbibliotheque.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define Yellow "\x1B[33m"
#define Reset "\x1B[0m"
#define Green "\x1B[32m"
#define Red "\x1B[31m"
#define Blue "\x1B[34m"
#define Magenta "\x1B[35m"
#define Cyan "\x1B[36m"
#define White "\x1B[37m"

void dateAujourdhui(char* date) {
    time_t maintenant;
    struct tm* infoTemps;
    char buffer[80];

    time(&maintenant);
    infoTemps = localtime(&maintenant);

    strftime(buffer, 80, "%d/%m/%Y %H:%M", infoTemps);
    sprintf(date, "%s", buffer);
}


// void hashPassword(const char *password, char *hashedPassword) {
//     unsigned char hash[SHA256_DIGEST_LENGTH];
//     SHA256_CTX sha256;
//     SHA256_Init(&sha256);
//     SHA256_Update(&sha256, password, strlen(password));
//     SHA256_Final(hash, &sha256);

//     for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//         sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
//     }
//     hashedPassword[64] = 0; // Ajouter le caractère de fin de chaîne
// }

// int verifyPassword(const char *inputPassword, const char *storedHash) {
//     char hashedInput[65];
//     hashPassword(inputPassword, hashedInput);
//     if (strcmp(hashedInput, storedHash) == 0) {
//         return 1; // Mot de passe correct
//     } else {
//         return 0; // Mot de passe incorrect
//     }
// }


void enregistrerUser(User user) {
    FILE *fichier = fopen("user.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "%s %s %d\n", user.login, user.password, user.type);
       fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
}


void saveUserToFile(User user) {
    FILE *file = fopen("users.bin", "ab");  // ouverture du fichier en mode ajout binaire
    
    if (file != NULL) {
        fwrite(&user, sizeof(User), 1, file);  // écriture de l'utilisateur dans le fichier
        fclose(file);  // fermeture du fichier
       // printf("Utilisateur enregistré avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

void displayUsersFromFile() {
    FILE *file = fopen("users.bin", "rb");  // ouverture du fichier en mode lecture binaire
    
    if (file != NULL) {
        User user;
        while (fread(&user, sizeof(User), 1, file) == 1) {  // lecture des utilisateurs depuis le fichier
            printf("Login: %s, Mot de passe: %s, Type: %d\n", user.login, user.password, user.type);
        }
        fclose(file);  // fermeture du fichier
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}






int verifierUtilisateur(char login [], char motDePasse []) {
    FILE *fichier = fopen("user.txt", "r");
    User utilisateur;
    int trouve = -1;
    char buffer[100];
    
    if (fichier != NULL) {
        while (fgets(buffer, 100, fichier) != NULL) {

            sscanf(buffer, "%s %s  %d", utilisateur.login, utilisateur.password, &utilisateur.type);
            if (strcmp(login, utilisateur.login) == 0 && strcmp(motDePasse, utilisateur.password) == 0) {
                trouve = utilisateur.type;
                break;
            }
        }
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }

    return trouve;
}
int connexion(char login[]) {
    
   
    printf("Entrez votre login : ");
    scanf("%s", login);
    while(getchar() != '\n');
   
     char password[20];
    int i = 0,v;
    char ch;
    
    printf("Entrez votre mot de passe : ");
    
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);  // sauvegarde des paramètres actuels du terminal
    new_term = old_term;
    new_term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);  // désactive l'écho des caractères saisis et le mode canonique
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);  // applique les nouveaux paramètres du terminal
    
    while (1) {
        ch = getchar();
        

        
        if (ch == 10 && sizeof(password)!=0) {  // 10 is the ASCII code for Enter
            break;
        } else if (ch == 127) {  // 127 is the ASCII code for Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // efface le caractère de la console
            }
        } else if (ch != 10) {
            password[i] = ch;
            i++;
            printf("*");  // affiche un astérisque à la place du caractère réel
        }
    }
    if (password[strlen(password) - 1] == '\n') {
    password[strlen(password) - 1] = '\0';
}
    //printf("\nMot de passe saisi : %s\n", password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);  // restaure les paramètres du terminal d'origine
    
   
       
  
    v = verifierUtilisateur(login, password);
    return v ;
    printf("\n");
}

int menuAdmin()
{
    int choix;
     do{
    printf("\n1_________GESTION DES ÉTUDIANTS\n");
    printf("2_________GÉNÉRATION DE FICHIERS\n");
    printf("3_________MARQUER LES PRÉSENCES\n");
    printf("4_________ENVOYER UN MESSAGE\n");
    printf("5_________Quitter\n");
    scanf("%d", &choix);
    while(getchar() != '\n');
    if(choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5) printf("Choix invalide veuillez recommencer\n");

    }while(choix < 1 || choix > 5);

    return choix;
}

int menuGestionEtudiant()
{
    int choix;
     do{

    printf("\t1_________Ajouter un etudiant\n");
    printf("\t2_________Modifier un etudiant\n");
    printf("\t3_________Supprimer un etudiant\n");
    printf("\t4_________Lister tous les etudiants\n");
    printf("\t5_________Retour\n");
    scanf("%d", &choix);
    while(getchar() != '\n');
    if(choix < 1 || choix > 5) printf("Choix invalide veuillez recommencer !!\n");

    }while(choix < 1 || choix > 5);

    return choix;

}

Etudiant saisiEtudiant()
{
    Etudiant e;
    printf("Matricule : ");
    scanf("%d", &e.matricule);
    printf("Nom : ");
    scanf("%s", e.nom);
    printf("Prenom : ");
    scanf("%s", e.prenom);
    e.presence = 0;
    e.absence = 0;
   
    return e;
}

int ajouterEtudiant(){

    Etudiant e = saisiEtudiant();
    FILE *f = fopen("etudiants.txt", "a");
    fprintf(f, "%d %s %s %d %d\n", e.matricule, e.nom, e.prenom,e.presence , e.absence);
    fclose(f);
    return 0;
    

}

void modifierEtudiant(Etudiant e){
   
}

void supprimerEtudiant(Etudiant e){
    int matricule = e.matricule;
    FILE *f = fopen("etudiants.txt", "a");
   

}

void afficherEtudiants(){

}

int menuPresence(){
    int choix;
    do
    {
       printf ("\t1_________CHOISIR LA CLASSE\n");
       printf ("\t2_________ANULLER\n");
       scanf("%d", &choix);
       while(getchar() != '\n');
       if(choix < 1 || choix > 2) printf("Choix invalide veuillez recommencer\n");
    } while (choix < 1 || choix > 2);
    return choix;
    
}
void enregistrerClasses(const char* nomFichier, Classe nouvelleClasse) {
    FILE *fichier = fopen(nomFichier, "ab");  // ouverture du fichier en mode ajout binaire
    
    if (fichier != NULL) {
        fwrite(&nouvelleClasse, sizeof(Classe), 1, fichier);  // écriture de la nouvelle classe dans le fichier
        fclose(fichier);  // fermeture du fichier
        printf("La classe a été enregistrée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}


// void addEtudiant(const char* nomFichier, Etudiant nouvelEtudiant){
//     FILE *fichier = fopen(nomFichier, "ab");
//     if(fichier != NULL){
//         fwrite(&nouvelEtudiant, sizeof(Etudiant), 1, fichier);
//         printf("Etudiant ajouté avec succès.\n");
//         // User user;
//         // strcpy(user.login, nouvelEtudiant.login);
//         // strcpy(user.password, "passer");
//         // user.type = 0;
//         // enregistrerUser(user);
//         fclose(fichier);
//     }
// }


void addEtudiant(const char* nomFichier, Etudiant nouvelEtudiant){
    FILE *fichier = fopen(nomFichier, "a"); // Utilisation d'un fichier texte .txt

    if(fichier != NULL){
        fprintf(fichier,  "%d %s %s %s %d %d %d\n", nouvelEtudiant.matricule, nouvelEtudiant.login, nouvelEtudiant.nom, nouvelEtudiant.prenom, nouvelEtudiant.classe, nouvelEtudiant.presence, nouvelEtudiant.absence);
        printf("Etudiant ajouté avec succès.\n");
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
}
int listeEtudiants(const char* nomFichier, int idClasse){
    int choix;
    FILE *fichier = fopen(nomFichier, "rb");
    if(fichier != NULL){
        Etudiant etudiant;
        printf("mat Nom Prenom Presence Absence\n");
        while(fread(&etudiant, sizeof(Etudiant), 1, fichier) == 1){
            if(etudiant.classe == idClasse){
                printf("%d %s   %s   %d  %d\n", etudiant.matricule, etudiant.nom, etudiant.prenom,  etudiant.presence, etudiant.absence);
            }
        }
        fclose(fichier);
    
        do{
        printf(" veillez entrer le matricule d un etudiant\n");
        scanf("%d", &choix);
        while(getchar() != '\n');
        if((choix < 1 && choix != 0)  || (choix > etudiant.matricule  && choix != 0)) printf("Choix invalide veuillez recommencer\n");
    }while(choix < 0 || choix > etudiant.matricule );
    return choix;
    }
    
    }

    void incrementPresence(const char* login, const char* filename) {
    FILE *file = fopen(filename, "rb+"); // Ouvrir le fichier en mode lecture/écriture binaire
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        return; // Quitter la fonction en cas d'erreur
    }

    Etudiant etudiant;

    // Rechercher l'étudiant par son login dans le fichier binaire
    while (fread(&etudiant, sizeof(Etudiant), 1, file) == 1) {
        if (strcmp(login, etudiant.login) == 0) {
            etudiant.presence += 1; // Mettre à jour le nombre de présences
            fseek(file, -sizeof(Etudiant), SEEK_CUR); // Se déplacer en arrière d'une structure pour écrire par dessus
            fwrite(&etudiant, sizeof(Etudiant), 1, file); // Réécrire la structure modifiée
            break; // Arrêter la recherche une fois l'étudiant trouvé et modifié
        }
    }

    fclose(file); // Fermer le fichier après avoir terminé la modification
}

int verifieMatricule(int *matricule){
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 0;
    }
    Etudiant e;
    while (fscanf(f, "%d %s %s %s %d %d %d", &e.matricule,e.login, e.nom, e.prenom, &e.classe, &e.presence, &e.absence) != EOF) {
        //printf("%d %s %s %s %d %d %d\n", e.matricule,e.login, e.nom, e.prenom, e.classe, e.presence, e.absence);
        if (e.matricule == *matricule) {
            //printf("matricule existe\n");
            fclose(f);
            return 1;
        } 
    }
    fclose(f);
    return 0;
}


//fonction pour masquer mot de passe
int SaisieMotDePasse( char login[], char* password) {

    int i = 0;
    char ch;
   
    printf("Entrez votre mot de passe : ");
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);  // sauvegarde des paramètres actuels du terminal
    new_term = old_term;
    new_term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);  // désactive l'écho des caractères saisis et le mode canonique
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);  // applique les nouveaux paramètres du terminal
    while (1) {
        ch = getchar();
        
        if (ch == 10 && sizeof(password)!=0) {  // 10 is the ASCII code for Enter
            break;
        } else if (ch == 127) {  // 127 is the ASCII code for Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // efface le caractère de la console
            }
        } else if (ch != 10) {
            password[i] = ch;
            i++;
            printf("*");  // affiche un astérisque à la place du caractère réel
        }
    }
    password[i] = '\0';
    printf("\n");
    if (i == 0) {
        printf("Le mot de passe ne peut pas être vide.\n");
        return SaisieMotDePasse(login, password);
    }
    if (password[strlen(password) - 1] == '\n') {
    password[strlen(password) - 1] = '\0';
}
    //printf("\nMot de passe saisi : %s\n", password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);  // restaure les paramètres du terminal d'origine
     
    return verifierUtilisateur(login, password);
    printf("\n"); 
    
}




int verifierPresence(int matricule) {
    FILE *fichier = fopen("presences.txt", "r");
    int matriculePresent = 1; // Supposons par défaut que la matricule n'est pas présente

    if (fichier != NULL) {
        Presence newPresence;
          char line[100];
          char nom[20], prenom[20];
         
          while (fscanf(fichier, "%d %s %s présent Date: %d/%d/%d à %d:%d:%d ", &newPresence.matricule, nom, prenom, &newPresence.date.jour, &newPresence.date.mois, &newPresence.date.annee, &newPresence.date.heure, &newPresence.date.minute, &newPresence.date.seconde) != EOF) {
           // printf("%d %s %s présent Date: %d/%d/%d", newPresence.matricule, nom, prenom, newPresence.date.jour, newPresence.date.mois, newPresence.date.annee);
         // Supposons que nous voulons vérifier uniquement pour la date actuelle
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            int annee = tm->tm_year + 1900;
            int mois = tm->tm_mon + 1;
            int jour = tm->tm_mday;

            // ... (restez inchangé)
           if(matricule == newPresence.matricule && annee == newPresence.date.annee && mois == newPresence.date.mois && jour == newPresence.date.jour){
          // printf("%d %s %s est presente\n", newPresence.matricule, nom, prenom);
               matriculePresent = 0;
               break; 
           }
           

        }

        fclose(fichier);
    } 

    return matriculePresent;
}



void addPresenceAdmin(char login[]){
    char input[20], password[20];
    int matricule,s=1;
     printf("<--------------------------------------------------->\n");
    printf("----------------MARQUER LES PRESENCES-----------------\n");
    printf("<--------------------------------------------------->\n");
    
    while(s){
        printf("Entrer votre code [q pour quitter]: ");
        fgets(input, 20, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "q") == 0) {
            SaisieMotDePasse(login, password);
            //printf("Mot de passe saisi : %s\n", password);
            if(verifierUtilisateur(login, password) == 1){
                s=0;
                break;
            } 
            
        }else{  

            matricule = atoi(input);
            if(!verifieMatricule(&matricule)) printf("Matricule invalide \n");
        
            else {
             if (verifierPresence(matricule))
            enregistrerPresence( matricule,1);
            else  {
                printf( "\033[1;31m \u274C Presence deja marquée. \n");
             printf("\033[0m");
            printf("appuyez sur une touche pour continuer...");
            getchar();
            }
            }

    }
    }
    
      
} 



/*********Partie Etudiants************/
int menuEtudiant(int nbreMessages) {
    int choix;
    do
    {
    printf("\n\t1_______MARQUER MA PRÉSENCE\n");
    printf("\t2_________NOMBRE DE MINUTES D’ABSENCE\n");
    printf("\t3_________MES MESSAGES (%d)\n", nbreMessages);
    printf("\t4_________DECONNEXION\n");
    scanf("%d", &choix);
    while(getchar() != '\n');
    if(choix < 1 || choix > 4) printf("Choix invalide veuillez recommencer\n");
    } while ( choix < 1 || choix > 4);
    return choix;
    
    
}


int getMatriculeFromFile(const char* login, const char* filename) {
    FILE *file = fopen(filename, "r"); // Ouvrir le fichier en mode lecture
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1; // Valeur de retour indiquant une erreur
    }

    Etudiant etudiant;
    int matricule = -1;

    // Rechercher le login dans le fichier
     while (fscanf(file, "%d %s %s %s %d %d %d", &etudiant.matricule, etudiant.login, etudiant.nom, etudiant.prenom, &etudiant.classe, &etudiant.presence, &etudiant.absence) != EOF) {
        if (strcmp(login, etudiant.login) == 0) {
            matricule = etudiant.matricule;
            break;
        }
    }


    fclose(file); // Fermer le fichier après avoir terminé la lecture

    return matricule;
}

/************************************************Fichier*******************************/
void listePresences(const char* nomFichier) {
    FILE *fichier = fopen(nomFichier, "rb");
    if(fichier != NULL) {
        Presence presence;
        printf("mat Presence Date\n");
        while(fread(&presence, sizeof(Presence), 1, fichier) == 1){
            printf("%d %d %d %d %d\n", presence.matricule, presence.presence, presence.date.jour, presence.date.mois, presence.date.annee);
        }
        fclose(fichier);
    }
}

Etudiant rechercheEtudiant(int mat){
    FILE *fichier = fopen("etudiants.txt","r");
    if(fichier != NULL) {
        Etudiant etudiant;
        while(fscanf(fichier,"%d %s %s %s %d %d %d", &etudiant.matricule,etudiant.login, etudiant.nom, etudiant.prenom, &etudiant.classe, &etudiant.presence, &etudiant.absence) != EOF) {
           // printf("%d %s %s %s %d %d %d\n", etudiant.matricule,etudiant.login, etudiant.nom, etudiant.prenom, etudiant.classe, etudiant.presence, etudiant.absence);
            if(etudiant.matricule == mat){
                 //printf("%d %s %s ",etudiant.matricule,etudiant.prenom,etudiant.nom);
             return etudiant;
            }
           
        }
    }
}

void listePresencesAuneDate(const char* nomFichier, int jour, int mois, int annee) {
    FILE *fichier = fopen(nomFichier, "r");
    if(fichier != NULL) {
        Presence presence;
        while(fscanf(fichier, "%d %d %d %d %d %d %d", &presence.matricule, &presence.presence, &presence.date.jour, &presence.date.mois, &presence.date.annee, &presence.date.heure, &presence.date.minute) != EOF) {
        if(presence.presence == 1){
            Etudiant e = rechercheEtudiant(presence.matricule);
            printf("%d %s %s %d %d %d %d\n", presence.matricule,e.prenom,e.nom, presence.presence, presence.date.jour, presence.date.mois, presence.date.annee);
        }
            if(presence.date.jour == jour && presence.date.mois == mois && presence.date.annee == annee){
                // Etudiant e = rechercheEtudiant(presence.matricule);
                // printf("%d %s %s %d %d %d %d\n", presence.matricule,e.prenom,e.nom, presence.presence, presence.date.jour, presence.date.mois, presence.date.annee);
            }
        }
        fclose(fichier);
    }
}


void afficheTous() {
    FILE *fichier = fopen("presences.txt", "r");
    if(fichier != NULL) {
        Etudiant e;
        Presence presence;
        
      
        fclose(fichier);
    }
}

void genererFichierPresencesAujourdhui() {
    FILE *fichierEntree = fopen("presences.bin", "rb");
    FILE *fichierSortie = fopen("presences_aujourdhui.bin", "wb");

    if (fichierEntree != NULL && fichierSortie != NULL) {
        Presence presenceData;
        // Supposons que nous voulons filtrer pour la date actuelle
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        int annee = tm->tm_year + 1900;
        int mois = tm->tm_mon + 1;
        int jour = tm->tm_mday;

        while (fread(&presenceData, sizeof(Presence), 1, fichierEntree) == 1) {
            if (presenceData.date.annee == annee && presenceData.date.mois == mois && presenceData.date.jour == jour) {
                fwrite(&presenceData, sizeof(Presence), 1, fichierSortie);
            }
        }

        fclose(fichierEntree);
        fclose(fichierSortie);
    } else {
        printf("Erreur lors de l'ouverture des fichiers");
    }
}

int date_existe( Date date) {
    FILE *fichier = fopen("date.txt", "r");
    if (fichier != NULL) {
        Date date_lue;
        while (fscanf(fichier, "%d/%d/%d", &date_lue.jour, &date_lue.mois, &date_lue.annee) != EOF) {
            //printf("%d/%d/%d\n", date_lue.jour, date_lue.mois, date_lue.annee);
            
            if (date_lue.jour == date.jour && date_lue.mois == date.mois && date_lue.annee == date.annee) {
                fclose(fichier);
                //printf("Date %d/%d/%d existe dans le fichier\n", date.jour, date.mois, date.annee);
                return 1; // La date existe dans le fichier
                }
        }
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
    return 0; // La date n'existe pas dans le fichier
}

int mois_existe( Date date) {
    FILE *fichier = fopen("mois.txt", "r");
    if (fichier != NULL) {
        Date date_lue;
        while (fscanf(fichier, "%d/%d", &date_lue.mois, &date_lue.annee) != EOF) {
            //printf("%d/%d/%d\n", date_lue.jour, date_lue.mois, date_lue.annee);
            
            if (date_lue.mois == date.mois && date_lue.annee == date.annee) {
                fclose(fichier);
                //printf("Date %d/%d/%d existe dans le fichier\n", date.jour, date.mois, date.annee);
                return 1; // La date existe dans le fichier
                }
        }
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
    return 0; // La date n'existe pas dans le fichier
     
}
void enregistrer_mois( Date date) {
     FILE *fichier;

    fichier = fopen("mois.txt", "a");
    if (fichier != NULL) {
        if(mois_existe( date) == 0){
              fprintf(fichier, "%d/%d\n", date.mois, date.annee);
              fclose(fichier);
            
        }
           // printf("Date %d/%d/%d enregistree avec succes\n", date.jour, date.mois, date.annee);
      
        }
        
     else {
        printf("Erreur lors de l'ouverture du fichier");
    }
    
}
void enregistrer_date_fichier( Date date) {
     FILE *fichier;

    fichier = fopen("date.txt", "a");
    if (fichier != NULL) {
        if(date_existe( date) == 0){
           // printf("Date %d/%d/%d enregistree avec succes\n", date.jour, date.mois, date.annee);
        fprintf(fichier, "%d/%d/%d\n", date.jour, date.mois, date.annee);
        fclose(fichier);
        }
        
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
   
}

Date soustraite(Date date1, Date date2) {
    Date difference;
    difference.jour = date1.jour - date2.jour;
    difference.mois = date1.mois - date2.mois;
    difference.annee = date1.annee - date2.annee;
    difference.heure = date1.heure - date2.heure;
    difference.minute = date1.minute - date2.minute;
    difference.seconde = date1.seconde - date2.seconde;
    if( difference.seconde < 0){
        difference.seconde += 60;
        difference.minute--;
    }
    if( difference.minute < 0){
        difference.minute += 60;
        difference.heure--;
    }
    if( difference.heure < 0){
        difference.heure += 24;
        difference.jour--;
    }
    if( difference.jour < 0){
        difference.jour += 30;
        difference.mois--;
    }
    if( difference.mois < 0){
        difference.mois += 12;
        difference.annee--;
    }
    return difference;
}
void enregistrerPresence(int matricule, int presence) {
    FILE *fichier = fopen("presences.txt", "a"); // Utilisation d'un fichier texte .txt
    FILE *f = fopen("retards.txt", "a");
    Presence newPresence;
    newPresence.matricule = matricule;
    Etudiant e= rechercheEtudiant(matricule);
    newPresence.presence = presence;
    // Exemple d'obtention de la date actuelle
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    newPresence.date.annee = tm->tm_year + 1900;
    newPresence.date.mois = tm->tm_mon + 1;
    newPresence.date.jour = tm->tm_mday;
    newPresence.date.heure = tm->tm_hour;
    newPresence.date.minute = tm->tm_min;
    newPresence.date.seconde = tm->tm_sec;
    if (fichier != NULL) {
        // ... (restez inchangé)
         if(newPresence.date.heure >= 8 && newPresence.date.heure < 16){
    
        fprintf(fichier, " %d %s %s présent Date: %d/%d/%d à %d:%d:%d\n", newPresence.matricule,e.prenom,e.nom, newPresence.date.jour, newPresence.date.mois, newPresence.date.annee, newPresence.date.heure, newPresence.date.minute, newPresence.date.seconde);
        
            enregistrer_date_fichier(newPresence.date); // Vous pouvez ajuster cette fonction pour enregistrer dans un fichier texte également
        
        
        printf(" \033[1;32m\xE2\x9C\x85 code valide, présence à : %d:%d:%d \n", newPresence.date.heure, newPresence.date.minute, newPresence.date.seconde);
         printf("\033[0m");
         //retard au dela de 8h et 15min
          Date d8h15=newPresence.date;d8h15.heure=8;d8h15.minute=15; 
          Date d= soustraite(newPresence.date,d8h15);
        if( d.minute > 0 || d.heure > 0){
           
            fprintf(f, "%d %s %s Retard du %d/%d/%d de %d:%d:%d\n", newPresence.matricule,e.prenom,e.nom, newPresence.date.jour, newPresence.date.mois, newPresence.date.annee, d.heure,d.minute,d.seconde);
            if(mois_existe( newPresence.date) == 0){
                enregistrer_mois( newPresence.date);
            }
            
        }

         }
        fclose(fichier);
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
}

void cumulRetarsMois(int mois, int annee) {
    FILE *f = fopen("retards.txt", "r");
    FILE *c = fopen ("cumul.txt", "w");
    if (f != NULL) {
        int matricule;
        int tab[100];int nb;       
        les_mat(tab, &nb);
        int heure, minute, seconde;
        Presence p;
        Etudiant e,e2;
        fprintf(c,"+-------------------------------+\n");
        fprintf(c,"|           Mois: %d/%d        |\n", mois, annee); 
        fprintf(c,"+-------------------------------+\n"); 
        fprintf(c,"| Mat |  Nom  |  Prenom | Heure |\n");  
        fprintf(c,"+-------------------------------+\n");    
          for(int i = 0; i < nb; i++){
                int cumulH = 0, cumulM = 0;
                fseek(f, 0, SEEK_SET);
            while(fscanf(f,"%d %s %s Retard du %d/%d/%d de %d:%d:%d", &p.matricule,e.nom,e.prenom, &p.date.jour, &p.date.mois, &p.date.annee, &heure, &minute, &seconde) != EOF){
                //printf("%d %s %s Retard du %d/%d/%d de %d:%d:%d\n", p.matricule, e.nom, e.prenom, p.date.jour, p.date.mois, p.date.annee, heure, minute, seconde);

                    if(p.matricule == tab[i] && mois == p.date.mois && annee == p.date.annee){
                        cumulH += heure;
                        cumulM += minute;
                        
                    }
         
                } 
               e2 = rechercheEtudiant(tab[i]);
                
                fprintf(c, "|%4d |%6s |%6s |%3d:%3d  |\n",tab[i],e2.prenom,e2.nom, cumulH, cumulM);
                fprintf(c,"+-------------------------------+\n"); 
            }
        }
        fclose(f);
        fclose(c);
               }
        
        
    void cumulRetards() {
        FILE *f = fopen ("mois.txt", "r");
        FILE *c = fopen ("cumul.txt", "a");
        if (f != NULL) {
            int mois, annee;
            while(fscanf(f, "%d/%d", &mois, &annee) != EOF) {
                cumulRetarsMois(mois, annee);
                printf("\n");
            }
            copyfile("cumul.txt", "cumuls.txt");
          
        }
        fclose(f);
        fclose(c);
        
    }  


int menuFichier(){
    int choix;
    do{
        printf("1_______gererer le fichier de presence\n");
        printf("2_______gererer le fichier de presence par date\n");
        printf("3_______gererer le fichier de retard\n");
        printf("4_______retour\n");
    scanf("%d", &choix);
    while(getchar() != '\n');
    if(choix < 1 || choix > 4) printf("Choix invalide veuillez recommencer\n");
    } while ( choix < 1 || choix > 4);
    return choix;

}




void afficherParDate(Date d,char *nomFichier) {
    FILE* fichier2 = fopen("presences.txt", "r");
    FILE* fichier=fopen(nomFichier,"a");
    Presence p;
    Etudiant e;
    Classe c; 
    if (fichier2 != NULL) {
                fprintf(fichier, "                              Les présents du %d/%d/%d\n", d.jour, d.mois, d.annee);
                fprintf(fichier, "+---------------+---------------+---------------+---------------+\n");
                fprintf(fichier, "|  Matricule    | Prénom        | Nom          | Heure          |\n");
                fprintf(fichier, "+---------------+---------------+---------------+---------------+\n");
         
    while(fscanf(fichier2, "%d %s %s présent Date: %d/%d/%d à %d:%d:%d\n", &e.matricule, e.nom, e.prenom, &p.date.jour, &p.date.mois, &p.date.annee, &p.date.heure, &p.date.minute, &p.date.seconde) != EOF) {
            //    Etudiant e1 = rechercheEtudiant(p.matricule);
            //    printf("%d",e1.classe);
                c = diokhClasse(e.classe);
               if (d.jour == p.date.jour && d.mois == p.date.mois && d.annee == p.date.annee) {
                    fprintf(fichier,"|%-14d |%-14s |%-14s |%d:%d:%d        |\n",e.matricule,e.nom,e.prenom,p.date.heure,p.date.minute,p.date.seconde);                   
                fprintf(fichier, "+---------------+---------------+---------------+---------------+\n");
                }
            }
} else {
    printf("Erreur lors de l'ouverture du fichier des présences.\n");
}
fclose(fichier);
fclose(fichier2);
}

void afficherTous(){
    FILE* fichier = fopen("date.txt", "r");
    Presence p;
    Etudiant e;
    if (fichier != NULL) {
        Date d;
        while(fscanf(fichier, "%d/%d/%d", &d.jour, &d.mois, &d.annee) != EOF) {
            //printf("%d/%d/%d\n", d.jour, d.mois, d.annee);
            afficherParDate(d,"presencepardate.txt");   
        }
        fclose(fichier);
    }
    copyfile("presencepardate.txt", "presence_tous.txt");
    affichierFichier("presence_tous.txt");
}

void copyfile(char *nomFichier1, char *nomFichier2) {
    FILE* fichier1 = fopen(nomFichier1, "r");
    FILE* fichier2 = fopen(nomFichier2, "w");
    if (fichier1 != NULL && fichier2 != NULL) {
        char ch;
        while ((ch = fgetc(fichier1)) != EOF) {
            fputc(ch, fichier2);
        }
        fclose(fichier1);
        fclose(fichier2);
    }
     // Suppression du fichier source
    remove(nomFichier1);
    // Copie du fichier source dans le fichier de destination
    //rename(nomFichier2, nomFichier1);
   }

   int estBissextile(int annee) {
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0))
        return 1; // Si bissextile
    else
        return 0; // Sinon
}
// Fonction pour vérifier si une date est valide
int estDateValide(int jour, int mois, int annee) {
    // Vérification des limites des mois et du jour
    if (mois < 1 || mois > 12 || jour < 1)
        return 0;
    // Vérification du nombre de jours pour février
    if (mois == 2) {
        if (estBissextile(annee)) {
            if (jour > 29)
                return 0;
        } else {
            if (jour > 28)
                return 0;
        }
    }
    // Vérification du nombre de jours pour les mois de 30 jours
    else if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
        if (jour > 30)
            return 0;
    }
    // Vérification du nombre de jours pour les mois de 31 jours
    else {
        if (jour > 31)
            return 0;
    }
    // Si la date est valide
    return 1;
}

Date verifieDate(){
    char date[10],ch;
    Date d;
    int i = 0;
    do
    {
        printf("Saisir une date (JJ/MM/AAAA) : ");
        scanf("%d/%d/%d", &d.jour, &d.mois, &d.annee);
        while(getchar() != '\n');
        if (!estDateValide(d.jour, d.mois, d.annee)) {
            printf("Date invalide. Recommencez.\n");
        }else {
            break;
        }
    } while (1);
    return d;
    
}

void afficherAuneDate(Date d){
    //char mot ="presence"+d.jour+"-"+d.mois+"-"+d.annee;
    char mot[50];
    sprintf(mot, "presence-%d-%d-%d.txt", d.jour, d.mois, d.annee);
   // printf("%s\n",mot);
    FILE* fichier = fopen(mot, "w");
     if (fichier != NULL) {
        afficherParDate(d,mot);
        fclose(fichier);
     }
}


void affichierFichier(char *nomFichier) {
    FILE *f =fopen(nomFichier, "r");
    if (f != NULL) {
        char ch;
        while ((ch = fgetc(f)) != EOF) {
            printf("%c", ch);
        }
        fclose(f);
    }
}

/******************************Messages*******************************/
void envoieMsg(int matricule, char *message) {
    //printf("envoieMsg(%d, %s)\n", matricule, message);
    Message msg;
    msg.matricule = matricule;
    Etudiant e= rechercheEtudiant(matricule);
    strcpy(msg.message, message);
    strcpy(msg.source,"admin");
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    msg.date.annee = tm->tm_year + 1900;
    msg.date.mois = tm->tm_mon + 1;
    msg.date.jour = tm->tm_mday;
    msg.date.heure = tm->tm_hour;
    msg.date.minute = tm->tm_min;
    msg.date.seconde = tm->tm_sec;
    msg.etat = 0;
    FILE *f = fopen("messages.txt", "a");
    fprintf(f, "%s  %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s\n",msg.source,msg.matricule, e.prenom, e.nom,msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde, msg.etat ,msg.message);
    fclose(f);
    //printf(Green"Message envoyé avec succès \xE2\x9C\x85\n");
}

int sousMenu4(){
    int choix;
    do{
        printf("1_________Envoyer un message à tous\n");
        printf("2_________Envoyer un message à une classe\n");
        printf("3_________Envoyer un message à un etudiant\n");
        printf("4_________Retour\n");
        scanf("%d", &choix);
        while(getchar() != '\n');
        if(choix < 1 || choix > 4) printf("Choix invalide veuillez recommencer\n");
    
    }while(choix < 1 || choix > 4);
    return choix;
}

void Messageaetudiant(){
    int matricule;
    char msg[100];
    do{
    printf("veuillez entrer le matricule de l'etudiant : \n");
    scanf("%d", &matricule);
    while(getchar() != '\n');
     if(!verifieMatricule(&matricule)) printf("Matricule invalide \n");

    } while(!verifieMatricule(&matricule)); 
    printf("veuillez entrer le message : \n");
    fgets(msg, 100, stdin); // Utilisation de fgets pour lire la chaîne complète
    msg[strcspn(msg, "\n")] = '\0'; // Suppression du saut de ligne
    envoieMsg(matricule, msg);
    printf(Green"Message envoyé avec succès \xE2\x9C\x85\n");
     printf("\033[0m"); 

}


Classe diokhClasse(int id){
    
    FILE *file = fopen("classes.bin", "rb");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    Classe temp;
    while (fread(&temp, sizeof(Classe), 1, file)) {
        if (temp.id == id) {
            fclose(file);
            return temp;
        }
    }

    fclose(file);
    // Retourner une classe par défaut si l'identifiant n'est pas trouvé
    Classe defaultClasse = { .id = -1, .libelle = "Classe Inconnue" };
    return defaultClasse;
}
   
  
void rechercher_etudiants_par_id(int id_classe, int tableau_etudiants[],int *nb_etudiants) {
    FILE *fichier;
    char ligne[100];
    int matricule;
    Etudiant e;
    int index = 0;

    fichier = fopen("etudiants.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supposons que le format de ligne soit : matricule,ID_classe
        sscanf(ligne, "%d %s %s %s %d %d %d", &matricule,e.login, e.nom, e.prenom,  &e.classe, &e.presence, &e.absence);
        
        if (e.classe == id_classe) {
           // printf("%d %s %s %s %d %d %d\n", matricule,e.login, e.nom, e.prenom, e.classe, e.presence, e.absence);
            tableau_etudiants[index] = matricule;
            index++;
        }
    }

    fclose(fichier);

    *nb_etudiants = index;
}


void messageClasse(int id){
   int tab[100],nb_etudiants;
    char msg[100];
    printf("veuillez entrer le message : \n");
    fgets(msg, 100, stdin); // Utilisation de fgets pour lire la chaîne complète
    msg[strcspn(msg, "\n")] = '\0'; // Suppression du saut de ligne
    rechercher_etudiants_par_id(id,tab, &nb_etudiants);
    for(int i=0;i<nb_etudiants;i++){
        envoieMsg(tab[i], msg);
    }
    printf(Green"Message envoyé avec succès \xE2\x9C\x85\n");
     printf("\033[0m");


}

int listeClasses(const char* nomFichier){
    int id;
  
    FILE *fichier = fopen(nomFichier, "rb");  // ouverture du fichier en mode lecture binaire
    
    if (fichier != NULL) {
        Classe classe;
         if (fichier != NULL) {
        Classe classe;
        while (fread(&classe, sizeof(Classe), 1, fichier) == 1) {  // lecture des classes depuis le fichier
            printf(" %d  %s  \n", classe.id, classe.libelle);
            // Lire et afficher les étudiants si nécessaire
        }
        fclose(fichier); 
        do{
            printf("choisir une classe\n");
            scanf("%d", &id);
            while(getchar() != '\n');
            if(id < 1 || id > classe.id) printf("Choix invalide veuillez recommencer\n");
        } while (id < 1 || id > classe.id);
        return id;

    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}
 return 0;
}

void les_mat(int tab[100],int *nb){
    FILE *fichier;
    char ligne[100];
    int matricule;
    Etudiant e;
    int index = 0;

    fichier = fopen("etudiants.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supposons que le format de ligne soit : matricule,ID_classe
        sscanf(ligne, "%d %s %s %s %d %d %d", &matricule,e.login, e.nom, e.prenom,  &e.classe, &e.presence, &e.absence);
        
       
           // printf("%d %s %s %s %d %d %d\n", matricule,e.login, e.nom, e.prenom, e.classe, e.presence, e.absence);
            tab[index] = matricule;
            index++;
        
    }

    fclose(fichier);

    *nb = index;
}
void messageaTous(){
    int tab[100],nb_etudiants;
    char msg[100];
    printf("veuillez entrer le message : \n");
    fgets(msg, 100, stdin); // Utilisation de fgets pour lire la chaîne complète
    msg[strcspn(msg, "\n")] = '\0'; // Suppression du saut de ligne
    les_mat(tab, &nb_etudiants);
    for(int i=0;i<nb_etudiants;i++){
        
        envoieMsg(tab[i], msg);
    }
    printf(Green"Message envoyé avec succès \xE2\x9C\x85\n");
     printf("\033[0m");

}

void messageAdesEtudiants(){
    char input[100];
    char msg[100];
    printf("Veuillez saisir les matricules séparés par des virgules: \n");
    fgets(input, 100, stdin);

    // Découper la chaîne en matricules individuels
    char *token = strtok(input, ",");
    printf(" veillez entrer le message\n");
        fgets(msg, 100, stdin);
        msg[strcspn(msg, "\n")] = '\0';
    while (token != NULL) {
        int matricule = atoi(token);
        if(!verifieMatricule(&matricule)){
            printf("Matricule  %d invalide\n", matricule);
        }else{
            envoieMsg(matricule, msg);
            
           
        }
        token = strtok(NULL, ",");
        
    }

}

void lireMessage(int matricule) {
    FILE *f = fopen("messages.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }
    char ligne[100];
    Message msg;
    Etudiant e;
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %[^\n]", msg.source, &msg.matricule, e.nom, e.prenom, &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat, msg.message) != EOF) {
            if (msg.matricule == matricule && msg.etat == 0) {
                printf("Date: %d/%d/%d à %d:%d:%d\n", msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde);
                printf("+--------------------------------------+\n");
                printf("|");
                printf("\033[1;33m"); // Jaune gras
                printf("Message envoyé par: %-17s |\n", msg.source);
                printf("\033[0m"); // Réinitialiser la couleur
                printf("|");
                printf("\033[1;36m"); // Cyan gras
                printf("Message: %-30s |\n", msg.message);
                printf("\033[0m"); // Réinitialiser la couleur
                printf("+--------------------------------------+\n");
            }
        }
    }

    fclose(f);
}
// void lireMessage(int matricule) {
//     FILE *f = fopen("messages.txt", "r");
//     if (f == NULL) {
//         printf("Erreur lors de l'ouverture du fichier.");
//         exit(1);
//     }
//     char ligne[100];
//     Message msg;
//     Etudiant e;
    
//     while (fgets(ligne, sizeof(ligne), f) != NULL) {
//         if (sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %[^\n]", msg.source, &msg.matricule, e.nom, e.prenom, &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat, msg.message) != EOF) {
//             if (msg.matricule == matricule) {
//               printf("  +---------------+------------------+");
//               printf("||")
//               printf("  +---------------+------------------+");
//                 printf( Yellow"Message envoyé par:%s\n",msg.source);
//                printf("\033[0m");
//                 printf( Cyan "Message:%s\n",msg .message);
//                 printf("\033[0m");
//                 printf("Date:%d/%d/%d à %d:%d:%d\n",msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde);
               
//             }
//         }
//     }

//     fclose(f);
// }
        
    
void modifierEtatMessage(int matricule){
    FILE *f_in = fopen("messages.txt", "r");
    FILE *f_out = fopen("messages_temp.txt", "w"); // Fichier temporaire pour écrire les mises à jour

    if (f_in == NULL || f_out == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.");
        exit(1);
    }

    char ligne[200];
    Message msg;
    Etudiant e;
    
    while (fgets(ligne, sizeof(ligne), f_in) != NULL) {
        if (sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %[^\n]", msg.source, &msg.matricule, e.nom, e.prenom, &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat, msg.message) != EOF) {
            if (msg.matricule == matricule) {
                msg.etat = 1;
                fprintf(f_out, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s\n", msg.source, msg.matricule, e.nom, e.prenom,  msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde, msg.etat, msg.message);
            }else {
                fprintf(f_out, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s\n", msg.source, msg.matricule, e.nom, e.prenom,  msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde, msg.etat, msg.message);
        
            }

        }
    } 
        

    fclose(f_in);
    fclose(f_out);

    // Remplacer l'ancien fichier par le nouveau
    remove("messages.txt");
    rename("messages_temp.txt", "messages.txt");
}
    

    void nbreMessages(int mat,int *nb){
    FILE *fichier;
    char ligne[100];
    int matricule;
    Etudiant e;
    int index = 0;
    Message msg;

    fichier = fopen("messages.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }

    fseek(fichier, 0, SEEK_SET);
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supposons que le format de ligne soit : matricule,ID_classe
        sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s", msg.source, &msg.matricule, e.nom, e.prenom,  &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat,msg.message);
        
        if(msg.etat == 0 && msg.matricule == mat){
            index++;
        }
           // printf("%d %s %s %s %d %d %d\n", matricule,e.login, e.nom, e.prenom, e.classe, e.presence, e.absence);
                   
    }

    fclose(fichier);

    *nb = index;
}

/*************gestion etudiants*************/
    