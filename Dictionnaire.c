#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Mot{
    char fr[100];
    char def[200];
    char ang[100];
    struct Mot *next;
} Mot;

void convert_maj(char *mot, int taille){
    mot[0] = toupper(mot[0]);
    for(int i = 1; i < taille && mot[i] !='\0'; i++){
        mot[i] = tolower(mot[i]);
    }
}

Mot* Charger_dictionnaire(Mot *Dictionnaire){
    FILE* pf = fopen("dict.txt", "r");
        if(pf){
            Mot *temp = (Mot*)malloc(sizeof(Mot));
            if(!temp) {printf("Erreur d'allocation!\n"); exit(1); }

            while(fscanf(pf, "%99[^:] : %199[^:] : %99[^\n]", temp->fr, temp->def, temp->ang ) == 3){

                temp->next = Dictionnaire;
                Dictionnaire = temp;
                temp = (Mot*)malloc(sizeof(Mot));
                if(!temp) {printf("Erreur d'allocation!\n"); exit(1);}
            }

            free(temp);
            }
        else {printf("Erreur d'ouverture de fichier!\n");}
    fclose(pf);
    return Dictionnaire;
 }

 Mot* Ajouter_mot(Mot* Dictionnaire){
    char fr[100], def[200], ang[100];
    Mot* temp = (Mot*)malloc(sizeof(Mot));
    if(!temp) {printf("Erreur d'allocation!\n"); exit(1);}
    printf("\nSaisissez le mot en francais : ");
    fgets(fr, 100, stdin);
    fr[strcspn(fr, "\n")] = '\0';

    printf("\nSaisissez la definition du mot : ");
    fgets(def, 200, stdin);
    def[strcspn(def, "\n")] = '\0';

    printf("\nSaisissez la traduction en anglais : ");
    fgets(ang, 100, stdin);
    ang[strcspn(ang, "\n")] = '\0';

    strcpy(temp->fr, fr); strcpy(temp->def, def); strcpy(temp->ang, ang);
    temp->next = Dictionnaire;
    Dictionnaire = temp;
    return Dictionnaire;
 }

 void Chercher_mot(Mot* Dictionnaire){
    char mot[100];
    Mot* temp = Dictionnaire;
    printf("\nSaisissez le mot  que vous cherchez : ");
    fgets(mot, 100, stdin);
    mot[strcspn(mot, "\n")] = '\0';
    convert_maj(mot, 100);
    convert_maj(temp->fr, 100); convert_maj(temp->def, 200); convert_maj(temp->ang, 100);
    while(temp) {

        if(strcmp(temp->fr, mot) == 0 || strcmp(temp->ang, mot) == 0)
        {

            printf("%s : %s : %s", temp->fr, temp->def, temp->ang);
            return;
        }
        temp = temp->next;

    }
    printf("\nMot non trouve.\n");
}

void trouver_definition(Mot* Dictionnaire){
    char mot[100];
    Mot* temp = Dictionnaire;
    printf("\nSaisissez le mot  dont vous cherchez la definition : ");
    fgets(mot, 100, stdin);
    mot[strcspn(mot, "\n")] = '\0';
    convert_maj(mot, 100);
    convert_maj(temp->fr, 100); convert_maj(temp->def, 200); convert_maj(temp->ang, 100);

    while(temp) {

        if(strcmp(temp->fr, mot) == 0)
        {

            printf("%s : %s ", temp->fr, temp->def);
            return;
        }
        else if(strcmp(temp->ang, mot) == 0)
        {
            convert_maj(temp->def, 200); convert_maj(temp->ang, 100);
            printf("%s : %s", temp->ang, temp->def);
            return;
        }
        temp = temp->next;

    }
    printf("\nMot non trouvé.\n");

}

