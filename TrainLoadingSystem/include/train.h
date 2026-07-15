#ifndef TRAIN_H

#define TRAIN_H
#include "vagon.h"

typedef struct {
    char train_id[20];
    struct Vagon* first_wagon;
    int vagon_count;
} Train;

//*****FUNCTIONS*****
int can_add_material(LoadedMaterial* loaded_materials, MaterialType* new_material);
Train* create_train(char* train_id); //tren oluşturma
void load_material(Train* train , MaterialType* material , float weight , int quantity); //baştan itibaren doldurma
void unload_metarial(Train* train ,MaterialType* material , int quantity);  //ürün çıkartma
void empty_train (Train* train); //trenin tamamını boşaltma
void display_train (Train* Train); // tren durumunu görüntüle

#endif