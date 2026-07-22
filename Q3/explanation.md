open() creates or opens the file at the system call level and returns a file descriptor, which is used by all subsequent operations instead of a FILE pointer. Using O_CREAT with O_TRUNC sets up a fresh file for writing, while O_RDWR is used later for updating so the same descriptor can both read and write.

Records are stored as fixed-size C structures, so every record occupies exactly RECORD_SIZE bytes. This fixed size is what makes direct access possible: the byte offset of any record is simply (record_number - 1) * RECORD_SIZE.

lseek() moves the file's internal read/write pointer directly to that offset without touching any other part of the file. This is the key to updating or retrieving a specific record efficiently, since the program never has to read through preceding records or rewrite the whole file, unlike appending to a plain text file.

write() and read() then operate at the current file position set by lseek(), transferring exactly RECORD_SIZE bytes at a time so each call corresponds to exactly one employee record. To update a record, the program seeks to its offset, reads it into memory, modifies the needed field, seeks back to the same offset, and writes it back, leaving all other records untouched.

close() releases the file descriptor once operations are done, ensuring buffers are flushed to disk and the resource is freed.

Together, open() and close() manage the file's lifecycle, lseek() enables direct, efficient access to any record by offset, and read()/write() transfer data in fixed-size chunks aligned with that offset, allowing individual records to be updated or retrieved without processing the entire file.