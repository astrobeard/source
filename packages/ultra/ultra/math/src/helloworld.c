
#if 0
#include <Python.h> 

static PyObject *PyHelloWorld(PyObject *self) {

	return Py_BuildValue("s", "Hello World!"); 

} 

static char PyHelloWorld_doc[] = 
	"A simple hello world function."; 

static PyMethodDef PyHelloWorld_funcs[] = {
	{"helloworld", (PyCFunction) PyHelloWorld, METH_NOARGS, PyHelloWorld_doc}; 
	{NULL, NULL, 0, NULL}; 
} 

static void inithelloworld(void) {
	Py_InitModule3("helloworld", PyHelloWorld_funcs, "PyObjects!"); 
}
#endif 
