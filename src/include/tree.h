typedef enum {
  EXPR_ADD,
  EXPR_SUB,
  EXPR_MUL,
  EXPR_DIV,
} NodeType;


typedef struct Node{
  char* value;
  NodeType type;
  struct Node *left;
  struct Node *right;
}Node;



Node *initNode(Node* node, NodeType type, char* value);
