#include "rbtree.h"
#include <stdlib.h>

Node *rbt_init(const int data) {
    Node *node = (Node *)(malloc(sizeof(Node)));
    if (!node) {
        return NULL;
    }

    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data = data;

    return node;
}

void rbt_destroy(Node *root) {
    if (!root) {
        return;
    }

    if (root->left) {
        rbt_destroy(root->left);
        root->left = NULL;
    }
    if (root->right) {
        rbt_destroy(root->right);
        root->right = NULL;
    }

    free(root);
}

/**
 * @brief Performs a left rotation on the given node within a Red-Black tree.
 *
 * This function applies a left rotation to the node pointed to by @p x,
 * adjusting the tree's structure to maintain Red-Black properties. Below is an
 * ASCII art diagram illustrating the left rotation:
 *
 * @verbatim
 *    p              p
 *    |              |
 *    x              y
 *   / \            / \
 *  _   y    =>    x   z
 *     / \        / \
 *    T   z      _   T
 * @endverbatim
 *
 * The rotation involves reassigning parent-child relationships between @p x,
 * its right child @p y, and the left child of @p y. Here, we label the right
 * child of @x as @p _ because it is irrelevant to the rotation. Additionally,
 * @p x's parent @p p is directly above @p x since we need to check if @p x is
 * a left or right child of @p p.
 *
 * @param x Pointer to the node to rotate. This node becomes the left child of
 * its right child after rotation.
 * @return The new parent node after the rotation, which was the right child of
 * @p x before the rotation.
 *
 * @note Assumes @p x's right child is non-NULL and it's the caller's
 * responsibility to ensure this.
 */
static Node *rbt_left_rotate(Node *x) {
    Node *y = x->right;

    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent) {
        if (x->parent->left == x) {
            x->parent->left = y;
        } else if (x->parent->right == x) {
            x->parent->right = y;
        }
    }

    y->left = x;
    x->parent = y;

    return y;
}

/**
 * @brief Performs a right rotation on the given node within a Red-Black tree.
 *
 * This function applies a right rotation to the node pointed to by @p x,
 * adjusting the tree's structure to maintain Red-Black properties. Below is an
 * ASCII art diagram illustrating the right rotation:
 *
 * @verbatim
 *      g             g
 *      |             |
 *      x             y
 *     / \           / \
 *    y   _    =>   z   x
 *   / \               / \
 *  z   T             T   _
 * @endverbatim
 *
 * The rotation involves reassigning parent-child relationships between @p x,
 * its left child @p y, and the right child of @p y. Here, we label the left
 * child of @x as @p _ because it is irrelevant to the rotation. Additionally,
 * @p x's parent @p p is directly above @p x since we need to check if @p x is
 * a left or right child of @p p.
 *
 * @param x Pointer to the node to rotate. This node becomes the right child of
 * its left child after rotation.
 * @return The new parent node after the rotation, which was the left child of
 * @p x before the rotation.
 *
 * @note Assumes @p x's left child is non-NULL and it's the caller's
 * responsibility to ensure this.
 */
static Node *rbt_right_rotate(Node *x) {
    Node *y = x->left;

    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent) {
        if (x->parent->left == x) {
            x->parent->left = y;
        } else if (x->parent->right == x) {
            x->parent->right = y;
        }
    }

    y->right = x;
    x->parent = y;

    return y;
}

/**
 * @brief Inserts a new node using standard BST rules and updates the starting
 * point for fixups.
 *
 * This function inserts a new node into the tree rooted at @p root, based
 * on the given @p data. It performs the insertion recursively,
 * ensuring the BST properties are maintained. Upon insertion, the function
 * updates the @p z pointer to reference the newly inserted node. @p z serves
 * as the starting point for subsequent fixup operations to preserve
 * the Red-Black properties.
 *
 * @param root The root of the binary search tree. If @p root is NULL,
 * indicating an empty tree, a new node is created, and @p z is set to this
 * node, effectively starting a new tree.
 * @param data The integer value for the new node.
 * @param z A double pointer to a Node, explicitly updated to point to the newly
 * inserted node. This node is used for any necessary fixup operations to adjust
 * the tree's structure and color properties post-insertion.
 * @return The root of the tree after the insertion. This may be the same as the
 * input @p root, or, in the case of inserting into an empty tree, the new node
 * itself.
 *
 * @note The correct update of the @p z pointer is crucial for the integrity of
 * Red-Black Tree operations, as it facilitates the required adjustments to
 * maintain tree balance and coloring rules.
 *
 * @note We set equality to the left of the subtree.
 */
