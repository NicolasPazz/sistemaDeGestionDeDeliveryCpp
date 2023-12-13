#include "funciones.hpp"
#include <string>
#include <string.h>
#include <iostream>
using namespace std;

NodoPedido *buscar(NodoPedido *listaPedidos, infoPedido v){
	while (listaPedidos != NULL && listaPedidos->info.idPedido != v.idPedido){
		listaPedidos = listaPedidos->sgte;
	}
	return listaPedidos;
}
NodoPedido *insertarOrdenado(NodoPedido *&listaPedidos, infoPedido v){
	NodoPedido *nuevo = new NodoPedido();
	nuevo->info = v;
	nuevo->sgte = NULL;
	NodoPedido *aux = listaPedidos;
	NodoPedido *ant = NULL;
	while (aux != NULL && aux->info.idPedido <= v.idPedido){
		ant = aux;
		aux = aux->sgte;
	}
	if (ant == NULL){
		listaPedidos = nuevo;
	}else{ // entró al while
		ant->sgte = nuevo;
	}
	nuevo->sgte = aux;
	return nuevo;
}
NodoPedido *buscaEInsertaOrdenado(NodoPedido *&listaPedidos, infoPedido v, bool &enc){
	NodoPedido *buscado = buscar(listaPedidos, v);
	if (buscado == NULL){ // no esta
		enc = false;
		v.facturaTotal = 0;
		v.menu = NULL;
		buscado = insertarOrdenado(listaPedidos, v);
	}else{
		enc = true;
	}
	return buscado;
}
NodoMenu *buscar(NodoMenu *listaMenu, infoMenu v){
	while (listaMenu != NULL && listaMenu->info.idMenu != v.idMenu){
		listaMenu = listaMenu->sgte;
	}
	return listaMenu;
}
NodoMenu *insertarOrdenado(NodoMenu *&listaMenu, infoMenu v){
	NodoMenu *nuevo = new NodoMenu();
	nuevo->info = v;
	nuevo->sgte = NULL;
	NodoMenu *aux = listaMenu;
	NodoMenu *ant = NULL;
	while (aux != NULL && aux->info.idMenu <= v.idMenu){
		ant = aux;
		aux = aux->sgte;
	}
	if (ant == NULL){
		listaMenu = nuevo;
	}else{ // entró al while
		ant->sgte = nuevo;
	}
	nuevo->sgte = aux;
	return nuevo;
}
NodoMenu *buscaEInsertaOrdenado(NodoMenu*& listaMenu, infoMenu v, bool& enc){
	NodoMenu* buscado = buscar(listaMenu, v);
	if (buscado == NULL){ // no esta
		enc = false;
		v.cantidad = 0;
		buscado = insertarOrdenado(listaMenu, v);
	}else{
		enc = true;
	}
	return buscado;
}

//Pilas
void push(NodoPedido *&pila, infoPedido v){
	NodoPedido *nuevo = new NodoPedido();
	nuevo->info = v;
	nuevo->sgte = pila;
	pila = nuevo;
}
infoPedido pop(NodoPedido *&pila){
	infoPedido ret = pila->info;
	NodoPedido *aux = pila;
	pila = aux->sgte;
	delete aux;
	return ret;
}

//Colas
void encolar(NodoPedido *&colafte, NodoPedido *&colafin, infoPedido v){
	NodoPedido *nuevo = new NodoPedido();
	nuevo->info = v;
	nuevo->sgte = NULL;
	if (colafte == NULL){
		colafte = nuevo;
	}else{
		colafin->sgte = nuevo;
	}
	colafin = nuevo;
}
infoPedido desencolar(NodoPedido *&colafte, NodoPedido *&colafin){
	infoPedido ret = colafte->info;
	NodoPedido *aux = colafte;
	colafte = colafte->sgte;
	if (colafte == NULL){
		colafin = NULL;
	}
	delete aux;
	return ret;
}


