#include <string>
#include <string.h>
using namespace std;

struct infoMenu{
	char nombre[50];
	int precio;
	char descripcion[500];
	int idMenu;
	int cantidad;
};
struct NodoMenu{
	infoMenu info;
	NodoMenu* sgte;
};
struct infoPedido{
	int idCliente;
	int facturaTotal;
	bool completado;
	int idPedido;
	NodoMenu* menu;
};
struct NodoPedido{
	infoPedido info;
	NodoPedido* sgte;
};
struct infoCliente{
	char nombre[50];
	char direccion[500];
	int telefono;
	int idCliente;
	int facturaTotal;
	NodoPedido* pedidosAnt;
};
struct NodoCliente{
	infoCliente info;
	NodoCliente* sgte;
};
//Estructuras de archivos
struct menu{
	char nombre[50];
	int precio;
	char descripcion[500]; 
	int idMenu;
};
struct cliente{
	char nombre[50];
	char direccion[500];
	int telefono;
	int idCliente;
	int facturaTotal;
};
struct pedido{
	int idCliente;
	int idMenu;
	int cantidad;
	int idPedido;
	bool completado;
};

#ifndef funciones
#define funciones

NodoPedido *buscar(NodoPedido *listaPedidos, infoPedido v);
NodoPedido *insertarOrdenado(NodoPedido *&listaPedidos, infoPedido v);
NodoPedido *buscaEInsertaOrdenado(NodoPedido *&listaPedidos, infoPedido v, bool &enc);
NodoMenu *buscar(NodoMenu *listaMenu, infoMenu v);
NodoMenu *insertarOrdenado(NodoMenu *&listaMenu, infoMenu v);
NodoMenu *buscaEInsertaOrdenado(NodoMenu *&listaMenu, infoMenu v, bool &enc);

//Pilas
void push(NodoPedido *&pila, infoPedido v);
infoPedido pop(NodoPedido *&pila);

//Colas
void encolar(NodoPedido *&colafte, NodoPedido *&colafin, infoPedido v);
infoPedido desencolar(NodoPedido *&colafte, NodoPedido *&colafin);

void mostrarMenu();
void cargarMenu(NodoMenu*& listaMenu);
void cargarArchivoMenu(NodoMenu* listaMenu);

void agregarMenu(NodoMenu*& listaMenu, char nombre[50], int precio, char descripcion[500], int idMenu);
void modificarMenu(NodoMenu* listaMenu, int idMenu, char nuevoNombre[50], int nuevoPrecio, char nuevaDescripcion[500]);
void eliminarMenu(NodoMenu*& listaMenu, int idMenu);

void mostrarClientes();
void cargarClientes(NodoCliente*& listaClientes);
void cargarArchivoClientes(NodoCliente* listaClientes);

void agregarCliente(NodoCliente*& listaClientes, char nombre[50], char direccion[500], int telefono, int idCliente);
void actualizarCliente(NodoCliente* listaClientes, int idCliente, char nuevoNombre[50], char nuevaDireccion[500], int nuevoTelefono);
void eliminarCliente(NodoCliente*& listaClientes, int idCliente);

void mostrarPedidos();
void cargarPedidosPendientes(NodoPedido*& listaPedidos, NodoPedido*& colafte, NodoPedido*& colafin);
void cargarPedidosCompletados(NodoPedido*& listaPedidos, NodoPedido*& pila);
void cargarPedidos(NodoPedido*& listaPedidos, NodoMenu*& listaMenu, NodoPedido*& colafte, NodoPedido*& colafin, NodoPedido*& pila);
void cargarArchivoFacturaTotal(NodoPedido*& listaPedidos, NodoCliente*& listaClientes);
void cargarArchivoPedidos(NodoPedido* listaPedidos);
void mostrarFacturaTotal();
void cargarPedidosAnteriores(NodoCliente* listaClientes,NodoPedido*& pila);
void mostrarPedidosAnteriores(NodoCliente* listaClientes);

void agregarPedido(NodoPedido*& listaPedidos, NodoMenu* listaMenu, int idMenu, int cantidad, int idCliente, int idPedido, NodoPedido*& colafte, NodoPedido*& colafin, NodoPedido*& pila);
void completarPedido(NodoPedido*& listaPedidos, NodoPedido*& colafte, NodoPedido*& colafin, NodoPedido*& pila);
void mostrarPedidosPendientes(NodoPedido* colafte);
void mostrarPedidosCompletados(NodoPedido* pila);

#endif