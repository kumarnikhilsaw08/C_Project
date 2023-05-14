
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

struct product {
    char name[50];
    int quantity;
    float price;
    int sales;
};

struct product inventory[MAX_PRODUCTS];
int num_products = 0,i,j;

void load_inventory() {
    FILE *fp;
    fp = fopen("inventory.txt", "w");
    if (fp == NULL) {
        printf("Error: cannot open inventory file\n");
        return;
    }
    num_products = 0;
    while (fscanf(fp, "%s %d %f %d", inventory[num_products].name, &inventory[num_products].quantity, &inventory[num_products].price, &inventory[num_products].sales) == 4) {
        num_products++;
    }
    fclose(fp);
    printf("Inventory loaded: %d products\n", num_products);
}

void save_inventory() {
    FILE *fp; 
    fp = fopen("inventory.txt", "w");
    if (fp == NULL) {
        printf("Error: cannot open inventory file\n");
        return;
    }
    // for (int i = 0; i < num_products; i++) 
     for(i=0;i<num_products;i++)
	 {
        fprintf(fp, "%s %d %.2f %d\n", inventory[i].name, inventory[i].quantity, inventory[i].price, inventory[i].sales);
    }
    fclose(fp);
    printf("Inventory saved: %d products\n", num_products);
}

void add_product() {
    if (num_products >= MAX_PRODUCTS) {
        printf("Error: maximum number of products reached\n");
        return;
    }
    struct product p;
    printf("Enter product name: ");
    scanf("%s", p.name);
    printf("Enter quantity: ");
    scanf("%d", &p.quantity);
    printf("Enter price: ");
    scanf("%f", &p.price);
    p.sales = 0;
    inventory[num_products++] = p;
    printf("Product added: %s\n", p.name);
}

void remove_product() {
    char name[50];
    printf("Enter product name to remove: ");
    scanf("%s", name);
    int found = 0;
    for (i = 0; i < num_products; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            printf("Product removed: %s\n", inventory[i].name);
            found = 1;
            for (j = i; j < num_products - 1; j++) {
                inventory[j] = inventory[j+1];
            }
            num_products--;
            break;
        }
    }
    if (!found) {
        printf("Error: product not found\n");
    }
}

void update_quantity() {
    char name[50];
    printf("Enter product name to update quantity: ");
    scanf("%s", name);
    int found = 0;
    for (i = 0; i < num_products; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Quantity updated: %s\n", inventory[i].name);
           
 found = 1;
        break;
    }
}
if (!found) {
    printf("Error: product not found\n");
}
}

void update_price() {
char name[50];
printf("Enter product name to update price: ");
scanf("%s", name);
int found = 0;
for (i = 0; i < num_products; i++) {
if (strcmp(inventory[i].name, name) == 0) {
printf("Enter new price: ");
scanf("%f", &inventory[i].price);
printf("Price updated: %s\n", inventory[i].name);
found = 1;
break;
}
}
if (!found) {
printf("Error: product not found\n");
}
}

void record_sale() {
char name[50];
printf("Enter product name to record sale: ");
scanf("%s", name);
int found = 0;
for (i = 0; i < num_products; i++) {
if (strcmp(inventory[i].name, name) == 0) {
printf("Enter quantity sold: ");
int quantity;
scanf("%d", &quantity);
if (quantity > inventory[i].quantity) {
printf("Error: not enough stock\n");
return;
}
inventory[i].quantity -= quantity;
inventory[i].sales += quantity;
printf("Sale recorded: %s\n", inventory[i].name);
found = 1;
break;
}
}
if (!found) {
printf("Error: product not found\n");
}
}

void generate_report() {
float total_sales = 0;
float total_revenue = 0;
printf("Product\tQuantity\tPrice\tSales\tRevenue\n");
for (i = 0; i < num_products; i++) {
float revenue = inventory[i].sales * inventory[i].price;
printf("%s\t%d\t\t%.2f\t%d\t%.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price, inventory[i].sales, revenue);
total_sales += inventory[i].sales;
total_revenue += revenue;
}
printf("Total\t\t\t\t%.2f\t%.2f\n", total_sales, total_revenue);
}

int main() {
load_inventory();
int choice;
do {
printf("\nInventory management system\n");
printf("1. Add product\n");
printf("2. Remove product\n");
printf("3. Update quantity\n");
printf("4. Update price\n");
printf("5. Record sale\n");
printf("6. Generate report\n");
printf("0. Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);
switch (choice) {
case 1: add_product(); break;
case 2: remove_product(); break;
case 3: update_quantity(); break;
case 4: update_price(); break;
case 5: record_sale(); break;
case 6: generate_report(); break;
case 0: break;
default: printf("Error: invalid choice\n"); break;
}
} while (choice != 0);
save_inventory();
return 0;
}
