#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"
//aceasta este functa de sortare
void alfabetic(Tree tree)
{
    int n= tree->direct_employees_no;
    Tree aux;
    for (int i=0; i <n -1; i++)
    for (int j=i + 1; j < n; j++)
    if (strcmp(tree->team[i]->name,tree->team[j]->name) > 0)
    {
        aux = tree->team[i];
	    tree->team[i] = tree->team[j];
	    tree->team[j] = aux;
    }
}
Tree CreareNodAngajat(char *employee_name) {
	Tree nod = (Tree)malloc(sizeof(TreeNode));
	nod->manager = NULL;
	nod->name = strdup(employee_name);
    nod->direct_employees_no = 0;
	nod->team = NULL;
	return nod;
}

Tree PointerLaNod(Tree tree, char *manager_name){
    if (tree == NULL)
        return NULL;
    if (strcmp(tree->name, manager_name) == 0)
        return tree;
//aceasta functia imi returneaza un  pointer la un angajat
//daca acesta exista si null daca nu exista
    for(int i=0; i < tree->direct_employees_no; i++) {
        if(tree->team[i] == NULL)
        if (strcmp(tree->team[i]->name, manager_name) == 0)
            return tree->team[i];
        Tree sub_tree = PointerLaNod(tree->team[i], manager_name);
        if (sub_tree)
            return sub_tree;
    }
    return NULL;
}

/* Adauga un angajat nou in ierarhie.
 *
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 * manager_name: numele sefului noului angajat
 *
 * return: intoarce ierarhia modificata. Daca tree si manager_name sunt NULL,
            atunci employee_name e primul om din ierarhie.
 */
Tree hire(Tree tree, char *employee_name, char *manager_name) {
    //se verifica cazurile limita
    if (tree == NULL && manager_name == NULL)
        {
            return CreareNodAngajat(employee_name);
        }
    Tree nod = CreareNodAngajat(employee_name);
    Tree n = PointerLaNod(tree, manager_name);
    if (n == NULL)
        return tree;
    else
        nod->manager = n;

    int size = nod->manager->direct_employees_no;

        //la toate exercitiile am folosit un ptr pentru realloc, deoarece am
        //observat ca realloc are un comportament mai special fata de malloc
        Tree *ptr = realloc(nod->manager->team, (size + 1) * sizeof(Tree));
        nod->manager->team = ptr;
    //se pune nodul la final, se creste numarul de copii si se alfabetizeaza
    nod->manager->team[size] = nod;
    nod->manager->direct_employees_no++;
    alfabetic(nod->manager);
    //free(n);
    return tree;
}

/* Sterge un angajat din ierarhie.
 *
 * tree: ierarhia existenta
 * employee_name: numele angajatului concediat
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire(Tree tree, char *employee_name) {
    Tree nod = PointerLaNod(tree, employee_name);
    if (nod == NULL)
        return tree;
    if (nod->manager == NULL)
        return tree;
    int r = 0;
    //se elimina nodul din team-ul managerului, se pune NULL
        for (int i = 0; i < nod->manager->direct_employees_no; i++)
            if(nod->manager->team[i] == nod) {
                    nod->manager->team[i] = NULL;
                    r = i;
                    break;
            }
            //se muta cu o caseta inapoi vectorul team ca sa nu mai existe NULL
            for(int j = r; j< nod->manager->direct_employees_no-1;j++)
                nod->manager->team[j] = nod->manager->team[j+1];
            nod->manager->direct_employees_no--;
    if(nod->direct_employees_no != 0) {
            //se realoca spatiu pentru copiii nodului de eliminat
            Tree* ptr = realloc(nod->manager->team, (nod->manager->direct_employees_no + nod->direct_employees_no  + 1)  * sizeof(Tree));
            nod->manager->team = ptr;
            //se insereaza copiii
            for(int i = 0; i < nod->direct_employees_no; i++) {
                nod->team[i]->manager = nod->manager;
                nod->manager->team[nod->manager->direct_employees_no] = nod->team[i];
                nod->manager->direct_employees_no++;
            }
        }
    alfabetic(nod->manager);
    free(nod->team);
    free(nod->name);
    free(nod);
    return tree;
}

/* Promoveaza un angajat in ierarhie. Verifica faptul ca angajatul e cel putin
 * pe nivelul 2 pentru a putea efectua operatia.
 *
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 *
 * return: intoarce ierarhia modificata.
 */
