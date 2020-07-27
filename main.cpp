/* La explicacion de este programa Ejercicio_colas muestra un programa capaz de manejar componentes de la cola (que en este caso son nombres),el cons-
ta de un menu que permite al usuario elegir opciones como lo es retornar el primer elemento a la cola, el segundo encolar, el tercero eliminar, el cuarto-
determina si la cola no tiene nada en su interior y por ultimo la salida. Es un programa que cumple perfectamente con el principio de robustez indican-
dole al usuario cuando tiene algun error(debe cumplir condiciones antes de iniciar con alguna operacion). A continuacion se inicia con el programa*/
#include <iostream>

//Definimos si estamos en windows o linux para definir funcion d limpiar pantalla
#ifdef WIN32
    #define cls() system("cls");
#else
   #define cls() system("clear");
#endif // WIN32

using namespace std;

//Estructuras
struct Componente
{
    string nombre;
    struct Componente *sig;
};

typedef Componente *Puntero;
//Estructura que se encarga de manejar los componentes (nombres) de la cola
struct Cola
{
    Puntero principio, fin;
};

//Prototipos de funciones
bool menuOpciones(struct Cola *&);
void mostrarPrimerElementoCola(struct Cola *&);
void encolarCola(struct Cola *&);
void sacarCola(struct Cola *&);
bool verificarColaVacia(struct Cola *);
void eliminarMemoriaDinamica(Puntero);


int main()
{
    cout << "Bienvenido al programa manejador de nombres con colas." << endl << endl;

    //Creamos la cola
    struct Cola *cola = new Cola();
    cola ->principio = NULL;
    cola ->fin = NULL;

    cout << "Cola creada correctamente" << endl << endl;

    while(menuOpciones(cola)) {}

    eliminarMemoriaDinamica(cola ->principio);

    return 0;
}


bool menuOpciones(struct Cola *&cola)
{
    /*Función que gestiona el menú principal, retorna true si el usuario oprimio algo deferente de "Salir"*/

    cout << endl << "1) Primero: retorna el elemento que ocupe la primera posición de la cola" << endl;
    cout << "2) Encolar: Introduce un nuevo elemento en la cola" << endl;
    cout << "3) Sacar Cola: eiminar el elemento en la cabeza de la cola" << endl;
    cout << "4) Vacía: determina si una cola no tiene nada en su interior" << endl;
    cout << "5) Salir del programa" << endl;
    cout << endl << "Ingrese el número de la opción correspondiente: ";
    int opcion;
    cin >> opcion;
    //Limpiamos buffer
    cin.ignore();

    //Dependiendo de la opción se llama a la función correspondiente
    switch(opcion)
    {
    case 1:
        mostrarPrimerElementoCola(cola);
        return true;
        break;
    case 2:
        encolarCola(cola);
        return true;
        break;
    case 3:
        sacarCola(cola);
        return true;
        break;
    case 4:
        cls();
        if(verificarColaVacia(cola))
            cout << "La cola está vacía" << endl;
        else
            cout << "La cola NO está vacía" << endl;
        return true;
        break;
    case 5:
        break;
    default:
        cls();
        cout << "Opción invalida, intente nuevamente" << endl;
        return true;
        break;
    }
    return false;
}


void mostrarPrimerElementoCola(struct Cola *&cola)
{
    /*Muestra el primer elemento de la cola*/
    cls();
    if(verificarColaVacia(cola))
        cout << "La cola se encuentra vacía, ingrese algún valor antes de realizar esta operación" << endl;
    else
        cout << "El primer elemento en la cola es: " << cola ->principio ->nombre << endl;
}


void encolarCola(struct Cola *&cola)
{
    /*Función que recibe la cola, le pregunta al usuario un nombre y lo agrega a la cola*/
    cout << "Ingrese el nombre que se agregara a la cola: ";

    string nuevoNombre;
    getline(cin, nuevoNombre);

    //Creamos el nuevo nodo
    Puntero nuevoNodo = new Componente;
    nuevoNodo ->nombre = nuevoNombre;

    nuevoNodo ->sig = NULL;

    //Verificamos si la cola esta vacía, y dependiendo de eso asignamos o no el nuevo elemento como principio
    if(verificarColaVacia(cola))
        cola ->principio = nuevoNodo;
    else
        cola ->fin ->sig = nuevoNodo;

    cola ->fin = nuevoNodo;

    cls();

    cout << "Elemento " << cola ->fin ->nombre << " agregado correctamente" << endl << endl;
}


void sacarCola(struct Cola *&cola)
{
    /*Elimina el elemento frente o cabeza de la cola*/
    cls();
    //Verificamos si la cola se encuentra vacía, en caso de que así sea, se detiene la ejecución de la función
    if(verificarColaVacia(cola) == true)
    {
        cout << "La cola se encuentra vacía, ingrese algún valor antes de realizar esta operación" << endl;
        return;
    }

    Puntero elementoEliminarAux = cola ->principio;

    //Asignamos el nuevo principio/frente a la cola
    cola ->principio = cola ->principio ->sig;

    cout << "Nombre " << elementoEliminarAux ->nombre << " Eliminado correctamente" << endl;

    delete elementoEliminarAux;

}


bool verificarColaVacia(struct Cola *cola)
{
    /*Función que se encarga de verificar si una cola se encuentra vacía o no*/
    return (cola ->principio == NULL)? true:false;
}


void eliminarMemoriaDinamica(Puntero elementoCola)
{
    /*Función que se encarga de eliminar toda la memoría dinámica de la cola, de forma recursiva*/

    //SI la cola esta vacía, no hacemos nada
    if(elementoCola == NULL)
        return;

    if(elementoCola ->sig != NULL)
    {
        eliminarMemoriaDinamica(elementoCola ->sig);
    }

    if(elementoCola != NULL)
        delete elementoCola;

}
