/**
 * @file rbt.h
 *
 * @brief Declaration of Red-Black Tree data structures and functions.
 *
 * This header file contains the declarations for the Red-Black Tree data
 * structures and outlines the interface for operations on a Red-Black Tree. A
 * Red-Black Tree is a kind of self-balancing binary search tree where each
 * node stores an extra bit representing its color (RED or BLACK) to ensure the
 * tree remains approximately balanced. This property enables the tree to
 * support insertion, deletion, and search operations in O(log n) time, making
 * it efficient for various applications. A Red-Black tree satisfies the following
 * properties:
 *
 * 1. Every node is either RED or BLACK.
 * 2. Red nodes cannot have RED children; i.e. RED nodes can only have BLACK children.
 * 3. NULL nodes are BLACK.
 * 4. The root is always BLACK.
 * 5. Every path from a node to its descendant NULL nodes
 * has the same number of BLACK nodes.
 *
 * Key Components:
 * - Color: An enumeration that defines the possible colors (RED, BLACK) of
 *   nodes in the tree.
 * - Node: A structure representing a node within the Red-Black Tree. It
 *   includes the node's data, its color, and pointers to its children and
 *   parent.
 * - Tree: A structure representing the Red-Black Tree itself, encapsulating a
 *   pointer to its root and the total number of nodes in the tree.
 *
 * Key Functions (Declared):
 * - rbt_init(): Creates and returns a new instance of a Red-Black Tree.
 * - rbt_destroy(): Destroys the Red-Black Tree, freeing all
 *   allocated memory.
 * - rbt_insert(): Inserts a new element with the
 *   specified data into the tree.
 * - rbt_inorder(): Conducts an inorder traversal of the tree.
 * - rbt_print_tree(): Prints the structure of the tree.
 *
 * This header file should be included in any source file that intends to
 * utilize the Red-Black Tree data structures or operations. The implementation
 * details are provided in the corresponding source file (`rbtree.c`).
 *
 * @version 1.0
 * @date 2024-02-27
 * @author Warren Kim
 */

#include <stddef.h>

/**
 * @typedef enum Color
 * @enum Color
 * @brief Represents the color of a node in a Red-Black tree.
 *
 * This enumeration is used to represent the color property of nodes within a
 * Red-Black tree.
 */
typedef enum { RED, BLACK } Color;


/**
 * @typedef struct Node
 * @struct Node
 * @brief Node structure for a Red-Black Tree.
 *
 * Each node in the Red-Black Tree contains the data it stores, pointers to its left and right
 * children, a pointer to its parent, and its color.
 *
 * @var Node::color
 * The color of the node is either red or black.
 *
 * @var Node::left
 * Pointer to the left child of the node. If the node does not have a left child, this pointer is NULL.
 *
 * @var Node::right
 * Pointer to the right child of the node. If the node does not have a right child, this pointer is NULL.
 *
 * @var Node::parent
 * Pointer to the parent of the node. For the root node, this pointer is NULL.
 *
 * @var Node::data
 * The data stored in the node. For simplicity, this implementation considers an integer.
 */
typedef struct Node {
    Color color;
    struct Node  *left;
    struct Node  *right;
    struct Node  *parent;
    int data;
} Node;

/**
 * @typedef struct Tree
 * @struct Tree
 * @brief Structure representing a Red-Black Tree.
 *
 * This structure is used to maintain a Red-Black Tree. It encapsulates the root of the tree
 * and the total number of nodes within the tree, providing a high-level interface for operations
 * on the tree such as insertion, and search.
 *
 * @var Tree::root
 * Pointer to the root node of the Red-Black Tree. It points to NULL when the tree is empty.
 *
 * @var Tree::size
 * The total number of nodes in the tree. This count helps in operations that may require knowledge
 * of the tree's size, such as balancing, validation, and traversal optimizations.
 */
typedef struct Tree {
    Node *root;
    size_t size;
} Tree;

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
Tree *rbt_init();

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
void rbt_destroy(Tree *tree);

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
 * @param tree A pointer to the the tree.
 * @param data The integer value to be inserted.
 * @return     A pointer to the root of the tree.
 */
Node *rbt_insert(Tree *tree, const int data);

/**
 * @brief Performs an inorder traversal of the Red-Black Tree.
 *
 * Prints the elements of the tree in an in-order fashion. This function can be used
 * for debugging purposes to visualize the tree structure and contents.
 *
 * @param root A pointer to the root node of the Red-Black Tree.
 */
void rbt_inorder(Node *root);

/**
 * @brief Prints the entire Red-Black Tree.
 *
 * Prints the tree in a structured manner to visualize its layout, including the color of each node.
 * This is useful for debugging and verifying the structure of the tree.
 *
 * @param root A pointer to the root node of the Red-Black Tree.
 */
void rbt_print_tree(Node *root);

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
Node *rbt_search(Tree *tree, const int data);