Tree promote(Tree tree, char *employee_name) {
    if (!tree)
        return tree;
    Tree nod = PointerLaNod(tree, employee_name);
        if (!nod)
            return tree;
    //conditie cel putin nivelul 2
    if (nod->manager && nod->manager->manager)
    {
        int r = 0;
        //se realoca spatiu la team ul managerului
        //se pun toti copiii nodului de promovat la managerull anterior
        nod->manager->team = realloc(nod->manager->team, (nod->manager->direct_employees_no + nod->direct_employees_no  + 1)  * sizeof(Tree));
        for(int i = 0; i< nod->direct_employees_no; i++) {
            nod->manager->team[nod->manager->direct_employees_no] = nod->team[i];
            nod->manager->direct_employees_no++;
            nod->team[i]->manager = nod->manager;

        }
        //se aloca noul manager al nodului
        nod->manager->manager->team = realloc(nod->manager->manager->team, (nod->manager->manager->direct_employees_no +  1)  * sizeof(Tree));
        nod->manager->manager->direct_employees_no++;
        Tree temp = nod->manager;
        //acelasi algoritm ca la functiile de mai sus
        for (int i = 0; i < nod->manager->direct_employees_no; i++)
            if(nod->manager->team[i] == nod) {

                nod->manager->manager->team[nod->manager->manager->direct_employees_no - 1] = nod;
                nod->manager = temp->manager;
                temp->team[i] = NULL;
                r = i;
                break;
            }
        for(int j = r; j < temp->direct_employees_no - 1; j++)
            temp->team[j] = temp->team[j + 1];
        temp->direct_employees_no--;
        alfabetic(temp);
        alfabetic(nod->manager);
        nod->direct_employees_no = 0;
    }
    return tree;
}

/* Muta un angajat in ierarhie.
 *
 * tree: ierarhia existenta
 * employee_name: numele angajatului
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */


Tree move_employee(Tree tree, char *employee_name, char *new_manager_name) {
    if (!tree)
        return tree;
    Tree nod = PointerLaNod(tree, employee_name);
        if (!nod)
            return tree;
    Tree m = PointerLaNod(tree, new_manager_name);
    if (!m)
        return tree;
    if (nod->manager)
    {
        if (m == nod->manager)
            return tree;
        int r = 0;
        Tree* ptr;
        ptr = realloc(nod->manager->team, (nod->manager->direct_employees_no + nod->direct_employees_no  + 1)  * sizeof(Tree));
        nod->manager->team = ptr;
        for(int i = 0; i< nod->direct_employees_no; i++) {
            nod->manager->team[nod->manager->direct_employees_no] = nod->team[i];
            nod->manager->direct_employees_no++;
            nod->team[i]->manager = nod->manager;

        }

        ptr = realloc(m->team, (m->direct_employees_no +  1)  * sizeof(Tree));
        m->team = ptr;
        m->direct_employees_no++;
        Tree temp = nod->manager;
        for (int i = 0; i < nod->manager->direct_employees_no; i++)
            if(nod->manager->team[i] == nod) {

                m->team[m->direct_employees_no - 1] = nod;
                nod->manager = m;
                temp->team[i] = NULL;
                r = i;
                break;
        }
        for(int j = r; j < temp->direct_employees_no - 1; j++)
            temp->team[j] = temp->team[j + 1];
        temp->direct_employees_no--;

        alfabetic(temp);
        alfabetic(m);
        nod->direct_employees_no = 0;
    }
    return tree;
}

/* Muta o echipa in ierarhie.
 *
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei mutate
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_team(Tree tree, char *employee_name, char *new_manager_name) {
    //se verifica cazurile limita
    if (!tree)
        return tree;
    Tree nod = PointerLaNod(tree, employee_name);
        if (!nod)
            return tree;
    Tree m = PointerLaNod(tree, new_manager_name);
    if (!m)
        return tree;
    if (nod->manager)
    {
        if (m == nod->manager)
            return tree;
        int r = 0;
        Tree *ptr;
        //se realoca spatiu in echipa managerului
        ptr = realloc(m->team, (m->direct_employees_no +  1)  * sizeof(Tree));
        m->team = ptr;
        m->direct_employees_no++;
        Tree temp = nod->manager;
        for (int i = 0; i < nod->manager->direct_employees_no; i++)
            if(nod->manager->team[i] == nod) {

                m->team[m->direct_employees_no - 1] = nod;
                nod->manager = m;
                temp->team[i] = NULL;
                r = i;
                break;
        }
        for(int j = r; j < temp->direct_employees_no - 1; j++)
            temp->team[j] = temp->team[j + 1];
        temp->direct_employees_no--;
        alfabetic(m);
    }
    return tree;
}
//am utilizat aceasta functie ca sa sterg subarborele cu radacina intr-un
// nod primit
void parcurgere_subarbore_de_sters(Tree tree) {
    if(tree == NULL || tree->name == NULL)
        return;
    int nr = tree->direct_employees_no;
    for(int i = 0; i < nr; i++)
    {
        destroy_tree(tree->team[i]);
    }
    free(tree->team);
    free(tree->name);
    free(tree);
    return;

}

/* Concediaza o echipa din ierarhie.
 *
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei concediate
 *
 * return: intoarce ierarhia modificata.
 */

