#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct Node** array;  //Burada double pointer kullanmamız, dizinin boyutunu dinamik olarak ayarlayabilmemize yardımcı olur. MinHeap yapısı, her bir düğümün işaretçisini saklayan bir diziye sahiptir.
};

struct Node* newNode(char data, unsigned freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

void swapNode(struct Node** a, struct Node** b) {  //*a *b işaretçilerinin işaret ettiği düğümleri swap işlemine tabii tuttuğumuz için double pointer kullandık. 
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node**)malloc(minHeap->capacity * sizeof(struct Node*));
    return minHeap;
}

void minHeapify(struct MinHeap* minHeap, int index) {
    int minimum = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < minHeap->size && minHeap->array[left]->freq < minHeap->array[minimum]->freq) {
        minimum = left;
    }

    if(right < minHeap->size && minHeap->array[right]->freq < minHeap->array[minimum]->freq) {
        minimum = right;
    }

    if(minimum != index) {
        swapNode(&minHeap->array[minimum], &minHeap->array[index]);
        minHeapify(minHeap, minimum);
    }
}

struct Node* extractMin(struct MinHeap* minHeap) {
    struct Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];  //Burada (size - 1) ile rootu tekrar saymamış oluruz.
    --minHeap->size;                                        //Yığından bir düğüm çıkarttığımız için yığının boyutunu küçültmüş olduk.
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct Node* minHeapNode) {
    ++minHeap->size;                                        //Burada yığına yeni bir düğüm eklediğimiz için minHeap yığınının boyutunu arttırdık. 
    int i = minHeap->size - 1;
    while(i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

struct Node* buildMinHeap(char data[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);
    for(int i = 0; i < size; ++i) {
        minHeap->array[i] = newNode(data[i], freq[i]);
    }
    minHeap->size = size;
    for(int i = size / 2 - 1; i >= 0; --i) {
        minHeapify(minHeap, i);
    }
    while(minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);  //Burada iki minimum değerin toplamını hesaplatıp yeni düğüme ekleriz. Bu sayede en düşük frekansa sahip düğümler en üstte olacak şekilde ağaç oluşturulur ve sıkıştırma için kullanılacak olan Huffman kodları belirlenir. $ iç düğümlerin değerini ayırt etmemizi sağlar. 
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct Node* root, int arr[], int top) {
    if(root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if(root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if(!root->left && !root->right) {
        printf("%c: ", root->data);
        for(int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct Node* root = buildMinHeap(data, freq, size);
    int arr[size], top = 0;
    printCodes(root, arr, top);
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {10, 34, 48, 7, 1, 8};
    int size = sizeof(data) / sizeof(data[0]);
    HuffmanCodes(data, freq, size);
    return 0;
}
