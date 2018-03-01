from distutils.core import setup, Extension

module1 = Extension('alsavol',
    sources = ['alsavol.c'],
    libraries = ['asound'])

setup (name = 'AlsaVol',
        version = '0.1',
        description = 'Conrol ALSA master channel volume',
        ext_modules = [module1])
