from distutils.core import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "Recomendacao",
        sources=["Cupido.cpp"],
        cxx_std=17,
    ),
]

setup(
    name = "Recomendacao",
    version ="0.0",
    description = "Preciso de uma xícara de café",
    ext_modules = ext_modules,
    cmdclass = {"build_ext": build_ext},
    zip_safe = False,
)