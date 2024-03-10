// void listePresencesAuneDate(const char* nomFichier, int jour, int mois, int annee) {
//     FILE *fichier = fopen(nomFichier, "rb"); // Ouvrir le fichier en mode écriture
//     if(fichier != NULL) {
//         Presence presence;
        
//         while(fread(&presence, sizeof(Presence), 1, fichier) == 1){
//             printf( "mat Presence Date\n"); // Écrire l'en-tête dans le fichier
//             if(presence.date.jour == jour && presence.date.mois == mois && presence.date.annee == annee){
//                 printf("%d %d %d %d %d\n", presence.matricule, presence.presence, presence.date.jour, presence.date.mois, presence.date.annee);
//             }
//         }
//         fclose(fichier); // Fermer le fichier après écriture
//     }
// }

// //  void addPresence(const char* nomFichier, int matricule, int presence) {
// //     FILE *fichier = fopen(nomFichier, "rb");
   
// //     if(fichier != NULL ) {
// //         Presence p, p1;
// //         p.matricule = matricule;
// //         p.presence = presence;
// //         char date[20];  
// //         dateAujourdhui(date);
// //         p.date.jour = (date[0] - '0') * 10 + (date[1] - '0');
// //         p.date.mois = (date[3] - '0') * 10 + (date[4] - '0');
// //         p.date.annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
// //         p.date.heure = (date[11] - '0') * 10 + (date[12] - '0');
// //         p.date.minute = (date[14] - '0') * 10 + (date[15] - '0');
        
// //         int presenceDejaAjoutee = 0;

// //         // Vérifier si la présence est déjà ajoutée dans le fichier
// //         while (fread(&p1, sizeof(Presence), 1, fichier) == 1)  {
// //              printf( "La presence est déjà ajoutée dans le fichier.\n");
                   
// //             if(p1.matricule == p.matricule ) {
            
// //                 presenceDejaAjoutee = 1;
// //                 break;
// //             }
// //         }

// //         if (!presenceDejaAjoutee) {
// //             // Si la présence n'est pas déjà ajoutée, on l'ajoute
// //             fseek(fichier, 0, SEEK_END);
// //             fwrite(&p, sizeof(Presence), 1, fichier);
// //             printf( "\xE2\x9C\x85 code valide, présence à :  %d:%d\n", p.date.heure, p.date.minute);
// //         }

//         fclose(fichier);
//     } else {
//         printf( "Impossible d'ouvrir le fichier.\n");
//     }
// }
