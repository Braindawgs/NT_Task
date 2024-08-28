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

<details>
<summary>Example</summary>

```
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
--------------
1
Enter text:First line              
Text:"First line" is saved on position 1
--------------
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
--------------
1
Enter text:Second line
Text:"Second line" is saved on position 2
--------------
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
--------------
3
Listing entries:
Key: 1, Value: First line:12121062197758380058
Key: 2, Value: Second line:5112499109616018711
```

Corruption added
```
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
--------------
4
Which row to corrupt:1
--------------
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
--------------
3
Listing entries:
Key: 1, Value: CoRRuPtiiiiNg
Key: 2, Value: Second line:5112499109616018711
--------------
Options:
1) Write
2) Read
3) List all entries
4) Corrupt
5) Quit
--------------
2
Enter row to be read:1
Error: Corruption: checksum missing
```
</details>

## Memory leak checks
Valgrind output (`valgrind --leak-check=yes ./NT_Task`):
```
==10577== HEAP SUMMARY:
==10577==     in use at exit: 0 bytes in 0 blocks
==10577==   total heap usage: 448 allocs, 448 frees, 247,238 bytes allocated
==10577== 
==10577== All heap blocks were freed -- no leaks are possible
==10577== 
==10577== For lists of detected and suppressed errors, rerun with: -s
==10577== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```