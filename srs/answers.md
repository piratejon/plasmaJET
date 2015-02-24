Title Page
==========
Software Requirements Specification for

Super Tic Tac Toe

Version 1.0 approved

Prepared by

  * Jonathan Wesley Stone <jstone25@uco.edu>
  * Logan Glenn Huskins <lhuskins@uco.edu>
  * Thomas Focht <keyboardtyper2@gmail.com>
  * Matthew McHughes <mmchughes@uco.edu>

Department of Computer Science, University of Central Oklahoma

2015-02-11

1. Introduction

  1.1 Purpose and Scope

    This document specifies the design of Super Tic Tac Toe 1.0 ("the project"), Team 5 ("PlasmaJET")'s Spring 2015 CMSC 4283/5283 semester project.
    <Identify the product whose software requirements are specified in this document, including the revision or release number. Describe the scope of the product that is covered by this SRS (what does it do and what does it not do), particularly if this SRS describes only part of the system or a single subsystem.>

  1.2 Definitions, Acronyms, and Abbreviations

    <Describe definitions of all the terms, acronyms and abbreviations used in the document. Special attention should be paid to the clarification of terms and concepts from the domain of application.>

  1.3 References

    * http://www.math.cornell.edu/~mec/2003-2004/graphtheory/tictactoe/howtoplayttt.html
    * Dr. Jicheng Fu's Spring 2015 CMSC 4283/5283 Project Description, <https://github.com/loganhuskins/plasmaJET/blob/master/Project%2BDescription.docx>
    * Super Tic Tac Toe protocol documentation (as yet unreleased)
    * PlasmaJET Super Tic Tac Toe Use Case Diagrams (under development)
    * PlasmaJET Super Tic Tac Toe Sequence Diagrams (under development)
    * PlasmaJET Super Tic Tac Toe Class Diagrams
    * Google Java Style Guide, <https://google-styleguide.googlecode.com/svn/trunk/javaguide.html>
    * usability.gov User Interface Design Basics <http://www.usability.gov/what-and-why/user-interface-design.html>

    <List any other documents or Web addresses to which this SRS refers. These may include user interface style guides, contracts, standards, system requirements specifications, use case documents, or a vision and scope document. Provide enough information so that the reader could access a copy of each reference, including title, author, version number, date, and source or location.>

  1.4 Overview
    
    <Contain an outline of the remainder of the document.>

    See attached diagram.

2. Overall Description

  2.1 Product Functions

    This project provides a Super Tic Tac Toe client that enables an operator to identify another client ("opponent") to connect to and initiate an AI-controlled Super Tic Tac Toe game with. The client displays its current status to the operator as well as the state of the game as it progresses. Once connected, the client handles all protocol interactions with the opposing client until the completion of the round in accordance with Dr. Fu's project description and protocol documentation. The project will also include a player versus client mode in which a local user can play the game against an AI-controlled opponent.

    <Summarize the major features the product contains or the significant functions that it performs or lets the user perform. Details will be provided in Section 3, so only a high level summary  is needed here. Organize the functions to make them understandable to any reader of the SRS. A picture of the major groups of related requirements and how they relate, such as a top level data flow diagram or a use case diagram, is often effective.>

  2.2 User Classes and Characteristics

    The primary user class of the client is the student operator who is a member of Team PlasmaJET. Supervisory faculty members, students from other teams, and other interested parties may also occasionally use the client. By design, the user interactivity with the client is minimal and each of the mentioned individuals will use the client in the exact same way. For design purposes a single user class is identified that effectively meets the needs of all anticipated users.

    <Identify the various user classes that you anticipate will use this product. User classes may be differentiated based on frequency of use, subset of product functions used, technical expertise, security or privilege levels, educational level, or experience. Describe the pertinent characteristics of each user class. Certain requirements may pertain only to certain user classes. Distinguish the favored user classes from those who are less important to satisfy.>

  2.3 Constraints

    Team PlasmaJET will design, develop, test, deploy, operate, and distribute the client in strict accordance with course policies, academic integrity guidelines, community decency standards, and applicable local and federal laws. During normal operation the client may traverse a game state space of upto 9! (362,880) boards in the ordinary 3x3 case and a few more in the tie-breaking Achi case. Modern personal and mobile computer hardware will adequately support the client's performance of all anticipated computations in a timely fashion. Specific timing requirements or more complex gameplay rules may later be introduced, and Team PlasmaJET will meet or exceed all requirements. The client will additionally require hardware and operating environment support to interoperate with opponents via the to-be-determined interconnection protocol. Team PlasmaJET will maintain design documents, source code, and validation protocols and procedures so as to enable responsiveness to changing requirements.

    <Describe any items or issues that will limit the options available to the developers. These might include: corporate or regulatory policies; hardware limitations (timing requirements, memory requirements); interfaces to other applications; specific technologies, tools, and databases to be used; parallel operations; language requirements; communications protocols; security considerations; design conventions or programming standards (for example, if the customerâ€™s organization will be responsible for maintaining the delivered software).>

  2.4 Assumptions and Dependencies

    It is assumed that all external components will operate according to their documented purposes and specifications and that an escalation path exists for any failures to do so which inhibit Team PlasmaJET's ability to capitalize on their utility for the purpose of implementing the client.

    <List any assumed factors (as opposed to known facts) that could affect the requirements stated in the SRS. These could include third-party or commercial components that you plan to use, issues around the development or operating environment, or constraints. The project could be affected if these assumptions are incorrect, are not shared, or change. Also identify any dependencies the project has on external factors, such as software components that you intend to reuse from another project, unless they are already documented elsewhere (for example, in the vision and scope document or the project plan).>

