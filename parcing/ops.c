/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:34 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 13:55:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

void inorder(t_trs *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%s ->", root->value);
    inorder(root->right);
  }
  
  // Preorder
  void preorder(t_trs *root) {
    if (root == NULL) return;
    printf("%s ->", root->value);
    preorder(root->left);
    preorder(root->right);
  }
  
  // Postorder traversal
  void postorder(t_trs *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%s ->", root->value);
  }
  
  // Create a new Node
  t_trs* createNode(char *value) {
    t_trs *newNode = malloc(sizeof(t_trs));
    newNode->value = strdup(value);
    newNode->left = NULL;
    newNode->right = NULL;
  
    return newNode;
  }
  
  // Insert on the left of the node
  t_trs* insertLeft(t_trs *root, char *value) {
    root->left = createNode(value);
    return root->left;
  }
  
  // Insert on the right of the node
  t_trs* insertRight(t_trs *root, char *value) {
    root->right = createNode(value);
    return root->right;
  }
  