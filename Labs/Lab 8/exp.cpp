#include <bits/stdc++.h>
using namespace std;

class Term {
   private:
    string word;
    int score;

   public:
    Term(string w, int s) : word(w), score(s) {}
    string getTermWord() const { return word; }
    int getTermScore() const { return score; }
    bool operator==(const Term& t) const { return word == t.getTermWord(); }
    bool operator<(const Term& rhs) const { return word < rhs.getTermWord(); }
    int operator*(const Term& rhs) const { return score * rhs.getTermScore(); }
};

template <>
struct std::hash<Term> {
    std::size_t operator()(const Term& t) const {
        using std::hash;
        using std::size_t;
        using std::string;

        // return ((hash<string>()(t.getTermWord()) ^
        //          hash<int>()(t.getTermScore() << 1)) >>
        //         1);
        return hash<string>()(t.getTermWord());
    }
};

class Document {
   private:
    string title;
    string doc;
    vector<Term> vec;

   public:
    string getTitle() const { return title; }
    string getDoc() const { return doc; }
    bool operator<(const Document& rhs) const {
        if (title != rhs.getTitle()) {
            return doc < rhs.getDoc();
        }
        return title < rhs.getTitle();
    }
    Document(string title, string docu) {
        this->title = title;
        doc = docu;
        string temp = doc + " " + title;
        stringstream ss(temp);
        string word;

        unordered_map<string, int> mp;
        while (ss >> word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            mp[word]++;
        }

        for (auto x : mp) vec.push_back(Term(x.first, x.second));
    }
    vector<Term> getTerms() const { return vec; }
    string getDocText() const { return doc; }
};

class Index {
   private:
    unordered_map<Term, vector<Document>> mpp;
    unordered_set<Term> totalTerms;
    static bool comp(const pair<Document, int>& p1,
                     const pair<Document, int>& p2) {
        return p1.second > p2.second;
    }
    int dotProd(vector<Term> v1, vector<Term> v2) {
        int score = 0;
        for (auto x : v1) {
            auto it = find(v2.begin(), v2.end(), x);
            if (it != v2.end()) {
                score += (*it) * x;
            }
        }
        return score;
    }
    map<Document, int> findRelevantDocs(vector<Term> queryTerms) {
        map<Document, int> r;
        for (auto x : queryTerms) {
            vector<Document> documentsContainingQueryTerm = mpp[x];
            for (auto doc : documentsContainingQueryTerm) {
                vector<Term> termsInDoc = doc.getTerms();
                r.insert({doc, dotProd(queryTerms, termsInDoc)});
            }
        }
        return r;
    }
    vector<pair<Document, int>> sortDocs(map<Document, int> r) {
        vector<pair<Document, int>> res;
        for (auto x : r) {
            res.push_back({x.first, x.second});
        }
        sort(res.begin(), res.end(), comp);
        return res;
    }

   public:
    Index(vector<Document> vec) {
        for (auto doc : vec) {
            vector<Term> termsInDoc = doc.getTerms();
            for (auto term : termsInDoc) {
                mpp[term].push_back(doc);
            }
        }
    }
    vector<pair<Document, int>> search(string query) {
        stringstream ss(query);
        string word;
        unordered_map<string, int> m;
        while (ss >> word) m[word]++;

        vector<Term> queryTerms;
        for (auto x : m) queryTerms.push_back(Term(x.first, x.second));

        map<Document, int> relDocs = findRelevantDocs(queryTerms);
        return sortDocs(relDocs);
    }
};

