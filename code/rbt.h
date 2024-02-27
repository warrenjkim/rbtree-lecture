/** @file rbtree.h @brief Declaration of Red-Black Tree data structures and
 * functions.
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
 * - rbt_destroy(Tree *tree): Destroys the Red-Black Tree, freeing all
 *   allocated memory.
 * - rbt_insert(Tree *tree, const int data): Inserts a new element with the
 *   specified data into the tree.
 * - rbt_inorder(Node *root): Conducts an inorder traversal of the tree.
 * - rbt_print_tree(Node *root): Prints the structure of the tree.
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
 * @enum Color
 * @brief Represents the color of a node in a Red-Black tree.
 *
 * This enumeration is used to represent the color property of nodes within a
 * Red-Black tree.
 */
typedef enum { RED, BLACK } Color;


/**
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
    Color color; ///< The color of the node, important for maintaining tree properties.
    struct Node  *left; ///< Pointer to the left child.
    struct Node  *right; ///< Pointer to the right child.
    struct Node  *parent; ///< Pointer to the parent node.
    int data; ///< The data stored in the node.
} Node;

/**
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
    Node *root; ///< Pointer to the root node of the tree.
    size_t size; ///< Number of nodes in the tree.
} Tree;

/**
 * @brief Initializes a new Red-Black Tree.
 *
 * Allocates memory for a new Red-Black Tree and initializes its root to NULL and size to 0.
 * The caller is responsible for calling rbt_destroy to free the memory allocated by this function.
 *
 * @return A pointer to the newly created Red-Black Tree.
 */
Tree *rbt_init();

/**
 * @brief Destroys a Red-Black Tree.
 *
 * Frees all the memory associated with the Red-Black Tree's nodes and the tree itself.
 * After this operation, the pointer to the tree should not be used.
 *
 * @param tree A pointer to the Red-Black Tree.
 */
void rbt_destroy(Tree *tree);

/**
 * @brief Inserts a new value into the Red-Black Tree.
 *
 * Inserts a new node with the specified data value into the tree while maintaining
 * the Red-Black Tree properties. Adjustments and color changes are performed as necessary.
 *
 * @param tree A pointer to the Red-Black Tree where the data will be inserted.
 * @param data The data value to insert into the tree.
 * @param root A pointer to the root node of the Red-Black Tree.
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
