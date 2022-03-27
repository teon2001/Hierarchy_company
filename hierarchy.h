#ifndef _HIERARCHY_H_
#define _HIERARCHY_H_

/* 
 * Reprezentarea unui nod din arbore. 
 */
typedef struct TreeNode {
    char *name;                 // numele angajatului
    int direct_employees_no;    // numarul de copii ai nodului curent
    struct TreeNode **team;     // copiii nodului curent
    struct TreeNode *manager;   // parintele nodului curent
} TreeNode, *Tree;


Tree hire(Tree tree, char *employee_name, char *manager_name);
Tree fire(Tree tree, char *employee_name);
Tree promote(Tree tree, char *employee_name);
Tree move_employee(Tree tree, char *employee_name, char *new_manager_name);
Tree move_team(Tree tree, char *employee_name, char *new_manager_name);
Tree fire_team(Tree tree, char *employee_name);
void get_employees_by_manager(FILE *f, Tree tree, char *employee_name);
void get_employees_by_level(FILE *f, Tree tree, int level);
void get_best_manager(FILE *f, Tree tree);
Tree reorganize(Tree tree, char *employee_name);
void preorder_traversal(FILE *f, Tree tree);
void destroy_tree(Tree tree);

#endif
