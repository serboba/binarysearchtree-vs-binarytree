#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node node;
typedef struct bstree bstree;
typedef struct queue queue;
struct node{

     node* left;
     node* right;
     node * next;

    int number;
    char *word;
    int frequency;
};

struct bstree
{
    node* root;
    int count;
};

struct queue{
node *first;
node *last;
};

queue* init(node * nod){
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));

    q->first = nod;
    q->last = nod;

    return q;
}

int empty(queue *q){
    if(q->first==NULL){
      return 1;
    }
    return 0;
}

queue * push(node *nod, queue *q)
{
    nod->next=NULL;
    if(empty(q)){
        q->first=nod;
        q->last=nod;
    }
    else{
        q->last->next = nod;
        q->last=nod;
    }
    return q;
}
node* top(queue *q){
    if (empty(q) != 1){
    return q->first;
  }else{
    return NULL;
  }
}
void pop(queue *q){
    q->first= q->first->next;
}


void insert_bt(bstree *bt){
  int number, frequency;
  char *word;
  char line[512];
  FILE *fp = fopen("input.txt" , "r");
  if (fp == NULL){
      printf("CANT OPEN FILE ABORT\n" );
  }

  while(fgets(line, sizeof(line),fp)!= NULL){

    char *ptr = strtok(line,",");
    number = atoi(ptr);
    if(number == 0){
      number++;
    }
    ptr = strtok(NULL, ",");
    word = ptr;
    if (strcmp(word," ") == 0){
      printf("ERROR, NOT VALID WORD, CHECK TXT FILE?\n" );
      return;
    }
    ptr = strtok(NULL,",");
    frequency = atoi(ptr);

    if(frequency<0){
      printf("ERROR, NOT VALID FREQUENCY\n" );
      return;
    }


    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->word = (char*)calloc(strlen(word) + 1, sizeof(char));
    sprintf(new_node->word,"%s",word);
    new_node->number = number;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;

    //printf("%d %s %d\n", new_node->number, new_node->word,new_node->frequency );
    if (new_node->number == 1){
        bt->root = new_node;
        bt->count= 1;
        continue;
    }

    queue* q = init(bt->root);

    while(empty(q) != 1){

      node* temp = top(q);
      pop(q);

      if(temp -> left != NULL){

        q = push(temp->left,q);

      }else{
        temp->left = new_node;

        break;

      }

      if(temp -> right != NULL){
        q = push(temp->right,q);
      }else{
        temp->right = new_node;
        break;
      }

      }
}
    fclose(fp);
    return;
}


void insert(bstree * bst) {
    int number, frequency;
    char *word;
    char line[512];
    FILE *fp = fopen("input.txt" , "r");
    if (fp == NULL){
        printf("CANT OPEN FILE ABORT\n" );
    }

    while(fgets(line, sizeof(line),fp)!= NULL){

      char *ptr = strtok(line,",");
      number = atoi(ptr);
      if(number == 0){
        number++;
      }
      if (number <0){
        printf("INVALID NUMBER OF WORD\n" );
        return;
      }
      ptr = strtok(NULL, ",");
      word = ptr;
      if (strcmp(word," ") == 0){
        printf("ERROR, NOT VALID WORD, CHECK TXT FILE?\n" );
        return;

      }
      ptr = strtok(NULL,",");

      frequency = atoi(ptr);

      if(frequency<0){
        printf("ERROR, NOT VALID FREQUENCY\n" );
        return;
      }

      struct node* new_node = (struct node*)malloc(sizeof(struct node));

      int found = 0;
      node* temp = NULL;
        if (new_node == NULL) return;

      new_node->word = (char*)calloc(strlen(word) + 1, sizeof(char));
      sprintf(new_node->word,"%s",word);


      new_node->number = number;
      new_node->frequency = frequency;

      printf("%d %s %d\n", new_node->number, new_node->word,new_node->frequency );

      if (new_node->number == 1)
      {
          bst->root = new_node;
          bst->count= 1;
          continue;
      }

      temp = bst->root;

      while (found == 0) {
        if (strcmp(temp->word,word) >0){
          if (temp->left != NULL){
            temp = temp->left;
          }
          else{
            found = 1;
            temp->left = new_node;
          }
        }
        else{
          if (temp->right != NULL){
            temp = temp->right;
          }else{
            found = 1;
            temp->right = new_node;
          }
        }
      }

  }
    fclose(fp);
    return;

}

