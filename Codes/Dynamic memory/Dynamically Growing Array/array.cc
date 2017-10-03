#include <iostream>

using namespace std;

double *v;
int count = 0; 
int size = 2;
  
void Finalize() {
	cout << "\nBye have a good day...\n\n";
}

void Grow() {
	double *nv;
	nv = new double[size*2];
	
	for (int i = 0; i <= count; i++){
		nv[i] = v[i];
	}
	delete v;
	cout << "\n Vector Grown \n Previous capacity: " << size << "\n New capacity: " << size*2 << endl;
	size = 2 * size;
        v = nv;
}

void Shrink() {
	double *nv;
	nv = new double[size / 2];
	
	for (int i = 0; i <= count; i++){
		nv[i] = v[i];
	}
	delete v;
	cout << "\n Vector Shrunk \n Previous capacity: " << size << "\n New capacity: " << size / 2 << endl;
	size =  size / 2;
        v = nv;
}

void Append(double n) {
	if (count == size-1){
		Grow();
	}	
	v[count] = n;
	count++;
}

void Remove(int index) {
	if (index < count && index >= 0){
		for (int i = index; i < count; i++){ 
			v[i] = v[i+1];
		}
		count--; 
	}else{
		cout << "\nERROR!!! The index is invalid\n"; 
	}
	if (size != 2 && count < size * 0.3){
		Shrink();
	}
}

void Insert(int index, double number) {}

void Print() {
	if (count > 0){
		for (int i = 0;i < count;i++){
			cout << v[i]<<"     ";
		}	
	}else{
		cout << " ERROR!!! Array it's empty\n";
	}
}

void Initialize() {
	int x=0;
	int opt;
	int index;
	double num;
	
	do{
		cout <<"\n  Main Menu: \n\n 1. Print the Array \n\n 2. Append element at the end \n\n 3. Remove one element \n\n 4. Insert one element \n\n 5. Exit \n\n Select an option:"; 
		cin >> opt; 
		if (opt <= 5 && opt>0){

		        switch (opt){
                		case 1: cout << "\n You selected: Print the array\n";
					Print();
					break;
				case 2: cout << "\n You selected: Append element at the end\n";
					cout<< " Please enter the number you whish to append: ";
					cin >> num;
					Append(num);
					break;
                		case 3: cout << "\n You selected: Remove one element \n";
					if (count > 0){
						cout << " Please enter the index of the number you whish to remove(1 to "<<count<<"):";
						cin >> index;
						index -= 1;
						Remove(index);
					}else{
						cout << " ERROR!!! Array it's empty\n";
					}	

					break;
                		case 4: cout << "\n You selected: Insert one element  \n";
		//			Insert();
					break;
                		case 5: cout << "\n You selected: Exit \n";
					x = 1;
					break;
		
        		}	
		}else{
			cout<< "\nERROR!!! option must be from 1 to 5\n please select again ";
		}
	}while (x == 0);

	Finalize();
}

int main() { 
	v = new double (size);
	Initialize();

return 0;
}























