/*
* Copyright 2006 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef AUTUMN_UTIL_H
#define AUTUMN_UTIL_H

#include <string>

using namespace std;

/** 
 * Utility
 */
class Util{
   /**
    * If the String s starts with a string literal, a comment or white spaces,
    * return the length of the literal, comment and white spaces. String
    * literals are enclosed in " or ' and comments start with /* or //.
    */
	static int skip(string& s);
	
public:
	/**
	 * which line the position is in s
	 * @param idx The position
	 */
	static int lineno(string& s, int idx);

	/** return the number of white spaces at the head of s */
	static int whiteSapceLen(string& s);

	/** the length of comment at the head of s */
	static int commentLen(string& s);

	/** the length of pre-processor at the head of s */
	static int preProcessortLen(string& s);

	/** the length of literal at the head of s */
	static int literalLen(string& s);

	/** 
	 * if has irrelevant part, return a nonzero number.
	 * it may the length of white spaces, or of comment, of define and macro.
	 * it may not the whole length of the irrelevant part.
	 */
	static int irrelevantLen(string&s);

	/** 
	 * if has un-recognised part, return a nonzero number.
	 * it may the length of using ..., or friendly ..., or extern ...,
	 * or template ... .
	 * it may not the whole length of the un-recognised part.
	 */
	static int unrecognisedLen(string&s);

	/**
     * Matches braces and is C-aware. It skips string literals and comments.
	 * This function can't match quotes, because skip function skips quotes.
	 * @return the index of matching c2.
     */
	static int findMatching(string& s, char c1, char c2);

	/**
	 * Performs a C-aware version of String.indexOf(String) in that it skips
	 * string literals and comments and makes sure that the target string
	 * is not embedded in a longer word.
	 */
	static int indexOf(string& s, string t);

	/**
	 * Performs a C-aware version of String.indexOf(char) in that it skips
	 * string literals and comments.
	 */
	static int indexOf(string& s, char c);
	
	//以t为单字的开始，避免t在一个大的单词中
	static bool startWith(string& s, string t);

	/** parse file name from a path */
	static string filenameOf(string s);

	/** is special char or not */
	static bool isSpecialChar(char c);

	/** get the last word separated by white space or special char */
	static string getLastWord(string s);

	/** replace comment with white space */
	static string replaceComment(string s);

	/** erase white spaces at head and tail */
	static string trim(string s);

	/** erase all white spaces in the string */
	static string trimall(string s);

	/** a word is primitive data type or not */
	static bool isPrimType(string w);

	/** a word is struct data type key or not */
	static bool isStruTypeKey(string w);
};

#endif
