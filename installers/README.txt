# 2019_GROUP_33

#### Design Team :
  * Junaid Afzal
  * Jedidiah Paterson
  * Chanyanis Kulanumphol
  * Chang XING

# Project Overview
The end-state of the project is to read a .txt/.stl file; display it using Qt and VTK libraries; ******** Later revision of this project will include using a 3-D imaging tool to display the .txt file to the user. Overview of what model_viewer is.

# Current Build Status [![Build Status](https://travis-ci.com/warrior1601/2019_GROUP_33.svg?token=xyetJbByAw7qFXmcvGWN&branch=master)](https://travis-ci.com/warrior1601/2019_GROUP_33)
travisCi build status explanation - and thus test code and explain what it tests and for which classes and ctest. exmaples models then some stuff about documentation generation automation

# Documentation
The current, most up-to-date documentation can be found [here](https://warrior1601.github.io/2019_GROUP_33/html). then talk about documentation generation

# Model Viewer Library
  * explanation
  * see readme in model_viewer folder for instructions for compiling with cmake

#### Functions
  * sdsdsdsd
  * sadsadas

# Model Library
  * A Model is a 3-dimenional shape that can be comprised of many smaller shapes referred to as cells.
  * Class Cell further differentiates into smaller sub-classes of tetrahedron, pyramid, hexahedron.
  * Each Cell is defined by it's number of vertices and material. Tetrahedras have 4,  pyramids have 5, and hexahedrals have 6.
  * Each vertex is described as a Vector in this project that has a X-Y-Z coordinate.
  * A material includes it's colour, density and name.
  * This allows the model to be made of many different cells, with each cell having its own dimensions and material type.
  * see readme in model folder for instructions for compiling with cmake

#### Functions
  * Create and edit materials
  * Create and edit vectors
  * Vector functions include - add vectors, subtract vectors, multiply vectors, obtain magnitude of vector, and get distance to another vector
  * Create and edit cells
  * Cell function include - calculating the weight, calculating the volume, calculating the center of gravity of a cell, rotating a cell around an X, Y, or Z axis centered on a vector point
  * Create and edit model
  * Model functions include - calculating the volume of the model, calculating the weight of the model, calculating the center of gravity of the model, calculating the overall dimensions of the model, rotating the entire model around an X, Y, or Z axis centered on a vector point

# Installers
  * explain what they are and how to use them and how they are created
