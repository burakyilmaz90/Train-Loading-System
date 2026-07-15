#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\train.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
bool can_load = true;

// tren oluşturma
Train *create_train(char *train_id)
{
    Train *new_train = (Train *)func_malloc(sizeof(Train));
    if (new_train == NULL)
    {
        error_message("Creating train failed.");
        return NULL;
    }
    strcpy(new_train->train_id, train_id);
    new_train->first_wagon = NULL;
    return new_train;
}
int can_add_material(LoadedMaterial *loaded_materials, MaterialType *new_material)
{
    while (loaded_materials)
    {
        if (loaded_materials->type->weight < new_material->weight)
        {
            return 0; // Hafif malzemenin üzerine ağır malzeme yüklenemez
        }
        loaded_materials = loaded_materials->next;
    }
    return 1; // Malzeme eklenebilir
}

// baştan itibaren doldurma
void load_material(Train *train, MaterialType *material, float weight, int quantity)
{
    if (train == NULL || material == NULL)
    {
        printf("Train or material is NULL!\n");
        return;
    }

    int remaining_quantity = quantity; // Başlangıçta yüklenmesi gereken miktar
    Vagon *current_wagon = train->first_wagon;

    // Eğer tren boşsa, bir vagon ekle
    if (current_wagon == NULL)
    {
        current_wagon = add_vagon(NULL, 1, 1000.0); // İlk vagonu ekle
        if (current_wagon == NULL)
        {
            printf("Failed to create the first wagon.\n");
            return;
        }
        train->first_wagon = current_wagon;
        train->vagon_count = 1;
    }

    // Yükleme işlemi başlıyor
    while (remaining_quantity > 0)
    {
        // Vagonun kalan kapasitesini hesapla
        float remaining_capacity = current_wagon->max_weight - current_wagon->current_weight;
        int max_loadable_quantity = (int)(remaining_capacity / material->weight);

        // Bu vagona yüklenebilecek miktar
        int load_quantity = (remaining_quantity > max_loadable_quantity) ? max_loadable_quantity : remaining_quantity;

        // Vagonun önceki malzemelerine bakıyoruz
        LoadedMaterial *existing_material = current_wagon->loaded_material;
        bool can_load = true;

        // Eğer vagonda zaten malzeme varsa, yeni malzemenin yüklenip yüklenemeyeceğini kontrol et
        while (existing_material)
        {
            // Eğer yüklenen malzeme hafifse ve yeni malzeme daha ağırsa, yüklenemez
            if (existing_material->type->weight < material->weight)
            {
                printf("Cannot load heavier material (%s) on top of lighter material (%s) in wagon %d.\n",
                       material->name, existing_material->type->name, current_wagon->vagon_id);
                can_load = false;
                break;
            }
            existing_material = existing_material->next;
        }

        // Eğer yüklenmesine izin veriliyorsa
        if (can_load && load_quantity > 0)
        {
            // Vagonun ağırlığını güncelle
            current_wagon->current_weight += load_quantity * material->weight;
            remaining_quantity -= load_quantity;

            // Vagona malzeme ekle veya var olan malzemeyi güncelle
            existing_material = current_wagon->loaded_material;
            while (existing_material)
            {
                if (existing_material->type == material)
                {
                    existing_material->quantity += load_quantity; // Miktarı güncelle
                    break;
                }
                existing_material = existing_material->next;
            }

            if (existing_material == NULL)
            {
                // Yeni malzeme düğümü oluştur ve vagona ekle
                LoadedMaterial *new_loaded_material = malloc(sizeof(LoadedMaterial));
                if (new_loaded_material == NULL)
                {
                    printf("Memory allocation failed for LoadedMaterial.\n");
                    return;
                }
                new_loaded_material->type = material;
                new_loaded_material->quantity = load_quantity;
                new_loaded_material->next = current_wagon->loaded_material;
                new_loaded_material->prev = NULL;

                if (current_wagon->loaded_material)
                {
                    current_wagon->loaded_material->prev = new_loaded_material;
                }
                current_wagon->loaded_material = new_loaded_material;
            }

            printf("Loaded %d of %s into wagon %d. Remaining: %d\n",
                   load_quantity, material->name, current_wagon->vagon_id, remaining_quantity);
        }

        // Eğer bu vagon tamamen dolmuşsa ve hala yükleme yapılacak malzeme varsa, bir sonraki vagona geç
        if (remaining_quantity > 0)
        {
            if (current_wagon->next == NULL)
            {
                // Yeni vagon ekleyin ve doğru ID'yi atayın
                int a = current_wagon->vagon_id + 1;
                current_wagon->next = add_vagon(current_wagon, a, 1000.0);
                if (current_wagon->next == NULL)
                {
                    printf("Failed to add a new wagon.\n");
                    return;
                }
                train->vagon_count++;
                // current_wagon->next->vagon_id = train->vagon_count;  // Yeni vagon ID'sini güncelle
            }
            current_wagon = current_wagon->next;
        }
    }
}

