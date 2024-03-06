
#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
void dateAujourdhui(char* date);
int connexion ();
int menuAdmin();
int menuGestionEtudiant();
int ajouterEtudiant();
void modifierEtudiant();
void supprimerEtudiant();
void afficherEtudiants();
// int genererFichiers();
// int marquerPresence();
// int envoyerMessage();

/*********** partie admin *********/

typedef struct  {
    char login[20];
    char password[20];
    int type;
}User;
void saveUserToFile(User user);

void displayUsersFromFile();

typedef struct {
    
    int matricule;
    char login[20];
    char nom[100];
    char prenom[100];
    int classe;
    int presence;
    int absence;
}Etudiant;

Etudiant saisiEtudiant();
void addEtudiant(const char* nomFichier, Etudiant nouvelEtudiant);
int menuPresence();
int listeClasses();

typedef struct Classe {
    int id;
    char libelle[50];
    Etudiant etudiants[10];
    int nbEtudiants;
}Classe;

void enregistrerClasses(const char* nomFichier, Classe classe);

int listeEtudiants(const char* nomFichier, int idClasse);

typedef struct Date {
    int jour;
    int mois;
    int annee;
} Date;
typedef struct  Presence {
    int matricule;
    int presence ;
    Date date; 
} Presence;
int rappel();
int MenuPresence();
void addPresence(const char* nomFichier,int matricule, int presence);


/****************partie etudiant*****************/
int menuEtudiant();


#endif