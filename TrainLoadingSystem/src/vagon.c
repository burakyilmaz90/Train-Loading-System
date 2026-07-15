#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\vagon.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sona yeni vagon ekle
Vagon *add_vagon(Vagon *lastvagon, int id, float max_weight)
{
    Vagon *new_vagon = (Vagon *)func_malloc(sizeof(Vagon));
    new_vagon->vagon_id = id;
    new_vagon->current_weight = 0;
    new_vagon->max_weight = max_weight;
    new_vagon->current_weight = 0;
    new_vagon->loaded_material = NULL;
    new_vagon->next = NULL;
    new_vagon->prev = lastvagon;

    if (lastvagon)
    {
        lastvagon->next = new_vagon;
    }
    return new_vagon;
}

// vagon kaldır
void remove_vagon(Vagon **first_vagon, Vagon *removed_vagon)
{
    if (first_vagon == NULL || removed_vagon == NULL) // İlk vagon yoksa veya kaldırılacak vagon yoksa error
    {
        error_message("FAIL");
        return;
    }

    Vagon *flagprev = removed_vagon->prev;
    Vagon *flagnext = removed_vagon->next;
    if (removed_vagon->prev)
    {

        flagprev->next = removed_vagon->next;
    }
    else
    {
        *first_vagon = removed_vagon->next; // ilk vagon kalkarsa ilk vagon düzenlemesi yapar.
    }
    if (removed_vagon->next)
    {
        flagnext->prev = flagprev->next;
    }
    free_loaded_material(removed_vagon->loaded_material);
    free(removed_vagon);
}

// vagonun durumunu göster
void display_vagon(Vagon *vagon)
{
    if (vagon == NULL)
    {
        error_message("Invalid vagon to display");
        return;
    }
    printf("Wagon ID : %d\n", vagon->vagon_id);
    printf("Max weight : %.2f kg\n", vagon->max_weight);
    printf("Current weight : %.2f kg\n", vagon->current_weight);
    if (vagon->loaded_material)
    {
        while (load_material != NULL)
        {
            display_loaded_material(vagon->loaded_material);
            vagon->loaded_material = vagon->loaded_material->next;
        }
    }
    else
    {
        printf("There is no materials in this vagon");
    }
}

// vagonları serbest bırak
void free_allvagon(Vagon *headvagon)
{
    while (headvagon)
    {
        Vagon *flag = headvagon;
        headvagon = headvagon->next;
        free_loaded_material(flag->loaded_material);
        free(flag);
    }
}

// Belirli vagona malzeme yükle
void add_matarial_specific_vagon(Vagon *vagon, MaterialType *material, int quantity)
{
    if (vagon == NULL || material == NULL)
    {
        printf("Wagon or material is NULL.\n");
        return;
    }

    int loadable_quantity = (vagon->max_weight - vagon->current_weight) / material->weight;

    // Hafif malzeme kontrolü
    LoadedMaterial *current_material = vagon->loaded_material;
    while (current_material)
    {
        if (current_material->type->weight < material->weight)
        {
            printf("Cannot load heavier material (%s) on top of lighter material (%s) in this wagon.\n",
                   material->name, current_material->type->name);
            return;
        }
        current_material = current_material->next;
    }

    int load_quantity = (quantity > loadable_quantity) ? loadable_quantity : quantity;

    if (load_quantity <= 0)
    {
        printf("The wagon does not have enough capacity.\n");
        return;
    }

    LoadedMaterial *new_material = create_loaded_material(material, load_quantity);
    if (new_material == NULL)
    {
        return; // Bellek tahsisi başarısızsa çıkış yap
    }

    new_material->next = vagon->loaded_material;
    if (vagon->loaded_material)
    {
        vagon->loaded_material->prev = new_material;
    }
    vagon->loaded_material = new_material;

    vagon->current_weight += load_quantity * material->weight;
    material->loaded += load_quantity;
    material->quantity -= load_quantity;

    printf("Successfully loaded %d of %s into the wagon.\n", load_quantity, material->name);
}

// Belirli vagondan malzemeyi boşalt
void remove_material_specific_vagon(Vagon *vagon, MaterialType *material, int quantity)
{

    if (vagon == NULL || material == NULL)
    {
        printf("Vagon or material is NULL!\n");
        return;
    }

    LoadedMaterial *current_material = vagon->loaded_material;
    LoadedMaterial *prev_material = NULL;

    while (current_material != NULL)
    {
        if (current_material->type == material)
        {
            // Eğer malzeme bulunduysa ve yeterli miktarda varsa, çıkar
            if (current_material->quantity >= quantity)
            {
                current_material->quantity -= quantity;

                // Eğer malzeme miktarı 0'a düşerse, bu malzemeyi listeden kaldır
                if (current_material->quantity == 0)
                {
                    if (prev_material == NULL)
                    {
                        vagon->loaded_material = current_material->next;
                    }
                    else
                    {
                        prev_material->next = current_material->next;
                    }

                    free(current_material);
                    printf("Material '%s' has been removed from the wagon.\n", material->name);
                }
                else
                {
                    printf("Material '%s' quantity reduced by %d.\n", material->name, quantity);
                }

                // Kalan ağırlığı güncelle ve kalan kapasiteyi hesapla
                vagon->current_weight -= (material->weight * quantity);
                float remaining_capacity = vagon->max_weight - vagon->current_weight;

                // Kalan kapasiteyi yazdır
                printf("Remaining capacity in the wagon: %.2f\n", remaining_capacity);
                return;
            }
            else
            {
                printf("Not enough quantity of material '%s' to remove.\n", material->name);
                return;
            }
        }

        prev_material = current_material;
        current_material = current_material->next;
    }

    printf("Material '%s' not found in this wagon.\n", material->name);
}
