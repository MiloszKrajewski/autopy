#ifndef __COMPATIBILITY23_H
#define __COMPATIBILITY23_H

#include <Python.h>

#ifndef PyVarObject_HEAD_INIT
    #define PyVarObject_HEAD_INIT(type, size) PyObject_HEAD_INIT(type) size,
#endif

#ifndef Py_TYPE
    #define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)
#endif

#if PY_MAJOR_VERSION >= 3
  #define MOD_INIT_ERROR { return NULL; }
  #define MOD_INIT_SUCCESS(val) { return val; }
  #define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
  #define MOD_DEF(ob, name, methods, doc) { static struct PyModuleDef moduledef = { PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; ob = PyModule_Create(&moduledef); }
  #define MOD_INIT_RETURN(ob) { return ob; }
#else
  #define MOD_INIT_ERROR { return; }
  #define MOD_INIT_SUCCESS(val) { return; }
  #define MOD_INIT(name) void init##name(void)
  #define MOD_DEF(ob, name, methods, doc) { ob = Py_InitModule3(name, methods, doc); }
  #define MOD_INIT_RETURN(ob) { return; }
#endif

#endif // __COMPATIBILITY23_H