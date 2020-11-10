# Terminal Overview

In this lab, you are going to perform a few terminal commands to get familiar with the Unix Environment along with some other standard tools used throughout this course (and that you will use in your career!).

## The Lab files

1. Make sure you have accepted the invitation to the Lab assignment from Piazza. You have to do this for every lab as each lab is a separate repo.
2. Run through the following github tutorial if you are not familiar with git.
  - https://guides.github.com/introduction/git-handbook/
  - This is worth the 15 minutes it takes to avoid headaches later on!
  - Video guides if needed: https://www.youtube.com/githubguides

## SSH

**I don't care what operating system you use locally as long as you have a terminal and internet access**

### ssh clients for each operating system

* For Windows Users installing Putty is sufficient. (https://www.putty.org/)
  * The best option is to install the bash shell from the Windows Store. (https://docs.microsoft.com/en-us/windows/wsl/install-win10)
* For Linux/Mac users, you already have a terminal available! Just search for 'terminal'.
* We additionally will install a virtual machine which you may work from, and which has a terminal.

### ssh'ing
* Once your terminal is open, 'ssh' into Khoury with: `ssh khoury_user_name_here@login.khoury.neu.edu`
  * If for some reason you do not have a Khoury username, [follow these instructions](https://www.khoury.northeastern.edu/systems/getting-started/)
* After you have successfully ssh'd, you are now running programs on the Khoury servers (i.e. not locally on your machine).


## Retrieving your repo (i.e. cloning your repository)

When you have successfully ssh'd into your repository, you should download a copy of your repository on the Khoury servers. The rough workflow for using git is the following.

1. Run `git clone your_repository_url` to establish a git repository on your system. *your_repository_url* is found by clicking the 'green' button on you Monorepo homepage(move one directory up from this folder).

	i. It should look something like `https://github.com/CourseName/Monorepo-yourname.git`
	
2. When you make a change to a file within this directory you can see what is different by:

	i. run `git status` to see what you have changed locally on your computer. Changes you have made locally have not yet been saved to github's servers. 

3. When you are happy with your changes do `git add whatever_file.c` which prepares that specific file to be added to the master. [[git add documentation](https://git-scm.com/docs/git-add)]

4. Next, you will do `git commit -m "some informative message about your changes"` to record changes in your repository [[git-commit documentation](https://git-scm.com/docs/git-commit)]

5. Finally, do a `git push` to actually make things happen--meaning everything you have added will go to the github server. You can check your github.com repository to see exactly what I will see. [[git push documentation](https://git-scm.com/docs/git-push)]


## Task 1 - The (at least) 10 Commands

Try running the following commands (See deliverables section at the end for copying and pasting to [output.txt](./output.txt)).

1. [ls](http://man7.org/linux/man-pages/man1/ls.1.html) - lists the files and folders in the current directory.
2. [mkdir](http://man7.org/linux/man-pages/man2/mkdir.2.html) - Create a new directory
3. [cd](http://man7.org/linux/man-pages/man1/cd.1p.html) - Change directory
4. [man](http://man7.org/linux/man-pages/man1/man.1.html) - Manual pages
5. [rmdir](http://man7.org/linux/man-pages/man2/rmdir.2.html) - Removes an empty directory
6. [sort](http://man7.org/linux/man-pages/man1/sort.1.html) - Sorts information
7. [cat](http://man7.org/linux/man-pages/man1/cat.1.html) - Concatenates files and prints them to standard output
8. [nl](http://man7.org/linux/man-pages/man1/nl.1.html) - Outputs a file with number of lines
9. [cut](http://man7.org/linux/man-pages/man1/cut.1.html) - Remove sections from each file
10. [grep](http://man7.org/linux/man-pages/man1/grep.1.html) - Prints lines that match a pattern.

*Note from instructor:* I included urls to the commands above, but it will almost always be faster for you to search the man pages within your terminal (and if you do not have terminal access, you will want to use the manual pages anyway).

_Hidden easter egg task:_ By default when you ssh into login servers, your prompt looks something like bash-4.xxx$. Change it to display as follows: _your_username@login:present_directory$_ For example, if I am in the cs3650 directory my bash prompt should look like _aanjhan@login:cs3650 $_

### Navigating the terminal quickly.

Here are some other nice things to know with the terminal.

* Pressing up and down arrowkeys iterates through your command history (There is also a commmand called *history* you can checkout).
* Pressing *tab* autocompletes if it finds a program, command, or file path.
* Pressing Ctrl+C sends a signal to the terminal to terminate a program if it gets stuck.
* Pressing Ctrl+Z sends a signal to the terminal to suspend a program and give you back control.
  * You can play with these by typing in *sleep 10* (which puts the terminal to sleep) for 10 seconds, and see how you can terminate this program.
* Practice getting help by typing `man ssh` into the terminal. (Press q to quit the manual pages).

### A bit of precision
Calling each of these 'commands' (i.e. ls, sort, cat, etc.) is not really correct. Each of these is itself a program (typically implemented in C or some other language).

As an example, here is the source code for 'ls': http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/ls.c
Each of these commands are part of the coreutils package in Unix. If you look through the source tree, you will additionally find many other programs (i.e. terminal commands you run in your shell) here: http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/.

# Programmer's Workflow

<img align="right" width="300px" src="https://joshldavis.com/img/vim/tabs.gif">

Figuring out a good workflow is an important part of becoming a good programmer. Some popular workflows typically involve vim or emacs (and I strongly recommend learning one for this course!). Today, tools have developed sufficiently e.g., it is possible to open a remote folder using Visual Studio Code and get the job done. You are free to get creative but expect limited support from my side or the TAs.

### Student and Teacher Dialouge

*"But I love visual studio, sublime, XCode, Atom, etc."*

*That's great, but you cannot use those in a remote environment easily--so I suggest learning another skill. By all means, use both or multiple tools to write the highest quality code.*

*"Hehe, the professor will never know if I just use notepad. I'll just take a shortcut on this assignment"*

*While that's true you can take a shortcut now, it will eventually catch up to you. I promise this is a good skill to learn! This first assignment is much more lightweight, take the time now to do things properly.*

Here are some suggested resources to get started.
* (VIM+TMUX Example) https://www.youtube.com/watch?v=YD9aFIvlQYs (16:31)
* Type *man tmux* in a terminal.
* Tmux tutorial - https://www.youtube.com/watch?v=BHhA_ZKjyxo (11:23)
* [Vim Cheatsheet](https://vim.rtorr.com/) - A handy cheat sheet for navigting Vim. Practice mastering one thing at a time.


# Automate (some of) your life

Getting familiar with the terminal is a fundamental skill to have. Many of you have various levels of experience using the terminal.

For this assignment, you will be warming up by writing a 1-2 page tutorial on bash scripting. Your tutorial will be embededded in a shell script, explaining how to do something on the terminal that is non-trivial but that can be automated. You will run your script by typing `sh myScript.sh` on the command line as an executable shell script(sh is the GNU Bourne-Again SHell -- type 'man sh' for more information).  You can look at example 'sh' scripts for inspiration on what you can achieve on the web and cite them appropriately. 

The tutorial will be done purely in text and and within a file called 'myscript.sh'. You can use any editor of your choice to type your tutorial. However, I strongly recommend a terminal based text editor like 'vim', 'emacs', or 'nano' as there will be many scenarios (both in real world and in the labs) where you are only having a remote terminal access through e.g., ssh.

Examples of a non-trivial scripts

* Sort a particular column of data from a .csv file (e.g. stock prices). Then print out the top ten values, and the average of that column of data.
* Write a shell script that allows you to query information about your computer system from a menu of options. Users might like to know information like hard drive space, if a graphics card is available, how fast the cpu is, etc.
* Write a shell script that downloads a webpage (using wget, perhaps to grab some json data), then parses some of the data, and prints it to the terminal. 
* You can use your imagination to create other examples.

## Task 2 - myScript.sh

<img width="400px" src="https://cdn-images-1.medium.com/max/1600/1*MaSfT-bQOxfWnKjFPxMg6g.gif">

## Very Brief Example Tutorial (Template)
(Note this example is fairly trivial, probably worth a C-. You can use it as a template)

```
# Problem Statement: "Often I have to search for different files and directories within my computer system. 
#                     In order to do this I use the 'ls' command to help orient myself.
# Name of command: ls
# Example of its usage: 
# -bash-4.2$ ls
# Lab1  README.md

# Here is the myScript.sh script that can list the directories and how many total directories are in the current folder.
# usage: sh myScript.sh

ls
ls | wc -l
```

Some ideas for improving the script above script to earn closer to an A are the following:

- Print out a 'tree' visualization of the directory you are searching.
- Output the amount of file space each directory is taking up
- Output some graphical patterns after running the command.
- List the history of the last 100 commands that have been run.
  - Then sort how frequently they are used.
- The crazier the better: For example, write a script to crawl a weather site and inform if any critical information (e.g., rain from xx am, carry a jacket etc.)

* Some inspiration for developing shell scripting skills (try atleast the medium difficulty ones) can be found here: https://www.hackerrank.com/domains/shell

**Grading:** The grade will be given based on how well the script is commented, does it run without any bugs on Khoury machines, does it handle monkey (random!) inputs, etc.


# Setting up a Virtual Machine locally (Optional but recommended)

Sometimes ssh is not available if the internet is not. Hmm, how will we then work on our Khoury machines which are in a linux environment? The solution is to install locally (i.e. your desktop machine) a virtual machine. A virtual machine emulates an entire operating system!

Here appear to be two useful videos on getting setup:

1. [Installing Ubuntu in Virtual Box on Windows](https://www.youtube.com/watch?v=QbmRXJJKsvs)
2. [Install Ubuntu in Virtual Box on Mac](https://www.youtube.com/watch?v=4SbTXqPk_1Y)


The instructions to get setup are here:

**Note** If you are on windows and have the Windows Linux Subsystem, you can submit a screenshot of that running. That *should be* sufficient for most things in this course. And if you are using linux...just submit a screenshot of your desktop (You may still find the exercise useful however--especially if you want to test software on multiple OS's).

* First start downloading the operating system I recommend using: Ubuntu https://www.ubuntu.com/download/desktop
  * While our Khoury machines are actually CentOS for the operating system, Ubuntu will work just fine (They core kernel is the same).
  * The download is rather large, so start with this step! :)
* Visit https://www.virtualbox.org/
* Download the binary for Virtual box 5.2 or later.
  1. This will show up as "Windows hosts" for window users, OSX hosts for mac users, etc.
* Install the program using the default installation settings (i.e. you will click 'next' a bunch of times).
* When installation has completed, launch Virtaul Box.
* Next click 'new' in the top right, and select *Linux* from the 'Type' dropbown box.
  1. You can name it something like 'myUbuntuMachine'
  2. Click 'next'
  3. You can then configure the memory size. I recommend at least 4096 MB (Unless that is not more than half of what you have available).
  4. Click 'next' and then create a Virtual Hard disk(default option). This essentially creates a giant file that acts like a hard drive.
  5. You can create a VDI (Virtual Disk Image). Click next.
  6. For the storage, you can select 'Dynamically allocated'
* Okay, now you are configured, and ready to boot your OS!
  1. Go ahead and right-click on your machine name, and select 'start'. 
  2. This will begin launching your virtual machine (It may take a few minutes to create some files)
  3. The first dialog will ask where your media is, and you will select wherever you downloaded the Ubuntu 18 .iso file (in step 1).
  4. Then run through the 'normal install'
  5. Follow the dialogs to install Ubuntu.
  6. Remember, you are working within a virtual environment, so this installation is only taking place within virtual box.
  7. From within Ubuntu, try opening a terminal. Run `sudo apt-get install build-essential` to make sure you get some tools(like our compiler gcc) setup.

Again, if you have a linux machine you may not need a virtual machine. What is nice about a virtual machine however, is if you mess something up, you can always reboot it and start from scratch very easily.

## More resources to help

- Mike Shah's video tutorial playlist: https://www.youtube.com/watch?v=HjZVOWAGgZQ&list=PLvv0ScY6vfd8qupx0owF78ZcbvySvbWfx
- There is a lovely user manual on Virtual Box here: https://www.virtualbox.org/manual/
- There is another example of installing an older Ubuntu on an older version of virtual box here with pictures: https://askubuntu.com/questions/142549/how-to-install-ubuntu-on-virtualbox
- Installing Ubuntu on virtual box in windows video tutorial: https://www.youtube.com/watch?v=IVquJh3DXUA
- If you are not comfortable with compiling a C program on the terminal, take a look at this resource: https://www.cs.fsu.edu/~myers/howto/g++compiling.txt
- Hackerrank has an excellent series of shell tutorials here: https://www.hackerrank.com/domains/shell/bash
  - I highly recommend going through them if you are not comfortable with the shell.
- **If you accidently delete something** you can navigate to `cd .snapshot/` which will show files that have been periodically backed up for that current directory. This is yet anothe reason to make sure you are working within the Khoury systems which provide this backup service.
- A pretty good introduction to shell scripting is here: https://www.howtogeek.com/67469/the-beginners-guide-to-shell-scripting-the-basics/ .





## Going Further

(Some more terminal programs to research and try out on your own time)

1. [history](http://man7.org/linux/man-pages/man3/history.3.html)
2. tree
3. [touch](http://man7.org/linux/man-pages/man1/touch.1.html)
4. [awk](http://man7.org/linux/man-pages/man1/awk.1p.html)
5. [sed](http://man7.org/linux/man-pages/man1/sed.1.html)
6. [mv](http://man7.org/linux/man-pages/man1/mv.1.html) - Move a file or directory to a new location (or rename an item)
7. [cp](http://man7.org/linux/man-pages/man1/cp.1.html) - Copies a file
8. [scp](https://linux.die.net/man/1/scp)
	- Copy a file(e.g. backup_copy.txt) from a remote host(i.e. a server) to a local host(i.e. your machine)
		- `scp username@from_host:backup_copy.txt /mike/desktop/`
	- Copy file(e.g. linux.jpg) from local host(i.e. your machine) to a remote host (i.e. a server)
		- `scp linux.jpg username@to_host:/remote/directory/monorepo-whoever/Lab1`
