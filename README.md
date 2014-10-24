![Travis CI status]
(https://travis-ci.org/daniel-kun/omni.svg?branch=master)

![Coverity Scan status]
(https://scan.coverity.com/projects/2559/badge.svg)

# The Omni Programming Language Manifest

This manifest declares goals that The Omni Programming Language wants to reach.
Omni is meant to provide a new way of coding. A way of coding where less time is spent on text editing and more time spent on engineering, designing, defining and changing logic and architecture, assuring quality and documenting.

In short, Omni frees the programmer of unnecessary tasks that the classic way of writing programs in text files imposes on them.

# Goals

## Productivity

Higher productivity and quality for programmers

* Let programmers focus on coding
* Let programmers create higher quality and more robust code, with less effort
* Integrated backlogs and work tasks

## Agility
 
* Make wide-scale code changes *safe*, fast and easy
* Make code easier to refactor
* Make code easier to be statically analysed
* Make code easier to be automatically manipulated

## Quality 
 
* Integrated unit tests
* Integrated test director
* Integrated documentation system

## Technology

* Code is not stored in text files, but in a database
* This enables Omni to present code pieces independent of their physical storage
* Declarative and imperative code model in the same language
* Deterministic Garbage Collector via Automatic Reference Counting
* API to access the code model (for coded refactoring, analysis, metrics, reports, etc.)
* Built-in, compile-time-safe multithreading

# Status quo

Last updated: 24.10.2014

Currently, the code model exists for basic structures such as functions, variables, if/for/while/etc. and can be compiled to binaries on Win32 and Linux.
I am building prototypes for the UI to edit the code model in the branch omni-forge. Nothing fancy, yet.
