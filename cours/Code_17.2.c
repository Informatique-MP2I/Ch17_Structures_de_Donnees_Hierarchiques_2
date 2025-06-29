enum node_color_e {
  RED,   
  BLACK  
};
typedef struct binary_tree {
  int value;                 
  struct binary_tree *left; 
  struct binary_tree *right;
  enum node_color_e color;  
} binary_tree_s;
