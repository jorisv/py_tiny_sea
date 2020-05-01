// PyTinySea: TinySea python binding
// Copyright (C) 2019 Joris Vaillant
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// includes
// pybind11
#include <pybind11/pybind11.h>

// tiny_sea
#include <tiny_sea/core/linear_list.h>

namespace py = pybind11;
using namespace tiny_sea;

template<typename Unit, typename Data, typename Interp>
inline auto
stdLinearList(const char* name, py::module& m)
{
    using linear_list = LinearList<Unit, Data, Interp>;
    return py::class_<linear_list>(m, name)
      .def("__getitem__",
           py::overload_cast<Unit>(&linear_list::safeAt, py::const_))
      .def("__getitem__",
           py::overload_cast<std::size_t>(&linear_list::safeAt, py::const_))
      .def("interpolated", &linear_list::safeInterpolated)
      .def("x_space", &linear_list::xSpace)
      .def("values", &linear_list::values);
}

template<typename Unit, typename Data, typename Interp>
inline void
stdLinearListBuilder(const char* name, py::module& m)
{
    using linear_space = LinearSpace<Unit>;
    using linear_list_builder = LinearListBuilder<Unit, Data, Interp>;
    py::class_<linear_list_builder>(m, name)
      .def(py::init<linear_space>())
      .def("__getitem__",
           py::overload_cast<std::size_t>(&linear_list_builder::safeAt))
      .def("build", &linear_list_builder::build);
}

template<typename Unit, typename Data, typename Interp>
inline void
stdLinearListAndBuilder(const char* listName,
                        const char* builderName,
                        py::module& m)
{
    stdLinearList<Unit, Data, Interp>(listName, m);
    stdLinearListBuilder<Unit, Data, Interp>(builderName, m);
}
