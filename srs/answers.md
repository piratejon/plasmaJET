Title Page
==========
Software Requirements Specification for

Super Tic Tac Toe

Version 1.0 approved

Prepared by

  * _hey guys fork this and add your name!_
  * Jonathan Wesley Stone <jstone25@uco.edu>
  * Logan Glenn Huskins <lhuskins@uco.edu>

Department of Computer Science, University of Oklahoma

2015-02-11

1. Introduction

  1.1 Purpose and Scope

    This document specifies the design of Super Tic Tac Toe 1.0 ("the project"), Team 5 ("PlasmaJET")'s Spring 2015 CMSC 4283/5283 semester project.
    <Identify the product whose software requirements are specified in this document, including the revision or release number. Describe the scope of the product that is covered by this SRS (what does it do and what does it not do), particularly if this SRS describes only part of the system or a single subsystem.>

  1.2 Definitions, Acronyms, and Abbreviations

    <Describe definitions of all the terms, acronyms and abbreviations used in the document. Special attention should be paid to the clarification of terms and concepts from the domain of application.>

  1.3 References

    * http://www.math.cornell.edu/~mec/2003-2004/graphtheory/tictactoe/howtoplayttt.html
    * Dr. Jicheng Fu's Spring 2015 CMSC 4283/5283 Project Description <https://github.com/loganhuskins/plasmaJET/blob/master/Project%2BDescription.docx>
    * Super Tic Tac Toe protocol documentation (as yet unreleased)
    * PlasmaJET Super Tic Tac Toe Use Case Diagrams (under development)
    * PlasmaJET Super Tic Tac Toe Sequence Diagrams (under development)
    * PlasmaJET Super Tic Tac Toe Class Diagrams

    <List any other documents or Web addresses to which this SRS refers. These may include user interface style guides, contracts, standards, system requirements specifications, use case documents, or a vision and scope document. Provide enough information so that the reader could access a copy of each reference, including title, author, version number, date, and source or location.>

  1.4 Overview

    <Contain an outline of the remainder of the document.>

2. Overall Description

  2.1 Product Functions

    This project provides a Super Tic Tac Toe client that enables an operator to identify another client ("opponent") to connect to and initiate an AI-controlled Super Tic Tac Toe game with. The client displays its current status to the operator as well as the state of the game as it progresses. Once connected, the client handles all protocol interactions with the opposing client until the completion of the round in accordance with Dr. Fu's project description and protocol documentation.

    <Summarize the major features the product contains or the significant functions that it performs or lets the user perform. Details will be provided in Section 3, so only a high level summary  is needed here. Organize the functions to make them understandable to any reader of the SRS. A picture of the major groups of related requirements and how they relate, such as a top level data flow diagram or a use case diagram, is often effective.>

  2.2 User Classes and Characteristics

    The primary user class of the client is the student operator who is a member of Team PlasmaJET. Supervisory faculty members, students from other teams, and other interested parties may also occasionally use the client. By design, the user interactivity with the client is minimal and each of the mentioned individuals will use the client in the exact same way. For design purposes a single user class is identified that effectively meets the needs of all anticipated users.

    <Identify the various user classes that you anticipate will use this product. User classes may be differentiated based on frequency of use, subset of product functions used, technical expertise, security or privilege levels, educational level, or experience. Describe the pertinent characteristics of each user class. Certain requirements may pertain only to certain user classes. Distinguish the favored user classes from those who are less important to satisfy.>

  2.3 Constraints

    Team PlasmaJET will design, develop, test, deploy, operate, and distribute the client in strict accordance with course policies, academic integrity guidelines, community decency standards, and applicable local and federal laws. During normal operation the client may traverse a game state space of upto 9! (362,880) boards in the ordinary 3x3 case and a few more in the tie-breaking Achi case. Modern personal and mobile computer hardware will adequately support the client's performance of all anticipated computations in a timely fashion. Specific timing requirements or more complex gameplay rules may later be introduced, and Team PlasmaJET will meet or exceed all requirements. The client will additionally require hardware and operating environment support to interoperate with opponents via the to-be-determined interconnection protocol. Team PlasmaJET will maintain design documents, source code, and validation protocols and procedures so as to enable responsivity to changing requirements.

    <Describe any items or issues that will limit the options available to the developers. These might include: corporate or regulatory policies; hardware limitations (timing requirements, memory requirements); interfaces to other applications; specific technologies, tools, and databases to be used; parallel operations; language requirements; communications protocols; security considerations; design conventions or programming standards (for example, if the customerâ€™s organization will be responsible for maintaining the delivered software).>

  2.4 Assumptions and Dependencies

    It is assumed that all external components will operate according to their documented purposes and specifications and that an escalation path exists for any failures to do so which inhibit Team PlasmaJET's ability to capitalize on their utility for the purpose of implementing the client.

    <List any assumed factors (as opposed to known facts) that could affect the requirements stated in the SRS. These could include third-party or commercial components that you plan to use, issues around the development or operating environment, or constraints. The project could be affected if these assumptions are incorrect, are not shared, or change. Also identify any dependencies the project has on external factors, such as software components that you intend to reuse from another project, unless they are already documented elsewhere (for example, in the vision and scope document or the project plan).>

