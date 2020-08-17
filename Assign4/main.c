/* 
 * File:   main.c
 * Author: hoangjam
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 20

typedef struct data {
    int number;
    char name[MAX_LEN];
} node_data_t;

typedef struct node {
    node_data_t data;
    struct node *left;
    struct node *right;
} tree_node_t;

tree_node_t *newNode(node_data_t newData) {
    tree_node_t *node = (tree_node_t*) malloc(sizeof (tree_node_t));
    node->data = newData;
    node->left = NULL;
    node->right = NULL;
    return node;
}

tree_node_t *createEmployeeNode(int number, char name[MAX_LEN]);
void addEmployee(tree_node_t *root, tree_node_t *employeeNode);
void removeEmployee(tree_node_t* root, int number);

// You must implement all the functions below

node_data_t* populateEmployeesData() {
    node_data_t *employees = (node_data_t *) calloc(5, sizeof (node_data_t));
    int index = 0;

    employees[index].number = 50;
    strncpy(employees[index].name, "Chris", MAX_LEN);
    ++index;

    employees[index].number = 25;
    strncpy(employees[index].name, "James", MAX_LEN);
    ++index;

    employees[index].number = 100;
    strncpy(employees[index].name, "Jerry", MAX_LEN);
    ++index;

    employees[index].number = 75;
    strncpy(employees[index].name, "John", MAX_LEN);
    ++index;

    employees[index].number = 125;
    strncpy(employees[index].name, "Chris", MAX_LEN);
    ++index;

    return employees;
} //this function should create and return an array of five different employees. You should hardcode the employees data in the function (e.g. no need to interact with the user)

tree_node_t* createTreeFromArray(node_data_t *employeesData) {
    tree_node_t *root = (tree_node_t *) calloc(1, sizeof (tree_node_t));
    memcpy(&root->data, &employeesData[0], sizeof (node_data_t));
    int i;

    for (i = 1; i < 5; ++i) {
        tree_node_t *emp = createEmployeeNode(employeesData[i].number, employeesData[i].name);
        addEmployee(root, emp);
    }
    return root;

} //this function is supposed to take an array of struct (node_data_t) as input and create a BST based of this array. The function should return a pointer to the root of the BST

tree_node_t* createEmployeeNode(int number, char name[MAX_LEN]) {
    tree_node_t *node = (tree_node_t *) calloc(1, sizeof (tree_node_t));

    node->data.number = number;
    strncpy(node->data.name, name, MAX_LEN);

    return node;
} // this function should create a BST node that holds one employee. This function should be called inside addEmployee function

void printAllEmployees(tree_node_t* root) {

    if (root == NULL) {
        //        printf("Nothing to print");
        return;
    }
    printAllEmployees(root->left);
    printf("%d-%s \n", root->data.number, root->data.name);
    printAllEmployees(root->right);

} // function to display the employees data (in order).

tree_node_t *addEmployeeHelper(tree_node_t *node, tree_node_t *employeeNode) {
    if (node == NULL) {
        return NULL;
    }

    int num = employeeNode->data.number;
    if (num < node->data.number) {
        return node->left;
    } else if (num > node->data.number) {
        return node->right;
    } else {
        printf("Can't have duplicates numbers!");
        return node;
    }
}

void addEmployee(tree_node_t* root, tree_node_t* employeeNode) {
    tree_node_t *temp = root;
    if (root == NULL) {
        return;
    }

    int newNum = employeeNode->data.number;

    // traverse BST until we hit NULL, insert new employee under parent of that NULL child-node
    while (temp != NULL) {
        tree_node_t *next = addEmployeeHelper(root, employeeNode);

        if (next == temp) {
            printf("Employee number already exists!");
            return;
        } else if (next == NULL) {
            if (newNum < root->data.number) {
                temp->left = employeeNode;
                return;
            } else {
                temp->right = employeeNode;
                return;
            }
        }

        temp = next;
    }
} // this function should and insert an employee node into the BST. node is supposed to be created by createEmployeeNode function. The function should print a message if an employee with the same number exists in the BST (duplicates aren't allowed)

tree_node_t* findEmployeeByNumber(tree_node_t* root, int number) {
    if (root == NULL || number == root->data.number)
        return NULL;

    if (number > root->data.number) {
        findEmployeeByNumber(root->right, number);
    } else {
        findEmployeeByNumber(root->left, number);
    }
} // this function should search and return an employee node with specific number. If no fount, it should return null.

tree_node_t* findEmployeeByName(tree_node_t* root, char name[MAX_LEN]) {
    tree_node_t *employee = (tree_node_t *) calloc(25, sizeof (tree_node_t));
    int i;
    if (root == NULL || name == root->data.name)
        return root;

    for (i = 0; i < 5; i++) {
        employee[i].data.number;
        if (strncmp(employee[i].data.name, name, MAX_LEN) == 0) {
            return employee[i].data.name;
        }
        else {
            // no matches
            return NULL;
        }
    }

    return employee;
} // this function should search and return an employee node with specific name. If no fount, it should return null. The function should return an array of pointers to all the tree nodes where the name is equal to the parameter passed to the function

void updateEmployeeName(tree_node_t* root, int number, char newName[MAX_LEN]) {
    tree_node_t *node = findEmployeeByNumber(root, number);

    if (node == NULL) {
        printf("No record of employee with number: %d\n", number);
        return;
    }

    strncpy(node->data.name, newName, MAX_LEN);
} // this function should updated the name of an employee in the tree. number parameter is used to find the employee, newName is the new name that should be assigned to the employee

void updateEmployeeNumber(tree_node_t* root, int number, int newNumber) {
    char name[MAX_LEN];
    tree_node_t *employee = findEmployeeByNumber(root, number);
    strncpy(name, employee->data.name, MAX_LEN);

    removeEmployee(root, number);
    addEmployee(root, createEmployeeNode(newNumber, name));

} // this function should updated the number of an employee in the tree. number parameter is used to find the employee, newNumber is the new number that should be assigned to the employee. When updating the number of a node the tree should be changed (as the location of the node would be changed to maintain thre BST structure). It would be easier to remove the node (using removeEmployee function) and re-insert it in the tree (using addEmployee function)

void removeEmployee(tree_node_t* root, int number) {

    if (root == NULL) {
        printf("Nothing to delete");
    }

    if (number < root->data.number) {
        removeEmployee(root->left, number);
    } else if (number > root->data.number) {
        removeEmployee(root->right, number);
    } else {
        if (root->left == NULL) {
            tree_node_t *temp = root->right;
            free(root);
        } else if (root->right == NULL) {
            tree_node_t *temp = root->left;
            free(root);
        }
    }

} // this function should remove a node from the tree. Check out the deletion algorithm here: http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete2.html

int main() {

    node_data_t *employeesData = populateEmployeesData();
    tree_node_t* root = createTreeFromArray(employeesData);
    printf("The employees list:\n");
    printAllEmployees(root);

    addEmployee(root, createEmployeeNode(123, "alexandra"));
    printf("\n\nThe employees list after adding Alexandra:\n");
    printAllEmployees(root);

    if (findEmployeeByNumber(root, 234) != NULL)
        printf("An employee with the number 234 exists in the tree\n");
    else
        printf("An employee with the number 234 doesn't exist in the tree\n");

    if (findEmployeeByName(root, "alexandra") != NULL)
        printf("An employee with the name alexandra exists in the tree\n");
    else
        printf("An employee with the name alexandra doesn't exist in the tree\n");

    updateEmployeeName(root, 123, "Alex");
    printf("\n\nThe employees list after changing Alexandra name:\n");
    printAllEmployees(root);

    updateEmployeeNumber(root, 123, 321);
    printf("\n\nThe employees list after updaing Alex's number:\n");
    printAllEmployees(root);

    removeEmployee(root, 321);
    printf("\n\nThe employees list after removing Alex :\n");
    printAllEmployees(root);

}

