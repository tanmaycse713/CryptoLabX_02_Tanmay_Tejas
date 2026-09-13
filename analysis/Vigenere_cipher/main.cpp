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

int main(){

	return 0;
}