void free_team(Tree tree)
{
    if(tree == NULL)
        return;
    for(int i = 0; i < tree->direct_employees_no; i++)
        destroy_tree(tree->team[i]);
    free(tree->team);
    free(tree->name);
    free(tree);
}

Tree fire_team(Tree tree, char *employee_name) {
    if (!tree)
        return tree;
    Tree nod = PointerLaNod(tree, employee_name);
    if (!nod)
        return tree;
    if (nod->manager == NULL)
        return tree;
    //se foloseste functia anterioara de stergere subarbore
    //parcurgere_subarbore_de_sters(nod);
    int r;
    for (int i = 0; i < nod->manager->direct_employees_no; i++)
            if(nod->manager->team[i] == nod) {
                    nod->manager->team[i] = NULL;
                    r = i;
                    break;
            }
        //se muta cu o caseta inapoi casa nu mai fie NULL
            for(int j = r; j< nod->manager->direct_employees_no-1;j++)
                nod->manager->team[j] = nod->manager->team[j+1];
            nod->manager->direct_employees_no--;
    parcurgere_subarbore_de_sters(nod);
    return tree;
}

/* Afiseaza toti angajatii sub conducerea unui angajat.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei
 */


//aceasta functie imi parcurge subarborele si imi pune in vetor elementele
void generare(Tree nod_primit, Tree* vector, int* contor)
{
    if(nod_primit == NULL)
        return;
    if(nod_primit != NULL)
        {
            for(int i = 0; i < nod_primit->direct_employees_no; i++)
                generare(nod_primit->team[i], vector, contor);
            vector[(*contor)++] = nod_primit;
        }
}

void sortare(FILE *f, Tree* vector, int n)
{
    Tree aux;
    for (int i=0; i <n -1; i++)
    for (int j=i + 1; j < n; j++)
    if (strcmp(vector[i]->name,vector[j]->name) > 0)
    {
        aux = vector[i];
	    vector[i] = vector[j];
	    vector[j] = aux;
    }
    for(int i = 0; i < n; i++)

    fprintf(f, "%s ", vector[i]->name);
    fprintf(f, "\n");
}

void get_employees_by_manager(FILE *f, Tree tree, char *employee_name) {
    if(tree == NULL || tree->name == NULL)
        return;
    Tree vector[3000];
    Tree nod = PointerLaNod(tree, employee_name);
    int contor = 0;
    generare(nod, vector, &contor);
    sortare(f, vector, contor);
}

/* Afiseaza toti angajatii de pe un nivel din ierarhie.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * level: nivelul din ierarhie
 */

//m-am folosit de recursivitatea si am scazut level.ul pana cand ajunge
//la 0, iar cand a ajuns la 0 afiseaza nodul respectiv
void get_employees_by_levell(Tree tree, int level, Tree* vector, int *contor) {
    if(level == 0)
            vector[(*contor)++] = tree;
    if(tree == NULL || tree->name == NULL) {
        return;
    }
    level--;
    for(int i = 0; i < tree->direct_employees_no; i++)
    {
        if(level != 0)
        //apelarea recursiva
            get_employees_by_levell(tree->team[i], level, vector, contor);
        else
        //il pune in vector
           vector[(*contor)++] = tree->team[i];
    }

}


void get_employees_by_level(FILE *f, Tree tree, int level) {
    Tree vector[5000];
    int contor = 0;
    get_employees_by_levell(tree, level, vector, &contor);
    sortare(f, vector, contor);
}



