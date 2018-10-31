#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node{
    char *data; // Node storing the character
    char *code; // Node storing it's morse code (Could have used backtracking, but it adds unnecessary time-complexity, so :P)
    struct Node *left, *right;
}node;

typedef struct Table{ // To effectively store morse code characters with thier code
    char *code;
    char *alphabet;
}morse_table;

node *create(char *data, char *code){
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data; // Initializing character
    temp->code = code; // Initializing it's morse code
    temp->left = temp->right = NULL;
    return temp;
}

node *make_a_tree(morse_table arr[], node *root, int i, int n){
    node *temp = NULL;
    if(i < n){
        temp = create(arr[i].alphabet, arr[i].code);
        root = temp;
        root->left = make_a_tree(arr, root->left, 2*i + 1, n); // Inserting left child
        root->right = make_a_tree(arr, root->right, 2*i + 2, n); // Inserting right child
    }
    return root;
}

void to_morse(node *x, char *key){ // DFS search to find the character
    if(!x){
        return;
    }
    if(*(x->data) == *key){
        printf("%s", x->code); // Printing it's morse code, once found
        return;
    }
    to_morse(x->left, key);
    to_morse(x->right, key);
}

void morse_to(node *x){
    int i;
    node *root = x;
    char code[100];
    printf("Enter Morse code (Max length 100)\n");
    scanf(" %[^\n]", code);
    int len = strlen(code);

    for(i=0; i<len; i++){
        if(code[i] == '.'){
            x = x->left; // We go left
            if(code[i+1] == ' ' || i+1 == len){ // If next character is space so we have to end up traversing and print the found character and go back to root
                printf("%s", x->data);
                x = root;
                i++;
            }
            else if(code[i+1] == '/'){ // '/' implies space between words
                printf("%s ", x->data);
                x = root;
                i++;
            }
        }
        else if(code[i] == '-'){
            x = x->right; // We go right
            if(code[i+1] == ' ' || i+1 == len){ // If next character is space so we have to end up traversing and print the found character and go back to root
                printf("%s", x->data);
                x = root;
                i++;
            }
            else if(code[i+1] == '/'){ // '/' implies space between words
                printf("%s ", x->data);
                x = root;
                i++;
            }
        }
    }
}

void upper_case(char arr[]){
    int i, n = strlen(arr);
    for(i=0; i<n; i++){
        arr[i] = toupper(arr[i]);
    }
}

int main(void){
    int i, choice = -1, store;
    char text[50]; // Input texzt for encoding to morse code

	morse_table dict[] = { // An array with all the nodes arranged in level order
        {"*", "*"},

        {".", "E"}, {"-", "T"},

        {"..", "I"}, {".-", "A"}, {"-.", "N"}, {"--", "M"},

        {"...", "S"}, {"..-", "U"}, {".-.", "R"}, {".--", "W"},
        {"-..", "D"}, {"-.-", "K"}, {"--.", "G"}, {"---", "O"},

        {"....", "H"}, {"...-", "V"}, {"..-.", "F"}, {"_","_"},
        {".-..", "L"}, {"_", "_"}, {".--.", "P"}, {".---", "J"},
        {"-...", "B"}, {"-..-", "X"}, {"-.-.", "C"}, {"-.--", "Y"},
        {"--..", "Z"}, {"--.-", "Q"}, {"_", "_"}, {"_", "_"},

        {".....", "5"}, {"....-", "4"}, {"_", "_"}, {"...--", "3"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"..---", "2"}, {"_", "_"},
        {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"},
        {".----", "1"}, {"-....", "6"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"_", "_"}, {"--...", "7"}, {"_", "_"}, {"_", "_"}, {"_", "_"},{"---..", "8"}, {"_", "_"}, {"----.","9"}, {"-----", "0"}
    };

    int n = sizeof(dict) / sizeof(dict[0]);
    node *root = make_a_tree(dict, NULL, 0, n); // Constructing the tree from the above level-order

    while(choice){
        printf("\nMenu:\n\n");
        printf("1. Morse Code to Text\n");
        printf("2. Text to Morse Code\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch(choice){
            case 1: morse_to(root);
                    break;
            case 2: printf("Enter Text (Max length 50)\n");
                    scanf(" %[^\n]", text);
                    upper_case(text);
                    printf("Morse code: ");
                    for(i=0; i<strlen(text); i++){
                        if(text[i] == ' ')
                            printf("/");
                        else{
                            to_morse(root, text + i);
                            if(text[i+1] != ' ')
                                printf(" ");
                        }
                    }
                    printf("\n");
                    break;
            case 0: break;
            default : printf("Wrong choice.\n");
        }
    }

    return 0;
}
