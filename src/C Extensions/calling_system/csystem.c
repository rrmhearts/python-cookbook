/*
This example requires a larger Python module
and can be used through reading 
https://docs.python.org/3/extending/extending.html

*/
#define PY_SSIZE_T_CLEAN

/*
All user-visible symbols defined by 
Python.h have a prefix of Py or PY, 
except those defined in standard header 
files. For convenience, and since they 
are used extensively by the Python 
interpreter, "Python.h" includes a few 
standard header files: <stdio.h>, 
<string.h>, <errno.h>, and <stdlib.h>. 
If the latter header file does not exist 
on your system, it declares the functions 
malloc(), free() and realloc() directly.
*/
#include <Python.h>

static PyObject *SpamError;

static PyObject *
csystem_system(PyObject *self, PyObject *args)
{
    /* 
     * self argument points to the module object for module-level functions; for a method it would point to the object instance.
     * args argument will be a pointer to a Python tuple object containing the arguments
     *
     */
    const char *command;
    int sts;

    // Checks args types and converts to C values
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL; // if fails
    sts = system(command);
    if (sts < 0) { // command fails
        PyErr_SetString(SpamError, "System command failed");
        return NULL;
    }
    // Returns python object from C int
    return PyLong_FromLong(sts);

    // if return void, return None instead
    // Py_INCREF(Py_None);
    // return Py_None;
}

PyMODINIT_FUNC
PyInit_spam(void)
{
    PyObject *m;

    m = PyModule_Create(&csystemmodule);
    if (m == NULL)
        return NULL;

    SpamError = PyErr_NewException("spam.error", NULL, NULL);
    Py_XINCREF(SpamError);
    if (PyModule_AddObject(m, "error", SpamError) < 0) {
        Py_XDECREF(SpamError);
        Py_CLEAR(SpamError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
