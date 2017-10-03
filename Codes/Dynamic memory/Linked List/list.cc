#include <iostream>



struct Person {

  
	std::string name;
	int age;

};



void PrintPerson( Person *p) {

	std::cout << p->name << " is " << p->age << " years old.\n";

}



struct Node {

	Person* person;	
        Node* next;

};



struct List {

  struct Node* head;
  struct Node* tail;
  int count;



};



/**

 * Append a person to the end of the list.

 */

void ListAppend(struct List *list,struct Person *person) {

	
	if(list->count==0){

        
        	Node* new_node = new  Node();

	        new_node -> person = person;

		new_node -> next = NULL;

	       	list -> head = new_node;

		list -> tail = new_node;

		list -> count++;

     
	}else{


	 	struct Node* new_node = new Node();

		new_node -> person = person;

		new_node -> next = NULL;

		list->tail -> next = new_node;

		list -> tail = new_node;

		list -> count++;

	}

}

/**

 * Insert a new person at an index.

 */

void ListInsert( List *list, int index, Person *person) {

	Node* new_node = new Node();

	Node* curr = list -> head;

	Node* prox = list -> head;

	for (int i = 0; i < index-1; i++){

		curr = curr -> next;

	}

	for (int i = 0; i < index; i++){

		prox = prox -> next;

	}

	new_node -> person = person;

	new_node -> next = prox;

	curr -> next = new_node;

	list -> count ++;

}

/**

 * Return the person at a certain index.

 */

struct Person*ListGet(struct List *list, int index) {

	Node* curr = list -> head;

	for (int i = 0; i < index; i++){

		curr = curr -> next;

	}

	return curr -> person;

}



/**

 * Remove a certain person from the list by the index. The removed person is

 * returned.

 */

struct Person *ListRemove(struct List *list, int index) {


	Node* curr = list -> head;

	Node* prox = list -> head;

	Node* del = list->head;

	for (int i = 0; i < index-1; i++){

		curr = curr -> next;

	}

	for (int i = 0; i < index+1; i++){

		prox = prox -> next;

	}

	for(int i = 0;i<=index-1;i++){

		del = del->next;

	}


	curr->next = prox; 

	list -> count --;

	return del->person; 

}
/*
 * Print all the people in the list

 */

void ListP(struct List  *list) {



	if (list -> count  == 0){

		std::cerr << " The List is empty\n";

	}else{	

		int x=0;

		struct Person* p = new Person();

		Node* new_node = new Node(); 

		new_node = list->head;

		while(new_node != NULL){

			p =new_node->person;

			std::cerr << "["<<x<<"]: ";

			PrintPerson(p);
	
			new_node=new_node->next;

			x++;

		}

	}

}

/**

 * The global variable list

 */

struct List list;

 

/**

 * Initialize set the init value for the global variable list

 */

void Initialize() {


	list.count = 0;

	list.head = NULL;

	list.tail = NULL;

/**

   * Implement the Initialize function here

   */

}



/**

 * Finalize frees all the memory that is not freed in the list

 */

void Finalize() {

}
void Sort(struct List* list, int opt){

 	int *v = new int [list->count];
	
	Person* person = new Person();

	std::string *name = new std::string [list->count];

	Node *new_node=list-> head; 

	std::string z;

	int y;
	
	switch(opt){

	

		case 1:{

			for (int i = 0; i<list->count; i++){

				name[i] = new_node->person->name;

				v[i] = new_node ->person -> age;

				new_node = new_node -> next;	

			}		


		        for(int i = 0;i < list->count-1;i++){
	
		                for(int j = i+1;j < list->count;j++){

	        	                if ((name[i].compare(name[j])) > 0){

		                        	z = name[j];
	
		                        	name[j] = name[i];
	
		                        	name[i] = z;

	        	               		y = v[j];

						v[j] = v[i];

						v[i] = y;

					 }	

		                }
			}

			new_node = list -> head;

			for (int i = 0; i<list->count; i++){

				new_node->person->name = name[i];

				new_node ->person -> age = v[i];
	
				new_node = new_node -> next;	

			}



		 	break;
	
	}
        case 2:{

        	for( int i=0;i < list->count;i++){

                	v[i] = new_node->person->age;

	                name[i] = new_node->person->name;

        	        new_node = new_node->next;
        	}
	

		for(int j=0;j < list -> count-1;j++){

			for(int i=j+1;i < list -> count;i++){

				if (v[j] > v[i]){
			
			        	y = v[j];

        			        v[j] = v[i];
			
					v[i] = y;
			
					z = name[j];
                        
					name[j] = name[i];
		
					name[i] = z;
        	                }


                	}	

        	}
	
		new_node=list->head;

		for (int i=0; i<list->count; i++){

			new_node->person->age = v[i];

			new_node->person->name = name[i];

			new_node = new_node->next;


		}




		break;
		}
	}
}

int main(){
  // Since the main function is very similar to the main function of lab2, the 

  // main function is implemented for you. Please do not modify the main 

  // function.



  int input;
  

  Initialize();



  while (1) {

    std::cerr << "Main menu:\n\n"

                 "\t1. Append a person\n"

                 "\t2. Find a person\n"

                 "\t3. Remove a person\n"

                 "\t4. Insert a person\n"

                 "\t5. Print the list\n"

                 "\t6. Exit\n"

		 "\t7. Sort list\n";

    std::cin >> input;



    switch (input) {

      case 1: {

        struct Person *p = new Person();

        std::cerr << "Enter the name: ";

        std::cin >> p->name;

        std::cerr << "Enter the age: ";

        std::cin >> p->age;

        ListAppend(&list, p);

        break;

      }

      case 2: {

        int index;

        struct Person *p;

        std::cerr << "Enter the index of the person: ";

        std::cin >> index;

        if (index >= list.count ||  index < 0){

		std::cerr << "ERROR!!! invalid index\n";	

	}else{

		p = ListGet(&list, index);

		if (p != NULL) {

        		PrintPerson(p);

        	}

        }



        break;

      }

      case 3: {

        int index;

        struct Person *p;

        std::cerr << "Enter the index of the person to remove: ";

        std::cin >> index;

         if (index >= list.count || index < 0){

		std::cerr << "ERROR!!! invalid index\n";	

	}else{

		p = ListRemove(&list, index);

      	}

        break;

      }

      case 4: {

        int index;

        struct Person *p = new Person();

        std::cerr << "Enter the index to insert to: ";

        std::cin >> index;

        if (index >= list.count || index < 0){

		std::cerr << "ERROR!!! invalid index\n";	

	}else{ 

		std::cerr << "Enter the name: ";

        	std::cin >> p->name;

        	std::cerr << "Enter the age: ";

        	std::cin >> p->age;

        	ListInsert(&list, index, p);

        }

	break;

      }

      case 5:

        ListP(&list);

        break;

      case 6:

        Finalize();

        return 0;

      case 7:

	 int opt;

	 std::cerr << "pleae enter 1 to sort by name or 2 to sort by age\n";

	 std::cin >> opt;

	 Sort(&list, opt);

	 break;

      default:

        std::cerr << "Unknow input.\n";

        break;

    }  
  }
  Finalize();

  return 0;
    

}
