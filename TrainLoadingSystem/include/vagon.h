#ifndef VAGON_H

#define VAGON_H
#include "material.h"

typedef struct Vagon
{
    int vagon_id;
    float max_weight;
    float current_weight;
    LoadedMaterial* loaded_material;
    struct Vagon* next;
    struct Vagon* prev;
} Vagon;


//*****FUNCTIONS*****
Vagon* add_vagon(Vagon* lastvagon , int id , float max_weight); //sona yeni vagon ekle
void remove_vagon(Vagon** first_vagon , Vagon* removed_vagon);  //vagon kaldır
void display_vagon(Vagon* vagon); //vagonun durumunu göster
void free_allvagon(Vagon* headvagon); //vagonları serbest bırak
// TRENDE YAPIALACAK void add_matarial(Vagon* headvagon, MaterialType* metarial , int quantity);//Trenin başından itibaren ilk uygun vagondan başlayarak malzeme yükle
void add_matarial_specific_vagon(Vagon* vagon , MaterialType* matarial , int quantity);//Belirli vagona malzeme yükle
// TRENDE YAPILACAK void remove_matarial(Vagon* lastvagon, MaterialType* material, int quantity); // Trenin sonundan itibaren ilk uygun vagondan başlayarak malzemeyi boşalt
void remove_material_specific_vagon(Vagon* vagon, MaterialType* material , int quantity);//Belirli vagondan malzemeyi boşalt


#endif
