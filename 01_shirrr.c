#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

typedef struct node
{
    int value;
    struct node* left;
    struct node* right;
    struct node* parent;
    struct node* next;
} node;

typedef struct tree
{
    struct node* root;
    int count;
} tree;

typedef struct queue
{
    struct node* start;
    struct node* end;
} queue;

void init(tree* t)
{
    t->root = NULL;
    t->count = 0;
}

void queue_init(queue* q)
{
    q->start = NULL;
    q->end = NULL;
}

void tree_clean(node* t)
{
    if (t != NULL)
    {
        if (t->left != NULL)
            tree_clean(t->left);
        if (t->right != NULL)
            tree_clean(t->right);
        free(t);
    }
}

node* find(tree* t, int value)
{
    if (t->root == NULL)
    {
        return 	NULL;
    }
    struct node* tmp = t->root;
    while (tmp)
    {
        if (value < tmp->value)
        {
            tmp = tmp->left;
            continue;
        }
        else if (value > tmp->value)
        {
            tmp = tmp->right;
            continue;
        }
        else
        {
            return tmp;
        }
    }
    return NULL;
}

int insert(tree* t, int to_insert)
{
    if (t->root == NULL)
    {
        node* tmp = (node*)malloc(sizeof(node));
        tmp->left = tmp->right = NULL;
        tmp->value = to_insert;
        tmp->parent = NULL;
        t->root = tmp;
        return 0;
    }
    int level = 0;
    node* root2 = t->root, * root3 = NULL;
    node* tmp = (node*)malloc(sizeof(node));
    tmp->value = to_insert;
    while (root2 != NULL)
    {
        root3 = root2;
        if (to_insert < root2->value)
            root2 = root2->left;
        else if (to_insert > root2->value)
            root2 = root2->right;
        else
            return 0;
        level++;
    }
    tmp->parent = root3;
    tmp->left = NULL;
    tmp->right = NULL;
    if (to_insert < root3->value)
    {
        root3->left = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    }
    else
    {
        root3->right = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    }
    t->count++;
    return 1;
}

node* min(node* root)
{
    node* l = root;
    while (l->left != NULL)
        l = l->left;
    return l;
}
node* max(node* root)
{
    node* r = root;
    while (r->right != NULL)
        r = r->right;
    return r;
}


int remove_node(node* l, int value, tree* tr)
{
    struct node* m = NULL;
    if (l->value == value)
    {
        if (l == tr->root)
        {
            if (l->left == NULL && l->right == NULL)
            {
                l = NULL;
                init(tr);
                free(l);
                return 0;
            }
            if (l->right != NULL)
            {
                m = min(l->right);
                l->value = m->value;
                remove_node(m, m->value, tr);
                return 0;
            }
            if (l->left != NULL && l->right == NULL)
            {
                m = l->left;
                m->parent = NULL;
                tr->root = m;
                free(l);
                return 0;
            }

        }
        else
        {
            if ((l->left != NULL && l->right != NULL))
            {
                m = min(l->right);
                l->value = m->value;
                remove_node(m, m->value, tr);
                return 0;

            }
            if (l->left == NULL && l->right == NULL)
            {
                m = l->parent;
                if (l == m->right) m->right = NULL;
                else m->left = NULL;
                free(l);
                return 0;
            }
            if (l->left == NULL && l->right != NULL)
            {
                m = l->parent;
                if (l == m->right) m->right = l->right;
                else m->left = l->right;
                free(l);
                return 0;
            }
            if (l->left != NULL && l->right == NULL)
            {
                m = l->parent;
                if (l == m->right) m->right = l->left;
                else m->left = l->left;
                free(l);
                return 0;
            }
        }

    }
    else
    {
        if (value < l->value)
        {
            if (l->left != NULL)
                return(remove_node(l->left, value, tr));
            else
                return 1;
        }
        else
        {
            if (l->right != NULL)
                return(remove_node(l->right, value, tr));
            else
                return 1;
        }
    }
    return 0;
}

