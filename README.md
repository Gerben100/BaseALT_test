# BaseALT_test
To use this project on your system, you must:
1) Have git and cmake installed (sudo apt-get install git, sudo apt-get install cmake)
2) Have the nlohmann/json library installed (sudo apt-get install nlohmann-devel)
3) Have the libcurl library installed (sudo apt-get install libcurl-devel
)
   
Then you must download this project to your system:
git clone https://github.com/Gerben100/BaseALT_test.git

Then you need to build this project and compile:
cmake PATH_your_project
make (to the project folder)

Now you can run the project executable:
./test_task_main

When you start, you will be asked for the name of the two branches from which you want to get the result.
After the end of the program, the results will be saved to the "Outputs" folder (in the project folder)

To run tests for the library.cpp library:

Have the catch2 library installed (sudo apt-get install catch2-devel)

Then you need to build this project and compile:
cmake PATH_your_project
make (to the project folder)

Now you can run the project test:
./test_task
