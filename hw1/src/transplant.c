#include "global.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

/*
 * You may modify this file and/or move the functions contained here
 * to other source files (except for main.c) as you wish.
 *
 * IMPORTANT: You MAY NOT use any array brackets (i.e. [ and ]) and
 * you MAY NOT declare any arrays or allocate any storage with malloc().
 * The purpose of this restriction is to force you to use pointers.
 *
 * Variables to hold the pathname of the current file or directory
 * as well as other data have been pre-declared for you in global.h.
 * You must use those variables, rather than declaring your own.
 * IF YOU VIOLATE THIS RESTRICTION, YOU WILL GET A ZERO!
 *
 * IMPORTANT: You MAY NOT use floating point arithmetic or declare
 * any "float" or "double" variables.  IF YOU VIOLATE THIS RESTRICTION,
 * YOU WILL GET A ZERO!
 */

/*
 * @brief  Initialize path_buf to a specified base path.
 * @details  This function copies its null-terminated argument string into
 * path_buf, including its terminating null byte.
 * The function fails if the argument string, including the terminating
 * null byte, is longer than the size of path_buf.  The path_length variable 
 * is set to the length of the string in path_buf, not including the terminating
 * null byte.
 *
 * @param  Pathname to be copied into path_buf.
 * @return 0 on success, -1 in case of error
 */
int path_init(char *name) {
    // To be implemented.
    // abort();
    char *src = name;
    char *dst = path_buf;
    path_length = 0;

    // Copy the string from `name` into `path_buf`
    while (*src != '\0') {
        if (path_length >= PATH_MAX - 1) {  // Ensure enough space for null terminator
            return -1;  // Error: String too long to fit in path_buf
        }
        *dst = *src;  // Copy character from name to path_buf
        dst++;
        src++;
        path_length++;
    }

    *dst = '\0';  // Null-terminate path_buf
    return 0;  // Success
}

/*
 * @brief  Append an additional component to the end of the pathname in path_buf.
 * @details  This function assumes that path_buf has been initialized to a valid
 * string.  It appends to the existing string the path separator character '/',
 * followed by the string given as argument, including its terminating null byte.
 * The length of the new string, including the terminating null byte, must be
 * no more than the size of path_buf.  The variable path_length is updated to
 * remain consistent with the length of the string in path_buf.
 * 
 * @param  The string to be appended to the path in path_buf.  The string must
 * not contain any occurrences of the path separator character '/'.
 * @return 0 in case of success, -1 otherwise.
 */
int path_push(char *name) {
    // To be implemented.
    // abort();
    char *dst = path_buf + path_length;

    // Add '/' if not already at the end
    if (path_length > 0 && *(dst - 1) != '/') {
        if (path_length >= PATH_MAX - 1) {  // Ensure space for '/'
            return -1;  // Error: Not enough space to append '/'
        }
        *dst = '/';
        dst++;
        path_length++;
    }

    // Append the new component from `name`
    while (*name != '\0') {
        if (*name == '/') {
            return -1;  // Error: name contains '/'
        }
        if (path_length >= PATH_MAX - 1) {  // Ensure enough space for the full name and null terminator
            return -1;  // Error: Not enough space to append
        }
        *dst = *name;
        dst++;
        name++;
        path_length++;
    }

    *dst = '\0';  // Null-terminate the new path_buf
    return 0;  // Success
}

/*
 * @brief  Remove the last component from the end of the pathname.
 * @details  This function assumes that path_buf contains a non-empty string.
 * It removes the suffix of this string that starts at the last occurrence
 * of the path separator character '/'.  If there is no such occurrence,
 * then the entire string is removed, leaving an empty string in path_buf.
 * The variable path_length is updated to remain consistent with the length
 * of the string in path_buf.  The function fails if path_buf is originally
 * empty, so that there is no path component to be removed.
 *
 * @return 0 in case of success, -1 otherwise.
 */