3. Specific Requirements

  <This template illustrates organizing the functional requirements for the system by system features, the major services provided by the system. You may prefer to organize this section by use case, mode of operation, user class, object class, functional hierarchy, or combinations of these, whatever makes the most logical sense for your system.>

  3.1 External Interface Requirements

    3.1.1 User Interfaces

      User interfaces are required to define the opponent connection parameters and display the status and progress of the running game. Specific details of the connection parameters are determined by the chosen protocol. The user interface for connection parameters will enable the specification of connection parameter information at an appropriate level of detail to the underlying protocol (e.g. TCP/IP), for example, an input box labeled "Peer IP address: " and a "Connect" or "Exit" button. The client status will indicate to the user whether the client is negotiating a connection with an opponent, determining its next move, communicating its move to the opponent, waiting for the opponent to issue a move, receiving a move from the opponent, or negotiating a tie-breaking round. The game progress will dynamically update to reflect the current state of the board after each move is registered by the client. A graphical client will display the board graphically, with bitmaps or rendered graphics. A terminal client will display the board using standard printable ASCII characters arranged in visually descriptive ways. In the case of a graphical client, when the user is playing a local game versus an AI, the user will be able to click on individual quadrants to select their move. In the case of the graphical environment, the user will be asked to type their select quadrant (e.g. A1 for the top left coordinate). Screen shots will be included as the product reaches further stages of development.

      <Describe the logical characteristics of each interface between the software product and the users. This may include sample screen images, any GUI standards or product family style guides that are to be followed, screen layout constraints, standard buttons and functions (e.g., help) that will appear on every screen, keyboard shortcuts, error message display standards, and so on. Define the software components for which a user interface is needed. Details of the user interface design should be documented in a separate user interface specification.>

    3.1.2 Hardware Interfaces

      The client software runs in an operating environment that exposes hardware capabilities required by the client in environment standard ways. For example, a desktop or laptop PC running the Microsoft Windows operating system enables a user operating a keyboard, mouse, or touch-sensitive tablet to communicate with the client by passing input events to the program's message loop. The client can graphically feedback to the user with API calls that enable the construction and management of graphical display objects such as windows and dialog boxes that show text, buttons, and graphics. The client requires the operating environment afford the user a way to input opponent connection information (such as a keyboard with numbers and a period to input an IP address, or a virtual keyboard presented on a mobile phone enabling same), and a way for the program to communicate its status and present its game state back to the user, via a graphical display buffer or a textual console buffer.

      <Describe the logical and physical characteristics of each interface between the software product and the hardware components of the system. This may include the supported device types, the nature of the data and control interactions between the software and the hardware, and communication protocols to be used.>

    3.1.3 Software Interfaces

