#include "List.h"

List::List()
{
    this->head = NULL;
}
void List::insertNode(int data)
{
    // Create the new Node.
    Node* newNode = new Node(data);

    // Assign to head
    if (head == NULL) {
        head = newNode;
        return;
    }

    // Traverse till end of list
    Node* temp = head;
    while (temp->next != NULL) {

        // Update temp
        temp = temp->next;
    }

    // Insert at the last.
    temp->next = newNode;
}
void List::insert_30()
{
    Node* temp = head;
    for (int i = 1; i <= 30; i++)
        this->insertNode(i);
    this->insert_ladder(search(11), search(26));
    this->insert_ladder(search(3), search(22));
    this->insert_ladder(search(5), search(8));
    this->insert_ladder(search(11), search(26));
    this->insert_ladder(search(20), search(29));
    this->insert_snake(search(27), search(1));
    this->insert_snake(search(21), search(9));
    this->insert_snake(search(17), search(4));
    this->insert_snake(search(19), search(7));
}
void List::insert_100()
{
    Node* temp = head;
    for (int i = 1; i <= 100; i++)
        this->insertNode(i);
    this->insert_ladder(search(4), search(22));
    this->insert_ladder(search(10), search(29));
    this->insert_ladder(search(14), search(77));
    this->insert_ladder(search(33), search(51));
    this->insert_ladder(search(64), search(82));
    this->insert_ladder(search(74), search(90));

    this->insert_snake(search(40), search(20));
    this->insert_snake(search(50), search(16));
    this->insert_snake(search(81), search(78));
    this->insert_snake(search(95), search(36));
    this->insert_snake(search(92), search(52));
}
Node* List::search(int k)
{
    Node* Temp = head;
    while (Temp->data != k)
    {
        Temp = Temp->next;
    }
    return  Temp;
}
void List::insert_snake(Node*snake, Node*d)
{
    snake->Up_Down = d;
    snake->state = -1;
}
void List::insert_ladder(Node*ladder, Node*d)
{
    ladder->Up_Down = d;
    ladder->state = 1;
}
void List::Display(Node* head)
{
    while (head != NULL)
    {
        printf("%d\t", head->data);
        head = head->next;
    }
}
Node* List::Get_Head()
{
    return this->head;
}
int  List::movement(Node** player)
{
    if ((*player)->next != NULL)
    {
        (*player) = (*player)->next;
        return ((*player)->data);
    }
}
int List::move2(Node** player)
{
    (*player) = (*player)->Up_Down;
    return (*player)->data;
}