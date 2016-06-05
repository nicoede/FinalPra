#define MaxBufferConfig 50
#define MaxBufferHeader 100
#define MaxBufferHeaderInd 5000
#define MaxBuffer 10000
#define MaxNameEnt 20
#define MAX 4
#define MIN 2

int *valorAutoInc;

typedef struct{
    int tamHeader;
    int qtdCampos;
    char campos[6][30];
    int tamanhos[6];
    char tipos[6][4];
    int null[6];
    int autoInc[6];
    int nPk;
    char pk[3][10]; 
}Tabela;

struct btreeNode {
      long long int val[MAX + 1], count;
      struct btreeNode *link[MAX + 1];
};

struct btreeNode *root;

struct btreeNode * createNode(long long int val, struct btreeNode *child) {
      struct btreeNode *newNode;
      newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
      newNode->val[1] = val;
      newNode->count = 1;
      newNode->link[0] = root;
      newNode->link[1] = child;
      return newNode;
}

void inserir(int opcE);
void excluir(int opcE);
void atualizar(int opcE);
int buscar(int opcE);
int menuCrud(int opcE);
void inicializaArvore();
FILE* abreEntidade(int opcE);
FILE* abreIndice(int opcE);
Tabela lerHeader(FILE *arqEnt);
void createHeader();

//Árvore
void addValToNode(long long int val, int pos, struct btreeNode *node, struct btreeNode *child);
void splitNode (long long int val, long long int *pval, int pos, struct btreeNode *node, struct btreeNode *child, struct btreeNode **newNode);
int setValueInNode(long long int val, long long int *pval, struct btreeNode *node, struct btreeNode **child);
void insertion(long long int val);
void copySuccessor(struct btreeNode *myNode, int pos);
void removeVal(struct btreeNode *myNode, int pos);
void doRightShift(struct btreeNode *myNode, int pos);
void doLeftShift(struct btreeNode *myNode, int pos);
void mergeNodes(struct btreeNode *myNode, int pos);
void adjustNode(struct btreeNode *myNode, int pos);
int delValFromNode(long long int val, struct btreeNode *myNode);
void deletion(long long int val, struct btreeNode *myNode);
void searching(long long int val, int *pos, struct btreeNode *myNode);
void buscaIndice(long long int val, int *pos, struct btreeNode *myNode, long long int *v);
void traversal(struct btreeNode *myNode);
