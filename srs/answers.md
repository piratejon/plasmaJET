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

    This document specifies the design of Super Tic Tac Toe 1.0 ("the project"), Team 5 ("PlasmaJET")'s Spring 2015 CMSC 4283/5283 semester project.  The System will efficiently perform all requirements found in the project description for Dr. Jicheng Fu's Spring 2015 CMSC 4283/5283 Software Engineering class.  The basic idea is a system that creates a connection to another team's system and performs within protocol a game of Tic Tac Toe with Achi tiebreaker.

  1.2 Definitions, Acronyms, and Abbreviations

    AI - Refers to an artificial intelligence player written into the program. In this system's case, it refers to the system's ability to choose a move with intent to win or draw against a user when there is only one user playing.

  1.3 References

    * http://www.math.cornell.edu/~mec/2003-2004/graphtheory/tictactoe/howtoplayttt.html
    * Dr. Jicheng Fu's Spring 2015 CMSC 4283/5283 Project Description, <https://github.com/loganhuskins/plasmaJET/blob/master/Project%2BDescription.docx>
    * Super Tic Tac Toe protocol documentation (as yet unreleased)
    * PlasmaJET Super Tic Tac Toe Use Case Diagrams (under development)
    * PlasmaJET Super Tic Tac Toe Sequence Diagrams (under development)
    * PlasmaJET Super Tic Tac Toe Class Diagrams
    * Google Java Style Guide, <https://google-styleguide.googlecode.com/svn/trunk/javaguide.html>
    * usability.gov User Interface Design Basics <http://www.usability.gov/what-and-why/user-interface-design.html>

  1.4 Overview
    
    See attached use-case diagram.

2. Overall Description

  2.1 Product Functions

    This project provides a Super Tic Tac Toe client that enables an operator to identify another client ("opponent") to connect to and initiate an AI-controlled Super Tic Tac Toe game with. The client displays its current status to the operator as well as the state of the game as it progresses. Once connected, the client handles all protocol interactions with the opposing client until the completion of the round in accordance with Dr. Fu's project description and protocol documentation. The project will also include a player versus client mode in which a local user can play the game against an AI-controlled opponent.

  2.2 User Classes and Characteristics

    The primary user class of the client is the student operator who is a member of Team PlasmaJET. Supervisory faculty members, students from other teams, and other interested parties may also occasionally use the client. By design, the user interactivity with the client is minimal and each of the mentioned individuals will use the client in the exact same way. For design purposes a single user class is identified that effectively meets the needs of all anticipated users.

  2.3 Constraints

    Team PlasmaJET will design, develop, test, deploy, operate, and distribute the client in strict accordance with course policies, academic integrity guidelines, community decency standards, and applicable local and federal laws. During normal operation the client may traverse a game state space of upto 9! (362,880) boards in the ordinary 3x3 case and a few more in the tie-breaking Achi case. Modern personal hardware will adequately support the client's performance of all anticipated computations in a timely fashion. Specific timing requirements or more complex gameplay rules may later be introduced, and Team PlasmaJET will meet or exceed all requirements. The client will additionally require hardware and operating environment support to interoperate with opponents via the to-be-determined interconnection protocol. Team PlasmaJET will maintain design documents, source code, and validation protocols and procedures so as to enable responsiveness to changing requirements.

  2.4 Assumptions and Dependencies

    It is assumed that all external components will operate according to their documented purposes and specifications and that an escalation path exists for any failures to do so which inhibit Team PlasmaJET's ability to capitalize on their utility for the purpose of implementing the client.

