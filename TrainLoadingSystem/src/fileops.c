#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\fileops.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\utils.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MaterialType *find_or_create_material(const char *name, float weight)
{
    // Yeni bir malzeme oluştur
    MaterialType *created_material = malloc(sizeof(MaterialType));
    if (created_material == NULL)
    {
        printf("Memory allocation failed for material type.\n");
        return NULL;
    }

    // Malzeme bilgilerini doldur
    strncpy(created_material->name, name, sizeof(created_material->name) - 1);
    created_material->name[sizeof(created_material->name) - 1] = '\0'; // Null terminator
    created_material->short_name[0] = name[0];                         // İlk harfi kısa isme koy
    created_material->short_name[1] = '\0';                            // Null terminator
    created_material->weight = weight;
    created_material->quantity = 0; // Toplam elde olan başlangıçta 0
    created_material->loaded = 0;   // Trene yüklenen başlangıçta 0

    return created_material;
}

void save_train_file(Train *train, char *filename)
{
    if (train == NULL)
    {
        printf("Train does not exist!\n");
        return;
    }

    FILE *file = fopen(filename, "w"); // Dosyayı yazma modunda aç
    if (file == NULL)
    {
        printf("Failed to open file for saving train status.\n");
        return;
    }

    fprintf(file, "Train ID: %s\n", train->train_id);
    fprintf(file, "Number of wagons: %d\n", train->vagon_count);

    Vagon *current_wagon = train->first_wagon;
    while (current_wagon != NULL)
    {
        fprintf(file, "Wagon ID: %d\n", current_wagon->vagon_id);
        fprintf(file, "Max weight: %.2f kg\n", current_wagon->max_weight);
        fprintf(file, "Current weight: %.2f kg\n", current_wagon->current_weight);

        LoadedMaterial *current_material = current_wagon->loaded_material;
        if (current_material == NULL)
        {
            fprintf(file, "  No materials in this wagon.\n");
        }
        else
        {
            while (current_material != NULL)
            {
                // Mevcut malzeme miktarına göre yazdırma
                for (int i = 0; i < current_material->quantity; i++)
                {
                    fprintf(file, "  Material: %s, Quantity: 1, Weight: %.2f kg\n",
                            current_material->type->name,    // Malzeme adı
                            current_material->type->weight); // Malzeme ağırlığı
                }
                current_material = current_material->next; // Sonraki malzemeye geç
            }
        }

        fprintf(file, "Remaining Capacity: %.2f kg\n",
                current_wagon->max_weight - current_wagon->current_weight);
        fprintf(file, "\n");

        current_wagon = current_wagon->next; // Sonraki vagona geç
    }

    fclose(file); // Dosyayı kapat
    printf("Train status has been saved to file successfully.\n");
}

void load_train_fromfile(Train *train, char *filename)
{

    if (train == NULL || filename == NULL)
    {
        printf("Train structure or filename is NULL!\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        perror("Error");
        return;
    }

    char buffer[256];
    Vagon *current_wagon = NULL;

    while (fgets(buffer, sizeof(buffer), file))
    {
        // Train ID
        if (strncmp(buffer, "Train ID:", 9) == 0)
        {
            sscanf(buffer, "Train ID: %s", train->train_id);
        }
        // Number of wagons
        else if (strncmp(buffer, "Number of wagons:", 18) == 0)
        {
            sscanf(buffer, "Number of wagons: %d", &train->vagon_count);
        }
        // Wagon details
        else if (strncmp(buffer, "Wagon ID:", 9) == 0)
        {
            int wagon_id;
            float max_weight, current_weight;

            sscanf(buffer, "Wagon ID: %d", &wagon_id);
            fgets(buffer, sizeof(buffer), file); // Max weight
            sscanf(buffer, "Max weight: %f kg", &max_weight);
            fgets(buffer, sizeof(buffer), file); // Current weight
            sscanf(buffer, "Current weight: %f kg", &current_weight);

            // Create or update wagon
            Vagon *new_wagon = add_vagon(current_wagon, wagon_id, max_weight);
            if (new_wagon == NULL)
            {
                printf("Failed to create wagon.\n");
                fclose(file);
                return;
            }
            new_wagon->current_weight = current_weight;

            if (current_wagon == NULL)
            {
                train->first_wagon = new_wagon;
            }
            else
            {
                current_wagon->next = new_wagon;
            }
            current_wagon = new_wagon;
        }
        // Material details
        else if (strncmp(buffer, "  Material:", 11) == 0)
        {
            char material_name[50];
            int quantity;
            float weight;

            if (sscanf(buffer, "  Material: %[^,], Quantity: %d, Weight: %f kg",
                       material_name, &quantity, &weight) == 3)
            {

                // Create or find material type
                MaterialType *material_type = find_or_create_material(material_name, weight);
                if (material_type == NULL)
                {
                    printf("Failed to create material type: %s\n", material_name);
                    fclose(file);
                    return;
                }

                // Add material to the current wagon
                for (int i = 0; i < quantity; i++)
                {
                    load_material(train, material_type, weight, 1);
                }
            }
            else
            {
                printf("Error reading material details: %s", buffer);
            }
        }
    }

    fclose(file);
    printf("Train loaded successfully from file: %s\n", filename);
}
