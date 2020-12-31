#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word_node word_node;
typedef struct words_linked_list words_linked_list;

struct word_node {
    char *data;
    int count;
    word_node *next;
};

struct words_linked_list {
    word_node *head;
    word_node *tail;
};

/* Enter pointer to the string. The node will begin with its count = 1*/
word_node *create_word_node(char *node_data);

/* Inserts a node with "node data" pointing to a string into the end
   of the linked list*/
void insert_word_into_list(words_linked_list *singly_linked_list,
                           char *node_data);

/* Enter pointer to the head of the list to free it.*/
void free_linked_list(word_node *node);

/* Searches for the string in the data of the list.
   Also checks if the list holds enough for the string's count.
   Returns 'true' if so.*/
bool search(word_node *head, word_node *node);

char* readline();
char** split_string(char*);


// Complete the checkMagazine function below.
void checkMagazine(int magazine_count,
                   char **magazine,
                   int note_count,
                   char **note) {

    words_linked_list MagzineList;  //Initializing lists.
    words_linked_list NoteList;
    MagzineList.head=NULL;
	MagzineList.tail=NULL;
	NoteList.head=NULL;
	NoteList.tail=NULL;
    word_node *current;
    int i=0;

    /*This spreads the magazine array into a linked list, where words that
    appear more than once are added to the count of an existing node*/
    for (i=0; i < (magazine_count); i++){
    	current = MagzineList.head;
    	while (current != NULL){
    		if(!(strcmp(current->data, magazine[i]))){
    			current -> count++;
    		    break;
    		}
    		current=current->next;
    	}
    	if (current == NULL){
    		insert_word_into_list(&MagzineList,magazine[i]);
        }
    }

    /*This does the same thing we did for the magazine, to the note.*/
    for (i=0; i < (note_count); i++){
    	current = NoteList.head;
    	while (current != NULL){
        	if(!strcmp(current->data,note[i])){
        		current->count++;
        		break;
        	}
        	current=current->next;
    	}
        if (current == NULL){
        	insert_word_into_list(&NoteList,note[i]);
        }
    }
    current = NoteList.head;
    bool noteFits=true;

    /* Here we go over each node in the note list, and check if the magazine
    list holds enough words*/
    while (current != NULL){
    	if (!search(MagzineList.head, current)){
    	    noteFits=false;
    	    break;
        }
    	current = current->next;
    }

    /*If we've reached the end of the list and every word has been found, we
    print 'Yes'. Otherwise, 'No'.*/
    printf("%s" , noteFits? "Yes":"No");

    free_linked_list(NoteList.head);
    free_linked_list(MagzineList.head);
    return;
}

    int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char **magazine_temp = split_string(readline());

    char **magazine = malloc(m * sizeof(char*));
        //magazine is an array of *char pointers

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char **note_temp = split_string(readline());

    char **note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}


word_node *create_word_node(char *node_data) {
    word_node *node = malloc(sizeof(word_node));
    node->data = node_data;
    node->count = 1;
    node->next = NULL;
    return node;
}

void insert_word_into_list(words_linked_list *singly_linked_list,
                           char *node_data) {
    word_node *node = create_word_node(node_data);

    if (!(singly_linked_list->head)) {
        (singly_linked_list)->head = node;
    } else {
        (singly_linked_list)->tail->next = node;
    }
    (singly_linked_list)->tail = node;
}

void free_linked_list(word_node *node) {
    while (node) {
        word_node *temp = node;
        node = node->next;
        free(temp);
    }
}



bool search(word_node *head, word_node *node){
	word_node *temp = head;
	while (temp != NULL){
		if (!strcmp(temp->data, node->data) && ((temp->count)>=(node->count))){
            return true;
        }
		temp = temp->next;
    }
    return false;
}
