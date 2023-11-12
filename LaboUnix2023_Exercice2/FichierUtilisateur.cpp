#include "FichierUtilisateur.h"
#include <cstdio>
#include <cstdlib>
#include <sys/type.h>
#include <sys/stat.h>
#include <fcntl.h>

int estPresent(const char* nom)
{
  // TO DO
  int FileDescriptor;
  int i =0;
  struct UTILISATEUR utilisateur;
  FileDescriptor = open(FICHIER_UTILISATEURS, O_RDONLY);
  int nUtilisateur = (int) (lseek(FileDescriptor, 0, SEEK_END)/ sizeof(struct UTILISATEUR));
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
    hashresult += i * motDePasse[i]
    i++
  }
  hashresult%=97;
  return hashresult;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  // TO DO
  int FileDescriptor = open(FICHIER_UTILISATEURS, O_WRONLY|O_APPEND|O_CREAT, 0760);
  struct UTILISATEUR new_user = {nom, hash(motDePasse)};
  write(FileDescriptor, new_user, sizeof(new_user));
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
    if(hash(motDePasse)==utilisateur.hash){
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
  return i;
}