void unload_metarial(Train *train, MaterialType *material, int quantity)
{
    if (train == NULL || train->first_wagon == NULL || material == NULL)
    {
        error_message("Train, material or wagon not defined");
        return;
    }

    // Tren ve malzeme geçerli mi kontrolü
    Vagon *current_wagon = train->first_wagon;
    while (current_wagon != NULL && quantity > 0)
    {
        // Vagon içerisindeki malzeme bulunup, çıkartılacak
        LoadedMaterial *current_material = current_wagon->loaded_material;
        while (current_material != NULL)
        {
            if (current_material->type == material)
            {
                // Malzeme bulundu ve yeterli miktarda varsa çıkar
                if (current_material->quantity >= quantity)
                {
                    current_material->quantity -= quantity;
                    quantity = 0; // Hedeflenen miktar bitti

                    // Eğer miktar sıfır olursa, malzeme çıkarılabilir
                    if (current_material->quantity == 0)
                    {
                        remove_material_specific_vagon(current_wagon, material, current_material->quantity);
                    }
                    printf("Material '%s' unloaded successfully.\n", material->name);
                    return;
                }
                else
                {
                    // Yeterli malzeme yoksa, sadece kalan miktar kadar boşalt
                    quantity -= current_material->quantity;
                    current_material->quantity = 0;
                    remove_material_specific_vagon(current_wagon, material, current_material->quantity);
                    printf("Not enough material, remaining quantity: %d\n", quantity);
                }
            }
            current_material = current_material->next;
        }
        current_wagon = current_wagon->next; // Bir sonraki vagona geç
    }

    if (quantity > 0)
    {
        printf("Could not unload all the material. Remaining quantity: %d\n", quantity);
    }
}

// trenin tamamını boşaltma
void empty_train(Train *train)
{
    if (train == NULL)
    {
        error_message("Train is not defined");
        return;
    }
    free_allvagon(train->first_wagon);
    train->first_wagon = NULL;
    printf("Train emptied successfully");
}

// Tren durumunu görüntüleme
void display_train(Train *train)
{
    if (train == NULL)
    {
        printf("Train is not defined.\n");
        return;
    }

    printf("Train ID: %s\n", train->train_id);

    if (train->first_wagon == NULL)
    {
        printf("Train has no wagons.\n");
        return;
    }

    Vagon *current_wagon = train->first_wagon;
    while (current_wagon)
    {
        printf("WAGON: %d\n", current_wagon->vagon_id);
        printf("  Max Weight: %.2f, Current Weight: %.2f\n",
               current_wagon->max_weight, current_wagon->current_weight);

        LoadedMaterial *current_material = current_wagon->loaded_material;
        if (current_material == NULL)
        {
            printf("  No materials in this wagon.\n");
        }
        else
        {
            while (current_material)
            {
                printf("  - Material: %s, Quantity: %d, Weight per unit: %.2f\n",
                       current_material->type->name,
                       current_material->quantity, // Doğru miktarı göstermek için quantity kullanılıyor
                       current_material->type->weight);
                current_material = current_material->next;
            }
        }

        float remaining_capacity = current_wagon->max_weight - current_wagon->current_weight;
        printf("  Remaining Capacity: %.2f\n", remaining_capacity);

        current_wagon = current_wagon->next;
    }
}
