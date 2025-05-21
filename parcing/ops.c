/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/21 01:02:57 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

// void inorder(t_trs *root) {
//     if (root == NULL) return;
//     inorder(root->left);
//     printf("%s ->", root->value);
//     inorder(root->right);
//   }
  /*
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
    newNode->value = ft_strdup(value);
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
  
  */
