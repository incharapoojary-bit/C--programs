#include <stdio.h>
#include <stdlib.h>

struct hotel
{
    int room;
    char name[50];
    int days;
    float rent;
};

void add()
{
    struct hotel h;
    FILE *fp;

    fp = fopen("hotel.dat", "ab");

    printf("Enter Room Number: ");
    scanf("%d", &h.room);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", h.name);

    printf("Enter Number of Days: ");
    scanf("%d", &h.days);

    printf("Enter Rent per Day: ");
    scanf("%f", &h.rent);

    fwrite(&h, sizeof(h), 1, fp);
    fclose(fp);

    printf("Record Added Successfully!\n");
}

void display()
{
    struct hotel h;
    FILE *fp = fopen("hotel.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    while (fread(&h, sizeof(h), 1, fp))
    {
        printf("\nRoom Number: %d", h.room);
        printf("\nCustomer Name: %s", h.name);
        printf("\nDays: %d", h.days);
        printf("\nTotal Bill: %.2f\n", h.days * h.rent);
    }

    fclose(fp);
}

void update()
{
    struct hotel h;
    int room, found = 0;
    FILE *fp = fopen("hotel.dat", "rb+");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Room Number to Update: ");
    scanf("%d", &room);

    while (fread(&h, sizeof(h), 1, fp))
    {
        if (h.room == room)
        {
            printf("Enter New Customer Name: ");
            scanf(" %[^\n]", h.name);

            printf("Enter New Number of Days: ");
            scanf("%d", &h.days);

            printf("Enter New Rent per Day: ");
            scanf("%f", &h.rent);

            fseek(fp, -(long)sizeof(h), SEEK_CUR);
            fwrite(&h, sizeof(h), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("Record Updated Successfully!\n");
    else
        printf("Room Not Found!\n");
}

void delete()
{
    struct hotel h;
    int room, found = 0;

    FILE *fp = fopen("hotel.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("File Error!\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("Enter Room Number to Delete: ");
    scanf("%d", &room);

    while (fread(&h, sizeof(h), 1, fp))
    {
        if (h.room == room)
            found = 1;
        else
            fwrite(&h, sizeof(h), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("hotel.dat");
        rename("temp.dat", "hotel.dat");
        printf("Record Deleted Successfully!\n");
    }
    else
    {
        remove("temp.dat");
        printf("Room Not Found!\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n===== HOTEL MANAGEMENT SYSTEM =====");
        printf("\n1. Add Customer");
        printf("\n2. Display Customers");
        printf("\n3. Update Customer");
        printf("\n4. Delete Customer");
        printf("\n5. Exit");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add();
                break;

            case 2:
                display();
                break;

            case 3:
                update();
                break;

            case 4:
                delete();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid Choice!");
        }
    }

    return 0;
}
