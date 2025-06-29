binary_tree_s *fix_red_black(binary_tree_s *root) {
  if(root->left != NULL && root->left->color == RED && root->left->left != NULL && root->left->left->color == RED){
    root->left->left->color = BLACK;
    return bst_rotate_right(root);
  }
  if(root->left != NULL && root->left->color == RED && root->left->right != NULL && root->left->right->color == RED){
    root->left->color = BLACK;
    root->left = bst_rotate_left(root->left);
    return bst_rotate_right(root);  
  }
  if(root->right != NULL && root->right->color == RED && root->right->right != NULL && root->right->right->color == RED){
    root->right->right->color = BLACK;
    return bst_rotate_left(root);
  }
  if(root->right != NULL && root->right->color == RED && root->right->left != NULL && root->right->left->color == RED){
    root->right->color = BLACK;
    root->right = bst_rotate_right(root->right);
    return bst_rotate_left(root);
  }
  return root;
}  
