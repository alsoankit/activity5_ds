#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item
{
  int item_id;
  char item_name[30];
  float price;
  int quantity;
  struct item *next;
} item;

typedef struct shopping_card
{
  int card_id;
  char customer_name[50];
  int points;
  char dob[15];
  char last_transaction_date[15];
  char address[100];
  struct shopping_card *next;
} shopping_card;

typedef struct header
{
  int count;
  struct item *item_head;
  struct shopping_card *card_head;
} header;

header *initialize_header()
{
  header *new_header = (header *)malloc(sizeof(header));
  new_header->count = 0;
  new_header->item_head = NULL;
  new_header->card_head = NULL;
  return new_header;
}

shopping_card *create_customer(int card_id, char customer_name[], char dob[], char last_transaction_date[], char address[])
{
  shopping_card *new_customer = (shopping_card *)malloc(sizeof(shopping_card));
  new_customer->card_id = card_id;
  strcpy(new_customer->customer_name, customer_name);
  new_customer->points = 0;
  strcpy(new_customer->dob, dob);
  strcpy(new_customer->last_transaction_date, last_transaction_date);
  strcpy(new_customer->address, address);
  new_customer->next = NULL;
  return new_customer;
}

item *create_item(int item_id, char item_name[], float price, int quantity)
{
  item *new_item = (item *)malloc(sizeof(item));
  new_item->item_id = item_id;
  strcpy(new_item->item_name, item_name);
  new_item->price = price;
  new_item->quantity = quantity;
  new_item->next = NULL;
  return new_item;
}

void add_customer(header *card_header, int card_id, char customer_name[], char dob[], char last_transaction_date[], char address[])
{
  shopping_card *temp = card_header->card_head;
  while (temp != NULL)
  {
    if (temp->card_id == card_id)
    {
      printf("Customer with Card ID %d already exists.\n", card_id);
      return;
    }
    temp = temp->next;
  }
  shopping_card *new_customer = create_customer(card_id, customer_name, dob, last_transaction_date, address);
  new_customer->next = card_header->card_head;
  card_header->card_head = new_customer;
  card_header->count++;
  printf("Customer added successfully!\n");
}

void add_item(header *item_header, int item_id, char item_name[], float price, int quantity)
{
  item *temp = item_header->item_head;
  while (temp != NULL)
  {
    if (temp->item_id == item_id)
    {
      printf("Item with Item ID %d already exists.\n", item_id);
      return;
    }
    temp = temp->next;
  }
  item *new_item = create_item(item_id, item_name, price, quantity);
  new_item->next = item_header->item_head;
  item_header->item_head = new_item;
  item_header->count++;
  printf("Item added successfully!\n");
}

void update_address(header *card_header, int card_id, char new_address[])
{
  shopping_card *temp = card_header->card_head;
  while (temp != NULL)
  {
    if (temp->card_id == card_id)
    {
      strcpy(temp->address, new_address);
      printf("Address updated successfully!\n");
      return;
    }
    temp = temp->next;
  }
  printf("Customer with Card ID %d not found.\n", card_id);
}

void assign_points(header *card_header, header *item_header, int card_id, int item_id, int amount_spent)
{
  shopping_card *temp_card = card_header->card_head;
  while (temp_card != NULL)
  {
    if (temp_card->card_id == card_id)
    {
      item *temp_item = item_header->item_head;
      while (temp_item != NULL)
      {
        if (temp_item->item_id == item_id)
        {
          int points = 0;
          if (strcmp(temp_item->item_name, "Grocery") == 0)
          {
            points = (amount_spent / 100) * 1;
          }
          else if (strcmp(temp_item->item_name, "Garments") == 0)
          {
            points = (amount_spent / 100) * 5;
          }
          else if (strcmp(temp_item->item_name, "Electronics") == 0)
          {
            points = (amount_spent / 100) * 10;
          }
          temp_card->points += points;
          printf("Points assigned based on the purchase.\n");
          return;
        }
        temp_item = temp_item->next;
      }
      printf("Item with ID %d not found.\n", item_id);
      return;
    }
    temp_card = temp_card->next;
  }
  printf("Customer with Card ID %d not found.\n", card_id);
}

float calculate_discount(shopping_card *customer)
{
  float discount = 0.0;
  int age = 2024 - atoi(customer->dob + 6); // Assuming DOB format is dd/mm/yyyy

  if (age >= 60)
  {
    discount = 0.1; // 10% discount for senior citizens
  }
  else if (age <= 12)
  {
    discount = 0.05; // 5% discount for children
  }
  else if (strcmp(customer->last_transaction_date, "14/11/2024") == 0)
  {
    discount = 0.15; // 15% discount for shopping on birthday
  }

  return discount;
}

void display_customers(header *card_header)
{
  shopping_card *temp = card_header->card_head;
  if (temp == NULL)
  {
    printf("No customers to display.\n");
    return;
  }
  while (temp != NULL)
  {
    printf("Card ID: %d, Name: %s, Points: %d, DOB: %s, Last Transaction Date: %s, Address: %s\n",
           temp->card_id, temp->customer_name, temp->points, temp->dob, temp->last_transaction_date, temp->address);
    temp = temp->next;
  }
}

void display_items(header *item_header)
{
  item *temp = item_header->item_head;
  if (temp == NULL)
  {
    printf("No items to display.\n");
    return;
  }
  while (temp != NULL)
  {
    printf("Item ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
           temp->item_id, temp->item_name, temp->price, temp->quantity);
    temp = temp->next;
  }
}

int main()
{
  header *item_header = initialize_header();
  header *card_header = initialize_header();
  int choice, card_id, item_id, amount_spent, quantity;
  char customer_name[50], dob[15], last_transaction_date[15], address[100], item_name[30], new_address[100];
  float price;

  do
  {
    printf("\nMenu:\n");
    printf("1. Add Customer\n2. Add Item\n3. Update Address\n4. Assign Points\n5. Display Customers\n6. Display Items\n7. Calculate Discount\n8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      printf("Enter Card ID, Name, DOB (dd/mm/yyyy), Last Transaction Date, Address:\n");
      scanf("%d %s %s %s %s", &card_id, customer_name, dob, last_transaction_date, address);
      add_customer(card_header, card_id, customer_name, dob, last_transaction_date, address);
      break;

    case 2:
      printf("Enter Item ID, Name, Price, Quantity:\n");
      scanf("%d %s %f %d", &item_id, item_name, &price, &quantity);
      add_item(item_header, item_id, item_name, price, quantity);
      break;

    case 3:
      printf("Enter Card ID and New Address:\n");
      scanf("%d %s", &card_id, new_address);
      update_address(card_header, card_id, new_address);
      break;

    case 4:
      printf("Enter Card ID, Item ID, and Amount Spent:\n");
      scanf("%d %d %d", &card_id, &item_id, &amount_spent);
      assign_points(card_header, item_header, card_id, item_id, amount_spent);
      break;

    case 5:
      display_customers(card_header);
      break;

    case 6:
      display_items(item_header);
      break;

    case 7:
      printf("Enter Card ID to calculate discount:\n");
      scanf("%d", &card_id);
      shopping_card *temp = card_header->card_head;
      while (temp != NULL)
      {
        if (temp->card_id == card_id)
        {
          float discount = calculate_discount(temp);
          printf("Discount for Card ID %d: %.2f%%\n", card_id, discount * 100);
          break;
        }
        temp = temp->next;
      }
      if (temp == NULL)
      {
        printf("Customer with Card ID %d not found.\n", card_id);
      }
      break;

    case 8:
      printf("Exiting.\n");
      break;

    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 8);

  return 0;
}
