# KoiKoi
KoiKoi (hanafuda card game)

C++ project to recreate the hanafuda card game KoiKoi.

# Motive
My aim is to use this project to learn how to implement SDL from scratch, as well as setup networking for a 2-player game using a server-socket design.
I plan to accomplish this in 3 steps.

## Step 1
Create a working version of KoiKoi as a single, non-networked application (players will share a computer - aka hotseat).
I will follow a MVC deisgn pattern for class relationships. All interactions will be done via the console and std::cout and std::cin/getline.


## Step 2
Take the working app from step 1 and split it into 2 pieces - a client application and a server application.
I will host the server in Azure as an App Service, as that is what I am familiar with.
However, Azure does not appear to support a C++ framework for this service, so I will use Python for the server.
The client application will still be in C++, although it appears most of the server-socket code is mainly C.


## Step 3
Once I have the game working correctly over the network I will implement SDL and likely other libraries to improve the UI and add sound.


## Further work
At this point the next step would be to improve the server code to manage multiple games/connections.
