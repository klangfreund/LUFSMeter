/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#include "../jucer_Headers.h"
#include "jucer_CodeHelpers.h"


//==============================================================================
namespace CodeHelpers
{
    String indent (const String& code, const int numSpaces, bool indentFirstLine)
    {
        if (numSpaces == 0)
            return code;

        const String space (String::repeatedString (" ", numSpaces));

        StringArray lines;
        lines.addLines (code);

        for (int i = (indentFirstLine ? 0 : 1); i < lines.size(); ++i)
        {
            String s (lines[i].trimEnd());
            if (s.isNotEmpty())
                s = space + s;

            lines.set (i, s);
        }

        return lines.joinIntoString (newLine);
    }

    String makeValidIdentifier (String s, bool capitalise, bool removeColons, bool allowTemplates)
    {
        if (s.isEmpty())
            return "unknown";

        if (removeColons)
            s = s.replaceCharacters (".,;:/@", "______");
        else
            s = s.replaceCharacters (".,;/@", "_____");

        for (int i = s.length(); --i > 0;)
            if (CharacterFunctions::isLetter (s[i])
                 && CharacterFunctions::isLetter (s[i - 1])
                 && CharacterFunctions::isUpperCase (s[i])
                 && ! CharacterFunctions::isUpperCase (s[i - 1]))
                s = s.substring (0, i) + " " + s.substring (i);

        String allowedChars ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_ 0123456789");
        if (allowTemplates)
            allowedChars += "<>";

        if (! removeColons)
            allowedChars += ":";

        StringArray words;
        words.addTokens (s.retainCharacters (allowedChars), false);
        words.trim();

        String n (words[0]);

        if (capitalise)
            n = n.toLowerCase();

        for (int i = 1; i < words.size(); ++i)
        {
            if (capitalise && words[i].length() > 1)
                n << words[i].substring (0, 1).toUpperCase()
                  << words[i].substring (1).toLowerCase();
            else
                n << words[i];
        }

        if (CharacterFunctions::isDigit (n[0]))
            n = "_" + n;

        if (CPlusPlusCodeTokeniser::isReservedKeyword (n))
            n << '_';

        return n;
    }

    static void writeEscapeChars (OutputStream& out, const char* utf8, const int numBytes,
                                  const int maxCharsOnLine, const bool breakAtNewLines,
                                  const bool replaceSingleQuotes, const bool allowStringBreaks)
    {
        int charsOnLine = 0;
        bool lastWasHexEscapeCode = false;

        for (int i = 0; i < numBytes || numBytes < 0; ++i)
        {
            const unsigned char c = (unsigned char) utf8[i];
            bool startNewLine = false;

            switch (c)
            {
                case '\t':  out << "\\t";  lastWasHexEscapeCode = false; charsOnLine += 2; break;
                case '\r':  out << "\\r";  lastWasHexEscapeCode = false; charsOnLine += 2; break;
                case '\n':  out << "\\n";  lastWasHexEscapeCode = false; charsOnLine += 2; startNewLine = breakAtNewLines; break;
                case '\\':  out << "\\\\"; lastWasHexEscapeCode = false; charsOnLine += 2; break;
                case '\"':  out << "\\\""; lastWasHexEscapeCode = false; charsOnLine += 2; break;

                case 0:
                    if (numBytes < 0)
                        return;

                    out << "\\0";
                    lastWasHexEscapeCode = true;
                    charsOnLine += 2;
                    break;

                case '\'':
                    if (replaceSingleQuotes)
                    {
                        out << "\\\'";
                        lastWasHexEscapeCode = false;
                        charsOnLine += 2;
                        break;
                    }

                    // deliberate fall-through...

                default:
                    if (c >= 32 && c < 127 && ! (lastWasHexEscapeCode  // (have to avoid following a hex escape sequence with a valid hex digit)
                                                   && CharacterFunctions::getHexDigitValue (c) >= 0))
                    {
                        out << (char) c;
                        lastWasHexEscapeCode = false;
                        ++charsOnLine;
                    }
                    else if (allowStringBreaks && lastWasHexEscapeCode && c >= 32 && c < 127)
                    {
                        out << "\"\"" << (char) c;
                        lastWasHexEscapeCode = false;
                        charsOnLine += 3;
                    }
                    else
                    {
                        out << (c < 16 ? "\\x0" : "\\x") << String::toHexString ((int) c);
                        lastWasHexEscapeCode = true;
                        charsOnLine += 4;
                    }

                    break;
            }

            if ((startNewLine || (maxCharsOnLine > 0 && charsOnLine >= maxCharsOnLine))
                 && (numBytes < 0 || i < numBytes - 1))
            {
                charsOnLine = 0;
                out << "\"" << newLine << "\"";
                lastWasHexEscapeCode = false;
            }
        }
    }

    String addEscapeChars (const String& s)
    {
        MemoryOutputStream out;
        writeEscapeChars (out, s.toUTF8().getAddress(), -1, -1, false, true, true);
        return out.toUTF8();
    }

