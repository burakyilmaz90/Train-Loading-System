#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\utils.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\train.h"
#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\vagon.h"
int main(int argc, char const *argv[])
{
    Train *train = (Train *)malloc(sizeof(Train)); // Train yapısını ayırıyoruz
    train->first_wagon = NULL;
    train->vagon_count = 1;
    // Train *train = {0}; // Trenin tanımını yapıyoruz çünkü başta tren olmazsa neye doldurucaz.
    int choose;
    //  Train* default_train = (Train*)malloc(sizeof(Train));
    strcpy(train->train_id, "burak");
    MaterialType *lb_material = create_metarial("Large Box", 200.0f, 50);
    MaterialType *mb_material = create_metarial("Medium Box", 150.0f, 50);
    MaterialType *sb_material = create_metarial("Small Box", 100.0f, 50);
    int choice;
    char chose2[2];
    char filename[100];
    int material_choice, quantity;
    // Vagon* def_vagon = NULL;
    Vagon *def_vagon = add_vagon(NULL, 1, 1000.0f);
    train->first_wagon = def_vagon; // def_vagon->vagon_id=1;
    // İlk vagon id: 1, max ağırlık: 1000 kg
    if (def_vagon == NULL)
    {
        error_message("Failed to create default wagon.");
        return EXIT_FAILURE;
    }
    train->first_wagon = def_vagon;

    while (1)
    {
        printf("\n");
        printf("***** Train Loading Management System *****\n");
        printf("1.Load train status from file.\n");
        printf("2.Load material, starting from first suitable wagon from head of the train.\n");
        printf("3.Load material to specific wagon.\n");
        printf("4.Unload material, starting from first suitable wagon from tail of the train.\n");
        printf("5.Unload material from specific wagon.\n");
        printf("6.Display train status.\n");
        printf("7.Display material status..\n");
        printf("8.Empty train.\n");
        printf("9.Save train status to file.\n");
        printf("10.Exit.\n");
        printf("Select a process :");
        scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            printf("Enter file name to load: ");
            scanf("%s", filename);
            load_train_fromfile(train, filename);
            printf("Do you want to continue to menu? If you choose no program will be closed. (y/n)");
            scanf("%s", &chose2);
            if (!strcmp(chose2, "y"))
            {
                break;
            }
            else
            {
                printf("Program is closing...");
                exit(EXIT_SUCCESS);
            }
            break;
        case 2: // 2.Load material, starting from first suitable wagon from head of the train.
            printf("Select material: \n 1-Steel \n 2-Aluminium \n 3-Wood \n");
            scanf("%d", &material_choice);

            if (material_choice < 1 || material_choice > 3)
            {
                printf("Invalid material choice! Returning to the main menu.\n");
                break;
            }

            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity <= 0)
            {
                printf("Invalid quantity! Returning to the main menu.\n");
                break;
            }

            MaterialType *selected_material = NULL;

            // Malzeme seçimi
            switch (material_choice)
            {
            case 1:
                selected_material = lb_material; // Steel
                break;
            case 2:
                selected_material = mb_material; // Aluminium
                break;
            case 3:
                selected_material = sb_material; // Wood
                break;
            default:
                printf("Unexpected error occurred.\n");
                break;
            }

            if (selected_material != NULL)
            {
                load_material(train, selected_material, selected_material->weight, quantity);

                printf("Material '%s' loaded successfully into the train.\n", selected_material->name);
            }
            else
            {
                printf("Material selection failed. Returning to the main menu.\n");
            }
            break;

        case 3: // 3.Load material to specific wagon.\n");
                // add_matarial_specific_vagon(Vagon* vagon , MaterialType* material , int quantity)
            printf("Select material: \n 1-Steel \n 2-Aluminium \n 3-Wood \n");
            scanf("%d", &material_choice);
            printf("Enter quantity:");
            scanf("%d", &quantity);
            printf("Enter Wagon ID : ");
            scanf("%d", &choice);
            Vagon *current_wagonx = train->first_wagon;
            int found2 = 0;
            for (int i = 1; current_wagonx != NULL; i++)
            {
                if (i == choice)
                {
                    found2 = 1;
                    break;
                }
                current_wagonx = current_wagonx->next;
            }

            if (!found2)
            {
                printf("Wagon number %d not found.\n", choice);
                break;
            }

            switch (material_choice)
            {
            case 1:
                /* code */
                add_matarial_specific_vagon(current_wagonx, lb_material, quantity);
                break;
            case 2:
                /* code */
                add_matarial_specific_vagon(current_wagonx, mb_material, quantity);
                break;
            case 3:
                /* code */
                add_matarial_specific_vagon(current_wagonx, sb_material, quantity);
                break;
            default:
                break;
            }

            break;
        case 4: // 4.Unload material, starting from first suitable wagon from tail of the train.
            printf("Select material to unload: \n 1-Steel \n 2-Aluminium \n 3-Wood \n");
            scanf("%d", &material_choice);

            if (material_choice < 1 || material_choice > 3)
            {
                printf("Invalid material choice! Returning to the main menu.\n");
                break;
            }

            // Malzeme Seçimi
            switch (material_choice)
            {
            case 1:
                selected_material = lb_material; // Steel
                break;
            case 2:
                selected_material = mb_material; // Aluminium
                break;
            case 3:
                selected_material = sb_material; // Wood
                break;
            default:
                printf("Invalid material choice.\n");
                break;
            }

            // Eğer malzeme seçildiyse, malzeme boşaltma işlemi yapılacak
            if (selected_material != NULL)
            {
                printf("Enter quantity to unload: ");
                scanf("%d", &quantity);

                if (quantity <= 0)
                {
                    printf("Invalid quantity! Returning to the main menu.\n");
                    break;
                }

                unload_metarial(train, selected_material, quantity);
            }
            else
            {
                printf("Material selection failed. Returning to the main menu.\n");
            }
            break;
        case 5:

            int wagon_number, quantity;
            printf("Enter the wagon number: ");
            scanf("%d", &wagon_number);

            Vagon *current_wagon = train->first_wagon;
            int found = 0;
            for (int i = 1; current_wagon != NULL; i++)
            {
                if (i == wagon_number)
                {
                    found = 1;
                    break;
                }
                current_wagon = current_wagon->next;
            }

            if (!found)
            {
                printf("Wagon number %d not found.\n", wagon_number);
                break;
            }

            // Malzeme Seçimi
            int material_choice;
            printf("Select material to remove:\n 1-Steel\n 2-Aluminium\n 3-Wood\n");
            scanf("%d", &material_choice);

            switch (material_choice)
            {
            case 1:
                selected_material = lb_material; // Steel
                break;
            case 2:
                selected_material = mb_material; // Aluminium
                break;
            case 3:
                selected_material = sb_material; // Wood
                break;
            default:
                printf("Invalid material choice.\n");
                break;
            }

            if (selected_material != NULL)
            {
                printf("Enter quantity to remove: ");
                scanf("%d", &quantity);
                remove_material_specific_vagon(current_wagon, selected_material, quantity);
            }

            break;

            // Malzeme seçimi
            switch (material_choice)
            {
            case 1:
                remove_material_specific_vagon(def_vagon, lb_material, quantity);
                break;
            case 2:
                remove_material_specific_vagon(def_vagon, lb_material, quantity);
                break;
            case 3:
                remove_material_specific_vagon(def_vagon, lb_material, quantity);
                break;
            default:
                printf("Unexpected error occurred.\n");
                break;
            }

            break;
        case 6:
            display_train(train);
            break;
        case 7:
            LoadedMaterial sm;
            sm.type = sb_material; // sb_material MaterialType* türünde
            display_loaded_material(&sm);
            LoadedMaterial lm;
            lm.type = lb_material; // lb_material MaterialType* türünde
            display_loaded_material(&lm);
            LoadedMaterial mm;
            mm.type = mb_material; // smb_material MaterialType* türünde
            display_loaded_material(&mm);

            printf("Do you want to continue to menu? If you choose no program will be closed. (y/n)");
            scanf("%s", &chose2);
            if (!strcmp(chose2, "y"))
            {
                break;
            }
            else
            {
                printf("Program is closing...");
                exit(EXIT_SUCCESS);
            }
            break;
        case 8:
            empty_train(train);
            break;
        case 9:
            char filename[256];
            printf("Enter a file name to save the default train data: ");
            scanf("%s", filename);

            save_train_file(train, filename);
            break;
            break;
        case 10:
            printf("Program is closing...");

            exit(EXIT_SUCCESS);
            break;
        default:
            error_message("Invalid choosing try again.\n");

            break;
        }
    }
}
