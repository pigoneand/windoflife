#include <iostream>
#include <string>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////
// This class can deal with chinese character
/////////////////////////////////////////////////////////
class Character
{
    public:
        static bool hasChineseCharacter(string s)
        {
            for (int i = 0; i < s.length(); ++i)
                if (s[i] < 0) return true;
            return false;
        }

        static bool hasEnglishCharacter(string s)
        {
            for (int i = 0; i < s.length(); ++i)
                if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z') 
                    return true;
            return false;
        }

        static bool isLetter(char c)
        {
            return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
        }

        static bool isChineseCharacter(char a , char b)
        {
            if (a < 0) return true;
            else return false;
        }

        static bool isGBCode(char a , char b)
        {
            unsigned char ch1 = (unsigned char) a;
            unsigned char ch2 = (unsigned char) b;

            if (ch1 >= 176 && ch1 <= 247 && ch2 >= 160 && ch2 <= 254) 
                return true;
            else
                return false;
        }

        static bool isGBKCode(char a , char b)
        {
            unsigned char ch1 = (unsigned char) a;
            unsigned char ch2 = (unsigned char) b;

            if (ch1 >= 129 && ch1 <= 254 && ch2 >= 64 && ch2 <= 254)
                return true;
            else
                return false;
        }
        
        static int getLastChineseCharacter(string s)
        {
            int lastChinese = 0;
            int i = 0;
            while (i < s.length()) {
                if (s[i] < 0) {
                    lastChinese = i + 3;
                    i += 3;
                }
                else
                {
                    i++;
                }
            }
            return lastChinese;
        }            

        static int getLastEnglishCharacter(string s)
        {
            int lastEnglish = 0;
            int i = 0;
            while (i < s.length()) {
                if (s[i] < 0) {
                    i += 3;
                }
                else
                {
                    lastEnglish = i + 1;
                    i++;
                }
            }
            return lastEnglish;
        } 

        static vector<string> splitChineseEnglish_UTF8(string s)
        {
            string chinese;
            string english;
            for (int i = 0; i < s.length(); ++i) {
                if (isChineseCharacter(s[i] , s[i+1])) {
                    chinese += s[i];
                    chinese += s[i+1];
                    chinese += s[i+2];
                    i+=2;
                }
                else
                    english += s[i];
            }
            vector<string> ret;
            ret.push_back(chinese);
            ret.push_back(english);
            return ret;
        }

        static vector<string> splitSentenseByLastChinese(string s)
        {
            string chinese;
            string english;
            vector<string> ret;
            int i;
            int lastChinese = getLastChineseCharacter(s);
            for (i = 0; i < lastChinese; ++i)
                chinese += s[i];
            for (i = lastChinese; i < s.length(); ++i)
                english += s[i];
            ret.push_back(chinese);
            ret.push_back(english);
            return ret;
        }
        
        static vector<string> splitSentenseByLastEnglish(string s)
        {
            string chinese;
            string english;
            vector<string> ret;

            int lastEnglish = getLastEnglishCharacter(s);
            int i;
            for (i = 0; i < lastEnglish; ++i)
                english += s[i];
            for (i = lastEnglish; i < s.length(); ++i)
                chinese += s[i];
            ret.push_back(chinese);
            ret.push_back(english);
            return ret;
        }

        static const int CHINESE = 1;
        static const int ENGLISH = 2;

        static int getMainLanguage(string s)
        {
            int chinese = 0;
            int english = 0;
            int i = 0;
            while (i < s.length()) {
                if (s[i] < 0) {
                    chinese += 3;
                    i += 3;
                }
                else {
                    english++;
                    i++;
                }
            }
            if (chinese > english) return CHINESE;
            else return ENGLISH;
        }
};

int main()
{
    char temp[10000];
    string line;
    string s_temp;

    line = "";
    int lastLang = 0;
    cin.getline(temp,10000,'\n');
    s_temp = temp;
    lastLang = Character::getMainLanguage(s_temp);
    line += s_temp;

    while (cin.getline(temp,10000,'\n')) {
        s_temp = temp;
        int lang = Character::getMainLanguage(s_temp);
        if (lang == lastLang) {
            line += s_temp;
        }
        else {
            cout << line << endl;
            line = s_temp;
            lastLang = lang;
        }
    }
    cout << line << endl;
    /** 
    while (cin.getline(temp,10000,'\n')) { s_temp = temp;
        bool containEnglish = Character::hasEnglishCharacter(s_temp); 
        bool containChinese = Character::hasChineseCharacter(s_temp);
        int lastChinese = Character::getLastChineseCharacter(s_temp);
        int lastEnglish = Character::getLastEnglishCharacter(s_temp);

        if (containEnglish && !containChinese) 
            cout << s_temp << endl;
        if (!containEnglish && containChinese)
            cout << s_temp << endl;
        if (!containEnglish && !containChinese) 
            continue;
        if (containEnglish && containChinese) {
            if (lastChinese < lastEnglish) {
                vector<string> result = Character::splitSentenseByLastChinese(s_temp);
                cout << result[0] << endl;
                cout << result[1] << endl;
            }
            else
            {
                if (Character::isLetter(s_temp[0])) {
                    vector<string> result = Character::splitSentenseByLastEnglish(s_temp);
                    cout << result[1] << endl;
                    cout << result[0] << endl;
                }
                else
                {
                    cout << s_temp << endl;
                }
            }
        }
    }
    */

    return 0;
}
