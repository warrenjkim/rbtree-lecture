/**
 * @file rbt.c @brief Implementation of a Red-Black Tree in C (Insertion Only).
 *
 * This file contains the definition and implementation details of a Red-Black
 * Tree, a self-balancing binary search tree. In a Red-Black Tree, each node
 * contains an extra bit for denoting the color of the node, either RED or
 * BLACK. A Red-Black tree satisfies the following properties:
 *
 * 1. Every node is either RED or BLACK.
 * 2. Red nodes cannot have RED children; i.e. RED nodes can only have BLACK children.
 * 3. NULL nodes are BLACK.
 * 4. The root is always BLACK.
 * 5. Every path from a node to its descendant NULL nodes
 * has the same number of BLACK nodes.
 *
 * The tree structure supports operations such as insertion, deletion, and
 * search with guaranteed log(n) maximum time complexity for each operation,
 * making it efficient for data retrieval and manipulation. Space complexity is
 * linear; i.e. O(n).
 *
 * Key Components:
 * - Color: An enumeration defining the color (RED, BLACK) of nodes in the
 *   tree.
 * - Node: A structure representing a node in the Red-Black Tree, containing
 *   data, color, and pointers to its children and parent.
 * - Tree: A structure representing the entire Red-Black Tree, encapsulating
 *   its root and size.
 *
 * Key Functions:
 * - rbt_init(): Initializes and returns a new Red-Black Tree.
 * - rbt_destroy(Tree *tree): Frees memory allocated for the Red-Black Tree.
 * - rbt_insert(Tree *tree, const int data): Inserts a new node with the given
 *   data into the tree.
 * - rbt_inorder(Node *root): Performs an inorder traversal of the tree.
 * - rbt_print_tree(Node *root): Prints the tree structure.
 *
 * This file provides a basic implementation and can be extended for more
 * complex operations and use cases.
 *
 * @version 1.0
 * @date 2024-02-27
 * @author Warren Kim
 */

#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @section bst Binary Search Tree
 *
 * This section covers a subset of the fundamental operations related to managing nodes
 * within a Red-Black Tree, including initialization and destruction of nodes,
 * as well as the BST insert and search operations. These functions form the basis
 * for maintaining the structural and color properties that define Red-Black Trees.
 * Key operations include:
 *
 * - `node_init()`: Initializes a new node with specified data, setting it to RED.
 * - `node_destroy()`: Frees the memory allocated for a node, ensuring no access to its children.
 * - `bst_insert()`: Inserts a new node into the tree following BST rules, setting up for Red-Black fixups.
 * - `bst_search()`: Recursively searches for a node by its value, adhering to BST search semantics.
 */

/**
 * @brief Initializes a new node for a Red-Black tree with given data.
 *
 * This function dynamically allocates memory for a new Red-Black tree node,
 * sets its color to RED, and initializes its left, right, and parent pointers
 * to NULL. The node's data is set to the provided value.
 *
 * @param data The integer value to be stored in the new node.
 * @return A pointer to the created node if successful, error and exit otherwise.
 *
 * @note The function uses malloc for memory allocation and checks for its
 *       success. If memory allocation fails, the function prints an error
 *       message and exits the program.
 */
static Node *node_init(const int data) {
    Node *node = (Node *)(malloc(sizeof(Node)));
    if (!node) {
        perror("node_init(): malloc failed");
        exit(1);
    }

    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data = data;

    return node;
}


/**
 * @brief Frees the memory allocated for a Red-Black tree node.
 *
 * This function releases the memory allocated for a Red-Black tree node
 * and sets its left and right pointers to NULL to prevent any further access.
 * It is designed to be called on a single node after ensuring its children
 * (if any) have been properly handled or deleted to avoid memory leaks.
 *
 * @param node A pointer to the node to be destroyed.
 *
 * @note This function does not recursively delete the children of the node;
 *       it only deletes the node itself. It is the caller's responsibility to
 *       handle the deletion of any child nodes to prevent memory leaks.
 */
static void node_destroy(Node *node) {
    if (!node) {
        return;
    }

    if (node->left) {
        node->left = NULL;
    }
    if (node->right) {
        node->right = NULL;
    }

    free(node);
}


