## Static vs Dynamic Libraries

`Static link libraries` are libraries that are compiled with your main program.
They are included in you executable file (.exe for windows). 

They are standard way of creating libaries.
You should create static libraries when making a utility for standalone applications

`Dynamic Link Libraries` are libraries which are make for general-purpose programs.
They are not compiled with your main program and thus not inside your executable.
These types of libraries are good when you have multiple programs dependent on your library


Note:
> When creating dynamic libraries, you need to make sure that the files are __searchable__ by your OS.

That is, you need to ensure that the library is present at the same level as your executable or in your `PATH` variables

You can watch the video i make [HERE](https://youtu.be/cz8e7KwhMbg?si=tW2IcNnvNIv24Chg)

