#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>


using namespace std;


class tuition{

public:

struct classInfo
{

	char name[20];  //class name
	char time[20];    //class day and time
	char lectureName[20]; //Lecture name
	int num;		//class capacity
};

//define linked list
struct Node
{
	struct classInfo data;
	struct Node* next;
};

struct Node* list = NULL;  //declare the linked list as a global variable

//Create a header: the header is a structure variable
struct Node* createHead()
{
	//dynamic memory application
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//variable initialization
	headNode->next = NULL;
	return headNode;
};

//Create node: prepare for insertion
// Turn user data into struct variables
struct Node* createNode(struct classInfo data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
};



//Data insertion (header insertion method)
void insertNodeByHead(struct Node* headNode, struct classInfo data)
{
	struct Node* newNode = createNode(data); //create a new node
	newNode->next = headNode->next;  //connect the node
	headNode->next = newNode;
};

//Specify delete (delete elements in the linked list)
//posLeftNode->next=posNode->next;
//free(posNode);
void deleteNodeByName(struct Node* headNode, char* classname)
{
	struct Node* prevNode = headNode;
	struct Node* curNode = headNode->next;
	//Class name is a string, string comparison function
	while (curNode != NULL && strcmp(curNode->data.name, classname))
	{
		prevNode = curNode;
		curNode = prevNode->next;
	}
	//discuss the result of the search
	if (curNode == NULL)
		return;
	else
	{
		cout<<"Delete Successful!\n";
		prevNode->next = curNode->next;
		delete(curNode);
		curNode = NULL;
	}
}

void editNodeByName(struct Node* headNode, char* classname)
{
	struct Node* prevNode = headNode;
	struct Node* curNode = headNode->next;

	while (curNode != NULL && strcmp(curNode->data.name, classname))
	{
		prevNode = curNode;
		curNode = prevNode->next;
	}
	//discuss the result of the search
	if (curNode == NULL)
		return;
	else
	{
		cout<<"Found it!\n";
		prevNode->next = curNode->next;
		delete(curNode);
		curNode = NULL;
	}
}
//Search
struct Node* searchByName(struct Node* headNode, char* className) //sequential search
{
	struct Node* curNode = headNode->next;
	while (curNode != NULL && strcmp(curNode->data.name, className)) //string compare between data.name and class name
	{
		curNode = curNode->next;
	}
	return curNode;
}

// Print Linked-List
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next; //print after headnode
	printf("%-20s %-30s %-20s %5s\n\n","Class Name", "Time table", "Lecture name", "Capacity");

	while (pMove != NULL)
	{
		printf("%-20s %-30s %-20s %5d\n", pMove->data.name, pMove->data.time, pMove->data.lectureName, pMove->data.num );//s string, d integer
		cout<<"----------------------------------------------------------------------------------"<<endl;

		pMove = pMove->next; //print next
	}
}

// Direct file operation
// file write operation
void saveInfoToFile(const char* filename, struct Node* headNode)
{
	FILE* fp = fopen(filename, "w"); // open the file with write
	struct Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		fprintf(fp, "%-20s %-30s %-20s %5d\n", pMove->data.name, pMove->data.time, pMove->data.lectureName, pMove->data.num);//write into the file s string, d integer
		pMove = pMove->next;
	}
	fclose(fp); //close the file
}

//read file
void readInfoFromFile(const char* fileName, struct Node* headNode)
{
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		//Create this file if it doesn't exist
		fp = fopen(fileName, "w+"); // "w+" creating the file if it does not exist
	}
	struct classInfo tempData;
	while (fscanf(fp, "%s\t\t%s%s%d\n", tempData.name, &tempData.time, &tempData.lectureName, &tempData.num) != EOF)//fscanf- read the data from the file  EOF- end of file
	{
		insertNodeByHead(list, tempData); //insert the data into node
	}
	fclose(fp);//close the file
}

//Bubble Sort Function
void bubbleSortList(struct Node* headNode)
{

	for (struct Node* p = headNode->next; p != NULL;  p= p->next)
	{
		for (struct Node* q = headNode->next; q->next != NULL;  q = q->next)
		{
			if (q->data.name[0] > q->next->data.name[0])
			{
				//swap value
				struct classInfo tempData = q->data;
				q->data = q->next->data;
				q->next->data = tempData;

			}
		}
	}
	printList(headNode);

}