void cargarMenu(NodoMenu*& listaMenu){
	//Agrega archivo menu a la lista de menus
	FILE* archMenu = fopen("menu.dat","rb+");
	menu reg;
	rewind(archMenu);
	fread(&reg, sizeof(menu),1,archMenu);
	while(!feof(archMenu)){
		NodoMenu* nuevoMenu = new NodoMenu();
		strcpy(nuevoMenu->info.nombre,reg.nombre);
		nuevoMenu->info.precio = reg.precio;
		strcpy(nuevoMenu->info.descripcion,reg.descripcion);
		nuevoMenu->info.idMenu = reg.idMenu;
		
		if (listaMenu == NULL) {
			listaMenu = nuevoMenu;
		} else {
			NodoMenu* AUX = listaMenu;
			while (AUX->sgte != NULL) {
				AUX = AUX->sgte;
			}
			AUX->sgte = nuevoMenu;
		}
		fread(&reg, sizeof(menu),1,archMenu);
	}
	fclose(archMenu);
}

void cargarArchivoMenu(NodoMenu* listaMenu){
	FILE* archMenu = fopen("menu.dat","wb+");
	menu reg;
	rewind(archMenu);
	fread(&reg, sizeof(menu),1,archMenu);
	NodoMenu* AUX = listaMenu;
	while(AUX != NULL){
		strcpy(reg.nombre,AUX->info.nombre);
		reg.precio = AUX->info.precio;
		strcpy(reg.descripcion,AUX->info.descripcion);
		reg.idMenu = AUX->info.idMenu;
		fwrite(&reg, sizeof(menu),1,archMenu);
		AUX = AUX->sgte;
	}
	fclose(archMenu);
}

void mostrarMenu() {
	FILE* archMenu = fopen("menu.dat","rb+");
	menu reg;

	rewind(archMenu);
	fread(&reg, sizeof(menu),1,archMenu);

	cout << endl;
	cout << "MENU:" << endl;
	cout<<"nombre"<<" "<<"precio"<<" "<<"descripcion"<<" "<<"idMenu"<<endl;
	
	while(!feof(archMenu)) {
		cout<<reg.nombre<<" "<<reg.precio<<" "<<reg.descripcion<<" "<<reg.idMenu<<endl;
		fread(&reg, sizeof(menu),1,archMenu);
	}
	fclose(archMenu);
	cout << endl;
}

void agregarMenu(NodoMenu*& listaMenu, char nombre[50], int precio, char descripcion[500], int idMenu) {
	NodoMenu* nuevoMenu = new NodoMenu();
	strcpy(nuevoMenu->info.nombre,nombre);
	nuevoMenu->info.precio = precio;
	strcpy(nuevoMenu->info.descripcion,descripcion);
	nuevoMenu->info.idMenu = idMenu;
	nuevoMenu->sgte = NULL;
	//Agrega menu nuevo a la lista de menus
	if (listaMenu == NULL) {
		listaMenu = nuevoMenu;
	} else {
		NodoMenu* AUX = listaMenu;
		while (AUX->sgte != NULL) {
			AUX = AUX->sgte;
		}
		AUX->sgte = nuevoMenu;
	}
	cargarArchivoMenu(listaMenu);
	mostrarMenu();
}

void modificarMenu(NodoMenu* listaMenu, int idMenu, char nuevoNombre[50], int nuevoPrecio, char nuevaDescripcion[500]) {
	NodoMenu* AUX = listaMenu;
	while (AUX != NULL && AUX->info.idMenu != idMenu) {
		AUX = AUX->sgte;
	}

	if (AUX != NULL) {
		//Modifica menu en la lista
		strcpy(AUX->info.nombre,nuevoNombre);
		AUX->info.precio = nuevoPrecio;
		strcpy(AUX->info.descripcion,nuevaDescripcion);
		
		cargarArchivoMenu(listaMenu);
		mostrarMenu();
	} else {
		cout << "Menu no encontrado." << endl;
	}
}

void eliminarMenu(NodoMenu*& listaMenu, int idMenu) {
	NodoMenu* AUX = listaMenu;
	NodoMenu* ant = NULL;

	while (AUX != NULL && AUX->info.idMenu != idMenu) {
		ant = AUX;
		AUX = AUX->sgte;
	}

	if (AUX != NULL) {
		if (ant != NULL) {
			ant->sgte = AUX->sgte;
		} else {
			listaMenu = AUX->sgte;
		}
		delete AUX;
		cout << "Menu eliminado correctamente." << endl;
	} else {
		cout << "Menu no encontrado." << endl;
	}
	cargarArchivoMenu(listaMenu);
	mostrarMenu();	
}

