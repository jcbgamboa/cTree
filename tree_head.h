
/* Macros taken from /include/linux/kernel.h in the Linux Kernel */
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct tree_head {
	struct tree_head* father;

	struct tree_head* first_child;
	struct tree_head* last_child;

	struct tree_head* prev_sibling;
	struct tree_head* next_sibling;
};

typedef void (*tree_func_t)(struct tree_head *t);


/** Initializes the tree_head structure, creating a one node tree.
 *  \param root The tree element to be initialized */
void tree_init(struct tree_head* root);

/** Adds `child` as `this`' last child.
 *  \param this The "father" node.
 *  \param child The "child" node.
 *  \return A pointer to the resulting tree. */
struct tree_head* tree_add_child(struct tree_head* this, struct tree_head* child);

/** Removes the node from the tree it belonged to, consisting node's
 *  "neighborhood".
 *  \param node The node to remove from its tree. */
void tree_remove_from_tree(struct tree_head* node);

/** Runs through the tree, executing the 'f', passing as parameter the node
 *  element and the node father.
 *  \param root The root of the tree to be searched through.
 *  \param f The function to be executed in the tree.*/
void tree_search_depth_first(struct tree_head* root, tree_func_t f);


