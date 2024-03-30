#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>


class Helper
{
private:
    //Helper();

public:
    Helper();
    
    friend class Game; 

    /**
     * @brief Check whether the given string is an integer or a float 
     * 
     * @param s The given string
     * @return true if the string is an integer or a float 
     * @return false if the string is neither an integer nor a float 
     */
    static bool isNumber(std::string s);

    /**
     * @brief Split the given string given a delimeter. For instance, given the string "1,2,3" and the delimeter ",", 
     *        This string will be splited into "1","2","3", and they will be put into the vector.  
     * 
     * @param s The given string
     * @param tokens The vector containing the results
     * @param delimeter the string based on which splitting is performed
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    static void printInvalidInput();

    /**
     * @brief Convert the user input (a string) to integer
     * 
     * @param myString The given string
     * @return an Int representation of the given string
    */
    static int convertInt(std::string myString); 

    /**
     * @brief Convert the user input (a string) to float
     * 
     * @param myString The given string
     * @return a float representation of the given string
    */
    static float convertFloat(std::string myString);

};
#endif