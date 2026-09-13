#include <bits/stdc++.h>
using namespace std;

string clean_ciphertext(const string& input) {
    string clean;
    for (unsigned char ch : input) {
        if (isalpha(ch))
            clean += static_cast<char>(toupper(ch));
    }
    return clean;
}

map<string, vector<int>> find_repeated_patterns(const string& text,
                                                 int min_len = 3,
                                                 int max_len = 5) {
    map<string, vector<int>> repeated;
    for (int len = min_len; len <= max_len; ++len) {
        unordered_map<string, vector<int>> pos;
        for (int i = 0; i + len <= static_cast<int>(text.size()); ++i)
            pos[text.substr(i, len)].push_back(i);

        for (const auto& [pattern, positions] : pos) {
            if (positions.size() > 1)
                repeated[pattern] = positions;
        }
    }
    return repeated;
}

vector<int> calculate_distances(const vector<int>& positions) {
    vector<int> distances;
    for (size_t i = 1; i < positions.size(); ++i)
        distances.push_back(positions[i] - positions[i - 1]);
    return distances;
}

vector<int> find_factors(const vector<int>& distances, int max_factor = 20) {
    vector<int> factors;
    for (int d : distances) {
        for (int f = 2; f <= max_factor; ++f) {
            if (d % f == 0)
                factors.push_back(f);
        }
    }
    return factors;
}

int kasiski_analysis(const string& text, ostream& out) {
    auto repeated = find_repeated_patterns(text);
    vector<int> all_distances;

    out << "KASISKI ANALYSIS\n";
    out << "Repeated patterns (length 3-5):\n";

    for (const auto& [pattern, positions] : repeated) {
        auto distances = calculate_distances(positions);
        all_distances.insert(all_distances.end(), distances.begin(), distances.end());

        out << "  " << pattern << " : positions ";
        for (int p : positions) out << p << " ";
        out << "| distances ";
        for (int d : distances) out << d << " ";
        out << "\n";
    }

    auto factors = find_factors(all_distances, 20);
    map<int, int> factor_count;
    for (int f : factors) ++factor_count[f];

    out << "\nFactor frequency (2-20):\n";
    for (const auto& [f, count] : factor_count)
        out << "  " << f << " -> " << count << "\n";

    vector<int> candidates;
    for (int k = 2; k <= 20; ++k)
        if (factor_count[k] > 0)
            candidates.push_back(k);

    double best_score = -1e9;
    int best_len = 1;

    for (int k : candidates) {
        double avg_ic = 0.0;
        for (int col = 0; col < k; ++col) {
            int n = 0;
            array<int, 26> count{};
            for (int i = col; i < static_cast<int>(text.size()); i += k) {
                ++count[text[i] - 'A'];
                ++n;
            }
            if (n > 1) {
                long long numerator = 0;
                for (int x : count) numerator += 1LL * x * (x - 1);
                avg_ic += static_cast<double>(numerator) / (n * (n - 1));
            }
        }
        avg_ic /= k;

        double score = factor_count[k] + 350.0 * avg_ic;
        if (score > best_score) {
            best_score = score;
            best_len = k;
        }
    }

    out << "\nEstimated key length: " << best_len << "\n";
    return best_len;
}

double calculate_ic(const string& text) {
    if (text.size() < 2) return 0.0;
    array<int, 26> count{};
    for (char c : text) ++count[c - 'A'];

    long long numerator = 0;
    for (int x : count) numerator += 1LL * x * (x - 1);
    return static_cast<double>(numerator) /
           (static_cast<double>(text.size()) * (text.size() - 1));
}

vector<string> split_into_groups(const string& text, int key_len) {
    vector<string> groups(key_len);
    for (size_t i = 0; i < text.size(); ++i)
        groups[i % key_len] += text[i];
    return groups;
}


vector<array<int, 26>> frequency_analysis(const vector<string>& groups) {
    vector<array<int, 26>> table(groups.size());
    for (size_t g = 0; g < groups.size(); ++g) {
        table[g].fill(0);
        for (char c : groups[g]) ++table[g][c - 'A'];
    }
    return table;
}


int find_shift(const array<int, 26>& counts) {
    static const double english[26] = {
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
        0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
        0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
        0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
        0.01974, 0.00074
    };

    int n = accumulate(counts.begin(), counts.end(), 0);
    int best_shift = 0;
    double best_chi = 1e100;

    for (int shift = 0; shift < 26; ++shift) {
        double chi = 0.0;
        for (int plain = 0; plain < 26; ++plain) {
            int cipher_index = (plain + shift) % 26;
            double expected = n * english[plain];
            if (expected > 0) {
                double diff = counts[cipher_index] - expected;
                chi += diff * diff / expected;
            }
        }
        if (chi < best_chi) {
            best_chi = chi;
            best_shift = shift;
        }
    }
    return best_shift;
}