int path_pop() {
    // To be implemented.
    // abort();
    if (path_length == 0) {
        return -1;  // Error: path_buf is empty
    }

    char *ptr = path_buf + path_length - 1;

    // Move backwards to find the last '/'
    while (ptr >= path_buf && *ptr != '/') {
        ptr--;
    }

    if (ptr < path_buf) {
        // No '/' found, clear the entire path
        path_length = 0;
        *path_buf = '\0';  // Set path_buf to empty string
    } else {
        // Null-terminate at the found '/' to remove the last component
        *ptr = '\0';
        path_length = ptr - path_buf;  // Update path_length
    }

    return 0;  // Success
}

/*
 * @brief Deserialize directory contents into an existing directory.
 * @details  This function assumes that path_buf contains the name of an existing
 * directory.  It reads (from the standard input) a sequence of DIRECTORY_ENTRY
 * records bracketed by a START_OF_DIRECTORY and END_OF_DIRECTORY record at the
 * same depth and it recreates the entries, leaving the deserialized files and
 * directories within the directory named by path_buf.
 *
 * @param depth  The value of the depth field that is expected to be found in
 * each of the records processed.
 * @return 0 in case of success, -1 in case of an error.  A variety of errors
 * can occur, including depth fields in the records read that do not match the
 * expected value, the records to be processed to not being with START_OF_DIRECTORY
 * or end with END_OF_DIRECTORY, or an I/O error occurs either while reading
 * the records from the standard input or in creating deserialized files and
 * directories.
 */
int deserialize_directory(int depth) {
    // To be implemented.
    abort();
}

/*
 * @brief Deserialize the contents of a single file.
 * @details  This function assumes that path_buf contains the name of a file
 * to be deserialized.  The file must not already exist, unless the ``clobber''
 * bit is set in the global_options variable.  It reads (from the standard input)
 * a single FILE_DATA record containing the file content and it recreates the file
 * from the content.
 *
 * @param depth  The value of the depth field that is expected to be found in
 * the FILE_DATA record.
 * @return 0 in case of success, -1 in case of an error.  A variety of errors
 * can occur, including a depth field in the FILE_DATA record that does not match
 * the expected value, the record read is not a FILE_DATA record, the file to
 * be created already exists, or an I/O error occurs either while reading
 * the FILE_DATA record from the standard input or while re-creating the
 * deserialized file.
 */
int deserialize_file(int depth) {
    // To be implemented.
    abort();
}

/*
 * @brief  Serialize the contents of a directory as a sequence of records written
 * to the standard output.
 * @details  This function assumes that path_buf contains the name of an existing
 * directory to be serialized.  It serializes the contents of that directory as a
 * sequence of records that begins with a START_OF_DIRECTORY record, ends with an
 * END_OF_DIRECTORY record, and with the intervening records all of type DIRECTORY_ENTRY.
 *
 * @param depth  The value of the depth field that is expected to occur in the
 * START_OF_DIRECTORY, DIRECTORY_ENTRY, and END_OF_DIRECTORY records processed.
 * Note that this depth pertains only to the "top-level" records in the sequence:
 * DIRECTORY_ENTRY records may be recursively followed by similar sequence of
 * records describing sub-directories at a greater depth.
 * @return 0 in case of success, -1 otherwise.  A variety of errors can occur,
 * including failure to open files, failure to traverse directories, and I/O errors
 * that occur while reading file content and writing to standard output.
 */
int serialize_directory(int depth) {
    // To be implemented.
    abort();
}

/*
 * @brief  Serialize the contents of a file as a single record written to the
 * standard output.
 * @details  This function assumes that path_buf contains the name of an existing
 * file to be serialized.  It serializes the contents of that file as a single
 * FILE_DATA record emitted to the standard output.
 *
 * @param depth  The value to be used in the depth field of the FILE_DATA record.
 * @param size  The number of bytes of data in the file to be serialized.
 * @return 0 in case of success, -1 otherwise.  A variety of errors can occur,
 * including failure to open the file, too many or not enough data bytes read
 * from the file, and I/O errors reading the file data or writing to standard output.
 */
int serialize_file(int depth, off_t size) {
    // To be implemented.
    abort();
}

