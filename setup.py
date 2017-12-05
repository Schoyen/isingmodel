from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import numpy as np
import os


os.environ["CFLAGS"] = "-std=c++11"
os.environ["CFLAGS"] += " -stdlib=libc++"

sourcefiles = [
    "ising_model/sample_ising_model.pyx",
    "src/metropolis_sampling.cpp"
]

include_dirs = [
    "include",
    np.get_include()
]

libraries = ["armadillo"]

extensions = [
    Extension(
        name="sample_ising_model",
        sources=sourcefiles,
        language="c++",
        include_dirs=include_dirs,
        libraries=libraries
    )
]

setup(
    name="Cython C++ Ising",
    version="0.1",
    ext_modules=cythonize(extensions)
)