/**
 * @brief Inserts a new node using standard BST rules and updates the starting
 *        point for fixups.
 *
 * This function inserts a new node into the tree rooted at @p root, based
 * on the given @p data. It performs the insertion recursively, ensuring the
 * BST properties are maintained. Upon insertion, the function updates the
 * @p z pointer to reference the newly inserted node. @p z serves as the starting
 * point for subsequent fixup operations to preserve the Red-Black properties.
 *
 * @param root The root of the binary search tree. If @p root is NULL,
 *             indicating an empty tree, a new node is created, and @p z is set
 *             to this node, effectively starting a new tree.
 * @param data The integer value for the new node.
 * @param z    A double pointer to a Node, explicitly updated to point to the newly
 *             inserted node. This node is used for any necessary fixup operations
 *             to adjust the tree's structure and color properties post-insertion.
 * @return     The root of the tree after the insertion. This may be the same as the
 *             input @p root, or, in the case of inserting into an empty tree, the
 *             new node itself.
 *
 * @note We set equality to the left of the subtree.
 */
static Node *bst_insert(Node *root, const int data, Node **z) {
  if (!root) {
    *z = node_init(data);
    return *z;
  }

  if (data <= root->data) {
    root->left = bst_insert(root->left, data, z);
    if (root->left == *z) {
      (*z)->parent = root;
    }
  } else if (root->data < data) {
    root->right = bst_insert(root->right, data, z);
    if (root->right == *z) {
      (*z)->parent = root;
    }
  }

  return root;
}


/**
 * @brief Searches for a node with a given value in a BST.
 *
 * This function recursively searches for a node containing the specified @p data
 * within a BST. It navigates through the tree based on the binary search property:
 * left subtree contains values less than the node's value, and right subtree contains
 * values greater than the node's value.
 *
 * @param root A pointer to the current node of the BST.
 * @param data The value to search for.
 * @return     A pointer to the node containing @p data if found, NULL otherwise.
 */
static Node *bst_search(Node *root, const int data) {
    if (!root) {
        return NULL;
    }

    if (data == root->data) {
        return root;
    }
    if (data < root->data) {
        return bst_search(root->left, data);
    }
    else if (root->data < data) {
        return bst_search(root->right, data);
    }

    return NULL;
}





/**
 * @section rbt_helpers Red-Black Tree Helper Functions
 *
 * This section describes the helper functions used for maintaining the
 * Red-Black tree properties. These functions are essential for internal
 * operations such as rotations, insertions, deletions, and color adjustments
 * which ensure the tree remains balanced and conforms to red-black tree rules.
 * Key operations include:
 *
 * - `grandparent()`: Returns the grandparent of a given node.
 * - `uncle()`: Returns the uncle of a given node.
 * - `recolor()`: Handles the recolor case, fixing a double red violation.
 * - `left_rotate()`: Rotates around a node @p x once to the left.
 * - `right_rotate()`: Rotates around a node @p x once to the right.
 * - `restructure()`: Restructures the tree with respect to a node @p z,
 *                    fixing a double red violation.
 * - `fixup()`: Recursively fixes up the Red-Black tree after insertion.
 */

/**
 * @brief Returns the grandparent of a given node in a Red-Black tree.
 *
 * This helper function makes the code easier to read.
 *
 * @param z A pointer to the grandchild of the node we want.
 * @return  A pointer to the grandparent node if it exists; NULL otherwise.
 *
 * @note This function assumes that the provided node @p z and its parent are
 *       non-NULL. It is the caller's responsibility to ensure this condition is met
 *       before calling the function. Failing to do so may result in undefined behavior.
 */
static Node *grandparent(Node *z) {
    return z->parent->parent;
}


/**
 * @brief Returns the uncle of a given node in a Red-Black tree.
 *
 * The function returns the uncle of a node, which is defined as the sibling of
 * the node's parent.
 *
 * @param z A pointer to the node whose uncle is desired.
 * @return  A pointer to the uncle node if it exists; NULL otherwise. This is
 *          because if the grandparent does not exist, it implies that the uncle
 *          cannot exist.
 */
static Node *uncle(Node *z)
{
    Node *gp = grandparent(z);

    if (!gp) {
        return NULL;
    }

    if (gp->left == z->parent) {
        return gp->right;
    } else {
        return gp->left;
    }
}


/**
 * @brief Recolors the parent, uncle, and grandparent of a given node in a Red-Black tree.
 *
 * This function changes the color of the parent and uncle of the node @p z to BLACK,
 * and the color of the grandparent to RED.
 *
 * @param z A pointer to the node we are recoloring with respect to.
 * @return  A pointer to the grandparent of the node @p z after recoloring.
 *
 * @note This function assumes that the node @p z, its parent, and its grandparent are
 *       non-NULL, and that it has an uncle. These conditions are met by definition
 *       since by property 3, nil nodes are treated as BLACK.
 */
