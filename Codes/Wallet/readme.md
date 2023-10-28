A Wallet system implementation in C++ in which user can create an account,transfer money to a different account, can view the summary of the account, add money, withdraw money and exit from the system.

Object oriented design is used for developing the system's architecture and inheritance as well as virtual functions to handle the various functionalities of the system through polymorphic behaviour.

Abstraction is implemented to protect the unintended modification of the data members and system variables such as Account Number, and Balance that serves as the soul of the wallet system.

Two seperate classes are implemented to access the ACCOUNT class that provides the implementation details for various functions that subclasses can override.

