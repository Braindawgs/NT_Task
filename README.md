# NT_Task

## Summary

Task: 
```
Implement a smart storage library. The library should be able to store and retrieve
values from a file and must be resistant to corruption (to a certain extent).
```
The modular approach was taken here, making `InterfaceStorage` an abstract class from which all storages inherit.
For this particular case database (sqlite3) was used but generic files can be used and "hooked" to it.

The `SmartStorage` generates `data:checksum` combination and saves it to a file. When reading `:` will be checked and checksum verified.

## Build

This task depends on SQLite3 lib, instead of submoduling the lib apt-get was used.

```sh
sudo apt-get install libsqlite3-dev
```

To build the task use:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## Execution

When ./NT_Task is executed you'll be prompted with 

```
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
```
1) Write writes to a file, and will print out the "position" of the string in the file.
2) Reads the values from the "position" in the file.
3) List all entries in the file.
4) Corrupts value in the position.
5) Quits the program