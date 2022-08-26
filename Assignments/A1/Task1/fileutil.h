/**
 * @brief prints string to standard error output
 *
 * @param errorString
 */
void printError(char *errorString);

/**
 * @brief outputs file contents to filename given
 *
 * @param fileName
 * @param buffer
 */
void appendToFile(char *fileName, char *buffer);

/**
 * @brief prints string to standard output
 *
 * @param string
 */
void printStandard(char *string);

/**
 * @brief returns boolean whether the input character is a delimiter or not
 * 
 * @param character 
 * @return true 
 * @return false 
 */
bool isDelimiter(char character);