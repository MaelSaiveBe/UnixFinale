#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include "protocole.h" // contient la cle et la structure d'un message
#include <unistd.h>
#include <cstring>
int idQ;
int pid1,pid2;


int main()
{
  MESSAGE requete;
  pid_t destinataire;

  // Armement du signal SIGINT
  // TO DO (etape 6)

  // Creation de la file de message
  fprintf(stderr,"(SERVEUR) Creation de la file de messages\n");
  // TO DO (etape 2)
  if((idQ = msgget(CLE, IPC_CREAT|0666))==-1)
  {
    perror("erreur Lors de la creaton de la  file (msgget)");
    exit(1);
  }


  // Attente de connection de 2 clients
  fprintf(stderr,"(SERVEUR) Attente de connection d'un premier client...\n");
  // TO DO (etape 5)
  msgrcv(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 1, 0);
  if(pid1 != requete.expediteur)pid1 = requete.expediteur;
  else{
    pid2 = requete.expediteur;
  }
  fprintf(stderr,"(SERVEUR) Attente de connection d'un second client...\n");
  // TO DO (etape 5)

  while(1) 
  {
    // TO DO (etapes 3, 4 et 5)
  	fprintf(stderr,"(SERVEUR) Attente d'une requete...\n");
    if(msgrcv(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 1, 0) == -1)
    {
      perror("(SERVEUR) erreur Lors de la reception de la requete...");
      exit(1);
    }
    fprintf(stderr,"(SERVEUR) Requete recue de %d : --%s--\n",requete.expediteur,requete.texte);
    //Traitement de la requete
    MESSAGE reponse;
    reponse.expediteur = 1;

    char buffer[80];
    strcat(strcpy(buffer,"(SERVEUR)"), requete.texte);
    strcpy(reponse.texte, buffer);
    reponse.type = requete.expediteur;
    fprintf(stderr,"(SERVEUR) Envoi de la reponse a %d\n",requete.expediteur);
    if(msgsnd(idQ, &reponse, sizeof(MESSAGE)- sizeof(long), 0) == -1)
    {
      perror("(SERVEUR) Erreur lors de l'envoie de la Reponse...\n");
      exit(1);
    }
    if(reponse.type == pid1)kill(pid1, SIGUSR1);
    if(reponse.type == pid2)kill(pid2, SIGUSR1);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 6)