3. Specific Requirements

  <This template illustrates organizing the functional requirements for the system by system features, the major services provided by the system. You may prefer to organize this section by use case, mode of operation, user class, object class, functional hierarchy, or combinations of these, whatever makes the most logical sense for your system.>

  3.1 External Interface Requirements

    3.1.1 User Interfaces

      User interfaces are required to define the opponent connection parameters and display the status and progress of the running game. Specific details of the connection parameters are determined by the chosen protocol. The user interface for connection parameters will enable the specification of connection parameter information at an appropriate level of detail to the underlying protocol (e.g. TCP/IP), for example, an input box labeled "Peer IP address: " and a "Connect" or "Exit" button. The client status will indicate to the user whether the client is negotiating a connection with an opponent, determining its next move, communicating its move to the opponent, waiting for the opponent to issue a move, receiving a move from the opponent, or negotiating a tie-breaking round. The game progress will dynamically update to reflect the current state of the board after each move is registered by the client. A graphical client will display the board graphically, with bitmaps or rendered graphics. A terminal client will display the board using standard printable ASCII characters arranged in visually descriptive ways.

      <Describe the logical characteristics of each interface between the software product and the users. This may include sample screen images, any GUI standards or product family style guides that are to be followed, screen layout constraints, standard buttons and functions (e.g., help) that will appear on every screen, keyboard shortcuts, error message display standards, and so on. Define the software components for which a user interface is needed. Details of the user interface design should be documented in a separate user interface specification.>

    3.1.2 Hardware Interfaces

      The client software runs in an operating environment that exposes hardware capabilities required by the client in environment standard ways. For example, a desktop or laptop PC running the Microsoft Windows operating system enables a user operating a keyboard, mouse, or touch-sensitive tablet to communicate with the client by passing input events to the program's message loop. The client can graphically feedback to the user with API calls that enable the construction and management of graphical display objects such as windows and dialog boxes that show text, buttons, and graphics. The client requires the operating environment afford the user a way to input opponent connection information (such as a keyboard with numbers and a period to input an IP address, or a virtual keyboard presented on a mobile phone enabling same), and a way for the program to communicate its status and present its game state back to the user, via a graphical display buffer or a textual console buffer.

      <Describe the logical and physical characteristics of each interface between the software product and the hardware components of the system. This may include the supported device types, the nature of the data and control interactions between the software and the hardware, and communication protocols to be used.>

    3.1.3 Software Interfaces

# I'm skipping this since we probably need to have a team conversation first -- wouldn't it be fun to do our project on a microcontroller or FPGA!!

      <Describe the connections between this product and other specific software components (name and version), including databases, operating systems, tools, libraries, and integrated commercial components. Identify the data items or messages coming into the system and going out and describe the purpose of each. Describe the services needed and the nature of communications. Refer to documents that describe detailed application programming interface protocols. Identify data that will be shared across software components. If the data sharing mechanism must be implemented in a specific way (for example, use of a global data area in a multitasking operating system), specify this as an implementation constraint.>

    3.1.4 Communications Interfaces

      <Describe the requirements associated with any communications functions required by this product, including e-mail, web browser, network server communications protocols, electronic forms, and so on. Define any pertinent message formatting. Identify any communication standards that will be used, such as FTP or HTTP. Specify any communication security or encryption issues, data transfer rates, and synchronization mechanisms.>

  3.2 Functional Requirements

    <Describe how the transformation of inputs to outputs is achieved. The description is given for each class of functions, and sometimes for each individual function. To a certain extent, this description can be seen as a solution to the user. This component of the requirement specification is the main starting point for the design phase.>

    3.2.1 Functional Requirement 1

      3.2.1.1 Introduction

        <Describe the purpose of this function and the approaches and techniques used. The introduction should include information to clarify the intent of the function.>

      3.2.1.2 Inputs

        <Describe the functionâ€™s inputs (source, quantities, range of acceptable values and the like).>

      3.2.1.3 Processing

        <A definition of the operations that must be performed, such as checking for acceptable values, reaction to abnormal situations, or a description of algorithms to be used.>

      3.2.1.4 Outputs

        <Describes the outputs (destination, quantities, error messages, and the like).>

    3.2.2 Functional Requirement 2

      more stuff!

  3.3 Performance Requirements

    <If there are performance requirements for the product under various circumstances, state them here and explain their rationale, to help the developers understand the intent and make suitable design choices. Specify the timing relationships for real time systems. Make such requirements as specific as possible. You may need to state performance requirements for individual functional requirements or features.>

  3.4 Software System Attributes

      <Particular attention is paid to quality aspects. These requirements must be measurable and verifiable. They must be stated in objective terms.>

    3.4.1 Availability

      <Factors that guarantee a certain level of availability such as restart procedures. In this subsection we may also enlist requirements regarding fault tolerance (with respect to both hardware failures and software failures.>

    3.4.2 Security

      <Requirements regarding unauthorized access and other forms of misuse. Certain cryptographic techniques may be prescribed, and we may put constraints on the communication between different parts of the system.>

    3.4.3 Maintainability

      <Requirements to guarantee a certain level of maintainability of the system, such as a maximum allowable coupling between components.>

  3.5 Design Constraints

    <Design constraints may result from such things as the prescribed use of certain standards or hardware.>

    3.5.1 Standards Compliance

      <Which existing standards or regulations must be followed, and what requirements result from these. For example, certain report formats or audit procedures may be prescribed>

    3.5.2 Hardware Limitations

      <A description of the characteristics of the hardware environment, in as far as they lead to software requirements. An example of this might be the amount of memory available.>

Appendix A: Issues List

  < This is a dynamic list of the open requirements issues that remain to be resolved, including TBDs, pending decisions, information that is needed, conflicts awaiting resolution, and the like.>
