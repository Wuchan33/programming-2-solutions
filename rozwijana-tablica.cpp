// Mikołaj Suchan
#include <iostream>

using namespace std;

#define BYTE unsigned char
#define OBJECT_TYPE int

BYTE SIZE = 4;

struct  NODE_STRUCT {
    OBJECT_TYPE* object;
    BYTE use;
    NODE_STRUCT* next;
};

NODE_STRUCT* NewNode( void ){
    NODE_STRUCT* new_node = new NODE_STRUCT;
    new_node->object = new OBJECT_TYPE[SIZE];
    new_node->use = 0;
    new_node->next = NULL;
    return new_node;
}


void DeleteNode( NODE_STRUCT* node ){
    delete [] node->object;
    delete node;
}

void Clear( NODE_STRUCT** list ){
    NODE_STRUCT* curr = *list;
    NODE_STRUCT* prev = *list;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        DeleteNode(prev);
    }
    *list = NULL;
}

void AddFirst( NODE_STRUCT** list, OBJECT_TYPE* object ){
    if (list == NULL || object == NULL) {
        return;
    }

    if (*list == NULL) {
        NODE_STRUCT* new_node = NewNode();
        *(new_node->object) = *object;
        new_node->use = 1;
        *list = new_node;
        return;
    }

    NODE_STRUCT* root = *list;
    if (root != NULL && root->use < SIZE) {
        for (int i = root->use; i > 0; i--) {
            *(root->object + i) = *(root->object + i - 1); 
        }
        *(root->object) = *object;
        root->use++;
    } else {
        NODE_STRUCT* new_node = NewNode();
        *(new_node->object) = *object;
        new_node->use = 1;
        new_node->next = root;
        *list = new_node; 
    }
}

void AddLast( NODE_STRUCT** list, OBJECT_TYPE* object ){
    if (list == NULL || object == NULL) {
        return;
    }

    if (*list == NULL) {
        NODE_STRUCT* new_node = NewNode();
        *(new_node->object) = *object;
        new_node->use = 1;
        *list = new_node;
        return;
    }

    NODE_STRUCT* curr = *list;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    if (curr != NULL && curr->use < SIZE) {
        *(curr->object + curr->use) = *object;
        curr->use++;
    } else {
        NODE_STRUCT* new_node = NewNode();
        *(new_node->object) = *object;
        new_node->use = 1;
        curr->next = new_node;
    }
}

void GetFirst( NODE_STRUCT* list, NODE_STRUCT** node, BYTE* id ){
    if (list == NULL) {
        *node = NULL;
        return;
    }
    *node = list;
    *id = 0;
}

void GetPrev( NODE_STRUCT* list, NODE_STRUCT* object, BYTE idx, NODE_STRUCT** node, BYTE* id ){
    if (list == NULL || object == NULL || object->use <= idx) {
        *node = NULL;
        return;
    }

    if (idx != 0) {
        *node = object;
        *id = idx - 1;
    } else {
        if (list == object) {
            *node = NULL;
            return;
        }
        while (list != object) {
            *node = list;
            *id = list->use - 1;
            list = list->next;
        }
    }
}

void GetNext( NODE_STRUCT* list, NODE_STRUCT* object, BYTE idx, NODE_STRUCT** node, BYTE* id ){
    if (list == NULL || object == NULL || object->use <= idx) {
        node = NULL;
        return;
    }

    if (idx + 1 < object->use) {
        *node = object;
        *id = idx + 1;
    } else {
        if (object->next == NULL) {
            *node = NULL;
            return;
        }
        *node = object->next;
        *id = 0;
    }
}

void GetLast( NODE_STRUCT* list, NODE_STRUCT** node, BYTE* id ){
    if (list == NULL) {
        *node = NULL;
        return;
    }

    while (list != NULL) {
        *node = list;
        *id = list->use-1;
        list = list->next;
    }
}

