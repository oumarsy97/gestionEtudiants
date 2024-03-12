
#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
void dateAujourdhui(char* date);
int connexion (char login[]);
int menuAdmin();
int menuGestionEtudiant();
int ajouterEtudiant();
void modifierEtudiant();
void supprimerEtudiant();
void afficherEtudiants();
// int genererFichiers();
// int marquerPresence();
// int envoyerMessage();


void displayUsersFromFile();
void hashPassword(const char *password, char *hashedPassword);
int verifyPassword(const char *password, const char *hashedPassword);

/*********** partie admin *********/

typedef struct  {
    char login[20];
    char password[20];
    int type;
}User;
void enregistrerUser(User utilisateur);
void saveUserToFile(User user);

void displayUsersFromFile();

typedef struct { 
    int matricule;
    char login[20];
    char prenom[20];
    char nom[20];
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
}Classe;

void enregistrerClasses(const char* nomFichier, Classe classe);

int listeEtudiants(const char* nomFichier, int idClasse);
typedef struct  {
    int minute;
    int seconde;
    int heure;
    int jour;
    int mois;
    int annee;
} Date;

typedef struct  {
    int matricule;
    Date date;
    int presence;
} Presence;
int rappel();
int MenuPresence();
void addPresence(const char* nomFichier,int matricule, int presence);
void listePresence(const char* nomFichier);
void incrementPresence(const char* login, const char* filename);
void listePresences(const char* nomFichier);
void listePresencesAuneDate(const char* nomFichier, int jour, int mois, int annee);
void addPresenceAdmin(char login[]);
int verifieMatricule(int *matricule);

int  SaisieMotDePasse( char login[], char password []);
void enregistrerPresence( int matricule, int presence);
int verifierPresence( int matricule);
void genererFichierPresencesAujourdhui();
void afficherPresencesAujourdhui();
void enregistreEtudiant(Etudiant etudiant, char *nomFichier);
void enregistrer_date_fichier(Date date);
void afficher_dates(const char *nom_fichier) ;
int date_existe( Date date);
void afficherAunedate();
Etudiant rechercheEtudiant(int);
int menuFichier();
void listeComplet(void);
void parcourirFichier();
void afficherParDate(Date d,char *nomFichier);
void afficherTous();
void copyfile(char *nomFichier1, char *nomFichier2) ;
int estBissextile(int annee);
int estDateValide(int jour, int mois, int annee);
Date verifieDate();
void afficherAuneDate(Date d);
void affichierFichier(char *nomFichier);
typedef struct {
    char source[20];
    int matricule;
    char nom[20];
    char prenom[20];
    char message[100];
    Date date;
    int etat;
} Message;



Classe diokhClasse(int);
int sousMenu4();
void envoieMsg(int matricule, char *message) ;
void Messageaetudiant();
void rechercher_etudiants_par_id(int id_classe, int tableau_etudiants[],int *nb_etudiants);
void messageClasse(int id);
void les_mat(int tab[100],int *nb);
void messageaTous();
void lireMessage(int matricule);
void nbreMessages(int,int *nb);
void modifierEtatMessage(int matricule);
void messageAdesEtudiants();

/****************partie etudiant*****************/
int menuEtudiant(int nbreMessages);
int getMatriculeFromFile(const char* login, const char* filename);




#endif