void cargarClientes(NodoCliente*& listaClientes){
	//Agrega archivo clientes a la lista de clientes
	FILE* archClientes = fopen("clientes.dat","rb+");
	cliente reg;
	rewind(archClientes);
	fread(&reg, sizeof(cliente),1,archClientes);
	while(!feof(archClientes)){
		NodoCliente* nuevoCliente = new NodoCliente();
		strcpy(nuevoCliente->info.nombre,reg.nombre);
		strcpy(nuevoCliente->info.direccion,reg.direccion);
		nuevoCliente->info.telefono = reg.telefono;
		nuevoCliente->info.idCliente = reg.idCliente;
		nuevoCliente->info.pedidosAnt = NULL;
		if (listaClientes == NULL) {
			listaClientes = nuevoCliente;
		} else {
			NodoCliente* AUX = listaClientes;
			while (AUX->sgte != NULL) {
				AUX = AUX->sgte;
			}
			AUX->sgte = nuevoCliente;
		}
		fread(&reg, sizeof(cliente),1,archClientes);
	}
	fclose(archClientes);
}

void cargarArchivoClientes(NodoCliente* listaClientes){
	FILE* archClientes = fopen("clientes.dat","wb+");
	cliente reg;
	rewind(archClientes);
	fread(&reg, sizeof(cliente),1,archClientes);
	NodoCliente* AUX = listaClientes;
	while(AUX != NULL){
		strcpy(reg.nombre,AUX->info.nombre);
		strcpy(reg.direccion,AUX->info.direccion);
		reg.telefono = AUX->info.telefono;
		reg.idCliente = AUX->info.idCliente;
		fwrite(&reg, sizeof(cliente),1,archClientes);
		AUX = AUX->sgte;
	}
	fclose(archClientes);
}

void mostrarClientes() {
	FILE* archClientes = fopen("clientes.dat","rb+");
	cliente reg;

	rewind(archClientes);
	fread(&reg, sizeof(cliente),1,archClientes);

	cout << endl;
	cout << "CLIENTES:" << endl;
	cout<<"nombre"<<" "<<"direccion"<<" "<<"telefono"<<" "<<"idCliente"<<endl;

	while(!feof(archClientes)) {
		cout<<reg.nombre<<" "<<reg.direccion<<" "<<reg.telefono<<" "<<reg.idCliente<<endl;
		fread(&reg, sizeof(cliente),1,archClientes);
	}
	fclose(archClientes);
	cout << endl;
}

void agregarCliente(NodoCliente*& listaClientes, char nombre[50], char direccion[500], int telefono, int idCliente) {
	NodoCliente* nuevoCliente = new NodoCliente;
	strcpy(nuevoCliente->info.nombre,nombre);
	strcpy(nuevoCliente->info.direccion,direccion);
	nuevoCliente->info.telefono = telefono;
	nuevoCliente->info.idCliente = idCliente;
	nuevoCliente->info.pedidosAnt = NULL;
	nuevoCliente->sgte = NULL;
	//Agrega cliente nuevo a la lista de clientes
	if (listaClientes == NULL) {
		listaClientes = nuevoCliente;
	} else {
		NodoCliente* AUX = listaClientes;
		while (AUX->sgte != NULL) {
			AUX = AUX->sgte;
		}
		AUX->sgte = nuevoCliente;
	}
	cargarArchivoClientes(listaClientes);
	mostrarClientes();
}

void actualizarCliente(NodoCliente* listaClientes, int idCliente, char nuevoNombre[50], char nuevaDireccion[500], int nuevoTelefono) {
	NodoCliente* AUX = listaClientes;
	while (AUX != NULL && AUX->info.idCliente != idCliente) {
		AUX = AUX->sgte;
	}

	if (AUX != NULL) {
		strcpy(AUX->info.nombre,nuevoNombre);
		strcpy(AUX->info.direccion,nuevaDireccion);
		AUX->info.telefono = nuevoTelefono;
		
		cargarArchivoClientes(listaClientes);
		mostrarClientes();
	} else {
		cout << "Cliente no encontrado." << endl;
	}
}

