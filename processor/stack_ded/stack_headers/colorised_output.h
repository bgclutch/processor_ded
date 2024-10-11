#ifndef COLORISED_OUTPUT_H_
#define COLORISED_OUTPUT_H_

#define RED     "\e[0;31m" ///< red
#define GREEN   "\e[0;32m" ///< green
#define YELLOW  "\e[0;33m" ///< yellow
#define BLUE    "\e[0;34m" ///< blue
#define MAGENTA "\e[0;35m" ///< magenta
#define RES_COL    "\e[0m" ///< reset color

#define RED_TEXT(text)     RED text RES_COL     ///< red text     + reset color  
#define GREEN_TEXT(text)   GREEN text RES_COL   ///< green text   + reset color
#define YELLOW_TEXT(text)  YELLOW text RES_COL  ///< yellow text  + reset color
#define BLUE_TEXT(text)    BLUE text RES_COL    ///< blue text    + reset color
#define MAGENTA_TEXT(text) MAGENTA text RES_COL ///< magenta text + reset color


#endif //COLORISED_OUTPUT_H_