void RemoveFirst( NODE_STRUCT** list ){
    if (list == NULL || *list == NULL) {
        return;
    }

    NODE_STRUCT* curr = *list;
    NODE_STRUCT* prev = *list;
    while (curr != NULL) {
        if (curr->use != 0) {
            for (int i = 0; i < SIZE - 1; i++) {
                *(curr->object + i) = *(curr->object + i + 1);
            }
            curr->use--;
            if (curr->use == 0) {
                if (prev == curr) {
                    *list = curr->next;
                } else if (curr->next != NULL) {
                    prev->next = curr->next;
                }
                DeleteNode(curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void RemovePrev( NODE_STRUCT** list, NODE_STRUCT* node, BYTE id ){
    if (list == NULL || *list == NULL || node == NULL || node->use <= id) {
        return;
    }

    if (id != 0) {
        for (int i = id - 1; i < SIZE; i++) {
            *(node->object + i) = *(node->object + i + 1);
        }
        node->use--;
    } else {
        if (*list == node) {
            return;
        }
        NODE_STRUCT* curr = *list;
        NODE_STRUCT* prev = *list;
        while (curr->next != node) {
            prev = curr;
            curr = curr->next;
        }
        curr->use--;
        if (curr->use == 0) {
            if (prev == curr) {
                *list = curr->next;
            } else {
                prev->next = curr->next;
            }
            DeleteNode(curr);
        }
    }
}

void RemoveCurrent( NODE_STRUCT** list, NODE_STRUCT* node, BYTE id ){
    if (list == NULL || *list == NULL || node == NULL) {
        return;
    }

    NODE_STRUCT* curr = *list;
    NODE_STRUCT* prev = *list;
    while (curr != node) {
        prev = curr;
        curr = curr->next;
    }
    curr->use--;
    for (int i = id; i < SIZE - 1; i++) {
        *(curr->object + i) = *(curr->object + i + 1);
    }
    if (curr->use == 0) {
        if (prev == curr) {
            *list = curr->next;
        } else {
            prev->next = curr->next;
        }
        DeleteNode(curr);
    }
}

void RemoveNext( NODE_STRUCT* list, NODE_STRUCT* node, BYTE id ){
    if (list == NULL || node == NULL || node->use <= id) {
        return;
    }

    if (id + 1 < node->use) {
        for (int i = id + 1; i < SIZE; i++) {
            *(node->object + i) = *(node->object + i + 1);
        }
        node->use--;
    } else {
        if (node->next == NULL) {
            return;
        }
        NODE_STRUCT* next = node->next;
        for (int i = 0; i < SIZE; i++) {
            *(next->object + i) = *(next->object + i + 1);
        }
        next->use--;
        if (next->use == 0) {
            if (next->next != NULL) {
                node->next = next->next;
            } else {
                node->next = NULL;
            }
            DeleteNode(next);
        }
    }
}

void RemoveLast( NODE_STRUCT** list){
    if (list == NULL || *list == NULL) {
        return;
    }

    NODE_STRUCT* curr = *list;
    NODE_STRUCT* prev = *list;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    curr->use--;
    if (curr->use == 0) {
        if (curr == *list) {
            *list = NULL;
        } else {
            prev->next = NULL;
        }
        DeleteNode(curr);
    }
}

void Find( NODE_STRUCT* list, OBJECT_TYPE* val, NODE_STRUCT** node, BYTE* id ){
    if (list == NULL) {
        return;
    }

    while (list != NULL) {
        for (int i = 0; i < list->use; i++) {
            if (*val == *(list->object + i)) {
                *node = list;
                *id = i;
                return;
            }
        }
        list = list->next;
    }
    *node = NULL;
}

void Compress( NODE_STRUCT* list ){
    if (list == NULL) {
        return;
    }
    NODE_STRUCT* add = list;
    NODE_STRUCT* del = list;
    int id_del = 0, id_add = 0;
    while (del != NULL) {
        *(add->object + id_add) = *(del->object+id_del);
        id_add++;
        id_del++;
        if (id_del == del->use) {
            del = del->next;
            id_del = 0;
        }
        if (id_add == SIZE) {
            add->use = SIZE;
            add = add->next;
            id_add = 0;
        }
    }

    NODE_STRUCT* curr = list;
    if (add != NULL) {
        add->use = id_add;
        if (id_add != 0) {
            curr = add;
            add = add->next;
            curr->next = NULL;
        } else {
            while (curr->next != add) {
                curr = curr->next;
            }
            curr->next = NULL;
        }
    }
    while (add != NULL) {
        curr = add;
        add = add->next;
        curr->use = 0;
        DeleteNode(curr);
    }
}

void Reverse( NODE_STRUCT* list ){
    if (list == NULL) {
        return;
    }
    NODE_STRUCT* temp = NULL;
    NODE_STRUCT* curr = list;
    while (curr != NULL) {
        for (int i = 0; i < curr->use; i++) {
            AddFirst(&temp, (curr->object + i));
        }
        curr = curr->next;
    }
    Compress(temp);
    Compress(list);
    NODE_STRUCT* head = temp;
    while (temp != NULL) {
        list->use = temp->use;
        for (int i = 0; i < list->use; i++) {
            *(list->object+i) = *(temp->object+i);
        }
        temp = temp->next;
        list = list->next;
    }
    Clear(&head);
}
