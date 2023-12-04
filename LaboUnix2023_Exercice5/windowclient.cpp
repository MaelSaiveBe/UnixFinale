#include "windowclient.h"
#include "ui_windowclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


extern WindowClient *w;

#include "protocole.h" // contient la cle et la structure d'un message

extern char nomClient[40];
int idQ; // identifiant de la file de message

void handlerSIGUSR1(int sig);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowClient)
{
  ui->setupUi(this);
  setWindowTitle(nomClient);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(CLIENT %s %d) Recuperation de l'id de la file de messages\n",nomClient,getpid());
  // TO DO (etape 2)
  if((idQ = msgget(CLE, 0)) == -1){
    perror("Erreur lors de la récupération de la clé");
    exit(1);
  }

  // Envoi d'une requete d'identification
  // TO DO (etape 5)
  MESSAGE msg
  msg.type = 1;
  strcpy(msg.texte, "Identification");
  msg.expediteur = getpid();
  msgsnd(idQ, &msg, sizeof(MESSAGE) - sizeof(long),IPC_NOWAIT);
  // Armement du signal SIGUSR1
  // TO DO (etape 4)
  struct sigaction sigUSR1;
  sigUSR1.sa_handler = handlerSIGUSR1;
  sigUSR1.sa_flags=0;
  sigemptyset(&sigUSR1.sa_mask);
  if(sigaction(SIGUSR1, &sigUSR1, NULL)==-1)
  {
    perror("erreur SigAction (sigUSR1)");
    exit(1);
  }
}

WindowClient::~WindowClient()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setRecu(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditRecu->clear();
    return;
  }
  ui->lineEditRecu->setText(Text);
}

void WindowClient::setAEnvoyer(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditEnvoyer->clear();
    return;
  }
  ui->lineEditEnvoyer->setText(Text);
}

const char* WindowClient::getAEnvoyer()
{
  if (ui->lineEditEnvoyer->text().size())
  { 
    strcpy(aEnvoyer,ui->lineEditEnvoyer->text().toStdString().c_str());
    return aEnvoyer;
  }
  return NULL;
}

const char* WindowClient::getRecu()
{
  if (ui->lineEditRecu->text().size())
  { 
    strcpy(recu,ui->lineEditRecu->text().toStdString().c_str());
    return recu;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonEnvoyer_clicked()
{
  fprintf(stderr,"Clic sur le bouton Envoyer\n");
  // TO DO (etapes 2, 3, 4)
  fprintf(stderr, "I Was Here 1");
  MESSAGE msgsent;
  fprintf(stderr, "I Was Here 2");
  if(getAEnvoyer() == NULL){
    fprintf(stderr, "MESSAGE INVALIDE");
    return;
  }
  strcpy(msgsent.texte, getAEnvoyer());
  msgsent.expediteur =getpid();
  fprintf(stderr,"(CLIENT) PID Expediteur: %d\n",msgsent.expediteur);
  fprintf(stderr,"(CLIENT) PID Expediteur: %d\n",getpid());
  msgsent.type = 1;
  fprintf(stderr, "I Was Here 3");
  

  if(msgsnd(idQ, &msgsent, sizeof(MESSAGE) - sizeof(long),IPC_NOWAIT)== -1)
  {
    perror("erreur lors de l'envoie du message");
  }
  fprintf(stderr, "I Was Here 4");

}

void WindowClient::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  exit(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 4)
void handlerSIGUSR1(int sig){
  MESSAGE msgreceived;

  fprintf(stderr, "(CLIENT)%d signal SIGUSR1(%d) Recus: Lecture du Messages \n",getpid(),sig);

  msgrcv(idQ,&msgreceived, sizeof(MESSAGE) - sizeof(long), getpid(), 0);
  w->setRecu(msgreceived.texte);
}
