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


void PrintTree(tree* nTree) {
    if (nTree == NULL) {
        return;
    }

    printf("name:[%s], dap:[%f], height:[%f], factorBiomass:[%f]\n",
    nTree->name, nTree->dap, nTree->height, nTree->factorBiomass);
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

TREE_LIST LoadTreeListFromCsvFile(const char *csvPath) {
    unsigned char line[MAX_LINE_LENGHT] = {0};
    FILE * csvFile = fopen(csvPath, "r");
    char * pch;
    TREE_LIST head = NULL;
    node* tail = NULL;

    char name[MAX_LINE_LENGHT];
    float dap;
    float height;
    float volume;
    float factorBiomass;
    float biomass;

    if (csvFile == NULL) {
        return EMPLY_TREE_LIST;
    }
    

    // avoid head line
    fgets(line, MAX_LINE_LENGHT, csvFile);

    while(fgets(line, MAX_LINE_LENGHT, csvFile)) {
        printf("line: [%s]", line);
        pch = strtok (line,",");
        
        // name
        if (pch) {
            printf("pch: [%s]\n", pch);
            strcpy(name, pch);
            printf("name: [%s]\n", name);
        } else {
            break;
        }

        // dap
        pch = strtok(NULL, ",");
        if (pch) {
            printf("pch: [%s]\n", pch);
            dap = atof(pch);
            printf("dap: [%f]\n", dap);
        } else {
            break;
        }

        // height
        pch = strtok(NULL, ",");
        if (pch) {
            printf("pch: [%s]\n", pch);
            height = atof(pch);
            printf("height: [%f]\n", height);
        } else {
            break;
        }

        // factorBiomass
        pch = strtok(NULL, ",");
        if (pch) {
            printf("pch: [%s]\n", pch);
            factorBiomass = atof(pch);
            printf("factorBiomass: [%f]\n", factorBiomass);
        } else {
            break;
        }

        tree* nTree = CreateTree(name, strlen(name), dap,
                                        height, factorBiomass);
        node * nNode = CreateNode(nTree, NULL);
        if (head == NULL) {
            head = nNode;
            tail = head;
        } else {
            tail->next = nNode;
            tail = tail->next;
        }
    }

    fclose(csvFile);
    return head;
}

void ReleaseTreeList(TREE_LIST head) {
    node* tmp;
    while (head) {
        tmp = head;
        head = tmp->next;
        RelaseNode(tmp);
    }
}

void PrintTreeList(TREE_LIST head) {
    node* tmp;
    node* curr = head;
    while (curr) {
        tmp = curr;
        curr = tmp->next;
        PrintTree(tmp->item);
    }
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
    
    TREE_LIST listHead = LoadTreeListFromCsvFile(csvPath);
    PrintTreeList(listHead);
    ReleaseTreeList(listHead);
    // printf("Teste\n");
    // char name[] = "andiroba";
    // tree * nTree = CreateTree(name, strlen(name), 30.0, 9.0, 0.4);

// // CreateNode move the ownership of nTree to the created nNode
//     node* nNode = CreateNode(nTree, NULL);
// //    ReleaseTree(nTree);
//     RelaseNode(nNode);

    return EXIT_SUCCESS;
}