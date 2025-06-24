#include <iostream>
#include <cstring>
using namespace std;

void callMenuList();
void callMenuStack(struct STOCKLIST* aux);

//pila
struct STACK {
	int serialNumber;
	struct STACK *next;
};

//lista
struct STOCKLIST {
	char productName[25];
	struct STOCKLIST *next;
	struct STACK *managementArticle;
};

//puntero raiz de lista 
struct STOCKLIST* principalStockNode = NULL;


void showProductList() {
	struct STOCKLIST* aux = principalStockNode;
	cout << "List of products" << endl;
	for (int i = 0; aux; i++) {
		cout << "Product " << i << " : " << aux->productName << endl;
		aux = aux->next;
	}
	callMenuList();
}

void addProductList() {
	struct STOCKLIST* product = new STOCKLIST; //instanciando el producto a añadir en la lista
	cout << "Name of the product to add: ";
	cin >> product->productName;
	product->next = NULL;
	product->managementArticle = NULL; // Inicializando puntero para poder gestionar puntero raiz de la pila

	if (principalStockNode == NULL) {
		principalStockNode = product;
	}
	else {
		struct STOCKLIST* aux = new STOCKLIST[1]; //variable auxiliar para recorrer la lista
		aux = principalStockNode;
		while (aux->next != NULL) aux = aux->next;
		aux->next = product;
	}
	callMenuList();
}

void selectProductList() {
	//mostrar la lista de productos
	struct STOCKLIST* aux = principalStockNode;
	cout << "List of products" << endl;
	for (int i = 0; aux; i++) {
		cout << "Product " << i << " : " << aux->productName << endl;
		aux = aux->next;
	}

	// solicitar un numero
	int index;
	cout << "Select the product to manage (Type the number)" << endl;
	cin >> index;

	//recorrer la lista para enviar como parametro el producto elegido 
	aux = principalStockNode;
	for (int i = 0; i < index && aux != NULL; i++) {
		aux = aux->next;
	}
	if (aux == NULL) {
		cout << "Invalid product number" << endl;
		callMenuList();
		return;
	}
	//mandar a llamar callMenuStack
	callMenuStack(aux);
}

void showStack(struct STOCKLIST* aux) {
	cout << endl << "Products in stock" << endl;
	cout << endl << aux->productName;

	struct STACK* var;
	var = aux->managementArticle;

	while (var) {
		cout << endl << "Serial number: " << var->serialNumber;
		var = var->next;
	}
	callMenuStack(aux);
}

void addElementStack(struct STOCKLIST* aux) {
	int quantity;
	cout << "How many " << aux->productName << " do you need to add?" << endl;
	cin >> quantity;
	for (int i = 0; i < quantity; i++) {
		struct STACK* unity = new STACK[1];
		unity->serialNumber = rand() % 1000;

		if (aux->managementArticle == NULL) {
			aux->managementArticle = unity;
			unity->next = NULL;
		}
		else {
			unity->next = aux->managementArticle;
			aux->managementArticle = unity;
		}
	}
	callMenuStack(aux);
}

void removeElementStack(struct STOCKLIST* aux) {
	int quantity;
	cout << "How many elements of " << aux->productName << "do you need to remove from stack?" << endl;
	cin >> quantity;

	struct STACK* var = aux->managementArticle;
	for (int i = 0; i < quantity; i++) {
		if (var == NULL) {
			cout << endl << "The stock is empty";
		}
		else {
			aux->managementArticle = aux->managementArticle->next;
			delete var;
			var = aux->managementArticle;
		}
	}
	callMenuStack(aux);
}

void deleteProductList() {

}

void callMenuStack(struct STOCKLIST* aux) {
	int option;
	do {
		cout << endl << endl << "Managing " << aux->productName << endl;
		cout << "1. Show products" << endl;
		cout << "2. Add products " << endl;
		cout << "3. Remove products" << endl;
		cout << "4. Go back and select a different product" << endl;
		cout << "5. Exit" << endl;
		cin >> option;
	} while (option < 0 || option > 5);
	switch (option) {
	case 1:
		showStack(aux);
		break;
	case 2:
		addElementStack(aux);
		break;
	case 3:
		removeElementStack(aux);
		break;
	case 4:
		callMenuList();
		break;
	case 5:
		break;
	}
}

//Menu para la lista de productos
void callMenuList() {
	int option;
	do {
		cout << endl << "Welcome" << endl;
		cout << "Select an option." << endl;
		cout << "1. Show list of products" << endl;
		cout << "2. Add a product" << endl;
		cout << "3. Manage stock of a particular product" << endl;
		cout << "4. Delete a product" << endl;
		cout << "5. Exit" << endl;
		cin >> option;
	} while (option < 1 || option > 5);

	switch (option) {
	case 1: showProductList();
		break;
	case 2: addProductList();
		break;
	case 3: selectProductList();
		break;
	case 4: deleteProductList();
		break;
	case 5: break;
	}
}


int main() {
	callMenuList();
	return 0;
}

