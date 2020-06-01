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

namespace py = pybind11;

void
initException(py::module& m);
void
initUnits(py::module& m);
void
initLinearSpace(py::module& m);
void
initNVector(py::module& m);
void
initBoatVelocityTable(py::module& m);
void
initWorldMap(py::module& m);
void
initGSPState(py::module& m);
void
initGSPStateFactory(py::module& m);
void
initAllGSPOpenList(py::module& m);
void
initGSPCloseList(py::module& m);
void
initGSPNeighborsFinder(py::module& m);
void
initGSPGloablShortestPath(py::module& m);

PYBIND11_MODULE(pytinysea, m)
{
    m.doc() = "tiny_sea python binding"; // optional module docstring
    initException(m);
    initUnits(m);
    initLinearSpace(m);
    initNVector(m);
    initBoatVelocityTable(m);
    initWorldMap(m);

    py::module gsp(m.def_submodule("gsp"));
    initGSPState(gsp);
    initGSPStateFactory(gsp);
    initGSPCloseList(gsp);
    initAllGSPOpenList(gsp);
    initGSPNeighborsFinder(gsp);
    initGSPGloablShortestPath(gsp);
}

