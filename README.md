# Minishell
Minishell for 2022 with ydemura from codam

[Step-by-Step set up guide.]

First clone the repo. Good first step

[Brew Installation for Readline]

To compile the project the most updated version of readline is used. You may need to acquire brew first. You can do so from here https://brew.sh/ and then following their instructions.

If you are another Student at Codam you may need to do another way to install brew as we do not have permissions to regularly install it. If that is the case you would want to run this command

rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

You should be able to find the source of that in the 42 network slack if you are curious enough.

Once you have acquired brew you will want to follow the instructions here.
https://formulae.brew.sh/formula/readline This link works for both Codam and Non Codam computers.

[To run the project]

Simply typing "make" into your terminal while in the directory with the makefile
will compile the project and give you the program named minishell
You can cleanse anything that is not the program or source files by running "make clean" and you can rid the program itself with "make fclean"