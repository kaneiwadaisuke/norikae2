#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

class Station;

class Connection {
public:
    Station* station;
    int distance;
    string lineName;

    Connection(Station* s, int d, string l) : station(s), distance(d), lineName(l) {}
};

class Station {
public:
    string name;
    vector<Connection> connections;

    Station(string n) : name(n) {}

    void addConnection(Station* station, int distance, string lineName) {
        connections.emplace_back(station, distance, lineName);
    }
};

class SubwaySystem {
public:
    unordered_map<string, Station*> stations;

    void addStation(string name) {
        stations[name] = new Station(name);
    }

    void addConnection(string from, string to, int distance, string lineName) {
        stations[from]->addConnection(stations[to], distance, lineName);
        stations[to]->addConnection(stations[from], distance, lineName);
    }

    void findShortestRoute(string start, string destination) {
        unordered_map<string, int> distances;
        unordered_map<string, pair<string, string>> previous; 
        for (auto& station : stations) {
            distances[station.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;

        auto compare = [&distances](string left, string right) { return distances[left] > distances[right]; };
        priority_queue<string, vector<string>, decltype(compare)> queue(compare);

        queue.push(start);

        while (!queue.empty()) {
            string current = queue.top();
            queue.pop();

            if (current == destination) {
                break;
            }

            for (auto& neighbor : stations[current]->connections) {
                int alt = distances[current] + neighbor.distance;
                if (alt < distances[neighbor.station->name]) {
                    distances[neighbor.station->name] = alt;
                    previous[neighbor.station->name] = { current, neighbor.lineName };
                    queue.push(neighbor.station->name);
                }
            }
        }

        printRoute(previous, start, destination);
    }

private:
    void printRoute(unordered_map<string, pair<string, string>>& previous, string start, string destination) {
        vector<string> path;
        vector<string> lines;
        for (string at = destination; at != start; at = previous[at].first) {
            path.push_back(at);
            lines.push_back(previous[at].second);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        reverse(lines.begin(), lines.end());

        if (path[0] == start) {
            cout << start << "Ç©ÇÁ" << destination << "Ç‹Ç≈" << ": " << endl;
            string lastLine = "";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < lines.size()) {
                    if (lines[i] != lastLine) {
                        cout << " (" << lines[i] << ")";
                        lastLine = lines[i];
                    }
                }
                if (i < path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
        else {
            cout << start << "Ç©ÇÁ" << destination << "Ç‹Ç≈ÇÃ" << "ÉãÅ[ÉgÇ™å©Ç¬Ç©ÇËÇ‹ÇπÇÒÇ≈ÇµÇΩÅB" << endl;
        }
    }
};

int main() {
    SubwaySystem system;

    // âwÇÃí«â¡
   
    //éRéËê¸
    system.addStation("ìåãû");
    system.addStation("óLäyí¨");
    system.addStation("êVã¥");
    system.addStation("ïlèºí¨");
    system.addStation("çÇó÷ÉQÅ[ÉgÉEÉFÉC");
    system.addStation("ìcí¨");
    system.addStation("ëÂçË");
    system.addStation("ïiêÏ");
    system.addStation("å‹îΩìc");
    system.addStation("ñ⁄çï");
    system.addStation("åbî‰éı");
    system.addStation("èaíJ");
    system.addStation("å¥èh");
    system.addStation("ë„ÅXñÿ");
    system.addStation("êVèh");
    system.addStation("êVëÂãvï€");
    system.addStation("çÇìcînèÍ");
    system.addStation("ñ⁄îí");
    system.addStation("írë‹");
    system.addStation("ëÂíÀ");
    system.addStation("ëÉäõ");
    system.addStation("ãÓçû");
    system.addStation("ìcí[");
    system.addStation("êºì˙ïÈó¢");
    system.addStation("ì˙ïÈó¢");
    system.addStation("ÈÚíJ");
    system.addStation("è„ñÏ");
    system.addStation("å‰ìkí¨");
    system.addStation("èHótå¥");
    system.addStation("ê_ìc");
   
    //ãûïlìåñkê¸
    
    system.addStation("ëÂà‰í¨");
    system.addStation("ëÂêX");
    system.addStation("äóìc");
    system.addStation("ê‘âH");
    system.addStation("ìåè\è");
    system.addStation("â§éq");
    system.addStation("è„íÜó¢");

    //ëçïêê¸
    system.addStation("înãÚí¨");
    system.addStation("ìåì˙ñ{ã¥");
    system.addStation("êÛëêã¥");
    system.addStation("óºçë");
    system.addStation("ã—éÖí¨");
    system.addStation("ãTåÀ");
    system.addStation("ïΩà‰");
    system.addStation("êVè¨ä‚");
    system.addStation("è¨ä‚");
    
    //íÜâõê¸
    system.addStation("Ç®íÉÇÃêÖ");
    system.addStation("êÖìπã¥");
    system.addStation("ésÉñíJ");
    system.addStation("î—ìcã¥");
    system.addStation("élÉcíJ");
    system.addStation("êMîZí¨");
    system.addStation("êÁë ÉñíJ");
    system.addStation("ëÂãvï€");
    system.addStation("ìåíÜñÏ");
    system.addStation("íÜñÏ");
    system.addStation("çÇâ~éõ");
    system.addStation("à¢ç≤ÉñíJ");
    system.addStation("â¨åE");
    system.addStation("êºâ¨åE");
    system.addStation("ãgèÀéõ");
    system.addStation("éOëÈ");
  
    //ÇªÇÃëº
    system.addStation("ïÇä‘èMìn");
    system.addStation("ñkê‘âH");
    system.addStation("è\è");
    system.addStation("î¬ã¥");
    system.addStation("îˆãv");
    system.addStation("ñkêÁèZ");
    system.addStation("ìÏêÁèZ");
    system.addStation("éOâÕìá");
    system.addStation("àªê£");
    system.addStation("ãTóL");
    system.addStation("ã‡í¨");
    system.addStation("êºëÂà‰");
    system.addStation("î™íöñx");
    system.addStation("âzíÜìá");
    system.addStation("í™å©");
    system.addStation("êVñÿèÍ");
    system.addStation("äãêºó’äCåˆâÄ");

    // ê⁄ë±ÇÃí«â¡ (âºÇÃãóó£Ç∆òHê¸ñºÇ≈ê›íË)
    
    // éRéËê¸ (Yamanote Line)
    system.addConnection("ìåãû", "óLäyí¨", 2, "éRéËê¸");
    system.addConnection("óLäyí¨", "êVã¥", 2, "éRéËê¸");
    system.addConnection("êVã¥", "ïlèºí¨", 2, "éRéËê¸");
    system.addConnection("ïlèºí¨", "çÇó÷ÉQÅ[ÉgÉEÉFÉC", 2, "éRéËê¸");
    system.addConnection("çÇó÷ÉQÅ[ÉgÉEÉFÉC", "ìcí¨", 2, "éRéËê¸");
    system.addConnection("ìcí¨", "ëÂçË", 2, "éRéËê¸");
    system.addConnection("ëÂçË", "ïiêÏ", 3, "éRéËê¸");
    system.addConnection("ïiêÏ", "å‹îΩìc", 2, "éRéËê¸");
    system.addConnection("å‹îΩìc", "ñ⁄çï", 2, "éRéËê¸");
    system.addConnection("ñ⁄çï", "åbî‰éı", 3, "éRéËê¸");
    system.addConnection("åbî‰éı", "èaíJ", 2, "éRéËê¸");
    system.addConnection("èaíJ", "å¥èh", 2, "éRéËê¸");
    system.addConnection("å¥èh", "ë„ÅXñÿ", 2, "éRéËê¸");
    system.addConnection("ë„ÅXñÿ", "êVèh", 2, "éRéËê¸");
    system.addConnection("êVèh", "êVëÂãvï€", 2, "éRéËê¸");
    system.addConnection("êVëÂãvï€", "çÇìcînèÍ", 2, "éRéËê¸");
    system.addConnection("çÇìcînèÍ", "ñ⁄îí", 2, "éRéËê¸");
    system.addConnection("ñ⁄îí", "írë‹", 3, "éRéËê¸");
    system.addConnection("írë‹", "ëÂíÀ", 2, "éRéËê¸");
    system.addConnection("ëÂíÀ", "ëÉäõ", 2, "éRéËê¸");
    system.addConnection("ëÉäõ", "ãÓçû", 2, "éRéËê¸");
    system.addConnection("ãÓçû", "ìcí[", 2, "éRéËê¸");
    system.addConnection("ìcí[", "êºì˙ïÈó¢", 2, "éRéËê¸");
    system.addConnection("êºì˙ïÈó¢", "ì˙ïÈó¢", 1, "éRéËê¸");
    system.addConnection("ì˙ïÈó¢", "ÈÚíJ", 2, "éRéËê¸");
    system.addConnection("ÈÚíJ", "è„ñÏ", 2, "éRéËê¸");
    system.addConnection("è„ñÏ", "å‰ìkí¨", 2, "éRéËê¸");
    system.addConnection("å‰ìkí¨", "èHótå¥", 2, "éRéËê¸");
    system.addConnection("èHótå¥", "ê_ìc", 2, "éRéËê¸");
    system.addConnection("ê_ìc", "ìåãû", 1, "éRéËê¸");

    // ãûïlìåñkê¸ (Keihin-Tohoku Line)
    system.addConnection("ëÂà‰í¨", "ëÂêX", 2, "ãûïlìåñkê¸");
    system.addConnection("ëÂêX", "äóìc", 2, "ãûïlìåñkê¸");
    system.addConnection("äóìc", "ïiêÏ", 2, "ãûïlìåñkê¸");
    system.addConnection("ê‘âH", "ìåè\è", 3, "ãûïlìåñkê¸");
    system.addConnection("ìåè\è", "â§éq", 3, "ãûïlìåñkê¸");
    system.addConnection("â§éq", "è„íÜó¢", 2, "ãûïlìåñkê¸");
    system.addConnection("â§éq", "è„íÜó¢", 3, "ãûïlìåñkê¸");
   
    // ëçïêê¸ (Sobu Line)
    system.addConnection("înãÚí¨", "ìåì˙ñ{ã¥", 3, "ëçïêâıë¨ê¸");
    system.addConnection("ìåì˙ñ{ã¥", "ìåãû", 4, "ëçïêâıë¨ê¸");
    system.addConnection("înãÚí¨", "ã—éÖí¨", 5, "ëçïêâıë¨ê¸");
    system.addConnection("êVè¨ä‚", "ã—éÖí¨", 5, "ëçïêâıë¨ê¸");
    system.addConnection("êÛëêã¥", "óºçë", 2, "ëçïêê¸");
    system.addConnection("óºçë", "ã—éÖí¨", 2, "ëçïêê¸");
    system.addConnection("ã—éÖí¨", "ãTåÀ", 2, "ëçïêê¸");
    system.addConnection("ãTåÀ", "ïΩà‰", 3, "ëçïêê¸");
    system.addConnection("ïΩà‰", "êVè¨ä‚", 2, "ëçïêê¸");
    system.addConnection("êVè¨ä‚", "è¨ä‚", 2, "ëçïêê¸");

    // íÜâõê¸ (Chuo Line)
    system.addConnection("Ç®íÉÇÃêÖ", "êÖìπã¥", 2, "íÜâõê¸");
    system.addConnection("êÖìπã¥", "ésÉñíJ", 2, "íÜâõê¸");
    system.addConnection("ésÉñíJ", "î—ìcã¥", 2, "íÜâõê¸");
    system.addConnection("î—ìcã¥", "élÉcíJ", 2, "íÜâõê¸");
    system.addConnection("élÉcíJ", "êMîZí¨", 2, "íÜâõê¸");
    system.addConnection("êMîZí¨", "êÁë ÉñíJ", 2, "íÜâõê¸");
    system.addConnection("êMîZí¨", "ë„ÅXñÿ", 1, "íÜâõê¸");
    system.addConnection("ëÂãvï€", "êVèh", 2, "íÜâõê¸");
    system.addConnection("êÁë ÉñíJ", "ëÂãvï€", 1, "íÜâõê¸");
    system.addConnection("ëÂãvï€", "ìåíÜñÏ", 1, "íÜâõê¸");
    system.addConnection("ìåíÜñÏ", "íÜñÏ", 1, "íÜâõê¸");
    system.addConnection("íÜñÏ", "çÇâ~éõ", 1, "íÜâõê¸");
    system.addConnection("çÇâ~éõ", "à¢ç≤ÉñíJ", 1, "íÜâõê¸");
    system.addConnection("à¢ç≤ÉñíJ", "â¨åE", 1, "íÜâõê¸");
    system.addConnection("â¨åE", "êºâ¨åE", 1, "íÜâõê¸");
    system.addConnection("êºâ¨åE", "ãgèÀéõ", 1, "íÜâõê¸");
    system.addConnection("ãgèÀéõ", "éOëÈ", 1, "íÜâõê¸");

    // íÜâõâıë¨ê¸ (Chuo Line)
    system.addConnection("Ç®íÉÇÃêÖ", "élÉcíJ", 2, "íÜâõâıë¨ê¸");
    system.addConnection("ê_ìc", "Ç®íÉÇÃêÖ", 2, "íÜâõâıë¨ê¸");
    system.addConnection("élÉcíJ", "êVèh", 2, "íÜâõâıë¨ê¸");
    system.addConnection("ìåãû", "ê_ìc", 1, "íÜâõâıë¨ê¸");
    // ÇªÇÃëº (Other Stations)
    //çÈãûê¸
    system.addConnection("ïÇä‘èMìn", "ñkê‘âH", 2, "çÈãûê¸");
    system.addConnection("ê‘âH", "ñkê‘âH", 2, "çÈãûê¸");
    system.addConnection("ê‘âH", "è\è", 2, "çÈãûê¸");
    system.addConnection("è\è", "î¬ã¥", 2, "çÈãûê¸");
    system.addConnection("î¬ã¥", "írë‹", 2, "çÈãûê¸");
    system.addConnection("ëÂçË", "èaíJ", 4, "çÈãûê¸");
    system.addConnection("èaíJ", "êVèh", 4, "çÈãûê¸");
    system.addConnection("êVèh", "írë‹", 5, "çÈãûê¸");

    system.addConnection("îˆãv", "ñkêÁèZ", 2, "ÇªÇÃëº");
    system.addConnection("ñkêÁèZ", "ìÏêÁèZ", 2, "ÇªÇÃëº");
    system.addConnection("ìÏêÁèZ", "éOâÕìá", 2, "ÇªÇÃëº");
    system.addConnection("éOâÕìá", "àªê£", 2, "ÇªÇÃëº");
    system.addConnection("àªê£", "ãTóL", 2, "ÇªÇÃëº");
    system.addConnection("ãTóL", "ã‡í¨", 2, "ÇªÇÃëº");
    system.addConnection("ã‡í¨", "êºëÂà‰", 2, "ÇªÇÃëº");
    system.addConnection("êºëÂà‰", "î™íöñx", 2, "ÇªÇÃëº");
    system.addConnection("î™íöñx", "âzíÜìá", 2, "ÇªÇÃëº");
    system.addConnection("âzíÜìá", "í™å©", 2, "ÇªÇÃëº");
    system.addConnection("í™å©", "êVñÿèÍ", 2, "ÇªÇÃëº");
    system.addConnection("êVñÿèÍ", "äãêºó’äCåˆâÄ", 2, "ÇªÇÃëº");


    // ÉÜÅ[ÉUÅ[ì¸óÕ
    string startStation, endStation;
    cout << "èÊé‘âwÇì¸óÕÇµÇƒâ∫Ç≥Ç¢: ";
    cin >> startStation;
    cout << "ç~é‘âwÇì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢: ";
    cin >> endStation;

    // åoòHåüçı
    system.findShortestRoute(startStation, endStation);

    return 0;
}