node* find_node(bstree* bst, char* word) {
  node* temp = bst->root;
  int catchh = 0;

  while (catchh == 0) {
    if (strcmp(temp->word,word)==0){
      return temp;
    }
    if (strcmp(temp->word,word)>0){
      if (temp->left != NULL){
        temp = temp->left;
      }
      else {
        return NULL;
      }
    }
    else{
      if (temp->right != NULL){
        temp = temp->right;
      }
      else{
        return NULL;
      }
    }
  }
  return NULL;
}

node * node_search_bt(node* node, char* key)
{
    if (node == NULL){
        return NULL;
    }
    if (strcmp(node->word,key) == 0){
        return node;
    }

    struct node* lefft = node_search_bt(node->left, key);

    if(lefft !=NULL){
      return lefft;
    }

    struct node* rightt = node_search_bt(node->right, key);
    return rightt;
}


double calculate_access_time_bt(bstree *bt){

  clock_t start, end;
  double accesstime = 0.0;
  double temptime = 0.0;

  char line[512];

  char * word;

  FILE *fp = fopen("input.txt" , "r");

  while(fgets(line, sizeof(line),fp)!= NULL){
    char *ptr = strtok(line,",");
    ptr = strtok(NULL, ",");
    word = ptr;
    node* nod;

    start = clock();
    nod = node_search_bt(bt->root,word);
    end = clock();
    if(nod == NULL){
      printf("ENTERED WORD : %s ->NOT FOUND, WILL TRY NEXT WORD IF ANY LEFT\n", word );
      continue;
    }
    temptime = (double)(end - start) / CLOCKS_PER_SEC;
    accesstime += (temptime)*(nod->frequency);
  }
  fclose(fp);
return accesstime;

}



double calculate_access_time(bstree *bst){

  clock_t start, end;
  double accesstime = 0.0;
  double temptime = 0.0;

  char line[512];

  char * word;

  FILE *fp = fopen("input.txt" , "r");

  while(fgets(line, sizeof(line),fp)!= NULL){
    char *ptr = strtok(line,",");
    ptr = strtok(NULL, ",");
    word = ptr;
    node* nod;

    start = clock();
    nod = find_node(bst,word);
    end = clock();
    if(nod == NULL){
      printf("ENTERED WORD: %s -> NOT FOUND, WILL TRY NEXT WORD IF ANY LEFT\n", word );
      continue;
    }
    temptime = (double)(end - start) / CLOCKS_PER_SEC;
    accesstime += (temptime)*(nod->frequency);
  }
  fclose(fp);
return accesstime;

}

void tree_free(node* node) {
    if(node){
        tree_free(node->left);
        tree_free(node->right);
        free(node->word);
        free(node);
    }
    return;
}

void print_recursive(node *root, int margin)
{
    if (root == NULL){
        return;
      }

    margin += 5;
    print_recursive(root->right, margin);
    int i = 5;
    while(i < margin){
      printf(" ");
      i++;
    }
    if(root->word != NULL){
    printf("%s\n",root->word );
    }
    print_recursive(root->left, margin);
}

void print_tree(node *root)
{
    print_recursive(root, 0);
}

int main()
{
  bstree* bst = (bstree*)malloc(sizeof(bstree));
  insert(bst);

  double accesstime = calculate_access_time(bst);
  printf("\n Accestime BST: \n %f\n", accesstime );
  print_tree(bst->root);
  tree_free(bst->root);
  free(bst);


  bstree* bt = (bstree*)malloc(sizeof(bstree));
  insert_bt(bt);

  double accesstime_bt = calculate_access_time_bt(bt);
  printf("\n Accestime BT: \n %f\n", accesstime_bt );
  print_tree(bt->root);

  tree_free(bt->root);
  free(bt);
  
 

    return 0;
}
