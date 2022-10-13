//#pragma comment(lib, "Strmiids.lib")
#include <Python.h>
#include <string>
#include <iostream>
#include "MediaPlayer.h"
#include "Functions.h"
using namespace std;

static PyObject* Start(PyObject* self, PyObject* args)
{
	char* objectBuff = NULL;
	char* pathCString = NULL;

	if (!PyArg_ParseTuple(args, "ss", &objectBuff, &pathCString))
	{
		printf("Échec de l'analyse des arguments\n");
		return NULL;
	}
	printf("Ouverture: %s \n", pathCString);

	string pathString = pathCString;
	wstring pathWString = s2ws(pathString);
	LPCWSTR pathLPCWSTR = pathWString.c_str();
	MediaPlayer* mediaPlayer = MediaPlayer::GetInstance();
	mediaPlayer->Start(pathLPCWSTR);
	return Py_BuildValue("i", 0);
}


static PyObject* Play_Pause_video(PyObject* self, PyObject* args)
{
	std::cout << "Play_Pause_video" << endl;
	MediaPlayer* mediaPlayer = MediaPlayer::GetInstance();
	mediaPlayer->Play_Pause_video();
	return Py_BuildValue("i", 0);
}

static PyObject* Accelerate(PyObject* self, PyObject* args)
{
	std::cout << "Accelerate" << endl;
	MediaPlayer* mediaPlayer = MediaPlayer::GetInstance();
	mediaPlayer->Accelerate();
	return Py_BuildValue("i", 0);
}

static PyObject* Repeat(PyObject* self, PyObject* args)
{
	std::cout << "Repeat" << endl;
	MediaPlayer* mediaPlayer = MediaPlayer::GetInstance();
	mediaPlayer->Repeat();
	return Py_BuildValue("i", 0);
}

static PyObject* Quitter(PyObject* self, PyObject* args)
{
	std::cout << "Quitter" << endl;
	MediaPlayer* mediaPlayer = MediaPlayer::GetInstance();
	mediaPlayer->Quitter();
	MediaPlayer::DeleteInstance();
	return Py_BuildValue("i", 0);
}

static PyMethodDef methods[] = {
	{"Play_Pause_video", (PyCFunction)Play_Pause_video, METH_NOARGS,
	"Cette méthode ne prend aucun argument \"0\". Il met  la video en pause ou reprend."},
	{"Repeat", (PyCFunction)Repeat, METH_NOARGS,
	"Cette méthode ne prend aucun argument \"0\". debute de la video ."},
	{"Accelerate", (PyCFunction)Accelerate, METH_NOARGS,
	"Cette méthode ne prend aucun argument \"0\". accelerée la video"},
	{"Quitter", (PyCFunction)Quitter, METH_NOARGS,
	"elle ne prend  \"0\". elle permet de quitter la video"},
	{"Start", (PyCFunction)Start, METH_VARARGS,
	},
	{NULL, NULL, 0, NULL}
};


static PyModuleDef Lab3 =
{
	PyModuleDef_HEAD_INIT,
	"Lab3",
	"NULL",
	0,
	methods
};

PyMODINIT_FUNC PyInit_Lab3(void)
{
	return PyModule_Create(&Lab3);
}