/**
 * @brief Serializes a tree of files and directories, writes
 * serialized data to standard output.
 * @details This function assumes path_buf has been initialized with the pathname
 * of a directory whose contents are to be serialized.  It traverses the tree of
 * files and directories contained in this directory (not including the directory
 * itself) and it emits on the standard output a sequence of bytes from which the
 * tree can be reconstructed.  Options that modify the behavior are obtained from
 * the global_options variable.
 *
 * @return 0 if serialization completes without error, -1 if an error occurs.
 */
int serialize() {
    // To be implemented.
    abort();
}

/**
 * @brief Reads serialized data from the standard input and reconstructs from it
 * a tree of files and directories.
 * @details  This function assumes path_buf has been initialized with the pathname
 * of a directory into which a tree of files and directories is to be placed.
 * If the directory does not already exist, it is created.  The function then reads
 * from from the standard input a sequence of bytes that represent a serialized tree
 * of files and directories in the format written by serialize() and it reconstructs
 * the tree within the specified directory.  Options that modify the behavior are
 * obtained from the global_options variable.
 *
 * @return 0 if deserialization completes without error, -1 if an error occurs.
 */
int deserialize() {
    // To be implemented.
    abort();
}

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and -1 if validation fails.
 * Upon successful return, the selected program options will be set in the
 * global variable "global_options", where they will be accessible
 * elsewhere in the program.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and -1 if validation fails.
 * Refer to the homework document for the effects of this function on
 * global variables.
 * @modifies global variable "global_options" to contain a bitmap representing
 * the selected options.
 */
int validargs(int argc, char **argv)
{
    // To be implemented.
    // abort();

    // Set global_options to 0 initially
    global_options = 0;

    // If there are no command-line arguments passed, return an error
    if (argc == 1) {
        return -1;  // No arguments provided
    }

    // Use pointer arithmetic to access the first argument
    char *arg = *(argv + 1);

    // Check if the first argument is "-h"
    if (*arg == '-' && *(arg + 1) == 'h') {
        global_options = 0x1;  // Set help flag
        return 0;  // Success
    }

    // Variables to track the presence of each argument
    int serialize = 0;
    int deserialize = 0;
    int clobber = 0;
    int positional_done = 0;  // Track if positional arguments have been processed

    // Loop through all the arguments using pointer arithmetic
    for (char **arg_ptr = argv + 1; arg_ptr < argv + argc; arg_ptr++) {
        arg = *arg_ptr;  // Current argument

        if (*arg != '-') {
            return -1;  // Invalid argument (must start with '-')
        }

        arg++;  // Skip the '-'

        // Handle positional arguments
        if (*arg == 's' && *(arg + 1) == '\0') {
            if (positional_done) {
                return -1;  // No positional arguments allowed after options
            }
            serialize = 1;
        } else if (*arg == 'd' && *(arg + 1) == '\0') {
            if (positional_done) {
                return -1;
            }
            deserialize = 1;
        } else if (*arg == 'c' && *(arg + 1) == '\0') {
            positional_done = 1;  // Options have started, no more positional arguments
            clobber = 1;
        } else if (*arg == 'p') {
            positional_done = 1;  // Options have started
            if (arg_ptr + 1 < argv + argc && **(arg_ptr + 1) != '-') {
                arg_ptr++;  // Skip the directory argument
            } else {
                return -1;  // '-p' provided but no directory argument
            }
        } else {
            return -1;  // Unrecognized argument
        }
    }

    // Enforce that either '-s' or '-d' must be provided, but not both
    if ((serialize && deserialize) || (!serialize && !deserialize)) {
        return -1;
    }

    // '-c' (clobber) is only valid if '-d' (deserialize) is provided
    if (clobber && !deserialize) {
        return -1;
    }

    // Set global_options based on the parsed arguments
    if (serialize) {
        global_options |= 0x2;  // Set the serialize flag
    }
    if (deserialize) {
        global_options |= 0x4;  // Set the deserialize flag
    }
    if (clobber) {
        global_options |= 0x8;  // Set the clobber flag
    }

    return 0;  // Success
}
