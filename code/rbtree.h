#include <stdlib.h>

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
 * @brief Represents a node in a Red-Black tree.
 *
 * This structure defines the properties of the nodes within a Red-Black tree.
 */
typedef struct Node {
    Color color;            /**< The color of the node. */
    struct Node  *left;     /**< Pointer to the left child node. */
    struct Node  *right;    /**< Pointer to the right child node. */
    struct Node  *parent;   /**< Pointer to the parent node. */
    int data;               /**< The data value stored in the node. */
} Node;


/**
 * @brief Initializes a Red-Black tree node.
 *
 * Allocates memory for a new Red-Black tree node, initializes it with the given
 * data, and sets its color to RED. This function is typically used to create
 * new nodes before inserting them into the Red-Black tree.
 *
 * Usage:
 * @code
 * Node* root = rbt_init();
 * @endcode
 *
 * @param data The integer value to initialize the node with.
 * @return A pointer to the newly created Node that is colored RED and
 * initialized with the given data. Returns NULL if the node could not be
 * created due to memory allocation failure.
 */
Node *rbt_init(const int data);


/**
 * @brief Destroys the entire Red-Black tree.
 *
 * This function recursively destroys the tree starting from the root, including
 * all its subtrees. It frees up all the resources used by the nodes of the
 * tree. After calling this function, the pointer to the tree should not be used
 * unless it is reassigned to a new tree.
 *
 * @param root A pointer to the root of the tree. It's
 * important that this parameter is correctly provided to avoid undefined
 * behavior or memory leaks.
 *
 * Usage:
 * @code
 * Node* root = rbt_init();
 * root = rbt_insert(root, 10);
 * root = rbt_insert(root, 20);
 * rbt_destroy(root); // destroys the above tree.
 * root = NULL; // avoid dangling pointer usage
 * @endcode
 */
void rbt_destroy(Node *node);


/**
 * @brief Inserts a value into the Red-Black tree.
 *
 * This function inserts a new node into the Red-Black tree. The insertion
 * follows the Red-Black tree properties to ensure the tree remains balanced.
 *
 * @details The function first inserts the new node using standard BST rules,
 * empirically setting equality to the left subtree. After insertion, we perform
 * a (potentially) recursive fixup starting at the newly inserted node.
 *
 * @note The root node may change as a result of these adjustments. This is
 * because we may rotate around the root of the tree. It is important to use
 * this new root for future operations on the tree.
 *
 * Example usage:
 * @code
 * Node *root = NULL;
 * root = rbt_insert(root, 10);
 * root = rbt_insert(root, 20);
 * @endcode
 *
 * @param root A pointer to the root node of the tree.
 * @param data The integer value to be inserted.
 * @return A pointer to the root of the tree.
 */
Node *rbt_insert(Node *root, const int data);


static Node *rbt_right_rotate(Node *x);
static Node *rbt_left_rotate(Node *x);

static Node *rbt_fixup(Node *root);

static Node *rbt_recolor(Node *z);
static Node *rbt_restructure(Node *z);

static Node *bst_insert(Node *root, const int data, Node **z);