string find_key(const vector<array<int, 26>>& freq_table) {
    string key;
    for (const auto& counts : freq_table)
        key += static_cast<char>('A' + find_shift(counts));
    return key;
}


string vigenere_decrypt(const string& ciphertext, const string& key) {
    string plaintext;
    plaintext.reserve(ciphertext.size());

    for (size_t i = 0; i < ciphertext.size(); ++i) {
        int c = ciphertext[i] - 'A';
        int k = key[i % key.size()] - 'A';
        plaintext += static_cast<char>('A' + (c - k + 26) % 26);
    }
    return plaintext;
}


string vigenere_encrypt(const string& plaintext, const string& key) {
    string ciphertext;
    ciphertext.reserve(plaintext.size());

    for (size_t i = 0; i < plaintext.size(); ++i) {
        int p = plaintext[i] - 'A';
        int k = key[i % key.size()] - 'A';
        ciphertext += static_cast<char>('A' + (p + k) % 26);
    }
    return ciphertext;
}


bool verify(const string& original, const string& reencrypted) {
    return original == reencrypted;
}

int main(){
    const string INPUT_FILE = "../../datasets/ciphertext.txt";
    const string OUTPUT_FILE = "../../outputs/output.txt";
    const int GROUP_NUMBER = 11;

    ifstream fin(INPUT_FILE);
    if (!fin)
    {
        cerr << "Error: cannot open " << INPUT_FILE << "\n";
        return 1;
    }

    string raw((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    string ciphertext = clean_ciphertext(raw);
    if (ciphertext.empty())
    {
        cerr << "Error: ciphertext is empty.\n";
        return 1;
    }

    ofstream out(OUTPUT_FILE);
    if (!out)
    {
        cerr << "Error: cannot create " << OUTPUT_FILE << "\n";
        return 1;
    }

    out << "VIGENERE CRYPTANALYSIS - KASISKI EXAMINATION + FREQUENCY ANALYSIS\n";
    out << "Group Number: " << GROUP_NUMBER << "\n";
    out << "Ciphertext length after preprocessing: " << ciphertext.size() << "\n\n";

    int key_length = kasiski_analysis(ciphertext, out);

    auto groups = split_into_groups(ciphertext, key_length);
    auto freq_table = frequency_analysis(groups);
    string key = find_key(freq_table);

    out << "\nINDEX OF COINCIDENCE\n";
    out << fixed << setprecision(5);
    out << "Whole ciphertext IC: " << calculate_ic(ciphertext) << "\n";
    out << "Average IC for key length " << key_length << ": ";
    double avg_ic = 0.0;
    for (const auto &group : groups)
        avg_ic += calculate_ic(group);
    avg_ic /= groups.size();
    out << avg_ic << "\n";

    out << "\nFREQUENCY TABLES FOR EACH GROUP\n";
    out << "Group  Size  ";
    for (char c = 'A'; c <= 'Z'; ++c)
        out << c << " ";
    out << "\n";

    for (size_t i = 0; i < groups.size(); ++i)
    {
        out << setw(5) << i + 1 << " " << setw(4) << groups[i].size() << "  ";
        for (int x : freq_table[i])
            out << setw(2) << x << " ";
        out << "\n";
    }

    out << "\nRECOVERED KEY\n";
    out << key << "\n";

    string plaintext = vigenere_decrypt(ciphertext, key);
    string reencrypted = vigenere_encrypt(plaintext, key);

    out << "\nRECOVERED PLAINTEXT\n";
    out << plaintext << "\n";

    out << "\nVERIFICATION\n";
    out << "Re-encrypted ciphertext matches original: "
        << (verify(ciphertext, reencrypted) ? "YES" : "NO") << "\n";

    out.close();

    cout << "Done.\n";
    cout << "Input : " << INPUT_FILE << "\n";
    cout << "Output: " << OUTPUT_FILE << "\n";
    cout << "Estimated key length: " << key_length << "\n";
    cout << "Recovered key: " << key << "\n";
    cout << "Verification: " << (verify(ciphertext, reencrypted) ? "PASSED" : "FAILED") << "\n";
	return 0;
}
