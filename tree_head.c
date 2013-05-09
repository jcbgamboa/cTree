#include <stdlib.h>
#include <assert.h>

#include "tree_head.h"


void tree_init(struct tree_head* root)
{
	root->father       = NULL;
	root->first_child  = NULL;
	root->last_child   = NULL;
	root->prev_sibling = NULL;
	root->next_sibling = NULL;
}

struct tree_head* tree_add_child(struct tree_head* this, struct tree_head* c)
{
	/* If one of the values is NULL, then it is simple */
	if (!this) return c;
	if (!c) return this;

	tree_remove_from_tree(c);

	if (this->first_child == NULL) {
		/* Easy case: father has no child */
		assert(this->last_child == NULL);

		this->first_child = c;
		this->last_child = c;
		return this;
	} else if (this->last_child == NULL) {
		/* Just an error checking code */
		assert(this->first_child == NULL);

		this->first_child = c;
		this->last_child = c;
		return this;
	} else {
		c->prev_sibling = this->last_child;
		c->father = this;
		this->last_child = c;
		c->prev_sibling->next_sibling = c;
		return this;
	}
}

void tree_remove_from_tree(struct tree_head* c)
{
	/* Consists the node's father information */
	if (c->father && (c->father->first_child == c))
		c->father->first_child = c->next_sibling;
	if (c->father && (c->father->last_child == c))
		c->father->last_child = c->prev_sibling;

	/* If there was a previous sibling, makes it "skip" the node as its next
	 * sibling */
	if (c->prev_sibling)
		c->prev_sibling->next_sibling = c->next_sibling;

	/* If there was a next sibling, makes it "skip" the node as its previous
	 * sibling */
	if (c->next_sibling)
		c->next_sibling->prev_sibling = c->prev_sibling;

	c->father = NULL;
	c->next_sibling = NULL;
	c->prev_sibling = NULL;
}


void tree_search_depth_first(struct tree_head* root, tree_func_t f)
{
	/* Runs `f` in the child */
	if (root->first_child) {
		assert(root->last_child != NULL);
		tree_search_depth_first(root->first_child, f);
	}

	/* Runs `f` in the node */
	if (root)
		f(root);

	/* Runs `f` in the sibling */
	if (root->next_sibling)
		tree_search_depth_first(root->next_sibling, f);
}


