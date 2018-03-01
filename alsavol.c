/*
   Copyright 2018 Eduardo A. Paris Penas

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Python.h>
#include <alsa/asoundlib.h>
#include <alsa/mixer.h>

// General stuff
#define float PYTON_API_VERSION = 3.6

// Module methods
static PyObject * set_master_volume(PyObject *self, PyObject *args)
{
  long min, max, volume;
  snd_mixer_t *handle;
  snd_mixer_selem_id_t *sid;
  const char *card = "default";
  const char *selem_name = "Master";

  if (!PyArg_ParseTuple(args, "l", &volume)) {
    return NULL;
  }

  snd_mixer_open(&handle, 0);
  snd_mixer_attach(handle, card);
  snd_mixer_selem_register(handle, NULL, NULL);
  snd_mixer_load(handle);

  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, 0);
  snd_mixer_selem_id_set_name(sid, selem_name);
  snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

  snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
  snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

  snd_mixer_close(handle);

  return Py_True;
}

// Define a module specific exception
static PyObject *AlsaVolError;

// Module initialization
static PyMethodDef AlsaVolMethods[] = {
  {"set_master_volume", set_master_volume, METH_VARARGS, "Set ALSA master channel volume."},
  {NULL, NULL, 0, NULL}   /* Sentinel */
};

static struct PyModuleDef alsavolmodule = {
  PyModuleDef_HEAD_INIT,
  "alsavol",  /* name of module */
  NULL,       /* module documentation */
  -1,         /* size of the per-interpreter state of the module */
  AlsaVolMethods
};

PyMODINIT_FUNC PyInit_alsavol(void)
{
  PyObject *m;
  m = PyModule_Create2(&alsavolmodule, PYTHON_API_VERSION);
  if (m == NULL) {
    return NULL;
  }

  AlsaVolError = PyErr_NewException("alsavol.error", NULL, NULL);
  Py_INCREF(AlsaVolError);
  PyModule_AddObject(m, "error", AlsaVolError);
  return m;
}