void trouver_traduction(Mot* Dictionnaire){
    char mot[100];
    Mot* temp = Dictionnaire;
    printf("\nSaisissez le mot  dont vous cherchez la traduction : ");
    fgets(mot, 100, stdin);
    mot[strcspn(mot, "\n")] = '\0';
    convert_maj(mot, 100);
    convert_maj(temp->fr, 100); convert_maj(temp->def, 200); convert_maj(temp->ang, 100);

    while(temp) {

        if(strcmp(temp->fr, mot) == 0 || strcmp(temp->ang, mot) == 0)
        {

            printf("%s : %s", temp->fr, temp->ang);
            return;
        }
        temp = temp->next;
    }
    printf("\nMot non trouvé.\n");

}

Mot* Supprimer_mot(Mot* Dictionnaire){
    char mot[100];
    Mot* temp = Dictionnaire;
    Mot* temp2 = NULL;
    printf("\nSaisissez le mot que vous voulez supprimer : ");
    fgets(mot, 100, stdin);
    mot[strcspn(mot, "\n")] = '\0';
    convert_maj(mot, 100);
    convert_maj(temp->fr, 100); convert_maj(temp->def, 200); convert_maj(temp->ang, 100);

    while(temp){
        if(strcmp(temp->fr, mot) == 0 || strcmp(temp->ang, mot) == 0)
        {
            if(temp2 == NULL){
                Dictionnaire = temp->next;
                free(temp);
                printf("\nMot supprime avec succes!\n");
                return Dictionnaire;
            }
            else{
                temp2->next = temp->next;
                free(temp);
                printf("Mot supprime avec succes!\n");
                return Dictionnaire;
            }
        }
        temp2 = temp;
        temp = temp->next;
    }
    printf("Mot non trouve!\n");
    return Dictionnaire;
}

void Sauvegarder(Mot* Dictionnaire){
    FILE* pf = fopen("dict.txt", "w");
    if(!pf){
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Mot* temp = Dictionnaire;
       while(temp){
        convert_maj(temp->fr, 100); convert_maj(temp->def, 200); convert_maj(temp->ang, 100);
        fprintf(pf, "%s : %s : %s", temp->fr, temp->def, temp->ang);
        temp = temp->next;
       }
fclose(pf);
printf("Dictionnaire sauvegarde avec succes!\n");
}

void Afficher_dict(Mot* Dictionnaire){
    printf("\nAffichage de votre dictionnaire: \n");
    while(Dictionnaire){
        convert_maj(Dictionnaire->fr, 100); convert_maj(Dictionnaire->def, 200); convert_maj(Dictionnaire->ang, 100);
        printf("%s : %s : %s \n", Dictionnaire->fr, Dictionnaire->def, Dictionnaire->ang);
        Dictionnaire = Dictionnaire->next;
    }
}




int main(){
    int choix;
    Mot* Dictionnaire = NULL;
    Dictionnaire = Charger_dictionnaire(Dictionnaire);

do{
    printf("\n============================================MENU============================================\n");
    printf("1. Afficher Dictionnaire\t\t\t\t 5. Chercher un mot\n");
    printf("2. Ajouter un mot\t\t\t\t\t 6. Supprimer un mot\n");
    printf("3. Trouver la definition \t\t\t\t 7. Sauvegarder\n");
    printf("4. Traduire un mot  \t\t\t\t\t 8. Quitter\n");
    printf("\nChoisissez une option : ");
    scanf("%d", &choix);
    getchar();

    switch (choix){
        case 1:
            Afficher_dict(Dictionnaire);
            break;
        case 2:
            Dictionnaire = Ajouter_mot(Dictionnaire);
            break;
        case 3:
            trouver_definition(Dictionnaire);
            break;
        case 4:
            trouver_traduction(Dictionnaire);
            break;
        case 5:
            Chercher_mot(Dictionnaire);
            break;
        case 6:
            Dictionnaire = Supprimer_mot(Dictionnaire);
            break;
        case 7:
            Sauvegarder(Dictionnaire);
            break;
        case 8:
            printf("\nAu revoir!\n");
            break;
        default:
            printf("\nChoix invalide!\n");
            break;
    }
} while(choix != 8);

 while (Dictionnaire) {
        Mot* temp = Dictionnaire;
        Dictionnaire = Dictionnaire->next;
        free(temp);
    }
return 0;

}
