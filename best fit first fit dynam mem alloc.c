// dynamic memory allocation best fit first fit
#include <stdio.h>
#include <stdlib.h>

// Define the structure for memory blocks
struct Block
{
    int size;
    int allocatedSize;
    struct Block *next;
};

// Function to create a memory block
struct Block *createBlock(int size)
{
    struct Block *block = (struct Block *)malloc(sizeof(struct Block));
    block->size = size;
    block->allocatedSize = 0;
    block->next = NULL;
    return block;
}

// Function to display memory blocks
void displayBlocks(struct Block *head)
{
    struct Block *current = head;
    while (current != NULL)
    {
        printf("Block Size: %d, Allocated: %d (%d units)\n", current->size, current->allocatedSize != 0, current->allocatedSize);
        current = current->next;
    }
}

// Function for First Fit allocation
void firstFit(struct Block *head, int size)
{
    struct Block *current = head;
    while (current != NULL)
    {
        if (current->allocatedSize == 0 && current->size >= size)
        {
            current->allocatedSize = size;
            printf("Allocated %d using First Fit\n", size);
            return;
        }
        current = current->next;
    }
    printf("No suitable block found for %d using First Fit\n", size);
}

// Function for Best Fit allocation
void bestFit(struct Block *head, int size)
{
    struct Block *bestBlock = NULL;
    struct Block *current = head;
    while (current != NULL)
    {
        if (current->allocatedSize == 0 && current->size >= size)
        {
            if (bestBlock == NULL || current->size < bestBlock->size)
            {
                bestBlock = current;
            }
        }
        current = current->next;
    }
    if (bestBlock != NULL)
    {
        bestBlock->allocatedSize = size;
        printf("Allocated %d using Best Fit\n", size);
    }
    else
    {
        printf("No suitable block found for %d using Best Fit\n", size);
    }
}

// Function for Worst Fit allocation
void worstFit(struct Block *head, int size)
{
    struct Block *worstBlock = NULL;
    struct Block *current = head;
    while (current != NULL)
    {
        if (current->allocatedSize == 0 && current->size >= size)
        {
            if (worstBlock == NULL || current->size > worstBlock->size)
            {
                worstBlock = current;
            }
        }
        current = current->next;
    }
    if (worstBlock != NULL)
    {
        worstBlock->allocatedSize = size;
        printf("Allocated %d using Worst Fit\n", size);
    }
    else
    {
        printf("No suitable block found for %d using Worst Fit\n", size);
    }
}

int main()
{
    int numBlocks, blockSize, requestSize, choice;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    struct Block *head = NULL;
    struct Block *tail = NULL;

    for (int i = 0; i < numBlocks; i++)
    {
        printf("Enter size for block %d: ", i + 1);
        scanf("%d", &blockSize);
        struct Block *newBlock = createBlock(blockSize);
        if (head == NULL)
        {
            head = newBlock;
        }
        else
        {
            tail->next = newBlock;
        }
        tail = newBlock;
    }

    printf("\nInitial Memory Blocks:\n");
    displayBlocks(head);

    while (1)
    {
        printf("\nEnter the size of allocation request (0 to exit): ");
        scanf("%d", &requestSize);
        if (requestSize == 0)
            break;

        printf("Choose allocation strategy (1 for First Fit, 2 for Best Fit, 3 for Worst Fit): ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            firstFit(head, requestSize);
        }
        else if (choice == 2)
        {
            bestFit(head, requestSize);
        }
        else if (choice == 3)
        {
            worstFit(head, requestSize);
        }
        else
        {
            printf("Invalid choice!\n");
        }

        printf("\nMemory Blocks after Allocation:\n");
        displayBlocks(head);
    }

    // Free memory blocks
    struct Block *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