void eliminarCliente(NodoCliente*& listaClientes, int idCliente) {
	NodoCliente* AUX = listaClientes;
	NodoCliente* ant = NULL;

	while (AUX != NULL && AUX->info.idCliente != idCliente) {
		ant = AUX;
		AUX = AUX->sgte;
	}

	if (AUX != NULL) {
		if (ant != NULL) {
			ant->sgte = AUX->sgte;
		} else {
			listaClientes = AUX->sgte;
		}
		delete AUX;
		cout << "Cliente eliminado correctamente." << endl;
	} else {
		cout << "Cliente no encontrado." << endl;
	}
	cargarArchivoClientes(listaClientes);
	mostrarClientes();
}

void cargarPedidosPendientes(NodoPedido*& listaPedidos, NodoPedido*& colafte, NodoPedido*& colafin){
	colafte = NULL;
	colafin = NULL;
	infoPedido v;
	NodoPedido* AUX = listaPedidos;
	while(AUX != NULL){
		if(!AUX->info.completado){
			v.idCliente = AUX->info.idCliente;
			v.idPedido = AUX->info.idPedido;
			v.facturaTotal = AUX->info.facturaTotal;
			v.menu = AUX->info.menu;
			encolar(colafte, colafin, v);	
		}
		AUX = AUX -> sgte;
	}
}

void cargarPedidosCompletados(NodoPedido*& listaPedidos, NodoPedido*& pila){
	pila = NULL;
	infoPedido v;
	NodoPedido* AUX = listaPedidos;
	while(AUX != NULL){
		if(AUX->info.completado){
			v.idCliente = AUX->info.idCliente;
			v.idPedido = AUX->info.idPedido;
			v.facturaTotal = AUX->info.facturaTotal;
			v.menu = AUX->info.menu;
			push(pila, v);	
		}
		AUX = AUX -> sgte;
	}
}

void cargarPedidos(NodoPedido*& listaPedidos, NodoMenu*& listaMenu, NodoPedido*& colafte, NodoPedido*& colafin, NodoPedido*& pila){
	//Agrega archivo pedidos a la lista de pedidos
	FILE* archPedidos = fopen("pedidos.dat","rb");
	pedido reg;
	rewind(archPedidos);
	fread(&reg, sizeof(pedido),1,archPedidos);
	
	infoPedido ip;
	infoMenu im;
	NodoPedido* pedidoBuscado;
	NodoMenu* menuBuscado;
	bool enc;
	
	while(!feof(archPedidos)){
		ip.idCliente = reg.idCliente;
		ip.idPedido = reg.idPedido;
		ip.completado = reg.completado;

		pedidoBuscado = buscaEInsertaOrdenado(listaPedidos,ip,enc);

		im.idMenu = reg.idMenu;
		im.precio = buscar(listaMenu,im)->info.precio;
		strcpy(im.nombre,buscar(listaMenu,im)->info.nombre);

		menuBuscado = buscaEInsertaOrdenado(pedidoBuscado->info.menu,im,enc);
		menuBuscado->info.cantidad += reg.cantidad;
		pedidoBuscado->info.facturaTotal += (im.precio * reg.cantidad);
			
		fread(&reg, sizeof(pedido),1,archPedidos);
	}
	fclose(archPedidos);
}

void cargarArchivoFacturaTotal(NodoPedido*& listaPedidos, NodoCliente*& listaClientes){
	NodoPedido* AUXP = listaPedidos;
	FILE* archClientesFacturaTotal = fopen("facturaTotal.dat","wb+");
	infoCliente reg;
	rewind(archClientesFacturaTotal);
	fread(&reg, sizeof(infoCliente),1,archClientesFacturaTotal);
	
	while(AUXP != NULL){
		
		NodoCliente* AUXC = listaClientes;
		while(AUXC != NULL && AUXP->info.idCliente != AUXC->info.idCliente){
			AUXC = AUXC->sgte;
		}
		if(AUXC != NULL){
			AUXC->info.facturaTotal += AUXP->info.facturaTotal;
			reg = AUXC->info;
			fwrite(&reg, sizeof(infoCliente),1,archClientesFacturaTotal);
		}
		AUXP = AUXP->sgte;
	}
	
	fclose(archClientesFacturaTotal);
}

