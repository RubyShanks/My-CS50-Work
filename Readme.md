Problem Specification: https://cs50.harvard.edu/x/2020/psets/5/speller/
• Built a spell checker in C for text files that loads and hashes words from a dictionary to check for misspelled words.
• Implemented a hash table by hashing on first 4 letters of every word for 500k+ buckets to minimize checking time.
• Used valgrind to check for and eliminate memory leaks caused due to the use of dynamic memory allocation.
Files modified/implemented: dictionary.c
