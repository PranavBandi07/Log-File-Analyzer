

```markdown
# Log File Analyzer

a small C project i built to get better at pointers and dynamic memory allocation. it reads through a log file line by line and lets you search for keywords, filter lines, and count occurrences.

## how to compile

```bash
gcc logfileanalyzer.c -o logfileanalyzer
```

## how to run

```bash
./logfileanalyzer yourfile.log
```

## example

```bash
./logfileanalyzer test.log
```

output:
```
loaded 4 lines

search results for 'error':
line 1: error something went wrong
line 4: error connection failed
found 2 match(es)

filter for 'warning':
lines containing 'warning':
warning low memory

total occurrences of 'error': 2
```

## what it does

- loads a log file into a dynamic array that grows as needed
- searches for lines containing a keyword
- filters and prints matching lines
- counts total occurrences of a word

## stuff i learned

manual memory management with malloc, realloc and free was honestly the hardest part. had to be careful about copying strings properly and freeing everything at the end without leaking memory. debugged a few segfaults along the way which was painful but made it click.