void mostrarFacturaTotal(){
	FILE* archClientesFacturaTotal = fopen("facturaTotal.dat","rb+");
	infoCliente reg;

	rewind(archClientesFacturaTotal);
	fread(&reg, sizeof(infoCliente),1,archClientesFacturaTotal);

	cout << endl;
	cout << "Cliente:" << endl;
	cout<< "Nombre " << "ID"<<" "<<"Factura Total"<<" "<<"Telefono"<<" "<<"Direccion"<<endl;
	
	while(!feof(archClientesFacturaTotal)) {
		cout<<reg.nombre<<" "<<reg.idCliente<<" "<<reg.facturaTotal<<" "<<reg.telefono<<" "<<reg.direccion<<endl;
		fread(&reg, sizeof(infoCliente),1,archClientesFacturaTotal);
		cout << "----------------------------------" << endl;
	}
	fclose(archClientesFacturaTotal);
	cout << endl;
}

void cargarArchivoPedidos(NodoPedido* listaPedidos){
	FILE* archPedidos = fopen("pedidos.dat","wb+");
	pedido reg;
	rewind(archPedidos);
	fread(&reg, sizeof(pedido),1,archPedidos);
	NodoPedido* AUX = listaPedidos;
	while(AUX != NULL){
		reg.idCliente = AUX->info.idCliente;
		reg.idPedido = AUX->info.idPedido;
		reg.completado = AUX->info.completado;
		NodoMenu* AUX2 = AUX->info.menu;
		while(AUX2 != NULL){
			reg.idMenu = AUX2->info.idMenu;
			reg.cantidad = AUX2->info.cantidad;
			fwrite(&reg, sizeof(pedido),1,archPedidos);
			AUX2 = AUX2->sgte;
		}
		AUX = AUX->sgte;
	}
	fclose(archPedidos);
}

void mostrarPedidos() {
	FILE* archPedidos = fopen("pedidos.dat","rb+");
	pedido reg;

	rewind(archPedidos);
	fread(&reg, sizeof(pedido),1,archPedidos);

	cout << endl;
	cout << "PEDIDOS:" << endl;
	cout<<"idCliente"<<" "<<"idMenu"<<" "<<"cantidad"<<" "<<"idPedido"<<" "<<"completado"<<endl;

	while(!feof(archPedidos)) {
		cout<<reg.idCliente<<" "<<reg.idMenu<<" "<<reg.cantidad<<" "<<reg.idPedido<<" "<<reg.completado<<endl;
		fread(&reg, sizeof(pedido),1,archPedidos);
	}
	fclose(archPedidos);
	cout << endl;
}

void agregarPedido(NodoPedido*& listaPedidos, NodoMenu* listaMenu, int idMenu, int cantidad, int idCliente, int idPedido, NodoPedido*& colafte, NodoPedido*& colafin, NodoPedido*& pila){
	infoPedido ip;
	infoMenu im;
	NodoPedido* pedidoBuscado;
	NodoMenu* menuBuscado;
	bool enc;
	
	ip.idCliente = idCliente;
	ip.idPedido = idPedido;
	ip.completado = false;
	
	pedidoBuscado = buscaEInsertaOrdenado(listaPedidos,ip,enc);
			
	im.idMenu = idMenu;
	im.cantidad = cantidad;
	im.precio = buscar(listaMenu,im)->info.precio;
	strcpy(im.nombre,buscar(listaMenu,im)->info.nombre);
			
	menuBuscado = buscaEInsertaOrdenado(pedidoBuscado->info.menu,im,enc);
	menuBuscado->info.cantidad += cantidad;
	pedidoBuscado->info.facturaTotal += (im.precio * cantidad);
	
	cargarArchivoPedidos(listaPedidos);
	cargarPedidosCompletados(listaPedidos, pila);
	cargarPedidosPendientes(listaPedidos, colafte, colafin);
}

void completarPedido(NodoPedido*& listaPedidos, NodoPedido*& colafte, NodoPedido*& colafin, NodoPedido*& pila) {
	if (colafte != NULL) {
		int idPedido;
		cout << "ID del pedido a completar: ";
		cin >> idPedido;
		NodoPedido* AUX = listaPedidos;
		while(AUX != NULL && AUX->info.idPedido != idPedido){
			AUX = AUX->sgte;
		}
		if(AUX != NULL){
			AUX->info.completado = true;
			cargarArchivoPedidos(listaPedidos);
			cargarPedidosCompletados(listaPedidos, pila);
			cargarPedidosPendientes(listaPedidos, colafte, colafin);
			cout << "Pedido completado correctamente." << endl;
		}else{
			cout << "El pedido no se encontró." << endl;
		}
	} else {
		cout << "No hay pedidos pendientes para completar." << endl;
	}
}

