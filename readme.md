## Using VSCode

1. Install C++ Extension Pack
2. Clone the repo in VSCode into a directory of your choice.

	`git clone https://github.com/akshitkaranam/CZ4031_Project1.git`

3. Open the cloned project in VSCode

4. Click on "Build" on the tab on the bottom to build the project.
5. On the task bar, click on the "run and debug" button, and select [(lldb) launch] as your debugger. Take note that only the code in main.cpp is able to run. 

If you have any problems with CMake, you can check out their tutorial page here:
[https://code.visualstudio.com/docs/cpp/CMake-linux
](https://code.visualstudio.com/docs/cpp/CMake-linux)

## Adding new files

After you have created new files, to compile it, please add the relevant file name into addExecutable() in the CMakeLists.txt file. 

Upon re-building the project, the new files should compile as well!