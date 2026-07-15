#ifndef MATERIAL_H

#define MATERIAL_H

typedef struct {
    char name[50];       //malzeme adı
    char short_name[2];     //Kısaltma
    float weight;        //malzeme ağırlığı
    int quantity;        //toplam elde olan
    int loaded;          //trene yüklenen
} MaterialType;

typedef struct LoadedMaterial {
MaterialType* type;  
struct LoadedMaterial *next, *prev;
int quantity;
} LoadedMaterial;


//*****FUNCTIONS***** 


MaterialType* create_metarial(char* name, float weight, int quantity);
void loading_material(MaterialType* material , int quantity);
void remove_material (MaterialType* material , int quantity);
LoadedMaterial* create_loaded_material(MaterialType* material , int quantity);
void display_loaded_material(LoadedMaterial* material);
void free_loaded_material(LoadedMaterial* material);
MaterialType* find_or_create_material(const char* name, float weight);


#endif
