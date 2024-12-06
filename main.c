#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGHT 80

typedef struct {
    char *name;
    float dap;
    float height;
    float volume;
    float factorBiomass;
    float biomass;
} tree;

typedef struct node{
    tree* item;
    struct node* next;
} node;

#define TREE_LIST node*
#define EMPLY_TREE_LIST NULL;

tree* CreateTree(const char* name, unsigned int nameLen, float dap,
                                float height, float factorBiomass) {

    tree* nTree = (tree*) malloc(sizeof(tree));
    if (nTree == NULL) {
        return NULL;
    }

    nTree->name = (char*) malloc(nameLen + 1);
    memcpy(nTree->name, name, nameLen);
    nTree->name[nameLen] = '\0';
    nTree->dap = dap;
    nTree->height = height;
    nTree->factorBiomass = factorBiomass;
    return nTree;
}

void ReleaseTree(tree * treeItem) {
    if (treeItem == NULL) {
        return;
    }

    if (treeItem->name) {
        free(treeItem->name);
    }

    free(treeItem);
    treeItem = NULL;
}

node * CreateNode(tree* item, node* next) {
    node * nNode = (node *) malloc(sizeof(node));
    if (nNode == NULL) {
        return NULL;
    }
    
    nNode->item = item;
    nNode->next = next;

    return nNode;
}

void RelaseNode(node * nNode) {
    if (nNode == NULL) {
        return;
    }

    if (nNode->item) {
        ReleaseTree(nNode->item);
    }
    
    nNode->next = NULL;
    free(nNode);
    nNode = NULL;
}

TREE_LIST LoadListFromCsvFile(const char *csvPath) {
    unsigned char line[MAX_LINE_LENGHT] = {0};
    FILE * csvFile = fopen(csvPath, "r");
    while(fgets(line, MAX_LINE_LENGHT, csvFile)) {
        printf("%s\n", line);
    } 

    fclose(csvFile);
    return EMPLY_TREE_LIST;
}

void usage() {
    printf("usage:\n");
    printf("CTreeProcessor <tree.csv>\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        return EXIT_FAILURE;
    }

    char *csvPath = argv[1];
    
    TREE_LIST listHead = LoadListFromCsvFile(csvPath);

    // printf("Teste\n");
    // char name[] = "andiroba";
    // tree * nTree = CreateTree(name, strlen(name), 30.0, 9.0, 0.4);

// // CreateNode move the ownership of nTree to the created nNode
//     node* nNode = CreateNode(nTree, NULL);
// //    ReleaseTree(nTree);
//     RelaseNode(nNode);

    return EXIT_SUCCESS;
}