static Node * bst_insert(Node *root, const int data, Node **z) {
  if (!root) {
    *z = rbt_init(data);
    return *z;
  }

  if (data <= root->data) {
    root->left = bst_insert(root->left, data, z);
    if (root->left == *z) {
      (*z)->parent = root->left;
    }
  } else if (root->data < data) {
    root->right = bst_insert(root->right, data, z);
    if (root->right == *z) {
      (*z)->parent = root->right;
    }
  }

  return root;
}

/**
 * @brief Returns the grandparent of a given node in a Red-Black tree.
 *
 * This function provides a simple way to access the grandparent of a node
 * within a Red-Black tree.
 *
 * @param z A pointer to the grandchild of the node we want.
 * @return A pointer to the grandparent node if it exists, NULL otherwise.
 *
 * @note This function assumes that the provided node @p z and its parent are
 * non-NULL. It is the caller's responsibility to ensure this condition is met.
 */
static Node *rbt_grandparent(Node *z) {
    return z->parent->parent;
}

/**
 * @brief Returns the uncle of a given node in a Red-Black tree.
 *
 * The function calculates and returns the uncle of a node, which is defined as
 * the sibling of the node's parent.
 *
 * @param z A pointer to the nephew of the node we want.
 * @return A pointer to the uncle node if it exists, NULL otherwise. This is
 * because if the grandparent does not exist, it implicitly means the uncle
 * cannot exist.
 *
 * @note The function safely handles cases where the node's grandparent might
 * not exist by returning NULL.
 */
static Node *rbt_uncle(Node *z) {
    Node *gp = rbt_grandparent(z);

    if (!gp) {
        return NULL;
    }

    if (gp->left == z->parent) {
        return gp->right;
    } else {
        return gp->left;
    }
}

static Node *rbt_fixup(Node *z) {
    if (!(z->parent)) {
        return z;
    }

    if (z->parent->color == BLACK) {
        return z->parent;
    }

    if (z->color == RED && z->parent->color == RED) {
        Node *uncle = rbt_uncle(z);

        if (!uncle || uncle->color == BLACK) {
            z = rbt_fixup(rbt_restructure(z));
        }
        else {
            z = rbt_fixup(rbt_recolor(z));
        }
    }

    return z;
}

Node *rbt_insert(Node *root, const int data) {
    if (!root) {
        root = rbt_init(data);
        root->color = BLACK;
        return root;
    }

    Node *z = NULL;
    root = bst_insert(root, data, &z);

    root = rbt_fixup(z);
    return root;
}


static Node *rbt_recolor(Node *z) {
    z->parent->color = BLACK;
    rbt_uncle(z)->color = BLACK;
    rbt_grandparent(z)->color = RED;

    return rbt_grandparent(z);
}



static Node *rbt_restructure(Node *z) {
    // left left case
    // * we need to perform a right rotate
    //       g             g
    //       |             |
    //       x             y
    //      / \           / \
    //     y   _    =>   z   x
    //    / \               / \
    //   z   T             T   _
    if (z->parent->left == z && rbt_grandparent(z)->left == z->parent) {
        return rbt_right_rotate(rbt_grandparent(z));
    }

    // right right case
    // * we need to perform a left rotate
    //      g              g
    //      |              |
    //      x              y
    //     / \            / \
    //    _   y    =>    x   z
    //       / \        / \
    //      T   z      _   T
    else if (z->parent->right == z && rbt_grandparent(z)->right == z->parent) {
        return rbt_left_rotate(rbt_grandparent(z));
    }

    // left right case
    // * we need to first perform a right rotate around x
    //   and then a left rotate around g
    //       u                u              u
    //       |                |              |
    //       g                g              z
    //      / \              / \           /   \
    //     x   _    =>      z   _  =>    x       g
    //    / \              / \          / \     / \
    //   _   z            x   T2       _   T1  T2  _
    //      / \          / \
    //     T1 T2        _  T1
    else if (z->parent->left == z && rbt_grandparent(z)->right == z->parent) {
        return rbt_left_rotate(rbt_right_rotate(z->parent));
    }

    // right left case
    // * we need to first perform a left rotate around x
    //   and then a right rotate around g
    //       u                u                  u
    //       |                |                  |
    //       g                g                  z
    //      / \              / \               /   \
    //     _   x    =>      _   z      =>    g       x
    //        / \              / \          / \     / \
    //       z   _            T1  x        _   T1  T2  _
    //      / \                  / \
    //     T1 T2                T2  _
    else if (z->parent->right == z && rbt_grandparent(z)->left == z->parent) {
        return rbt_right_rotate(rbt_left_rotate(z->parent));
    }

    return NULL;
}