int main() {
    Document doc1(
        "Malaria",
        "Malaria is a mosquito-borne infectious disease that affects humans "
        "and other vertebrates. Human malaria causes symptoms that "
        "typically include fever, fatigue, vomiting, and headaches. In "
        "severe cases, it can cause jaundice, seizures, coma, or death. "
        "Symptoms usually begin 10 to 15 days after being bitten by an "
        "infected Anopheles mosquito. If not properly treated, people "
        "may have recurrences of the disease months later.In those who "
        "have recently survived an infection, reinfection usually causes "
        "milder symptoms. This partial resistance disappears over months to "
        "years if the person has no continuing exposure to malaria. Human "
        "malaria is caused by single-celled microorganisms of the Plasmodium "
        "group. It is spread exclusively through bites of infected female "
        "Anopheles mosquitoes. The mosquito bite introduces the "
        "parasites from the mosquito's saliva into a person's blood.The "
        "parasites travel to the liver where they mature and reproduce. "
        "Five species of Plasmodium can infect and be spread by humans. "
        "Most deaths are caused by P. falciparum, whereas P. vivax, P. ovale, "
        "and P. malariae generally cause a milder form of malaria. The "
        "species P. knowlesi rarely causes disease in humans.Malaria is "
        "typically diagnosed by the microscopic examination of blood using "
        "blood films, or with antigen-based rapid diagnostic tests. Methods "
        "that use the polymerase chain reaction to detect the parasites DNA "
        "have been developed, but they are not widely used in areas where "
        "malaria is common, due to their cost and complexity. The risk of "
        "disease can be reduced by preventing mosquito bites through the use "
        "of mosquito nets and insect repellents or with mosquito-control "
        "measures such as spraying insecticides and draining standing "
        "water. Several medications are available to prevent malaria for "
        "travellers in areas where the disease is common.Occasional doses "
        "of the combination medication sulfadoxine/pyrimethamine are "
        "recommended in infants and after the first trimester of pregnancy in "
        "areas with high rates of malaria.Efforts to develop more "
        "effective malaria vaccines are ongoing. The recommended treatment "
        "for malaria is a combination of antimalarial medications that "
        "includes artemisinin.The second medication may be "
        "either mefloquine, lumefantrine, or sulfadoxine/pyrimethamine. "
        "Quinine, along with doxycycline, may be used if artemisinin is not "
        "available. In areas where the disease is common, malaria should "
        "be confirmed if possible before treatment is started due to concerns "
        "of increasing drug resistance.Resistance among the parasites has "
        "developed to several antimalarial medications; for example, "
        "chloroquine-resistant P. falciparum has spread to most malarial "
        "areas, and resistance to artemisinin has become a problem in some "
        "parts of Southeast Asia. The disease is widespread in the tropical "
        "and subtropical regions that exist in a broad band around the "
        "equator.[15] This includes much of sub-Saharan Africa, Asia, and "
        "Latin America.In 2021, some 247 million cases of malaria "
        "worldwide resulted in an estimated 619,000 deaths, with 77 percent "
        "being 5 years old or less. Around 95% of the cases and deaths "
        "occurred in sub-Saharan Africa. Rates of disease decreased from 2010 "
        "to 2014, but increased from 2015 to 2021.[5] Malaria is commonly "
        "associated with poverty and has a significant negative effect on "
        "economic development. In Africa, it is estimated to result in "
        "losses of US$12 billion a year due to increased healthcare costs, "
        "lost ability to work, and adverse effects on tourism. UNICEF has "
        "reported that nearly every minute, a child under five dies of "
        "malaria, and that many of these deaths are preventable and treatable");
    Document doc2(
        "microRNA",
        "MicroRNA (miRNA) are small, single-stranded, non-coding RNA molecules "
        "containing 21 to 23 nucleotides. Found in plants, animals and some "
        "viruses, miRNAs are involved in RNA silencing and "
        "post-transcriptional regulation of gene expression. miRNAs "
        "base-pair to complementary sequences in mRNA molecules, then gene "
        "silence said mRNA molecules by one or more of the following "
        "processes: Cleavage of mRNA strand into two pieces, Destabilization "
        "of mRNA by shortening its poly(A) tail, or Translation of mRNA into "
        "proteins. This last method of gene silencing is the least efficient "
        "of the three, and requires the aid of ribosomes. miRNAs resemble the "
        "small interfering RNAs (siRNAs) of the RNA interference (RNAi) "
        "pathway, except miRNAs derive from regions of RNA transcripts that "
        "fold back on themselves to form short hairpins, whereas siRNAs derive "
        "from longer regions of double-stranded RNA. The human genome may "
        "encode over 1900 miRNAs, although more recent analysis suggests "
        "that the number is closer to 2,300. However, only about 500 human "
        "microRNAs represent bona fide miRNA in the manually curated miRNA "
        "gene database MirGeneDB. miRNAs are abundant in many mammalian cell "
        "types and as extracellular circulating miRNAs."
        "Circulating miRNAs are released into body fluids including blood and "
        "cerebrospinal fluid and have the potential to be available as "
        "biomarkers in a number of diseases. MiRNAs appear to target "
        "about 60% of the genes of humans and other mammals. Many "
        "miRNAs are evolutionarily conserved, which implies that they have "
        "important biological functions. For example, 90 families of "
        "miRNAs have been conserved since at least the common ancestor of "
        "mammals and fish, and most of these conserved miRNAs have important "
        "functions, as shown by studies in which genes for one or more members "
        "of a family have been knocked out in mice.");

    Document doc3(
        "Israel",
        "Israel is located in the Southern Levant, a region known historically "
        "as Canaan, the Land of Israel, Palestine and the Holy Land. In "
        "ancient times, the region was home to several Israelite and Jewish "
        "kingdoms, including Israel and Judah and Hasmonean Judea. Over the "
        "ages, the region witnessed rule by imperial powers such as the "
        "Assyrians, Babylonians, Persians, Greeks, and Romans. The "
        "Jewish-Roman wars initiated a process which turned Jews from a "
        "majority population in the region into a widely dispersed people. The "
        "region later came under Byzantine and Arab rule. In the medieval "
        "period, it was part of the Islamic Caliphates, the Crusader Kingdom "
        "of Jerusalem, and the Ottoman Empire. The late 19th century saw the "
        "rise of Zionism, a movement advocating for the establishment of a "
        "Jewish homeland, during which the Jewish people began purchasing land "
        "in Palestine. British control under the League of Nations after World "
        "War I, known as the British Mandate, heightened tensions between "
        "Jewish and Arab communities. The UN-approved 1947 partition plan "
        "subsequently triggered a civil war between these two communities. The "
        "British terminated the Mandate on 14 May 1948, and Israel declared "
        "independence that day. Upon its independence, Israel became almost "
        "immediately embroiled in conflict with its five neighboring Arab "
        "states, whose armies began entering the area of the former Mandatory "
        "Palestine on 15 May, starting the 1948 Arab-Israeli War. Early the "
        "next year, the 1949 Armistice Agreements left Israel in control of "
        "over one-third more territory than the partition plan had called for, "
        "with no independent Arab state created. During both stages of the "
        "1948 Palestine war, over 700,000 Palestinian Arabs were expelled from "
        "or fled Israeli territory to Jordanian-ruled West Bank, "
        "Egyptian-controlled Gaza, and the neighboring Arab countries, with "
        "fewer than 150,000 Palestinian Arabs remaining within Israel. During "
        "and immediately after the war, around 260,000 Jews emigrated or fled "
        "from the Arab world to Israel. The 1967 Six-Day War tripled the size "
        "of territory under Israel's control and resulted in the Israeli "
        "occupation of the West Bank and Gaza Strip, along with the Egyptian "
        "Sinai Peninsula and the Syrian Golan Heights. Israel has since "
        "effectively annexed both East Jerusalem and the Golan Heights, and "
        "has established settlements across the Israeli-occupied territories, "
        "actions the international community has rejected as illegal under "
        "international law. Since the 1973 Yom Kippur War, Israel has signed "
        "peace treaties with Egypt, returning the Sinai Peninsula, and with "
        "Jordan, and more recently normalized relations with several Arab "
        "countries, though efforts to resolve the Israeli-Palestinian conflict "
        "have not succeeded. Israel's practices in its occupation of the "
        "Palestinian territories, the longest military occupation in modern "
        "history, have drawn international condemnation for violating the "
        "human rights of the Palestinians.");

    vector<Document> docs = {doc1, doc2, doc3};

    Index indx(docs);

    // q: plasmodium rna transcripts - s5
    // q: rna transcripts viruses - s5

    cout << "Enter query now: " << endl;

    while (true) {
        string query;
        getline(cin, query);
        if (query == "break") break;
        vector<pair<Document, int>> res = indx.search(query);
        cout << "Ordered results for query: \"" << query << "\"" << endl;
        for (auto x : res) {
            cout << x.first.getTitle() << " (score: " << x.second << ")"
                 << endl;
        }
    }

    // string query = "oops about object";
    // vector<pair<Document, int>> res = indx.search(query);
    // cout << "Ordered results for query: \"" << query << "\"" << endl;
    // for (auto x : res) {
    //     cout << x.first.getTitle() << " (score: " << x.second << ")" << endl;
    // }

    return 0;
}