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
#include <pybind11/stl.h>

// tiny_sea
#include <tiny_sea/gsp/binary_heap_nu_open_list.h>
#include <tiny_sea/gsp/binary_heap_open_list.h>
#include <tiny_sea/gsp/open_list.h>

namespace py = pybind11;
using namespace tiny_sea;

void
initGSPOpenList(py::module& m)
{
    py::class_<gsp::OpenList>(m, "OpenList")
      .def(py::init<>())
      .def("empty", &gsp::OpenList::empty)
      .def("pop", &gsp::OpenList::pop)
      .def("insert", &gsp::OpenList::insert)
      .def("update", &gsp::OpenList::update)
      .def("nr_update", &gsp::OpenList::nrUpdate)
      .def("store", &gsp::OpenList::store);

    py::class_<gsp::OpenList::Iterator>(m, "OpenListIterator");
}

void
initGSPBinaryHeapOpenList(py::module& m)
{
    py::class_<gsp::BinaryHeapOpenList>(m, "BinaryHeapOpenList")
      .def(py::init<>())
      .def("empty", &gsp::BinaryHeapOpenList::empty)
      .def("pop", &gsp::BinaryHeapOpenList::pop)
      .def("insert", &gsp::BinaryHeapOpenList::insert)
      .def("update", &gsp::BinaryHeapOpenList::update)
      .def("size", &gsp::BinaryHeapOpenList::size)
      .def("nr_update", &gsp::BinaryHeapOpenList::nrUpdate)
      .def("__getitem__", &gsp::BinaryHeapOpenList::at)
      .def("__len__",
           [](const gsp::BinaryHeapOpenList& cl) { return cl.size(); })
      .def(
        "__iter__",
        [](gsp::BinaryHeapOpenList& cl) {
            return py::make_iterator(cl.begin(), cl.end());
        },
        py::keep_alive<0, 1>());

    py::class_<gsp::BinaryHeapOpenList::Iterator>(m,
                                                  "BinaryHeapOpenListIterator");
}

void
initGSPBinaryHeapNUOpenList(py::module& m)
{
    py::class_<gsp::BinaryHeapNUOpenList>(m, "BinaryHeapNUOpenList")
      .def(py::init<>())
      .def("empty", &gsp::BinaryHeapNUOpenList::empty)
      .def("pop", &gsp::BinaryHeapNUOpenList::pop)
      .def("insert", &gsp::BinaryHeapNUOpenList::insert)
      .def("size", &gsp::BinaryHeapNUOpenList::size)
      .def("__len__",
           [](const gsp::BinaryHeapNUOpenList& cl) { return cl.size(); })
      .def(
        "__iter__",
        [](gsp::BinaryHeapNUOpenList& cl) {
            return py::make_iterator(cl.begin(), cl.end());
        },
        py::keep_alive<0, 1>());

    py::class_<gsp::BinaryHeapNUOpenList::Iterator>(
      m, "BinaryHeapNUOpenListIterator");
}

void
initAllGSPOpenList(py::module& m)
{
    initGSPOpenList(m);
    initGSPBinaryHeapOpenList(m);
    initGSPBinaryHeapNUOpenList(m);
}
