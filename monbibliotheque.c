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
void dateAujourdhui(char* date) {
    time_t maintenant;
    struct tm* infoTemps;
    char buffer[80];

    time(&maintenant);
    infoTemps = localtime(&maintenant);

    strftime(buffer, 80, "%d/%m/%Y %H:%M", infoTemps);
    sprintf(date, "%s", buffer);
}


void enregistrerUser(User utilisateur) {
    FILE *fichier = fopen("user.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "%s %s %d\n", utilisateur.login, utilisateur.password, utilisateur.type);
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


int verifierIdentifiants(char login[], char password[] ) {
    FILE *fichier = fopen("users.bin", "rb");  
    if (fichier != NULL) {
        User utilisateur;
        while (fread(&utilisateur, sizeof(User), 1, fichier) == 1) {  // lecture des utilisateurs depuis le fichier
            if (strcmp(utilisateur.login, login) == 0 && strcmp(utilisateur.password, password) == 0) {
                fclose(fichier);  // fermeture du fichier
                return utilisateur.type;  // retourne le type d'utilisateur si les identifiants sont corrects
            }
        }
        fclose(fichier);  // fermeture du fichier
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
    
    return -1;  // retourne -1 si les identifiants ne correspondent à aucun utilisateur
}

int verifierUtilisateur(char login [], char motDePasse []) {
    FILE *fichier = fopen("user.txt", "r");
    User utilisateur;
    int trouve = -1;
    char buffer[100];
    
    if (fichier != NULL) {
        while (fgets(buffer, 100, fichier) != NULL) {

            sscanf(buffer, "%s %s %d", utilisateur.login, utilisateur.password, &utilisateur.type);
            if (strcmp(login, utilisateur.login) == 0 && strcmp(motDePasse, utilisateur.password) == 0) {
                printf("Authentification reussie.\n");
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
    if(choix < 1 || choix > 5) printf("Choix invalide veuillez recommencer\n");

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
    if(choix < 1 || choix > 5) printf("Choix invalide veuillez recommencer\n");

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

int listeClasses(const char* nomFichier){
    int id;
  
    FILE *fichier = fopen(nomFichier, "rb");  // ouverture du fichier en mode lecture binaire
    
    if (fichier != NULL) {
        Classe classe;
         if (fichier != NULL) {
        Classe classe;
        while (fread(&classe, sizeof(Classe), 1, fichier) == 1) {  // lecture des classes depuis le fichier
            printf(" %d  %s  nbEtudiants: %d\n", classe.id, classe.libelle, classe.nbEtudiants);
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

void addEtudiant(const char* nomFichier, Etudiant nouvelEtudiant){
    FILE *fichier = fopen(nomFichier, "ab");
    if(fichier != NULL){
        fwrite(&nouvelEtudiant, sizeof(Etudiant), 1, fichier);
        printf("Etudiant ajouté avec succès.\n");
        fclose(fichier);
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


    void addPresence(const char* nomFichier, int matricule, int presence) {
    FILE *fichier = fopen(nomFichier, "rb");
   
    if(fichier != NULL ) {
        Presence p, p1;
        p.matricule = matricule;
        p.presence = presence;
        char date[20];  
        dateAujourdhui(date);
        p.date.jour = (date[0] - '0') * 10 + (date[1] - '0');
        p.date.mois = (date[3] - '0') * 10 + (date[4] - '0');
        p.date.annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
        p.date.heure = (date[11] - '0') * 10 + (date[12] - '0');
        p.date.minute = (date[14] - '0') * 10 + (date[15] - '0');
        
        int presenceDejaAjoutee = 0;

        // Vérifier si la présence est déjà ajoutée dans le fichier
        while(fread(&p1, sizeof(Presence), 1, fichier) == 1) {
            if(p1.matricule == p.matricule && p1.date.jour == p.date.jour && p1.date.mois == p.date.mois && p1.date.annee == p.date.annee ){
                printf( "La présence est déjà ajoutée.\n");
                presenceDejaAjoutee = 1;
                break;
            }
        }

        if (!presenceDejaAjoutee) {
            // Si la présence n'est pas déjà ajoutée, on l'ajoute
            fprintf(fichier, "%d %d %d %d %d %d:%d\n", p.matricule, p.presence, p.date.jour, p.date.mois, p.date.annee, p.date.heure, p.date.minute);

            printf( "\xE2\x9C\x85 code valide, présence à :  %d:%d\n", p.date.heure, p.date.minute);
        }

        fclose(fichier);
    } else {
        printf( "Impossible d'ouvrir le fichier.\n");
    }
}

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
void listePresencesAuneDate(const char* nomFichier, int jour, int mois, int annee) {
    FILE *fichier = fopen(nomFichier, "rb"); // Ouvrir le fichier en mode écriture
    if(fichier != NULL) {
        Presence presence;
        
        while(fread(&presence, sizeof(Presence), 1, fichier) == 1){
            printf( "mat Presence Date\n"); // Écrire l'en-tête dans le fichier
            if(presence.date.jour == jour && presence.date.mois == mois && presence.date.annee == annee){
                printf("%d %d %d %d %d\n", presence.matricule, presence.presence, presence.date.jour, presence.date.mois, presence.date.annee);
            }
        }
        fclose(fichier); // Fermer le fichier après écriture
    }
}
// void listePresencesAuneDate(const char* nomFichier, int jour, int mois, int annee) {
//     FILE *fichier = fopen(nomFichier, "rb");
//     if(fichier != NULL) {
//         Presence presence;
//         printf("mat Presence Date\n");
//         while(fread(&presence, sizeof(Presence), 1, fichier) == 1){
//             if(presence.date.jour == jour && presence.date.mois == mois && presence.date.annee == annee){
//                 printf("%d %d %d %d %d\n", presence.matricule, presence.presence, presence.date.jour, presence.date.mois, presence.date.annee);
//             }
//         }
//         fclose(fichier);
//     }
// }
int verifieMatricule(int *matricule){
    FILE *f = fopen("etudiants.bin", "rb");
    if (f == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 0;
    }
    Etudiant e;
    while (fread(&e, sizeof(Etudiant), 1, f) == 1) {
        if (e.matricule == *matricule) {
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
void addPresenceAdmin(char login[]){
    char input[20], password[20];
    int matricule,s=1;
     printf("<--------------------------------------------------->\n");
    printf("----------------MARQUER LES PRESENCES--------------\n");
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
             
            addPresence( "presences.bin",matricule,1);
            }

    }
    }
    
      
} 



/*********Partie Etudiants************/
int menuEtudiant(){
    int choix;
    do
    {

    printf("\n\t1_______MARQUER MA PRÉSENCE\n");
    printf("\t2_________NOMBRE DE MINUTES D’ABSENCE\n");
    printf("\t3_________MES MESSAGES (0)\n");
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
     while (fread(&etudiant, sizeof(Etudiant), 1, file) == 1) {
        if (strcmp(login, etudiant.login) == 0) {
            matricule = etudiant.matricule;
            break;
        }
    }


    fclose(file); // Fermer le fichier après avoir terminé la lecture

    return matricule;
}