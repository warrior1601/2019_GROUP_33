##Temp Instructions 


# After downloading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir build
# enter command> cd build
# Commands need to be tailored to match you version of Visual Studio
# enter command> cmake -G "Visual Studio 15 2017 Win64" ..\model_viewer        or      cmake -G "Visual Studio 16 2019" ..\modelviewer

################ Note that the path for the .bat file below may need changing for your visual studio version ################

# enter command> "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64        or        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
# This sets the PATH for the Visual Studio compiler
# enter command> msbuild model_viewer.sln
# enter command> cd Debug
# The executable files will be located here and can be entered via command prompt as follows
# enter command> model_viewer.exe (or any other classes test code)
