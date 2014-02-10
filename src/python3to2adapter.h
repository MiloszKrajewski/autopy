#ifndef __PYTHON2TO3ADAPTER_H
#define __PYTHON2TO3ADAPTER_H

#include <Python.h>

#ifndef PyVarObject_HEAD_INIT
    #define PyVarObject_HEAD_INIT(type, size) PyObject_HEAD_INIT(type) size,
#endif

#ifndef Py_TYPE
    #define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)
#endif

#if PY_MAJOR_VERSION >= 3
	#define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
	#define MOD_DEF(ob, name, methods, doc) { static struct PyModuleDef moduledef = { PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; ob = PyModule_Create(&moduledef); }
	#define MOD_INIT_RETURN(ob) { return ob; }
	#define MOD_INIT_FAIL { return NULL; }
#else
	#define MOD_INIT(name) void init##name(void)
	#define MOD_DEF(ob, name, methods, doc) { ob = Py_InitModule3(name, methods, doc); }
	#define MOD_INIT_RETURN(ob) { return; }
	#define MOD_INIT_FAIL { return; }
#endif

#if PY_MAJOR_VERSION < 3
	#define PyInt_FromLong PyLong_FromLong
#endif

#if PY_MAJOR_VERSION >=3
	#define Py_TPFLAGS_HAVE_ITER 0
#endif

#if PY_MAJOR_VERSION < 3
	#define PyStringU_FromFormat PyString_FromFormat
	#define PyStringU_Check PyString_Check
	#define PyStringB_FromString PyString_FromString
#else
	#define PyStringU_FromFormat PyUnicode_FromFormat
	#define PyStringU_Check PyUnicode_Check
	#define PyStringB_FromString PyBytes_FromString
	#define PyInt_Check PyLong_Check
	#define PyInt_AsUnsignedLongMask PyLong_AsUnsignedLongMask
#endif



#endif // __PYTHON2TO3ADAPTER_H