void mostrarPedidosPendientes(NodoPedido* colafte) {
	if (colafte != NULL) {
		NodoPedido* AUX = colafte;
		while(AUX != NULL){
			cout << "----------------------------------" << endl;
			infoPedido info = AUX->info; 
			cout << "ID Cliente:" << info.idCliente << endl;
			cout << "ID Pedido:" << info.idPedido << endl;
			cout << "Factura Total:" << info.facturaTotal << endl;
			cout << endl;
			NodoMenu* AUX2 = info.menu;
			while(AUX2 != NULL){
				cout << "ID Menu :" << AUX2->info.idMenu << endl;
				cout << "Nombre:" << AUX2->info.nombre << endl;
				cout << "Precio:" << AUX2->info.precio << endl;
				cout << "Cantidad:" << AUX2->info.cantidad << endl;
				AUX2 = AUX2->sgte;
				cout << endl;
			}
			AUX = AUX->sgte;
		}
		cout << "----------------------------------" << endl;
	} else {
		cout << "No hay pedidos pendientes." << endl;
	}
}

void mostrarPedidosCompletados(NodoPedido* pila) {
	NodoPedido* AUX = pila;
	if (AUX != NULL) {
		while(AUX != NULL){
			cout << "----------------------------------" << endl;
			infoPedido info = AUX->info; 
			cout << "ID Cliente:" << info.idCliente << endl;
			cout << "ID Pedido:" << info.idPedido << endl;
			cout << "Factura Total:" << info.facturaTotal << endl;
			cout << endl;
			NodoMenu* AUX2 = info.menu;
			while(AUX2 != NULL){
				cout << "ID Menu :" << AUX2->info.idMenu << endl;
				cout << "Nombre:" << AUX2->info.nombre << endl;
				cout << "Precio:" << AUX2->info.precio << endl;
				cout << "Cantidad:" << AUX2->info.cantidad << endl;
				AUX2 = AUX2->sgte;
				cout << endl;
			}
			//pop(AUX); -> elimina el nodo y pierdo los datos de la pila, no se puede volver a utilizar
			AUX = AUX->sgte;
		}
		cout << "----------------------------------" << endl;
	} else {
		cout << "No hay pedidos completados." << endl;
	}
}

void cargarPedidosAnteriores(NodoCliente* listaClientes,NodoPedido*& pila){
	NodoPedido* AUXP = pila;
	while(AUXP != NULL){
		NodoCliente* AUXC = listaClientes;
		while(AUXC != NULL && AUXP->info.idCliente != AUXC->info.idCliente){
			AUXC = AUXC->sgte;
		}
		if(AUXC != NULL){
			if(AUXC->info.pedidosAnt = NULL){
				AUXC->info.pedidosAnt->info = AUXP->info;
			}else{
				while(AUXC->info.pedidosAnt != NULL){
					AUXC->info.pedidosAnt->sgte;
				}
				AUXC->info.pedidosAnt = AUXP;
			}
		}
		AUXP = AUXP->sgte;
	}
}

void mostrarPedidosAnteriores(NodoCliente* listaClientes){
	NodoCliente* auxC = listaClientes;
	while(auxC != NULL){
		cout << "----------------------------------" << endl;
		cout << "ID Cliente: " << auxC->info.idCliente << endl;
		cout << "Nombre: " << auxC->info.nombre << endl;
		NodoPedido* auxP = auxC->info.pedidosAnt;
		while(auxP != NULL){
			cout << "----------------------------------" << endl;
			cout << "ID Pedido :" << auxP->info.idPedido << endl;
			NodoMenu* auxM = auxP->info.menu;
			while(auxM != NULL){
				cout << "----------------------------------" << endl;
				cout << "ID Menu :" << auxM->info.idMenu << endl;
				cout << "Nombre:" << auxM->info.nombre << endl;
				cout << "Precio:" << auxM->info.precio << endl;
				cout << "Cantidad:" << auxM->info.cantidad << endl;
				auxM = auxM->sgte;
			}
			auxP = auxP->sgte;
			cout << endl;
		}
		auxC = auxC->sgte;
		cout << endl;
		cout << endl;
	}
}





