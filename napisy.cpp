// Mikolaj Suchan
#include <string>

using namespace std;

string NajwiekszeSlowo(string str) {
    string ans;
    string curr_word;
    for (int i = 0; i < str.size(); i++) {     
        if (curr_word != "" && str[i] == ' ') {
            if (curr_word > ans)
                ans = curr_word;
            curr_word = "";
        }
        
        if (str[i] != ' ')
            curr_word += str[i];
    }

    if (curr_word != "" && curr_word > ans)
        ans = curr_word;
    return ans;
}

string NormalizujNapis(string str) {
    string ans;
    string curr_word;
    for (int i = 0; i < str.size(); i++) {     
        if (curr_word != "" && str[i] == ' ') {
            if (ans != "")
                ans += " ";
            ans += curr_word;
            curr_word = "";
        }
        if (str[i] != ' ' && str[i] != '.' && str[i] != ',')
            curr_word += str[i];
        else if (str[i] != ' ') {
            if (curr_word != "") {
                if (ans != "")
                    ans += " ";
                ans += curr_word;
                curr_word = "";
            }
            ans += str[i];
        }
    }

    if (curr_word != "") {
        if (ans != "")
            ans += " ";
        ans += curr_word;
    }

    return ans;
}

string UsunSlowo(string str, int id) {
    string ans;
    string curr_word;
    int cnt = 1;
    for (int i = 0; i < str.size(); i++) {     
        if (curr_word != "" && str[i] == ' ') {
            if (cnt != id)
                ans += curr_word;
            cnt++;
            curr_word = "";
        }
        if (str[i] != ' ')
            curr_word += str[i];
        else
            ans += str[i];
    }

    if (curr_word != "" && cnt != id)
            ans += curr_word;

    return ans;
}

string FormatujNapis(string str, string a, string b, string c) {
    string ans;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '{') {
            if(str[i + 1] == 'p') {
                int n = str[i + 3] - '0';
                char c = str[i + 5];
                while (n--) {
                    ans += c;
                }
                i += 6;
            } else if (str[i + 1] == 'u') {
                int n = str[i + 3] - '0';
                i += 4 + n;
            } else if (str[i + 1] == 'U') {
                int n = str[i + 3] - '0';
                string jd;
                for (int j = 0; j < ans.size() - n; j++) {
                    jd += ans[j];
                } 
                ans = jd;
                i += 4;
            } else if (str[i + 1] == 'w') {
                int n = str[i + 3] - '0';
                if (n == 1)
                    ans += a;
                else if (n == 2)
                    ans += b;
                else
                    ans += c;
                i += 4;
            } else if (str[i + 1] == 'W') {
                int n = str[i + 3] - '0';
                int m = str[i + 5] - '0';
                string curr;
                if (n == 1)
                    curr = a;
                else if (n == 2)
                    curr = b;
                else
                    curr = c;
                for (int j = 0; j < m; j++) {
                    if (j < curr.size())
                        ans += curr[j];
                    else
                        ans += ' ';
                }
                i += 6;
            }
        } else
            ans += str[i];
    }
    return ans;
}
