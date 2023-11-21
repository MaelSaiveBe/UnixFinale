#include "mainwindowex4.h"
#include "ui_mainwindowex4.h"

extern MainWindowEx4 *w;

int idFils1, idFils2, idFils3;
// TO DO : HandlerSIGCHLD
void handlerSIGCHILD(int);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindowEx4::MainWindowEx4(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx4)
{
  ui->setupUi(this);
  ui->pushButtonAnnulerTous->setVisible(false);

  // armement de SIGCHLD
  // TO DO
  struct sigaction sigchild;
  sigchild.sa_handler = handlerSIGCHILD;
  sigchild.sa_flags=0;
  sigemptyset(&sigchild.sa_mask);
  if(sigaction(SIGCHLD, &sigchild, NULL)==-1)
  {
    perror("erreur SigAction");
    exit(1);
  }
}

MainWindowEx4::~MainWindowEx4()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::setGroupe1(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx4::setGroupe2(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx4::setGroupe3(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx4::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx4::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx4::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx4::traitement1Selectionne()
{
  return ui->checkBoxTraitement1->isChecked();
}

bool MainWindowEx4::traitement2Selectionne()
{
  return ui->checkBoxTraitement2->isChecked();
}

bool MainWindowEx4::traitement3Selectionne()
{
  return ui->checkBoxTraitement3->isChecked();
}

const char* MainWindowEx4::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::on_pushButtonDemarrerTraitements_clicked()
{
  fprintf(stderr,"Clic sur le bouton Demarrer Traitements\n");
  // TO DO
  if(traitement1Selectionne())
  {
    fprintf(stderr, "Traitement 1 Selected");
    if ((idFils1 = fork()) == -1)
    {
      perror("(PERE) Erreur de fork()");
      exit(1);
    }
    if(!idFils1)
    {
      fprintf(stderr,"ENTRER FILS 1\n"); 
      if(execl("./Traitement","Traitement", getGroupe1(), "200", NULL)== -1)
      {
        perror("Erreur de execl");
        exit(1);
      }else{
        printf("fin du fils...");
        exit(0);
      }
    }
  }

  if(traitement2Selectionne())
  {
    fprintf(stderr, "Traitement 1 Selected");
    if ((idFils2 = fork()) == -1)
    {
      perror("(PERE) Erreur de fork()");
      exit(1);
    }
    if(!idFils2)
    {
      fprintf(stderr,"ENTRER FILS 1\n"); 
      if(execl("./Traitement","Traitement", getGroupe2(), "450", NULL)== -1)
      {
        perror("Erreur de execl");
        exit(1);
      }else{
        printf("fin du fils...");
        exit(0);
      }
    }
  }

  if(traitement3Selectionne())
  {
    fprintf(stderr, "Traitement 3 Selected");
    if ((idFils3 = fork()) == -1)
    {
      perror("(PERE) Erreur de fork()");
      exit(1);
    }
    if(!idFils3)
    {
      fprintf(stderr,"ENTRER FILS 3\n"); 
      if(execl("./Traitement","Traitement", getGroupe3(), "700", NULL)== -1)
      {
        perror("Erreur de execl");
        exit(1);
      }else{
        printf("fin du fils...");
        exit(0);
      }
    }
  }
}

void MainWindowEx4::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");
  setGroupe1("");
  setGroupe2("");
  setGroupe3("");
  // TO DO
}

void MainWindowEx4::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  // TO DO
}

void MainWindowEx4::on_pushButtonAnnuler1_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler1\n");
  kill(idFils1, SIGUSR1);
  // TO DO
}

void MainWindowEx4::on_pushButtonAnnuler2_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler2\n");
  // TO DO
    kill(idFils2, SIGUSR1);

}

void MainWindowEx4::on_pushButtonAnnuler3_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler3\n");
  // TO DO
    kill(idFils3, SIGUSR1);

}

void MainWindowEx4::on_pushButtonAnnulerTous_clicked()
{
  // fprintf(stderr,"Clic sur le bouton Annuler tout\n");
  // NOTHING TO DO --> bouton supprimé
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Handlers de signaux //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TO DO : HandlerSIGCHLD
void handlerSIGCHILD(int sigint){
  int id, status;
  id = wait(&status);
  if(id == idFils1)w->setResultat1(WEXITSTATUS(status));
  if(id == idFils2)w->setResultat2(WEXITSTATUS(status));
  if(id == idFils3)w->setResultat3(WEXITSTATUS(status));
  fprintf(stderr, "signal sigCHILD recus");
}