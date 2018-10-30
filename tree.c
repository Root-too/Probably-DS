#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char data;
    struct Node *left, *right;
}node;

char *encoded = NULL;

node *create(char data){
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

node *make_a_tree(char arr[], node *root, int i, int n){
    node *temp = NULL;
    if(i < n){
        temp = create(arr[i]);
        root = temp;
        // Inserting left child
        root->left = make_a_tree(arr, root->left, 2*i + 1, n);

        // Inserting right child
        root->right = make_a_tree(arr, root->right, 2*i + 2, n);
    }
    return root;
}

int encoder(char x, char *encoded){
    static int i;
    encoded[i] = x;
    i++;
    return i;
}

int to_morse(node *x, char key, char *encoded){
    int found;
    if(!x){
        return 0;
    }
    if(x->data == key){
        return 1;
    }
    found = to_morse(x->left, key, encoded);
    if(found){
        encoder('.', encoded);
        return 1;
    }
    found = to_morse(x->right, key, encoded);
    if(found){
        encoder('-', encoded);
        return 1;
    }
    return 0;
}

void morse_to(node *x){
    int i, j = 0;
    node *root = x;
    char code[1000], ans[1000];
    printf("Enter Morse code (Max length 1000)\n");
    scanf(" %[^\n]", code);
    code[strlen(code)] = ' ';

    for(i=0; i<strlen(code); i++){
        if(code[i] == '.'){
            // We go left
            x = x->left;
        }
        else if(code[i] == '-'){
            // We go right
            x = x->right;
        }
        else if(code[i] == ' '){
            ans[j] = x->data;
            x = root;
            j++;
        }
        else{
            ans[j] = x->data;
            j++;
            ans[j] = ' ';
            x = root;
            j++;
        }
    }
    ans[j] = '\0';
    printf("Text: %s\n", ans);
}

// char *clean_up(char **encoded){
//     if(*encoded){
//         free(*encoded);
//         return (char *)malloc(100*sizeof(char));
//     }
//     return (char *)malloc(100*sizeof(char));
// }

int main(void){
    int i, choice = -1, store;
    char *text = (char *)malloc(100*sizeof(char));

    char morse_code_data[] = {'*', 'e', 't', 'i', 'a', 'n', 'm', 's', 'u', 'r', 'w', 'd', 'k', 'g', 'o', 'h', 'v', 'f', '_', 'l', '_', 'p', 'j', 'b', 'x', 'c', 'y', 'z', 'q', '_', '_', '5', '4', '_', '3', '_', '_', '_', '2', '_', '_', '+', '_', '_', '_', '_', '1', '6', '=', '/', '_', '_', '_', '_', '_', '7', '_', '_', '_', '8', '_', '9', '0'};
    int n = sizeof(morse_code_data) / sizeof(morse_code_data[0]);
    node *root = make_a_tree(morse_code_data, NULL, 0, n);
    // char *encoded = NULL;

    while(choice){
        printf("\nMenu:\n\n");
        printf("1. Morse Code to Text\n");
        printf("2. Text to Morse Code\n");
        printf("0. Exit\n");
        scanf("%d", &choice);
        // encoded = clean_up(&encoded);
        // encoded = (char *)malloc(1000 * sizeof(char));
        switch(choice){
            case 1: morse_to(root);
                    break;
            case 2: printf("Enter Text (Max length 20)\n");
                    scanf(" %[^\n]", text);
                    printf("Morse code: ");
                    for(i=0; i<strlen(text); i++){
                        char encoded[1000];
                        if(text[i] == ' ')
                            printf("/");

                        to_morse(root, text[i], encoded);
                        store = encoder(' ', encoded);
                        encoded[store] = '\0';
                        printf("%d\n", store);
                        // for(i=strlen(encoded); i>=0; i--)
                        //     printf("%c", encoded[i]);

                    }
                    //
                    // // printf("\n%ld\n", strlen(encoded));
                    // for(i=strlen(encoded); i>=0; i--)
                    //     printf("%c", encoded[i]);
                    // printf("\n");
                    break;
            case 0: break;
            default : printf("Wrong choice.\n");
        }
    }

    return 0;
}