    String createIncludeStatement (const File& includeFile, const File& targetFile)
    {
        return createIncludeStatement (FileHelpers::unixStylePath (FileHelpers::getRelativePathFrom (includeFile, targetFile.getParentDirectory())));
    }

    String createIncludeStatement (const String& includePath)
    {
        if (includePath.startsWithChar ('<') || includePath.startsWithChar ('"'))
            return "#include " + includePath;

        return "#include \"" + includePath + "\"";
    }

    String makeHeaderGuardName (const File& file)
    {
        return "__" + file.getFileName().toUpperCase()
                                        .replaceCharacters (" .", "__")
                                        .retainCharacters ("_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
                + "_" + String::toHexString (file.hashCode()).toUpperCase() + "__";
    }

    String makeBinaryDataIdentifierName (const File& file)
    {
        return makeValidIdentifier (file.getFileName()
                                        .replaceCharacters (" .", "__")
                                        .retainCharacters ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_0123456789"),
                                    false, true, false);
    }

    String stringLiteral (const String& text, int maxLineLength)
    {
        if (text.isEmpty())
            return "String::empty";

        StringArray lines;
        lines.add (text);

        if (maxLineLength > 0)
        {
            while (lines [lines.size() - 1].length() > maxLineLength)
            {
                String& lastLine = lines.getReference (lines.size() - 1);
                const String start (lastLine.substring (0, maxLineLength));
                const String end (lastLine.substring (maxLineLength));
                lastLine = start;
                lines.add (end);
            }
        }

        for (int i = 0; i < lines.size(); ++i)
            lines.getReference(i) = "\"" + addEscapeChars (lines.getReference(i)) + "\"";

        String result (lines.joinIntoString (newLine));

        if (! CharPointer_ASCII::isValidString (text.toUTF8(), std::numeric_limits<int>::max()))
            result = "CharPointer_UTF8 (" + result + ")";

        return result;
    }

    String alignFunctionCallParams (const String& call, const StringArray& parameters, const int maxLineLength)
    {
        String result, currentLine (call);

        for (int i = 0; i < parameters.size(); ++i)
        {
            if (currentLine.length() >= maxLineLength)
            {
                result += currentLine.trimEnd() + newLine;
                currentLine = String::repeatedString (" ", call.length()) + parameters[i];
            }
            else
            {
                currentLine += parameters[i];
            }

            if (i < parameters.size() - 1)
                currentLine << ", ";
        }

        return result + currentLine.trimEnd() + ")";
    }

    String floatLiteral (float value, int numDecPlaces)
    {
        String s ((double) value, numDecPlaces);

        if (s.containsChar ('.'))
            s << 'f';
        else
            s << ".0f";

        return s;
    }

    String boolLiteral (bool value)
    {
        return value ? "true" : "false";
    }

    String colourToCode (const Colour& col)
    {
        const Colour colours[] =
        {
            #define COL(col)  Colours::col,
            #include "jucer_Colours.h"
            #undef COL
            Colours::transparentBlack
        };

        static const char* colourNames[] =
        {
            #define COL(col)  #col,
            #include "jucer_Colours.h"
            #undef COL
            0
        };

        for (int i = 0; i < numElementsInArray (colourNames) - 1; ++i)
            if (col == colours[i])
                return "Colours::" + String (colourNames[i]);

        return "Colour (0x" + hexString8Digits ((int) col.getARGB()) + ')';
    }

    String justificationToCode (const Justification& justification)
    {
        switch (justification.getFlags())
        {
            case Justification::centred:                return "Justification::centred";
            case Justification::centredLeft:            return "Justification::centredLeft";
            case Justification::centredRight:           return "Justification::centredRight";
            case Justification::centredTop:             return "Justification::centredTop";
            case Justification::centredBottom:          return "Justification::centredBottom";
            case Justification::topLeft:                return "Justification::topLeft";
            case Justification::topRight:               return "Justification::topRight";
            case Justification::bottomLeft:             return "Justification::bottomLeft";
            case Justification::bottomRight:            return "Justification::bottomRight";
            case Justification::left:                   return "Justification::left";
            case Justification::right:                  return "Justification::right";
            case Justification::horizontallyCentred:    return "Justification::horizontallyCentred";
            case Justification::top:                    return "Justification::top";
            case Justification::bottom:                 return "Justification::bottom";
            case Justification::verticallyCentred:      return "Justification::verticallyCentred";
            case Justification::horizontallyJustified:  return "Justification::horizontallyJustified";
            default:                                    break;
        }

        jassertfalse;
        return "Justification (" + String (justification.getFlags()) + ")";
    }

    void writeDataAsCppLiteral (const MemoryBlock& mb, OutputStream& out,
                                bool breakAtNewLines, bool allowStringBreaks)
    {
        const int maxCharsOnLine = 250;

        const unsigned char* data = (const unsigned char*) mb.getData();
        int charsOnLine = 0;

        bool canUseStringLiteral = mb.getSize() < 32768; // MS compilers can't handle big string literals..

        if (canUseStringLiteral)
        {
            unsigned int numEscaped = 0;

            for (size_t i = 0; i < mb.getSize(); ++i)
            {
                const unsigned int num = (unsigned int) data[i];
                if (! ((num >= 32 && num < 127) || num == '\t' || num == '\r' || num == '\n'))
                {
                    if (++numEscaped > mb.getSize() / 4)
                    {
                        canUseStringLiteral = false;
                        break;
                    }
                }
            }
        }

        if (! canUseStringLiteral)
        {
            out << "{ ";

            for (size_t i = 0; i < mb.getSize(); ++i)
            {
                const int num = (int) (unsigned int) data[i];
                out << num << ',';

                charsOnLine += 2;

                if (num >= 10)
                {
                    ++charsOnLine;

                    if (num >= 100)
                        ++charsOnLine;
                }

                if (charsOnLine >= maxCharsOnLine)
                {
                    charsOnLine = 0;
                    out << newLine;
                }
            }

            out << "0,0 };";
        }
        else
        {
            out << "\"";
            writeEscapeChars (out, (const char*) data, (int) mb.getSize(),
                              maxCharsOnLine, breakAtNewLines, false, allowStringBreaks);
            out << "\";";
        }
    }

    //==============================================================================
    static unsigned int calculateHash (const String& s, const int hashMultiplier)
    {
        const char* t = s.toUTF8();
        unsigned int hash = 0;
        while (*t != 0)
            hash = hashMultiplier * hash + (unsigned int) *t++;

        return hash;
    }

    static int findBestHashMultiplier (const StringArray& strings)
    {
        int v = 31;

        for (;;)
        {
            SortedSet <unsigned int> hashes;
            bool collision = false;
            for (int i = strings.size(); --i >= 0;)
            {
                const unsigned int hash = calculateHash (strings[i], v);
                if (hashes.contains (hash))
                {
                    collision = true;
                    break;
                }

                hashes.add (hash);
            }

            if (! collision)
                break;

            v += 2;
        }

        return v;
    }

    void createStringMatcher (OutputStream& out, const String& utf8PointerVariable,
                              const StringArray& strings, const StringArray& codeToExecute, const int indentLevel)
    {
        jassert (strings.size() == codeToExecute.size());
        const String indent (String::repeatedString (" ", indentLevel));
        const int hashMultiplier = findBestHashMultiplier (strings);

        out << indent << "unsigned int hash = 0;" << newLine
            << indent << "if (" << utf8PointerVariable << " != 0)" << newLine
            << indent << "    while (*" << utf8PointerVariable << " != 0)" << newLine
            << indent << "        hash = " << hashMultiplier << " * hash + (unsigned int) *" << utf8PointerVariable << "++;" << newLine
            << newLine
            << indent << "switch (hash)" << newLine
            << indent << "{" << newLine;

        for (int i = 0; i < strings.size(); ++i)
        {
            out << indent << "    case 0x" << hexString8Digits (calculateHash (strings[i], hashMultiplier))
                << ":  " << codeToExecute[i] << newLine;
        }

        out << indent << "    default: break;" << newLine
            << indent << "}" << newLine << newLine;
    }

    String getLeadingWhitespace (String line)
    {
        line = line.removeCharacters ("\r\n");
        const String::CharPointerType endOfLeadingWS (line.getCharPointer().findEndOfWhitespace());
        return String (line.getCharPointer(), endOfLeadingWS);
    }

    int getBraceCount (String::CharPointerType line)
    {
        int braces = 0;

        for (;;)
        {
            const juce_wchar c = line.getAndAdvance();

            if (c == 0)                         break;
            else if (c == '{')                  ++braces;
            else if (c == '}')                  --braces;
            else if (c == '/')                  { if (*line == '/') break; }
            else if (c == '"' || c == '\'')     { while (! (line.isEmpty() || line.getAndAdvance() == c)) {} }
        }

        return braces;
    }

    bool getIndentForCurrentBlock (CodeDocument::Position pos, const String& tab,
                                   String& blockIndent, String& lastLineIndent)
    {
        int braceCount = 0;
        bool indentFound = false;

        while (pos.getLineNumber() > 0)
        {
            pos = pos.movedByLines (-1);

            const String line (pos.getLineText());
            const String trimmedLine (line.trimStart());

            braceCount += getBraceCount (trimmedLine.getCharPointer());

            if (braceCount > 0)
            {
                blockIndent = getLeadingWhitespace (line);
                if (! indentFound)
                    lastLineIndent = blockIndent + tab;

                return true;
            }

            if ((! indentFound) && trimmedLine.isNotEmpty())
            {
                indentFound = true;
                lastLineIndent = getLeadingWhitespace (line);
            }
        }

        return false;
    }
}
