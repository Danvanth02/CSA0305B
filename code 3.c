#include <stdio.h>
#include <stdlib.h>

typedef struct Trie {
    struct Trie *child[26];
    int words; /* number of words passing through here */
    int end;   /* 1 if a word ends here */
} Trie;

Trie *node(void) { return calloc(1, sizeof(Trie)); }

void insert(Trie *t, const char *w)
{
    // TODO 1: For every lowercase letter of w, create the child node if it is missing,
    // move to it and increase its words count; mark end at the last node
    Trie *curr = t;
    for (int i = 0; w[i] != '\0'; i++) {
        int idx = w[i] - 'a';
        if (curr->child[idx] == NULL) {
            curr->child[idx] = node();
        }
        curr = curr->child[idx];
        curr->words++;
    }
    curr->end = 1;
}

int count_prefix(const Trie *t, const char *p)
{
    // TODO 2: Follow the letters of p; return 0 if a letter is missing, otherwise the
    // words count of the last node
    const Trie *curr = t;
    for (int i = 0; p[i] != '\0'; i++) {
        int idx = p[i] - 'a';
        if (curr->child[idx] == NULL) {
            return 0;
        }
        curr = curr->child[idx];
    }
    return curr->words;
}

void destroy(Trie *t)
{
    if (!t) return;
    for (int i = 0; i < 26; i++) destroy(t->child[i]);
    free(t);
}

int main(void)
{
    const char *contacts[] = {"anand", "anitha", "anu", "arun", "bala", "anusuya"};
    Trie *root = node();
    for (int i = 0; i < 6; i++) insert(root, contacts[i]);

    const char *typed[] = {"a", "an", "anu", "b", "z"};
    for (int i = 0; i < 5; i++)
        printf("%s:%d ", typed[i], count_prefix(root, typed[i]));
    printf("\n");

    destroy(root);
    return 0;
}