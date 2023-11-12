#include "FichierUtilisateur.h"


int estPresent(const char* nom)
{
  // TO DO
  int FileDescriptor;
  int i =0;
  UTILISATEUR utilisateur;
  FileDescriptor = open(FICHIER_UTILISATEURS, O_RDONLY);
  int nUtilisateur = (int) (lseek(FileDescriptor, 0, SEEK_END)/ sizeof(UTILISATEUR));
  lseek(FileDescriptor, 0, SEEK_SET);
  if(FileDescriptor>0){
    do{
      read(FileDescriptor, &utilisateur, sizeof(UTILISATEUR));
      i++;
      if(strcmp(utilisateur.nom, nom)==0){
        close(FileDescriptor);
        return i;
      }
    }while(i < nUtilisateur);
    close(FileDescriptor);
    return 0;
  }else return -1;
}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  int i =0;
  int hashresult = 0;
  while(motDePasse[i]){

    hashresult += (i +1 )* (int)motDePasse[i];
    i++;
  }
  hashresult%=97;
  return hashresult;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  // TO DO
  int FileDescriptor = open(FICHIER_UTILISATEURS, O_WRONLY|O_APPEND|O_CREAT, 0666);
  UTILISATEUR new_user;
  strcpy(new_user.nom, nom);
  new_user.hash= hash(motDePasse);
  printf("nom = %s     hash = %d",new_user.nom, new_user.hash);
  write(FileDescriptor, &new_user, sizeof(UTILISATEUR));
  close(FileDescriptor);
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  // TO DO
  UTILISATEUR utilisateur;
  int FileDescriptor = open(FICHIER_UTILISATEURS, O_RDONLY);
  if(FileDescriptor >=0){
    lseek(FileDescriptor, sizeof(UTILISATEUR)*pos, SEEK_SET);
    read(FileDescriptor, &utilisateur, sizeof(UTILISATEUR));
    //printf("%s\n",strerror(errno));
    printf("%s", utilisateur.nom);
    printf("%d \n", hash(motDePasse));
    if(hash(motDePasse)==utilisateur.hash){
      close(FileDescriptor);
      return 1;
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  // TO DO
  int i = 0;
  int FileDescriptor = open(FICHIER_UTILISATEURS, O_RDONLY);
  while(read(FileDescriptor, vecteur+i, sizeof(UTILISATEUR))>=sizeof(UTILISATEUR)){
    i++;
  }
  close(FileDescriptor);
  return i;
}

int getNUtilisateur(){
  int FileDescriptor = open(FICHIER_UTILISATEURS, O_RDONLY);
  int nUtilisateur = (int) (lseek(FileDescriptor, 0, SEEK_END)/ sizeof(UTILISATEUR));
  close(FileDescriptor);
  return nUtilisateur;
}