int get_level(struct node* t)
{
    int r = 0, l = 0;
    if ((t->right) != NULL)
        r = get_level(t->right);
    if ((t->left) != NULL)
        l = get_level(t->left);
    if (r > l)
        return (r + 1);
    return (l + 1);
}

int print_tree(struct node* t)
{
    if (t == NULL)
    {
        printf("-\n");
        return 1;
    }
    struct node* Temp = t;
    int Rang = 0, i, j, k, sk;
    int* comb;
    Rang = get_level(t);
    comb = (int*)malloc(sizeof(int));
    for (i = 0; i < Rang; i++)
    {
        if (i != 0)
        {
            comb = (int*)realloc(comb, i * sizeof(int));
            for (j = 0; j < i; j++)
            {
                comb[j] = 0;
            }
        }
        j = 1;
        sk = i;
        while (sk != 0)
        {
            j = j * 2;
            sk--;
        }
        while (j != 0)
        {
            k = 0;
            Temp = t;
            for (k = 0; k < i; k++)
            {
                if (comb[k] == 0)
                {
                    if ((Temp->left) != NULL) Temp = Temp->left;
                    else
                    {
                        k = -1;
                        break;
                    }
                }
                else
                {
                    if ((Temp->right) != NULL) Temp = Temp->right;
                    else
                    {
                        k = -1;
                        break;
                    }
                }
            }
            if (i != 0)
            {
                sk = i - 1;
                comb[sk]++;
                while (1)
                {
                    if (comb[sk] == 2)
                    {
                        comb[sk] = 0;
                        sk--;
                        if (sk < 0) break;
                        else comb[sk]++;
                    }
                    else break;
                }
            }
            if (k == -1) printf("_");
            else printf("%d", (int)Temp->value);
            j--;
            if (j != 0) printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    return 1;
}


int rotate_right(tree* t, node* x) {
    if (x == NULL) return 1;
    node* y = x->left;
    if ((y != NULL) && (x != NULL))
    {
        x->left = y->right;
        if (y->right != NULL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent != NULL)
        {
            if (x->parent->left == x) x->parent->left = y;
            else x->parent->right = y;
        }
        t->root = y;
        y->right = x;
        x->parent = y;
        return 0;
    }
    else return 1;


}

int rotate_left(tree* t, node* x) {
    if (x == NULL) return 1;
    node* y = x->right;
    if ((y != NULL) && (x != NULL))
    {
        x->right = y->left;
        if (y->left != NULL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent != NULL)
        {
            if (x->parent->right == x) x->parent->right = y;
            else x->parent->left = y;
        }
        t->root = y;
        y->left = x;
        x->parent = y;
        return 0;
    }
    else return 1;
}

void enqueue(queue* q, node* to_add) 
{
    if (q->start == NULL && q->end == NULL) 
    {
        q->start = to_add;
        q->end = to_add;
    }
    else 
    {
        q->end->next = to_add;
        q->end = to_add;
    }
}

node* dequeue(queue* q) 
{
    if (q->start == q->end) 
    {
        node* to_subtract = q->start;
        q->start = NULL;
        q->end = NULL;
        return to_subtract;
    }
    else 
    {
        node* to_subtract = q->start;
        q->start = q->start->next;
        return to_subtract;
    }
}

void breadth_first_traversal(tree* t, int count) 
{
    queue q;
    queue_init(&q);
    node* t_node = t->root;

    for (count; count > 0; count--)
    {
        printf("%d ", t_node->value);
        if (t_node->left != NULL)
            enqueue(&q, t_node->left);
        if (t_node->right != NULL)
            enqueue(&q, t_node->right);

        t_node = dequeue(&q);
    }
}
    
int main()
{
    int x, i;
    tree t;
    queue q;
    init(&t);
    for (i = 0; i < 7; i++)
    {
        scanf("%d", &x);
        insert(&t, x);
    }

    breadth_first_traversal(&t, 7);
}