/* Afiseaza angajatul cu cei mai multi oameni din echipa.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */
void max_copii(Tree tree, int* max)
{
    //aceasta functie calculeaza numarul maxim de copii
    if(tree == NULL || tree->name == NULL) {
        return;
    }
    if(tree->direct_employees_no > *max)
        (*max) = tree->direct_employees_no;
    for(int i = 0; i< tree->direct_employees_no; i++)
        max_copii(tree->team[i], max);
}

void g(Tree *vector, Tree tree, int max, int *contor) {
    //pun in vector toti oamenii care au acel numar max ca numar de angajati
    if(tree == NULL || tree->name == NULL) {
        return;
    }
    if(tree->direct_employees_no == max)
        vector[(*contor)++] = tree;
    for(int i = 0; i < tree->direct_employees_no; i++)
        g(vector, tree->team[i], max, contor);
}

void get_best_manager(FILE *f, Tree tree) {
    int contor = 0;
    int max = 0;
    Tree vector[3000];
    max_copii(tree, &max);
    g(vector, tree, max, &contor);
    sortare(f, vector, contor);
    return;
}

/* Reorganizarea ierarhiei cu un alt angajat in varful ierarhiei.
 *
 * tree: ierarhia existenta
 * employee_name: numele angajatului care trece in varful ierarhiei
 */

Tree re(Tree initial, Tree final, Tree emp, Tree last) {
    //se verifica cazurile limita
    if (!initial || !emp)
        return final;
        //daca managerul emp.ului primit
    	if (!emp->manager) {
        	//si daca final e null
            if (!final)
            		return initial;// inseamna ca nu am de facut nimic
            //daca finalul are ceva in el, deci nu sunt la prima modificare
            emp->manager = last;//il fac pe emp sa pointeze la last(cel din "final")
	        Tree* ptr = realloc(emp->manager->team, (emp->manager->direct_employees_no + 1) * sizeof(Tree));
	        emp->manager->team = ptr;
            //il adaug si alfabetizez
	        emp->manager->team[emp->manager->direct_employees_no++] = emp;
	        alfabetic(emp->manager);
	    	return final;
	}
    //retin managerul fostului nod copil in "manager" ca sa pot sa refac
    //legaturile si sa devina copilul nodului
    Tree manager = emp->manager;
    if (!final)
        emp->manager = NULL;
    else
        emp->manager = last;
    if (emp->manager) {
        Tree *ptr = realloc(emp->manager->team, (emp->manager->direct_employees_no + 1) * sizeof(Tree));
	emp->manager->team = ptr;
        emp->manager->team[emp->manager->direct_employees_no++] = emp;
        alfabetic(emp->manager);
    }
    int r;
    //se parcurge si se muta ca sa nu ramana un gol
    for (int i = 0; i < manager->direct_employees_no; i++)
            if(manager->team[i] == emp) {
                manager->team[i] = NULL;
                r = i;
                break;
        }
        for(int j = r; j < manager->direct_employees_no - 1; j++)
            manager->team[j] = manager->team[j + 1];
        manager->direct_employees_no--;
        alfabetic(manager);
    if (!final)
        final = emp;
    last = PointerLaNod(final, emp->name);
    return re(initial, final, manager, last);
}

Tree reorganize(Tree tree, char *employee_name) {
    Tree emp = PointerLaNod(tree, employee_name);
    if(!emp || !emp->manager)
        return tree;
    return re(tree, NULL, emp, NULL);
}

/* Parcurge ierarhia conform parcurgerii preordine.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */
void preorder_traversal(FILE *f, Tree tree) {
    if(tree == NULL || tree->name == NULL) {
        return;
    }
    int nr = tree->direct_employees_no;
    if (tree->manager == NULL)
        fprintf(f, "%s ", tree->name);
    else
        fprintf(f, "%s-%s ", tree->name, tree->manager->name);
    for(int i = 0; i < nr; i++)
        preorder_traversal(f, tree->team[i]);
    if (tree->manager == NULL)
        fprintf(f, "\n");
}

/* Elibereaza memoria alocata nodurilor din arbore
 *
 * tree: ierarhia existenta
 */
void  destroy_tree(Tree tree)
{
    if(tree == NULL || tree->name == NULL)
        return;
    int nr = tree->direct_employees_no;
    for(int i = 0; i < nr; i++)
    {
        destroy_tree(tree->team[i]);
    }
    free(tree->team);
    free(tree->name);
    free(tree);
    return;
}