# openCcsds
Open source C code that implements a client-server architecture that uses the CCSDS packet structure to exchange data.

The server part is meant to represent the whole software running in the onboard segment and is designed to be easily integrated into the onboard computer. The client part represents a simple mission control software fit only for the purpose of exercising this software.

# Getting Started

Open a terminal window and do "make runClient"  

Open another terminal window and do "make runServer"  

You should see the two exchanging packets with sequence number and data numbers incrementing. The server inverts the order of the data and sends it back to the client

# Documentation

Inside the docs directory, the file "integration-guide.odt" introduces the architecture and the steps to integrate into an onboard computer and help the user to create its own application.

# License

Apache 2.0 - permissive license, user has full rights to the code, even for commercial purposes as long as he mentions the author of this code and no rights are denied to the original author (obviously).

# Status
work in progress, code base done, documentation is work in progress