#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\material.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MaterialType *create_metarial(char *name, float weight, int quantity)
{
    MaterialType *material = (MaterialType *)func_malloc(sizeof(MaterialType));
    strcpy(material->name, name);
    material->weight = weight;
    material->quantity = quantity;
    material->loaded = 0; // default value
}

void loading_material(MaterialType *material, int box)
{
    MaterialType material1;
    printf("1- large box \n 2- medium box \n 3-small box");
    printf("please choose the box:\n ");
    scanf("%d", &box);
    if (scanf("%d", &box) != 1 || scanf("%d", &box) != 2 || scanf("%d", &box) != 3)
    {
        printf("Invalid input! Please enter a number.\n");
        return;
    }
    else
    {
        if (box == 1)
        {
            strcpy(material1.name, "Steel");
            material1.weight = 200;
            printf("please enter the kg: \n");
            scanf("%f", &material1.loaded);
            strcpy(material1.short_name, "LB");
        }
        else if (box == 2)
        {
            strcpy(material1.name, "Aluminium");
            material1.weight = 150;
            printf("please enter the kg: \n");
            scanf("%f", &material1.loaded);
            strcpy(material1.short_name, "MB");
        }
        else if (box == 3)
        {
            strcpy(material1.name, "Wood");
            material1.weight = 100;
            printf("please enter the kg: \n");
            scanf("%f", &material1.loaded);
            strcpy(material1.short_name, "SB");
        }
    }
}
void remove_material(MaterialType *material, int quantity)
{
    if (material == NULL)
    {
        error_message("Material does not exist!");
        return;
    }
    if (material->quantity < quantity)
    {
        error_message("Not enough material available to remove!");
        return;
    }
    material->quantity -= quantity;
    printf("Removed %d units of %s. Remaining: %d\n", quantity, material->name, material->quantity);
}

LoadedMaterial *create_loaded_material(MaterialType *material, int quantity)
{
    if (material == NULL || quantity <= 0)
    {
        printf("Invalid material or quantity.\n");
        return NULL;
    }

    LoadedMaterial *new_material = (LoadedMaterial *)malloc(sizeof(LoadedMaterial));
    if (new_material == NULL)
    {
        printf("Memory allocation failed for LoadedMaterial.\n");
        return NULL;
    }

    new_material->type = material;
    new_material->quantity = quantity; // Doğru miktarı ata
    new_material->next = NULL;
    new_material->prev = NULL;

    return new_material;
}

// Yüklenmiş malzemeyi ekrana yazdırma
void display_loaded_material(LoadedMaterial *material)
{

    if (material == NULL)
    {
        error_message("No loaded material to display.\n");
        return;
    }

    if (material->type == NULL)
    {
        error_message("Material type is not defined.\n");
        return;
    }

    printf("Loaded Material: %s\n", material->type->name);
    printf("Weight: %.2f kg\n", material->type->weight);
    printf("Quantity: %d\n", material->type->loaded);
}

void free_loaded_material(LoadedMaterial *material)
{
    if (material == NULL)
    {
        error_message("No loaded material to remove.\n");
        return;
    }

    material->type->quantity += material->type->quantity; // depodaki miktarı arttırma
    material->type->loaded -= material->type->quantity;   // yüklü miktarı düşürme

    printf("Removed loaded material: %d units of %s.\n", material->type->quantity, material->type->name);

    // belleği temizle
    free(material);
}
