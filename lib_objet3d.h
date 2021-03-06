#ifndef _LIB_OBJET3D_H_
#define _LIB_OBJET3D_H_

#include "lib_surface.h"
#include "lib_3d.h"

typedef enum {
  false=0, true
} t_bool;

typedef struct __liste3d t_maillon;

struct __liste3d
{
  t_triangle3d *face;
  Uint32*couleur;
  t_maillon *pt_suiv;
  double z_index;
};

typedef struct __listep3d t_chaine;

struct __listep3d
{
  t_point3d *point;
  t_chaine *pt_suiv;
};

typedef struct __objet3d t_objet3d;

struct __objet3d
{
  t_bool est_trie;
  t_bool est_camera;
  t_maillon *tete;
  t_chaine *chaine;
};
//renvoie la moyenne des coor z du triangle
double moy_z(t_triangle3d *t);
//update la valeur des z_index pour une liste chainer 
void remplir_z_index(t_maillon *pt_maillon);
//renvoie une chaine créer a partir d'un point
t_chaine* __cree_chaine(t_point3d *point);
void __insere_tete_chaine(t_objet3d *pt_objet, t_chaine *pt_chaine);
t_maillon* __cree_maillon(t_triangle3d *face, Uint32*couleur);
void __insere_tete(t_objet3d *pt_objet, t_maillon *pt_maillon);
// retourne un object alloue mais avec une liste vide de faces
t_objet3d* objet_vide();
// retourne un object de type camera alloue (liste vide de faces evidement)
t_objet3d* camera(); // == objet vide
// retourne un object alloue mais avec une liste de 12 faces centrees sur (0,0,0) de dimension lx,ly,lz
t_objet3d* parallelepipede(double lx, double ly, double lz,Uint32*c);
// retourne un object alloue mais avec une liste de faces centrees sur (0,0,0) de rayon r avec nlat latitudes et nlong longitudes
t_objet3d* sphere(double r, double nlat, double nlong,Uint32*c);
t_objet3d* demisphere(double r, int nlat, int nlong,Uint32 tabc[nlat][nlong]);
t_objet3d* geode(double r,Uint32*c);
t_objet3d* cone(double lh,double r, double nlat, double nlong,Uint32*c);
t_objet3d* cylindre(double lh,double r, double nlong,Uint32*c);
t_objet3d* tore(double r1,double r2,double nlat,double nlong,Uint32*c);
t_objet3d* n64(double r);
t_objet3d* ellipse(double a,double b,int pres,Uint32*c);
// retourne un object alloue mais avec une liste de faces centrees sur (0,0,0) de rayon r avec nlat latitudes et nlong longitudes, prend des couleurs rouges et blanches sur des carres adjacents, cf google
t_objet3d* sphere_amiga(double r, double nlat, double nlong,Uint32*c1,Uint32*c2);
// retourne un object alloue mais avec une liste de faces centrees sur (0,0,0) : c'est un rectangle marron (plusieurs marrons possibles) et une pyramide au verte (plusieurs verts possibles) au sommet
t_objet3d* arbre(double lx, double ly, double lz);
// retourne un object alloue mais avec une liste de faces centrees sur (0,0,0) de taille lx,0,lz decoupe avec nx et nz carres alternativement noirs et blancs
t_objet3d* damier(double lx, double lz, double nx, double nz,Uint32*c1,Uint32*c2);
// affiche toutes les faces de l'objet sur la surface
void dessinerObjet3d(t_surface *surface, t_objet3d* pt_objet,double h);
// retourne un object alloue dont toutes les faces sont une copie des faces de l'objet d'origine
t_objet3d *copierObjet3d(t_objet3d *o); // attention, effectue une copie
// o = o + o2 : transforme l'objet o en la somme des deux objets, il suffit de brancher la liste des faces de o2 a la fin de celle de o
void composerObjet3d(t_objet3d* o, t_objet3d* o2);
// libere la memoire occupee par l'objet, attention il faut aussi liberer les faces de o
void libererObjet3d(t_objet3d *o);
// effectue une translation sur les faces de l'objet selon le vecteur donne en parametre
void translationObjet3d(t_objet3d* pt_objet, t_point3d *vecteur);
// effectue une rotation sur les faces de l'objet selon le vecteur donne en parametre
void rotationObjet3d(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);
// effectue une transformation arbitraire sur les faces de l'objet selon le vecteur donne en parametre, vous pourrez ensuite modifier les deux fonctions precedentes pour faire appel a cette fonction
void transformationObjet3d(t_objet3d* pt_objet, double mat[4][4]);

#endif