//2. Choice
void keyIn()
{
	int userkey = 0;
	struct classInfo tempclass;  ////Generate a temporary variable to store tuition class information
	struct Node* result = NULL;
	cin >> userkey;
	switch (userkey) {
	case 1:
		cout<<" [ Add Class ] \n";
		cout<<"  Enter the Class Name: ";
		scanf("%s", tempclass.name);
		cout<<"  Set the Class Timetable (Time format -> Wed_10.00am-12.00pm): ";
		scanf("%s", &tempclass.time);
		cout<<"  Enter the lecture name: ";
		scanf("%s", &tempclass.lectureName);
		cout<<"  Enter the Class Capacity: ";
		scanf("%d", &tempclass.num);


		insertNodeByHead(list, tempclass);
		saveInfoToFile("classinfo.txt", list);
		cout<<"Add Successful!\n";
		break;

	case 2:
		cout<<" [ Display All Classes ] \n\n";
		printList(list);
		break;
	case 3:
		cout<<" [ Student Enroll Class ] \n\n";
		cout<<"  Enter the Class Name: ";
		scanf("%s", tempclass.name);
		result = searchByName(list,tempclass.name);
		if (result == NULL)
			cout<<"  Not Found! \n";
		else
		{
			if (result->data.num > 0)
			{
				result->data.num--;
				cout<<"  Enroll Successful\n";
				saveInfoToFile("classinfo.txt", list);
			}
			else
			{
				cout<<"  Class is Currently Full! Please Enroll Next-Time.\n";
			}
		}
		break;
	case 4:
		cout<<" [ Student Withdrawn Class ] \n\n";
		cout<< "  Enter the Class Name What Student Want To Withdrawn: ";
		scanf("%s", tempclass.name);
		result = searchByName(list, tempclass.name);
		if (result == NULL)
			cout<<"  Not Found This Class Name in Linked List!\n";
		else
		{
			result->data.num++;
			cout<<"  Withdrawn Successful!\n";
			saveInfoToFile("classinfo.txt", list);
		}
		break;

    case 5:
        cout<<" [ Edit Class Information ] \n\n";
        cout<< "  Enter the Class Name What You Want to Edit: ";
        scanf("%s", tempclass.name);
        result = searchByName(list, tempclass.name);
        if (result == NULL)
		{
			cout<<"  Not Found This Class Name in Linked List!\n";
		}
		else
		{
			printf("\n%-20s %-30s %-20s %5s\n","Class Name", "Time table", "Lecture Name", "Capacity");
			cout<<"----------------------------------------------------------------------------------"<<endl;
			printf("%-20s %-30s %-20s %5d\n\n", result->data.name, result->data.time, result->data.lectureName, result->data.num);
			editNodeByName(list, tempclass.name);
            cout<<" [ Re-Enter the Correct Information Again: ] \n\n";
            cout<<"  Enter the Class Name: ";
            scanf("%s", tempclass.name);
            cout<<"  Enter the Class Timetable: ";
            scanf("%s", &tempclass.time);
            cout<<"  Enter the Lecture Name: ";
            scanf("%s", &tempclass.lectureName);
            cout<<"  Enter the Class Capacity: ";
            scanf("%d", &tempclass.num);
            insertNodeByHead(list, tempclass);
            saveInfoToFile("classinfo.txt", list);


		}
        break;


	case 6:
		cout<<" [ Search Class ] \n\n";
		cout<<"  Enter Class Name :";
		scanf("%s", tempclass.name);
		result = searchByName(list, tempclass.name);
		if (result == NULL)
		{
			cout<<"  Not Found This Class Name in Linked List!\n";
		}
		else
		{
			printf("\n%-20s %-30s %-20s %5s\n","Class Name", "Time table","Lecture Name", "Capacity");
			cout<<"----------------------------------------------------------------------------------"<<endl;
			printf("%-20s %-30s %-20s %5d\n\n", result->data.name, result->data.time, result->data.lectureName, result->data.num);
		}
		break;
	case 7:
		cout<< " [ Sort All Classes ] \n\n";
		bubbleSortList(list);
		break;
	case 8:
		cout<< " [ Delete Class ] \n\n";
		cout<< "  Enter Class Name: ";
		scanf("%s", tempclass.name);
		deleteNodeByName(list, tempclass.name);
		saveInfoToFile("classinfo.txt", list);
		break;
	case 9:
		cout<< " [ Exit ] \n\n";
		cout<< "  Exit Successful! \n";
		system("pause");
		exit(0);   //close whole program
		break;
	default(keyIn()):
		cout<< "  [ error ]\n";
        break;
	}
}


void makeMenu()
{
	cout<< "--------------------------------------------\n";
	cout<< "////////  TUITION CENTRE MANAGEMENT SYSTEM  \n\n";
	cout<< "/////  1. Add Class\n";
	cout<< "/////  2. Display All Classes\n";
	cout<< "/////  3. Student Enroll Class\n";
	cout<< "/////  4. Student Withdrawn Class \n";
	cout<< "/////  5. Edit Class Information \n";
	cout<< "/////  6. Search Class\n";
	cout<< "/////  7. Sort All Classes\n";
	cout<< "/////  8. Delete Class\n";
	cout<< "/////  9. Exit\n";
	cout<< "--------------------------------------------\n";
	cout<< "Please Press(1-9): ";
}
};