# I'm skipping this since we probably need to have a team conversation first -- wouldn't it be fun to do our project on a microcontroller or FPGA!! (LOGAN - I have an unused raspberry pi we can use)

      <Describe the connections between this product and other specific software components (name and version), including databases, operating systems, tools, libraries, and integrated commercial components. Identify the data items or messages coming into the system and going out and describe the purpose of each. Describe the services needed and the nature of communications. Refer to documents that describe detailed application programming interface protocols. Identify data that will be shared across software components. If the data sharing mechanism must be implemented in a specific way (for example, use of a global data area in a multitasking operating system), specify this as an implementation constraint.>

    3.1.4 Communications Interfaces

      Standard games of User versus AI will be played through a browser server model where the user communicates with the application through a web browser running locally on their machine and the AI is running off of a server hosted at UCO, which will communicate over Hyper Text Transfer Protocol (HTTP). Games of AI versus AI will use a peer-to-peer protocol specified by the group leaders during their first meeting and the document will be updated to reflect any decisions made. 

      <Describe the requirements associated with any communications functions required by this product, including e-mail, web browser, network server communications protocols, electronic forms, and so on. Define any pertinent message formatting. Identify any communication standards that will be used, such as FTP or HTTP. Specify any communication security or encryption issues, data transfer rates, and synchronization mechanisms.>

  3.2 Functional Requirements
    Connects to compatible client
    AI must win or draw
    Real time updates of game status
    Validates opponent moves
    

    <Describe how the transformation of inputs to outputs is achieved. The description is given for each class of functions, and sometimes for each individual function. To a certain extent, this description can be seen as a solution to the user. This component of the requirement specification is the main starting point for the design phase.>

    # I think we should also talk over the design of the program 

    3.2.1 Connects to a Compatible Client

      3.2.1.1 Introduction

        <Describe the purpose of this function and the approaches and techniques used. The introduction should include information to clarify the intent of the function.>

      3.2.1.2 Inputs

        <Describe the functionâ€™s inputs (source, quantities, range of acceptable values and the like).>

        The graphical version of the game will will accept both mouse and keyboard input form the user. When selecting an opponent's IP address in an AI versus AI game, the user will be expected to use a keyboard to input the information. Once the game has begun, no input will be required until the game is complete. At that time, the user will be able to select to either play the same opponent again, enter a new IP address, or quit the game. These inputs will require the use of a mouse or touch screen. In a User versus AI graphical game, the user will be required to select their moves by clicking in the appropriate quadrant on the game board. Once the game is over they once again will use their mouse to select the appropriate action. In the text version of the game, the user will once again be required to use a keyboard to enter the opponents IP address using their keyboard when playing a AI versus AI game. After the conclusion of an AI versus AI game, the user will user their keyboard to select options from a displayed list of actions using their keyboard. When playing a User versus AI game, the user will be expected to use an alpha-numeric keyboard to input their move when prompted. The user will be expected to input values A1-A3, B1-B3, or C1-C3.

      3.2.1.3 Processing

        <A definition of the operations that must be performed, such as checking for acceptable values, reaction to abnormal situations, or a description of algorithms to be used.>

      3.2.1.4 Outputs

        <Describes the outputs (destination, quantities, error messages, and the like).>

    3.2.2 AI Must Win or Draw
      3.2.2.1 Introduction
        In the normal mode of the tic-tac-toe game, under normal starting conditions, the computer decision algorithm does not admit the possibility of defeat. This functional requirement is met in part by program code which implements the best-next-move algorithm on behalf of the computer player, and in part by a proof showing that at any point in the sequence of tic-tac-toe game moves consisting of alternating plays by each player, it is possible for either player to determine a best move which, when supported by subsequent best moves, yields no outcome worse than a draw for that player; effectively showing that this algorithm operates within the constructs of the game rules to guarantee the asserted outcomes. Additionally it is shown that by following this procedure from the very beginning of the game, no state can be entered from which it is impossible to direct the game toward a win or draw from the player whose perspective is considered. It follows that by identifying and choosing from among only the possible moves which precipitate the best possible outcome available at each state, it is not possible for the player to lose, only to win or draw, and that when two players both employ this strategy precisely, the game will always result in a draw.
      3.2.2.2 Inputs
        The input to the best-next-move algorithm consists only of the current board state, under the assumption that it is the current player's turn, and not his opponent.
      3.2.2.3 Processing
        Open spaces on the current board are considered. Each is recursively and dynamically visited and evaluated for the outcomes it can entail. No move which results in a loss need be found if the game is played fairly from the outset.
      3.2.2.4 Outputs
        The output of the method is the position which is the best next move for the player to take to force a win if possible or a draw if not. If a player applies the method from the beginning of the game, no losing move sequence can be found.

    3.2.3 Realtime updates of game status
      3.2.3.1 Introduction
      3.2.3.2 Inputs
      3.2.3.3 Processing
      3.2.3.4 Outputs

    3.2.4 Validate opponent moves
      3.2.3.1 Introduction
      3.2.3.2 Inputs
      3.2.3.3 Processing
      3.2.3.4 Outputs

  3.3 Performance Requirements

    <If there are performance requirements for the product under various circumstances, state them here and explain their rationale, to help the developers understand the intent and make suitable design choices. Specify the timing relationships for real time systems. Make such requirements as specific as possible. You may need to state performance requirements for individual functional requirements or features.>

    When deciding moves on the game board, both the user and the client will have a set time to make a decision before they are forced forfeit. While the client is required to meet the same time standards as the user, due to the small and finite number of moves the system is able to make, the system will be expected to make a decision much faster. It will generally be expected that the system makes any decisions in <1 second, or on a pace that is unnoticeable by the user while playing on a 3x3 board. When determining a winner or a draw, the system is expected to make an equally quick determination. The performance requirements in an AI versus AI game will depend largely on the networking between the two clients. In this situation, the system will be expected to make decisions and determine the winner as quickly as in a player versus AI from when the data reaches the system. It will send the moves out in an additional time-frame of about 1 second, or a time unnoticeable to the observers.

  3.4 Software System Attributes 

      <Particular attention is paid to quality aspects. These requirements must be measurable and verifiable. They must be stated in objective terms.>

    3.4.1 Availability

      <Factors that guarantee a certain level of availability such as restart procedures. In this subsection we may also enlist requirements regarding fault tolerance (with respect to both hardware failures and software failures.>

      The desktop client will be available for player versus AI games as long as the hardware the system is running on is avalable. FOr any demonstration, the system will be running on one of plasmaJET's personal computers. Between the team members, we can promise 95% uptime. With respect to AI vs AI, we can promise 95% uptime for our application, but can make promises about uptime outside of our specific system due to uncontrollable variables.

    3.4.2 Security

      <Requirements regarding unauthorized access and other forms of misuse. Certain cryptographic techniques may be prescribed, and we may put constraints on the communication between different parts of the system.>

      The system will be able to check and prevent a user from performing illegal moves and adjust accordingly for player versus AI games. In AI versus AI games, any outgoing communications will be encrypted using an as-to-be determined public key system. In these games the system will also look for external systems attempting to cheat or alter any game elements.

    3.4.3 Maintainability

      <Requirements to guarantee a certain level of maintainability of the system, such as a maximum allowable coupling between components.>

      The system will have well produced documentation using Java's built-in documentation feature that will come alongside any version of the application. This documentation, along with designing alongside typical Object Oriented patterns and standards, will guarentee maintainability for any future work.

  3.5 Design Constraints

    <Design constraints may result from such things as the prescribed use of certain standards or hardware.>

    3.5.1 Standards Compliance

      Several standards govern different aspects of the project. This design document itself and the design it details adhere to software engineering best practices as described by Dr. Jicheng Fu in course lectures, on Dr. Fu's slide decks and presentation notes, and in the course text, _Object-Oriented Software Engineering using UML, Patterns, and Java (3rd Edition)_. This project's use case diagrams adhere to the UML 2.0 standard. Work done in conjunction with the project is fully compliant with UCO academic integrity standards. Program code written for the project primarily adheres to Google Java Style guide as of March 21, 2014, favoring readability and consistency of style everywhere possible. Additional guidelines determined by team consensus regarding to documentation, testing, and program design patterns are also upheld, with minimal deviations from accepted conventions admitted where noted with an explanation as to why the best practice could not be followed and how the exception better supports the fulfillment of the component's role in meeting the design goal. The user interface and experience conforms to Usability.gov User Interface Design Basics.

      <Which existing standards or regulations must be followed, and what requirements result from these. For example, certain report formats or audit procedures may be prescribed>

    3.5.2 Hardware Limitations

      The project is implemented in Java and will theoretically run anywhere a JVM is available. Centain hardware capabilities must be available to the JVM in order to meet specific design requirements. The user interface requires requires a hardware graphical display capable of rendering bitmap graphics as outlined in the interface design section of this document, as well as hardware input devices enabling the user to participate in the use cases outlined above, including choosing a game mode (AI-vs-AI or player-vs-AI), entering an opponent network address, indicating a move during gameplay, and acknowledging the result of the game at its conclusion. These user actions are facilitated by some combination of input devices such as a hardware keyboard, hardware mouse, virtual keyboard operated by hardware mouse, or hardware touchscreen as pointer enabling operation of a virtual keyboard -- it is these which will be successfully handled by the client.
      In order for the client to successfully participate in AI-vs-AI mode, a TCP/IP network stack and supporting hardware must also be available to the JVM that is running the application code.
      The computer tic-tac-toe algorithm is either CPU-bound or memory-bound and additional hardware architectural constraints must be met to ensure the game is capable of meeting the per-move time limit. Possible decision algorithm implementations include iterating through all possible game states each move, which is CPU-bound, or building a decision tree before the game starts and walking/pruning as the game progresses, which is memory-bound. Specific CPU and memory requirements satisfying these constraints will be determined during development.

Appendix A: Issues List

  < This is a dynamic list of the open requirements issues that remain to be resolved, including TBDs, pending decisions, information that is needed, conflicts awaiting resolution, and the like.>