static Node *recolor(Node *z) {
    z->parent->color = BLACK;
    uncle(z)->color = BLACK;
    grandparent(z)->color = RED;

    return grandparent(z);
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
 * Here, we label the left child of @x as @p _ because it is irrelevant to the
 * rotation. Additionally, @p x's parent @p p is directly above @p x since we
 * need to check if @p x is a left or right child of @p p.
 *
 * @param x Pointer to the node to rotate. This node becomes the left child of
 *          its right child after rotation.
 * @return  The new root of the subtree after the rotation, which was the right
 *          child of @p x before the rotation.
 *
 * @note This function assumes @p x's right child is non-NULL and it's the caller's
 *       responsibility to ensure this. These conditions are met by definition of
 *       how we call the function. We call the function with respect to @p z, so
 *       @p y is defined.
 */
static Node *left_rotate(Node *x) {
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
 * Here, we label the right child of @x as @p _ because it is irrelevant to the
 * rotation. Additionally, @p x's parent @p p is directly above @p x since we
 * need to check if @p x is a left or right child of @p p.
 *
 * @param x Pointer to the node to rotate. This node becomes the right child of
 *          its left child after rotation.
 * @return  The new parent node after the rotation, which was the left child of
 *          @p x before the rotation.
 *
 * @note Assumes @p x's left child is non-NULL and it's the caller's
 * responsibility to ensure this.
 */
static Node *right_rotate(Node *x) {
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
 * @brief Restructures the tree to maintain Red-Black properties after insertion.
 *
 * This function performs rotations on a given node @p z in a Red-Black tree to
 * fix any violations caused by insertion. There are four cases considered for
 * rotation: left-left, right-right, left-right, and right-left, each requiring
 * specific rotations to maintain the tree's balancing properties.
 *
 * @param z A pointer to the node that we rotate with respect to.
 * @return  A pointer to the node that becomes the new root of the subtree after
 *          the rotations are completed.
 *
 * @note The function modifies the tree structure through rotations and recolors
 *       the nodes to adhere to Red-Black tree properties. The specific rotations
 *       performed depend on the position of @p z relative to its parent and
 *       grandparent, addressing the different cases of tree imbalance:
 *       - Left-Left Case: A single right rotation is needed.
 *       - Right-Right Case: A single left rotation is needed.
 *       - Left-Right Case: A right rotation followed by a left rotation is needed.
 *       - Right-Left Case: A left rotation followed by a right rotation is needed.
 *       After the rotations, the function correctly recolors affected nodes.
 *
 * @note The code is purposefully verbose as it serves an educational purpose.
 *       Given @p z, @p p, @p x, we can reduce redundancy by nesting cases as
 *       follows:
 *
 * @verbatim
 *  if @p z is a left child:
 *    if @p p is a left child:
 *      left_rotate()
 *    else:
 *      right_rotate(left_rotate())
 *
 *    recolor appropriately
 *  else:
 *    if @p p is a right child:
 *      right_rotate()
 *    else:
 *      left_rotate(right_rotate)
 *
 *    recolor appropriately
 *
 *  return z
 * @endverbatim
 */
static Node *restructure(Node *z) {
    /* left left case
     * - we need to perform a right rotation
     *       g             g
     *       |             |
     *       x             y
     *      / \           / \
     *     y   _    =>   z   x
     *    / \               / \
     *   z   T             T   _
     */
    if (z->parent->left == z && grandparent(z)->left == z->parent) {
        z = right_rotate(grandparent(z));
        z->color = BLACK;
        z->right->color = RED;
        return z;
    }

    /* right right case
     * - we need to perform a left rotation
     *      g              g
     *      |              |
     *      x              y
     *     / \            / \
     *    _   y    =>    x   z
     *       / \        / \
     *      T   z      _   T
     */
    else if (z->parent->right == z && grandparent(z)->right == z->parent) {
        z = left_rotate(grandparent(z));
        z->color = BLACK;
        z->left->color = RED;
        return z;
    }

    /* left right case
     * - we need to first perform a right rotation around x
     *   and then a left rotate around g
     *       u                u              u
     *       |                |              |
     *       g                g              z
     *      / \              / \           /   \
     *     x   _    =>      z   _  =>    x       g
     *    / \              / \          / \     / \
     *   _   z            x   T2       _   T1  T2  _
     *      / \          / \
     *     T1 T2        _  T1
     */
    else if (z->parent->right == z && grandparent(z)->left == z->parent) {
        z = right_rotate(left_rotate(z->parent)->parent);
        z->color = BLACK;
        z->right->color = RED;
        return z;
    }

    /* right left case
     * - we need to first perform a left rotation around x
     *   and then a right rotate around g
     *       u                u                  u
     *       |                |                  |
     *       g                g                  z
     *      / \              / \               /   \
     *     _   x    =>      _   z      =>    g       x
     *        / \              / \          / \     / \
     *       z   _            T1  x        _   T1  T2  _
     *      / \                  / \
     *     T1 T2                T2  _
     */
    else if (z->parent->left == z && grandparent(z)->right == z->parent) {
        z = left_rotate(right_rotate(z->parent)->parent);
        z->color = BLACK;
        z->left->color = RED;
        return z;
    }

    return z;
}


/**
 * @brief Fixes up the Red-Black tree after insertion to maintain its properties.
 *
 * This function adjusts the colors and structure of a Red-Black tree starting
 * from node @p z upwards to ensure that the tree maintains balance after an
 * insertion. The fixup procedure includes recoloring nodes and performing
 * rotations as necessary.
 *
 * @param z A pointer to the newly inserted node or a node that may cause a
 *          double red violation.
 * @return  A pointer to the root of the (valid Red-Black) tree after the
 *          adjustments.
 *
 * @note The function recursively addresses two main cases:
 *       1. If @p z's parent is NULL, @p z is the root and is colored BLACK.
 *       2. If both @p z and its parent are RED, then it checks the color of @p z's uncle.
 *          - If the uncle is RED, we recolor.
 *          - If the uncle is BLACK or NULL, we restructure with respect to @p z.
 *       After (recursively) addressing these cases, the function ascends the tree to its
 *       root to return it.
 */
static Node *fixup(Node *z) {
    if (!z->parent) {
        z->color = BLACK;
        return z;
    }

    if (z->color == RED && z->parent->color == RED) {
        Node *u = uncle(z);

        if (!u || u->color == BLACK) {
            return fixup(restructure(z));
        }
        else {
            return fixup(recolor(z));
        }
    }

    while (z->parent) {
        z = z->parent;
    }

    return z;
}





/**
 * @section formatter Tree Formatter
 *
 * This section covers all the helper functions for formatting so
 * we can pretty-print the tree.
 * Key operations include:
 *
 * - `height()`: Returns the height of the tree.
 * - `col()`: Returns the column position for a given height.
 */

/**
 * @brief Calculates the height of the tree.
 *
 * This function computes the height of the tree recursively.
 *
 * @param root A pointer to the root node of the tree.
 * @return     The height of the tree.
 */
static int height(Node *root) {
    if (!root) {
        return 0;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);
    return (right_height < left_height ? left_height : right_height) + 1;
}


/**
 * @brief Calculates the column position for a given height.
 *
 * This function determines the column position based on the height of the tree,
 * which is used for pretty printing purposes.
 *
 * @param h The height of the tree.
 * @return  The calculated column position.
 */
int col(int h) {
    if (h == 1)
        return 1;
    return col(h - 1) + col(h - 1) + 1;
}





/**
 * @section printing_section Printing Section
 *
 * This section is dedicated to the functions required for printing the tree. These
 * functions are specifically designed for pretty printing and do not directly relate
 * to the tree's logical operations.
 * Key operations include:
 *
 * - `print_treee()`: Utility function to pretty print the tree.
 * - `rbt_print_tree()`: Pretty prints the tree.
 * - `rbt_inorder()`: Traverses the tree in order.
 */

/**
 * @brief Utility function to print the tree structure.
 *
 * This function prints the tree structure. It uses matrix representation for
 * the tree where each node's position is calculated based on its height and
 * position in the tree.
 *
 * @param mat_tree  The matrix representation of the tree's structure.
 * @param mat_color The matrix representing the color of each node in the tree.
 * @param root      A pointer to the root node of the tree.
 * @param c         The column position for the root.
 * @param r         The row position for the root.
 * @param h         The height of the tree.
 */
static void print_tree(int **mat_tree, char **mat_color, Node *root, int c, int r, int h) {
    if (!root) {
        return;
    }

    mat_tree[r][c] = root->data;
    mat_color[r][c] = root->color == RED ? 'R' : 'B';
    print_tree(mat_tree, mat_color, root->left, c - pow(2, h - 2), r + 1, h - 1);
    print_tree(mat_tree, mat_color, root->right, c + pow(2, h - 2), r + 1, h - 1);
}


/**
 * @brief Initiates the tree printing process.
 *
 * This function sets up the necessary data structures and calls the
 * `print_tree()` function to start printing the tree structure.
 *
 * @param root A pointer to the root node of the tree.
 */
void rbt_print_tree(Node *root) {
    int h = height(root);
    int c = col(h);

    int **mat_tree = (int **)malloc(h * sizeof(int *));
    char **mat_color = (char **)malloc(h * sizeof(char *));

    for (int i = 0; i < h; i++) {
        mat_tree[i] = (int *)malloc(c * sizeof(int));
        mat_color[i] = (char *)malloc(c * sizeof(char));
    }

    print_tree(mat_tree, mat_color, root, c / 2, 0, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < c; j++) {
            if (mat_tree[i][j] == 0) {
                printf("     ");
            } else {
                printf("%d(%c) ", mat_tree[i][j], mat_color[i][j]);
            }
        }
        printf("\n");
    }
}


/**
 * @brief Inorder traversal of the tree.
 *
 * This function traverses the tree in order.
 *
 * @param root A pointer to the root node of the tree.
 */
void rbt_inorder(Node *root) {
    if (!root) {
        return;
    }

    rbt_inorder(root->left);
    printf("%d ", root->data);
    rbt_inorder(root->right);
}





/**
 * @section rbt Red-Black Tree
 *
 * This section documents the public facing API for the red-black tree. It includes
 * functions for creating the tree, inserting nodes, searching for values, and
 * other utilities that facilitate interaction with the red-black tree data structure.
 * Key operations include:
 *
 * - `rbt_init()`: Initializes a new tree with a NULL root and size of 0.
 * - `rbt_destroy()`: Frees the memory allocated for the entire tree.
 * - `rbt_insert()`: Inserts a new node into the Red-Black tree, fixing up recursively to maintain
 *                   the balance properties.
 * - `rbt_search()`: Recursively searches for a node by its value, adhering to BST search semantics.
 */

/**
 * @brief Initializes a new Red-Black tree.
 *
 * This function dynamically allocates memory for a new Red-Black tree structure,
 * sets its root to NULL, and initializes its size to 0. It returns a pointer to
 * the newly created tree.
 *
 * @return A pointer to the newly initialized Red-Black tree if successful,
 *         error and exits otherwise.
 *
 * @note The function checks for successful memory allocation and exits the program
 *       with an error message if allocation fails. This ensures that the function
 *       returns a valid pointer to a Red-Black tree.
 */
Tree *rbt_init() {
    Tree *tree = (Tree *)(malloc(sizeof(Tree)));
    if (!tree) {
        perror("rbt_init(): malloc failed");
        exit(1);
    }

    tree->root = NULL;
    tree->size = 0;
    return tree;
}


/**
 * @brief Destroys a Red-Black tree and frees its memory.
 *
 * This function recursively frees the memory allocated for the nodes of a Red-Black
 * tree. It ensures that all associated memory is released to prevent memory leaks.
 *
 * @param tree A pointer to the Red-Black tree to be destroyed.
 *
 * @note This function recursively destroys the entire tree. To destroy a single node,
 *       use `node_destroy()` instead.
 */
void rbt_destroy(Tree *tree) {
    if (!tree || !tree->root) {
        return;
    }

    if (tree->root->left) {
        node_destroy(tree->root->left);
        tree->root->left = NULL;
    }
    if (tree->root->right) {
        node_destroy(tree->root->right);
        tree->root->right = NULL;
    }

    free(tree->root);
    free(tree);
}


/**
 * @brief Inserts a value into the Red-Black tree.
 *
 * function first inserts the new node using standard BST rules,
 * empirically setting equality to the left subtree. After insertion, we perform
 * a (potentially) recursive fixup starting at the newly inserted node.
 *
 * @note The root node may change as a result of these adjustments. This is
 *       because we may rotate around the root of the tree. It is important to use
 *       this new root for future operations on the tree.
 *
 * @param root A pointer to the root node of the tree.
 * @param data The integer value to be inserted.
 * @return     A pointer to the root of the tree.
 */
Node *rbt_insert(Tree *tree, const int data) {
    Node *z = NULL;
    tree->root = bst_insert(tree->root, data, &z);

    tree->root = fixup(z);
    tree->size++;
    return tree->root;
}


/**
 * @brief Searches for a node with a given value in a Red-Black Tree.
 *
 * This function acts as a wrapper for the `bst_search()` function, initiating a search
 * for a node containing the specified @p data within a Red-Black Tree.
 *
 * @param tree A pointer to the Red-Black Tree we want to search.
 * @param data The value to search for.
 * @return A pointer to the node containing @p data if found, NULL otherwise.
 */
Node *rbt_search(Tree *tree, const int data) {
    return bst_search(tree->root, data);
}
