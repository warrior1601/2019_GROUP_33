# 2019_GROUP_33
 
###### Design Team :
 
  * Junaid Afzal
  * Jedidiah Paterson
  * Chanyanis Kulanumphol
  * Chang XING

###Read carefully
 
   * Intructions for downloading and complining this file are detailed below.
   * When downloading as a zip file or cloning the repository DO NOT rename the files or directories.
   * Renaming files or directories will cause build errors when trying to compile.
   * This project utilizes CMake via the command pomt compile the project.
   * The endstate of the project is to read a .txt document then generate a 3-Dimensional obeject
   * Currently the projects generation is only virtual. All of the Vertices are represened by numerical values for the *X-Y-Z* coordinates
   * Later revision of this project will include using a 3-D imaging tool to display th .txt file to the user.
   
#### Model Explained
   * A Model is a 3-dimenional shape that can be comprised of many smaller shapes refered to as cells. 
   * Class Cells furter differentiates into smaller subclasses of hexahedral, pyramid, and tetrahedral. 
   * Each Cell is defined by the number of vertices they have and of the material they are comprised. Tetrahedras have 4,  pyramids have 5, and hexahedrals have 6. 
   * Each vertice is described as a Vector in this project that has a X-Y-Z coordinate. 
   * A material has describing features that includes Color, Density, and Name.
   * This allows the model to be made of many different cells, each cell having its own dimensions and material type. 

#### Functions
   * The user has the ability to create new and change material types of color, density and name
   * Create new vectors and change vectors
   * Add, subtract, multiply, obtain magnitude of, and get distance to a vector
   * Create new cells 
   * Calculate the weight of each cell
   * Calculate the volume of the cell
   * Calculate the center of the gavity of the cell 
   * Rotate a cell around its X, Y, or Z axis
   * Create new model of the model
   * Calculate the volume of the model
   * Calculate the weight of the model
   * Calculate the center of gravity of the model
   * Calculate the overal dimensions of the model
   * Rotate the entire model around its X, Y, or Z axis


# Important notes about compiling with CMake
##   * MinGW Compiler  
     * 