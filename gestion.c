

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





void sauvegarderEtudiantDansFichier(const char *nomFichier, Etudiant etudiant) {
    FILE *fichier = fopen(nomFichier, "a");
    
    if (fichier != NULL) {
        fprintf(fichier, "Matricule: %d\nLogin: %s\nNom: %s\nPrenom: %s\nClasse: %d\nPresence: %d\nAbsence: %d\n\n",
                etudiant.matricule, etudiant.login, etudiant.nom, etudiant.prenom, etudiant.classe, etudiant.presence, etudiant.absence);
        
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
    }
}

// void enregistreEtudiant(Etudiant etudiant, char *nomFichier) {
//     FILE *fichier = fopen(nomFichier, "r");
   

//     if (fichier != NULL) {
//         fscanf(fichier, "Matricule: %d\nLogin: %s\nNom: %s\nPrenom: %s\nClasse: %d\nPresence: %d\nAbsence: %d\n",
//                &etudiant.matricule, etudiant.login, etudiant.nom, etudiant.prenom, &etudiant.classe, &etudiant.presence, &etudiant.absence);
        
//         fclose(fichier);
//     } else {
//         printf("Erreur lors de l'ouverture du fichier");
//     }

//     User user ;
//     strcpy(user.login, etudiant.login);
//     strcpy(user.password, "passer");
//     user.type = 0;
//      enregistrerUser(user);
// }

void enregistreEtudiant(Etudiant etudiant, char *nomFichier) {
    FILE *fichier = fopen("etudiants.txt", "r");

    if (fichier != NULL) {
        fscanf(fichier, "Matricule: %d\nLogin: %s\nNom: %s\nPrenom: %s\nClasse: %d\nPresence: %d\nAbsence: %d\n",
               &etudiant.matricule, etudiant.login, etudiant.nom, etudiant.prenom, &etudiant.classe, &etudiant.presence, &etudiant.absence);
        User user;
        strcpy(user.login, etudiant.login);
        strcpy(user.password, "passer");
        user.type = 0;
        enregistrerUser(user);
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier");
        return;
    }

    
}