3. Specific Requirements

  3.1 External Interface Requirements

    3.1.1 User Interfaces

      User interfaces are required to define the opponent connection parameters and display the status and progress of the running game. Specific details of the connection parameters are determined by the chosen protocol. The user interface for connection parameters will enable the specification of connection parameter information at an appropriate level of detail to the underlying protocol (e.g. TCP/IP), for example, an input box labeled "Peer IP address: " and a "Connect" or "Exit" button. The client status will indicate to the user whether the client is negotiating a connection with an opponent, determining its next move, communicating its move to the opponent, waiting for the opponent to issue a move, receiving a move from the opponent, or negotiating a tie-breaking round. The game progress will dynamically update to reflect the current state of the board after each move is registered by the client. A graphical client will display the board graphically, with bitmaps or rendered graphics. A terminal client will display the board using standard printable ASCII characters arranged in visually descriptive ways. In the case of a graphical client, when the user is playing a local game versus an AI, the user will be able to click on individual quadrants to select their move. In the case of the graphical environment, the user will be asked to type their select quadrant (e.g. A1 for the top left coordinate). Screen shots will be included as the product reaches further stages of development.

    3.1.2 Hardware Interfaces

      The client software runs in an operating environment that exposes hardware capabilities required by the client in environment standard ways. For example, a desktop or laptop PC running the Microsoft Windows operating system enables a user operating a keyboard, mouse, or touch-sensitive tablet to communicate with the client by passing input events to the program's message loop. The client can graphically feedback to the user with API calls that enable the construction and management of graphical display objects such as windows and dialog boxes that show text, buttons, and graphics. The client requires the operating environment afford the user a way to input opponent connection information (such as a keyboard with numbers and a period to input an IP address, or a virtual keyboard presented on a mobile phone enabling same), and a way for the program to communicate its status and present its game state back to the user, via a graphical display buffer or a textual console buffer.

    3.1.3 Software Interfaces
    
      The Super Tic Tac Toe system will be a Java based desktop application that will connect to all competing systems through protocols proposed by the Software Engineering 4283/5283 protocol committee.  The current proposal is for connections to be made through a known good server.

    3.1.4 Communications Interfaces

      Standard games of User versus AI will be played through a browser server model where the user communicates with the application through a web browser running locally on their machine and the AI is running off of a server hosted at UCO, which will communicate over Hyper Text Transfer Protocol (HTTP). Games of AI versus AI will use a peer-to-peer protocol specified by the group leaders during their first meeting and the document will be updated to reflect any decisions made. 

  3.2 Functional Requirements

    3.2.1 Connects to a Compatible Client

      3.2.1.1 Introduction
      
      The connect function will allow the Super Tic Tac Toe system to connect to all competing systems that also adhere to the protocols put forth by the protocol committee.  

      3.2.1.2 Inputs

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
      
        The system will provide real time updates of the game status through the appropriate user interfaces.  This will include each move being displayed as they are made as well as game over decisions and connection status.
      
      3.2.3.2 Inputs
      
        The System will display moves made by both itself and the opposing system.  As the system makes its own move, it displays the move on the game board.  The system will also accept moves from the opposing system, but will not display the move until it has been properly validated within the system.
      
      3.2.3.3 Processing
      
        The system’s display of its own moves will happen automatically as it will have computed its move prior to deciding the move to make.  Opponent moves however will be inputted and processed through validation insuring that the move is indeed valid.  After moves are completed by either system, a check will be made that a game over decision has not been made.
      
      3.2.3.4 Outputs
      
        System moves will be automatically displayed.  After passing validation, opponent moves will be displayed to the user through the appropriate interface.  If a game over decision is triggered, the system will display the appropriate message to the user.  Loss of connection will also provide proper notification to the user that the connection is no longer available.

    3.2.4 Validate opponent moves
     
      3.2.3.1 Introduction
      
       The system will have a validation function that will check all opponent moves to ensure the move is allowable to the current game.  If the move validates, the system then continues to check to see if a game time decision has been made.  If the move fails validation, the system alerts the opposing system to the failure to accept its last move.
      
      3.2.3.2 Inputs
      
        The system will receive input commands defined by the protocols put forth by the class committee.  
      
      3.2.3.3 Processing
      
        The system will check that the move is both an allowable move as well as that the current move has not already been made.
      
      3.2.3.4 Outputs
      
        After the validation function is performed, the system will update accordingly.  A valid move will produce the move to be displayed as well as the system will be notified of either a game over decision or the go ahead to make its next move.

  3.3 Performance Requirements

    When deciding moves on the game board, both the user and the client will have a set time to make a decision before they are forced forfeit. While the client is required to meet the same time standards as the user, due to the small and finite number of moves the system is able to make, the system will be expected to make a decision much faster. It will generally be expected that the system makes any decisions in <1 second, or on a pace that is unnoticeable by the user while playing on a 3x3 board. When determining a winner or a draw, the system is expected to make an equally quick determination. The performance requirements in an AI versus AI game will depend largely on the networking between the two clients. In this situation, the system will be expected to make decisions and determine the winner as quickly as in a player versus AI from when the data reaches the system. It will send the moves out in an additional time-frame of about 1 second, or a time unnoticeable to the observers.

  3.4 Software System Attributes 

    3.4.1 Availability

      The desktop client will be available for player versus AI games as long as the hardware the system is running on is available. FOr any demonstration, the system will be running on one of plasmaJET's personal computers. Between the team members, we can promise 95% uptime. With respect to AI vs AI, we can promise 95% uptime for our application, but can make promises about uptime outside of our specific system due to uncontrollable variables.

    3.4.2 Security

      The system will be able to check and prevent a user from performing illegal moves and adjust accordingly for player versus AI games. In AI versus AI games, any outgoing communications will be encrypted using an as-to-be determined public key system. In these games the system will also look for external systems attempting to cheat or alter any game elements.

    3.4.3 Maintainability

      The system will have well produced documentation using Java's built-in documentation feature that will come alongside any version of the application. This documentation, along with designing alongside typical Object Oriented patterns and standards, will guarantee maintainability for any future work.

  3.5 Design Constraints

    3.5.1 Standards Compliance

      Several standards govern different aspects of the project. This design document itself and the design it details adhere to software engineering best practices as described by Dr. Jicheng Fu in course lectures, on Dr. Fu's slide decks and presentation notes, and in the course text, _Object-Oriented Software Engineering using UML, Patterns, and Java (3rd Edition)_. This project's use case diagrams adhere to the UML 2.0 standard. Work done in conjunction with the project is fully compliant with UCO academic integrity standards. Program code written for the project primarily adheres to Google Java Style guide as of March 21, 2014, favoring readability and consistency of style everywhere possible. Additional guidelines determined by team consensus regarding to documentation, testing, and program design patterns are also upheld, with minimal deviations from accepted conventions admitted where noted with an explanation as to why the best practice could not be followed and how the exception better supports the fulfillment of the component's role in meeting the design goal. The user interface and experience conforms to Usability.gov User Interface Design Basics.

    3.5.2 Hardware Limitations

      The project is implemented in Java and will theoretically run anywhere a JVM is available. Centain hardware capabilities must be available to the JVM in order to meet specific design requirements. The user interface requires requires a hardware graphical display capable of rendering bitmap graphics as outlined in the interface design section of this document, as well as hardware input devices enabling the user to participate in the use cases outlined above, including choosing a game mode (AI-vs-AI or player-vs-AI), entering an opponent network address, indicating a move during gameplay, and acknowledging the result of the game at its conclusion. These user actions are facilitated by some combination of input devices such as a hardware keyboard, hardware mouse, virtual keyboard operated by hardware mouse, or hardware touchscreen as pointer enabling operation of a virtual keyboard -- it is these which will be successfully handled by the client.
      In order for the client to successfully participate in AI-vs-AI mode, a TCP/IP network stack and supporting hardware must also be available to the JVM that is running the application code.
      The computer tic-tac-toe algorithm is either CPU-bound or memory-bound and additional hardware architectural constraints must be met to ensure the game is capable of meeting the per-move time limit. Possible decision algorithm implementations include iterating through all possible game states each move, which is CPU-bound, or building a decision tree before the game starts and walking/pruning as the game progresses, which is memory-bound. Specific CPU and memory requirements satisfying these constraints will be determined during development.

Appendix A: Issues List

  < This is a dynamic list of the open requirements issues that remain to be resolved, including TBDs, pending decisions, information that is needed, conflicts awaiting resolution, and the like.>
  * Our user-facing use cases should be compatible, with minimal modifications, with whatever protocol is decided upon by the protocol design team. However the specific protocol implementation details are as-yet-unknown and these may require unanticipated adjustments.
