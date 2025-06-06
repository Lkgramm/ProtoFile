from setuptools import setup, Extension

module = Extension(
    'testplugin',
    sources=['testplugin.c'],
)

setup(
    name='testplugin',
    version='1.0',
    description='C extension to write protobuf messages',
    ext_modules=[module],
)