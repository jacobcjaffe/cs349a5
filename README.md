Team: Austin Erwin-Martinetti, Jacob Jaffe

Compile main.cpp by secure copying to the Blue server, and then compiling with g++.
You can use the scp to securely copy the .cpp file on Blue (outlined in the line command below):

    scp [insert path to main.cpp]/main.cpp [insert username for blue]@blue.cs.sonoma.edu:[insert desired path on blue]

Then use an SSH connection to move to the path you secure copied the .cpp file onto. Then
compile the .cpp file using g++ using the following command:

    g++ -g main.cpp -o main

Finally, run the code by using the following command format in the directory with the executable:

    ./main [input text file] [output text file]

If there are not 2 command line arguments, the program will exit with -1. The program requires
an input text file and output text file.