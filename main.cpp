#include "funciones.hpp"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int main(){
	// Creamos el archivo menu.
	FILE* archMenu = fopen("menu.dat","wb+");
	menu regMenu;

	strcpy(regMenu.nombre,"Bacon Doble");
	regMenu.precio = 3000;
	strcpy(regMenu.descripcion,"Dos medallones de carne+chedar en fetas + bacon + salsa barbacoa.");
	regMenu.idMenu = 1;

	fwrite(&regMenu, sizeof(menu),1,archMenu);

	strcpy(regMenu.nombre,"Bacon Triple");
	regMenu.precio = 3400;
	strcpy(regMenu.descripcion,"Tres medallones de carne+chedar en fetas + bacon + salsa barbacoa.");
	regMenu.idMenu = 2;

	fwrite(&regMenu, sizeof(menu),1,archMenu);

	strcpy(regMenu.nombre,"Cheese Simple");
	regMenu.precio = 2400;
	strcpy(regMenu.descripcion,"Un medallon de carne + chedar en fetas + pan parmesano.");
	regMenu.idMenu = 3;

	fwrite(&regMenu, sizeof(menu),1,archMenu);

	fclose(archMenu);

	// Creamos el archivo de clientes
	FILE* archClientes = fopen("clientes.dat","wb+");
	cliente regCliente;

	strcpy(regCliente.nombre,"Juan");
	strcpy(regCliente.direccion,"Medrano 122");
	regCliente.telefono = 1134568234;
	regCliente.idCliente = 0;

	fwrite(&regCliente, sizeof(cliente),1,archClientes);

	strcpy(regCliente.nombre,"Pedro");
	strcpy(regCliente.direccion,"Mozart 422");
	regCliente.telefono = 1134562634;
	regCliente.idCliente = 1;


	fwrite(&regCliente, sizeof(cliente),1,archClientes);

	strcpy(regCliente.nombre,"Maria");
	strcpy(regCliente.direccion,"Ferrari 372");
	regCliente.telefono = 1134561012;
	regCliente.idCliente = 15;

	fwrite(&regCliente, sizeof(cliente),1,archClientes);

	fclose(archClientes);

	// Creamos el archivo de pedidos
	FILE* archPedidos = fopen("pedidos.dat","wb+");
	pedido regPedido;

	regPedido.idCliente = 0;
	regPedido.idMenu = 2;
	regPedido.cantidad = 5;
	regPedido.idPedido = 0;
	regPedido.completado = true;

	fwrite(&regPedido, sizeof(pedido),1,archPedidos);
	
	regPedido.idCliente = 1;
	regPedido.idMenu = 3;
	regPedido.cantidad = 3;
	regPedido.idPedido = 1;
	regPedido.completado = false;

	fwrite(&regPedido, sizeof(pedido),1,archPedidos);
	
	regPedido.idCliente = 1;
	regPedido.idMenu = 3;
	regPedido.cantidad = 2;
	regPedido.idPedido = 1;
	regPedido.completado = false;

	fwrite(&regPedido, sizeof(pedido),1,archPedidos);
	
	regPedido.idCliente = 15;
	regPedido.idMenu = 3;
	regPedido.cantidad = 1;
	regPedido.idPedido = 2;
	regPedido.completado = true;

	fwrite(&regPedido, sizeof(pedido),1,archPedidos);
	
	regPedido.idCliente = 15;
	regPedido.idMenu = 1;
	regPedido.cantidad = 2;
	regPedido.idPedido = 2;
	regPedido.completado = true;

	fwrite(&regPedido, sizeof(pedido),1,archPedidos);
	
	fclose(archPedidos);

	NodoMenu* listaMenu = NULL;
	NodoCliente* listaClientes = NULL;
	NodoPedido* listaPedidos = NULL;
	NodoPedido* colafte = NULL;
	NodoPedido* colafin = NULL;
	NodoPedido* pila = NULL;
	
	cargarMenu(listaMenu);
	cargarClientes(listaClientes);
	cargarPedidos(listaPedidos, listaMenu, colafte, colafin, pila);
	cargarPedidosCompletados(listaPedidos, pila);
	cargarPedidosPendientes(listaPedidos, colafte, colafin);
	mostrarMenu();
	mostrarClientes();
	mostrarPedidos();

	int opcion;
	do{
		cout << "--------RESTAURANTE--------" << endl;
		cout << "Selecciona una opcion: " << endl;
		cout << "1. Agregar un menu " << endl;
		cout << "2. Modificar un menu " << endl;
		cout << "3. Eliminar un menu " << endl;
		cout << "4. Agregar un Cliente " << endl;
		cout << "5. Actualizar un Cliente " << endl;
		cout << "6. Eliminar un Cliente " << endl;
		cout << "7. Agregar un Pedido " << endl;
		cout << "8. Completar un Pedido " << endl;
		cout << "9. Mostrar Pedidos Pendientes " << endl;
		cout << "10. Mostrar Pedidos Completados " << endl;
		cout << "11. Mostrar Facturacion Total" << endl;
		cout << "12. Mostrar Pedidos Anteriores" << endl;
		cout << "0. Para Salir" << endl;
		cin >> opcion;

		switch (opcion){
			case 0:{
				break;
			}
			case 1:{
				char nombre[50];
				int precio, idMenu;
				char descripcion[500];
				cout << "Ingrese nombre del menu: ";
				cin.ignore();
				cin.getline(nombre,sizeof(nombre));
				cout << "Ingrese precio del menu: ";
				cin >> precio;
				cout << "Ingrese descripcion del menu: ";
				cin.ignore();
				cin.getline(descripcion,sizeof(descripcion));
				cout << "Ingrese ID del menu: ";
				cin >> idMenu;
				agregarMenu(listaMenu, nombre, precio, descripcion, idMenu);
				break;
			}
			case 2:{
				int idMenu;
				char nuevoNombre[50];
				int nuevoPrecio;
				char nuevaDescripcion[500];
				cout << "Ingrese ID del menu a modificar: ";
				cin >> idMenu;
				cout << "Ingrese nuevo nombre del menu: ";
				cin.ignore();
				cin.getline(nuevoNombre,sizeof(nuevoNombre));
				cout << "Ingrese nuevo precio del menu: ";
				cin >> nuevoPrecio;
				cout << "Ingrese nueva descripcion del menu: ";
				cin.ignore();
				cin.getline(nuevaDescripcion,sizeof(nuevaDescripcion));
				modificarMenu(listaMenu, idMenu, nuevoNombre, nuevoPrecio, nuevaDescripcion);
				break;
			}
			case 3:{
				int idMenu;
				cout << "Ingrese ID del menu a eliminar: ";
				cin >> idMenu;
				eliminarMenu(listaMenu, idMenu);
				break;
			}
			case 4:{
				char nombre[50];
				char direccion[500];
				int telefono, idCliente;
				cout << "Ingrese nombre del cliente: ";
				cin.ignore();
				cin.getline(nombre,sizeof(nombre));
				cout << "Ingrese direccion del cliente: ";
				cin.ignore();
				cin.getline(direccion,sizeof(direccion));
				cout << "Ingrese telefono del cliente: ";
				cin >> telefono;
				cout << "Ingrese ID del cliente: ";
				cin >> idCliente;
				agregarCliente(listaClientes, nombre, direccion, telefono, idCliente);
				break;
			}
			case 5:{
				int idCliente, nuevoTelefono;
				char nuevoNombre[50];
				char nuevaDireccion[500];
				cout << "Ingrese ID del cliente a actualizar: ";
				cin >> idCliente;
				cout << "Ingrese nuevo nombre del cliente: ";
				cin.ignore();
				cin.getline(nuevoNombre,sizeof(nuevoNombre));
				cout << "Ingrese nueva direccion del cliente: ";
				cin.ignore();
				cin.getline(nuevaDireccion,sizeof(nuevaDireccion));
				cout << "Ingrese nuevo telefono del cliente: ";
				cin >> nuevoTelefono;
				actualizarCliente(listaClientes, idCliente, nuevoNombre, nuevaDireccion, nuevoTelefono);
				break;
			}
			case 6:{
				int idCliente;
				cout << "Ingrese ID del cliente a eliminar: ";
				cin >> idCliente;
				eliminarCliente(listaClientes, idCliente);
				break;
			}
			case 7:{
				int idPedido, idMenu, cantidad, idCliente;
				int continuar = 1;
				cout << "Ingrese ID del pedido: ";
				cin >> idPedido;
				cout << "Ingrese ID del cliente que hizo el pedido: ";
				cin >> idCliente;
				while(continuar == 1){
					cout << "Ingrese ID del menu: ";
					cin >> idMenu;
					cout << "Ingrese cantidad del pedido: ";
					cin >> cantidad;
	
					agregarPedido(listaPedidos, listaMenu, idMenu, cantidad, idCliente, idPedido, colafte, colafin, pila);
					
					cout << "1. Agregar otro menu al pedido" << endl;
					cout << "0. Terminar pedido" << endl;
					cin >> continuar;
				}
				break;
			}
			case 8:{
				completarPedido(listaPedidos, colafte, colafin, pila);
				break;
			}
			case 9:{
				mostrarPedidosPendientes(colafte);
				break;
			}
			case 10:{
				mostrarPedidosCompletados(pila);
				break;
			}
			case 11:{
				cargarArchivoFacturaTotal(listaPedidos, listaClientes);
				mostrarFacturaTotal();
				break;
			}
			case 12:{
				cargarPedidosAnteriores(listaClientes, pila);
				mostrarPedidosAnteriores(listaClientes);
				break;
			}
		}
	} while (opcion != 0);

	return 0;
}