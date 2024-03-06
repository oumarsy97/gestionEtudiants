#include "monbibliotheque.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
void dateAujourdhui(char* date) {
    time_t maintenant;
    struct tm* infoTemps;
    char buffer[80];

    time(&maintenant);
    infoTemps = localtime(&maintenant);

    strftime(buffer, 80, "%d/%m/%Y", infoTemps);
    sprintf(date, "%s", buffer);
}

void saveUserToFile(User user) {
    FILE *file = fopen("users.bin", "ab");  // ouverture du fichier en mode ajout binaire
    
    if (file != NULL) {
        fwrite(&user, sizeof(User), 1, file);  // écriture de l'utilisateur dans le fichier
        fclose(file);  // fermeture du fichier
        printf("Utilisateur enregistré avec succès.\n");
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


int verifierIdentifiants(char login[], char password[]) {
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


int connexion(){
    char login[20];
   
    printf("Entrez votre login : ");
    scanf("%s", login);
    while(getchar() != '\n');
   
     char password[20];
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
    if (password[strlen(password) - 1] == '\n') {
    password[strlen(password) - 1] = '\0';
}
    //printf("\nMot de passe saisi : %s\n", password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);  // restaure les paramètres du terminal d'origine
     
    return verifierIdentifiants(login, password);
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
        printf("0_________RETOUR\n");
        do{
        printf(" veillez entrer le matricule d un etudiant\n");
        scanf("%d", &choix);
        while(getchar() != '\n');
        if((choix < 1 && choix != 0)  || (choix > etudiant.matricule  && choix != 0)) printf("Choix invalide veuillez recommencer\n");
    }while(choix < 0 || choix > etudiant.matricule );
    return choix;
    }
    
    }

    

    void addPresence(const char* nomFichier, int matricule, int presence) {
    FILE *fichier = fopen(nomFichier, "rb+");
    if(fichier != NULL) {
        Presence p, p1;
        p.matricule = matricule;
        p.presence = presence;
        char date[11];  
        dateAujourdhui(date);
        p.date.jour = (date[0] - '0') * 10 + (date[1] - '0');
        p.date.mois = (date[3] - '0') * 10 + (date[4] - '0');
        p.date.annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

        int presenceDejaAjoutee = 0;

        // Vérifier si la présence est déjà ajoutée dans le fichier
        while(fread(&p1, sizeof(Presence), 1, fichier) == 1){
            if(p1.matricule == p.matricule && p1.date.jour == p.date.jour && p1.date.mois == p.date.mois && p1.date.annee == p.date.annee){
                printf("La présence est déjà ajoutée.\n");
                presenceDejaAjoutee = 1;
                break;
            }
        }

        if (!presenceDejaAjoutee) {
            // Si la présence n'est pas déjà ajoutée, on l'ajoute
            fwrite(&p, sizeof(Presence), 1, fichier);
            printf("Présence ajoutée avec succès.\n");
        }

        fclose(fichier);
    }
}
    



/*********Partie Etudiants************/
int menuEtudiant(){
    int choix;
    do
    {

    printf("\t1_________MARQUER MA PRÉSENCE\n");
    printf("\t2_________NOMBRE DE MINUTES D’ABSENCE\n");
    printf("\t3_________MES MESSAGES (0)\n");
    printf("\t4_________DECONNEXION\n");
    scanf("%d", &choix);
    while(getchar() != '\n');
    if(choix < 1 || choix > 4) printf("Choix invalide veuillez recommencer\n");
    } while ( choix < 1 || choix > 4);
    return choix;
    
    
}
