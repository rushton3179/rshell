-------
rshell
-------

Created by Ryan Rushton U5192657
Copyright (c) 2014 Ryan Rushton U5192657. All rights reserved.

---------------------------------------------------------------


rshell is a shell program with with file redirection, piping
and allows the current working directory(cwd) to be changed.
It will automatically search for programs in the cwd as well as
/bin and /usr/bin.

Note that for the usage instructions "cmnd" means cmnd is
typed into the command line followed by enter/return. Also the
shell takes a maximum of 512 input characters.

-------------
Using rshell
-------------

First to quit rshell just type q followed by enter/return.


Executing Programs
------------------

rshell will execute programs in /bin, /usr/bin and the cwd
without the need for entire path. It will first search in cwd
then in the /bin or /usr/bin depending on the systems environment
settings.

How To
------
"pgrm" executes pgrm. If pgrm is in both /bin and the cwd it will
execute pgrm in /bin.

"./pgrm" executes pgrm in the cwd.

"/bin/pgrm" executes pgrm in /bin. Similarly any program can be
executed by its path.
------


Changing Directory
------------------

The cwd is always displayed in this format

rshell:cwd:>

How To
------
"cd .." moves to a parent directory.

"cd dir1" moves to a directory, dir1, within the current
directory.

"cd dir1/dir2" moves to a directory, dir2, within a
directory, dir1,  of the current directory.

"cd" moves to the home directory of the system.
------


File Redirection
----------------

How To
------
"program < file" redirects a file to the programs input.

"program > file" redirects the programs output to write
to the file.

"program >> file" appends the programs output to the end
 of the file.
------

In each of these cases if the file doesn't exist myshell will
create a new file in the current working directory. The file
name extension must be specified by the user.

Also the redirection operator and the program/file names must
be separated by a whitespace character as given above.


Piping and File Redirection
---------------------------

How To
------
"pgrm1 | pgrm2" redirects or pipes the output from pgrm1 to
the input of pgrm2. These can be chained together for N
programs in the form "pgrm1 | pgrm2 | ect | pgrmN".

"pgrm1 < file | pgrm2" redirects file to the input of pgrm1
which pipes its output to pgrm2.

"pgrm1 | pgrm2 > file" pipes the output of pgrm1 to pgrm2
then redirects pgrm2's output to file.

"pgrm1 < infile | pgrm2 > outfile" combines the two previous
commands.

The previous 3 commands can also be combined with a chain of
N pipes.
------

As before all piping and redirection operators need a
whitespace character either side of them.

Incorrect piping commands will result in errors for a single pipe.
If multiple pipes are used the pipes up to the error will be
executed.

-------
Testing
-------

The testing done for rshell was all manual testing. The following
cases were checked.

-repeated newlines
-programs that don't exist
-piping a large number of programs with/without input and output
 files.
-redirection/piping operators in succession without the
 necessary programs/files


-------------------
Optional Extensions
-------------------

Two optional extensions have been completed. One minor and one
major.

The minor is using environment variables when we change
directories. This is not a particularly hard extension but does
make use of the HOME environment variable. We also used the PATH
variable.

The second is the file redirection and piping. The file
redirection was not particularly hard but I did learn a lot
about the system calls involved in implementing it.

The piping and in particular the recursive piping that is
implemented was the most challenging aspect of the program.
The recursive piping allows a number of piped programs to be
executed with the restriction being the size of the input.
This is limited to 512 characters. The major obstacle was
keeping track of the where the pipes were being passed to
and which ones were open and shut. Originally I tried to
implement this using a for loop but this was not possible as
it restricted the number of pipes I could implement. The
recursive method allowed as many was I could input.
