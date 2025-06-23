# openCcsds
Open source C code that implements a client-server architecture that uses the CCSDS packet structure to exchange data.

The server part is meant to represent the whole software running in the onboard segment and is designed to be easily integrated into the onboard computer. The client part represents a simple mission control software fit only for the purpose of exercising this software.

# Motivation
Pro bono. Through my career I have seen many examples where entities get the long awaited chance to develop software for a space application but do not really have a solid starting point. I decided to change this with this simple, light-weight, user friendly framework that benefits from my 20+ years career. It follows the classic approach of a real-time system, including all the software components needed for the user to start building his own software for an onboard computer/payload: A scheduler/watchdog, a publish/subscribe SW Bus and layered architecture to isolate from specific hardware/computers/operating system. The packets used are in the CCSDS format and the principal of having several applications addressable by their APID is also offered. All this available for free under an extremely permissive Apache 2.0 license.

# Getting Started

Open a terminal window and do "make runClient"  

Open another terminal window and do "make runServer"  

You should see the two exchanging packets with sequence number and data numbers incrementing. The server inverts the order of the data and sends it back to the client

# Documentation

Inside the docs directory, the file "integration-guide.odt" introduces the architecture and the steps to integrate into an onboard computer and help the user to create its own application.

# License

Apache 2.0 - permissive license, user has full rights to the code, even for commercial purposes as long as he mentions the author of this code and no rights are denied to the original author (obviously).

# Status
First release done, only minor improvements are in progress.
