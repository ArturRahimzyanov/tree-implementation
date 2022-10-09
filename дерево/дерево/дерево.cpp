#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>;
#include<iostream>;
#include<fstream>;
#include<string>;
#include<string>;
#include <windows.h>;

using namespace std;

struct student* readOfFile(FILE* f, char* strSurname);
struct student* create_el(char* surname, char* name, char* birth, char* group);
struct student* add_el(struct student* root, struct student tmp);
void printTree(struct student* root);
int checkStudent(char* tmpSurname, char* tmpGroup, char* strSurname);

struct student
{
	char surname[30];
	char name[30];
	char birth[30];
	char group[30];
	student* left;
	student* right;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	FILE* f = fopen("7.txt", "r");
	struct student* root;
	char strSurname[30];
	scanf("%s", strSurname);
	root = readOfFile(f, strSurname);
	printTree(root);
	return 0;	
}

struct student* add_el(struct student* root, struct student* tmp) {
	int a, b;
	if (root == NULL) {
		root = tmp;
	}
	else {
		 a = strcmp(tmp->group, root->group);
		 b = strcmp(tmp->surname, root->surname);

		if (a < 0 || ( a == 0 && b < 0 )) {
			root->left = add_el(root->left, tmp);
		}
		else if( a > 0 || (a == 0 && b > 0)) {
			root->right = add_el(root->right, tmp);
		}
	}

	return root;
}

struct student* create_el(char *surname, char *name, char *birth, char *group){
	struct student* tmp = new struct student;
	strcpy(tmp->surname, surname);
	strcpy(tmp->name, name);
	strcpy(tmp->birth, birth);
	strcpy(tmp->group, group);
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

void printTree(struct student* root) {
	if (root->left != NULL )	printTree(root->left);

		cout << root->surname << "  " << root->name << "  " << root->birth << "  " << root->group << endl;

	if (root->right != NULL)	printTree(root->right);
}

int checkStudent(char* tmpSurname, char* tmpGroup, char* strSurname) {
	int flag;
	int length = strlen(strSurname);
	flag = strncmp(tmpSurname, strSurname, length);
	if (flag == 0 && tmpGroup[2] == '4') return 1;
	return 0;
}

struct student* readOfFile(FILE* f, char* strSurname) {
	char tmpSurname[30];
	char tmpName[30];
	char tmpBirth[30];
	char tmpGroup[30];
	int flag = 0;
	struct student* root = NULL;
	struct student* tmp ;

	while (!feof(f)) {
		fscanf(f, "%s %s %s %s", tmpSurname, tmpName, tmpBirth, tmpGroup);

		flag = checkStudent(tmpSurname, tmpGroup, strSurname);

		if (flag == 1) {
			tmp = create_el(tmpSurname, tmpName, tmpBirth, tmpGroup);
			root = add_el(root, tmp);
		}
	}

	return root;
}