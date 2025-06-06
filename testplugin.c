#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

// write_proto(filename, key, lat, lon, apps)
static PyObject* write_proto(PyObject* self, PyObject* args) {
    const char* filename;
    const char* key;
    double lat, lon;
    PyObject* apps_list;

    if (!PyArg_ParseTuple(args, "ssddO!", &filename, &key, &lat, &lon, &PyList_Type, &apps_list)) {
        return NULL;
    }

    // Импортируем модуль appsinstalled_pb2
    PyObject* pb_module = PyImport_ImportModule("appsinstalled_pb2");
    if (!pb_module) return NULL;

    // Получаем класс UserApps
    PyObject* userapps_class = PyObject_GetAttrString(pb_module, "UserApps");
    if (!userapps_class) return NULL;

    // Создаем экземпляр UserApps
    PyObject* userapps_obj = PyObject_CallObject(userapps_class, NULL);
    if (!userapps_obj) return NULL;

    // Устанавливаем lat и lon
    PyObject_SetAttrString(userapps_obj, "lat", PyFloat_FromDouble(lat));
    PyObject_SetAttrString(userapps_obj, "lon", PyFloat_FromDouble(lon));

    // Получаем поле apps (repeated)
    PyObject* apps_field = PyObject_GetAttrString(userapps_obj, "apps");
    for (Py_ssize_t i = 0; i < PyList_Size(apps_list); ++i) {
        PyObject* app = PyList_GetItem(apps_list, i);
        PyObject_CallMethod(apps_field, "append", "O", app);
    }

    // Сериализуем через SerializeToString()
    PyObject* serialized = PyObject_CallMethod(userapps_obj, "SerializeToString", NULL);
    if (!serialized) return NULL;

    // Получаем указатель на байты
    char* data;
    Py_ssize_t size;
    if (PyBytes_AsStringAndSize(serialized, &data, &size) < 0) return NULL;

    // Открываем файл и записываем
    FILE* fp = fopen(filename, "ab");  // append binary
    if (!fp) {
        PyErr_SetString(PyExc_IOError, "Cannot open file for writing");
        return NULL;
    }

    fwrite(key, 1, strlen(key), fp);
    fwrite(data, 1, size, fp);
    fclose(fp);

    Py_RETURN_TRUE;
}

static PyMethodDef methods[] = {
    {"write_proto", write_proto, METH_VARARGS, "Serialize and write protobuf to file"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "testplugin",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_testplugin(void) {
    return PyModule_Create(&module);
}
