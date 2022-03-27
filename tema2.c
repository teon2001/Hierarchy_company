/*
*   Created by Stefania Ghita on 12.04.2021
*   Copyright (c) 2021 Data Structures team. All rights reserved.
*   Tema 2 - Structuri de date
*   Facultatea de Automatica si Calculatoare
*   Anul Universitar 2020-2021, Seria CD
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"


void test_hire() {
    FILE *f = fopen("output_hire.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    preorder_traversal(f, t);

    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    preorder_traversal(f, t);

    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    preorder_traversal(f, t);


    t = hire(t, "a8", "a4");
    t = hire(t, "a9", "a4");
    preorder_traversal(f, t);

    t = hire(t, "a10", "a8");
    t = hire(t, "a11", "a8");
    t = hire(t, "a12", "a8");
    preorder_traversal(f, t);

    t = hire(t, "a0", "a1");
    preorder_traversal(f, t);

    t = hire(t, "a22", "a1");
    preorder_traversal(f, t);

    t = hire(t, "a55", "a1");
    preorder_traversal(f, t);

    t = hire(t, "a111", "a8");
    preorder_traversal(f, t);

    t = hire(t, "a33", "a3");
    t = hire(t, "a34", "a33");
    preorder_traversal(f, t);

    t = hire(t, "a17", "a4");
    t = hire(t, "a88", "a4");
    t = hire(t, "a91", "a4");
    preorder_traversal(f, t);
    
    destroy_tree(t);
    fclose(f);
}

void test_fire() {
    FILE *f = fopen("output_fire.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a8", "a4");
    t = hire(t, "a9", "a4");
    t = hire(t, "a10", "a8");
    t = hire(t, "a11", "a8");
    t = hire(t, "a12", "a8");
    preorder_traversal(f, t);

    t = fire(t, "lala");
    preorder_traversal(f, t);
    t = fire(t, "a1");
    preorder_traversal(f, t);

    t = fire(t, "a3");
    preorder_traversal(f, t);

    t = fire(t, "a5");
    preorder_traversal(f, t);

    t = fire(t, "a10");
    preorder_traversal(f, t);

    t = hire(t, "a3", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a0", "a8");
    t = hire(t, "a91", "a8");
    t = hire(t, "a30", "a2");
    t = fire(t, "a8");
    preorder_traversal(f, t);

    t = hire(t, "a111", "a1");
    t = fire(t, "a4");
    preorder_traversal(f, t);

    t = fire(t, "a2");
    t = fire(t, "a3");
    preorder_traversal(f, t);

    destroy_tree(t);
    fclose(f);
}

void test_promote() {
    FILE *f = fopen("output_promote.out", "w");
    if (f == NULL) {
        printf("Error opening fil!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a8", "a4");
    t = hire(t, "a9", "a4");
    t = hire(t, "a10", "a8");
    t = hire(t, "a11", "a8");
    t = hire(t, "a12", "a8");
    preorder_traversal(f, t);

    t = promote(t, "a10");
    preorder_traversal(f, t);
    t = promote(t, "a6");
    preorder_traversal(f, t);
    t = promote(t, "a12");
    preorder_traversal(f, t);
    t = promote(t, "a12");
    preorder_traversal(f, t);

    t = promote(t, "a12");
    t = promote(t, "a5");
    t = promote(t, "a1");
    t = promote(t, "a6");
    preorder_traversal(f, t);
    destroy_tree(t);

    t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");
    preorder_traversal(f, t);

    t = promote(t, "a1");
    t = promote(t, "a4");
    t = promote(t, "a83");
    preorder_traversal(f, t);

    t = fire(t, "a81");
    t = promote(t, "a85");
    preorder_traversal(f, t);

    destroy_tree(t);
    fclose(f);
}

void test_move_employee() {
    FILE *f = fopen("output_move_employee.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");
    preorder_traversal(f, t);

    t = move_employee(t, "a1", "a2");
    preorder_traversal(f, t);

    t = move_employee(t, "a2", "a1");
    preorder_traversal(f, t);

    t = move_employee(t, "a7", "a3");
    t = move_employee(t, "a6", "a3");
    preorder_traversal(f, t);

    t = move_employee(t, "a2", "a1");
    preorder_traversal(f, t);
    t = move_employee(t, "a2", "a95");
    preorder_traversal(f, t);
    t = move_employee(t, "a2", "a1");
    preorder_traversal(f, t);

    t = move_employee(t, "a3", "a4");
    t = move_employee(t, "a5", "a4");
    preorder_traversal(f, t);

    t = fire(t, "a3");
    t = fire(t, "a5");
    t = move_employee(t, "a6", "a7");
    t = move_employee(t, "a83", "a6");
    preorder_traversal(f, t);

    t = move_employee(t, "a4", "a83");
    preorder_traversal(f, t);

    destroy_tree(t);
    fclose(f);
}

void test_move_team() {
    FILE *f = fopen("output_move_team.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");
    preorder_traversal(f, t);

    t = move_team(t, "a3", "a5");
    preorder_traversal(f, t);
    t = move_employee(t, "a3", "a1");
    t = move_team(t, "a5", "a3");
    t = fire(t, "a3");
    preorder_traversal(f, t);

    t = move_team(t, "a7", "a6");
    t = hire(t, "a0", "a6");
    preorder_traversal(f, t);
    t = move_team(t, "a6", "a1");
    preorder_traversal(f, t);
    t = move_team(t, "a6", "a97");
    t = hire(t, "a20", "a1");
    t = move_team(t, "a83", "a20");
    preorder_traversal(f, t);
    t = move_team(t, "a4", "a0");
    t = hire(t, "a21", "a20");
    t = move_team(t, "a83", "a21");
    preorder_traversal(f, t);

    destroy_tree(t);
    fclose(f);
}

void test_fire_team() {
    FILE *f = fopen("output_fire_team.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");
    preorder_traversal(f, t);

    t = fire_team(t, "a89");
    t = fire_team(t, "a95");
    t = fire_team(t, "a6");
    preorder_traversal(f, t);

    t = fire_team(t, "a2");
    preorder_traversal(f, t);

    t = move_employee(t, "a3", "a93");
    t = hire(t, "a92", "a93");
    t = fire(t, "a85");
    preorder_traversal(f, t);
    t = fire_team(t, "a4");
    preorder_traversal(f, t);
    t = fire_team(t, "a1");
    t = fire_team(t, "a5");
    preorder_traversal(f, t);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a2");
    t = hire(t, "a4", "a3");
    t = promote(t, "a3");
    t = hire(t, "a5", "a1");
    t = move_team(t, "a2", "a5");
    t = move_team(t, "a3", "a2");
    t = hire(t, "a0", "a2");
    preorder_traversal(f, t);
    t = move_employee(t, "a3", "a1");
    t = fire_team(t, "a5");
    preorder_traversal(f, t);

    destroy_tree(t);
    fclose(f);
}

void test_employees_by_manager() {
    FILE *f = fopen("output_employees_by_manager.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");
    
    get_employees_by_manager(f, t, "a1");
    get_employees_by_manager(f, t, "a0");

    t = fire(t, "a8");
    t = fire(t, "a85");
    preorder_traversal(f, t);
    get_employees_by_manager(f, t, "a1");
    get_employees_by_manager(f, t, "a5");
    t = hire(t, "a0", "a5");
    get_employees_by_manager(f, t, "a5");
    t = move_team(t, "a83", "a5");
    get_employees_by_manager(f, t, "a5");
    get_employees_by_manager(f, t, "a1");
    t = fire_team(t, "a5");
    get_employees_by_manager(f, t, "a5");
    get_employees_by_manager(f, t, "a1");
    t = hire(t, "a99", "a2");
    t = move_employee(t, "a87", "a99");
    t = hire(t, "a0", "a4");
    t = hire(t, "27", "a4");
    t = hire(t, "bogdan", "a1");
    preorder_traversal(f, t);
    get_employees_by_manager(f, t, "a1");
    get_employees_by_manager(f, t, "a2");
    get_employees_by_manager(f, t, "a4");
    get_employees_by_manager(f, t, "a99");

    destroy_tree(t);
    fclose(f);
}

void test_employees_by_level() {
    FILE *f = fopen("output_employees_by_level.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");

    for (int i = -2; i <= 5; i++)
        get_employees_by_level(f, t, i);

    t = fire_team(t, "a4");
    t = hire(t, "a4", "a5");
    t = hire(t, "a0", "a5");
    get_employees_by_level(f, t, 2);
    t = move_employee(t, "a6", "a7");
    get_employees_by_level(f, t, 2);
    get_employees_by_level(f, t, 3);
    t = fire(t, "a7");
    get_employees_by_level(f, t, 3);
    get_employees_by_level(f, t, 2);
    t = promote(t, "a6");
    get_employees_by_level(f, t, 1);
    get_employees_by_level(f, t, 2);
    t = move_team(t, "a5", "a3");
    for (int i = -2; i <= 5; i++)
        get_employees_by_level(f, t, i);

    destroy_tree(t);
    fclose(f);
}

void test_best_manager() {
    FILE *f = fopen("output_best_manager.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");

    get_best_manager(f, t);
    t = fire_team(t, "a5");
    get_best_manager(f, t);
    t = move_employee(t, "a3", "a2");
    get_best_manager(f, t);
    t = fire_team(t, "a85");
    get_best_manager(f, t);
    t = move_team(t, "a6", "a7");
    get_best_manager(f, t);
    t = fire_team(t, "a4");
    get_best_manager(f, t);
    t = move_team(t, "a7", "a3");
    get_best_manager(f, t);
    preorder_traversal(f, t);
    t = fire_team(t, "a2");
    preorder_traversal(f, t);
    get_best_manager(f, t);

    destroy_tree(t);
    fclose(f);
}

void test_reorganize() {
    FILE *f = fopen("output_reorganize.out", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Tree t = hire(NULL, "a1", NULL);
    t = hire(t, "a2", "a1");
    t = hire(t, "a3", "a1");
    t = hire(t, "a4", "a1");
    t = hire(t, "a5", "a1");
    t = hire(t, "a6", "a2");
    t = hire(t, "a7", "a2");
    t = hire(t, "a83", "a4");
    t = hire(t, "a87", "a4");
    t = hire(t, "a81", "a83");
    t = hire(t, "a85", "a83");
    t = hire(t, "a89", "a83");
    t = hire(t, "a97", "a85");
    t = hire(t, "a93", "a85");
    t = hire(t, "a95", "a85");
    preorder_traversal(f, t);
    t = reorganize(t, "a0");
    preorder_traversal(f, t);
    t = reorganize(t, "a5");
    preorder_traversal(f, t);
    t = reorganize(t, "a5");
    preorder_traversal(f, t);
    t = reorganize(t, "a1");
    t = hire(t, "a0", "a5");
    preorder_traversal(f, t);
    t = reorganize(t, "a0");
    preorder_traversal(f, t);
    t = reorganize(t, "a4");
    preorder_traversal(f, t);
    t = reorganize(t, "a1");
    preorder_traversal(f, t);
    t = reorganize(t, "a83");
    preorder_traversal(f, t);
    t = reorganize(t, "a85");
    preorder_traversal(f, t);


    destroy_tree(t);
    fclose(f);
}

int main() {
    test_hire();
    test_fire();
    test_promote();
    test_move_employee();
    test_move_team();
    test_fire_team();
    test_employees_by_manager();
    test_employees_by_level();
    test_best_manager();
    test_reorganize();
    return 0;
}
