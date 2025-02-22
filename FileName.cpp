#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include<algorithm>

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
            cout << start << "から" << destination << "まで" << ": " << endl;
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
            cout << start << "から" << destination << "までの" << "ルートが見つかりませんでした。" << endl;
        }
    }
};

int main() {
    SubwaySystem system;

    // 駅の追加
   
    //山手線
    system.addStation("東京");
    system.addStation("有楽町");
    system.addStation("新橋");
    system.addStation("浜松町");
    system.addStation("高輪ゲートウェイ");
    system.addStation("田町");
    system.addStation("大崎");
    system.addStation("品川");
    system.addStation("五反田");
    system.addStation("目黒");
    system.addStation("恵比寿");
    system.addStation("渋谷");
    system.addStation("原宿");
    system.addStation("代々木");
    system.addStation("新宿");
    system.addStation("新大久保");
    system.addStation("高田馬場");
    system.addStation("目白");
    system.addStation("池袋");
    system.addStation("大塚");
    system.addStation("巣鴨");
    system.addStation("駒込");
    system.addStation("田端");
    system.addStation("西日暮里");
    system.addStation("日暮里");
    system.addStation("鶯谷");
    system.addStation("上野");
    system.addStation("御徒町");
    system.addStation("秋葉原");
    system.addStation("神田");
   
    //京浜東北線
    
    system.addStation("大井町");
    system.addStation("大森");
    system.addStation("蒲田");
    system.addStation("赤羽");
    system.addStation("東十条");
    system.addStation("王子");
    system.addStation("上中里");

    //総武線
    system.addStation("馬喰町");
    system.addStation("東日本橋");
    system.addStation("浅草橋");
    system.addStation("両国");
    system.addStation("錦糸町");
    system.addStation("亀戸");
    system.addStation("平井");
    system.addStation("新小岩");
    system.addStation("小岩");
    
    //中央線
    system.addStation("お茶の水");
    system.addStation("水道橋");
    system.addStation("市ヶ谷");
    system.addStation("飯田橋");
    system.addStation("四ツ谷");
    system.addStation("信濃町");
    system.addStation("千駄ヶ谷");
    system.addStation("大久保");
    system.addStation("東中野");
    system.addStation("中野");
    system.addStation("高円寺");
    system.addStation("阿佐ヶ谷");
    system.addStation("荻窪");
    system.addStation("西荻窪");
    system.addStation("吉祥寺");
    system.addStation("三鷹");
  
    //その他
    system.addStation("浮間舟渡");
    system.addStation("北赤羽");
    system.addStation("十条");
    system.addStation("板橋");
    system.addStation("尾久");
    system.addStation("北千住");
    system.addStation("南千住");
    system.addStation("三河島");
    system.addStation("綾瀬");
    system.addStation("亀有");
    system.addStation("金町");
    system.addStation("西大井");
    system.addStation("八丁堀");
    system.addStation("越中島");
    system.addStation("潮見");
    system.addStation("新木場");
    system.addStation("葛西臨海公園");

    // 接続の追加 (仮の距離と路線名で設定)
    
    // 山手線 (Yamanote Line)
    system.addConnection("東京", "有楽町", 2, "山手線");
    system.addConnection("有楽町", "新橋", 2, "山手線");
    system.addConnection("新橋", "浜松町", 2, "山手線");
    system.addConnection("浜松町", "高輪ゲートウェイ", 2, "山手線");
    system.addConnection("高輪ゲートウェイ", "田町", 2, "山手線");
    system.addConnection("田町", "大崎", 2, "山手線");
    system.addConnection("大崎", "品川", 3, "山手線");
    system.addConnection("品川", "五反田", 2, "山手線");
    system.addConnection("五反田", "目黒", 2, "山手線");
    system.addConnection("目黒", "恵比寿", 3, "山手線");
    system.addConnection("恵比寿", "渋谷", 2, "山手線");
    system.addConnection("渋谷", "原宿", 2, "山手線");
    system.addConnection("原宿", "代々木", 2, "山手線");
    system.addConnection("代々木", "新宿", 2, "山手線");
    system.addConnection("新宿", "新大久保", 2, "山手線");
    system.addConnection("新大久保", "高田馬場", 2, "山手線");
    system.addConnection("高田馬場", "目白", 2, "山手線");
    system.addConnection("目白", "池袋", 3, "山手線");
    system.addConnection("池袋", "大塚", 2, "山手線");
    system.addConnection("大塚", "巣鴨", 2, "山手線");
    system.addConnection("巣鴨", "駒込", 2, "山手線");
    system.addConnection("駒込", "田端", 2, "山手線");
    system.addConnection("田端", "西日暮里", 2, "山手線");
    system.addConnection("西日暮里", "日暮里", 1, "山手線");
    system.addConnection("日暮里", "鶯谷", 2, "山手線");
    system.addConnection("鶯谷", "上野", 2, "山手線");
    system.addConnection("上野", "御徒町", 2, "山手線");
    system.addConnection("御徒町", "秋葉原", 2, "山手線");
    system.addConnection("秋葉原", "神田", 2, "山手線");
    system.addConnection("神田", "東京", 1, "山手線");

    // 京浜東北線 (Keihin-Tohoku Line)
    system.addConnection("大井町", "大森", 2, "京浜東北線");
    system.addConnection("大森", "蒲田", 2, "京浜東北線");
    system.addConnection("蒲田", "品川", 2, "京浜東北線");
    system.addConnection("赤羽", "東十条", 3, "京浜東北線");
    system.addConnection("東十条", "王子", 3, "京浜東北線");
    system.addConnection("王子", "上中里", 2, "京浜東北線");
    system.addConnection("王子", "上中里", 3, "京浜東北線");
   
    // 総武線 (Sobu Line)
    system.addConnection("馬喰町", "東日本橋", 3, "総武快速線");
    system.addConnection("東日本橋", "東京", 4, "総武快速線");
    system.addConnection("馬喰町", "錦糸町", 5, "総武快速線");
    system.addConnection("新小岩", "錦糸町", 5, "総武快速線");
    system.addConnection("浅草橋", "両国", 2, "総武線");
    system.addConnection("両国", "錦糸町", 2, "総武線");
    system.addConnection("錦糸町", "亀戸", 2, "総武線");
    system.addConnection("亀戸", "平井", 3, "総武線");
    system.addConnection("平井", "新小岩", 2, "総武線");
    system.addConnection("新小岩", "小岩", 2, "総武線");

    // 中央線 (Chuo Line)
    system.addConnection("お茶の水", "水道橋", 2, "中央線");
    system.addConnection("水道橋", "市ヶ谷", 2, "中央線");
    system.addConnection("市ヶ谷", "飯田橋", 2, "中央線");
    system.addConnection("飯田橋", "四ツ谷", 2, "中央線");
    system.addConnection("四ツ谷", "信濃町", 2, "中央線");
    system.addConnection("信濃町", "千駄ヶ谷", 2, "中央線");
    system.addConnection("信濃町", "代々木", 1, "中央線");
    system.addConnection("大久保", "新宿", 2, "中央線");
    system.addConnection("千駄ヶ谷", "大久保", 1, "中央線");
    system.addConnection("大久保", "東中野", 1, "中央線");
    system.addConnection("東中野", "中野", 1, "中央線");
    system.addConnection("中野", "高円寺", 1, "中央線");
    system.addConnection("高円寺", "阿佐ヶ谷", 1, "中央線");
    system.addConnection("阿佐ヶ谷", "荻窪", 1, "中央線");
    system.addConnection("荻窪", "西荻窪", 1, "中央線");
    system.addConnection("西荻窪", "吉祥寺", 1, "中央線");
    system.addConnection("吉祥寺", "三鷹", 1, "中央線");

    // 中央快速線 (Chuo Line)
    system.addConnection("お茶の水", "四ツ谷", 2, "中央快速線");
    system.addConnection("神田", "お茶の水", 2, "中央快速線");
    system.addConnection("四ツ谷", "新宿", 2, "中央快速線");
    system.addConnection("東京", "神田", 1, "中央快速線");
    // その他 (Other Stations)
    //埼京線
    system.addConnection("浮間舟渡", "北赤羽", 2, "埼京線");
    system.addConnection("赤羽", "北赤羽", 2, "埼京線");
    system.addConnection("赤羽", "十条", 2, "埼京線");
    system.addConnection("十条", "板橋", 2, "埼京線");
    system.addConnection("板橋", "池袋", 2, "埼京線");
    system.addConnection("大崎", "渋谷", 4, "埼京線");
    system.addConnection("渋谷", "新宿", 4, "埼京線");
    system.addConnection("新宿", "池袋", 5, "埼京線");

    system.addConnection("尾久", "北千住", 2, "その他");
    system.addConnection("北千住", "南千住", 2, "その他");
    system.addConnection("南千住", "三河島", 2, "その他");
    system.addConnection("三河島", "綾瀬", 2, "その他");
    system.addConnection("綾瀬", "亀有", 2, "その他");
    system.addConnection("亀有", "金町", 2, "その他");
    system.addConnection("金町", "西大井", 2, "その他");
    system.addConnection("西大井", "八丁堀", 2, "その他");
    system.addConnection("八丁堀", "越中島", 2, "その他");
    system.addConnection("越中島", "潮見", 2, "その他");
    system.addConnection("潮見", "新木場", 2, "その他");
    system.addConnection("新木場", "葛西臨海公園", 2, "その他");


    // ユーザー入力
    string startStation, endStation;
    cout << "乗車駅を入力して下さい: ";
    cin >> startStation;
    cout << "降車駅を入力してください: ";
    cin >> endStation;

    // 経路検索
    system.findShortestRoute(startStation, endStation);

    return 0;
}
