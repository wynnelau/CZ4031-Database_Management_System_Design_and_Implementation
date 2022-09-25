## Using VSCode

1. Install C++ Extension Pack
2. Clone the repo in VSCode into a directory of your choice.

	`git clone https://github.com/akshitkaranam/CZ4031_Project1.git`

3. Open the cloned project in VSCode

4. Click on "Build" on the tab on the bottom to build the project.
5. On the task bar, click on the "run and debug" button, and select [(lldb) launch] as your debugger. Take note that only the code in main.cpp is able to run. 
6. Output is shown in the debug console.

If you have any problems with CMake, you can check out their tutorial page here:
[https://code.visualstudio.com/docs/cpp/CMake-linux
](https://code.visualstudio.com/docs/cpp/CMake-linux)

## Adding new files

After you have created new files, to compile it, please add the relevant file name into addExecutable() in the CMakeLists.txt file. 

Upon re-building the project, the new files should compile as well!

## Suggested Git workflow

Each new feature should reside in its own branch. When a feature is complete, it gets merged into master via a pull request.

### Creating a new feature branch

```sh
git branch <branch_name>
git checkout <branch_name>
```

When done with development on fthat eature, make sure that your repo is up-to-date.

```sh
git checkout master
git pull
```

Then, rebase your feature branch on master and push.

```sh
git checkout <branch_name>
git rebase master
git push
```

After resolving merge conflicts(if any) submit a pull request on GitHub.

### Submitting a pull request

1. Go to the [repo](github.com/pehweihang/cryspbook) on GitHub.
2. Click on [Pull Requests](github.com/pehweihang/cryspbook/pulls)
3. Click on New pull request.
4. Request a merge to master branch.

Once a pull requested is created, every member checks it to see if there are any part of his code that has been accidentally changed. Once we confirm there are no issue, then the branch is merged with the master branch.
